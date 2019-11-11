// Generated by gencpp from file bebop_msgs/Ardrone3MediaRecordStateVideoStateChangedV2.msg
// DO NOT EDIT!


#ifndef BEBOP_MSGS_MESSAGE_ARDRONE3MEDIARECORDSTATEVIDEOSTATECHANGEDV2_H
#define BEBOP_MSGS_MESSAGE_ARDRONE3MEDIARECORDSTATEVIDEOSTATECHANGEDV2_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace bebop_msgs
{
template <class ContainerAllocator>
struct Ardrone3MediaRecordStateVideoStateChangedV2_
{
  typedef Ardrone3MediaRecordStateVideoStateChangedV2_<ContainerAllocator> Type;

  Ardrone3MediaRecordStateVideoStateChangedV2_()
    : header()
    , state(0)
    , error(0)  {
    }
  Ardrone3MediaRecordStateVideoStateChangedV2_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , state(0)
    , error(0)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef uint8_t _state_type;
  _state_type state;

   typedef uint8_t _error_type;
  _error_type error;



  enum {
    state_stopped = 0u,
    state_started = 1u,
    state_notAvailable = 2u,
    error_ok = 0u,
    error_unknown = 1u,
    error_camera_ko = 2u,
    error_memoryFull = 3u,
    error_lowBattery = 4u,
  };


  typedef boost::shared_ptr< ::bebop_msgs::Ardrone3MediaRecordStateVideoStateChangedV2_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::bebop_msgs::Ardrone3MediaRecordStateVideoStateChangedV2_<ContainerAllocator> const> ConstPtr;

}; // struct Ardrone3MediaRecordStateVideoStateChangedV2_

typedef ::bebop_msgs::Ardrone3MediaRecordStateVideoStateChangedV2_<std::allocator<void> > Ardrone3MediaRecordStateVideoStateChangedV2;

typedef boost::shared_ptr< ::bebop_msgs::Ardrone3MediaRecordStateVideoStateChangedV2 > Ardrone3MediaRecordStateVideoStateChangedV2Ptr;
typedef boost::shared_ptr< ::bebop_msgs::Ardrone3MediaRecordStateVideoStateChangedV2 const> Ardrone3MediaRecordStateVideoStateChangedV2ConstPtr;

// constants requiring out of line definition

   

   

   

   

   

   

   

   



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::bebop_msgs::Ardrone3MediaRecordStateVideoStateChangedV2_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::bebop_msgs::Ardrone3MediaRecordStateVideoStateChangedV2_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace bebop_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'std_msgs': ['/opt/ros/lunar/share/std_msgs/cmake/../msg'], 'bebop_msgs': ['/home/lucas/bebop_ws/src/bebop_autonomy/bebop_msgs/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::bebop_msgs::Ardrone3MediaRecordStateVideoStateChangedV2_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::bebop_msgs::Ardrone3MediaRecordStateVideoStateChangedV2_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::bebop_msgs::Ardrone3MediaRecordStateVideoStateChangedV2_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::bebop_msgs::Ardrone3MediaRecordStateVideoStateChangedV2_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::bebop_msgs::Ardrone3MediaRecordStateVideoStateChangedV2_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::bebop_msgs::Ardrone3MediaRecordStateVideoStateChangedV2_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::bebop_msgs::Ardrone3MediaRecordStateVideoStateChangedV2_<ContainerAllocator> >
{
  static const char* value()
  {
    return "a340391fac53d7779ead611c124980e6";
  }

  static const char* value(const ::bebop_msgs::Ardrone3MediaRecordStateVideoStateChangedV2_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xa340391fac53d777ULL;
  static const uint64_t static_value2 = 0x9ead611c124980e6ULL;
};

template<class ContainerAllocator>
struct DataType< ::bebop_msgs::Ardrone3MediaRecordStateVideoStateChangedV2_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bebop_msgs/Ardrone3MediaRecordStateVideoStateChangedV2";
  }

  static const char* value(const ::bebop_msgs::Ardrone3MediaRecordStateVideoStateChangedV2_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::bebop_msgs::Ardrone3MediaRecordStateVideoStateChangedV2_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# Ardrone3MediaRecordStateVideoStateChangedV2\n\
# auto-generated from up stream XML files at\n\
#   github.com/Parrot-Developers/libARCommands/tree/master/Xml\n\
# To check upstream commit hash, refer to last_build_info file\n\
# Do not modify this file by hand. Check scripts/meta folder for generator files.\n\
#\n\
# SDK Comment: Video record state.\n\
\n\
Header header\n\
\n\
# State of device video recording\n\
uint8 state_stopped=0  # Video is stopped\n\
uint8 state_started=1  # Video is started\n\
uint8 state_notAvailable=2  # The video recording is not available\n\
uint8 state\n\
# Error to explain the state\n\
uint8 error_ok=0  # No Error\n\
uint8 error_unknown=1  # Unknown generic error\n\
uint8 error_camera_ko=2  # Video camera is out of order\n\
uint8 error_memoryFull=3  # Memory full ; cannot save one additional video\n\
uint8 error_lowBattery=4  # Battery is too low to start/keep recording.\n\
uint8 error\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
";
  }

  static const char* value(const ::bebop_msgs::Ardrone3MediaRecordStateVideoStateChangedV2_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::bebop_msgs::Ardrone3MediaRecordStateVideoStateChangedV2_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.state);
      stream.next(m.error);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Ardrone3MediaRecordStateVideoStateChangedV2_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::bebop_msgs::Ardrone3MediaRecordStateVideoStateChangedV2_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::bebop_msgs::Ardrone3MediaRecordStateVideoStateChangedV2_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "state: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.state);
    s << indent << "error: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.error);
  }
};

} // namespace message_operations
} // namespace ros

#endif // BEBOP_MSGS_MESSAGE_ARDRONE3MEDIARECORDSTATEVIDEOSTATECHANGEDV2_H
