/*
 * FOpid_control_types.h
 *
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 *
 * Code generation for model "FOpid_control".
 *
 * Model version              : 13.61
 * Simulink Coder version : 26.1 (R2026a) 20-Nov-2025
 * C++ source code generated on : Wed Aug 19 13:10:53 2026
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef FOPID_CONTROL_TYPES_H_
#define FOPID_CONTROL_TYPES_H_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_SL_BUS_ROSVARIABLELENGTHARRAYINFO_
#define DEFINED_TYPEDEF_FOR_SL_BUS_ROSVARIABLELENGTHARRAYINFO_

struct SL_Bus_ROSVariableLengthArrayInfo
{
  uint32_T CurrentLength;
  uint32_T ReceivedLength;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_BUS_BUILTIN_INTERFACES_TIME_
#define DEFINED_TYPEDEF_FOR_SL_BUS_BUILTIN_INTERFACES_TIME_

struct SL_Bus_builtin_interfaces_Time
{
  int32_T sec;
  uint32_T nanosec;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_BUS_GEOMETRY_MSGS_POINT_
#define DEFINED_TYPEDEF_FOR_SL_BUS_GEOMETRY_MSGS_POINT_

struct SL_Bus_geometry_msgs_Point
{
  real_T x;
  real_T y;
  real_T z;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_BUS_GEOMETRY_MSGS_QUATERNION_
#define DEFINED_TYPEDEF_FOR_SL_BUS_GEOMETRY_MSGS_QUATERNION_

struct SL_Bus_geometry_msgs_Quaternion
{
  real_T x;
  real_T y;
  real_T z;
  real_T w;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_BUS_GEOMETRY_MSGS_POSE_
#define DEFINED_TYPEDEF_FOR_SL_BUS_GEOMETRY_MSGS_POSE_

struct SL_Bus_geometry_msgs_Pose
{
  SL_Bus_geometry_msgs_Point position;
  SL_Bus_geometry_msgs_Quaternion orientation;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_BUS_GEOMETRY_MSGS_VECTOR3_
#define DEFINED_TYPEDEF_FOR_SL_BUS_GEOMETRY_MSGS_VECTOR3_

struct SL_Bus_geometry_msgs_Vector3
{
  real_T x;
  real_T y;
  real_T z;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_BUS_GEOMETRY_MSGS_TWIST_
#define DEFINED_TYPEDEF_FOR_SL_BUS_GEOMETRY_MSGS_TWIST_

struct SL_Bus_geometry_msgs_Twist
{
  SL_Bus_geometry_msgs_Vector3 linear;
  SL_Bus_geometry_msgs_Vector3 angular;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_BUS_GAZEBO_MSGS_ENTITYSTATE_
#define DEFINED_TYPEDEF_FOR_SL_BUS_GAZEBO_MSGS_ENTITYSTATE_

struct SL_Bus_gazebo_msgs_EntityState
{
  uint8_T name[128];
  SL_Bus_ROSVariableLengthArrayInfo name_SL_Info;
  SL_Bus_geometry_msgs_Pose pose;
  SL_Bus_geometry_msgs_Twist twist;
  uint8_T reference_frame[128];
  SL_Bus_ROSVariableLengthArrayInfo reference_frame_SL_Info;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_BUS_GAZEBO_MSGS_SETENTITYSTATEREQUEST_
#define DEFINED_TYPEDEF_FOR_SL_BUS_GAZEBO_MSGS_SETENTITYSTATEREQUEST_

struct SL_Bus_gazebo_msgs_SetEntityStateRequest
{
  SL_Bus_gazebo_msgs_EntityState state;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_BUS_GAZEBO_MSGS_SETENTITYSTATERESPONSE_
#define DEFINED_TYPEDEF_FOR_SL_BUS_GAZEBO_MSGS_SETENTITYSTATERESPONSE_

struct SL_Bus_gazebo_msgs_SetEntityStateResponse
{
  boolean_T success;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_BUS_STD_MSGS_HEADER_
#define DEFINED_TYPEDEF_FOR_SL_BUS_STD_MSGS_HEADER_

struct SL_Bus_std_msgs_Header
{
  SL_Bus_builtin_interfaces_Time stamp;
  uint8_T frame_id[128];
  SL_Bus_ROSVariableLengthArrayInfo frame_id_SL_Info;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_BUS_GEOMETRY_MSGS_POSESTAMPED_
#define DEFINED_TYPEDEF_FOR_SL_BUS_GEOMETRY_MSGS_POSESTAMPED_

struct SL_Bus_geometry_msgs_PoseStamped
{
  SL_Bus_std_msgs_Header header;
  SL_Bus_geometry_msgs_Pose pose;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_BUS_GEOMETRY_MSGS_POSEWITHCOVARIANCE_
#define DEFINED_TYPEDEF_FOR_SL_BUS_GEOMETRY_MSGS_POSEWITHCOVARIANCE_

struct SL_Bus_geometry_msgs_PoseWithCovariance
{
  SL_Bus_geometry_msgs_Pose pose;
  real_T covariance[36];
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_BUS_GEOMETRY_MSGS_TWISTSTAMPED_
#define DEFINED_TYPEDEF_FOR_SL_BUS_GEOMETRY_MSGS_TWISTSTAMPED_

struct SL_Bus_geometry_msgs_TwistStamped
{
  SL_Bus_std_msgs_Header header;
  SL_Bus_geometry_msgs_Twist twist;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_BUS_GEOMETRY_MSGS_TWISTWITHCOVARIANCE_
#define DEFINED_TYPEDEF_FOR_SL_BUS_GEOMETRY_MSGS_TWISTWITHCOVARIANCE_

struct SL_Bus_geometry_msgs_TwistWithCovariance
{
  SL_Bus_geometry_msgs_Twist twist;
  real_T covariance[36];
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_BUS_NAV_MSGS_ODOMETRY_
#define DEFINED_TYPEDEF_FOR_SL_BUS_NAV_MSGS_ODOMETRY_

struct SL_Bus_nav_msgs_Odometry
{
  SL_Bus_std_msgs_Header header;
  uint8_T child_frame_id[128];
  SL_Bus_ROSVariableLengthArrayInfo child_frame_id_SL_Info;
  SL_Bus_geometry_msgs_PoseWithCovariance pose;
  SL_Bus_geometry_msgs_TwistWithCovariance twist;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_BUS_SENSOR_MSGS_IMU_
#define DEFINED_TYPEDEF_FOR_SL_BUS_SENSOR_MSGS_IMU_

struct SL_Bus_sensor_msgs_Imu
{
  SL_Bus_std_msgs_Header header;
  SL_Bus_geometry_msgs_Quaternion orientation;
  real_T orientation_covariance[9];
  SL_Bus_geometry_msgs_Vector3 angular_velocity;
  real_T angular_velocity_covariance[9];
  SL_Bus_geometry_msgs_Vector3 linear_acceleration;
  real_T linear_acceleration_covariance[9];
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_BUS_STD_MSGS_BOOL_
#define DEFINED_TYPEDEF_FOR_SL_BUS_STD_MSGS_BOOL_

struct SL_Bus_std_msgs_Bool
{
  boolean_T data;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_BUS_STD_MSGS_FLOAT64_
#define DEFINED_TYPEDEF_FOR_SL_BUS_STD_MSGS_FLOAT64_

struct SL_Bus_std_msgs_Float64
{
  real_T data;
};

#endif

#ifndef STRUCT_SJ4IH70VMKCVCEGUWN0MNVF
#define STRUCT_SJ4IH70VMKCVCEGUWN0MNVF

struct sJ4ih70VmKcvCeguWN0mNVF
{
  real_T sec;
  real_T nsec;
};

#endif                                 /* STRUCT_SJ4IH70VMKCVCEGUWN0MNVF */

