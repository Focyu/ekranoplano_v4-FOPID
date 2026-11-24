/*
 * FOpid_RL_types.h
 *
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 *
 * Code generation for model "FOpid_RL".
 *
 * Model version              : 14.3
 * Simulink Coder version : 26.2 (R2026b) 22-May-2026
 * C++ source code generated on : Tue Nov 24 12:04:19 2026
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef FOpid_RL_types_h_
#define FOpid_RL_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_ROSVariableLengthArrayInfo_
#define DEFINED_TYPEDEF_FOR_SL_Bus_ROSVariableLengthArrayInfo_

struct SL_Bus_ROSVariableLengthArrayInfo
{
  uint32_T CurrentLength;
  uint32_T ReceivedLength;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_builtin_interfaces_Time_
#define DEFINED_TYPEDEF_FOR_SL_Bus_builtin_interfaces_Time_

struct SL_Bus_builtin_interfaces_Time
{
  int32_T sec;
  uint32_T nanosec;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_geometry_msgs_Point_
#define DEFINED_TYPEDEF_FOR_SL_Bus_geometry_msgs_Point_

struct SL_Bus_geometry_msgs_Point
{
  real_T x;
  real_T y;
  real_T z;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_geometry_msgs_Quaternion_
#define DEFINED_TYPEDEF_FOR_SL_Bus_geometry_msgs_Quaternion_

struct SL_Bus_geometry_msgs_Quaternion
{
  real_T x;
  real_T y;
  real_T z;
  real_T w;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_geometry_msgs_Pose_
#define DEFINED_TYPEDEF_FOR_SL_Bus_geometry_msgs_Pose_

struct SL_Bus_geometry_msgs_Pose
{
  SL_Bus_geometry_msgs_Point position;
  SL_Bus_geometry_msgs_Quaternion orientation;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_geometry_msgs_Vector3_
#define DEFINED_TYPEDEF_FOR_SL_Bus_geometry_msgs_Vector3_

struct SL_Bus_geometry_msgs_Vector3
{
  real_T x;
  real_T y;
  real_T z;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_geometry_msgs_Twist_
#define DEFINED_TYPEDEF_FOR_SL_Bus_geometry_msgs_Twist_

struct SL_Bus_geometry_msgs_Twist
{
  SL_Bus_geometry_msgs_Vector3 linear;
  SL_Bus_geometry_msgs_Vector3 angular;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_gazebo_msgs_EntityState_
#define DEFINED_TYPEDEF_FOR_SL_Bus_gazebo_msgs_EntityState_

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

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_gazebo_msgs_SetEntityStateRequest_
#define DEFINED_TYPEDEF_FOR_SL_Bus_gazebo_msgs_SetEntityStateRequest_

struct SL_Bus_gazebo_msgs_SetEntityStateRequest
{
  SL_Bus_gazebo_msgs_EntityState state;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_gazebo_msgs_SetEntityStateResponse_
#define DEFINED_TYPEDEF_FOR_SL_Bus_gazebo_msgs_SetEntityStateResponse_

struct SL_Bus_gazebo_msgs_SetEntityStateResponse
{
  boolean_T success;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_std_msgs_Header_
#define DEFINED_TYPEDEF_FOR_SL_Bus_std_msgs_Header_

struct SL_Bus_std_msgs_Header
{
  SL_Bus_builtin_interfaces_Time stamp;
  uint8_T frame_id[128];
  SL_Bus_ROSVariableLengthArrayInfo frame_id_SL_Info;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_geometry_msgs_PoseStamped_
#define DEFINED_TYPEDEF_FOR_SL_Bus_geometry_msgs_PoseStamped_

struct SL_Bus_geometry_msgs_PoseStamped
{
  SL_Bus_std_msgs_Header header;
  SL_Bus_geometry_msgs_Pose pose;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_geometry_msgs_PoseWithCovariance_
#define DEFINED_TYPEDEF_FOR_SL_Bus_geometry_msgs_PoseWithCovariance_

struct SL_Bus_geometry_msgs_PoseWithCovariance
{
  SL_Bus_geometry_msgs_Pose pose;
  real_T covariance[36];
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_geometry_msgs_TwistStamped_
#define DEFINED_TYPEDEF_FOR_SL_Bus_geometry_msgs_TwistStamped_

struct SL_Bus_geometry_msgs_TwistStamped
{
  SL_Bus_std_msgs_Header header;
  SL_Bus_geometry_msgs_Twist twist;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_geometry_msgs_TwistWithCovariance_
#define DEFINED_TYPEDEF_FOR_SL_Bus_geometry_msgs_TwistWithCovariance_

struct SL_Bus_geometry_msgs_TwistWithCovariance
{
  SL_Bus_geometry_msgs_Twist twist;
  real_T covariance[36];
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_nav_msgs_Odometry_
#define DEFINED_TYPEDEF_FOR_SL_Bus_nav_msgs_Odometry_

struct SL_Bus_nav_msgs_Odometry
{
  SL_Bus_std_msgs_Header header;
  uint8_T child_frame_id[128];
  SL_Bus_ROSVariableLengthArrayInfo child_frame_id_SL_Info;
  SL_Bus_geometry_msgs_PoseWithCovariance pose;
  SL_Bus_geometry_msgs_TwistWithCovariance twist;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_sensor_msgs_Imu_
#define DEFINED_TYPEDEF_FOR_SL_Bus_sensor_msgs_Imu_

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

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_std_msgs_Bool_
#define DEFINED_TYPEDEF_FOR_SL_Bus_std_msgs_Bool_

struct SL_Bus_std_msgs_Bool
{
  boolean_T data;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_std_msgs_Float64_
#define DEFINED_TYPEDEF_FOR_SL_Bus_std_msgs_Float64_

struct SL_Bus_std_msgs_Float64
{
  real_T data;
};

#endif

#ifndef struct_sJ4ih70VmKcvCeguWN0mNVF
#define struct_sJ4ih70VmKcvCeguWN0mNVF

struct sJ4ih70VmKcvCeguWN0mNVF
{
  real_T sec;
  real_T nsec;
};

#endif                                 /* struct_sJ4ih70VmKcvCeguWN0mNVF */

