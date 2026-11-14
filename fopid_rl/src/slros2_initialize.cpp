// Copyright 2022-2024 The MathWorks, Inc.
// Generated 14-Nov-2026 23:51:10
#include "slros2_initialize.h"
const std::string SLROSNodeName("FOpid_RL");
// FOpid_RL/Publish
SimulinkPublisher<sensor_msgs::msg::Imu,SL_Bus_sensor_msgs_Imu> Pub_FOpid_RL_548;
// FOpid_RL/Publish1
SimulinkPublisher<nav_msgs::msg::Odometry,SL_Bus_nav_msgs_Odometry> Pub_FOpid_RL_697;
// FOpid_RL/Publish2
SimulinkPublisher<geometry_msgs::msg::PoseStamped,SL_Bus_geometry_msgs_PoseStamped> Pub_FOpid_RL_811;
// FOpid_RL/Publish3
SimulinkPublisher<geometry_msgs::msg::TwistStamped,SL_Bus_geometry_msgs_TwistStamped> Pub_FOpid_RL_835;
// FOpid_RL/SUBSYSTEM_MODEL/Subscribe1_TURBULENCIA1
SimulinkSubscriber<std_msgs::msg::Bool,SL_Bus_std_msgs_Bool> Sub_FOpid_RL_423;
// FOpid_RL/SUBSYSTEM_MODEL/Subscribe_HEAVE
SimulinkSubscriber<std_msgs::msg::Float64,SL_Bus_std_msgs_Float64> Sub_FOpid_RL_443;
// FOpid_RL/SUBSYSTEM_MODEL/Subscribe_RATE
SimulinkSubscriber<std_msgs::msg::Float64,SL_Bus_std_msgs_Float64> Sub_FOpid_RL_445;
// FOpid_RL/SUBSYSTEM_MODEL/Subscribe_TURBULENCIA
SimulinkSubscriber<std_msgs::msg::Bool,SL_Bus_std_msgs_Bool> Sub_FOpid_RL_417;
// FOpid_RL/Subscribe-ALTURA
SimulinkSubscriber<std_msgs::msg::Float64,SL_Bus_std_msgs_Float64> Sub_FOpid_RL_435;
// FOpid_RL/Subscribe-YAW
SimulinkSubscriber<std_msgs::msg::Float64,SL_Bus_std_msgs_Float64> Sub_FOpid_RL_377;
// FOpid_RL/Call Service
SimulinkServiceCaller<gazebo_msgs::srv::SetEntityState,SL_Bus_gazebo_msgs_SetEntityStateRequest,SL_Bus_gazebo_msgs_SetEntityStateResponse> ServCall_FOpid_RL_326;