#ifndef STRUCT_ROS_SLROS2_INTERNAL_BLOCK_SER_T
#define STRUCT_ROS_SLROS2_INTERNAL_BLOCK_SER_T

struct ros_slros2_internal_block_Ser_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  boolean_T QOSAvoidROSNamespaceConventions;
};

#endif                              /* STRUCT_ROS_SLROS2_INTERNAL_BLOCK_SER_T */

#ifndef STRUCT_ROBOTICS_SLCORE_INTERNAL_BLOC_T
#define STRUCT_ROBOTICS_SLCORE_INTERNAL_BLOC_T

struct robotics_slcore_internal_bloc_T
{
  int32_T isInitialized;
};

#endif                              /* STRUCT_ROBOTICS_SLCORE_INTERNAL_BLOC_T */

#ifndef STRUCT_E_ROBOTICS_CORE_INTERNAL_VALI_T
#define STRUCT_E_ROBOTICS_CORE_INTERNAL_VALI_T

struct e_robotics_core_internal_vali_T
{
  boolean_T FeatureControlFlag;
};

#endif                              /* STRUCT_E_ROBOTICS_CORE_INTERNAL_VALI_T */

#ifndef STRUCT_ROS_SLROS2_INTERNAL_BLOCK_PUB_T
#define STRUCT_ROS_SLROS2_INTERNAL_BLOCK_PUB_T

struct ros_slros2_internal_block_Pub_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  boolean_T QOSAvoidROSNamespaceConventions;
};

#endif                              /* STRUCT_ROS_SLROS2_INTERNAL_BLOCK_PUB_T */

#ifndef STRUCT_ROS_SLROS2_INTERNAL_BLOCK_SUB_T
#define STRUCT_ROS_SLROS2_INTERNAL_BLOCK_SUB_T

struct ros_slros2_internal_block_Sub_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  boolean_T QOSAvoidROSNamespaceConventions;
};

#endif                              /* STRUCT_ROS_SLROS2_INTERNAL_BLOCK_SUB_T */

/* Forward declaration for rtModel */
typedef struct tag_RTM_FOpid_control_T RT_MODEL_FOpid_control_T;

#endif                                 /* FOPID_CONTROL_TYPES_H_ */
