<<<<<<< HEAD
# <img align="left" src="https://avatars1.githubusercontent.com/u/36579711?s=200&v=4" width="40" ><p align="center">catkin_ws_bebop</p>

### <p align="center"><div style="text-align:center;color:red"><bold >Repo under development</bold> :exclamation:</div></p>
<br>


## what you will find in this repo
* Not quite sure yet...

----
## Prerequisites
* [ROS](http://wiki.ros.org/kinetic/Installation/Ubuntu)


----
## Setup Repository 
(tested on ubuntu 16.04)


clone repo
```
cd ~/
git clone --recurse-submodules https://github.com/buckerman/catkin_ws_bebop.git
```
install parrot-sphinx:
```
. ~/catkin_ws_bebop/install.sh
```

build catkin workspace
```
cd ~/catkin_ws_bebop/
rosdep update
rosdep install --from-paths src -i
catkin build
```
<!-- >Note: if you want to use the opencv build from source instead of the one that comes with the ros, you canedit the CMakeList.txt file of the packages that require OpenCV (simulation and cvbridge) uncommenting the block of code:
> ```
> #----------CUSTOM OPENCV--------- 
> ...
> #--------------------------------
> ```
> and than build the catkin workspace -->
<!-- 
finally run these commands
```
echo "source ~/catkin_ws_bebop/setup.sh" >> ~/.bashrc
source ~/.bashrc
``` -->

----
## Run simulation
* launch firmwared

open a new terminal and run:
```
. ~/catkin_ws_bebop/0_setup_simulation.sh
```
it's expected to get "I firmwared_firmwares: done indexing firmwares" printed on the last line.
>Note: If firmwared is running correctly you should get "PONG" </br>

after that start the simulated world by runnig:
```
. ~/catkin_ws_bebop/1_launch_simulation_world.sh
```
and than in another terminal launch the bebop driver to communicate with the drone
```
. ~/catkin_ws_bebop/2_launch_simulation_driver.sh
```
check (in another terminal) if the drone have spawned correctly by running :
```
ping 10.202.0.1   #it might be other ip like 10.202.X.1
```
you shoud get some thing like:
>64 bytes from 10.202.0.1: icmp_seq=1 ttl=64 time=0.030 ms<br>
64 bytes from 10.202.0.1: icmp_seq=2 ttl=64 time=0.034 ms<br>
64 bytes from 10.202.0.1: icmp_seq=3 ttl=64 time=0.046 ms<br>
...

Great! now you are ready to simulate!

>Note: you can also use roslaunch instead of the 2_launch_simulation_driver.sh script
>```
>roslaunch simulation simulate.launch
>```
>*if you are using a different ip, edit the value of the >arg "ip" on the simulate.launch file*


----

## Run on real live (offboard)
tested on parrot bebop 2 drone  <img align="center" style="margin:-50px 0px -50px 0px;" src=".assets/parrot-bebop-2" width="100" >

Firstly make sure that none of the simulation scripts is runing.<br>
Turn on the drone and connect to the drone's wifi<br>
start bebops'driver by running:
```
roslaunch imav_indoor drone.launch
```
<br>

run whatever node you want :smile: 
```
rosrun simulation small_square.py # for example
```
... under development ...


=======
# bebop_ws
# Bebop ROS Workspace
This repository contains the software developed aiming the International Micro Air Vehicle Conference and Competition indoor tasks. Thus, it includes drone control and computational vision applications.

It supposes you have the Robotic Operating System (ROS), OpenCV2, Pyzbar, Numpy and others dependences. 

# Setup the workspace on your PC

$ sudo apt-get install build-essential python-rosdep python-catkin-tools

### Get the repository

$ git clone https://github.com/lucaspenna00/bebop_ws/

### Create and initialize the workspace
$ cd ~/bebop_ws

### Update rosdep database and install dependencies (including parrot_arsdk)
$ rosdep update
$ rosdep install --from-paths src -i

### Build the workspace
$ catkin build

# Running the Workspace applications

Firstly, you need to run the Bebop ROS drive (in order to run all others applications)

### Run the drive

$ roslaunch bebop_driver bebop_node.launch

### Useful ROS commands

All the topics disponible on BEBOP_DRIVE:

$ rosmsg list

Message details:

$ rosmsg show [TOPIC_NAME]

Message type via ROS topic:

$ rostopic type [TOPIC_NAME]

See the Bebop camera image:

$ rosrun rqt_image_view rqt_image_view --force-discover

More information:
https://bebop-autonomy.readthedocs.io/en/latest/
>>>>>>> 41c274f59200ab79b53cfb1a15a8532641ccdad1