#ifndef struct_ros_slros2_internal_block_Ser_T
#define struct_ros_slros2_internal_block_Ser_T

struct ros_slros2_internal_block_Ser_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  boolean_T QOSAvoidROSNamespaceConventions;
};

#endif                              /* struct_ros_slros2_internal_block_Ser_T */

#ifndef struct_robotics_slcore_internal_bloc_T
#define struct_robotics_slcore_internal_bloc_T

struct robotics_slcore_internal_bloc_T
{
  int32_T isInitialized;
};

#endif                              /* struct_robotics_slcore_internal_bloc_T */

#ifndef struct_e_robotics_core_internal_vali_T
#define struct_e_robotics_core_internal_vali_T

struct e_robotics_core_internal_vali_T
{
  boolean_T FeatureControlFlag;
};

#endif                              /* struct_e_robotics_core_internal_vali_T */

#ifndef struct_ros_slros2_internal_block_Pub_T
#define struct_ros_slros2_internal_block_Pub_T

struct ros_slros2_internal_block_Pub_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  boolean_T QOSAvoidROSNamespaceConventions;
};

#endif                              /* struct_ros_slros2_internal_block_Pub_T */

#ifndef struct_ros_slros2_internal_block_Sub_T
#define struct_ros_slros2_internal_block_Sub_T

struct ros_slros2_internal_block_Sub_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  boolean_T QOSAvoidROSNamespaceConventions;
};

#endif                              /* struct_ros_slros2_internal_block_Sub_T */

/* Forward declaration for rtModel */
typedef struct tag_RTM_FOpid_RL_T RT_MODEL_FOpid_RL_T;

#endif                                 /* FOpid_RL_types_h_ */
