// Copyright 2022-2024 The MathWorks, Inc.
// Generated 08-Sep-2026 17:00:38
#include "slros2_initialize.h"
const std::string SLROSNodeName("FOpid_control_FIN");
// FOpid_control_FIN/Publish
SimulinkPublisher<sensor_msgs::msg::Imu,SL_Bus_sensor_msgs_Imu> Pub_FOpid_control_FIN_548;
// FOpid_control_FIN/Publish1
SimulinkPublisher<nav_msgs::msg::Odometry,SL_Bus_nav_msgs_Odometry> Pub_FOpid_control_FIN_697;
// FOpid_control_FIN/Publish2
SimulinkPublisher<geometry_msgs::msg::PoseStamped,SL_Bus_geometry_msgs_PoseStamped> Pub_FOpid_control_FIN_811;
// FOpid_control_FIN/Publish3
SimulinkPublisher<geometry_msgs::msg::TwistStamped,SL_Bus_geometry_msgs_TwistStamped> Pub_FOpid_control_FIN_835;
// FOpid_control_FIN/SUBSYSTEM_MODEL/Subscribe1_TURBULENCIA1
SimulinkSubscriber<std_msgs::msg::Bool,SL_Bus_std_msgs_Bool> Sub_FOpid_control_FIN_423;
// FOpid_control_FIN/SUBSYSTEM_MODEL/Subscribe_HEAVE
SimulinkSubscriber<std_msgs::msg::Float64,SL_Bus_std_msgs_Float64> Sub_FOpid_control_FIN_443;
// FOpid_control_FIN/SUBSYSTEM_MODEL/Subscribe_RATE
SimulinkSubscriber<std_msgs::msg::Float64,SL_Bus_std_msgs_Float64> Sub_FOpid_control_FIN_445;
// FOpid_control_FIN/SUBSYSTEM_MODEL/Subscribe_TURBULENCIA
SimulinkSubscriber<std_msgs::msg::Bool,SL_Bus_std_msgs_Bool> Sub_FOpid_control_FIN_417;
// FOpid_control_FIN/Subscribe-ALTURA
SimulinkSubscriber<std_msgs::msg::Float64,SL_Bus_std_msgs_Float64> Sub_FOpid_control_FIN_435;
// FOpid_control_FIN/Subscribe-YAW
SimulinkSubscriber<std_msgs::msg::Float64,SL_Bus_std_msgs_Float64> Sub_FOpid_control_FIN_377;
// FOpid_control_FIN/Call Service
SimulinkServiceCaller<gazebo_msgs::srv::SetEntityState,SL_Bus_gazebo_msgs_SetEntityStateRequest,SL_Bus_gazebo_msgs_SetEntityStateResponse> ServCall_FOpid_control_FIN_326;
