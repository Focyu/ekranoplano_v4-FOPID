// Copyright 2022-2024 The MathWorks, Inc.
// Generated 04-Jun-2026 13:38:45
#include "slros2_initialize.h"
const std::string SLROSNodeName("FOpid_control_V4");
// FOpid_control_V4/Publish
SimulinkPublisher<sensor_msgs::msg::Imu,SL_Bus_sensor_msgs_Imu> Pub_FOpid_control_V4_548;
// FOpid_control_V4/Publish1
SimulinkPublisher<nav_msgs::msg::Odometry,SL_Bus_nav_msgs_Odometry> Pub_FOpid_control_V4_697;
// FOpid_control_V4/Publish2
SimulinkPublisher<geometry_msgs::msg::PoseStamped,SL_Bus_geometry_msgs_PoseStamped> Pub_FOpid_control_V4_811;
// FOpid_control_V4/Publish3
SimulinkPublisher<geometry_msgs::msg::TwistStamped,SL_Bus_geometry_msgs_TwistStamped> Pub_FOpid_control_V4_835;
// FOpid_control_V4/SUBSYSTEM_MODEL/Subscribe1_TURBULENCIA1
SimulinkSubscriber<std_msgs::msg::Bool,SL_Bus_std_msgs_Bool> Sub_FOpid_control_V4_423;
// FOpid_control_V4/SUBSYSTEM_MODEL/Subscribe_HEAVE
SimulinkSubscriber<std_msgs::msg::Float64,SL_Bus_std_msgs_Float64> Sub_FOpid_control_V4_443;
// FOpid_control_V4/SUBSYSTEM_MODEL/Subscribe_RATE
SimulinkSubscriber<std_msgs::msg::Float64,SL_Bus_std_msgs_Float64> Sub_FOpid_control_V4_445;
// FOpid_control_V4/SUBSYSTEM_MODEL/Subscribe_TURBULENCIA
SimulinkSubscriber<std_msgs::msg::Bool,SL_Bus_std_msgs_Bool> Sub_FOpid_control_V4_417;
// FOpid_control_V4/Subscribe-ALTURA
SimulinkSubscriber<std_msgs::msg::Float64,SL_Bus_std_msgs_Float64> Sub_FOpid_control_V4_435;
// FOpid_control_V4/Subscribe-YAW
SimulinkSubscriber<std_msgs::msg::Float64,SL_Bus_std_msgs_Float64> Sub_FOpid_control_V4_377;
// FOpid_control_V4/Call Service
SimulinkServiceCaller<gazebo_msgs::srv::SetEntityState,SL_Bus_gazebo_msgs_SetEntityStateRequest,SL_Bus_gazebo_msgs_SetEntityStateResponse> ServCall_FOpid_control_V4_326;
