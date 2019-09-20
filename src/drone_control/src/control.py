#!/usr/bin/env python
import rospy
import numpy as np
import math

from geometry_msgs.msg import PoseStamped, TwistStamped, Twist, Point
from nav_msgs.msg import Odometry
from std_msgs.msg import Float64, Empty, Bool
from std_srvs.srv import Trigger, TriggerRequest, TriggerResponse, SetBool, SetBoolRequest, SetBoolResponse
from bebop_msgs.msg import Ardrone3PilotingStateAltitudeChanged
import ros_numpy

from PID import PID

from dynamic_reconfigure.server import Server
from drone_control.cfg import ControlConfig

import time


class vso_controler(object): # visual odometry drone controler
    
    goal_pose = np.array([0.0,0.0,1.0])
    current_pose = np.array([0.0,0.0,1.0])
    positioning_vel = np.array([0.0,0.0,1.0])
    angle_pose = 0.0

    pid_x = PID(P=0.0,I=0.0,D=0.0)
    pid_y = PID(P=0.0,I=0.0,D=0.0)
    pid_z = PID(P=0.0,I=0.0,D=0.0)

    camera_angle = Twist()
    setted_vel = Twist()

    control_mode = "position" # position or velocity  
    trust_vso = 0
    last_vso_time = 0 

    def __init__(self):

        #setup node
        rospy.init_node('Vel_Control_Node', anonymous=True)
        self.rate = rospy.Rate(60)  # refresh rate (Hz)

        #topics and services
        self.setpoint_velocity_pub = rospy.Publisher('/bebop/cmd_vel', Twist, queue_size=1)
        self.camera_angle_pub = rospy.Publisher('/bebop/camera_control', Twist, queue_size=10)

        self.running = rospy.get_param('~running',True)
        self.vso_on = rospy.get_param('~vso_on',True)
        self.config_file = rospy.get_param('~config_file',"default.json")
        calibrate_pid = rospy.get_param('~calibrate_pid',False)

        rospy.Subscriber('/bebop/land', Empty, self.land)
        rospy.Subscriber('/bebop/takeoff', Empty, self.takeoff)
        
        rospy.Subscriber('/odom_slam_sf/current_coord', Point, self.position_callback)

        rospy.Subscriber('/bebop/odom/', Odometry, self.odometry_callback)

        rospy.Subscriber('/control/position', Point, self.position_callback)
        rospy.Subscriber('/control/position_relative', Point, self.position_relative_callback)
        rospy.Subscriber('/control/velocity', Point, self.velocity_callback)
        rospy.Subscriber('/control/rotation', Float64, self.rotation_callback)
        # rospy.Subscriber('/control/land', Empty, self.land)

        rospy.Service('/control/reset_vso_coords', Trigger , self.reset_vso_position_service)
        rospy.Service('/control/calibrate_pid', SetBool, self.set_calibrate_pid)

        self.running_sub = rospy.Subscriber(
            "control/set_runnig_state", Bool, self.set_runninng_state, queue_size=1)

        self.current_pose_pub = rospy.Publisher(
            "control/current_position", Point, queue_size=1)
        #dynamic parameters serve
        if calibrate_pid:
            srv = Server(ControlConfig, self.parameters_callback)
        
        t = time.time()
        rospy.loginfo("aligning camera")
        while time.time() - t < 3:
            self.align_camera()
        rospy.loginfo("setup ok")
        self.goal_pose = self.current_pose
        self.pid_setpoint(self.goal_pose)

    # ------------ topics callbacks -----------
    def set_runninng_state(self,boolean_state):
        self.running = boolean_state.data

    def land(self,callback_data):
        self.vso_on = False

    def takeoff(self,callback_data):
        self.align_camera()
        
    def position_callback(self, goal_point):
        self.goal_pose = ros_numpy.numpify(goal_point)
        self.pid_setpoint(self.goal_pose)
        self.control_mode = "position"

    def position_relative_callback(self, goal_point): #
        self.goal_pose += ros_numpy.numpify(goal_point)
        self.pid_setpoint(self.goal_pose)
        self.control_mode = "position"

    def current_coord_callback(self, current_coord):
        self.current_pose = ros_numpy.numpify(current_coord)
        self.calculate_vel()
        


    def velocity_callback(self, goal_vec): #Point
        self.setted_vel = ros_numpy.numpify(goal_vec)

        self.control_mode = "velocity"
        rospy.loginfo("got velocity goal")

    def parameters_callback(self, config, level):

        rospy.loginfo("""Reconfigure Request: \n P_x {P_x} I_x {I_x} D_x {D_x} \n P_y {P_y} I_y {I_y} D_y {D_y} \n P_z {P_z} I_z {I_z} D_z {D_z} \n
                                        \n mult_P_x {mult_P_x} mult_I_x {mult_I_x} mult_D_x {mult_D_x} \n mult_P_y {mult_P_y} mult_I_y {mult_I_y} mult_D_y {mult_D_y} \n mult_P_z {mult_P_z} mult_I_z {mult_I_z} mult_D_z {mult_D_z}mult_x 10^{mult_P_x}""".format(**config))

        # if hasattr(self, 'pid_x'):
        self.pid_x.set_PID_constants(config.P_x*10**config.mult_P_x, config.I_x*10**config.mult_I_x, config.D_x*10**config.mult_D_x)
        self.pid_y.set_PID_constants(config.P_y*10**config.mult_P_y, config.I_y*10**config.mult_I_y, config.D_y*10**config.mult_D_y)
        self.pid_z.set_PID_constants(config.P_z*10**config.mult_P_z, config.I_z*10**config.mult_I_z, config.D_z*10**config.mult_D_z)
        
        return config

    # ------- service handles ----------
    def set_calibrate_pid(self, request):
        assert isinstance(request, SetBoolRequest)
        self.calibrate_pid = request.data
        srv = Server(ControlConfig, self.parameters_callback)
        return SetBoolResponse(True, "calibrate_pid is now : "+str(self.calibrate_pid))

    def reset_vso_position_service(self, request):
        assert isinstance(request, TriggerRequest)
        try:
            self.reset_vso_position()    
            return TriggerResponse(True, "vso coordenate system reseted for the current position")
        except:
            return TriggerResponse(False, "Reset Failed")


    # ------ control methods -----------
    def reset_vso_position(self):
        self.offset_pose += self.current_pose
        self.current_pose = np.array([0.0,0.0,0.0])
        self.goal_pose = np.array([0.0,0.0,0.0])
        
        self.pid_setpoint(self.goal_pose)

        self.pid_update(self.current_pose)

    def align_camera(self):
        self.camera_angle.angular.x = 0
        self.camera_angle.angular.y = 3
        self.camera_angle.angular.z = 0
        self.camera_angle_pub.publish(self.camera_angle)

    def calculate_vel(self):
        self.positioning_vel = self.pid_update(self.current_pose)


        rospy.loginfo("VELOCITY: x: " + str(self.positioning_vel[0]) + " y: " + str(self.positioning_vel[1]) + " z: " + str(self.positioning_vel[2]))
    
    def pid_setpoint(self, goal):
        self.pid_x.setPoint(goal[0])
        self.pid_y.setPoint(goal[1])
        self.pid_z.setPoint(goal[2])

    def pid_update(self, new_pose):
        return np.array([self.pid_x.update(new_pose[0]),self.pid_y.update(new_pose[1]),self.pid_z.update(new_pose[2])])

    def run(self):
        while not rospy.is_shutdown():
            if self.running:
                adjusted_vel = Twist()
                adjusted_vel.linear.x = self.positioning_vel[0]
                adjusted_vel.linear.y = self.positioning_vel[1]
                adjusted_vel.linear.z = self.positioning_vel[2]
                print(self.positioning_vel)
                # if self.control_mode == "position":
                    
                # else:
                #     adjusted_vel.linear.z = self.setted_vel[0]
                #     adjusted_vel.linear.y = self.setted_vel[1]
                #     adjusted_vel.linear.x = self.setted_vel[2]

                self.setpoint_velocity_pub.publish(adjusted_vel)

                p = Point()
                p.x = self.current_pose[0]
                p.y = self.current_pose[1]
                p.z = self.current_pose[2]
                self.current_pose_pub.publish(p)
                
            self.rate.sleep()


if __name__ == "__main__":
    c = vso_controler()
    c.run()
