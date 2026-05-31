// Copyright 2022-2025 The MathWorks, Inc.
// Generated 31-May-2026 11:11:58
#ifndef _SLROS2_INITIALIZE_H_
#define _SLROS2_INITIALIZE_H_
#include "FOpid_control_V4_types.h"
// Generic pub-sub header
#include "slros2_generic_pubsub.h"
// Generic service header
#include "slros2_generic_service.h"
#ifndef SET_QOS_VALUES
#define SET_QOS_VALUES(qosStruct, _history, _depth, _durability, _reliability, _deadline \
, _lifespan, _liveliness, _lease_duration, _avoid_ros_namespace_conventions)             \
    {                                                                                    \
        qosStruct.history = _history;                                                    \
        qosStruct.depth = _depth;                                                        \
        qosStruct.durability = _durability;                                              \
        qosStruct.reliability = _reliability;                                            \
        qosStruct.deadline.sec = _deadline.sec;                                          \
        qosStruct.deadline.nsec = _deadline.nsec;                                        \
        qosStruct.lifespan.sec = _lifespan.sec;                                          \
        qosStruct.lifespan.nsec = _lifespan.nsec;                                        \
        qosStruct.liveliness = _liveliness;                                              \
        qosStruct.liveliness_lease_duration.sec = _lease_duration.sec;                   \
        qosStruct.liveliness_lease_duration.nsec = _lease_duration.nsec;                 \
        qosStruct.avoid_ros_namespace_conventions = _avoid_ros_namespace_conventions;    \
    }
#endif
// Get QOS Settings from RMW
inline rclcpp::QoS getQOSSettingsFromRMW(const rmw_qos_profile_t& qosProfile) {
  // pull in history & depth
  auto init = rclcpp::QoSInitialization::from_rmw(qosProfile);
  // set durability, reliability, deadline, liveliness policy, liveliness lease duration and avoid ROS namespace convention
  rclcpp::QoS qos(init, qosProfile);
  return qos;
}
// FOpid_control_V4/Publish
extern SimulinkPublisher<sensor_msgs::msg::Imu,SL_Bus_sensor_msgs_Imu> Pub_FOpid_control_V4_548;
// FOpid_control_V4/Publish1
extern SimulinkPublisher<nav_msgs::msg::Odometry,SL_Bus_nav_msgs_Odometry> Pub_FOpid_control_V4_697;
// FOpid_control_V4/Publish2
extern SimulinkPublisher<geometry_msgs::msg::PoseStamped,SL_Bus_geometry_msgs_PoseStamped> Pub_FOpid_control_V4_811;
// FOpid_control_V4/Publish3
extern SimulinkPublisher<geometry_msgs::msg::TwistStamped,SL_Bus_geometry_msgs_TwistStamped> Pub_FOpid_control_V4_835;
// FOpid_control_V4/SUBSYSTEM_MODEL/Subscribe1_TURBULENCIA1
extern SimulinkSubscriber<std_msgs::msg::Bool,SL_Bus_std_msgs_Bool> Sub_FOpid_control_V4_423;
// FOpid_control_V4/SUBSYSTEM_MODEL/Subscribe_HEAVE
extern SimulinkSubscriber<std_msgs::msg::Float64,SL_Bus_std_msgs_Float64> Sub_FOpid_control_V4_443;
// FOpid_control_V4/SUBSYSTEM_MODEL/Subscribe_RATE
extern SimulinkSubscriber<std_msgs::msg::Float64,SL_Bus_std_msgs_Float64> Sub_FOpid_control_V4_445;
// FOpid_control_V4/SUBSYSTEM_MODEL/Subscribe_TURBULENCIA
extern SimulinkSubscriber<std_msgs::msg::Bool,SL_Bus_std_msgs_Bool> Sub_FOpid_control_V4_417;
// FOpid_control_V4/Subscribe-ALTURA
extern SimulinkSubscriber<std_msgs::msg::Float64,SL_Bus_std_msgs_Float64> Sub_FOpid_control_V4_435;
// FOpid_control_V4/Subscribe-YAW
extern SimulinkSubscriber<std_msgs::msg::Float64,SL_Bus_std_msgs_Float64> Sub_FOpid_control_V4_377;
// FOpid_control_V4/Call Service
extern SimulinkServiceCaller<gazebo_msgs::srv::SetEntityState,SL_Bus_gazebo_msgs_SetEntityStateRequest,SL_Bus_gazebo_msgs_SetEntityStateResponse> ServCall_FOpid_control_V4_326;
#endif
