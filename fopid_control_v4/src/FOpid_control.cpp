/*
 * FOpid_control.cpp
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

#include "FOpid_control.h"
#include "slros2_initialize.h"
#include "rtwtypes.h"
#include "FOpid_control_types.h"
#include "rmw/qos_profiles.h"
#include <string.h>
#include "FOpid_control_private.h"
#include <emmintrin.h>
#include <math.h>

extern "C"
{

#include "rt_nonfinite.h"

}

#include <stddef.h>
#include "zero_crossing_types.h"
#include "rt_defines.h"

uint32_T plook_bincpa(real_T u, const real_T bp[], uint32_T maxIndex, real_T
                      *fraction, uint32_T *prevIndex)
{
  uint32_T bpIndex;

  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Clip'
     Use previous index: 'on'
     Use last breakpoint for index at or above upper limit: 'on'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u <= bp[0U]) {
    bpIndex = 0U;
    *fraction = 0.0;
  } else if (u < bp[maxIndex]) {
    bpIndex = binsearch_u32d_prevIdx(u, bp, *prevIndex, maxIndex);
    *fraction = (u - bp[bpIndex]) / (bp[bpIndex + 1U] - bp[bpIndex]);
  } else {
    bpIndex = maxIndex;
    *fraction = 0.0;
  }

  *prevIndex = bpIndex;
  return bpIndex;
}

real_T intrp2d_la_pw(const uint32_T bpIndex[], const real_T frac[], const real_T
                     table[], const uint32_T stride, const uint32_T maxIndex[])
{
  real_T y;
  real_T yL_0d0;
  uint32_T offset_1d;

  /* Column-major Interpolation 2-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'on'
     Overflow mode: 'portable wrapping'
   */
  offset_1d = bpIndex[1U] * stride + bpIndex[0U];
  if (bpIndex[0U] == maxIndex[0U]) {
    y = table[offset_1d];
  } else {
    yL_0d0 = table[offset_1d];
    y = (table[offset_1d + 1U] - yL_0d0) * frac[0U] + yL_0d0;
  }

  if (bpIndex[1U] == maxIndex[1U]) {
  } else {
    offset_1d += stride;
    if (bpIndex[0U] == maxIndex[0U]) {
      yL_0d0 = table[offset_1d];
    } else {
      yL_0d0 = table[offset_1d];
      yL_0d0 += (table[offset_1d + 1U] - yL_0d0) * frac[0U];
    }

    y += (yL_0d0 - y) * frac[1U];
  }

  return y;
}

uint32_T binsearch_u32d_prevIdx(real_T u, const real_T bp[], uint32_T startIndex,
  uint32_T maxIndex)
{
  uint32_T bpIndex;
  uint32_T found;
  uint32_T iLeft;
  uint32_T iRght;

  /* Binary Search using Previous Index */
  bpIndex = startIndex;
  iLeft = 0U;
  iRght = maxIndex;
  found = 0U;
  while (found == 0U) {
    if (u < bp[bpIndex]) {
      iRght = bpIndex - 1U;
      bpIndex = ((bpIndex + iLeft) - 1U) >> 1U;
    } else if (u < bp[bpIndex + 1U]) {
      found = 1U;
    } else {
      iLeft = bpIndex + 1U;
      bpIndex = ((bpIndex + iRght) + 1U) >> 1U;
    }
  }

  return bpIndex;
}

/*
 * This function updates continuous states using the ODE4 fixed-step
 * solver algorithm
 */
void FOpid_control::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE4_IntgData *id = static_cast<ODE4_IntgData *>(rtsiGetSolverData(si));
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T *f3 = id->f[3];
  real_T temp;
  int_T i;
  int_T nXc = 42;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                static_cast<uint_T>(nXc)*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  FOpid_control_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  this->step();
  FOpid_control_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  this->step();
  FOpid_control_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  this->step();
  FOpid_control_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/*
 * Output and update for atomic system:
 *    '<Root>/MATLAB Function-ned_to_PoseStamped'
 *    '<Root>/MATLAB Function-ned_to_TwistStamped'
 */
void FOpid_control::MATLABFunctionned_to_PoseStampe
  (B_MATLABFunctionned_to_PoseSt_T *localB)
{
  static const uint8_T b[5] = { 119U, 111U, 114U, 108U, 100U };

  memset(&localB->stringOut[0], 0, sizeof(uint8_T) << 7U);
  for (int32_T i = 0; i < 5; i++) {
    localB->stringOut[i] = b[i];
  }

  localB->lengthOut = 5U;
}

/*
 * System initialize for enable system:
 *    '<S43>/Enabled Subsystem'
 *    '<S46>/Enabled Subsystem'
 */
void FOpid_control::FOpid_con_EnabledSubsystem_Init
  (B_EnabledSubsystem_FOpid_cont_T *localB)
{
  /* SystemInitialize for SignalConversion generated from: '<S86>/In1' */
  memset(&localB->In1, 0, sizeof(SL_Bus_std_msgs_Bool));
}

/*
 * Output and update for enable system:
 *    '<S43>/Enabled Subsystem'
 *    '<S46>/Enabled Subsystem'
 */
void FOpid_control::FOpid_control_EnabledSubsystem(boolean_T rtu_Enable, const
  SL_Bus_std_msgs_Bool *rtu_In1, B_EnabledSubsystem_FOpid_cont_T *localB)
{
  /* Outputs for Enabled SubSystem: '<S43>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S86>/Enable'
   */
  if (rtu_Enable) {
    /* SignalConversion generated from: '<S86>/In1' */
    localB->In1 = *rtu_In1;
  }

  /* End of Outputs for SubSystem: '<S43>/Enabled Subsystem' */
}

/*
 * System initialize for enable system:
 *    '<S44>/Enabled Subsystem'
 *    '<S45>/Enabled Subsystem'
 *    '<S36>/Enabled Subsystem'
 *    '<S37>/Enabled Subsystem'
 */
void FOpid_control::FOpid_c_EnabledSubsystem_g_Init
  (B_EnabledSubsystem_FOpid_co_d_T *localB)
{
  /* SystemInitialize for SignalConversion generated from: '<S87>/In1' */
  memset(&localB->In1, 0, sizeof(SL_Bus_std_msgs_Float64));
}

/*
 * Output and update for enable system:
 *    '<S44>/Enabled Subsystem'
 *    '<S45>/Enabled Subsystem'
 *    '<S36>/Enabled Subsystem'
 *    '<S37>/Enabled Subsystem'
 */
void FOpid_control::FOpid_contro_EnabledSubsystem_k(boolean_T rtu_Enable, const
  SL_Bus_std_msgs_Float64 *rtu_In1, B_EnabledSubsystem_FOpid_co_d_T *localB)
{
  /* Outputs for Enabled SubSystem: '<S44>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S87>/Enable'
   */
  if (rtu_Enable) {
    /* SignalConversion generated from: '<S87>/In1' */
    localB->In1 = *rtu_In1;
  }

  /* End of Outputs for SubSystem: '<S44>/Enabled Subsystem' */
}

void FOpid_control::FOpid_contr_Publisher_setupImpl(const
  ros_slros2_internal_block_Pub_T *obj)
{
  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  static const char_T b_zeroDelimTopic[17] = "/ekranoplano/imu";
  qos_profile = rmw_qos_profile_default;

  /* Start for MATLABSystem: '<S30>/SinkBlock' */
  FOpid_control_B.deadline_d.sec = 0.0;
  FOpid_control_B.deadline_d.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST, static_cast<
                 size_t>(10.0), RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE, FOpid_control_B.deadline_d,
                 lifespan, RMW_QOS_POLICY_LIVELINESS_AUTOMATIC,
                 liveliness_lease_duration, (bool)
                 obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i = 0; i < 17; i++) {
    /* Start for MATLABSystem: '<S30>/SinkBlock' */
    FOpid_control_B.b_zeroDelimTopic_g[i] = b_zeroDelimTopic[i];
  }

  Pub_FOpid_control_548.createPublisher(&FOpid_control_B.b_zeroDelimTopic_g[0],
    qos_profile);
}

rmw_qos_profile_t FOpid_control::FO_ROS2PubSubBase_setQOSProfile
  (rmw_qos_profile_t rmwProfile, real_T qosDepth, real_T qosDeadline, real_T
   qosLifespan, real_T qosLeaseDuration, boolean_T
   qosAvoidROSNamespaceConventions)
{
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  real_T input;
  real_T sec;
  input = qosDeadline;

  /* Start for MATLABSystem: '<S31>/SinkBlock' */
  if (qosDeadline == (rtInf)) {
    input = 0.0;
  }

  sec = floor(input);
  FOpid_control_B.deadline_dy.sec = sec;

  /* Start for MATLABSystem: '<S31>/SinkBlock' */
  FOpid_control_B.deadline_dy.nsec = (input - sec) * 1.0E+9;
  input = qosLifespan;

  /* Start for MATLABSystem: '<S31>/SinkBlock' */
  if (qosLifespan == (rtInf)) {
    input = 0.0;
  }

  sec = floor(input);
  lifespan.sec = sec;

  /* Start for MATLABSystem: '<S31>/SinkBlock' */
  lifespan.nsec = (input - sec) * 1.0E+9;
  input = qosLeaseDuration;

  /* Start for MATLABSystem: '<S31>/SinkBlock' */
  if (qosLeaseDuration == (rtInf)) {
    input = 0.0;
  }

  sec = floor(input);
  liveliness_lease_duration.sec = sec;

  /* Start for MATLABSystem: '<S31>/SinkBlock' */
  liveliness_lease_duration.nsec = (input - sec) * 1.0E+9;
  SET_QOS_VALUES(rmwProfile, RMW_QOS_POLICY_HISTORY_KEEP_LAST,
                 static_cast<size_t>(qosDepth),
                 RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE,
                 FOpid_control_B.deadline_dy, lifespan,
                 RMW_QOS_POLICY_LIVELINESS_AUTOMATIC, liveliness_lease_duration,
                 (bool)qosAvoidROSNamespaceConventions);
  return rmwProfile;
}

void FOpid_control::FOpid_con_Publisher_setupImpl_i(const
  ros_slros2_internal_block_Pub_T *obj)
{
  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  static const char_T b_zeroDelimTopic[25] = "/ekranoplano/PoseStamped";
  qos_profile = rmw_qos_profile_default;

  /* Start for MATLABSystem: '<S32>/SinkBlock' */
  FOpid_control_B.deadline_m.sec = 0.0;
  FOpid_control_B.deadline_m.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST,
                 static_cast<size_t>(10.0), RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE, FOpid_control_B.deadline_m,
                 lifespan, RMW_QOS_POLICY_LIVELINESS_AUTOMATIC,
                 liveliness_lease_duration, (bool)
                 obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i = 0; i < 25; i++) {
    /* Start for MATLABSystem: '<S32>/SinkBlock' */
    FOpid_control_B.b_zeroDelimTopic_c[i] = b_zeroDelimTopic[i];
  }

  Pub_FOpid_control_811.createPublisher(&FOpid_control_B.b_zeroDelimTopic_c[0],
    qos_profile);
}

void FOpid_control::FOpid_co_Publisher_setupImpl_ie(const
  ros_slros2_internal_block_Pub_T *obj)
{
  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  static const char_T b_zeroDelimTopic[26] = "/ekranoplano/TwistStamped";
  qos_profile = rmw_qos_profile_default;

  /* Start for MATLABSystem: '<S33>/SinkBlock' */
  FOpid_control_B.deadline.sec = 0.0;
  FOpid_control_B.deadline.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST,
                 static_cast<size_t>(10.0), RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE, FOpid_control_B.deadline,
                 lifespan, RMW_QOS_POLICY_LIVELINESS_AUTOMATIC,
                 liveliness_lease_duration, (bool)
                 obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i = 0; i < 26; i++) {
    /* Start for MATLABSystem: '<S33>/SinkBlock' */
    FOpid_control_B.b_zeroDelimTopic[i] = b_zeroDelimTopic[i];
  }

  Pub_FOpid_control_835.createPublisher(&FOpid_control_B.b_zeroDelimTopic[0],
    qos_profile);
}

void FOpid_control::FOpid_Subscriber_setupImpl_ieih(const
  ros_slros2_internal_block_Sub_T *obj)
{
  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  static const char_T b_zeroDelimTopic[17] = "/setpoint/altura";
  qos_profile = rmw_qos_profile_default;

  /* Start for MATLABSystem: '<S36>/SourceBlock' */
  FOpid_control_B.deadline_j.sec = 0.0;
  FOpid_control_B.deadline_j.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST,
                 static_cast<size_t>(10.0), RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE, FOpid_control_B.deadline_j,
                 lifespan, RMW_QOS_POLICY_LIVELINESS_AUTOMATIC,
                 liveliness_lease_duration, (bool)
                 obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i = 0; i < 17; i++) {
    /* Start for MATLABSystem: '<S36>/SourceBlock' */
    FOpid_control_B.b_zeroDelimTopic_f[i] = b_zeroDelimTopic[i];
  }

  Sub_FOpid_control_435.createSubscriber(&FOpid_control_B.b_zeroDelimTopic_f[0],
    qos_profile);
}

void FOpid_control::FOpi_Subscriber_setupImpl_ieihd(const
  ros_slros2_internal_block_Sub_T *obj)
{
  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  char_T b_zeroDelimTopic[14];
  static const char_T b_zeroDelimTopic_0[14] = "/setpoint/yaw";
  qos_profile = rmw_qos_profile_default;

  /* Start for MATLABSystem: '<S37>/SourceBlock' */
  FOpid_control_B.deadline_gu.sec = 0.0;
  FOpid_control_B.deadline_gu.nsec = 0.0;
  FOpid_control_B.lifespan.sec = 0.0;
  FOpid_control_B.lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST,
                 static_cast<size_t>(10.0), RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE,
                 FOpid_control_B.deadline_gu, FOpid_control_B.lifespan,
                 RMW_QOS_POLICY_LIVELINESS_AUTOMATIC, liveliness_lease_duration,
                 (bool)obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i = 0; i < 14; i++) {
    /* Start for MATLABSystem: '<S37>/SourceBlock' */
    b_zeroDelimTopic[i] = b_zeroDelimTopic_0[i];
  }

  Sub_FOpid_control_377.createSubscriber(&b_zeroDelimTopic[0], qos_profile);
}

void FOpid_control::FOpid_c_ServiceCaller_setupImpl
  (ros_slros2_internal_block_Ser_T *obj)
{
  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  static const char_T b_zeroDelimTopic[25] = "/gazebo/set_entity_state";
  qos_profile = rmw_qos_profile_default;

  /* Start for MATLABSystem: '<S6>/ServiceCaller' */
  FOpid_control_B.deadline_g.sec = 0.0;
  FOpid_control_B.deadline_g.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST,
                 static_cast<size_t>(1.0), RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE, FOpid_control_B.deadline_g,
                 lifespan, RMW_QOS_POLICY_LIVELINESS_AUTOMATIC,
                 liveliness_lease_duration, (bool)
                 obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i = 0; i < 25; i++) {
    /* Start for MATLABSystem: '<S6>/ServiceCaller' */
    FOpid_control_B.b_zeroDelimTopic_m[i] = b_zeroDelimTopic[i];
  }

  ServCall_FOpid_control_326.createServiceCaller
    (&FOpid_control_B.b_zeroDelimTopic_m[0], qos_profile);
}

void FOpid_control::FOpid__Subscriber_setupImpl_iei(const
  ros_slros2_internal_block_Sub_T *obj)
{
  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  static const char_T b_zeroDelimTopic[22] = "/setpoint/turbulencia";
  qos_profile = rmw_qos_profile_default;

  /* Start for MATLABSystem: '<S46>/SourceBlock' */
  FOpid_control_B.deadline_p.sec = 0.0;
  FOpid_control_B.deadline_p.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST,
                 static_cast<size_t>(10.0), RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE, FOpid_control_B.deadline_p,
                 lifespan, RMW_QOS_POLICY_LIVELINESS_AUTOMATIC,
                 liveliness_lease_duration, (bool)
                 obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i = 0; i < 22; i++) {
    /* Start for MATLABSystem: '<S46>/SourceBlock' */
    FOpid_control_B.b_zeroDelimTopic_b[i] = b_zeroDelimTopic[i];
  }

  Sub_FOpid_control_417.createSubscriber(&FOpid_control_B.b_zeroDelimTopic_b[0],
    qos_profile);
}

void FOpid_control::FOpid_cont_Subscriber_setupImpl(const
  ros_slros2_internal_block_Sub_T *obj)
{
  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  static const char_T b_zeroDelimTopic[22] = "/setpoint/turbulencia";
  qos_profile = rmw_qos_profile_default;

  /* Start for MATLABSystem: '<S43>/SourceBlock' */
  FOpid_control_B.deadline_n.sec = 0.0;
  FOpid_control_B.deadline_n.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST,
                 static_cast<size_t>(10.0), RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE, FOpid_control_B.deadline_n,
                 lifespan, RMW_QOS_POLICY_LIVELINESS_AUTOMATIC,
                 liveliness_lease_duration, (bool)
                 obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i = 0; i < 22; i++) {
    /* Start for MATLABSystem: '<S43>/SourceBlock' */
    FOpid_control_B.b_zeroDelimTopic_cx[i] = b_zeroDelimTopic[i];
  }

  Sub_FOpid_control_423.createSubscriber(&FOpid_control_B.b_zeroDelimTopic_cx[0],
    qos_profile);
}

void FOpid_control::FOpid_co_Subscriber_setupImpl_i(const
  ros_slros2_internal_block_Sub_T *obj)
{
  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  char_T b_zeroDelimTopic[12];
  static const char_T b_zeroDelimTopic_0[12] = "/olas/heave";
  qos_profile = rmw_qos_profile_default;

  /* Start for MATLABSystem: '<S44>/SourceBlock' */
  FOpid_control_B.deadline_ld.sec = 0.0;
  FOpid_control_B.deadline_ld.nsec = 0.0;
  FOpid_control_B.lifespan_d.sec = 0.0;
  FOpid_control_B.lifespan_d.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST,
                 static_cast<size_t>(10.0), RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE,
                 FOpid_control_B.deadline_ld, FOpid_control_B.lifespan_d,
                 RMW_QOS_POLICY_LIVELINESS_AUTOMATIC, liveliness_lease_duration,
                 (bool)obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i = 0; i < 12; i++) {
    /* Start for MATLABSystem: '<S44>/SourceBlock' */
    b_zeroDelimTopic[i] = b_zeroDelimTopic_0[i];
  }

  Sub_FOpid_control_443.createSubscriber(&b_zeroDelimTopic[0], qos_profile);
}

void FOpid_control::FOpid_c_Subscriber_setupImpl_ie(const
  ros_slros2_internal_block_Sub_T *obj)
{
  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  static const char_T b_zeroDelimTopic[17] = "/olas/pitch_rate";
  qos_profile = rmw_qos_profile_default;

  /* Start for MATLABSystem: '<S45>/SourceBlock' */
  FOpid_control_B.deadline_l.sec = 0.0;
  FOpid_control_B.deadline_l.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST,
                 static_cast<size_t>(10.0), RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE, FOpid_control_B.deadline_l,
                 lifespan, RMW_QOS_POLICY_LIVELINESS_AUTOMATIC,
                 liveliness_lease_duration, (bool)
                 obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i = 0; i < 17; i++) {
    /* Start for MATLABSystem: '<S45>/SourceBlock' */
    FOpid_control_B.b_zeroDelimTopic_cv[i] = b_zeroDelimTopic[i];
  }

  Sub_FOpid_control_445.createSubscriber(&FOpid_control_B.b_zeroDelimTopic_cv[0],
    qos_profile);
}

real_T rt_urand_Upu32_Yd_f_pw_snf(uint32_T *u)
{
  uint32_T hi;
  uint32_T lo;

  /* Uniform random number generator (random number between 0 and 1)

     #define IA      16807                      magic multiplier = 7^5
     #define IM      2147483647                 modulus = 2^31-1
     #define IQ      127773                     IM div IA
     #define IR      2836                       IM modulo IA
     #define S       4.656612875245797e-10      reciprocal of 2^31-1
     test = IA * (seed % IQ) - IR * (seed/IQ)
     seed = test < 0 ? (test + IM) : test
     return (seed*S)
   */
  lo = *u % 127773U * 16807U;
  hi = *u / 127773U * 2836U;
  if (lo < hi) {
    *u = 2147483647U - (hi - lo);
  } else {
    *u = lo - hi;
  }

  return static_cast<real_T>(*u) * 4.656612875245797E-10;
}

real_T rt_nrand_Upu32_Yd_f_pw_snf(uint32_T *u)
{
  real_T si;
  real_T sr;
  real_T y;

  /* Normal (Gaussian) random number generator */
  do {
    sr = 2.0 * rt_urand_Upu32_Yd_f_pw_snf(u) - 1.0;
    si = 2.0 * rt_urand_Upu32_Yd_f_pw_snf(u) - 1.0;
    si = sr * sr + si * si;
  } while (si > 1.0);

  y = sqrt(-2.0 * log(si) / si) * sr;
  return y;
}

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    int32_T tmp;
    int32_T tmp_0;
    if (u0 > 0.0) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    if (u1 > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    y = atan2(static_cast<real_T>(tmp), static_cast<real_T>(tmp_0));
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    real_T tmp;
    real_T tmp_0;
    tmp = fabs(u0);
    tmp_0 = fabs(u1);
    if (rtIsInf(u1)) {
      if (tmp == 1.0) {
        y = 1.0;
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = (rtNaN);
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

/* Model step function */
void FOpid_control::step()
{
  /* local block i/o variables */
  SL_Bus_std_msgs_Float64 rtb_SourceBlock_o2_d;
  SL_Bus_std_msgs_Bool rtb_SourceBlock_o2_j;
  SL_Bus_std_msgs_Bool rtb_SourceBlock_o2_dd;
  if (rtmIsMajorTimeStep((&FOpid_control_M))) {
    /* set solver stop time */
    if (!((&FOpid_control_M)->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&(&FOpid_control_M)->solverInfo, (((&FOpid_control_M)
        ->Timing.clockTickH0 + 1) * (&FOpid_control_M)->Timing.stepSize0 *
        4294967296.0));
    } else {
      rtsiSetSolverStopTime(&(&FOpid_control_M)->solverInfo, (((&FOpid_control_M)
        ->Timing.clockTick0 + 1) * (&FOpid_control_M)->Timing.stepSize0 +
        (&FOpid_control_M)->Timing.clockTickH0 * (&FOpid_control_M)
        ->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&FOpid_control_M))) {
    (&FOpid_control_M)->Timing.t[0] = rtsiGetT(&(&FOpid_control_M)->solverInfo);
  }

  {
    __m128d tmp_1;
    SL_Bus_gazebo_msgs_SetEntityStateResponse tmp;
    int32_T i;
    uint32_T rtb_nsec_0;
    int8_T rtAction;
    int8_T rtPrevAction;
    boolean_T serverAvailableOnTime;
    boolean_T tmp_0;
    static const uint8_T b[15] = { 101U, 107U, 114U, 97U, 110U, 111U, 112U, 108U,
      97U, 110U, 111U, 45U, 105U, 109U, 117U };

    static const uint8_T b_0[5] = { 119U, 111U, 114U, 108U, 100U };

    static const uint8_T b_1[11] = { 101U, 107U, 114U, 97U, 110U, 111U, 112U,
      108U, 97U, 110U, 111U };

    /* BusAssignment: '<Root>/Bus Assignment-IMU' */
    memset(&FOpid_control_B.BusAssignmentIMU, 0, sizeof(SL_Bus_sensor_msgs_Imu));

    /* RelationalOperator: '<S39>/Compare' incorporates:
     *  Constant: '<S39>/Constant'
     */
    FOpid_control_B.Compare = (FOpid_control_X.Integrator_CSTATE[11] >= 0.05);

    /* Outputs for Enabled SubSystem: '<S48>/Hrgw' incorporates:
     *  EnablePort: '<S61>/Enable'
     */
    /* Outputs for Enabled SubSystem: '<S48>/Hqgw' incorporates:
     *  EnablePort: '<S60>/Enable'
     */
    /* Outputs for Enabled SubSystem: '<S48>/Hpgw' incorporates:
     *  EnablePort: '<S59>/Enable'
     */
    /* Outputs for Enabled SubSystem: '<S49>/Hwgw(s)' incorporates:
     *  EnablePort: '<S64>/Enable'
     */
    /* Outputs for Enabled SubSystem: '<S49>/Hvgw(s)' incorporates:
     *  EnablePort: '<S63>/Enable'
     */
    tmp_0 = (rtmIsMajorTimeStep((&FOpid_control_M)) &&
             (&FOpid_control_M)->Timing.TaskCounters.TID[1] == 0);

    /* End of Outputs for SubSystem: '<S49>/Hvgw(s)' */
    /* End of Outputs for SubSystem: '<S49>/Hwgw(s)' */
    /* End of Outputs for SubSystem: '<S48>/Hpgw' */
    /* End of Outputs for SubSystem: '<S48>/Hqgw' */
    /* End of Outputs for SubSystem: '<S48>/Hrgw' */
    if (tmp_0) {
      /* MATLAB Function: '<S35>/MATLAB Function-reset' incorporates:
       *  Memory: '<S35>/Memory2'
       */
      memcpy(&FOpid_control_B.IC[0], &FOpid_control_DW.Memory2_PreviousInput[0],
             12U * sizeof(real_T));
      FOpid_control_B.IC[2] = 0.0;
      FOpid_control_B.IC[11] = 0.0;

      /* InitialCondition: '<S35>/IC' */
      if (FOpid_control_DW.IC_FirstOutputTime) {
        FOpid_control_DW.IC_FirstOutputTime = false;

        /* InitialCondition: '<S35>/IC' */
        memcpy(&FOpid_control_B.IC[0], &FOpid_control_ConstP.pooled14[0], 12U *
               sizeof(real_T));
      }

      /* End of InitialCondition: '<S35>/IC' */
    }

    /* Integrator: '<S35>/Integrator' incorporates:
     *  InitialCondition: '<S35>/IC'
     */
    if (rtsiIsModeUpdateTimeStep(&(&FOpid_control_M)->solverInfo)) {
      serverAvailableOnTime = (((FOpid_control_PrevZCX.Integrator_Reset_ZCE ==
        POS_ZCSIG) != FOpid_control_B.Compare) &&
        (FOpid_control_PrevZCX.Integrator_Reset_ZCE != UNINITIALIZED_ZCSIG));
      FOpid_control_PrevZCX.Integrator_Reset_ZCE = FOpid_control_B.Compare;

      /* evaluate zero-crossings and the level of the reset signal */
      if (serverAvailableOnTime || FOpid_control_B.Compare ||
          FOpid_control_DW.Integrator_DWORK1) {
        memcpy(&FOpid_control_X.Integrator_CSTATE[0], &FOpid_control_B.IC[0],
               12U * sizeof(real_T));
        rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
          ->solverInfo, true);
        rtsiSetContTimeOutputInconsistentWithStateAtMajorStep(&(&FOpid_control_M)
          ->solverInfo, true);
      }
    }

    /* Integrator: '<S35>/Integrator' */
    memcpy(&FOpid_control_B.x[0], &FOpid_control_X.Integrator_CSTATE[0], 12U *
           sizeof(real_T));

    /* MATLABSystem: '<Root>/Coordinate Transformation Conversion' */
    if (!FOpid_control_DW.fctrlobj_not_empty) {
      FOpid_control_DW.fctrlobj.FeatureControlFlag = false;
      FOpid_control_DW.fctrlobj_not_empty = true;
    }

    /* SignalConversion generated from: '<Root>/Coordinate Transformation Conversion' incorporates:
     *  MATLABSystem: '<Root>/Coordinate Transformation Conversion'
     */
    _mm_storeu_pd(&FOpid_control_B.wbe_b[0], _mm_div_pd(_mm_set_pd
      (FOpid_control_B.x[6], FOpid_control_B.x[8]), _mm_set1_pd(2.0)));

    /* MATLABSystem: '<Root>/Coordinate Transformation Conversion' incorporates:
     *  SignalConversion generated from: '<Root>/Coordinate Transformation Conversion'
     */
    FOpid_control_B.wbe_b[2] = FOpid_control_B.x[7] / 2.0;
    FOpid_control_B.sina = sin(FOpid_control_B.wbe_b[0]);
    FOpid_control_B.sinb = sin(FOpid_control_B.wbe_b[1]);
    FOpid_control_B.sinc = sin(FOpid_control_B.wbe_b[2]);
    FOpid_control_B.cosa = cos(FOpid_control_B.wbe_b[0]);
    FOpid_control_B.cosb = cos(FOpid_control_B.wbe_b[1]);
    FOpid_control_B.cosc = cos(FOpid_control_B.wbe_b[2]);

    /* Start for MATLABSystem: '<Root>/Coordinate Transformation Conversion' */
    FOpid_control_B.rtb_CoordinateTransformationC_n = FOpid_control_B.cosa *
      FOpid_control_B.cosb;

    /* MATLABSystem: '<Root>/Coordinate Transformation Conversion' */
    FOpid_control_B.rtb_CoordinateTransformation_bs = FOpid_control_B.sina *
      FOpid_control_B.sinb * FOpid_control_B.sinc +
      FOpid_control_B.rtb_CoordinateTransformationC_n * FOpid_control_B.cosc;
    FOpid_control_B.rtb_CoordinateTransformationC_n =
      FOpid_control_B.rtb_CoordinateTransformationC_n * FOpid_control_B.sinc -
      FOpid_control_B.cosc * FOpid_control_B.sina * FOpid_control_B.sinb;
    FOpid_control_B.rtb_CoordinateTransformationC_b = FOpid_control_B.cosa *
      FOpid_control_B.cosc * FOpid_control_B.sinb + FOpid_control_B.cosb *
      FOpid_control_B.sina * FOpid_control_B.sinc;
    FOpid_control_B.cosb = FOpid_control_B.cosb * FOpid_control_B.cosc *
      FOpid_control_B.sina - FOpid_control_B.cosa * FOpid_control_B.sinb *
      FOpid_control_B.sinc;
    if (tmp_0) {
      /* MATLAB Function: '<Root>/MATLAB Function-IMU2' */
      memset(&FOpid_control_B.stringOut_c[0], 0, sizeof(uint8_T) << 7U);
      for (i = 0; i < 15; i++) {
        FOpid_control_B.stringOut_c[i] = b[i];
      }

      FOpid_control_B.lengthOut_o = 15U;

      /* End of MATLAB Function: '<Root>/MATLAB Function-IMU2' */
    }

    /* MATLAB Function: '<Root>/MATLAB Function-ned_to_imu' incorporates:
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_gazebo'
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_odometry'
     */
    FOpid_control_B.sina = 0.0 * FOpid_control_B.rtb_CoordinateTransformationC_b
      + FOpid_control_B.rtb_CoordinateTransformationC_n;

    /* BusAssignment: '<Root>/Bus Assignment-IMU' incorporates:
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_imu'
     */
    FOpid_control_B.BusAssignmentIMU.orientation.x = -FOpid_control_B.sina;

    /* MATLAB Function: '<Root>/MATLAB Function-ned_to_imu' incorporates:
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_gazebo'
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_odometry'
     */
    FOpid_control_B.sinb = 0.0 * FOpid_control_B.rtb_CoordinateTransformationC_n
      - FOpid_control_B.rtb_CoordinateTransformationC_b;

    /* BusAssignment: '<Root>/Bus Assignment-IMU' incorporates:
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_imu'
     */
    FOpid_control_B.BusAssignmentIMU.orientation.y = FOpid_control_B.sinb;

    /* MATLAB Function: '<Root>/MATLAB Function-ned_to_imu' incorporates:
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_gazebo'
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_odometry'
     */
    FOpid_control_B.sinc = 0.0 * FOpid_control_B.rtb_CoordinateTransformation_bs
      - FOpid_control_B.cosb;

    /* BusAssignment: '<Root>/Bus Assignment-IMU' incorporates:
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_imu'
     */
    FOpid_control_B.BusAssignmentIMU.orientation.z = -FOpid_control_B.sinc;

    /* MATLAB Function: '<Root>/MATLAB Function-ned_to_imu' incorporates:
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_gazebo'
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_odometry'
     */
    FOpid_control_B.cosa = 0.0 * FOpid_control_B.cosb +
      FOpid_control_B.rtb_CoordinateTransformation_bs;

    /* BusAssignment: '<Root>/Bus Assignment-IMU' incorporates:
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_imu'
     */
    FOpid_control_B.BusAssignmentIMU.orientation.w = FOpid_control_B.cosa;
    FOpid_control_B.BusAssignmentIMU.angular_velocity.x = FOpid_control_B.x[0];
    FOpid_control_B.BusAssignmentIMU.angular_velocity.y = FOpid_control_B.x[1];
    FOpid_control_B.BusAssignmentIMU.angular_velocity.z = FOpid_control_B.x[2];
    memcpy(&FOpid_control_B.BusAssignmentIMU.header.frame_id[0],
           &FOpid_control_B.stringOut_c[0], sizeof(uint8_T) << 7U);
    FOpid_control_B.BusAssignmentIMU.header.frame_id_SL_Info.CurrentLength =
      FOpid_control_B.lengthOut_o;

    /* MATLABSystem: '<S30>/SinkBlock' */
    Pub_FOpid_control_548.publish(&FOpid_control_B.BusAssignmentIMU);

    /* Gain: '<Root>/Gain-Z' */
    FOpid_control_B.GainZ = -FOpid_control_B.x[11];
    if (tmp_0) {
      /* MATLAB Function: '<Root>/MATLAB Function-Odometry' */
      memset(&FOpid_control_B.str_out_c[0], 0, sizeof(uint8_T) << 7U);
      for (i = 0; i < 5; i++) {
        FOpid_control_B.str_out_c[i] = b_0[i];
      }

      FOpid_control_B.currentLen_l = 5U;
      FOpid_control_B.receivedLen_b = 5U;

      /* End of MATLAB Function: '<Root>/MATLAB Function-Odometry' */

      /* MATLAB Function: '<Root>/MATLAB Function-Odometry1' */
      memset(&FOpid_control_B.str_out[0], 0, sizeof(uint8_T) << 7U);
      for (i = 0; i < 11; i++) {
        FOpid_control_B.str_out[i] = b_1[i];
      }

      FOpid_control_B.currentLen = 11U;
      FOpid_control_B.receivedLen = 11U;

      /* End of MATLAB Function: '<Root>/MATLAB Function-Odometry1' */
    }

    /* Clock: '<Root>/Clock' */
    FOpid_control_B.cosc = (&FOpid_control_M)->Timing.t[0];

    /* MATLAB Function: '<Root>/MATLAB Function-clocl' */
    FOpid_control_B.FA_b_idx_0 = floor(FOpid_control_B.cosc);

    /* BusAssignment: '<Root>/Bus Assignment-ODOM' */
    memset(&FOpid_control_B.BusAssignmentODOM, 0, sizeof
           (SL_Bus_nav_msgs_Odometry));

    /* MATLAB Function: '<Root>/MATLAB Function-clocl' */
    if (FOpid_control_B.FA_b_idx_0 < 2.147483648E+9) {
      if (FOpid_control_B.FA_b_idx_0 >= -2.147483648E+9) {
        i = static_cast<int32_T>(FOpid_control_B.FA_b_idx_0);
      } else {
        i = MIN_int32_T;
      }
    } else {
      i = MAX_int32_T;
    }

    FOpid_control_B.cosc = rt_roundd_snf((FOpid_control_B.cosc -
      FOpid_control_B.FA_b_idx_0) * 1.0E+9);
    if (FOpid_control_B.cosc < 4.294967296E+9) {
      if (FOpid_control_B.cosc >= 0.0) {
        rtb_nsec_0 = static_cast<uint32_T>(FOpid_control_B.cosc);
      } else {
        rtb_nsec_0 = 0U;
      }
    } else {
      rtb_nsec_0 = MAX_uint32_T;
    }

    /* BusAssignment: '<Root>/Bus Assignment-ODOM' incorporates:
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_gazebo'
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_odometry'
     */
    FOpid_control_B.BusAssignmentODOM.pose.pose.position.x = FOpid_control_B.x
      [10];
    FOpid_control_B.BusAssignmentODOM.pose.pose.position.y = FOpid_control_B.x[9];
    FOpid_control_B.BusAssignmentODOM.pose.pose.position.z =
      -FOpid_control_B.GainZ;

    /* MATLAB Function: '<Root>/MATLAB Function-ned_to_odometry' */
    FOpid_control_B.cosc = 0.7071 * FOpid_control_B.sinb;
    FOpid_control_B.FA_b_idx_0 = 0.7071 * -FOpid_control_B.sina;

    /* BusAssignment: '<Root>/Bus Assignment-ODOM' incorporates:
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_odometry'
     */
    FOpid_control_B.BusAssignmentODOM.pose.pose.orientation.x =
      FOpid_control_B.FA_b_idx_0 + FOpid_control_B.cosc;
    FOpid_control_B.BusAssignmentODOM.pose.pose.orientation.y =
      FOpid_control_B.cosc - FOpid_control_B.FA_b_idx_0;

    /* MATLAB Function: '<Root>/MATLAB Function-ned_to_odometry' */
    FOpid_control_B.cosc = 0.7071 * FOpid_control_B.cosa;
    FOpid_control_B.FA_b_idx_0 = 0.7071 * FOpid_control_B.sinc;

    /* BusAssignment: '<Root>/Bus Assignment-ODOM' incorporates:
     *  MATLAB Function: '<Root>/MATLAB Function-clocl'
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_odometry'
     */
    FOpid_control_B.BusAssignmentODOM.pose.pose.orientation.z =
      FOpid_control_B.FA_b_idx_0 + FOpid_control_B.cosc;
    FOpid_control_B.BusAssignmentODOM.pose.pose.orientation.w =
      FOpid_control_B.cosc - FOpid_control_B.FA_b_idx_0;
    FOpid_control_B.BusAssignmentODOM.header.frame_id_SL_Info.CurrentLength =
      FOpid_control_B.currentLen_l;
    FOpid_control_B.BusAssignmentODOM.header.frame_id_SL_Info.ReceivedLength =
      FOpid_control_B.receivedLen_b;
    memcpy(&FOpid_control_B.BusAssignmentODOM.header.frame_id[0],
           &FOpid_control_B.str_out_c[0], sizeof(uint8_T) << 7U);
    memcpy(&FOpid_control_B.BusAssignmentODOM.child_frame_id[0],
           &FOpid_control_B.str_out[0], sizeof(uint8_T) << 7U);
    FOpid_control_B.BusAssignmentODOM.child_frame_id_SL_Info.CurrentLength =
      FOpid_control_B.currentLen;
    FOpid_control_B.BusAssignmentODOM.child_frame_id_SL_Info.ReceivedLength =
      FOpid_control_B.receivedLen;
    FOpid_control_B.BusAssignmentODOM.header.stamp.sec = i;
    FOpid_control_B.BusAssignmentODOM.header.stamp.nanosec = rtb_nsec_0;

    /* MATLABSystem: '<S31>/SinkBlock' */
    Pub_FOpid_control_697.publish(&FOpid_control_B.BusAssignmentODOM);
    if (tmp_0) {
      /* MATLAB Function: '<Root>/MATLAB Function-ned_to_PoseStamped' */
      MATLABFunctionned_to_PoseStampe
        (&FOpid_control_B.sf_MATLABFunctionned_to_PoseS_b);
    }

    /* BusAssignment: '<Root>/Bus Assignment-PoseStaamped' incorporates:
     *  MATLAB Function: '<Root>/MATLAB Function-clocl'
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_PoseStaamped'
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_gazebo'
     */
    memset(&FOpid_control_B.BusAssignmentPoseStaamped, 0, sizeof
           (SL_Bus_geometry_msgs_PoseStamped));
    memcpy(&FOpid_control_B.BusAssignmentPoseStaamped.header.frame_id[0],
           &FOpid_control_B.sf_MATLABFunctionned_to_PoseS_b.stringOut[0], sizeof
           (uint8_T) << 7U);
    FOpid_control_B.BusAssignmentPoseStaamped.header.frame_id_SL_Info.CurrentLength
      = FOpid_control_B.sf_MATLABFunctionned_to_PoseS_b.lengthOut;
    FOpid_control_B.BusAssignmentPoseStaamped.pose.position.x =
      -FOpid_control_B.x[10];
    FOpid_control_B.BusAssignmentPoseStaamped.pose.position.y =
      FOpid_control_B.x[9];
    FOpid_control_B.BusAssignmentPoseStaamped.pose.position.z =
      -FOpid_control_B.GainZ;
    FOpid_control_B.BusAssignmentPoseStaamped.pose.orientation.x = 0.7071 *
      FOpid_control_B.rtb_CoordinateTransformationC_b + -0.7071 *
      FOpid_control_B.rtb_CoordinateTransformationC_n;
    FOpid_control_B.BusAssignmentPoseStaamped.pose.orientation.y = 0.7071 *
      FOpid_control_B.rtb_CoordinateTransformationC_n - -0.7071 *
      FOpid_control_B.rtb_CoordinateTransformationC_b;
    FOpid_control_B.BusAssignmentPoseStaamped.pose.orientation.z = -(0.7071 *
      FOpid_control_B.cosb + -0.7071 *
      FOpid_control_B.rtb_CoordinateTransformation_bs);
    FOpid_control_B.BusAssignmentPoseStaamped.pose.orientation.w = 0.7071 *
      FOpid_control_B.rtb_CoordinateTransformation_bs - -0.7071 *
      FOpid_control_B.cosb;
    FOpid_control_B.BusAssignmentPoseStaamped.header.stamp.sec = i;
    FOpid_control_B.BusAssignmentPoseStaamped.header.stamp.nanosec = rtb_nsec_0;

    /* MATLABSystem: '<S32>/SinkBlock' */
    Pub_FOpid_control_811.publish(&FOpid_control_B.BusAssignmentPoseStaamped);
    if (tmp_0) {
      /* MATLAB Function: '<Root>/MATLAB Function-ned_to_TwistStamped' */
      MATLABFunctionned_to_PoseStampe
        (&FOpid_control_B.sf_MATLABFunctionned_to_TwistSt);
    }

    /* BusAssignment: '<Root>/Bus Assignment-TwistStamped' incorporates:
     *  MATLAB Function: '<Root>/MATLAB Function-clocl'
     *  MATLAB Function: '<Root>/MATLAB Function2'
     */
    memset(&FOpid_control_B.BusAssignmentTwistStamped, 0, sizeof
           (SL_Bus_geometry_msgs_TwistStamped));
    memcpy(&FOpid_control_B.BusAssignmentTwistStamped.header.frame_id[0],
           &FOpid_control_B.sf_MATLABFunctionned_to_TwistSt.stringOut[0], sizeof
           (uint8_T) << 7U);
    FOpid_control_B.BusAssignmentTwistStamped.header.frame_id_SL_Info.CurrentLength
      = FOpid_control_B.sf_MATLABFunctionned_to_TwistSt.lengthOut;
    FOpid_control_B.BusAssignmentTwistStamped.twist.linear.x =
      FOpid_control_B.x[1];
    FOpid_control_B.BusAssignmentTwistStamped.twist.linear.y =
      FOpid_control_B.x[0];
    FOpid_control_B.BusAssignmentTwistStamped.twist.linear.z =
      -FOpid_control_B.x[2];
    FOpid_control_B.BusAssignmentTwistStamped.header.stamp.sec = i;
    FOpid_control_B.BusAssignmentTwistStamped.header.stamp.nanosec = rtb_nsec_0;

    /* MATLABSystem: '<S33>/SinkBlock' */
    Pub_FOpid_control_835.publish(&FOpid_control_B.BusAssignmentTwistStamped);
    if (tmp_0) {
      /* MATLABSystem: '<S36>/SourceBlock' */
      FOpid_control_B.SourceBlock_o1_o = Sub_FOpid_control_435.getLatestMessage(
        &rtb_SourceBlock_o2_d);

      /* Outputs for Enabled SubSystem: '<S36>/Enabled Subsystem' */
      FOpid_contro_EnabledSubsystem_k(FOpid_control_B.SourceBlock_o1_o,
        &rtb_SourceBlock_o2_d, &FOpid_control_B.EnabledSubsystem_b);

      /* End of Outputs for SubSystem: '<S36>/Enabled Subsystem' */

      /* UnitDelay: '<Root>/Unit Delay3' */
      FOpid_control_B.Gain2 = FOpid_control_DW.UnitDelay3_DSTATE;

      /* Switch: '<Root>/Switch3' */
      if (FOpid_control_B.SourceBlock_o1_o) {
        /* Switch: '<Root>/Switch3' */
        FOpid_control_B.Switch3 = FOpid_control_B.EnabledSubsystem_b.In1.data;
      } else {
        /* Switch: '<Root>/Switch3' */
        FOpid_control_B.Switch3 = FOpid_control_B.Gain2;
      }

      /* End of Switch: '<Root>/Switch3' */
    }

    /* Sum: '<Root>/Sum2' */
    FOpid_control_B.Sum2 = FOpid_control_B.Switch3 - FOpid_control_B.GainZ;
    if (tmp_0) {
      /* MATLAB Function: '<Root>/MATLAB Function - fopid_altura' incorporates:
       *  Constant: '<Root>/Constant3'
       *  Constant: '<Root>/Constant4'
       *  Constant: '<Root>/Constant5'
       */
      FOpid_control_B.u_l = ((((((((FOpid_control_DW.y1_b - 2.0 *
        FOpid_control_DW.y2_he) + FOpid_control_DW.y3_a3) * -1.8 +
        ((FOpid_control_B.GainZ - 2.0 * FOpid_control_DW.y1_b) +
         FOpid_control_DW.y2_he)) + ((FOpid_control_DW.y2_he - 2.0 *
        FOpid_control_DW.y3_a3) + FOpid_control_DW.y4_g) * 1.62) +
        ((FOpid_control_DW.y3_a3 - 2.0 * FOpid_control_DW.y4_g) +
         FOpid_control_DW.y5_e) * -1.572) + ((FOpid_control_DW.y4_g - 2.0 *
        FOpid_control_DW.y5_e) + FOpid_control_DW.y6_b) * 1.5174) +
        ((FOpid_control_DW.y5_e - 2.0 * FOpid_control_DW.y6_b) +
         FOpid_control_DW.y7_mc) * -1.489464) * 1.1773992067262726 +
        ((FOpid_control_B.Sum2 - FOpid_control_DW.e1_j) * 0.5 +
         FOpid_control_DW.u_prev_i)) + (((((((2.0 * FOpid_control_DW.e2_i +
        FOpid_control_DW.e1_j) + FOpid_control_DW.e3_c) * -0.6000000000000001 +
        ((2.0 * FOpid_control_DW.e1_j + FOpid_control_B.Sum2) +
         FOpid_control_DW.e2_i)) + ((2.0 * FOpid_control_DW.e3_c +
        FOpid_control_DW.e2_i) + FOpid_control_DW.e4_p) * 0.18000000000000005) +
        ((2.0 * FOpid_control_DW.e4_p + FOpid_control_DW.e3_c) +
         FOpid_control_DW.e5_b) * -0.23600000000000004) + ((2.0 *
        FOpid_control_DW.e5_b + FOpid_control_DW.e4_p) + FOpid_control_DW.e6_b) *
        0.12540000000000004) + ((2.0 * FOpid_control_DW.e6_b +
        FOpid_control_DW.e5_b) + FOpid_control_DW.e7_d) * -0.15664800000000004) *
        0.0009802605560822353;
      if (!(FOpid_control_B.u_l <= 0.2)) {
        FOpid_control_B.u_l = 0.2;
      }

      if (!(FOpid_control_B.u_l >= -0.2)) {
        FOpid_control_B.u_l = -0.2;
      }

      FOpid_control_DW.u_prev_i = FOpid_control_B.u_l;
      FOpid_control_DW.e7_d = FOpid_control_DW.e6_b;
      FOpid_control_DW.e6_b = FOpid_control_DW.e5_b;
      FOpid_control_DW.e5_b = FOpid_control_DW.e4_p;
      FOpid_control_DW.e4_p = FOpid_control_DW.e3_c;
      FOpid_control_DW.e3_c = FOpid_control_DW.e2_i;
      FOpid_control_DW.e2_i = FOpid_control_DW.e1_j;
      FOpid_control_DW.e1_j = FOpid_control_B.Sum2;
      FOpid_control_DW.y7_mc = FOpid_control_DW.y6_b;
      FOpid_control_DW.y6_b = FOpid_control_DW.y5_e;
      FOpid_control_DW.y5_e = FOpid_control_DW.y4_g;
      FOpid_control_DW.y4_g = FOpid_control_DW.y3_a3;
      FOpid_control_DW.y3_a3 = FOpid_control_DW.y2_he;
      FOpid_control_DW.y2_he = FOpid_control_DW.y1_b;
      FOpid_control_DW.y1_b = FOpid_control_B.GainZ;

      /* End of MATLAB Function: '<Root>/MATLAB Function - fopid_altura' */

      /* MATLABSystem: '<S37>/SourceBlock' */
      FOpid_control_B.SourceBlock_o1 = Sub_FOpid_control_377.getLatestMessage
        (&FOpid_control_B.SourceBlock_o2);

      /* Outputs for Enabled SubSystem: '<S37>/Enabled Subsystem' */
      FOpid_contro_EnabledSubsystem_k(FOpid_control_B.SourceBlock_o1,
        &FOpid_control_B.SourceBlock_o2, &FOpid_control_B.EnabledSubsystem_a);

      /* End of Outputs for SubSystem: '<S37>/Enabled Subsystem' */

      /* UnitDelay: '<Root>/Unit Delay2' */
      FOpid_control_B.Gain2 = FOpid_control_DW.UnitDelay2_DSTATE;

      /* Switch: '<Root>/Switch2' */
      if (FOpid_control_B.SourceBlock_o1) {
        /* Switch: '<Root>/Switch2' */
        FOpid_control_B.Switch2 = FOpid_control_B.EnabledSubsystem_a.In1.data;
      } else {
        /* Switch: '<Root>/Switch2' */
        FOpid_control_B.Switch2 = FOpid_control_B.Gain2;
      }

      /* End of Switch: '<Root>/Switch2' */
    }

    /* Sum: '<Root>/Sum5' */
    FOpid_control_B.Sum5 = FOpid_control_B.Switch2 - FOpid_control_B.x[8];
    if (tmp_0) {
      /* MATLAB Function: '<Root>/MATLAB Function - fopid_yaw' incorporates:
       *  Constant: '<Root>/Constant10'
       *  Constant: '<Root>/Constant11'
       */
      FOpid_control_B.u = ((((((((FOpid_control_B.x[8] - 2.0 *
        FOpid_control_DW.y1) + FOpid_control_DW.y2) - ((FOpid_control_DW.y1 -
        2.0 * FOpid_control_DW.y2) + FOpid_control_DW.y3)) +
        ((FOpid_control_DW.y2 - 2.0 * FOpid_control_DW.y3) + FOpid_control_DW.y4)
        * 0.5) + ((FOpid_control_DW.y3 - 2.0 * FOpid_control_DW.y4) +
                  FOpid_control_DW.y5) * -0.5) + ((FOpid_control_DW.y4 - 2.0 *
        FOpid_control_DW.y5) + FOpid_control_DW.y6) * 0.375) +
                            ((FOpid_control_DW.y5 - 2.0 * FOpid_control_DW.y6) +
        FOpid_control_DW.y7) * -0.375) * -0.0 + (FOpid_control_DW.u_prev -
        (FOpid_control_B.Sum5 - FOpid_control_DW.e1))) + (((((((2.0 *
        FOpid_control_DW.e2 + FOpid_control_DW.e1) + FOpid_control_DW.e3) *
        -0.6000000000000001 + ((2.0 * FOpid_control_DW.e1 + FOpid_control_B.Sum5)
        + FOpid_control_DW.e2)) + ((2.0 * FOpid_control_DW.e3 +
        FOpid_control_DW.e2) + FOpid_control_DW.e4) * 0.18000000000000005) +
        ((2.0 * FOpid_control_DW.e4 + FOpid_control_DW.e3) + FOpid_control_DW.e5)
        * -0.23600000000000004) + ((2.0 * FOpid_control_DW.e5 +
        FOpid_control_DW.e4) + FOpid_control_DW.e6) * 0.12540000000000004) +
        ((2.0 * FOpid_control_DW.e6 + FOpid_control_DW.e5) + FOpid_control_DW.e7)
        * -0.15664800000000004) * -0.012253256951027941;
      if (!(FOpid_control_B.u <= 0.09)) {
        FOpid_control_B.u = 0.09;
      }

      if (!(FOpid_control_B.u >= -0.09)) {
        FOpid_control_B.u = -0.09;
      }

      FOpid_control_DW.u_prev = FOpid_control_B.u;
      FOpid_control_DW.e7 = FOpid_control_DW.e6;
      FOpid_control_DW.e6 = FOpid_control_DW.e5;
      FOpid_control_DW.e5 = FOpid_control_DW.e4;
      FOpid_control_DW.e4 = FOpid_control_DW.e3;
      FOpid_control_DW.e3 = FOpid_control_DW.e2;
      FOpid_control_DW.e2 = FOpid_control_DW.e1;
      FOpid_control_DW.e1 = FOpid_control_B.Sum5;
      FOpid_control_DW.y7 = FOpid_control_DW.y6;
      FOpid_control_DW.y6 = FOpid_control_DW.y5;
      FOpid_control_DW.y5 = FOpid_control_DW.y4;
      FOpid_control_DW.y4 = FOpid_control_DW.y3;
      FOpid_control_DW.y3 = FOpid_control_DW.y2;
      FOpid_control_DW.y2 = FOpid_control_DW.y1;
      FOpid_control_DW.y1 = FOpid_control_B.x[8];

      /* End of MATLAB Function: '<Root>/MATLAB Function - fopid_yaw' */

      /* Gain: '<Root>/Gain-roll_sp' */
      FOpid_control_B.Gain2 = -FOpid_control_B.u;

      /* Saturate: '<Root>/Saturation_roll_sp' */
      if (FOpid_control_B.Gain2 > 0.1) {
        /* Saturate: '<Root>/Saturation_roll_sp' */
        FOpid_control_B.Saturation_roll_sp = 0.1;
      } else if (FOpid_control_B.Gain2 < -0.1) {
        /* Saturate: '<Root>/Saturation_roll_sp' */
        FOpid_control_B.Saturation_roll_sp = -0.1;
      } else {
        /* Saturate: '<Root>/Saturation_roll_sp' */
        FOpid_control_B.Saturation_roll_sp = FOpid_control_B.Gain2;
      }

      /* End of Saturate: '<Root>/Saturation_roll_sp' */
    }

    /* Sum: '<Root>/Sum4' */
    FOpid_control_B.Sum4 = FOpid_control_B.Saturation_roll_sp -
      FOpid_control_B.x[6];
    if (tmp_0) {
      /* MATLAB Function: '<Root>/MATLAB Function - fopid_roll' incorporates:
       *  Constant: '<Root>/Constant1'
       *  Constant: '<Root>/Constant2'
       */
      FOpid_control_B.u_d = ((((((((FOpid_control_DW.y1_fg - 2.0 *
        FOpid_control_DW.y2_a) + FOpid_control_DW.y3_m) * -1.8 +
        ((FOpid_control_B.x[6] - 2.0 * FOpid_control_DW.y1_fg) +
         FOpid_control_DW.y2_a)) + ((FOpid_control_DW.y2_a - 2.0 *
        FOpid_control_DW.y3_m) + FOpid_control_DW.y4_c) * 1.62) +
        ((FOpid_control_DW.y3_m - 2.0 * FOpid_control_DW.y4_c) +
         FOpid_control_DW.y5_n) * -1.572) + ((FOpid_control_DW.y4_c - 2.0 *
        FOpid_control_DW.y5_n) + FOpid_control_DW.y6_lk) * 1.5174) +
        ((FOpid_control_DW.y5_n - 2.0 * FOpid_control_DW.y6_lk) +
         FOpid_control_DW.y7_g) * -1.489464) * -0.0 + (FOpid_control_DW.u_prev_l
        - (FOpid_control_B.Sum4 - FOpid_control_DW.e1_p))) + (((((((2.0 *
        FOpid_control_DW.e2_g + FOpid_control_DW.e1_p) + FOpid_control_DW.e3_p) *
        -0.6000000000000001 + ((2.0 * FOpid_control_DW.e1_p +
        FOpid_control_B.Sum4) + FOpid_control_DW.e2_g)) + ((2.0 *
        FOpid_control_DW.e3_p + FOpid_control_DW.e2_g) + FOpid_control_DW.e4_l) *
        0.18000000000000005) + ((2.0 * FOpid_control_DW.e4_l +
        FOpid_control_DW.e3_p) + FOpid_control_DW.e5_f) * -0.23600000000000004)
        + ((2.0 * FOpid_control_DW.e5_f + FOpid_control_DW.e4_l) +
           FOpid_control_DW.e6_m) * 0.12540000000000004) + ((2.0 *
        FOpid_control_DW.e6_m + FOpid_control_DW.e5_f) + FOpid_control_DW.e7_j) *
        -0.15664800000000004) * -0.012253256951027941;
      if (!(FOpid_control_B.u_d <= 0.1)) {
        FOpid_control_B.u_d = 0.1;
      }

      if (!(FOpid_control_B.u_d >= -0.1)) {
        FOpid_control_B.u_d = -0.1;
      }

      FOpid_control_DW.u_prev_l = FOpid_control_B.u_d;
      FOpid_control_DW.e7_j = FOpid_control_DW.e6_m;
      FOpid_control_DW.e6_m = FOpid_control_DW.e5_f;
      FOpid_control_DW.e5_f = FOpid_control_DW.e4_l;
      FOpid_control_DW.e4_l = FOpid_control_DW.e3_p;
      FOpid_control_DW.e3_p = FOpid_control_DW.e2_g;
      FOpid_control_DW.e2_g = FOpid_control_DW.e1_p;
      FOpid_control_DW.e1_p = FOpid_control_B.Sum4;
      FOpid_control_DW.y7_g = FOpid_control_DW.y6_lk;
      FOpid_control_DW.y6_lk = FOpid_control_DW.y5_n;
      FOpid_control_DW.y5_n = FOpid_control_DW.y4_c;
      FOpid_control_DW.y4_c = FOpid_control_DW.y3_m;
      FOpid_control_DW.y3_m = FOpid_control_DW.y2_a;
      FOpid_control_DW.y2_a = FOpid_control_DW.y1_fg;
      FOpid_control_DW.y1_fg = FOpid_control_B.x[6];

      /* End of MATLAB Function: '<Root>/MATLAB Function - fopid_roll' */

      /* Gain: '<Root>/Gain2' */
      FOpid_control_B.Gain2 = -FOpid_control_B.u_d;

      /* RateLimiter: '<Root>/Rate Limiter-theta_sp' */
      FOpid_control_B.rtb_CoordinateTransformation_bs = FOpid_control_B.u_l -
        FOpid_control_DW.PrevY;
      if (FOpid_control_B.rtb_CoordinateTransformation_bs > 0.004) {
        /* RateLimiter: '<Root>/Rate Limiter-theta_sp' */
        FOpid_control_B.RateLimitertheta_sp = FOpid_control_DW.PrevY + 0.004;
      } else if (FOpid_control_B.rtb_CoordinateTransformation_bs < -0.004) {
        /* RateLimiter: '<Root>/Rate Limiter-theta_sp' */
        FOpid_control_B.RateLimitertheta_sp = FOpid_control_DW.PrevY - 0.004;
      } else {
        /* RateLimiter: '<Root>/Rate Limiter-theta_sp' */
        FOpid_control_B.RateLimitertheta_sp = FOpid_control_B.u_l;
      }

      FOpid_control_DW.PrevY = FOpid_control_B.RateLimitertheta_sp;

      /* End of RateLimiter: '<Root>/Rate Limiter-theta_sp' */
    }

    /* Sum: '<Root>/Sum1' */
    FOpid_control_B.Sum1 = FOpid_control_B.RateLimitertheta_sp -
      FOpid_control_B.x[7];
    if (tmp_0) {
      /* MATLAB Function: '<Root>/MATLAB Function - fopid_pitch' incorporates:
       *  Constant: '<Root>/Constant6'
       *  Constant: '<Root>/Constant7'
       *  Constant: '<Root>/Constant8'
       */
      FOpid_control_B.u_o = ((((((((FOpid_control_DW.y1_j - 2.0 *
        FOpid_control_DW.y2_g) + FOpid_control_DW.y3_a) * -1.8 +
        ((FOpid_control_B.x[7] - 2.0 * FOpid_control_DW.y1_j) +
         FOpid_control_DW.y2_g)) + ((FOpid_control_DW.y2_g - 2.0 *
        FOpid_control_DW.y3_a) + FOpid_control_DW.y4_h) * 1.62) +
        ((FOpid_control_DW.y3_a - 2.0 * FOpid_control_DW.y4_h) +
         FOpid_control_DW.y5_c) * -1.572) + ((FOpid_control_DW.y4_h - 2.0 *
        FOpid_control_DW.y5_c) + FOpid_control_DW.y6_k) * 1.5174) +
        ((FOpid_control_DW.y5_c - 2.0 * FOpid_control_DW.y6_k) +
         FOpid_control_DW.y7_l) * -1.489464) * -1.1773992067262726 +
        ((FOpid_control_B.Sum1 - FOpid_control_DW.e1_g) * -0.7 +
         FOpid_control_DW.u_prev_lm)) + (((((((2.0 * FOpid_control_DW.e2_o +
        FOpid_control_DW.e1_g) + FOpid_control_DW.e3_m) * -0.8 + ((2.0 *
        FOpid_control_DW.e1_g + FOpid_control_B.Sum1) + FOpid_control_DW.e2_o))
        + ((2.0 * FOpid_control_DW.e3_m + FOpid_control_DW.e2_o) +
           FOpid_control_DW.e4_e) * 0.32000000000000006) + ((2.0 *
        FOpid_control_DW.e4_e + FOpid_control_DW.e3_m) + FOpid_control_DW.e5_o) *
        -0.35200000000000004) + ((2.0 * FOpid_control_DW.e5_o +
        FOpid_control_DW.e4_e) + FOpid_control_DW.e6_d) * 0.23040000000000005) +
        ((2.0 * FOpid_control_DW.e6_d + FOpid_control_DW.e5_o) +
         FOpid_control_DW.e7_p) * -0.24806400000000003) * -0.003330229480810401;
      if (!(FOpid_control_B.u_o <= 0.1)) {
        FOpid_control_B.u_o = 0.1;
      }

      if (!(FOpid_control_B.u_o >= -0.1)) {
        FOpid_control_B.u_o = -0.1;
      }

      FOpid_control_DW.u_prev_lm = FOpid_control_B.u_o;
      FOpid_control_DW.e7_p = FOpid_control_DW.e6_d;
      FOpid_control_DW.e6_d = FOpid_control_DW.e5_o;
      FOpid_control_DW.e5_o = FOpid_control_DW.e4_e;
      FOpid_control_DW.e4_e = FOpid_control_DW.e3_m;
      FOpid_control_DW.e3_m = FOpid_control_DW.e2_o;
      FOpid_control_DW.e2_o = FOpid_control_DW.e1_g;
      FOpid_control_DW.e1_g = FOpid_control_B.Sum1;
      FOpid_control_DW.y7_l = FOpid_control_DW.y6_k;
      FOpid_control_DW.y6_k = FOpid_control_DW.y5_c;
      FOpid_control_DW.y5_c = FOpid_control_DW.y4_h;
      FOpid_control_DW.y4_h = FOpid_control_DW.y3_a;
      FOpid_control_DW.y3_a = FOpid_control_DW.y2_g;
      FOpid_control_DW.y2_g = FOpid_control_DW.y1_j;
      FOpid_control_DW.y1_j = FOpid_control_B.x[7];

      /* End of MATLAB Function: '<Root>/MATLAB Function - fopid_pitch' */

      /* Gain: '<Root>/Gain3' */
      FOpid_control_B.Gain3_o = -FOpid_control_B.u_o;

      /* Gain: '<Root>/Gain4' */
      FOpid_control_B.WhiteNoise_p = -FOpid_control_B.u;
    }

    /* Sum: '<Root>/Sum3' incorporates:
     *  Constant: '<Root>/Constant_U'
     */
    FOpid_control_B.Sum3 = 20.0 - FOpid_control_B.x[0];
    if (tmp_0) {
      /* MATLAB Function: '<Root>/MATLAB Function - fopid_velocidad' incorporates:
       *  Constant: '<Root>/Constant12'
       *  Constant: '<Root>/Constant13'
       *  Constant: '<Root>/Constant14'
       */
      FOpid_control_B.u_b = ((((((((FOpid_control_B.x[0] - 2.0 *
        FOpid_control_DW.y1_f) + FOpid_control_DW.y2_h) -
        ((FOpid_control_DW.y1_f - 2.0 * FOpid_control_DW.y2_h) +
         FOpid_control_DW.y3_d)) + ((FOpid_control_DW.y2_h - 2.0 *
        FOpid_control_DW.y3_d) + FOpid_control_DW.y4_f) * 0.5) +
        ((FOpid_control_DW.y3_d - 2.0 * FOpid_control_DW.y4_f) +
         FOpid_control_DW.y5_k) * -0.5) + ((FOpid_control_DW.y4_f - 2.0 *
        FOpid_control_DW.y5_k) + FOpid_control_DW.y6_l) * 0.375) +
        ((FOpid_control_DW.y5_k - 2.0 * FOpid_control_DW.y6_l) +
         FOpid_control_DW.y7_m) * -0.375) * 0.0 + ((FOpid_control_B.Sum3 -
        FOpid_control_DW.e1_o) * 2.0 + FOpid_control_DW.u_prev_g)) + (((((((2.0 *
        FOpid_control_DW.e2_k + FOpid_control_DW.e1_o) + FOpid_control_DW.e3_i) *
        -0.6000000000000001 + ((2.0 * FOpid_control_DW.e1_o +
        FOpid_control_B.Sum3) + FOpid_control_DW.e2_k)) + ((2.0 *
        FOpid_control_DW.e3_i + FOpid_control_DW.e2_k) + FOpid_control_DW.e4_m) *
        0.18000000000000005) + ((2.0 * FOpid_control_DW.e4_m +
        FOpid_control_DW.e3_i) + FOpid_control_DW.e5_m) * -0.23600000000000004)
        + ((2.0 * FOpid_control_DW.e5_m + FOpid_control_DW.e4_m) +
           FOpid_control_DW.e6_n) * 0.12540000000000004) + ((2.0 *
        FOpid_control_DW.e6_n + FOpid_control_DW.e5_m) + FOpid_control_DW.e7_b) *
        -0.15664800000000004) * 0.024506513902055882;
      if (!(FOpid_control_B.u_b <= 0.8)) {
        FOpid_control_B.u_b = 0.8;
      }

      if (!(FOpid_control_B.u_b >= 0.0)) {
        FOpid_control_B.u_b = 0.0;
      }

      FOpid_control_DW.u_prev_g = FOpid_control_B.u_b;
      FOpid_control_DW.e7_b = FOpid_control_DW.e6_n;
      FOpid_control_DW.e6_n = FOpid_control_DW.e5_m;
      FOpid_control_DW.e5_m = FOpid_control_DW.e4_m;
      FOpid_control_DW.e4_m = FOpid_control_DW.e3_i;
      FOpid_control_DW.e3_i = FOpid_control_DW.e2_k;
      FOpid_control_DW.e2_k = FOpid_control_DW.e1_o;
      FOpid_control_DW.e1_o = FOpid_control_B.Sum3;
      FOpid_control_DW.y7_m = FOpid_control_DW.y6_l;
      FOpid_control_DW.y6_l = FOpid_control_DW.y5_k;
      FOpid_control_DW.y5_k = FOpid_control_DW.y4_f;
      FOpid_control_DW.y4_f = FOpid_control_DW.y3_d;
      FOpid_control_DW.y3_d = FOpid_control_DW.y2_h;
      FOpid_control_DW.y2_h = FOpid_control_DW.y1_f;
      FOpid_control_DW.y1_f = FOpid_control_B.x[0];

      /* End of MATLAB Function: '<Root>/MATLAB Function - fopid_velocidad' */
      /* MATLAB Function: '<Root>/MATLAB Function' */
      memset(&FOpid_control_B.stringOut_b[0], 0, sizeof(uint8_T) << 7U);
      for (i = 0; i < 11; i++) {
        FOpid_control_B.stringOut_b[i] = b_1[i];
      }

      FOpid_control_B.lengthOut_l = 11U;

      /* End of MATLAB Function: '<Root>/MATLAB Function' */

      /* MATLAB Function: '<Root>/MATLAB Function-MODELO' */
      memset(&FOpid_control_B.stringOut[0], 0, sizeof(uint8_T) << 7U);
      for (i = 0; i < 5; i++) {
        FOpid_control_B.stringOut[i] = b_0[i];
      }

      FOpid_control_B.lengthOut = 5U;

      /* End of MATLAB Function: '<Root>/MATLAB Function-MODELO' */
    }

    /* BusAssignment: '<Root>/Bus Assignment-MODELO' incorporates:
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_gazebo'
     */
    memset(&FOpid_control_B.BusAssignmentMODELO, 0, sizeof
           (SL_Bus_gazebo_msgs_SetEntityStateRequest));
    FOpid_control_B.BusAssignmentMODELO.state.name_SL_Info.CurrentLength =
      FOpid_control_B.lengthOut_l;
    FOpid_control_B.BusAssignmentMODELO.state.pose.position.x =
      -FOpid_control_B.x[10];
    FOpid_control_B.BusAssignmentMODELO.state.pose.position.y =
      FOpid_control_B.x[9];
    FOpid_control_B.BusAssignmentMODELO.state.pose.position.z =
      FOpid_control_B.GainZ;
    FOpid_control_B.BusAssignmentMODELO.state.pose.orientation.w =
      FOpid_control_B.sinc;
    FOpid_control_B.BusAssignmentMODELO.state.pose.orientation.z =
      FOpid_control_B.cosa;
    FOpid_control_B.BusAssignmentMODELO.state.pose.orientation.y =
      FOpid_control_B.sina;
    FOpid_control_B.BusAssignmentMODELO.state.pose.orientation.x =
      FOpid_control_B.sinb;
    memcpy(&FOpid_control_B.BusAssignmentMODELO.state.name[0],
           &FOpid_control_B.stringOut_b[0], sizeof(uint8_T) << 7U);
    memcpy(&FOpid_control_B.BusAssignmentMODELO.state.reference_frame[0],
           &FOpid_control_B.stringOut[0], sizeof(uint8_T) << 7U);
    FOpid_control_B.BusAssignmentMODELO.state.reference_frame_SL_Info.CurrentLength
      = FOpid_control_B.lengthOut;

    /* Outputs for Atomic SubSystem: '<Root>/Call Service' */
    /* MATLABSystem: '<S6>/ServiceCaller' */
    serverAvailableOnTime = ServCall_FOpid_control_326.waitForServer(5.0);
    if (serverAvailableOnTime) {
      ServCall_FOpid_control_326.call(&FOpid_control_B.BusAssignmentMODELO, &tmp);
    }

    /* End of MATLABSystem: '<S6>/ServiceCaller' */
    /* End of Outputs for SubSystem: '<Root>/Call Service' */

    /* UnitConversion: '<S50>/Unit Conversion' */
    /* Unit Conversion - from: m to: ft
       Expression: output = (3.28084*input) + (0) */
    FOpid_control_B.Gain2 = 3.280839895013123 * FOpid_control_B.x[11];
    if (tmp_0) {
      /* Memory: '<S35>/Memory' */
      FOpid_control_B.Memory[0] = FOpid_control_DW.Memory_PreviousInput[0];

      /* Memory: '<S35>/Memory1' */
      FOpid_control_B.Memory1[0] = FOpid_control_DW.Memory1_PreviousInput[0];

      /* Memory: '<S35>/Memory' */
      FOpid_control_B.Memory[1] = FOpid_control_DW.Memory_PreviousInput[1];

      /* Memory: '<S35>/Memory1' */
      FOpid_control_B.Memory1[1] = FOpid_control_DW.Memory1_PreviousInput[1];

      /* Memory: '<S35>/Memory' */
      FOpid_control_B.Memory[2] = FOpid_control_DW.Memory_PreviousInput[2];

      /* Memory: '<S35>/Memory1' */
      FOpid_control_B.Memory1[2] = FOpid_control_DW.Memory1_PreviousInput[2];
    }

    /* MATLAB Function: '<S35>/MATLAB Function - MODEL' incorporates:
     *  Memory: '<S35>/Memory'
     *  SignalConversion generated from: '<S41>/ SFunction '
     */
    if (FOpid_control_B.u_d <= 0.3490658503988659) {
      FOpid_control_B.u1 = FOpid_control_B.u_d;
    } else {
      FOpid_control_B.u1 = 0.3490658503988659;
    }

    if (!(FOpid_control_B.u1 >= -0.3490658503988659)) {
      FOpid_control_B.u1 = -0.3490658503988659;
    }

    if (FOpid_control_B.u_o <= 0.3490658503988659) {
      FOpid_control_B.u2 = FOpid_control_B.u_o;
    } else {
      FOpid_control_B.u2 = 0.3490658503988659;
    }

    if (!(FOpid_control_B.u2 >= -0.3490658503988659)) {
      FOpid_control_B.u2 = -0.3490658503988659;
    }

    tmp_1 = _mm_add_pd(_mm_loadu_pd(&FOpid_control_B.x[0]), _mm_loadu_pd
                       (&FOpid_control_B.Memory[0]));
    _mm_storeu_pd(&FOpid_control_B.dv1[0], tmp_1);

    /* MATLAB Function: '<S35>/MATLAB Function - MODEL' incorporates:
     *  Memory: '<S35>/Memory'
     *  Memory: '<S35>/Memory1'
     *  SignalConversion generated from: '<S41>/ SFunction '
     */
    FOpid_control_B.Gain3_o = FOpid_control_B.x[2] + FOpid_control_B.Memory[2];
    FOpid_control_B.u_l = sqrt((FOpid_control_B.dv1[0] * FOpid_control_B.dv1[0]
      + FOpid_control_B.dv1[1] * FOpid_control_B.dv1[1]) +
      FOpid_control_B.Gain3_o * FOpid_control_B.Gain3_o);
    if (FOpid_control_B.u_l < 0.5) {
      FOpid_control_B.u_l = 0.5;
      FOpid_control_B.Gain3_o = 0.0;
      FOpid_control_B.WhiteNoise_p = 0.0;
    } else {
      FOpid_control_B.Gain3_o = rt_atan2d_snf(FOpid_control_B.Gain3_o,
        FOpid_control_B.dv1[0]);
      FOpid_control_B.WhiteNoise_p = FOpid_control_B.dv1[1] /
        FOpid_control_B.u_l;
      if ((FOpid_control_B.WhiteNoise_p >= 1.0) || rtIsNaN
          (FOpid_control_B.WhiteNoise_p)) {
        FOpid_control_B.WhiteNoise_p = 1.0;
      }

      if (FOpid_control_B.WhiteNoise_p <= -1.0) {
        FOpid_control_B.WhiteNoise_p = -1.0;
      }

      FOpid_control_B.WhiteNoise_p = asin(FOpid_control_B.WhiteNoise_p);
    }

    FOpid_control_B.q_aero = FOpid_control_B.Memory1[1] + FOpid_control_B.x[4];
    if ((-FOpid_control_B.x[11] - 0.0505 <= 0.001) || rtIsNaN
        (-FOpid_control_B.x[11] - 0.0505)) {
      FOpid_control_B.rtb_CoordinateTransformation_bs = 0.001;
    } else {
      FOpid_control_B.rtb_CoordinateTransformation_bs = -FOpid_control_B.x[11] -
        0.0505;
    }

    if ((-FOpid_control_B.x[11] + 0.3475 <= 0.001) || rtIsNaN
        (-FOpid_control_B.x[11] + 0.3475)) {
      FOpid_control_B.sina = 0.001;
    } else {
      FOpid_control_B.sina = -FOpid_control_B.x[11] + 0.3475;
    }

    FOpid_control_B.Q = FOpid_control_B.u_l * FOpid_control_B.u_l * 0.6125;
    FOpid_control_B.wbe_b[0] = FOpid_control_B.x[3];
    FOpid_control_B.wbe_b[1] = FOpid_control_B.x[4];
    FOpid_control_B.wbe_b[2] = FOpid_control_B.x[5];
    FOpid_control_B.Vd1 = FOpid_control_B.rtb_CoordinateTransformation_bs /
      0.6977;
    FOpid_control_B.sinc = FOpid_control_B.sina / 0.3808;
    FOpid_control_B.sina = ((FOpid_control_B.Gain3_o - -0.06544984694978735) +
      0.02617993877991494) * 4.960409453036515;
    FOpid_control_B.rtb_CoordinateTransformation_bs = (((FOpid_control_B.Gain3_o
      - -0.04363323129985824) + 0.008726646259971648) - (0.56 /
      FOpid_control_B.u_l * 0.35 * FOpid_control_B.q_aero +
      (FOpid_control_B.Gain3_o - -0.06544984694978735) * 0.35)) *
      4.838774891736003;
    FOpid_control_B.rtb_CoordinateTransformationC_n = (rt_powd_snf
      (FOpid_control_B.Vd1, 0.787) * 288.0 * exp(rt_powd_snf(FOpid_control_B.Vd1,
      0.327) * -9.14) * 0.9798630886207249 / 5.912947654095886 + 1.0) *
      FOpid_control_B.sina;
    FOpid_control_B.rtb_CoordinateTransformationC_b = (rt_powd_snf
      (FOpid_control_B.sinc, 0.787) * 288.0 * exp(rt_powd_snf
      (FOpid_control_B.sinc, 0.327) * -9.14) * 0.9562859020012823 /
      5.35300902982722 + 1.0) * FOpid_control_B.rtb_CoordinateTransformation_bs;
    FOpid_control_B.sinb = ((1.0 - exp(rt_powd_snf(FOpid_control_B.Vd1, 0.814) *
      -4.74) * 0.9791664172678959) - exp(rt_powd_snf(FOpid_control_B.Vd1, 0.758)
      * -3.88) * (FOpid_control_B.Vd1 * FOpid_control_B.Vd1)) *
      (FOpid_control_B.rtb_CoordinateTransformationC_n *
       FOpid_control_B.rtb_CoordinateTransformationC_n / 21.205750411731103);
    FOpid_control_B.sinc = ((1.0 - exp(rt_powd_snf(FOpid_control_B.sinc, 0.814) *
      -4.74) * 0.9677063475148586) - exp(rt_powd_snf(FOpid_control_B.sinc, 0.758)
      * -3.88) * (FOpid_control_B.sinc * FOpid_control_B.sinc)) *
      (FOpid_control_B.rtb_CoordinateTransformationC_b *
       FOpid_control_B.rtb_CoordinateTransformationC_b / 18.943803701146454);
    FOpid_control_B.cosa = FOpid_control_B.u2 * 180.0 / 3.141592653589793;
    FOpid_control_B.cosa = ((FOpid_control_B.cosa * FOpid_control_B.cosa *
      -1.08E-5 + 0.000715 * FOpid_control_B.cosa) * 0.02164 +
      ((FOpid_control_B.sinb * 0.0649 + 0.0027258) + FOpid_control_B.sinc *
       0.02164)) * FOpid_control_B.Q;
    FOpid_control_B.cosb = (FOpid_control_B.rtb_CoordinateTransformationC_n *
      0.0649 + FOpid_control_B.rtb_CoordinateTransformationC_b * 0.02164) *
      FOpid_control_B.Q;
    FOpid_control_B.cosc = -0.019 * FOpid_control_B.WhiteNoise_p * 180.0 /
      3.141592653589793;
    FOpid_control_B.FA_b_idx_0 = sin(FOpid_control_B.Gain3_o);
    FOpid_control_B.FA_b_idx_1 = cos(FOpid_control_B.Gain3_o);
    FOpid_control_B.R[0] = FOpid_control_B.FA_b_idx_1;
    FOpid_control_B.R[3] = 0.0;
    FOpid_control_B.R[6] = -FOpid_control_B.FA_b_idx_0;
    FOpid_control_B.R[2] = FOpid_control_B.FA_b_idx_0;
    FOpid_control_B.R[5] = 0.0;
    FOpid_control_B.R[8] = FOpid_control_B.FA_b_idx_1;
    FOpid_control_B.Dtot[0] = -FOpid_control_B.cosa;
    FOpid_control_B.Dtot[1] = FOpid_control_B.cosc * FOpid_control_B.Q * 0.0649;
    FOpid_control_B.Dtot[2] = -FOpid_control_B.cosb;
    FOpid_control_B.R[1] = 0.0;
    FOpid_control_B.FA_b_idx_0 = 0.0;
    FOpid_control_B.R[4] = 1.0;
    FOpid_control_B.FA_b_idx_1 = 0.0;
    FOpid_control_B.R[7] = 0.0;
    FOpid_control_B.FA_b_idx_2 = 0.0;
    for (i = 0; i < 3; i++) {
      tmp_1 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&FOpid_control_B.R[3 * i]),
        _mm_set1_pd(FOpid_control_B.Dtot[i])), _mm_set_pd
                         (FOpid_control_B.FA_b_idx_1, FOpid_control_B.FA_b_idx_0));
      _mm_storeu_pd(&FOpid_control_B.dv1[0], tmp_1);
      FOpid_control_B.FA_b_idx_0 = FOpid_control_B.dv1[0];
      FOpid_control_B.FA_b_idx_1 = FOpid_control_B.dv1[1];
      FOpid_control_B.FA_b_idx_2 += FOpid_control_B.R[3 * i + 2] *
        FOpid_control_B.Dtot[i];
    }

    FOpid_control_B.Fg_b_idx_2 = 2.0 * FOpid_control_B.u_l;
    FOpid_control_B.Cl = ((FOpid_control_B.Memory1[0] + FOpid_control_B.x[3]) *
                          0.6977 / FOpid_control_B.Fg_b_idx_2 * -2.0 + -0.12 *
                          FOpid_control_B.WhiteNoise_p) + -0.5 *
      FOpid_control_B.u1;
    FOpid_control_B.u2 = ((exp(FOpid_control_B.Vd1 * -4.0) * -0.05 + -1.14 *
      FOpid_control_B.Gain3_o) + FOpid_control_B.q_aero * 0.093 /
                          FOpid_control_B.Fg_b_idx_2 * -5.0) + -3.0 *
      FOpid_control_B.u2;
    if (FOpid_control_B.u <= 0.2617993877991494) {
      FOpid_control_B.q_aero = FOpid_control_B.u;
    } else {
      FOpid_control_B.q_aero = 0.2617993877991494;
    }

    if (!(FOpid_control_B.q_aero >= -0.2617993877991494)) {
      FOpid_control_B.q_aero = -0.2617993877991494;
    }

    FOpid_control_B.u1 = (((FOpid_control_B.Memory1[2] + FOpid_control_B.x[5]) *
      0.6977 / FOpid_control_B.Fg_b_idx_2 * -1.5 + -0.1146 *
      FOpid_control_B.WhiteNoise_p) + -0.3 * FOpid_control_B.q_aero) + -0.05 *
      FOpid_control_B.u1;
    if (FOpid_control_B.u_b <= 1.0) {
      FOpid_control_B.q_aero = FOpid_control_B.u_b;
    } else {
      FOpid_control_B.q_aero = 1.0;
    }

    if (!(FOpid_control_B.q_aero >= 0.0)) {
      FOpid_control_B.q_aero = 0.0;
    }

    FOpid_control_B.Vd1 = (32.0 - FOpid_control_B.u_l) * FOpid_control_B.q_aero
      + FOpid_control_B.u_l;
    if (FOpid_control_B.u_b <= 1.0) {
      FOpid_control_B.q_aero = FOpid_control_B.u_b;
    } else {
      FOpid_control_B.q_aero = 1.0;
    }

    if (!(FOpid_control_B.q_aero >= 0.0)) {
      FOpid_control_B.q_aero = 0.0;
    }

    FOpid_control_B.q_aero = (32.0 - FOpid_control_B.u_l) *
      FOpid_control_B.q_aero + FOpid_control_B.u_l;
    FOpid_control_B.Vd1 = 0.004422606215997847 * FOpid_control_B.Vd1 *
      (FOpid_control_B.Vd1 - FOpid_control_B.u_l);
    FOpid_control_B.q_aero = 0.004422606215997847 * FOpid_control_B.q_aero *
      (FOpid_control_B.q_aero - FOpid_control_B.u_l);
    FOpid_control_B.FE1_b[0] = FOpid_control_B.Vd1 * 0.9961946980917455;
    FOpid_control_B.FE1_b[2] = -FOpid_control_B.Vd1 * 0.08715574274765817;
    FOpid_control_B.FE2_b_idx_0 = FOpid_control_B.q_aero * 0.9961946980917455;
    FOpid_control_B.FE2_b_idx_2 = -FOpid_control_B.q_aero * 0.08715574274765817;
    FOpid_control_B.q_aero = -9.81 * sin(FOpid_control_B.x[7]) * 1.2;
    _mm_storeu_pd(&FOpid_control_B.dv1[0], _mm_mul_pd(_mm_mul_pd(_mm_mul_pd
      (_mm_set1_pd(9.81), _mm_set1_pd(cos(FOpid_control_B.x[7]))), _mm_set_pd
      (cos(FOpid_control_B.x[6]), sin(FOpid_control_B.x[6]))), _mm_set1_pd(1.2)));
    FOpid_control_B.Vd1 = FOpid_control_B.dv1[0];
    FOpid_control_B.Fg_b_idx_2 = FOpid_control_B.dv1[1];
    FOpid_control_B.FE_b = FOpid_control_B.FE1_b[0] +
      FOpid_control_B.FE2_b_idx_0;
    FOpid_control_B.FE_b_idx_0 = FOpid_control_B.FE_b;
    FOpid_control_B.F_b[0] = (FOpid_control_B.q_aero + FOpid_control_B.FE_b) +
      FOpid_control_B.FA_b_idx_0;
    FOpid_control_B.F_b[1] = FOpid_control_B.dv1[0] + FOpid_control_B.FA_b_idx_1;
    FOpid_control_B.FE_b = FOpid_control_B.FE1_b[2] +
      FOpid_control_B.FE2_b_idx_2;
    FOpid_control_B.F_b[2] = (FOpid_control_B.dv1[1] + FOpid_control_B.FE_b) +
      FOpid_control_B.FA_b_idx_2;
    FOpid_control_B.L_dec = 0.6977 * FOpid_control_B.Q * 0.0649;
    FOpid_control_B.Mcg_b_idx_0 = (0.0834 * FOpid_control_B.FE1_b[2] + -0.0834 *
      FOpid_control_B.FE2_b_idx_2) + FOpid_control_B.L_dec * FOpid_control_B.Cl;
    FOpid_control_B.Q = 0.093 * FOpid_control_B.Q * 0.0649 * FOpid_control_B.u2
      + ((-0.0396 * FOpid_control_B.FE1_b[0] - 0.0721 * FOpid_control_B.FE1_b[2])
         + (-0.0396 * FOpid_control_B.FE2_b_idx_0 - 0.0721 *
            FOpid_control_B.FE2_b_idx_2));
    FOpid_control_B.FE2_b_idx_0 = ((0.0 - 0.0834 * FOpid_control_B.FE1_b[0]) +
      (0.0 - -0.0834 * FOpid_control_B.FE2_b_idx_0)) + FOpid_control_B.L_dec *
      FOpid_control_B.u1;
    FOpid_control_B.L_dec = FOpid_control_B.Mcg_b_idx_0 - 0.07841480417423635 *
      FOpid_control_B.FE2_b_idx_0;
    FOpid_control_B.FE2_b_idx_2 = FOpid_control_B.FE2_b_idx_0 -
      0.2258731897286114 * FOpid_control_B.Mcg_b_idx_0;
    memcpy(&FOpid_control_B.R[0], &FOpid_control_B.x[0], 9U * sizeof(real_T));
    FOpid_control_B.FE1_b[0] = FOpid_control_B.R[0];
    FOpid_control_B.FE1_b[1] = FOpid_control_B.R[1];
    FOpid_control_B.FE1_b[2] = FOpid_control_B.R[2];
    FOpid_control_B.c_phi = cos(FOpid_control_B.R[6]);
    FOpid_control_B.s_phi = sin(FOpid_control_B.R[6]);
    FOpid_control_B.c_the = cos(FOpid_control_B.R[7]);
    FOpid_control_B.s_the = sin(FOpid_control_B.R[7]);
    FOpid_control_B.c_psi = cos(FOpid_control_B.R[8]);
    FOpid_control_B.s_psi = sin(FOpid_control_B.R[8]);
    FOpid_control_B.R[0] = FOpid_control_B.c_the * FOpid_control_B.c_psi;
    FOpid_control_B.R_tmp = FOpid_control_B.s_phi * FOpid_control_B.s_the;
    FOpid_control_B.R[3] = FOpid_control_B.R_tmp * FOpid_control_B.c_psi -
      FOpid_control_B.c_phi * FOpid_control_B.s_psi;
    FOpid_control_B.R_tmp_l = FOpid_control_B.c_phi * FOpid_control_B.s_the;
    FOpid_control_B.R[6] = FOpid_control_B.R_tmp_l * FOpid_control_B.c_psi +
      FOpid_control_B.s_phi * FOpid_control_B.s_psi;
    FOpid_control_B.R[1] = FOpid_control_B.c_the * FOpid_control_B.s_psi;
    FOpid_control_B.R[4] = FOpid_control_B.R_tmp * FOpid_control_B.s_psi +
      FOpid_control_B.c_phi * FOpid_control_B.c_psi;
    FOpid_control_B.R[7] = FOpid_control_B.R_tmp_l * FOpid_control_B.s_psi -
      FOpid_control_B.s_phi * FOpid_control_B.c_psi;
    FOpid_control_B.R[2] = -FOpid_control_B.s_the;
    FOpid_control_B.R[5] = FOpid_control_B.s_phi * FOpid_control_B.c_the;
    FOpid_control_B.R[8] = FOpid_control_B.c_phi * FOpid_control_B.c_the;
    tmp_1 = _mm_sub_pd(_mm_mul_pd(_mm_set_pd(FOpid_control_B.x[0],
      FOpid_control_B.x[2]), _mm_loadu_pd(&FOpid_control_B.x[4])), _mm_mul_pd
                       (_mm_loadu_pd(&FOpid_control_B.x[1]), _mm_set_pd
                        (FOpid_control_B.x[3], FOpid_control_B.x[5])));
    _mm_storeu_pd(&FOpid_control_B.Dtot[0], tmp_1);
    FOpid_control_B.Dtot[2] = FOpid_control_B.x[1] * FOpid_control_B.x[3] -
      FOpid_control_B.x[0] * FOpid_control_B.x[4];
    FOpid_control_B.dv[0] = 1.0;
    _mm_storeu_pd(&FOpid_control_B.dv1[0], _mm_mul_pd(_mm_set_pd(cos
      (FOpid_control_B.x[6]), sin(FOpid_control_B.x[6])), _mm_set1_pd(tan
      (FOpid_control_B.x[7]))));
    FOpid_control_B.dv[3] = FOpid_control_B.dv1[0];
    FOpid_control_B.dv[6] = FOpid_control_B.dv1[1];
    FOpid_control_B.dv[1] = 0.0;
    FOpid_control_B.dv[4] = cos(FOpid_control_B.x[6]);
    FOpid_control_B.dv[7] = -sin(FOpid_control_B.x[6]);
    FOpid_control_B.dv[2] = 0.0;
    _mm_storeu_pd(&FOpid_control_B.dv1[0], _mm_div_pd(_mm_set_pd(cos
      (FOpid_control_B.x[6]), sin(FOpid_control_B.x[6])), _mm_set1_pd(cos
      (FOpid_control_B.x[7]))));
    FOpid_control_B.dv[5] = FOpid_control_B.dv1[0];
    FOpid_control_B.dv[8] = FOpid_control_B.dv1[1];
    FOpid_control_B.c_phi = 0.0;
    FOpid_control_B.s_phi = 0.0;
    FOpid_control_B.c_the = 0.0;
    FOpid_control_B.s_the = 0.0;
    FOpid_control_B.c_psi = 0.0;
    FOpid_control_B.s_psi = 0.0;
    for (i = 0; i < 3; i++) {
      tmp_1 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&FOpid_control_B.dv[3 * i]),
        _mm_set1_pd(FOpid_control_B.wbe_b[i])), _mm_set_pd(FOpid_control_B.s_phi,
        FOpid_control_B.c_phi));
      _mm_storeu_pd(&FOpid_control_B.dv1[0], tmp_1);
      FOpid_control_B.c_phi = FOpid_control_B.dv1[0];
      FOpid_control_B.s_phi = FOpid_control_B.dv1[1];
      _mm_storeu_pd(&FOpid_control_B.dv1[0], _mm_add_pd(_mm_mul_pd(_mm_set_pd
        (FOpid_control_B.R[3 * i], FOpid_control_B.dv[3 * i + 2]), _mm_set_pd
        (FOpid_control_B.FE1_b[i], FOpid_control_B.wbe_b[i])), _mm_set_pd
        (FOpid_control_B.s_the, FOpid_control_B.c_the)));
      FOpid_control_B.c_the = FOpid_control_B.dv1[0];
      FOpid_control_B.s_the = FOpid_control_B.dv1[1];
      tmp_1 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&FOpid_control_B.R[3 * i + 1]),
        _mm_set1_pd(FOpid_control_B.FE1_b[i])), _mm_set_pd(FOpid_control_B.s_psi,
        FOpid_control_B.c_psi));
      _mm_storeu_pd(&FOpid_control_B.dv1[0], tmp_1);
      FOpid_control_B.c_psi = FOpid_control_B.dv1[0];
      FOpid_control_B.s_psi = FOpid_control_B.dv1[1];
      FOpid_control_B.XDOT[i] = 0.8333333333333334 * FOpid_control_B.F_b[i] -
        FOpid_control_B.Dtot[i];
    }

    FOpid_control_B.XDOT[3] = ((0.023669 * FOpid_control_B.L_dec + 0.001856 *
      FOpid_control_B.FE2_b_idx_2) - (-2.6338496E-5 * FOpid_control_B.x[3] +
      0.000144843342 * FOpid_control_B.x[5]) * FOpid_control_B.x[4]) /
      0.000191043437;
    FOpid_control_B.XDOT[4] = ((FOpid_control_B.Q - -0.015451999999999999 *
      FOpid_control_B.x[3] * FOpid_control_B.x[5]) - (FOpid_control_B.x[3] *
      FOpid_control_B.x[3] - FOpid_control_B.x[5] * FOpid_control_B.x[5]) *
      0.001856) / 0.017695;
    FOpid_control_B.XDOT[5] = ((-2.6338496E-5 * FOpid_control_B.x[5] +
      -7.443598999999999E-5 * FOpid_control_B.x[3]) * FOpid_control_B.x[4] +
      (0.001856 * FOpid_control_B.L_dec + 0.008217 * FOpid_control_B.FE2_b_idx_2))
      / 0.000191043437;
    FOpid_control_B.XDOT[9] = FOpid_control_B.s_the;
    FOpid_control_B.XDOT[10] = FOpid_control_B.c_psi;
    FOpid_control_B.XDOT[11] = FOpid_control_B.s_psi;
    if (!(FOpid_control_B.cosa >= 0.001)) {
      FOpid_control_B.cosa = 0.001;
    }

    FOpid_control_B.XDOT[12] = FOpid_control_B.cosb / FOpid_control_B.cosa;
    FOpid_control_B.XDOT[19] = FOpid_control_B.cosc;
    FOpid_control_B.XDOT[20] = FOpid_control_B.Cl;
    FOpid_control_B.XDOT[21] = FOpid_control_B.u2;
    FOpid_control_B.XDOT[22] = FOpid_control_B.u1;
    FOpid_control_B.XDOT[23] = FOpid_control_B.Gain3_o;
    FOpid_control_B.XDOT[24] = FOpid_control_B.WhiteNoise_p;
    FOpid_control_B.XDOT[25] = FOpid_control_B.sina;
    FOpid_control_B.XDOT[26] = FOpid_control_B.rtb_CoordinateTransformation_bs;
    FOpid_control_B.XDOT[27] = FOpid_control_B.rtb_CoordinateTransformationC_n;
    FOpid_control_B.XDOT[28] = FOpid_control_B.rtb_CoordinateTransformationC_b;
    FOpid_control_B.XDOT[29] = FOpid_control_B.sinb;
    FOpid_control_B.XDOT[30] = FOpid_control_B.sinc;
    FOpid_control_B.XDOT[6] = FOpid_control_B.c_phi;
    FOpid_control_B.XDOT[13] = FOpid_control_B.F_b[0];
    FOpid_control_B.XDOT[16] = FOpid_control_B.Mcg_b_idx_0;
    FOpid_control_B.XDOT[31] = FOpid_control_B.q_aero;
    FOpid_control_B.XDOT[34] = FOpid_control_B.FE_b_idx_0;
    FOpid_control_B.XDOT[37] = FOpid_control_B.FA_b_idx_0;
    FOpid_control_B.XDOT[7] = FOpid_control_B.s_phi;
    FOpid_control_B.XDOT[14] = FOpid_control_B.F_b[1];
    FOpid_control_B.XDOT[17] = FOpid_control_B.Q;
    FOpid_control_B.XDOT[32] = FOpid_control_B.Vd1;
    FOpid_control_B.XDOT[35] = 0.0;
    FOpid_control_B.XDOT[38] = FOpid_control_B.FA_b_idx_1;
    FOpid_control_B.XDOT[8] = FOpid_control_B.c_the;
    FOpid_control_B.XDOT[15] = FOpid_control_B.F_b[2];
    FOpid_control_B.XDOT[18] = FOpid_control_B.FE2_b_idx_0;
    FOpid_control_B.XDOT[33] = FOpid_control_B.Fg_b_idx_2;
    FOpid_control_B.XDOT[36] = FOpid_control_B.FE_b;
    FOpid_control_B.XDOT[39] = FOpid_control_B.FA_b_idx_2;

    /* UnitConversion: '<S56>/Unit Conversion' incorporates:
     *  MATLAB Function: '<S35>/MATLAB Function - MODEL'
     */
    /* Unit Conversion - from: m/s to: ft/s
       Expression: output = (3.28084*input) + (0) */
    FOpid_control_B.u_l *= 3.280839895013123;

    /* Saturate: '<S83>/Limit Function 10ft to 1000ft' incorporates:
     *  Saturate: '<S66>/Limit Height h<1000ft'
     */
    if (FOpid_control_B.Gain2 > 1000.0) {
      FOpid_control_B.Gain3_o = 1000.0;
      FOpid_control_B.WhiteNoise_p = 1000.0;
    } else {
      if (FOpid_control_B.Gain2 < 10.0) {
        FOpid_control_B.Gain3_o = 10.0;
      } else {
        FOpid_control_B.Gain3_o = FOpid_control_B.Gain2;
      }

      if (FOpid_control_B.Gain2 < 0.0) {
        FOpid_control_B.WhiteNoise_p = 0.0;
      } else {
        FOpid_control_B.WhiteNoise_p = FOpid_control_B.Gain2;
      }
    }

    /* End of Saturate: '<S83>/Limit Function 10ft to 1000ft' */

    /* Fcn: '<S83>/Low Altitude Scale Length' */
    FOpid_control_B.rtb_CoordinateTransformation_bs = FOpid_control_B.Gain3_o /
      rt_powd_snf(0.000823 * FOpid_control_B.Gain3_o + 0.177, 1.2);

    /* Product: '<S66>/sigma_ug, sigma_vg' incorporates:
     *  Fcn: '<S66>/Low Altitude Intensity'
     */
    FOpid_control_B.sina = 1.0 / rt_powd_snf(0.000823 *
      FOpid_control_B.WhiteNoise_p + 0.177, 0.4) * FOpid_control_ConstB.sigma_wg;

    /* Interpolation_n-D: '<S65>/Medium//High Altitude Intensity' incorporates:
     *  PreLookup: '<S65>/PreLook-Up Index Search  (altitude)'
     *  PreLookup: '<S65>/PreLook-Up Index Search  (prob of exceed)'
     *  SecondOrderIntegrator: '<S29>/Integrator, Second-Order Limited'
     */
    FOpid_control_B.bpIndex[0] = plook_bincpa(FOpid_control_B.Gain2,
      FOpid_control_ConstP.PreLookUpIndexSearchaltitude_Br, 11U,
      &FOpid_control_B.WhiteNoise_p,
      &FOpid_control_DW.PreLookUpIndexSearchaltitude_DW);
    FOpid_control_B.Lv[0] = FOpid_control_B.WhiteNoise_p;
    FOpid_control_B.Lv[1] = FOpid_control_ConstB.PreLookUpIndexSearchprobofe;
    FOpid_control_B.bpIndex[1] =
      FOpid_control_ConstB.PreLookUpIndexSearchprobo_g;
    FOpid_control_B.WhiteNoise_p = intrp2d_la_pw(FOpid_control_B.bpIndex,
      FOpid_control_B.Lv, FOpid_control_ConstP.MediumHighAltitudeIntensity_Tab,
      12U, FOpid_control_ConstP.MediumHighAltitudeIntensity_max);
    if (tmp_0) {
      /* Product: '<S58>/Divide' incorporates:
       *  Product: '<S58>/Product'
       *  RandomNumber: '<S58>/White Noise'
       */
      tmp_1 = _mm_mul_pd(_mm_loadu_pd(&FOpid_control_ConstB.Divide[0]),
                         _mm_loadu_pd(&FOpid_control_DW.NextOutput[0]));

      /* Product: '<S58>/Product' */
      _mm_storeu_pd(&FOpid_control_B.Product[0], tmp_1);

      /* Product: '<S58>/Divide' incorporates:
       *  Product: '<S58>/Product'
       *  RandomNumber: '<S58>/White Noise'
       */
      tmp_1 = _mm_mul_pd(_mm_loadu_pd(&FOpid_control_ConstB.Divide[2]),
                         _mm_loadu_pd(&FOpid_control_DW.NextOutput[2]));

      /* Product: '<S58>/Product' */
      _mm_storeu_pd(&FOpid_control_B.Product[2], tmp_1);

      /* Outputs for Enabled SubSystem: '<S49>/Hugw(s)' incorporates:
       *  EnablePort: '<S62>/Enable'
       */
      if (rtsiIsModeUpdateTimeStep(&(&FOpid_control_M)->solverInfo) &&
          !FOpid_control_DW.Hugws_MODE) {
        (void) memset(&(FOpid_control_XDis.ug_p_CSTATE), 0,
                      2*sizeof(boolean_T));

        /* InitializeConditions for Integrator: '<S62>/ug_p' */
        FOpid_control_X.ug_p_CSTATE[0] = 0.0;
        FOpid_control_X.ug_p_CSTATE[1] = 0.0;
        FOpid_control_DW.Hugws_MODE = true;
      }

      /* End of Outputs for SubSystem: '<S49>/Hugw(s)' */
    }

    /* Outputs for Enabled SubSystem: '<S49>/Hugw(s)' incorporates:
     *  EnablePort: '<S62>/Enable'
     */
    if (FOpid_control_DW.Hugws_MODE) {
      /* Product: '<S62>/Lug//V' */
      FOpid_control_B.Lv[0] = FOpid_control_B.rtb_CoordinateTransformation_bs /
        FOpid_control_B.u_l;
      FOpid_control_B.Lv[1] = FOpid_control_ConstB.UnitConversion_c /
        FOpid_control_B.u_l;

      /* Sqrt: '<S62>/sqrt' incorporates:
       *  Gain: '<S62>/(2//pi)'
       *  Integrator: '<S62>/ug_p'
       *  Product: '<S62>/Lug//V1'
       */
      tmp_1 = _mm_div_pd(_mm_sub_pd(_mm_mul_pd(_mm_set_pd(sqrt
        (0.6366197723675814 * FOpid_control_B.Lv[1]), sqrt(0.6366197723675814 *
        FOpid_control_B.Lv[0])), _mm_set1_pd(FOpid_control_B.Product[0])),
        _mm_loadu_pd(&FOpid_control_X.ug_p_CSTATE[0])), _mm_loadu_pd
                         (&FOpid_control_B.Lv[0]));

      /* Product: '<S62>/w' */
      _mm_storeu_pd(&FOpid_control_B.w_n[0], tmp_1);

      /* Integrator: '<S62>/ug_p' incorporates:
       *  Product: '<S62>/w1'
       */
      tmp_1 = _mm_mul_pd(_mm_loadu_pd(&FOpid_control_X.ug_p_CSTATE[0]),
                         _mm_set_pd(FOpid_control_B.WhiteNoise_p,
        FOpid_control_B.sina));

      /* Product: '<S62>/w1' */
      _mm_storeu_pd(&FOpid_control_B.w1_c[0], tmp_1);
    }

    /* End of Outputs for SubSystem: '<S49>/Hugw(s)' */

    /* Gain: '<S55>/Lv' */
    FOpid_control_B.Lv[1] = FOpid_control_ConstB.UnitConversion_c;

    /* Outputs for Enabled SubSystem: '<S49>/Hvgw(s)' incorporates:
     *  EnablePort: '<S63>/Enable'
     */
    if (tmp_0 && rtsiIsModeUpdateTimeStep(&(&FOpid_control_M)->solverInfo) &&
        !FOpid_control_DW.Hvgws_MODE) {
      (void) memset(&(FOpid_control_XDis.vg_p1_CSTATE), 0,
                    4*sizeof(boolean_T));

      /* InitializeConditions for Integrator: '<S63>/vg_p1' */
      FOpid_control_X.vg_p1_CSTATE[0] = 0.0;

      /* InitializeConditions for Integrator: '<S63>/vgw_p2' */
      FOpid_control_X.vgw_p2_CSTATE[0] = 0.0;

      /* InitializeConditions for Integrator: '<S63>/vg_p1' */
      FOpid_control_X.vg_p1_CSTATE[1] = 0.0;

      /* InitializeConditions for Integrator: '<S63>/vgw_p2' */
      FOpid_control_X.vgw_p2_CSTATE[1] = 0.0;
      FOpid_control_DW.Hvgws_MODE = true;
    }

    if (FOpid_control_DW.Hvgws_MODE) {
      /* Product: '<S63>/Lvg//V' incorporates:
       *  Gain: '<S55>/Lv'
       */
      FOpid_control_B.rtb_CoordinateTransformation_bs /= FOpid_control_B.u_l;

      /* Product: '<S63>/w' incorporates:
       *  Gain: '<S63>/(1//pi)'
       *  Integrator: '<S63>/vg_p1'
       *  Product: '<S63>/Lug//V1'
       *  Sqrt: '<S63>/sqrt'
       *  Sum: '<S63>/Sum'
       */
      FOpid_control_B.rtb_CoordinateTransformationC_n = (sqrt(0.3183098861837907
        * FOpid_control_B.rtb_CoordinateTransformation_bs) *
        FOpid_control_B.Product[1] - FOpid_control_X.vg_p1_CSTATE[0]) /
        FOpid_control_B.rtb_CoordinateTransformation_bs;
      FOpid_control_B.w_g[0] = FOpid_control_B.rtb_CoordinateTransformationC_n;

      /* Product: '<S63>/w ' incorporates:
       *  Gain: '<S63>/sqrt(3)'
       *  Integrator: '<S63>/vg_p1'
       *  Integrator: '<S63>/vgw_p2'
       *  Product: '<S63>/Lvg//V '
       *  Sum: '<S63>/Sum1'
       */
      FOpid_control_B.w_e[0] = (FOpid_control_B.rtb_CoordinateTransformationC_n *
        FOpid_control_B.rtb_CoordinateTransformation_bs * 1.7320508075688772 +
        (FOpid_control_X.vg_p1_CSTATE[0] - FOpid_control_X.vgw_p2_CSTATE[0])) /
        FOpid_control_B.rtb_CoordinateTransformation_bs;

      /* Product: '<S63>/Lvg//V' */
      FOpid_control_B.rtb_CoordinateTransformation_bs = FOpid_control_B.Lv[1] /
        FOpid_control_B.u_l;

      /* Product: '<S63>/w' incorporates:
       *  Gain: '<S63>/(1//pi)'
       *  Integrator: '<S63>/vg_p1'
       *  Product: '<S63>/Lug//V1'
       *  Sqrt: '<S63>/sqrt'
       *  Sum: '<S63>/Sum'
       */
      FOpid_control_B.rtb_CoordinateTransformationC_n = (sqrt(0.3183098861837907
        * FOpid_control_B.rtb_CoordinateTransformation_bs) *
        FOpid_control_B.Product[1] - FOpid_control_X.vg_p1_CSTATE[1]) /
        FOpid_control_B.rtb_CoordinateTransformation_bs;
      FOpid_control_B.w_g[1] = FOpid_control_B.rtb_CoordinateTransformationC_n;

      /* Product: '<S63>/w ' incorporates:
       *  Gain: '<S63>/sqrt(3)'
       *  Integrator: '<S63>/vg_p1'
       *  Integrator: '<S63>/vgw_p2'
       *  Product: '<S63>/Lvg//V '
       *  Sum: '<S63>/Sum1'
       */
      FOpid_control_B.w_e[1] = (FOpid_control_B.rtb_CoordinateTransformationC_n *
        FOpid_control_B.rtb_CoordinateTransformation_bs * 1.7320508075688772 +
        (FOpid_control_X.vg_p1_CSTATE[1] - FOpid_control_X.vgw_p2_CSTATE[1])) /
        FOpid_control_B.rtb_CoordinateTransformation_bs;

      /* Product: '<S63>/w 1' incorporates:
       *  Integrator: '<S63>/vgw_p2'
       */
      tmp_1 = _mm_mul_pd(_mm_set_pd(FOpid_control_B.WhiteNoise_p,
        FOpid_control_B.sina), _mm_loadu_pd(&FOpid_control_X.vgw_p2_CSTATE[0]));

      /* Product: '<S63>/w 1' */
      _mm_storeu_pd(&FOpid_control_B.w1[0], tmp_1);
    }

    /* End of Outputs for SubSystem: '<S49>/Hvgw(s)' */

    /* Gain: '<S55>/Lw' */
    FOpid_control_B.Lv[1] = FOpid_control_ConstB.UnitConversion_c;

    /* Outputs for Enabled SubSystem: '<S49>/Hwgw(s)' incorporates:
     *  EnablePort: '<S64>/Enable'
     */
    if (tmp_0 && rtsiIsModeUpdateTimeStep(&(&FOpid_control_M)->solverInfo) &&
        !FOpid_control_DW.Hwgws_MODE) {
      (void) memset(&(FOpid_control_XDis.wg_p1_CSTATE), 0,
                    4*sizeof(boolean_T));

      /* InitializeConditions for Integrator: '<S64>/wg_p1' */
      FOpid_control_X.wg_p1_CSTATE[0] = 0.0;

      /* InitializeConditions for Integrator: '<S64>/wg_p2' */
      FOpid_control_X.wg_p2_CSTATE[0] = 0.0;

      /* InitializeConditions for Integrator: '<S64>/wg_p1' */
      FOpid_control_X.wg_p1_CSTATE[1] = 0.0;

      /* InitializeConditions for Integrator: '<S64>/wg_p2' */
      FOpid_control_X.wg_p2_CSTATE[1] = 0.0;
      FOpid_control_DW.Hwgws_MODE = true;
    }

    if (FOpid_control_DW.Hwgws_MODE) {
      /* Product: '<S64>/Lwg//V' incorporates:
       *  Gain: '<S55>/Lw'
       */
      FOpid_control_B.sina = FOpid_control_B.Gain3_o / FOpid_control_B.u_l;

      /* Product: '<S64>/w' incorporates:
       *  Gain: '<S64>/1//pi'
       *  Integrator: '<S64>/wg_p1'
       *  Product: '<S64>/Lug//V1'
       *  Sqrt: '<S64>/sqrt1'
       *  Sum: '<S64>/Sum'
       */
      FOpid_control_B.rtb_CoordinateTransformation_bs = (sqrt(0.3183098861837907
        * FOpid_control_B.sina) * FOpid_control_B.Product[2] -
        FOpid_control_X.wg_p1_CSTATE[0]) / FOpid_control_B.sina;
      FOpid_control_B.w[0] = FOpid_control_B.rtb_CoordinateTransformation_bs;

      /* Product: '<S64>/w ' incorporates:
       *  Integrator: '<S64>/wg_p1'
       *  Integrator: '<S64>/wg_p2'
       *  Product: '<S64>/Lwg//V'
       *  Product: '<S64>/Lwg//V '
       *  Sum: '<S64>/Sum1'
       */
      FOpid_control_B.w_a[0] = (FOpid_control_B.rtb_CoordinateTransformation_bs *
        FOpid_control_ConstB.sqrt_a * FOpid_control_B.sina +
        (FOpid_control_X.wg_p1_CSTATE[0] - FOpid_control_X.wg_p2_CSTATE[0])) /
        FOpid_control_B.sina;

      /* Product: '<S64>/Lwg//V' */
      FOpid_control_B.sina = FOpid_control_B.Lv[1] / FOpid_control_B.u_l;

      /* Product: '<S64>/w' incorporates:
       *  Gain: '<S64>/1//pi'
       *  Integrator: '<S64>/wg_p1'
       *  Product: '<S64>/Lug//V1'
       *  Sqrt: '<S64>/sqrt1'
       *  Sum: '<S64>/Sum'
       */
      FOpid_control_B.rtb_CoordinateTransformation_bs = (sqrt(0.3183098861837907
        * FOpid_control_B.sina) * FOpid_control_B.Product[2] -
        FOpid_control_X.wg_p1_CSTATE[1]) / FOpid_control_B.sina;
      FOpid_control_B.w[1] = FOpid_control_B.rtb_CoordinateTransformation_bs;

      /* Product: '<S64>/w ' incorporates:
       *  Integrator: '<S64>/wg_p1'
       *  Integrator: '<S64>/wg_p2'
       *  Product: '<S64>/Lwg//V'
       *  Product: '<S64>/Lwg//V '
       *  Sum: '<S64>/Sum1'
       */
      FOpid_control_B.w_a[1] = (FOpid_control_B.rtb_CoordinateTransformation_bs *
        FOpid_control_ConstB.sqrt_a * FOpid_control_B.sina +
        (FOpid_control_X.wg_p1_CSTATE[1] - FOpid_control_X.wg_p2_CSTATE[1])) /
        FOpid_control_B.sina;

      /* Product: '<S64>/Lwg//V 1' incorporates:
       *  Integrator: '<S64>/wg_p2'
       */
      tmp_1 = _mm_mul_pd(_mm_set_pd(FOpid_control_B.WhiteNoise_p,
        FOpid_control_ConstB.sigma_wg), _mm_loadu_pd
                         (&FOpid_control_X.wg_p2_CSTATE[0]));

      /* Product: '<S64>/Lwg//V 1' */
      _mm_storeu_pd(&FOpid_control_B.LwgV1[0], tmp_1);
    }

    /* End of Outputs for SubSystem: '<S49>/Hwgw(s)' */

    /* Angle2Dcm: '<S35>/Rotation Angles to Direction Cosine Matrix' */
    FOpid_control_B.sina = cos(FOpid_control_B.x[6]);
    FOpid_control_B.rtb_CoordinateTransformation_bs = sin(FOpid_control_B.x[6]);
    FOpid_control_B.rtb_CoordinateTransformationC_n = -sin(FOpid_control_B.x[6]);
    FOpid_control_B.rtb_CoordinateTransformationC_b = cos(FOpid_control_B.x[6]);
    FOpid_control_B.FA_b_idx_2 = cos(FOpid_control_B.x[7]);
    FOpid_control_B.q_aero = -sin(FOpid_control_B.x[7]);
    FOpid_control_B.sinb = sin(FOpid_control_B.x[7]);
    FOpid_control_B.sinc = cos(FOpid_control_B.x[7]);
    FOpid_control_B.cosa = cos(FOpid_control_B.x[8]);
    FOpid_control_B.cosb = sin(FOpid_control_B.x[8]);
    FOpid_control_B.cosc = -sin(FOpid_control_B.x[8]);
    FOpid_control_B.Cl = cos(FOpid_control_B.x[8]);
    FOpid_control_B.FA_b_idx_0 = 0.0 * FOpid_control_B.sinb +
      FOpid_control_B.FA_b_idx_2;
    FOpid_control_B.FA_b_idx_1 = 0.0 * FOpid_control_B.sinc +
      FOpid_control_B.q_aero;
    FOpid_control_B.u2 = FOpid_control_B.cosa * 0.0;
    FOpid_control_B.u1 = 0.0 * FOpid_control_B.FA_b_idx_2;
    FOpid_control_B.FA_b_idx_2 = (FOpid_control_B.u1 + FOpid_control_B.u2) +
      FOpid_control_B.cosb * FOpid_control_B.sinb;
    FOpid_control_B.cosa += FOpid_control_B.cosb * 0.0;
    FOpid_control_B.q_aero *= 0.0;
    FOpid_control_B.cosb = (FOpid_control_B.q_aero + FOpid_control_B.u2) +
      FOpid_control_B.cosb * FOpid_control_B.sinc;
    FOpid_control_B.u2 = FOpid_control_B.cosc * 0.0;
    FOpid_control_B.sinb = (FOpid_control_B.u1 + FOpid_control_B.u2) +
      FOpid_control_B.sinb * FOpid_control_B.Cl;
    FOpid_control_B.cosc += FOpid_control_B.Cl * 0.0;
    FOpid_control_B.sinc = (FOpid_control_B.q_aero + FOpid_control_B.u2) +
      FOpid_control_B.Cl * FOpid_control_B.sinc;
    FOpid_control_B.Cl = FOpid_control_B.FA_b_idx_1 * 0.0;
    FOpid_control_B.RotationAnglestoDirectionCo[0] = (FOpid_control_B.FA_b_idx_0
      * FOpid_control_B.sina + 0.0 *
      FOpid_control_B.rtb_CoordinateTransformationC_n) + FOpid_control_B.Cl;
    FOpid_control_B.u2 = FOpid_control_B.cosb * 0.0;
    FOpid_control_B.RotationAnglestoDirectionCo[1] = (FOpid_control_B.sina *
      FOpid_control_B.FA_b_idx_2 +
      FOpid_control_B.rtb_CoordinateTransformationC_n * FOpid_control_B.cosa) +
      FOpid_control_B.u2;
    FOpid_control_B.u1 = FOpid_control_B.sinc * 0.0;
    FOpid_control_B.RotationAnglestoDirectionCo[2] = (FOpid_control_B.sina *
      FOpid_control_B.sinb + FOpid_control_B.rtb_CoordinateTransformationC_n *
      FOpid_control_B.cosc) + FOpid_control_B.u1;
    FOpid_control_B.RotationAnglestoDirectionCo[3] = (FOpid_control_B.FA_b_idx_0
      * FOpid_control_B.rtb_CoordinateTransformation_bs + 0.0 *
      FOpid_control_B.rtb_CoordinateTransformationC_b) + FOpid_control_B.Cl;
    FOpid_control_B.RotationAnglestoDirectionCo[4] =
      (FOpid_control_B.rtb_CoordinateTransformation_bs *
       FOpid_control_B.FA_b_idx_2 + FOpid_control_B.cosa *
       FOpid_control_B.rtb_CoordinateTransformationC_b) + FOpid_control_B.u2;
    FOpid_control_B.RotationAnglestoDirectionCo[5] =
      (FOpid_control_B.rtb_CoordinateTransformation_bs * FOpid_control_B.sinb +
       FOpid_control_B.rtb_CoordinateTransformationC_b * FOpid_control_B.cosc) +
      FOpid_control_B.u1;
    FOpid_control_B.RotationAnglestoDirectionCo[6] = FOpid_control_B.FA_b_idx_0 *
      0.0 + FOpid_control_B.FA_b_idx_1;
    FOpid_control_B.RotationAnglestoDirectionCo[7] = (FOpid_control_B.FA_b_idx_2
      * 0.0 + FOpid_control_B.cosa * 0.0) + FOpid_control_B.cosb;
    FOpid_control_B.RotationAnglestoDirectionCo[8] = (FOpid_control_B.sinb * 0.0
      + FOpid_control_B.cosc * 0.0) + FOpid_control_B.sinc;

    /* If: '<S54>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' incorporates:
     *  Constant: '<S75>/max_height_low'
     *  Product: '<S75>/Product1'
     *  Product: '<S80>/Product1'
     *  Product: '<S80>/Product2'
     *  Product: '<S82>/Product1'
     *  Product: '<S82>/Product2'
     *  Sum: '<S75>/Sum1'
     *  Sum: '<S75>/Sum2'
     *  Sum: '<S75>/Sum3'
     *  Sum: '<S80>/Sum'
     *  Sum: '<S82>/Sum'
     */
    rtPrevAction = FOpid_control_DW.ifHeightMaxlowaltitudeelseifHei;
    if (rtsiIsModeUpdateTimeStep(&(&FOpid_control_M)->solverInfo)) {
      if (FOpid_control_B.Gain2 <= 1000.0) {
        rtAction = 0;
      } else if (FOpid_control_B.Gain2 >= 2000.0) {
        rtAction = 1;
      } else {
        rtAction = 2;
      }

      FOpid_control_DW.ifHeightMaxlowaltitudeelseifHei = rtAction;
    } else {
      rtAction = FOpid_control_DW.ifHeightMaxlowaltitudeelseifHei;
    }

    if (rtPrevAction != rtAction) {
      rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
        ->solverInfo, true);
    }

    switch (rtAction) {
     case 0:
      /* Outputs for IfAction SubSystem: '<S54>/Low altitude  velocities' incorporates:
       *  ActionPort: '<S76>/Action Port'
       */
      /* SignalConversion generated from: '<S81>/Vector Concatenate' */
      FOpid_control_B.Product_k[2] = FOpid_control_B.LwgV1[0];

      /* Trigonometry: '<S82>/Trigonometric Function' incorporates:
       *  UnitConversion: '<S47>/Unit Conversion'
       */
      FOpid_control_B.sina = sin(FOpid_control_ConstB.UnitConversion);
      FOpid_control_B.rtb_CoordinateTransformation_bs = cos
        (FOpid_control_ConstB.UnitConversion);
      _mm_storeu_pd(&FOpid_control_B.Product_k[0], _mm_add_pd(_mm_mul_pd
        (_mm_set_pd(FOpid_control_B.sina, FOpid_control_B.w1_c[0]), _mm_set_pd
         (FOpid_control_B.w1_c[0],
          FOpid_control_B.rtb_CoordinateTransformation_bs)), _mm_mul_pd
        (_mm_mul_pd(_mm_set_pd(FOpid_control_B.w1[0], FOpid_control_B.sina),
                    _mm_set_pd(FOpid_control_B.rtb_CoordinateTransformation_bs,
        FOpid_control_B.w1[0])), _mm_set_pd(1.0, -1.0))));

      /* Product: '<S81>/Product' incorporates:
       *  Angle2Dcm: '<S35>/Rotation Angles to Direction Cosine Matrix'
       *  Concatenate: '<S81>/Vector Concatenate'
       *  Product: '<S82>/Product1'
       *  Product: '<S82>/Product2'
       *  Reshape: '<S81>/Reshape1'
       *  Sum: '<S82>/Sum'
       */
      FOpid_control_B.sina = 0.0;
      FOpid_control_B.rtb_CoordinateTransformation_bs = 0.0;
      FOpid_control_B.rtb_CoordinateTransformationC_n = 0.0;
      for (i = 0; i < 3; i++) {
        tmp_1 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
          (&FOpid_control_B.RotationAnglestoDirectionCo[3 * i]), _mm_set1_pd
          (FOpid_control_B.Product_k[i])), _mm_set_pd
                           (FOpid_control_B.rtb_CoordinateTransformation_bs,
                            FOpid_control_B.sina));
        _mm_storeu_pd(&FOpid_control_B.dv1[0], tmp_1);
        FOpid_control_B.sina = FOpid_control_B.dv1[0];
        FOpid_control_B.rtb_CoordinateTransformation_bs = FOpid_control_B.dv1[1];
        FOpid_control_B.rtb_CoordinateTransformationC_n +=
          FOpid_control_B.RotationAnglestoDirectionCo[3 * i + 2] *
          FOpid_control_B.Product_k[i];
      }

      FOpid_control_B.wbe_b[2] = FOpid_control_B.rtb_CoordinateTransformationC_n;
      FOpid_control_B.wbe_b[1] = FOpid_control_B.rtb_CoordinateTransformation_bs;
      FOpid_control_B.wbe_b[0] = FOpid_control_B.sina;

      /* End of Product: '<S81>/Product' */
      /* End of Outputs for SubSystem: '<S54>/Low altitude  velocities' */
      break;

     case 1:
      /* Outputs for IfAction SubSystem: '<S54>/Medium//High  altitude velocities' incorporates:
       *  ActionPort: '<S77>/Action Port'
       */
      /* Gain: '<S77>/Gain' */
      FOpid_control_B.wbe_b[0] = FOpid_control_B.w1_c[1];
      FOpid_control_B.wbe_b[1] = FOpid_control_B.w1[1];
      FOpid_control_B.wbe_b[2] = FOpid_control_B.LwgV1[1];

      /* End of Outputs for SubSystem: '<S54>/Medium//High  altitude velocities' */
      break;

     default:
      /* Outputs for IfAction SubSystem: '<S54>/Interpolate  velocities' incorporates:
       *  ActionPort: '<S75>/Action Port'
       */
      /* Trigonometry: '<S80>/Trigonometric Function' incorporates:
       *  UnitConversion: '<S47>/Unit Conversion'
       */
      FOpid_control_B.sina = sin(FOpid_control_ConstB.UnitConversion);
      FOpid_control_B.rtb_CoordinateTransformation_bs = cos
        (FOpid_control_ConstB.UnitConversion);
      _mm_storeu_pd(&FOpid_control_B.wbe_b[0], _mm_add_pd(_mm_mul_pd(_mm_set_pd
        (FOpid_control_B.sina, FOpid_control_B.w1_c[0]), _mm_set_pd
        (FOpid_control_B.w1_c[0],
         FOpid_control_B.rtb_CoordinateTransformation_bs)), _mm_mul_pd
        (_mm_mul_pd(_mm_set_pd(FOpid_control_B.w1[0], FOpid_control_B.sina),
                    _mm_set_pd(FOpid_control_B.rtb_CoordinateTransformation_bs,
        FOpid_control_B.w1[0])), _mm_set_pd(1.0, -1.0))));

      /* SignalConversion generated from: '<S79>/Vector Concatenate' incorporates:
       *  Product: '<S80>/Product1'
       *  Product: '<S80>/Product2'
       *  Sum: '<S80>/Sum'
       */
      FOpid_control_B.wbe_b[2] = FOpid_control_B.LwgV1[0];

      /* Product: '<S79>/Product' incorporates:
       *  Angle2Dcm: '<S35>/Rotation Angles to Direction Cosine Matrix'
       *  Concatenate: '<S79>/Vector Concatenate'
       */
      FOpid_control_B.sina = 0.0;
      FOpid_control_B.rtb_CoordinateTransformation_bs = 0.0;
      FOpid_control_B.rtb_CoordinateTransformationC_n = 0.0;
      for (i = 0; i < 3; i++) {
        tmp_1 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
          (&FOpid_control_B.RotationAnglestoDirectionCo[3 * i]), _mm_set1_pd
          (FOpid_control_B.wbe_b[i])), _mm_set_pd
                           (FOpid_control_B.rtb_CoordinateTransformation_bs,
                            FOpid_control_B.sina));
        _mm_storeu_pd(&FOpid_control_B.dv1[0], tmp_1);
        FOpid_control_B.sina = FOpid_control_B.dv1[0];
        FOpid_control_B.rtb_CoordinateTransformation_bs = FOpid_control_B.dv1[1];
        FOpid_control_B.rtb_CoordinateTransformationC_n +=
          FOpid_control_B.RotationAnglestoDirectionCo[3 * i + 2] *
          FOpid_control_B.wbe_b[i];
      }

      FOpid_control_B.Product_k[2] =
        FOpid_control_B.rtb_CoordinateTransformationC_n;
      FOpid_control_B.Product_k[1] =
        FOpid_control_B.rtb_CoordinateTransformation_bs;
      FOpid_control_B.Product_k[0] = FOpid_control_B.sina;
      tmp_1 = _mm_add_pd(_mm_div_pd(_mm_mul_pd(_mm_sub_pd(_mm_set_pd
        (FOpid_control_B.w1[1], FOpid_control_B.w1_c[1]), _mm_loadu_pd
        (&FOpid_control_B.Product_k[0])), _mm_sub_pd(_mm_set1_pd
        (FOpid_control_B.Gain2), _mm_set1_pd(1000.0))), _mm_set1_pd
        (FOpid_control_ConstB.Sum)), _mm_loadu_pd(&FOpid_control_B.Product_k[0]));
      _mm_storeu_pd(&FOpid_control_B.wbe_b[0], tmp_1);

      /* Sum: '<S75>/Sum3' incorporates:
       *  Constant: '<S75>/max_height_low'
       *  Product: '<S75>/Product1'
       *  Product: '<S79>/Product'
       *  Sum: '<S75>/Sum1'
       *  Sum: '<S75>/Sum2'
       */
      FOpid_control_B.wbe_b[2] = (FOpid_control_B.LwgV1[1] -
        FOpid_control_B.rtb_CoordinateTransformationC_n) *
        (FOpid_control_B.Gain2 - 1000.0) / FOpid_control_ConstB.Sum +
        FOpid_control_B.rtb_CoordinateTransformationC_n;

      /* End of Outputs for SubSystem: '<S54>/Interpolate  velocities' */
      break;
    }

    /* End of If: '<S54>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
    /* Unit Conversion - from: ft/s to: m/s
       Expression: output = (0.3048*input) + (0) */
    if (tmp_0) {
      /* MATLABSystem: '<S46>/SourceBlock' */
      FOpid_control_B.SourceBlock_o1_h = Sub_FOpid_control_417.getLatestMessage(
        &rtb_SourceBlock_o2_j);

      /* Outputs for Enabled SubSystem: '<S46>/Enabled Subsystem' */
      FOpid_control_EnabledSubsystem(FOpid_control_B.SourceBlock_o1_h,
        &rtb_SourceBlock_o2_j, &FOpid_control_B.EnabledSubsystem_pt);

      /* End of Outputs for SubSystem: '<S46>/Enabled Subsystem' */
    }

    /* Switch: '<S35>/Switch' incorporates:
     *  UnitConversion: '<S40>/Unit Conversion'
     */
    if (FOpid_control_B.EnabledSubsystem_pt.In1.data) {
      tmp_1 = _mm_mul_pd(_mm_set1_pd(0.3048), _mm_loadu_pd
                         (&FOpid_control_B.wbe_b[0]));
      _mm_storeu_pd(&FOpid_control_B.Switch[0], tmp_1);

      /* Switch: '<S35>/Switch' incorporates:
       *  UnitConversion: '<S40>/Unit Conversion'
       */
      FOpid_control_B.Switch[2] = 0.3048 * FOpid_control_B.wbe_b[2];
    } else {
      /* Switch: '<S35>/Switch' incorporates:
       *  Constant: '<S35>/Constant'
       */
      FOpid_control_B.Switch[0] = 0.0;
      FOpid_control_B.Switch[1] = 0.0;
      FOpid_control_B.Switch[2] = 0.0;
    }

    /* End of Switch: '<S35>/Switch' */

    /* Outputs for Enabled SubSystem: '<S48>/Hpgw' incorporates:
     *  EnablePort: '<S59>/Enable'
     */
    if (tmp_0 && rtsiIsModeUpdateTimeStep(&(&FOpid_control_M)->solverInfo) &&
        !FOpid_control_DW.Hpgw_MODE) {
      (void) memset(&(FOpid_control_XDis.pgw_p_CSTATE), 0,
                    2*sizeof(boolean_T));

      /* InitializeConditions for Integrator: '<S59>/pgw_p' */
      FOpid_control_X.pgw_p_CSTATE[0] = 0.0;
      FOpid_control_X.pgw_p_CSTATE[1] = 0.0;
      FOpid_control_DW.Hpgw_MODE = true;
    }

    if (FOpid_control_DW.Hpgw_MODE) {
      /* Fcn: '<S59>/sqrt(0.8//V)' */
      FOpid_control_B.sina = sqrt(0.8 / FOpid_control_B.u_l);

      /* Product: '<S59>/w3' */
      FOpid_control_B.rtb_CoordinateTransformation_bs = FOpid_control_B.u_l *
        FOpid_control_ConstB.w4;

      /* Product: '<S59>/w' incorporates:
       *  Fcn: '<S59>/sqrt(0.8//V)'
       *  Gain: '<S55>/Lw'
       *  Integrator: '<S59>/pgw_p'
       *  Math: '<S59>/L^1//3'
       *  Product: '<S59>/Lug//V1'
       *  Product: '<S59>/w1'
       *  Product: '<S59>/w2'
       *  Sum: '<S59>/Sum'
       */
      FOpid_control_B.w_o[0] = (FOpid_control_B.sina / rt_powd_snf
        (FOpid_control_B.Gain3_o, 0.3333333333333333) * FOpid_control_ConstB.u16
        * FOpid_control_B.Product[3] - FOpid_control_X.pgw_p_CSTATE[0]) *
        FOpid_control_B.rtb_CoordinateTransformation_bs;

      /* Math: '<S59>/L^1//3' */
      if (FOpid_control_B.Lv[1] < 0.0) {
        FOpid_control_B.q_aero = -rt_powd_snf(-FOpid_control_B.Lv[1],
          0.3333333333333333);
      } else {
        FOpid_control_B.q_aero = rt_powd_snf(FOpid_control_B.Lv[1],
          0.3333333333333333);
      }

      /* Product: '<S59>/w' incorporates:
       *  Fcn: '<S59>/sqrt(0.8//V)'
       *  Integrator: '<S59>/pgw_p'
       *  Product: '<S59>/Lug//V1'
       *  Product: '<S59>/w1'
       *  Product: '<S59>/w2'
       *  Sum: '<S59>/Sum'
       */
      FOpid_control_B.w_o[1] = (FOpid_control_B.sina / FOpid_control_B.q_aero *
        FOpid_control_ConstB.u16 * FOpid_control_B.Product[3] -
        FOpid_control_X.pgw_p_CSTATE[1]) *
        FOpid_control_B.rtb_CoordinateTransformation_bs;

      /* Product: '<S59>/sigma_w' incorporates:
       *  Integrator: '<S59>/pgw_p'
       */
      tmp_1 = _mm_mul_pd(_mm_set_pd(FOpid_control_B.WhiteNoise_p,
        FOpid_control_ConstB.sigma_wg), _mm_loadu_pd
                         (&FOpid_control_X.pgw_p_CSTATE[0]));

      /* Product: '<S59>/sigma_w' */
      _mm_storeu_pd(&FOpid_control_B.sigma_w[0], tmp_1);
    }

    /* End of Outputs for SubSystem: '<S48>/Hpgw' */

    /* Outputs for Enabled SubSystem: '<S48>/Hqgw' incorporates:
     *  EnablePort: '<S60>/Enable'
     */
    if (tmp_0 && rtsiIsModeUpdateTimeStep(&(&FOpid_control_M)->solverInfo) &&
        !FOpid_control_DW.Hqgw_MODE) {
      (void) memset(&(FOpid_control_XDis.qgw_p_CSTATE), 0,
                    2*sizeof(boolean_T));

      /* InitializeConditions for Integrator: '<S60>/qgw_p' */
      FOpid_control_X.qgw_p_CSTATE[0] = 0.0;
      FOpid_control_X.qgw_p_CSTATE[1] = 0.0;
      FOpid_control_DW.Hqgw_MODE = true;
    }

    if (FOpid_control_DW.Hqgw_MODE) {
      /* Gain: '<S60>/pi//4' */
      FOpid_control_B.Gain3_o = 0.7853981633974483 * FOpid_control_B.u_l;

      /* Product: '<S60>/w' incorporates:
       *  Integrator: '<S60>/qgw_p'
       *  Product: '<S60>/wg//V'
       *  Sum: '<S60>/Sum'
       */
      FOpid_control_B.WhiteNoise_p = (FOpid_control_B.LwgV1[0] /
        FOpid_control_B.u_l - FOpid_control_X.qgw_p_CSTATE[0]) *
        (FOpid_control_B.Gain3_o / FOpid_control_ConstB.UnitConversion_n);
      FOpid_control_B.w_e0[0] = FOpid_control_B.WhiteNoise_p;

      /* UnaryMinus: '<S60>/Unary Minus' */
      FOpid_control_B.UnaryMinus[0] = -FOpid_control_B.WhiteNoise_p;

      /* Product: '<S60>/w' incorporates:
       *  Integrator: '<S60>/qgw_p'
       *  Product: '<S60>/wg//V'
       *  Sum: '<S60>/Sum'
       */
      FOpid_control_B.WhiteNoise_p = (FOpid_control_B.LwgV1[1] /
        FOpid_control_B.u_l - FOpid_control_X.qgw_p_CSTATE[1]) *
        (FOpid_control_B.Gain3_o / FOpid_control_ConstB.UnitConversion_n);
      FOpid_control_B.w_e0[1] = FOpid_control_B.WhiteNoise_p;

      /* UnaryMinus: '<S60>/Unary Minus' */
      FOpid_control_B.UnaryMinus[1] = -FOpid_control_B.WhiteNoise_p;
    }

    /* End of Outputs for SubSystem: '<S48>/Hqgw' */

    /* Outputs for Enabled SubSystem: '<S48>/Hrgw' incorporates:
     *  EnablePort: '<S61>/Enable'
     */
    if (tmp_0 && rtsiIsModeUpdateTimeStep(&(&FOpid_control_M)->solverInfo) &&
        !FOpid_control_DW.Hrgw_MODE) {
      (void) memset(&(FOpid_control_XDis.rgw_p_CSTATE), 0,
                    2*sizeof(boolean_T));

      /* InitializeConditions for Integrator: '<S61>/rgw_p' */
      FOpid_control_X.rgw_p_CSTATE[0] = 0.0;
      FOpid_control_X.rgw_p_CSTATE[1] = 0.0;
      FOpid_control_DW.Hrgw_MODE = true;
    }

    if (FOpid_control_DW.Hrgw_MODE) {
      /* Product: '<S61>/vg//V' incorporates:
       *  Gain: '<S61>/pi//3'
       *  Integrator: '<S61>/rgw_p'
       *  Product: '<S61>/w'
       */
      tmp_1 = _mm_mul_pd(_mm_sub_pd(_mm_div_pd(_mm_loadu_pd(&FOpid_control_B.w1
        [0]), _mm_set1_pd(FOpid_control_B.u_l)), _mm_loadu_pd
        (&FOpid_control_X.rgw_p_CSTATE[0])), _mm_div_pd(_mm_set1_pd
        (1.0471975511965976 * FOpid_control_B.u_l), _mm_set1_pd
        (FOpid_control_ConstB.UnitConversion_n)));

      /* Product: '<S61>/w' */
      _mm_storeu_pd(&FOpid_control_B.w_d[0], tmp_1);
    }

    /* End of Outputs for SubSystem: '<S48>/Hrgw' */

    /* If: '<S53>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' incorporates:
     *  Constant: '<S67>/max_height_low'
     *  Product: '<S67>/Product1'
     *  Product: '<S72>/Product1'
     *  Product: '<S72>/Product2'
     *  Product: '<S74>/Product1'
     *  Product: '<S74>/Product2'
     *  Sum: '<S67>/Sum1'
     *  Sum: '<S67>/Sum2'
     *  Sum: '<S67>/Sum3'
     *  Sum: '<S72>/Sum'
     *  Sum: '<S74>/Sum'
     */
    rtPrevAction = FOpid_control_DW.ifHeightMaxlowaltitudeelseifH_a;
    if (rtsiIsModeUpdateTimeStep(&(&FOpid_control_M)->solverInfo)) {
      if (FOpid_control_B.Gain2 <= 1000.0) {
        rtAction = 0;
      } else if (FOpid_control_B.Gain2 >= 2000.0) {
        rtAction = 1;
      } else {
        rtAction = 2;
      }

      FOpid_control_DW.ifHeightMaxlowaltitudeelseifH_a = rtAction;
    } else {
      rtAction = FOpid_control_DW.ifHeightMaxlowaltitudeelseifH_a;
    }

    if (rtPrevAction != rtAction) {
      rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
        ->solverInfo, true);
    }

    switch (rtAction) {
     case 0:
      /* Outputs for IfAction SubSystem: '<S53>/Low altitude  rates' incorporates:
       *  ActionPort: '<S68>/Action Port'
       */
      /* SignalConversion generated from: '<S73>/Vector Concatenate' */
      FOpid_control_B.Product_k[2] = FOpid_control_B.w_d[0];

      /* Trigonometry: '<S74>/Trigonometric Function1' incorporates:
       *  UnitConversion: '<S47>/Unit Conversion'
       */
      FOpid_control_B.Gain2 = sin(FOpid_control_ConstB.UnitConversion);
      FOpid_control_B.u_l = cos(FOpid_control_ConstB.UnitConversion);
      _mm_storeu_pd(&FOpid_control_B.Product_k[0], _mm_add_pd(_mm_mul_pd
        (_mm_set_pd(FOpid_control_B.Gain2, FOpid_control_B.sigma_w[0]),
         _mm_set_pd(FOpid_control_B.sigma_w[0], FOpid_control_B.u_l)),
        _mm_mul_pd(_mm_mul_pd(_mm_set_pd(FOpid_control_B.UnaryMinus[0],
        FOpid_control_B.Gain2), _mm_set_pd(FOpid_control_B.u_l,
        FOpid_control_B.UnaryMinus[0])), _mm_set_pd(1.0, -1.0))));

      /* Product: '<S73>/Product' incorporates:
       *  Angle2Dcm: '<S35>/Rotation Angles to Direction Cosine Matrix'
       *  Concatenate: '<S73>/Vector Concatenate'
       *  Product: '<S74>/Product1'
       *  Product: '<S74>/Product2'
       *  Reshape: '<S73>/Reshape1'
       *  Sum: '<S74>/Sum'
       */
      FOpid_control_B.sina = 0.0;
      FOpid_control_B.rtb_CoordinateTransformation_bs = 0.0;
      FOpid_control_B.rtb_CoordinateTransformationC_n = 0.0;
      for (i = 0; i < 3; i++) {
        tmp_1 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
          (&FOpid_control_B.RotationAnglestoDirectionCo[3 * i]), _mm_set1_pd
          (FOpid_control_B.Product_k[i])), _mm_set_pd
                           (FOpid_control_B.rtb_CoordinateTransformation_bs,
                            FOpid_control_B.sina));
        _mm_storeu_pd(&FOpid_control_B.dv1[0], tmp_1);
        FOpid_control_B.sina = FOpid_control_B.dv1[0];
        FOpid_control_B.rtb_CoordinateTransformation_bs = FOpid_control_B.dv1[1];
        FOpid_control_B.rtb_CoordinateTransformationC_n +=
          FOpid_control_B.RotationAnglestoDirectionCo[3 * i + 2] *
          FOpid_control_B.Product_k[i];
      }

      FOpid_control_B.wbe_b[2] = FOpid_control_B.rtb_CoordinateTransformationC_n;
      FOpid_control_B.wbe_b[1] = FOpid_control_B.rtb_CoordinateTransformation_bs;
      FOpid_control_B.wbe_b[0] = FOpid_control_B.sina;

      /* End of Product: '<S73>/Product' */
      /* End of Outputs for SubSystem: '<S53>/Low altitude  rates' */
      break;

     case 1:
      /* Outputs for IfAction SubSystem: '<S53>/Medium//High  altitude rates' incorporates:
       *  ActionPort: '<S69>/Action Port'
       */
      /* Gain: '<S69>/Gain' */
      FOpid_control_B.wbe_b[0] = FOpid_control_B.sigma_w[1];
      FOpid_control_B.wbe_b[1] = FOpid_control_B.UnaryMinus[1];
      FOpid_control_B.wbe_b[2] = FOpid_control_B.w_d[1];

      /* End of Outputs for SubSystem: '<S53>/Medium//High  altitude rates' */
      break;

     default:
      /* Outputs for IfAction SubSystem: '<S53>/Interpolate  rates' incorporates:
       *  ActionPort: '<S67>/Action Port'
       */
      /* Trigonometry: '<S72>/Trigonometric Function' incorporates:
       *  UnitConversion: '<S47>/Unit Conversion'
       */
      FOpid_control_B.u_l = sin(FOpid_control_ConstB.UnitConversion);
      FOpid_control_B.Gain3_o = cos(FOpid_control_ConstB.UnitConversion);
      _mm_storeu_pd(&FOpid_control_B.wbe_b[0], _mm_add_pd(_mm_mul_pd(_mm_set_pd
        (FOpid_control_B.u_l, FOpid_control_B.sigma_w[0]), _mm_set_pd
        (FOpid_control_B.sigma_w[0], FOpid_control_B.Gain3_o)), _mm_mul_pd
        (_mm_mul_pd(_mm_set_pd(FOpid_control_B.UnaryMinus[0],
        FOpid_control_B.u_l), _mm_set_pd(FOpid_control_B.Gain3_o,
        FOpid_control_B.UnaryMinus[0])), _mm_set_pd(1.0, -1.0))));

      /* SignalConversion generated from: '<S71>/Vector Concatenate' incorporates:
       *  Product: '<S72>/Product1'
       *  Product: '<S72>/Product2'
       *  Sum: '<S72>/Sum'
       */
      FOpid_control_B.wbe_b[2] = FOpid_control_B.w_d[0];

      /* Product: '<S71>/Product' incorporates:
       *  Angle2Dcm: '<S35>/Rotation Angles to Direction Cosine Matrix'
       *  Concatenate: '<S71>/Vector Concatenate'
       */
      FOpid_control_B.sina = 0.0;
      FOpid_control_B.rtb_CoordinateTransformation_bs = 0.0;
      FOpid_control_B.rtb_CoordinateTransformationC_n = 0.0;
      for (i = 0; i < 3; i++) {
        tmp_1 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
          (&FOpid_control_B.RotationAnglestoDirectionCo[3 * i]), _mm_set1_pd
          (FOpid_control_B.wbe_b[i])), _mm_set_pd
                           (FOpid_control_B.rtb_CoordinateTransformation_bs,
                            FOpid_control_B.sina));
        _mm_storeu_pd(&FOpid_control_B.dv1[0], tmp_1);
        FOpid_control_B.sina = FOpid_control_B.dv1[0];
        FOpid_control_B.rtb_CoordinateTransformation_bs = FOpid_control_B.dv1[1];
        FOpid_control_B.rtb_CoordinateTransformationC_n +=
          FOpid_control_B.RotationAnglestoDirectionCo[3 * i + 2] *
          FOpid_control_B.wbe_b[i];
      }

      FOpid_control_B.Product_k[2] =
        FOpid_control_B.rtb_CoordinateTransformationC_n;
      FOpid_control_B.Product_k[1] =
        FOpid_control_B.rtb_CoordinateTransformation_bs;
      FOpid_control_B.Product_k[0] = FOpid_control_B.sina;
      tmp_1 = _mm_add_pd(_mm_div_pd(_mm_mul_pd(_mm_sub_pd(_mm_set_pd
        (FOpid_control_B.UnaryMinus[1], FOpid_control_B.sigma_w[1]),
        _mm_loadu_pd(&FOpid_control_B.Product_k[0])), _mm_sub_pd(_mm_set1_pd
        (FOpid_control_B.Gain2), _mm_set1_pd(1000.0))), _mm_set1_pd
        (FOpid_control_ConstB.Sum_a)), _mm_loadu_pd(&FOpid_control_B.Product_k[0]));
      _mm_storeu_pd(&FOpid_control_B.wbe_b[0], tmp_1);

      /* Sum: '<S67>/Sum3' incorporates:
       *  Constant: '<S67>/max_height_low'
       *  Product: '<S67>/Product1'
       *  Product: '<S71>/Product'
       *  Sum: '<S67>/Sum1'
       *  Sum: '<S67>/Sum2'
       */
      FOpid_control_B.wbe_b[2] = (FOpid_control_B.w_d[1] -
        FOpid_control_B.rtb_CoordinateTransformationC_n) *
        (FOpid_control_B.Gain2 - 1000.0) / FOpid_control_ConstB.Sum_a +
        FOpid_control_B.rtb_CoordinateTransformationC_n;

      /* End of Outputs for SubSystem: '<S53>/Interpolate  rates' */
      break;
    }

    /* End of If: '<S53>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
    if (tmp_0) {
      /* MATLABSystem: '<S43>/SourceBlock' */
      FOpid_control_B.SourceBlock_o1_k = Sub_FOpid_control_423.getLatestMessage(
        &rtb_SourceBlock_o2_dd);

      /* Outputs for Enabled SubSystem: '<S43>/Enabled Subsystem' */
      FOpid_control_EnabledSubsystem(FOpid_control_B.SourceBlock_o1_k,
        &rtb_SourceBlock_o2_dd, &FOpid_control_B.EnabledSubsystem);

      /* End of Outputs for SubSystem: '<S43>/Enabled Subsystem' */
    }

    /* Switch: '<S35>/Switch1' */
    if (FOpid_control_B.EnabledSubsystem.In1.data) {
      /* Switch: '<S35>/Switch1' */
      FOpid_control_B.Switch1[0] = FOpid_control_B.wbe_b[0];
      FOpid_control_B.Switch1[1] = FOpid_control_B.wbe_b[1];
      FOpid_control_B.Switch1[2] = FOpid_control_B.wbe_b[2];
    } else {
      /* Switch: '<S35>/Switch1' incorporates:
       *  Constant: '<S35>/Constant2'
       */
      FOpid_control_B.Switch1[0] = 0.0;
      FOpid_control_B.Switch1[1] = 0.0;
      FOpid_control_B.Switch1[2] = 0.0;
    }

    /* End of Switch: '<S35>/Switch1' */
    if (tmp_0) {
      /* MATLABSystem: '<S44>/SourceBlock' */
      FOpid_control_B.SourceBlock_o1_c = Sub_FOpid_control_443.getLatestMessage(
        &FOpid_control_B.SourceBlock_o2_p);

      /* Outputs for Enabled SubSystem: '<S44>/Enabled Subsystem' */
      FOpid_contro_EnabledSubsystem_k(FOpid_control_B.SourceBlock_o1_c,
        &FOpid_control_B.SourceBlock_o2_p, &FOpid_control_B.EnabledSubsystem_k);

      /* End of Outputs for SubSystem: '<S44>/Enabled Subsystem' */
    }

    /* Switch: '<S35>/Switch2' */
    if (FOpid_control_B.EnabledSubsystem_k.In1.data != 0.0) {
      /* Switch: '<S35>/Switch2' incorporates:
       *  TransferFcn: '<S35>/Transfer Fcn'
       */
      FOpid_control_B.Switch2_i = 0.5303 * FOpid_control_X.TransferFcn_CSTATE[0]
        + 0.0 * FOpid_control_X.TransferFcn_CSTATE[1];
    } else {
      /* Switch: '<S35>/Switch2' incorporates:
       *  Constant: '<S35>/Constant3'
       */
      FOpid_control_B.Switch2_i = 0.0;
    }

    /* End of Switch: '<S35>/Switch2' */
    if (tmp_0) {
      /* RandomNumber: '<S38>/White Noise' */
      FOpid_control_B.WhiteNoise_p = FOpid_control_DW.NextOutput_k;

      /* Gain: '<S38>/Output' */
      FOpid_control_B.Output = 10.0 * FOpid_control_B.WhiteNoise_p;

      /* MATLABSystem: '<S45>/SourceBlock' */
      FOpid_control_B.SourceBlock_o1_d = Sub_FOpid_control_445.getLatestMessage(
        &FOpid_control_B.SourceBlock_o2_k);

      /* Outputs for Enabled SubSystem: '<S45>/Enabled Subsystem' */
      FOpid_contro_EnabledSubsystem_k(FOpid_control_B.SourceBlock_o1_d,
        &FOpid_control_B.SourceBlock_o2_k, &FOpid_control_B.EnabledSubsystem_p);

      /* End of Outputs for SubSystem: '<S45>/Enabled Subsystem' */
    }

    /* Switch: '<S35>/Switch3' */
    if (FOpid_control_B.EnabledSubsystem_p.In1.data != 0.0) {
      /* Switch: '<S35>/Switch3' incorporates:
       *  TransferFcn: '<S35>/Transfer Fcn1'
       */
      FOpid_control_B.Switch3_l = -0.0003571 *
        FOpid_control_X.TransferFcn1_CSTATE + 0.03571 * FOpid_control_B.Output;
    } else {
      /* Switch: '<S35>/Switch3' incorporates:
       *  Constant: '<S35>/Constant4'
       */
      FOpid_control_B.Switch3_l = 0.0;
    }

    /* End of Switch: '<S35>/Switch3' */
    if (tmp_0) {
    }

    /* Product: '<S35>/Product2' incorporates:
     *  Math: '<S35>/Square'
     *  Math: '<S35>/Square1'
     *  Math: '<S35>/Square2'
     *  Sqrt: '<S35>/Sqrt'
     *  Sum: '<S35>/Sum2'
     */
    FOpid_control_B.Power = sqrt((FOpid_control_B.x[0] * FOpid_control_B.x[0] +
      FOpid_control_B.x[1] * FOpid_control_B.x[1]) + FOpid_control_B.x[2] *
      FOpid_control_B.x[2]) * FOpid_control_B.XDOT[34];

    /* Gain: '<S35>/Gain3' */
    FOpid_control_B.Gain3 = 0.001 * FOpid_control_B.Power;
    if (tmp_0) {
    }

    /* Gain: '<S35>/Gain1' incorporates:
     *  Integrator: '<S35>/Integrator1'
     */
    FOpid_control_B.EnergykWh = 2.7777777777777776E-7 *
      FOpid_control_X.Integrator1_CSTATE;
    if (tmp_0) {
    }

    /* Product: '<S35>/Divide' incorporates:
     *  Constant: '<S35>/thrust efficiency Cp?'
     */
    FOpid_control_B.powerdemand = FOpid_control_B.Gain3 / 0.57;

    /* Product: '<S35>/Divide1' */
    FOpid_control_B.loadtorque = FOpid_control_B.powerdemand /
      FOpid_control_ConstB.motorspeed;

    /* Sum: '<S35>/SumOLA' */
    FOpid_control_B.SumOLA[0] = FOpid_control_B.Switch[0];
    FOpid_control_B.SumOLA[1] = FOpid_control_B.Switch[1] +
      FOpid_control_B.Switch2_i;
    FOpid_control_B.SumOLA[2] = FOpid_control_B.Switch[2];

    /* Sum: '<S35>/SumOLA1' */
    FOpid_control_B.SumOLA1[0] = FOpid_control_B.Switch1[0];
    FOpid_control_B.SumOLA1[1] = FOpid_control_B.Switch1[1] +
      FOpid_control_B.Switch3_l;
    FOpid_control_B.SumOLA1[2] = FOpid_control_B.Switch1[2];

    /* SecondOrderIntegrator: '<S25>/Integrator, Second-Order Limited' */
    if (rtsiIsModeUpdateTimeStep(&(&FOpid_control_M)->solverInfo)) {
      switch (FOpid_control_DW.IntegratorSecondOrderLimited_MO) {
       case 0:
        if (FOpid_control_X.IntegratorSecondOrderLimited_CS[0] <=
            -0.3490658503988659) {
          FOpid_control_X.IntegratorSecondOrderLimited_CS[0] =
            -0.3490658503988659;
          if (FOpid_control_X.IntegratorSecondOrderLimited_CS[1] > 0.0) {
            FOpid_control_DW.IntegratorSecondOrderLimited_MO = 0;
          } else {
            FOpid_control_X.IntegratorSecondOrderLimited_CS[1] = 0.0;
            FOpid_control_DW.IntegratorSecondOrderLimited_MO = 1;
          }

          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
            ->solverInfo, true);
        }

        if (FOpid_control_X.IntegratorSecondOrderLimited_CS[0] >=
            0.2617993877991494) {
          FOpid_control_X.IntegratorSecondOrderLimited_CS[0] =
            0.2617993877991494;
          if (FOpid_control_X.IntegratorSecondOrderLimited_CS[1] < 0.0) {
            FOpid_control_DW.IntegratorSecondOrderLimited_MO = 0;
          } else {
            FOpid_control_X.IntegratorSecondOrderLimited_CS[1] = 0.0;
            FOpid_control_DW.IntegratorSecondOrderLimited_MO = 2;
          }

          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
            ->solverInfo, true);
        }

        if (FOpid_control_X.IntegratorSecondOrderLimited_CS[1] <=
            -8.726646259971647) {
          FOpid_control_X.IntegratorSecondOrderLimited_CS[1] =
            -8.726646259971647;
          FOpid_control_DW.IntegratorSecondOrderLimited_MO = 3;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
            ->solverInfo, true);
        }

        if (FOpid_control_X.IntegratorSecondOrderLimited_CS[1] >=
            8.726646259971647) {
          FOpid_control_X.IntegratorSecondOrderLimited_CS[1] = 8.726646259971647;
          FOpid_control_DW.IntegratorSecondOrderLimited_MO = 4;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
            ->solverInfo, true);
        }
        break;

       case 1:
        if (FOpid_control_X.IntegratorSecondOrderLimited_CS[0] >
            -0.3490658503988659) {
          if (FOpid_control_X.IntegratorSecondOrderLimited_CS[0] >=
              0.2617993877991494) {
            FOpid_control_DW.IntegratorSecondOrderLimited_MO = 2;
            FOpid_control_X.IntegratorSecondOrderLimited_CS[0] =
              0.2617993877991494;
          } else {
            FOpid_control_DW.IntegratorSecondOrderLimited_MO = 0;
          }
        } else {
          FOpid_control_X.IntegratorSecondOrderLimited_CS[0] =
            -0.3490658503988659;
          FOpid_control_X.IntegratorSecondOrderLimited_CS[1] = 0.0;
        }
        break;

       case 2:
        if (FOpid_control_X.IntegratorSecondOrderLimited_CS[0] <
            0.2617993877991494) {
          if (FOpid_control_X.IntegratorSecondOrderLimited_CS[0] <=
              -0.3490658503988659) {
            FOpid_control_DW.IntegratorSecondOrderLimited_MO = 1;
            FOpid_control_X.IntegratorSecondOrderLimited_CS[0] =
              -0.3490658503988659;
          } else {
            FOpid_control_DW.IntegratorSecondOrderLimited_MO = 0;
          }
        } else {
          FOpid_control_X.IntegratorSecondOrderLimited_CS[0] =
            0.2617993877991494;
          FOpid_control_X.IntegratorSecondOrderLimited_CS[1] = 0.0;
        }
        break;

       case 3:
        if (FOpid_control_X.IntegratorSecondOrderLimited_CS[1] >
            -8.726646259971647) {
          if (FOpid_control_X.IntegratorSecondOrderLimited_CS[1] >=
              8.726646259971647) {
            FOpid_control_DW.IntegratorSecondOrderLimited_MO = 4;
            FOpid_control_X.IntegratorSecondOrderLimited_CS[1] =
              8.726646259971647;
          } else {
            FOpid_control_DW.IntegratorSecondOrderLimited_MO = 0;
          }
        } else {
          FOpid_control_X.IntegratorSecondOrderLimited_CS[1] =
            -8.726646259971647;
        }

        if (FOpid_control_X.IntegratorSecondOrderLimited_CS[0] <=
            -0.3490658503988659) {
          FOpid_control_X.IntegratorSecondOrderLimited_CS[0] =
            -0.3490658503988659;
          FOpid_control_X.IntegratorSecondOrderLimited_CS[1] = 0.0;
          FOpid_control_DW.IntegratorSecondOrderLimited_MO = 1;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
            ->solverInfo, true);
        }
        break;

       case 4:
        if (FOpid_control_X.IntegratorSecondOrderLimited_CS[1] <
            8.726646259971647) {
          if (FOpid_control_X.IntegratorSecondOrderLimited_CS[1] <=
              -8.726646259971647) {
            FOpid_control_DW.IntegratorSecondOrderLimited_MO = 3;
            FOpid_control_X.IntegratorSecondOrderLimited_CS[1] =
              -8.726646259971647;
          } else {
            FOpid_control_DW.IntegratorSecondOrderLimited_MO = 0;
          }
        } else {
          FOpid_control_X.IntegratorSecondOrderLimited_CS[1] = 8.726646259971647;
        }

        if (FOpid_control_X.IntegratorSecondOrderLimited_CS[0] >=
            0.2617993877991494) {
          FOpid_control_X.IntegratorSecondOrderLimited_CS[0] =
            0.2617993877991494;
          FOpid_control_X.IntegratorSecondOrderLimited_CS[1] = 0.0;
          FOpid_control_DW.IntegratorSecondOrderLimited_MO = 2;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
            ->solverInfo, true);
        }
        break;
      }
    }

    if (FOpid_control_X.IntegratorSecondOrderLimited_CS[0] < -0.3490658503988659)
    {
      FOpid_control_B.sina = -0.3490658503988659;
    } else if (FOpid_control_X.IntegratorSecondOrderLimited_CS[0] >
               0.2617993877991494) {
      FOpid_control_B.sina = 0.2617993877991494;
    } else {
      FOpid_control_B.sina = FOpid_control_X.IntegratorSecondOrderLimited_CS[0];
    }

    /* Sum: '<S25>/Sum3' incorporates:
     *  SecondOrderIntegrator: '<S25>/Integrator, Second-Order Limited'
     */
    FOpid_control_B.Gain2 = FOpid_control_ConstB.Demandlimits -
      FOpid_control_B.sina;

    /* Saturate: '<S25>/rate limit*2*zeta//wn' */
    if (FOpid_control_B.Gain2 > 5.235987755982988) {
      FOpid_control_B.Gain2 = 5.235987755982988;
    } else if (FOpid_control_B.Gain2 < -5.235987755982988) {
      FOpid_control_B.Gain2 = -5.235987755982988;
    }

    /* SecondOrderIntegrator: '<S25>/Integrator, Second-Order Limited' */
    if (FOpid_control_X.IntegratorSecondOrderLimited_CS[1] < -8.726646259971647)
    {
      FOpid_control_B.sina = -8.726646259971647;
    } else if (FOpid_control_X.IntegratorSecondOrderLimited_CS[1] >
               8.726646259971647) {
      FOpid_control_B.sina = 8.726646259971647;
    } else {
      FOpid_control_B.sina = FOpid_control_X.IntegratorSecondOrderLimited_CS[1];
    }

    /* Sum: '<S25>/Sum2' incorporates:
     *  Gain: '<S25>/2*zeta * wn'
     *  Saturate: '<S25>/rate limit*2*zeta//wn'
     *  SecondOrderIntegrator: '<S25>/Integrator, Second-Order Limited'
     */
    FOpid_control_B.Sum2_j = FOpid_control_B.Gain2 - 0.6 * FOpid_control_B.sina;

    /* SecondOrderIntegrator: '<S26>/Integrator, Second-Order Limited' */
    if (rtsiIsModeUpdateTimeStep(&(&FOpid_control_M)->solverInfo)) {
      switch (FOpid_control_DW.IntegratorSecondOrderLimited__h) {
       case 0:
        if (FOpid_control_X.IntegratorSecondOrderLimited__n[0] <=
            -0.3490658503988659) {
          FOpid_control_X.IntegratorSecondOrderLimited__n[0] =
            -0.3490658503988659;
          if (FOpid_control_X.IntegratorSecondOrderLimited__n[1] > 0.0) {
            FOpid_control_DW.IntegratorSecondOrderLimited__h = 0;
          } else {
            FOpid_control_X.IntegratorSecondOrderLimited__n[1] = 0.0;
            FOpid_control_DW.IntegratorSecondOrderLimited__h = 1;
          }

          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
            ->solverInfo, true);
        }

        if (FOpid_control_X.IntegratorSecondOrderLimited__n[0] >=
            0.3490658503988659) {
          FOpid_control_X.IntegratorSecondOrderLimited__n[0] =
            0.3490658503988659;
          if (FOpid_control_X.IntegratorSecondOrderLimited__n[1] < 0.0) {
            FOpid_control_DW.IntegratorSecondOrderLimited__h = 0;
          } else {
            FOpid_control_X.IntegratorSecondOrderLimited__n[1] = 0.0;
            FOpid_control_DW.IntegratorSecondOrderLimited__h = 2;
          }

          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
            ->solverInfo, true);
        }

        if (FOpid_control_X.IntegratorSecondOrderLimited__n[1] <=
            -8.726646259971647) {
          FOpid_control_X.IntegratorSecondOrderLimited__n[1] =
            -8.726646259971647;
          FOpid_control_DW.IntegratorSecondOrderLimited__h = 3;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
            ->solverInfo, true);
        }

        if (FOpid_control_X.IntegratorSecondOrderLimited__n[1] >=
            8.726646259971647) {
          FOpid_control_X.IntegratorSecondOrderLimited__n[1] = 8.726646259971647;
          FOpid_control_DW.IntegratorSecondOrderLimited__h = 4;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
            ->solverInfo, true);
        }
        break;

       case 1:
        if (FOpid_control_X.IntegratorSecondOrderLimited__n[0] >
            -0.3490658503988659) {
          if (FOpid_control_X.IntegratorSecondOrderLimited__n[0] >=
              0.3490658503988659) {
            FOpid_control_DW.IntegratorSecondOrderLimited__h = 2;
            FOpid_control_X.IntegratorSecondOrderLimited__n[0] =
              0.3490658503988659;
          } else {
            FOpid_control_DW.IntegratorSecondOrderLimited__h = 0;
          }
        } else {
          FOpid_control_X.IntegratorSecondOrderLimited__n[0] =
            -0.3490658503988659;
          FOpid_control_X.IntegratorSecondOrderLimited__n[1] = 0.0;
        }
        break;

       case 2:
        if (FOpid_control_X.IntegratorSecondOrderLimited__n[0] <
            0.3490658503988659) {
          if (FOpid_control_X.IntegratorSecondOrderLimited__n[0] <=
              -0.3490658503988659) {
            FOpid_control_DW.IntegratorSecondOrderLimited__h = 1;
            FOpid_control_X.IntegratorSecondOrderLimited__n[0] =
              -0.3490658503988659;
          } else {
            FOpid_control_DW.IntegratorSecondOrderLimited__h = 0;
          }
        } else {
          FOpid_control_X.IntegratorSecondOrderLimited__n[0] =
            0.3490658503988659;
          FOpid_control_X.IntegratorSecondOrderLimited__n[1] = 0.0;
        }
        break;

       case 3:
        if (FOpid_control_X.IntegratorSecondOrderLimited__n[1] >
            -8.726646259971647) {
          if (FOpid_control_X.IntegratorSecondOrderLimited__n[1] >=
              8.726646259971647) {
            FOpid_control_DW.IntegratorSecondOrderLimited__h = 4;
            FOpid_control_X.IntegratorSecondOrderLimited__n[1] =
              8.726646259971647;
          } else {
            FOpid_control_DW.IntegratorSecondOrderLimited__h = 0;
          }
        } else {
          FOpid_control_X.IntegratorSecondOrderLimited__n[1] =
            -8.726646259971647;
        }

        if (FOpid_control_X.IntegratorSecondOrderLimited__n[0] <=
            -0.3490658503988659) {
          FOpid_control_X.IntegratorSecondOrderLimited__n[0] =
            -0.3490658503988659;
          FOpid_control_X.IntegratorSecondOrderLimited__n[1] = 0.0;
          FOpid_control_DW.IntegratorSecondOrderLimited__h = 1;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
            ->solverInfo, true);
        }
        break;

       case 4:
        if (FOpid_control_X.IntegratorSecondOrderLimited__n[1] <
            8.726646259971647) {
          if (FOpid_control_X.IntegratorSecondOrderLimited__n[1] <=
              -8.726646259971647) {
            FOpid_control_DW.IntegratorSecondOrderLimited__h = 3;
            FOpid_control_X.IntegratorSecondOrderLimited__n[1] =
              -8.726646259971647;
          } else {
            FOpid_control_DW.IntegratorSecondOrderLimited__h = 0;
          }
        } else {
          FOpid_control_X.IntegratorSecondOrderLimited__n[1] = 8.726646259971647;
        }

        if (FOpid_control_X.IntegratorSecondOrderLimited__n[0] >=
            0.3490658503988659) {
          FOpid_control_X.IntegratorSecondOrderLimited__n[0] =
            0.3490658503988659;
          FOpid_control_X.IntegratorSecondOrderLimited__n[1] = 0.0;
          FOpid_control_DW.IntegratorSecondOrderLimited__h = 2;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
            ->solverInfo, true);
        }
        break;
      }
    }

    if (FOpid_control_X.IntegratorSecondOrderLimited__n[0] < -0.3490658503988659)
    {
      FOpid_control_B.sina = -0.3490658503988659;
    } else if (FOpid_control_X.IntegratorSecondOrderLimited__n[0] >
               0.3490658503988659) {
      FOpid_control_B.sina = 0.3490658503988659;
    } else {
      FOpid_control_B.sina = FOpid_control_X.IntegratorSecondOrderLimited__n[0];
    }

    /* Sum: '<S26>/Sum3' incorporates:
     *  SecondOrderIntegrator: '<S26>/Integrator, Second-Order Limited'
     */
    FOpid_control_B.Gain2 = FOpid_control_ConstB.Demandlimits_c -
      FOpid_control_B.sina;

    /* Saturate: '<S26>/rate limit*2*zeta//wn' */
    if (FOpid_control_B.Gain2 > 5.235987755982988) {
      FOpid_control_B.Gain2 = 5.235987755982988;
    } else if (FOpid_control_B.Gain2 < -5.235987755982988) {
      FOpid_control_B.Gain2 = -5.235987755982988;
    }

    /* SecondOrderIntegrator: '<S26>/Integrator, Second-Order Limited' */
    if (FOpid_control_X.IntegratorSecondOrderLimited__n[1] < -8.726646259971647)
    {
      FOpid_control_B.sina = -8.726646259971647;
    } else if (FOpid_control_X.IntegratorSecondOrderLimited__n[1] >
               8.726646259971647) {
      FOpid_control_B.sina = 8.726646259971647;
    } else {
      FOpid_control_B.sina = FOpid_control_X.IntegratorSecondOrderLimited__n[1];
    }

    /* Sum: '<S26>/Sum2' incorporates:
     *  Gain: '<S26>/2*zeta * wn'
     *  Saturate: '<S26>/rate limit*2*zeta//wn'
     *  SecondOrderIntegrator: '<S26>/Integrator, Second-Order Limited'
     */
    FOpid_control_B.Sum2_f = FOpid_control_B.Gain2 - 0.6 * FOpid_control_B.sina;

    /* SecondOrderIntegrator: '<S27>/Integrator, Second-Order Limited' */
    if (rtsiIsModeUpdateTimeStep(&(&FOpid_control_M)->solverInfo)) {
      switch (FOpid_control_DW.IntegratorSecondOrderLimited__b) {
       case 0:
        if (FOpid_control_X.IntegratorSecondOrderLimited__a[0] <=
            -0.2617993877991494) {
          FOpid_control_X.IntegratorSecondOrderLimited__a[0] =
            -0.2617993877991494;
          if (FOpid_control_X.IntegratorSecondOrderLimited__a[1] > 0.0) {
            FOpid_control_DW.IntegratorSecondOrderLimited__b = 0;
          } else {
            FOpid_control_X.IntegratorSecondOrderLimited__a[1] = 0.0;
            FOpid_control_DW.IntegratorSecondOrderLimited__b = 1;
          }

          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
            ->solverInfo, true);
        }

        if (FOpid_control_X.IntegratorSecondOrderLimited__a[0] >=
            0.2617993877991494) {
          FOpid_control_X.IntegratorSecondOrderLimited__a[0] =
            0.2617993877991494;
          if (FOpid_control_X.IntegratorSecondOrderLimited__a[1] < 0.0) {
            FOpid_control_DW.IntegratorSecondOrderLimited__b = 0;
          } else {
            FOpid_control_X.IntegratorSecondOrderLimited__a[1] = 0.0;
            FOpid_control_DW.IntegratorSecondOrderLimited__b = 2;
          }

          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
            ->solverInfo, true);
        }

        if (FOpid_control_X.IntegratorSecondOrderLimited__a[1] <=
            -8.726646259971647) {
          FOpid_control_X.IntegratorSecondOrderLimited__a[1] =
            -8.726646259971647;
          FOpid_control_DW.IntegratorSecondOrderLimited__b = 3;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
            ->solverInfo, true);
        }

        if (FOpid_control_X.IntegratorSecondOrderLimited__a[1] >=
            8.726646259971647) {
          FOpid_control_X.IntegratorSecondOrderLimited__a[1] = 8.726646259971647;
          FOpid_control_DW.IntegratorSecondOrderLimited__b = 4;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
            ->solverInfo, true);
        }
        break;

       case 1:
        if (FOpid_control_X.IntegratorSecondOrderLimited__a[0] >
            -0.2617993877991494) {
          if (FOpid_control_X.IntegratorSecondOrderLimited__a[0] >=
              0.2617993877991494) {
            FOpid_control_DW.IntegratorSecondOrderLimited__b = 2;
            FOpid_control_X.IntegratorSecondOrderLimited__a[0] =
              0.2617993877991494;
          } else {
            FOpid_control_DW.IntegratorSecondOrderLimited__b = 0;
          }
        } else {
          FOpid_control_X.IntegratorSecondOrderLimited__a[0] =
            -0.2617993877991494;
          FOpid_control_X.IntegratorSecondOrderLimited__a[1] = 0.0;
        }
        break;

       case 2:
        if (FOpid_control_X.IntegratorSecondOrderLimited__a[0] <
            0.2617993877991494) {
          if (FOpid_control_X.IntegratorSecondOrderLimited__a[0] <=
              -0.2617993877991494) {
            FOpid_control_DW.IntegratorSecondOrderLimited__b = 1;
            FOpid_control_X.IntegratorSecondOrderLimited__a[0] =
              -0.2617993877991494;
          } else {
            FOpid_control_DW.IntegratorSecondOrderLimited__b = 0;
          }
        } else {
          FOpid_control_X.IntegratorSecondOrderLimited__a[0] =
            0.2617993877991494;
          FOpid_control_X.IntegratorSecondOrderLimited__a[1] = 0.0;
        }
        break;

       case 3:
        if (FOpid_control_X.IntegratorSecondOrderLimited__a[1] >
            -8.726646259971647) {
          if (FOpid_control_X.IntegratorSecondOrderLimited__a[1] >=
              8.726646259971647) {
            FOpid_control_DW.IntegratorSecondOrderLimited__b = 4;
            FOpid_control_X.IntegratorSecondOrderLimited__a[1] =
              8.726646259971647;
          } else {
            FOpid_control_DW.IntegratorSecondOrderLimited__b = 0;
          }
        } else {
          FOpid_control_X.IntegratorSecondOrderLimited__a[1] =
            -8.726646259971647;
        }

        if (FOpid_control_X.IntegratorSecondOrderLimited__a[0] <=
            -0.2617993877991494) {
          FOpid_control_X.IntegratorSecondOrderLimited__a[0] =
            -0.2617993877991494;
          FOpid_control_X.IntegratorSecondOrderLimited__a[1] = 0.0;
          FOpid_control_DW.IntegratorSecondOrderLimited__b = 1;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
            ->solverInfo, true);
        }
        break;

       case 4:
        if (FOpid_control_X.IntegratorSecondOrderLimited__a[1] <
            8.726646259971647) {
          if (FOpid_control_X.IntegratorSecondOrderLimited__a[1] <=
              -8.726646259971647) {
            FOpid_control_DW.IntegratorSecondOrderLimited__b = 3;
            FOpid_control_X.IntegratorSecondOrderLimited__a[1] =
              -8.726646259971647;
          } else {
            FOpid_control_DW.IntegratorSecondOrderLimited__b = 0;
          }
        } else {
          FOpid_control_X.IntegratorSecondOrderLimited__a[1] = 8.726646259971647;
        }

        if (FOpid_control_X.IntegratorSecondOrderLimited__a[0] >=
            0.2617993877991494) {
          FOpid_control_X.IntegratorSecondOrderLimited__a[0] =
            0.2617993877991494;
          FOpid_control_X.IntegratorSecondOrderLimited__a[1] = 0.0;
          FOpid_control_DW.IntegratorSecondOrderLimited__b = 2;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
            ->solverInfo, true);
        }
        break;
      }
    }

    if (FOpid_control_X.IntegratorSecondOrderLimited__a[0] < -0.2617993877991494)
    {
      FOpid_control_B.sina = -0.2617993877991494;
    } else if (FOpid_control_X.IntegratorSecondOrderLimited__a[0] >
               0.2617993877991494) {
      FOpid_control_B.sina = 0.2617993877991494;
    } else {
      FOpid_control_B.sina = FOpid_control_X.IntegratorSecondOrderLimited__a[0];
    }

    /* Sum: '<S27>/Sum3' incorporates:
     *  SecondOrderIntegrator: '<S27>/Integrator, Second-Order Limited'
     */
    FOpid_control_B.Gain2 = FOpid_control_ConstB.Demandlimits_n -
      FOpid_control_B.sina;

    /* Saturate: '<S27>/rate limit*2*zeta//wn' */
    if (FOpid_control_B.Gain2 > 5.235987755982988) {
      FOpid_control_B.Gain2 = 5.235987755982988;
    } else if (FOpid_control_B.Gain2 < -5.235987755982988) {
      FOpid_control_B.Gain2 = -5.235987755982988;
    }

    /* SecondOrderIntegrator: '<S27>/Integrator, Second-Order Limited' */
    if (FOpid_control_X.IntegratorSecondOrderLimited__a[1] < -8.726646259971647)
    {
      FOpid_control_B.sina = -8.726646259971647;
    } else if (FOpid_control_X.IntegratorSecondOrderLimited__a[1] >
               8.726646259971647) {
      FOpid_control_B.sina = 8.726646259971647;
    } else {
      FOpid_control_B.sina = FOpid_control_X.IntegratorSecondOrderLimited__a[1];
    }

    /* Sum: '<S27>/Sum2' incorporates:
     *  Gain: '<S27>/2*zeta * wn'
     *  Saturate: '<S27>/rate limit*2*zeta//wn'
     *  SecondOrderIntegrator: '<S27>/Integrator, Second-Order Limited'
     */
    FOpid_control_B.Sum2_b = FOpid_control_B.Gain2 - 0.6 * FOpid_control_B.sina;

    /* SecondOrderIntegrator: '<S28>/Integrator, Second-Order Limited' */
    if (rtsiIsModeUpdateTimeStep(&(&FOpid_control_M)->solverInfo)) {
      switch (FOpid_control_DW.IntegratorSecondOrderLimited__o) {
       case 0:
        if (FOpid_control_X.IntegratorSecondOrderLimited__i[0] <= 0.0) {
          FOpid_control_X.IntegratorSecondOrderLimited__i[0] = 0.0;
          if (FOpid_control_X.IntegratorSecondOrderLimited__i[1] > 0.0) {
            FOpid_control_DW.IntegratorSecondOrderLimited__o = 0;
          } else {
            FOpid_control_X.IntegratorSecondOrderLimited__i[1] = 0.0;
            FOpid_control_DW.IntegratorSecondOrderLimited__o = 1;
          }

          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
            ->solverInfo, true);
        }

        if (FOpid_control_X.IntegratorSecondOrderLimited__i[0] >= 100.0) {
          FOpid_control_X.IntegratorSecondOrderLimited__i[0] = 100.0;
          if (FOpid_control_X.IntegratorSecondOrderLimited__i[1] < 0.0) {
            FOpid_control_DW.IntegratorSecondOrderLimited__o = 0;
          } else {
            FOpid_control_X.IntegratorSecondOrderLimited__i[1] = 0.0;
            FOpid_control_DW.IntegratorSecondOrderLimited__o = 2;
          }

          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
            ->solverInfo, true);
        }

        if (FOpid_control_X.IntegratorSecondOrderLimited__i[1] <=
            -8.726646259971647) {
          FOpid_control_X.IntegratorSecondOrderLimited__i[1] =
            -8.726646259971647;
          FOpid_control_DW.IntegratorSecondOrderLimited__o = 3;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
            ->solverInfo, true);
        }

        if (FOpid_control_X.IntegratorSecondOrderLimited__i[1] >=
            8.726646259971647) {
          FOpid_control_X.IntegratorSecondOrderLimited__i[1] = 8.726646259971647;
          FOpid_control_DW.IntegratorSecondOrderLimited__o = 4;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
            ->solverInfo, true);
        }
        break;

       case 1:
        if (FOpid_control_X.IntegratorSecondOrderLimited__i[0] > 0.0) {
          if (FOpid_control_X.IntegratorSecondOrderLimited__i[0] >= 100.0) {
            FOpid_control_DW.IntegratorSecondOrderLimited__o = 2;
            FOpid_control_X.IntegratorSecondOrderLimited__i[0] = 100.0;
          } else {
            FOpid_control_DW.IntegratorSecondOrderLimited__o = 0;
          }
        } else {
          FOpid_control_X.IntegratorSecondOrderLimited__i[0] = 0.0;
          FOpid_control_X.IntegratorSecondOrderLimited__i[1] = 0.0;
        }
        break;

       case 2:
        if (FOpid_control_X.IntegratorSecondOrderLimited__i[0] < 100.0) {
          if (FOpid_control_X.IntegratorSecondOrderLimited__i[0] <= 0.0) {
            FOpid_control_DW.IntegratorSecondOrderLimited__o = 1;
            FOpid_control_X.IntegratorSecondOrderLimited__i[0] = 0.0;
          } else {
            FOpid_control_DW.IntegratorSecondOrderLimited__o = 0;
          }
        } else {
          FOpid_control_X.IntegratorSecondOrderLimited__i[0] = 100.0;
          FOpid_control_X.IntegratorSecondOrderLimited__i[1] = 0.0;
        }
        break;

       case 3:
        if (FOpid_control_X.IntegratorSecondOrderLimited__i[1] >
            -8.726646259971647) {
          if (FOpid_control_X.IntegratorSecondOrderLimited__i[1] >=
              8.726646259971647) {
            FOpid_control_DW.IntegratorSecondOrderLimited__o = 4;
            FOpid_control_X.IntegratorSecondOrderLimited__i[1] =
              8.726646259971647;
          } else {
            FOpid_control_DW.IntegratorSecondOrderLimited__o = 0;
          }
        } else {
          FOpid_control_X.IntegratorSecondOrderLimited__i[1] =
            -8.726646259971647;
        }

        if (FOpid_control_X.IntegratorSecondOrderLimited__i[0] <= 0.0) {
          FOpid_control_X.IntegratorSecondOrderLimited__i[0] = 0.0;
          FOpid_control_X.IntegratorSecondOrderLimited__i[1] = 0.0;
          FOpid_control_DW.IntegratorSecondOrderLimited__o = 1;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
            ->solverInfo, true);
        }
        break;

       case 4:
        if (FOpid_control_X.IntegratorSecondOrderLimited__i[1] <
            8.726646259971647) {
          if (FOpid_control_X.IntegratorSecondOrderLimited__i[1] <=
              -8.726646259971647) {
            FOpid_control_DW.IntegratorSecondOrderLimited__o = 3;
            FOpid_control_X.IntegratorSecondOrderLimited__i[1] =
              -8.726646259971647;
          } else {
            FOpid_control_DW.IntegratorSecondOrderLimited__o = 0;
          }
        } else {
          FOpid_control_X.IntegratorSecondOrderLimited__i[1] = 8.726646259971647;
        }

        if (FOpid_control_X.IntegratorSecondOrderLimited__i[0] >= 100.0) {
          FOpid_control_X.IntegratorSecondOrderLimited__i[0] = 100.0;
          FOpid_control_X.IntegratorSecondOrderLimited__i[1] = 0.0;
          FOpid_control_DW.IntegratorSecondOrderLimited__o = 2;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
            ->solverInfo, true);
        }
        break;
      }
    }

    if (FOpid_control_X.IntegratorSecondOrderLimited__i[0] < 0.0) {
      FOpid_control_B.sina = 0.0;
    } else if (FOpid_control_X.IntegratorSecondOrderLimited__i[0] > 100.0) {
      FOpid_control_B.sina = 100.0;
    } else {
      FOpid_control_B.sina = FOpid_control_X.IntegratorSecondOrderLimited__i[0];
    }

    /* Sum: '<S28>/Sum3' incorporates:
     *  SecondOrderIntegrator: '<S28>/Integrator, Second-Order Limited'
     */
    FOpid_control_B.Gain2 = FOpid_control_ConstB.Demandlimits_g -
      FOpid_control_B.sina;

    /* Saturate: '<S28>/rate limit*2*zeta//wn' */
    if (FOpid_control_B.Gain2 > 5.235987755982988) {
      FOpid_control_B.Gain2 = 5.235987755982988;
    } else if (FOpid_control_B.Gain2 < -5.235987755982988) {
      FOpid_control_B.Gain2 = -5.235987755982988;
    }

    /* SecondOrderIntegrator: '<S28>/Integrator, Second-Order Limited' */
    if (FOpid_control_X.IntegratorSecondOrderLimited__i[1] < -8.726646259971647)
    {
      FOpid_control_B.sina = -8.726646259971647;
    } else if (FOpid_control_X.IntegratorSecondOrderLimited__i[1] >
               8.726646259971647) {
      FOpid_control_B.sina = 8.726646259971647;
    } else {
      FOpid_control_B.sina = FOpid_control_X.IntegratorSecondOrderLimited__i[1];
    }

    /* Sum: '<S28>/Sum2' incorporates:
     *  Gain: '<S28>/2*zeta * wn'
     *  Saturate: '<S28>/rate limit*2*zeta//wn'
     *  SecondOrderIntegrator: '<S28>/Integrator, Second-Order Limited'
     */
    FOpid_control_B.Sum2_jg = FOpid_control_B.Gain2 - 0.6 * FOpid_control_B.sina;

    /* SecondOrderIntegrator: '<S29>/Integrator, Second-Order Limited' */
    if (rtsiIsModeUpdateTimeStep(&(&FOpid_control_M)->solverInfo)) {
      switch (FOpid_control_DW.IntegratorSecondOrderLimited_h4) {
       case 0:
        if (FOpid_control_X.IntegratorSecondOrderLimited__f[0] <= 0.0) {
          FOpid_control_X.IntegratorSecondOrderLimited__f[0] = 0.0;
          if (FOpid_control_X.IntegratorSecondOrderLimited__f[1] > 0.0) {
            FOpid_control_DW.IntegratorSecondOrderLimited_h4 = 0;
          } else {
            FOpid_control_X.IntegratorSecondOrderLimited__f[1] = 0.0;
            FOpid_control_DW.IntegratorSecondOrderLimited_h4 = 1;
          }

          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
            ->solverInfo, true);
        }

        if (FOpid_control_X.IntegratorSecondOrderLimited__f[0] >= 100.0) {
          FOpid_control_X.IntegratorSecondOrderLimited__f[0] = 100.0;
          if (FOpid_control_X.IntegratorSecondOrderLimited__f[1] < 0.0) {
            FOpid_control_DW.IntegratorSecondOrderLimited_h4 = 0;
          } else {
            FOpid_control_X.IntegratorSecondOrderLimited__f[1] = 0.0;
            FOpid_control_DW.IntegratorSecondOrderLimited_h4 = 2;
          }

          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
            ->solverInfo, true);
        }

        if (FOpid_control_X.IntegratorSecondOrderLimited__f[1] <=
            -8.726646259971647) {
          FOpid_control_X.IntegratorSecondOrderLimited__f[1] =
            -8.726646259971647;
          FOpid_control_DW.IntegratorSecondOrderLimited_h4 = 3;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
            ->solverInfo, true);
        }

        if (FOpid_control_X.IntegratorSecondOrderLimited__f[1] >=
            8.726646259971647) {
          FOpid_control_X.IntegratorSecondOrderLimited__f[1] = 8.726646259971647;
          FOpid_control_DW.IntegratorSecondOrderLimited_h4 = 4;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
            ->solverInfo, true);
        }
        break;

       case 1:
        if (FOpid_control_X.IntegratorSecondOrderLimited__f[0] > 0.0) {
          if (FOpid_control_X.IntegratorSecondOrderLimited__f[0] >= 100.0) {
            FOpid_control_DW.IntegratorSecondOrderLimited_h4 = 2;
            FOpid_control_X.IntegratorSecondOrderLimited__f[0] = 100.0;
          } else {
            FOpid_control_DW.IntegratorSecondOrderLimited_h4 = 0;
          }
        } else {
          FOpid_control_X.IntegratorSecondOrderLimited__f[0] = 0.0;
          FOpid_control_X.IntegratorSecondOrderLimited__f[1] = 0.0;
        }
        break;

       case 2:
        if (FOpid_control_X.IntegratorSecondOrderLimited__f[0] < 100.0) {
          if (FOpid_control_X.IntegratorSecondOrderLimited__f[0] <= 0.0) {
            FOpid_control_DW.IntegratorSecondOrderLimited_h4 = 1;
            FOpid_control_X.IntegratorSecondOrderLimited__f[0] = 0.0;
          } else {
            FOpid_control_DW.IntegratorSecondOrderLimited_h4 = 0;
          }
        } else {
          FOpid_control_X.IntegratorSecondOrderLimited__f[0] = 100.0;
          FOpid_control_X.IntegratorSecondOrderLimited__f[1] = 0.0;
        }
        break;

       case 3:
        if (FOpid_control_X.IntegratorSecondOrderLimited__f[1] >
            -8.726646259971647) {
          if (FOpid_control_X.IntegratorSecondOrderLimited__f[1] >=
              8.726646259971647) {
            FOpid_control_DW.IntegratorSecondOrderLimited_h4 = 4;
            FOpid_control_X.IntegratorSecondOrderLimited__f[1] =
              8.726646259971647;
          } else {
            FOpid_control_DW.IntegratorSecondOrderLimited_h4 = 0;
          }
        } else {
          FOpid_control_X.IntegratorSecondOrderLimited__f[1] =
            -8.726646259971647;
        }

        if (FOpid_control_X.IntegratorSecondOrderLimited__f[0] <= 0.0) {
          FOpid_control_X.IntegratorSecondOrderLimited__f[0] = 0.0;
          FOpid_control_X.IntegratorSecondOrderLimited__f[1] = 0.0;
          FOpid_control_DW.IntegratorSecondOrderLimited_h4 = 1;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
            ->solverInfo, true);
        }
        break;

       case 4:
        if (FOpid_control_X.IntegratorSecondOrderLimited__f[1] <
            8.726646259971647) {
          if (FOpid_control_X.IntegratorSecondOrderLimited__f[1] <=
              -8.726646259971647) {
            FOpid_control_DW.IntegratorSecondOrderLimited_h4 = 3;
            FOpid_control_X.IntegratorSecondOrderLimited__f[1] =
              -8.726646259971647;
          } else {
            FOpid_control_DW.IntegratorSecondOrderLimited_h4 = 0;
          }
        } else {
          FOpid_control_X.IntegratorSecondOrderLimited__f[1] = 8.726646259971647;
        }

        if (FOpid_control_X.IntegratorSecondOrderLimited__f[0] >= 100.0) {
          FOpid_control_X.IntegratorSecondOrderLimited__f[0] = 100.0;
          FOpid_control_X.IntegratorSecondOrderLimited__f[1] = 0.0;
          FOpid_control_DW.IntegratorSecondOrderLimited_h4 = 2;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
            ->solverInfo, true);
        }
        break;
      }
    }

    if (FOpid_control_X.IntegratorSecondOrderLimited__f[0] < 0.0) {
      FOpid_control_B.sina = 0.0;
    } else if (FOpid_control_X.IntegratorSecondOrderLimited__f[0] > 100.0) {
      FOpid_control_B.sina = 100.0;
    } else {
      FOpid_control_B.sina = FOpid_control_X.IntegratorSecondOrderLimited__f[0];
    }

    /* Sum: '<S29>/Sum3' incorporates:
     *  SecondOrderIntegrator: '<S29>/Integrator, Second-Order Limited'
     */
    FOpid_control_B.Gain2 = FOpid_control_ConstB.Demandlimits_p -
      FOpid_control_B.sina;

    /* Saturate: '<S29>/rate limit*2*zeta//wn' */
    if (FOpid_control_B.Gain2 > 5.235987755982988) {
      FOpid_control_B.Gain2 = 5.235987755982988;
    } else if (FOpid_control_B.Gain2 < -5.235987755982988) {
      FOpid_control_B.Gain2 = -5.235987755982988;
    }

    /* SecondOrderIntegrator: '<S29>/Integrator, Second-Order Limited' */
    if (FOpid_control_X.IntegratorSecondOrderLimited__f[1] < -8.726646259971647)
    {
      FOpid_control_B.sina = -8.726646259971647;
    } else if (FOpid_control_X.IntegratorSecondOrderLimited__f[1] >
               8.726646259971647) {
      FOpid_control_B.sina = 8.726646259971647;
    } else {
      FOpid_control_B.sina = FOpid_control_X.IntegratorSecondOrderLimited__f[1];
    }

    /* Sum: '<S29>/Sum2' incorporates:
     *  Gain: '<S29>/2*zeta * wn'
     *  Saturate: '<S29>/rate limit*2*zeta//wn'
     *  SecondOrderIntegrator: '<S29>/Integrator, Second-Order Limited'
     */
    FOpid_control_B.Sum2_ba = FOpid_control_B.Gain2 - 0.6 * FOpid_control_B.sina;
  }

  if (rtmIsMajorTimeStep((&FOpid_control_M))) {
    int32_T i;

    /* Update for Integrator: '<S35>/Integrator' */
    FOpid_control_DW.Integrator_DWORK1 = false;
    if (rtmIsMajorTimeStep((&FOpid_control_M)) &&
        (&FOpid_control_M)->Timing.TaskCounters.TID[1] == 0) {
      /* Update for Memory: '<S35>/Memory2' incorporates:
       *  Integrator: '<S35>/Integrator'
       */
      memcpy(&FOpid_control_DW.Memory2_PreviousInput[0], &FOpid_control_B.x[0],
             12U * sizeof(real_T));

      /* Update for UnitDelay: '<Root>/Unit Delay3' */
      FOpid_control_DW.UnitDelay3_DSTATE = FOpid_control_B.Switch3;

      /* Update for UnitDelay: '<Root>/Unit Delay2' */
      FOpid_control_DW.UnitDelay2_DSTATE = FOpid_control_B.Switch2;

      /* Update for Memory: '<S35>/Memory' incorporates:
       *  Sum: '<S35>/SumOLA'
       */
      FOpid_control_DW.Memory_PreviousInput[0] = FOpid_control_B.SumOLA[0];

      /* Update for Memory: '<S35>/Memory1' incorporates:
       *  Sum: '<S35>/SumOLA1'
       */
      FOpid_control_DW.Memory1_PreviousInput[0] = FOpid_control_B.SumOLA1[0];

      /* Update for Memory: '<S35>/Memory' incorporates:
       *  Sum: '<S35>/SumOLA'
       */
      FOpid_control_DW.Memory_PreviousInput[1] = FOpid_control_B.SumOLA[1];

      /* Update for Memory: '<S35>/Memory1' incorporates:
       *  Sum: '<S35>/SumOLA1'
       */
      FOpid_control_DW.Memory1_PreviousInput[1] = FOpid_control_B.SumOLA1[1];

      /* Update for Memory: '<S35>/Memory' incorporates:
       *  Sum: '<S35>/SumOLA'
       */
      FOpid_control_DW.Memory_PreviousInput[2] = FOpid_control_B.SumOLA[2];

      /* Update for Memory: '<S35>/Memory1' incorporates:
       *  Sum: '<S35>/SumOLA1'
       */
      FOpid_control_DW.Memory1_PreviousInput[2] = FOpid_control_B.SumOLA1[2];

      /* Update for RandomNumber: '<S58>/White Noise' */
      FOpid_control_DW.NextOutput[0] = rt_nrand_Upu32_Yd_f_pw_snf
        (&FOpid_control_DW.RandSeed[0]);
      FOpid_control_DW.NextOutput[1] = rt_nrand_Upu32_Yd_f_pw_snf
        (&FOpid_control_DW.RandSeed[1]);
      FOpid_control_DW.NextOutput[2] = rt_nrand_Upu32_Yd_f_pw_snf
        (&FOpid_control_DW.RandSeed[2]);
      FOpid_control_DW.NextOutput[3] = rt_nrand_Upu32_Yd_f_pw_snf
        (&FOpid_control_DW.RandSeed[3]);

      /* Update for RandomNumber: '<S38>/White Noise' */
      FOpid_control_DW.NextOutput_k = rt_nrand_Upu32_Yd_f_pw_snf
        (&FOpid_control_DW.RandSeed_a);
    }

    /* Update for SecondOrderIntegrator: '<S25>/Integrator, Second-Order Limited' */
    i = FOpid_control_DW.IntegratorSecondOrderLimited_MO;
    if ((((FOpid_control_DW.IntegratorSecondOrderLimited_MO == 1) ||
          (FOpid_control_DW.IntegratorSecondOrderLimited_MO == 3)) &&
         (FOpid_control_B.Sum2_j > 0.0)) ||
        (((FOpid_control_DW.IntegratorSecondOrderLimited_MO == 2) ||
          (FOpid_control_DW.IntegratorSecondOrderLimited_MO == 4)) &&
         (FOpid_control_B.Sum2_j < 0.0))) {
      i = 0;
    }

    if (FOpid_control_DW.IntegratorSecondOrderLimited_MO != i) {
      FOpid_control_DW.IntegratorSecondOrderLimited_MO = i;
      rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
        ->solverInfo, true);
    }

    /* End of Update for SecondOrderIntegrator: '<S25>/Integrator, Second-Order Limited' */

    /* Update for SecondOrderIntegrator: '<S26>/Integrator, Second-Order Limited' */
    i = FOpid_control_DW.IntegratorSecondOrderLimited__h;
    if ((((FOpid_control_DW.IntegratorSecondOrderLimited__h == 1) ||
          (FOpid_control_DW.IntegratorSecondOrderLimited__h == 3)) &&
         (FOpid_control_B.Sum2_f > 0.0)) ||
        (((FOpid_control_DW.IntegratorSecondOrderLimited__h == 2) ||
          (FOpid_control_DW.IntegratorSecondOrderLimited__h == 4)) &&
         (FOpid_control_B.Sum2_f < 0.0))) {
      i = 0;
    }

    if (FOpid_control_DW.IntegratorSecondOrderLimited__h != i) {
      FOpid_control_DW.IntegratorSecondOrderLimited__h = i;
      rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
        ->solverInfo, true);
    }

    /* End of Update for SecondOrderIntegrator: '<S26>/Integrator, Second-Order Limited' */

    /* Update for SecondOrderIntegrator: '<S27>/Integrator, Second-Order Limited' */
    i = FOpid_control_DW.IntegratorSecondOrderLimited__b;
    if ((((FOpid_control_DW.IntegratorSecondOrderLimited__b == 1) ||
          (FOpid_control_DW.IntegratorSecondOrderLimited__b == 3)) &&
         (FOpid_control_B.Sum2_b > 0.0)) ||
        (((FOpid_control_DW.IntegratorSecondOrderLimited__b == 2) ||
          (FOpid_control_DW.IntegratorSecondOrderLimited__b == 4)) &&
         (FOpid_control_B.Sum2_b < 0.0))) {
      i = 0;
    }

    if (FOpid_control_DW.IntegratorSecondOrderLimited__b != i) {
      FOpid_control_DW.IntegratorSecondOrderLimited__b = i;
      rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
        ->solverInfo, true);
    }

    /* End of Update for SecondOrderIntegrator: '<S27>/Integrator, Second-Order Limited' */

    /* Update for SecondOrderIntegrator: '<S28>/Integrator, Second-Order Limited' */
    i = FOpid_control_DW.IntegratorSecondOrderLimited__o;
    if ((((FOpid_control_DW.IntegratorSecondOrderLimited__o == 1) ||
          (FOpid_control_DW.IntegratorSecondOrderLimited__o == 3)) &&
         (FOpid_control_B.Sum2_jg > 0.0)) ||
        (((FOpid_control_DW.IntegratorSecondOrderLimited__o == 2) ||
          (FOpid_control_DW.IntegratorSecondOrderLimited__o == 4)) &&
         (FOpid_control_B.Sum2_jg < 0.0))) {
      i = 0;
    }

    if (FOpid_control_DW.IntegratorSecondOrderLimited__o != i) {
      FOpid_control_DW.IntegratorSecondOrderLimited__o = i;
      rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
        ->solverInfo, true);
    }

    /* End of Update for SecondOrderIntegrator: '<S28>/Integrator, Second-Order Limited' */

    /* Update for SecondOrderIntegrator: '<S29>/Integrator, Second-Order Limited' */
    i = FOpid_control_DW.IntegratorSecondOrderLimited_h4;
    if ((((FOpid_control_DW.IntegratorSecondOrderLimited_h4 == 1) ||
          (FOpid_control_DW.IntegratorSecondOrderLimited_h4 == 3)) &&
         (FOpid_control_B.Sum2_ba > 0.0)) ||
        (((FOpid_control_DW.IntegratorSecondOrderLimited_h4 == 2) ||
          (FOpid_control_DW.IntegratorSecondOrderLimited_h4 == 4)) &&
         (FOpid_control_B.Sum2_ba < 0.0))) {
      i = 0;
    }

    if (FOpid_control_DW.IntegratorSecondOrderLimited_h4 != i) {
      FOpid_control_DW.IntegratorSecondOrderLimited_h4 = i;
      rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_control_M)
        ->solverInfo, true);
    }

    /* End of Update for SecondOrderIntegrator: '<S29>/Integrator, Second-Order Limited' */

    /* ContTimeOutputInconsistentWithStateAtMajorOutputFlag is set, need to run a minor output */
    if (rtmIsMajorTimeStep((&FOpid_control_M))) {
      if (rtsiGetContTimeOutputInconsistentWithStateAtMajorStep
          (&(&FOpid_control_M)->solverInfo)) {
        rtsiSetSimTimeStep(&(&FOpid_control_M)->solverInfo,MINOR_TIME_STEP);
        rtsiSetContTimeOutputInconsistentWithStateAtMajorStep(&(&FOpid_control_M)
          ->solverInfo, false);
        FOpid_control::step();
        rtsiSetSimTimeStep(&(&FOpid_control_M)->solverInfo, MAJOR_TIME_STEP);
      }
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep((&FOpid_control_M))) {
    rt_ertODEUpdateContinuousStates(&(&FOpid_control_M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++(&FOpid_control_M)->Timing.clockTick0)) {
      ++(&FOpid_control_M)->Timing.clockTickH0;
    }

    (&FOpid_control_M)->Timing.t[0] = rtsiGetSolverStopTime(&(&FOpid_control_M
      )->solverInfo);

    {
      /* Update absolute timer for sample time: [0.01s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.01, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      (&FOpid_control_M)->Timing.clockTick1++;
      if (!(&FOpid_control_M)->Timing.clockTick1) {
        (&FOpid_control_M)->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void FOpid_control::FOpid_control_derivatives()
{
  XDot_FOpid_control_T *_rtXdot;
  real_T tmp[2];
  _rtXdot = ((XDot_FOpid_control_T *) (&FOpid_control_M)->derivs);

  /* Derivatives for Integrator: '<S35>/Integrator' */
  if (!FOpid_control_B.Compare) {
    memcpy(&_rtXdot->Integrator_CSTATE[0], &FOpid_control_B.XDOT[0], 12U *
           sizeof(real_T));
  } else {
    /* level reset is active */
    memset(&_rtXdot->Integrator_CSTATE[0], 0, 12U * sizeof(real_T));
  }

  /* End of Derivatives for Integrator: '<S35>/Integrator' */

  /* Derivatives for Enabled SubSystem: '<S49>/Hugw(s)' */
  if (FOpid_control_DW.Hugws_MODE) {
    /* Derivatives for Integrator: '<S62>/ug_p' */
    _rtXdot->ug_p_CSTATE[0] = FOpid_control_B.w_n[0];
    _rtXdot->ug_p_CSTATE[1] = FOpid_control_B.w_n[1];
  } else {
    {
      real_T *dx;
      int_T i1;
      dx = &(((XDot_FOpid_control_T *) (&FOpid_control_M)->derivs)->ug_p_CSTATE
             [0]);
      for (i1=0; i1 < 2; i1++) {
        dx[i1] = 0.0;
      }
    }
  }

  /* End of Derivatives for SubSystem: '<S49>/Hugw(s)' */

  /* Derivatives for Enabled SubSystem: '<S49>/Hvgw(s)' */
  if (FOpid_control_DW.Hvgws_MODE) {
    /* Derivatives for Integrator: '<S63>/vg_p1' */
    _rtXdot->vg_p1_CSTATE[0] = FOpid_control_B.w_g[0];

    /* Derivatives for Integrator: '<S63>/vgw_p2' */
    _rtXdot->vgw_p2_CSTATE[0] = FOpid_control_B.w_e[0];

    /* Derivatives for Integrator: '<S63>/vg_p1' */
    _rtXdot->vg_p1_CSTATE[1] = FOpid_control_B.w_g[1];

    /* Derivatives for Integrator: '<S63>/vgw_p2' */
    _rtXdot->vgw_p2_CSTATE[1] = FOpid_control_B.w_e[1];
  } else {
    {
      real_T *dx;
      int_T i1;
      dx = &(((XDot_FOpid_control_T *) (&FOpid_control_M)->derivs)->
             vg_p1_CSTATE[0]);
      for (i1=0; i1 < 4; i1++) {
        dx[i1] = 0.0;
      }
    }
  }

  /* End of Derivatives for SubSystem: '<S49>/Hvgw(s)' */

  /* Derivatives for Enabled SubSystem: '<S49>/Hwgw(s)' */
  if (FOpid_control_DW.Hwgws_MODE) {
    /* Derivatives for Integrator: '<S64>/wg_p1' */
    _rtXdot->wg_p1_CSTATE[0] = FOpid_control_B.w[0];

    /* Derivatives for Integrator: '<S64>/wg_p2' */
    _rtXdot->wg_p2_CSTATE[0] = FOpid_control_B.w_a[0];

    /* Derivatives for Integrator: '<S64>/wg_p1' */
    _rtXdot->wg_p1_CSTATE[1] = FOpid_control_B.w[1];

    /* Derivatives for Integrator: '<S64>/wg_p2' */
    _rtXdot->wg_p2_CSTATE[1] = FOpid_control_B.w_a[1];
  } else {
    {
      real_T *dx;
      int_T i1;
      dx = &(((XDot_FOpid_control_T *) (&FOpid_control_M)->derivs)->
             wg_p1_CSTATE[0]);
      for (i1=0; i1 < 4; i1++) {
        dx[i1] = 0.0;
      }
    }
  }

  /* End of Derivatives for SubSystem: '<S49>/Hwgw(s)' */

  /* Derivatives for Enabled SubSystem: '<S48>/Hpgw' */
  if (FOpid_control_DW.Hpgw_MODE) {
    /* Derivatives for Integrator: '<S59>/pgw_p' */
    _rtXdot->pgw_p_CSTATE[0] = FOpid_control_B.w_o[0];
    _rtXdot->pgw_p_CSTATE[1] = FOpid_control_B.w_o[1];
  } else {
    {
      real_T *dx;
      int_T i1;
      dx = &(((XDot_FOpid_control_T *) (&FOpid_control_M)->derivs)->
             pgw_p_CSTATE[0]);
      for (i1=0; i1 < 2; i1++) {
        dx[i1] = 0.0;
      }
    }
  }

  /* End of Derivatives for SubSystem: '<S48>/Hpgw' */

  /* Derivatives for Enabled SubSystem: '<S48>/Hqgw' */
  if (FOpid_control_DW.Hqgw_MODE) {
    /* Derivatives for Integrator: '<S60>/qgw_p' */
    _rtXdot->qgw_p_CSTATE[0] = FOpid_control_B.w_e0[0];
    _rtXdot->qgw_p_CSTATE[1] = FOpid_control_B.w_e0[1];
  } else {
    {
      real_T *dx;
      int_T i1;
      dx = &(((XDot_FOpid_control_T *) (&FOpid_control_M)->derivs)->
             qgw_p_CSTATE[0]);
      for (i1=0; i1 < 2; i1++) {
        dx[i1] = 0.0;
      }
    }
  }

  /* End of Derivatives for SubSystem: '<S48>/Hqgw' */

  /* Derivatives for Enabled SubSystem: '<S48>/Hrgw' */
  if (FOpid_control_DW.Hrgw_MODE) {
    /* Derivatives for Integrator: '<S61>/rgw_p' */
    _rtXdot->rgw_p_CSTATE[0] = FOpid_control_B.w_d[0];
    _rtXdot->rgw_p_CSTATE[1] = FOpid_control_B.w_d[1];
  } else {
    {
      real_T *dx;
      int_T i1;
      dx = &(((XDot_FOpid_control_T *) (&FOpid_control_M)->derivs)->
             rgw_p_CSTATE[0]);
      for (i1=0; i1 < 2; i1++) {
        dx[i1] = 0.0;
      }
    }
  }

  /* End of Derivatives for SubSystem: '<S48>/Hrgw' */

  /* Derivatives for TransferFcn: '<S35>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE[0] = 0.0;
  _rtXdot->TransferFcn_CSTATE[0] += -0.898 * FOpid_control_X.TransferFcn_CSTATE
    [0];
  _rtXdot->TransferFcn_CSTATE[1] = 0.0;
  _rtXdot->TransferFcn_CSTATE[0] += -0.806 * FOpid_control_X.TransferFcn_CSTATE
    [1];
  _mm_storeu_pd(&tmp[0], _mm_add_pd(_mm_set_pd(_rtXdot->TransferFcn_CSTATE[0],
    FOpid_control_X.TransferFcn_CSTATE[0]), _mm_set_pd(FOpid_control_B.Output,
    _rtXdot->TransferFcn_CSTATE[1])));
  _rtXdot->TransferFcn_CSTATE[1] = tmp[0];
  _rtXdot->TransferFcn_CSTATE[0] = tmp[1];

  /* Derivatives for TransferFcn: '<S35>/Transfer Fcn1' */
  _rtXdot->TransferFcn1_CSTATE = 0.0;
  _rtXdot->TransferFcn1_CSTATE += -0.01 * FOpid_control_X.TransferFcn1_CSTATE;
  _rtXdot->TransferFcn1_CSTATE += FOpid_control_B.Output;

  /* Derivatives for Integrator: '<S35>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = FOpid_control_B.Power;

  /* Derivatives for SecondOrderIntegrator: '<S25>/Integrator, Second-Order Limited' */
  switch (FOpid_control_DW.IntegratorSecondOrderLimited_MO) {
   case 0:
    _rtXdot->IntegratorSecondOrderLimited_CS[0] =
      FOpid_control_X.IntegratorSecondOrderLimited_CS[1];
    _rtXdot->IntegratorSecondOrderLimited_CS[1] = FOpid_control_B.Sum2_j;
    break;

   case 3:
    _rtXdot->IntegratorSecondOrderLimited_CS[0] =
      FOpid_control_X.IntegratorSecondOrderLimited_CS[1];
    _rtXdot->IntegratorSecondOrderLimited_CS[1] = 0.0;
    break;

   case 4:
    _rtXdot->IntegratorSecondOrderLimited_CS[0] =
      FOpid_control_X.IntegratorSecondOrderLimited_CS[1];
    _rtXdot->IntegratorSecondOrderLimited_CS[1] = 0.0;
    break;

   case 1:
    _rtXdot->IntegratorSecondOrderLimited_CS[0] = 0.0;
    _rtXdot->IntegratorSecondOrderLimited_CS[1] = 0.0;
    break;

   case 2:
    _rtXdot->IntegratorSecondOrderLimited_CS[0] = 0.0;
    _rtXdot->IntegratorSecondOrderLimited_CS[1] = 0.0;
    break;
  }

  /* End of Derivatives for SecondOrderIntegrator: '<S25>/Integrator, Second-Order Limited' */

  /* Derivatives for SecondOrderIntegrator: '<S26>/Integrator, Second-Order Limited' */
  switch (FOpid_control_DW.IntegratorSecondOrderLimited__h) {
   case 0:
    _rtXdot->IntegratorSecondOrderLimited__n[0] =
      FOpid_control_X.IntegratorSecondOrderLimited__n[1];
    _rtXdot->IntegratorSecondOrderLimited__n[1] = FOpid_control_B.Sum2_f;
    break;

   case 3:
    _rtXdot->IntegratorSecondOrderLimited__n[0] =
      FOpid_control_X.IntegratorSecondOrderLimited__n[1];
    _rtXdot->IntegratorSecondOrderLimited__n[1] = 0.0;
    break;

   case 4:
    _rtXdot->IntegratorSecondOrderLimited__n[0] =
      FOpid_control_X.IntegratorSecondOrderLimited__n[1];
    _rtXdot->IntegratorSecondOrderLimited__n[1] = 0.0;
    break;

   case 1:
    _rtXdot->IntegratorSecondOrderLimited__n[0] = 0.0;
    _rtXdot->IntegratorSecondOrderLimited__n[1] = 0.0;
    break;

   case 2:
    _rtXdot->IntegratorSecondOrderLimited__n[0] = 0.0;
    _rtXdot->IntegratorSecondOrderLimited__n[1] = 0.0;
    break;
  }

  /* End of Derivatives for SecondOrderIntegrator: '<S26>/Integrator, Second-Order Limited' */

  /* Derivatives for SecondOrderIntegrator: '<S27>/Integrator, Second-Order Limited' */
  switch (FOpid_control_DW.IntegratorSecondOrderLimited__b) {
   case 0:
    _rtXdot->IntegratorSecondOrderLimited__a[0] =
      FOpid_control_X.IntegratorSecondOrderLimited__a[1];
    _rtXdot->IntegratorSecondOrderLimited__a[1] = FOpid_control_B.Sum2_b;
    break;

   case 3:
    _rtXdot->IntegratorSecondOrderLimited__a[0] =
      FOpid_control_X.IntegratorSecondOrderLimited__a[1];
    _rtXdot->IntegratorSecondOrderLimited__a[1] = 0.0;
    break;

   case 4:
    _rtXdot->IntegratorSecondOrderLimited__a[0] =
      FOpid_control_X.IntegratorSecondOrderLimited__a[1];
    _rtXdot->IntegratorSecondOrderLimited__a[1] = 0.0;
    break;

   case 1:
    _rtXdot->IntegratorSecondOrderLimited__a[0] = 0.0;
    _rtXdot->IntegratorSecondOrderLimited__a[1] = 0.0;
    break;

   case 2:
    _rtXdot->IntegratorSecondOrderLimited__a[0] = 0.0;
    _rtXdot->IntegratorSecondOrderLimited__a[1] = 0.0;
    break;
  }

  /* End of Derivatives for SecondOrderIntegrator: '<S27>/Integrator, Second-Order Limited' */

  /* Derivatives for SecondOrderIntegrator: '<S28>/Integrator, Second-Order Limited' */
  switch (FOpid_control_DW.IntegratorSecondOrderLimited__o) {
   case 0:
    _rtXdot->IntegratorSecondOrderLimited__i[0] =
      FOpid_control_X.IntegratorSecondOrderLimited__i[1];
    _rtXdot->IntegratorSecondOrderLimited__i[1] = FOpid_control_B.Sum2_jg;
    break;

   case 3:
    _rtXdot->IntegratorSecondOrderLimited__i[0] =
      FOpid_control_X.IntegratorSecondOrderLimited__i[1];
    _rtXdot->IntegratorSecondOrderLimited__i[1] = 0.0;
    break;

   case 4:
    _rtXdot->IntegratorSecondOrderLimited__i[0] =
      FOpid_control_X.IntegratorSecondOrderLimited__i[1];
    _rtXdot->IntegratorSecondOrderLimited__i[1] = 0.0;
    break;

   case 1:
    _rtXdot->IntegratorSecondOrderLimited__i[0] = 0.0;
    _rtXdot->IntegratorSecondOrderLimited__i[1] = 0.0;
    break;

   case 2:
    _rtXdot->IntegratorSecondOrderLimited__i[0] = 0.0;
    _rtXdot->IntegratorSecondOrderLimited__i[1] = 0.0;
    break;
  }

  /* End of Derivatives for SecondOrderIntegrator: '<S28>/Integrator, Second-Order Limited' */

  /* Derivatives for SecondOrderIntegrator: '<S29>/Integrator, Second-Order Limited' */
  switch (FOpid_control_DW.IntegratorSecondOrderLimited_h4) {
   case 0:
    _rtXdot->IntegratorSecondOrderLimited__f[0] =
      FOpid_control_X.IntegratorSecondOrderLimited__f[1];
    _rtXdot->IntegratorSecondOrderLimited__f[1] = FOpid_control_B.Sum2_ba;
    break;

   case 3:
    _rtXdot->IntegratorSecondOrderLimited__f[0] =
      FOpid_control_X.IntegratorSecondOrderLimited__f[1];
    _rtXdot->IntegratorSecondOrderLimited__f[1] = 0.0;
    break;

   case 4:
    _rtXdot->IntegratorSecondOrderLimited__f[0] =
      FOpid_control_X.IntegratorSecondOrderLimited__f[1];
    _rtXdot->IntegratorSecondOrderLimited__f[1] = 0.0;
    break;

   case 1:
    _rtXdot->IntegratorSecondOrderLimited__f[0] = 0.0;
    _rtXdot->IntegratorSecondOrderLimited__f[1] = 0.0;
    break;

   case 2:
    _rtXdot->IntegratorSecondOrderLimited__f[0] = 0.0;
    _rtXdot->IntegratorSecondOrderLimited__f[1] = 0.0;
    break;
  }

  /* End of Derivatives for SecondOrderIntegrator: '<S29>/Integrator, Second-Order Limited' */
}

/* Model initialize function */
void FOpid_control::initialize()
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&FOpid_control_M)->solverInfo, &(&FOpid_control_M)
                          ->Timing.simTimeStep);
    rtsiSetTPtr(&(&FOpid_control_M)->solverInfo, &rtmGetTPtr((&FOpid_control_M)));
    rtsiSetStepSizePtr(&(&FOpid_control_M)->solverInfo, &(&FOpid_control_M)
                       ->Timing.stepSize0);
    rtsiSetdXPtr(&(&FOpid_control_M)->solverInfo, &(&FOpid_control_M)->derivs);
    rtsiSetContStatesPtr(&(&FOpid_control_M)->solverInfo, (real_T **)
                         &(&FOpid_control_M)->contStates);
    rtsiSetNumContStatesPtr(&(&FOpid_control_M)->solverInfo, &(&FOpid_control_M
      )->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&FOpid_control_M)->solverInfo,
      &(&FOpid_control_M)->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&FOpid_control_M)->solverInfo,
      &(&FOpid_control_M)->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&FOpid_control_M)->solverInfo,
      &(&FOpid_control_M)->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&(&FOpid_control_M)->solverInfo, (boolean_T**)
      &(&FOpid_control_M)->contStateDisabled);
    rtsiSetErrorStatusPtr(&(&FOpid_control_M)->solverInfo, (&rtmGetErrorStatus((
      &FOpid_control_M))));
    rtsiSetRTModelPtr(&(&FOpid_control_M)->solverInfo, (&FOpid_control_M));
  }

  rtsiSetSimTimeStep(&(&FOpid_control_M)->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&(&FOpid_control_M)->solverInfo, false);
  rtsiSetIsContModeFrozen(&(&FOpid_control_M)->solverInfo, false);
  (&FOpid_control_M)->intgData.y = (&FOpid_control_M)->odeY;
  (&FOpid_control_M)->intgData.f[0] = (&FOpid_control_M)->odeF[0];
  (&FOpid_control_M)->intgData.f[1] = (&FOpid_control_M)->odeF[1];
  (&FOpid_control_M)->intgData.f[2] = (&FOpid_control_M)->odeF[2];
  (&FOpid_control_M)->intgData.f[3] = (&FOpid_control_M)->odeF[3];
  (&FOpid_control_M)->contStates = ((X_FOpid_control_T *) &FOpid_control_X);
  (&FOpid_control_M)->contStateDisabled = ((XDis_FOpid_control_T *)
    &FOpid_control_XDis);
  (&FOpid_control_M)->Timing.tStart = (0.0);
  rtsiSetSolverData(&(&FOpid_control_M)->solverInfo, static_cast<void *>
                    (&(&FOpid_control_M)->intgData));
  rtsiSetSolverName(&(&FOpid_control_M)->solverInfo,"ode4");
  rtmSetTPtr((&FOpid_control_M), &(&FOpid_control_M)->Timing.tArray[0]);
  (&FOpid_control_M)->Timing.stepSize0 = 0.01;
  rtmSetFirstInitCond((&FOpid_control_M), 1);

  {
    rmw_qos_profile_t qos_profile;
    int32_T i;
    static const char_T b_zeroDelimTopic[18] = "/ekranoplano/odom";

    /* Start for InitialCondition: '<S35>/IC' */
    memcpy(&FOpid_control_B.IC[0], &FOpid_control_ConstP.pooled14[0], 12U *
           sizeof(real_T));

    /* Start for InitialCondition: '<S35>/IC' */
    FOpid_control_DW.IC_FirstOutputTime = true;

    /* Start for MATLABSystem: '<Root>/Coordinate Transformation Conversion' */
    FOpid_control_DW.objisempty_d = true;
    FOpid_control_DW.obj_c.isInitialized = 1;

    /* Start for MATLABSystem: '<S30>/SinkBlock' */
    FOpid_control_DW.obj_i.QOSAvoidROSNamespaceConventions = false;
    FOpid_control_DW.obj_i.matlabCodegenIsDeleted = false;
    FOpid_control_DW.objisempty_m = true;
    FOpid_control_DW.obj_i.isSetupComplete = false;
    FOpid_control_DW.obj_i.isInitialized = 1;
    FOpid_contr_Publisher_setupImpl(&FOpid_control_DW.obj_i);
    FOpid_control_DW.obj_i.isSetupComplete = true;

    /* Start for MATLABSystem: '<S31>/SinkBlock' */
    FOpid_control_DW.obj_o.QOSAvoidROSNamespaceConventions = false;
    FOpid_control_DW.obj_o.matlabCodegenIsDeleted = false;
    FOpid_control_DW.objisempty_ev = true;
    FOpid_control_DW.obj_o.isSetupComplete = false;
    FOpid_control_DW.obj_o.isInitialized = 1;
    qos_profile = FO_ROS2PubSubBase_setQOSProfile(rmw_qos_profile_default, 10.0,
      (rtInf), (rtInf), (rtInf),
      FOpid_control_DW.obj_o.QOSAvoidROSNamespaceConventions);
    for (i = 0; i < 18; i++) {
      FOpid_control_B.b_zeroDelimTopic_p[i] = b_zeroDelimTopic[i];
    }

    Pub_FOpid_control_697.createPublisher(&FOpid_control_B.b_zeroDelimTopic_p[0],
      qos_profile);
    FOpid_control_DW.obj_o.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S31>/SinkBlock' */

    /* Start for MATLABSystem: '<S32>/SinkBlock' */
    FOpid_control_DW.obj_dl.QOSAvoidROSNamespaceConventions = false;
    FOpid_control_DW.obj_dl.matlabCodegenIsDeleted = false;
    FOpid_control_DW.objisempty_ld = true;
    FOpid_control_DW.obj_dl.isSetupComplete = false;
    FOpid_control_DW.obj_dl.isInitialized = 1;
    FOpid_con_Publisher_setupImpl_i(&FOpid_control_DW.obj_dl);
    FOpid_control_DW.obj_dl.isSetupComplete = true;

    /* Start for MATLABSystem: '<S33>/SinkBlock' */
    FOpid_control_DW.obj_d.QOSAvoidROSNamespaceConventions = false;
    FOpid_control_DW.obj_d.matlabCodegenIsDeleted = false;
    FOpid_control_DW.objisempty_cr = true;
    FOpid_control_DW.obj_d.isSetupComplete = false;
    FOpid_control_DW.obj_d.isInitialized = 1;
    FOpid_co_Publisher_setupImpl_ie(&FOpid_control_DW.obj_d);
    FOpid_control_DW.obj_d.isSetupComplete = true;

    /* Start for MATLABSystem: '<S36>/SourceBlock' */
    FOpid_control_DW.obj_m.QOSAvoidROSNamespaceConventions = false;
    FOpid_control_DW.obj_m.matlabCodegenIsDeleted = false;
    FOpid_control_DW.objisempty_g = true;
    FOpid_control_DW.obj_m.isSetupComplete = false;
    FOpid_control_DW.obj_m.isInitialized = 1;
    FOpid_Subscriber_setupImpl_ieih(&FOpid_control_DW.obj_m);
    FOpid_control_DW.obj_m.isSetupComplete = true;

    /* Start for MATLABSystem: '<S37>/SourceBlock' */
    FOpid_control_DW.obj_k.QOSAvoidROSNamespaceConventions = false;
    FOpid_control_DW.obj_k.matlabCodegenIsDeleted = false;
    FOpid_control_DW.objisempty = true;
    FOpid_control_DW.obj_k.isSetupComplete = false;
    FOpid_control_DW.obj_k.isInitialized = 1;
    FOpi_Subscriber_setupImpl_ieihd(&FOpid_control_DW.obj_k);
    FOpid_control_DW.obj_k.isSetupComplete = true;

    /* Start for Atomic SubSystem: '<Root>/Call Service' */
    /* Start for MATLABSystem: '<S6>/ServiceCaller' */
    FOpid_control_DW.obj.QOSAvoidROSNamespaceConventions = false;
    FOpid_control_DW.obj.matlabCodegenIsDeleted = false;
    FOpid_control_DW.objisempty_f = true;
    FOpid_control_DW.obj.isSetupComplete = false;
    FOpid_control_DW.obj.isInitialized = 1;
    FOpid_c_ServiceCaller_setupImpl(&FOpid_control_DW.obj);
    FOpid_control_DW.obj.isSetupComplete = true;

    /* End of Start for SubSystem: '<Root>/Call Service' */

    /* Start for Enabled SubSystem: '<S49>/Hugw(s)' */
    (void) memset(&(FOpid_control_XDis.ug_p_CSTATE), 1,
                  2*sizeof(boolean_T));

    /* End of Start for SubSystem: '<S49>/Hugw(s)' */

    /* Start for Enabled SubSystem: '<S49>/Hvgw(s)' */
    (void) memset(&(FOpid_control_XDis.vg_p1_CSTATE), 1,
                  4*sizeof(boolean_T));

    /* End of Start for SubSystem: '<S49>/Hvgw(s)' */

    /* Start for Enabled SubSystem: '<S49>/Hwgw(s)' */
    (void) memset(&(FOpid_control_XDis.wg_p1_CSTATE), 1,
                  4*sizeof(boolean_T));

    /* End of Start for SubSystem: '<S49>/Hwgw(s)' */

    /* Start for If: '<S54>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
    FOpid_control_DW.ifHeightMaxlowaltitudeelseifHei = -1;

    /* Start for MATLABSystem: '<S46>/SourceBlock' */
    FOpid_control_DW.obj_h.QOSAvoidROSNamespaceConventions = false;
    FOpid_control_DW.obj_h.matlabCodegenIsDeleted = false;
    FOpid_control_DW.objisempty_a = true;
    FOpid_control_DW.obj_h.isSetupComplete = false;
    FOpid_control_DW.obj_h.isInitialized = 1;
    FOpid__Subscriber_setupImpl_iei(&FOpid_control_DW.obj_h);
    FOpid_control_DW.obj_h.isSetupComplete = true;

    /* Start for Enabled SubSystem: '<S48>/Hpgw' */
    (void) memset(&(FOpid_control_XDis.pgw_p_CSTATE), 1,
                  2*sizeof(boolean_T));

    /* End of Start for SubSystem: '<S48>/Hpgw' */

    /* Start for Enabled SubSystem: '<S48>/Hqgw' */
    (void) memset(&(FOpid_control_XDis.qgw_p_CSTATE), 1,
                  2*sizeof(boolean_T));

    /* End of Start for SubSystem: '<S48>/Hqgw' */

    /* Start for Enabled SubSystem: '<S48>/Hrgw' */
    (void) memset(&(FOpid_control_XDis.rgw_p_CSTATE), 1,
                  2*sizeof(boolean_T));

    /* End of Start for SubSystem: '<S48>/Hrgw' */

    /* Start for If: '<S53>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
    FOpid_control_DW.ifHeightMaxlowaltitudeelseifH_a = -1;

    /* Start for MATLABSystem: '<S43>/SourceBlock' */
    FOpid_control_DW.obj_h4.QOSAvoidROSNamespaceConventions = false;
    FOpid_control_DW.obj_h4.matlabCodegenIsDeleted = false;
    FOpid_control_DW.objisempty_c = true;
    FOpid_control_DW.obj_h4.isSetupComplete = false;
    FOpid_control_DW.obj_h4.isInitialized = 1;
    FOpid_cont_Subscriber_setupImpl(&FOpid_control_DW.obj_h4);
    FOpid_control_DW.obj_h4.isSetupComplete = true;

    /* Start for MATLABSystem: '<S44>/SourceBlock' */
    FOpid_control_DW.obj_hy.QOSAvoidROSNamespaceConventions = false;
    FOpid_control_DW.obj_hy.matlabCodegenIsDeleted = false;
    FOpid_control_DW.objisempty_l = true;
    FOpid_control_DW.obj_hy.isSetupComplete = false;
    FOpid_control_DW.obj_hy.isInitialized = 1;
    FOpid_co_Subscriber_setupImpl_i(&FOpid_control_DW.obj_hy);
    FOpid_control_DW.obj_hy.isSetupComplete = true;

    /* Start for MATLABSystem: '<S45>/SourceBlock' */
    FOpid_control_DW.obj_p.QOSAvoidROSNamespaceConventions = false;
    FOpid_control_DW.obj_p.matlabCodegenIsDeleted = false;
    FOpid_control_DW.objisempty_e = true;
    FOpid_control_DW.obj_p.isSetupComplete = false;
    FOpid_control_DW.obj_p.isInitialized = 1;
    FOpid_c_Subscriber_setupImpl_ie(&FOpid_control_DW.obj_p);
    FOpid_control_DW.obj_p.isSetupComplete = true;
  }

  FOpid_control_PrevZCX.Integrator_Reset_ZCE = UNINITIALIZED_ZCSIG;

  /* InitializeConditions for Memory: '<S35>/Memory2' */
  memcpy(&FOpid_control_DW.Memory2_PreviousInput[0],
         &FOpid_control_ConstP.pooled14[0], 12U * sizeof(real_T));

  /* InitializeConditions for Integrator: '<S35>/Integrator' */
  if (rtmIsFirstInitCond((&FOpid_control_M))) {
    FOpid_control_X.Integrator_CSTATE[0] = 0.1;
    memset(&FOpid_control_X.Integrator_CSTATE[1], 0, 10U * sizeof(real_T));
    FOpid_control_X.Integrator_CSTATE[11] = -0.1;
  }

  FOpid_control_DW.Integrator_DWORK1 = true;

  /* End of InitializeConditions for Integrator: '<S35>/Integrator' */

  /* InitializeConditions for UnitDelay: '<Root>/Unit Delay3' */
  FOpid_control_DW.UnitDelay3_DSTATE = 0.8;

  /* InitializeConditions for RandomNumber: '<S58>/White Noise' */
  FOpid_control_DW.RandSeed[0] = 1529675776U;
  FOpid_control_DW.NextOutput[0] = rt_nrand_Upu32_Yd_f_pw_snf
    (&FOpid_control_DW.RandSeed[0]);
  FOpid_control_DW.RandSeed[1] = 1529741312U;
  FOpid_control_DW.NextOutput[1] = rt_nrand_Upu32_Yd_f_pw_snf
    (&FOpid_control_DW.RandSeed[1]);
  FOpid_control_DW.RandSeed[2] = 1529806848U;
  FOpid_control_DW.NextOutput[2] = rt_nrand_Upu32_Yd_f_pw_snf
    (&FOpid_control_DW.RandSeed[2]);
  FOpid_control_DW.RandSeed[3] = 1529872384U;
  FOpid_control_DW.NextOutput[3] = rt_nrand_Upu32_Yd_f_pw_snf
    (&FOpid_control_DW.RandSeed[3]);

  /* InitializeConditions for TransferFcn: '<S35>/Transfer Fcn' */
  FOpid_control_X.TransferFcn_CSTATE[0] = 0.0;
  FOpid_control_X.TransferFcn_CSTATE[1] = 0.0;

  /* InitializeConditions for RandomNumber: '<S38>/White Noise' */
  FOpid_control_DW.RandSeed_a = 1529675776U;
  FOpid_control_DW.NextOutput_k = rt_nrand_Upu32_Yd_f_pw_snf
    (&FOpid_control_DW.RandSeed_a);

  /* InitializeConditions for TransferFcn: '<S35>/Transfer Fcn1' */
  FOpid_control_X.TransferFcn1_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S35>/Integrator1' */
  FOpid_control_X.Integrator1_CSTATE = 0.0;

  /* InitializeConditions for SecondOrderIntegrator: '<S25>/Integrator, Second-Order Limited' */
  FOpid_control_X.IntegratorSecondOrderLimited_CS[0] = 0.0;
  FOpid_control_X.IntegratorSecondOrderLimited_CS[1] = 0.0;

  /* InitializeConditions for SecondOrderIntegrator: '<S26>/Integrator, Second-Order Limited' */
  FOpid_control_X.IntegratorSecondOrderLimited__n[0] = 0.0;
  FOpid_control_X.IntegratorSecondOrderLimited__n[1] = 0.0;

  /* InitializeConditions for SecondOrderIntegrator: '<S27>/Integrator, Second-Order Limited' */
  FOpid_control_X.IntegratorSecondOrderLimited__a[0] = 0.0;
  FOpid_control_X.IntegratorSecondOrderLimited__a[1] = 0.0;

  /* InitializeConditions for SecondOrderIntegrator: '<S28>/Integrator, Second-Order Limited' */
  FOpid_control_X.IntegratorSecondOrderLimited__i[0] = 0.0;
  FOpid_control_X.IntegratorSecondOrderLimited__i[1] = 0.0;

  /* InitializeConditions for SecondOrderIntegrator: '<S29>/Integrator, Second-Order Limited' */
  FOpid_control_X.IntegratorSecondOrderLimited__f[0] = 0.0;
  FOpid_control_X.IntegratorSecondOrderLimited__f[1] = 0.0;

  /* SystemInitialize for Enabled SubSystem: '<S36>/Enabled Subsystem' */
  FOpid_c_EnabledSubsystem_g_Init(&FOpid_control_B.EnabledSubsystem_b);

  /* End of SystemInitialize for SubSystem: '<S36>/Enabled Subsystem' */

  /* SystemInitialize for Enabled SubSystem: '<S37>/Enabled Subsystem' */
  FOpid_c_EnabledSubsystem_g_Init(&FOpid_control_B.EnabledSubsystem_a);

  /* End of SystemInitialize for SubSystem: '<S37>/Enabled Subsystem' */

  /* SystemInitialize for Enabled SubSystem: '<S49>/Hugw(s)' */
  /* InitializeConditions for Integrator: '<S62>/ug_p' */
  FOpid_control_X.ug_p_CSTATE[0] = 0.0;

  /* End of SystemInitialize for SubSystem: '<S49>/Hugw(s)' */

  /* SystemInitialize for Enabled SubSystem: '<S49>/Hvgw(s)' */
  /* InitializeConditions for Integrator: '<S63>/vg_p1' */
  FOpid_control_X.vg_p1_CSTATE[0] = 0.0;

  /* InitializeConditions for Integrator: '<S63>/vgw_p2' */
  FOpid_control_X.vgw_p2_CSTATE[0] = 0.0;

  /* End of SystemInitialize for SubSystem: '<S49>/Hvgw(s)' */

  /* SystemInitialize for Enabled SubSystem: '<S49>/Hwgw(s)' */
  /* InitializeConditions for Integrator: '<S64>/wg_p1' */
  FOpid_control_X.wg_p1_CSTATE[0] = 0.0;

  /* InitializeConditions for Integrator: '<S64>/wg_p2' */
  FOpid_control_X.wg_p2_CSTATE[0] = 0.0;

  /* End of SystemInitialize for SubSystem: '<S49>/Hwgw(s)' */

  /* SystemInitialize for Enabled SubSystem: '<S49>/Hugw(s)' */
  /* InitializeConditions for Integrator: '<S62>/ug_p' */
  FOpid_control_X.ug_p_CSTATE[1] = 0.0;

  /* End of SystemInitialize for SubSystem: '<S49>/Hugw(s)' */

  /* SystemInitialize for Enabled SubSystem: '<S49>/Hvgw(s)' */
  /* InitializeConditions for Integrator: '<S63>/vg_p1' */
  FOpid_control_X.vg_p1_CSTATE[1] = 0.0;

  /* InitializeConditions for Integrator: '<S63>/vgw_p2' */
  FOpid_control_X.vgw_p2_CSTATE[1] = 0.0;

  /* End of SystemInitialize for SubSystem: '<S49>/Hvgw(s)' */

  /* SystemInitialize for Enabled SubSystem: '<S49>/Hwgw(s)' */
  /* InitializeConditions for Integrator: '<S64>/wg_p1' */
  FOpid_control_X.wg_p1_CSTATE[1] = 0.0;

  /* InitializeConditions for Integrator: '<S64>/wg_p2' */
  FOpid_control_X.wg_p2_CSTATE[1] = 0.0;

  /* End of SystemInitialize for SubSystem: '<S49>/Hwgw(s)' */

  /* SystemInitialize for Enabled SubSystem: '<S46>/Enabled Subsystem' */
  FOpid_con_EnabledSubsystem_Init(&FOpid_control_B.EnabledSubsystem_pt);

  /* End of SystemInitialize for SubSystem: '<S46>/Enabled Subsystem' */

  /* SystemInitialize for Enabled SubSystem: '<S48>/Hpgw' */
  /* InitializeConditions for Integrator: '<S59>/pgw_p' */
  FOpid_control_X.pgw_p_CSTATE[0] = 0.0;

  /* End of SystemInitialize for SubSystem: '<S48>/Hpgw' */

  /* SystemInitialize for Enabled SubSystem: '<S48>/Hqgw' */
  /* InitializeConditions for Integrator: '<S60>/qgw_p' */
  FOpid_control_X.qgw_p_CSTATE[0] = 0.0;

  /* End of SystemInitialize for SubSystem: '<S48>/Hqgw' */

  /* SystemInitialize for Enabled SubSystem: '<S48>/Hrgw' */
  /* InitializeConditions for Integrator: '<S61>/rgw_p' */
  FOpid_control_X.rgw_p_CSTATE[0] = 0.0;

  /* End of SystemInitialize for SubSystem: '<S48>/Hrgw' */

  /* SystemInitialize for Enabled SubSystem: '<S48>/Hpgw' */
  /* InitializeConditions for Integrator: '<S59>/pgw_p' */
  FOpid_control_X.pgw_p_CSTATE[1] = 0.0;

  /* End of SystemInitialize for SubSystem: '<S48>/Hpgw' */

  /* SystemInitialize for Enabled SubSystem: '<S48>/Hqgw' */
  /* InitializeConditions for Integrator: '<S60>/qgw_p' */
  FOpid_control_X.qgw_p_CSTATE[1] = 0.0;

  /* End of SystemInitialize for SubSystem: '<S48>/Hqgw' */

  /* SystemInitialize for Enabled SubSystem: '<S48>/Hrgw' */
  /* InitializeConditions for Integrator: '<S61>/rgw_p' */
  FOpid_control_X.rgw_p_CSTATE[1] = 0.0;

  /* End of SystemInitialize for SubSystem: '<S48>/Hrgw' */

  /* SystemInitialize for Enabled SubSystem: '<S43>/Enabled Subsystem' */
  FOpid_con_EnabledSubsystem_Init(&FOpid_control_B.EnabledSubsystem);

  /* End of SystemInitialize for SubSystem: '<S43>/Enabled Subsystem' */

  /* SystemInitialize for Enabled SubSystem: '<S44>/Enabled Subsystem' */
  FOpid_c_EnabledSubsystem_g_Init(&FOpid_control_B.EnabledSubsystem_k);

  /* End of SystemInitialize for SubSystem: '<S44>/Enabled Subsystem' */

  /* SystemInitialize for Enabled SubSystem: '<S45>/Enabled Subsystem' */
  FOpid_c_EnabledSubsystem_g_Init(&FOpid_control_B.EnabledSubsystem_p);

  /* End of SystemInitialize for SubSystem: '<S45>/Enabled Subsystem' */

  /* set "at time zero" to false */
  if (rtmIsFirstInitCond((&FOpid_control_M))) {
    rtmSetFirstInitCond((&FOpid_control_M), 0);
  }
}

/* Model terminate function */
void FOpid_control::terminate()
{
  /* Terminate for MATLABSystem: '<S30>/SinkBlock' */
  if (!FOpid_control_DW.obj_i.matlabCodegenIsDeleted) {
    FOpid_control_DW.obj_i.matlabCodegenIsDeleted = true;
    if ((FOpid_control_DW.obj_i.isInitialized == 1) &&
        FOpid_control_DW.obj_i.isSetupComplete) {
      Pub_FOpid_control_548.resetPublisherPtr();//();
    }
  }

  /* End of Terminate for MATLABSystem: '<S30>/SinkBlock' */

  /* Terminate for MATLABSystem: '<S31>/SinkBlock' */
  if (!FOpid_control_DW.obj_o.matlabCodegenIsDeleted) {
    FOpid_control_DW.obj_o.matlabCodegenIsDeleted = true;
    if ((FOpid_control_DW.obj_o.isInitialized == 1) &&
        FOpid_control_DW.obj_o.isSetupComplete) {
      Pub_FOpid_control_697.resetPublisherPtr();//();
    }
  }

  /* End of Terminate for MATLABSystem: '<S31>/SinkBlock' */

  /* Terminate for MATLABSystem: '<S32>/SinkBlock' */
  if (!FOpid_control_DW.obj_dl.matlabCodegenIsDeleted) {
    FOpid_control_DW.obj_dl.matlabCodegenIsDeleted = true;
    if ((FOpid_control_DW.obj_dl.isInitialized == 1) &&
        FOpid_control_DW.obj_dl.isSetupComplete) {
      Pub_FOpid_control_811.resetPublisherPtr();//();
    }
  }

  /* End of Terminate for MATLABSystem: '<S32>/SinkBlock' */

  /* Terminate for MATLABSystem: '<S33>/SinkBlock' */
  if (!FOpid_control_DW.obj_d.matlabCodegenIsDeleted) {
    FOpid_control_DW.obj_d.matlabCodegenIsDeleted = true;
    if ((FOpid_control_DW.obj_d.isInitialized == 1) &&
        FOpid_control_DW.obj_d.isSetupComplete) {
      Pub_FOpid_control_835.resetPublisherPtr();//();
    }
  }

  /* End of Terminate for MATLABSystem: '<S33>/SinkBlock' */

  /* Terminate for MATLABSystem: '<S36>/SourceBlock' */
  if (!FOpid_control_DW.obj_m.matlabCodegenIsDeleted) {
    FOpid_control_DW.obj_m.matlabCodegenIsDeleted = true;
    if ((FOpid_control_DW.obj_m.isInitialized == 1) &&
        FOpid_control_DW.obj_m.isSetupComplete) {
      Sub_FOpid_control_435.resetSubscriberPtr();//();
    }
  }

  /* End of Terminate for MATLABSystem: '<S36>/SourceBlock' */

  /* Terminate for MATLABSystem: '<S37>/SourceBlock' */
  if (!FOpid_control_DW.obj_k.matlabCodegenIsDeleted) {
    FOpid_control_DW.obj_k.matlabCodegenIsDeleted = true;
    if ((FOpid_control_DW.obj_k.isInitialized == 1) &&
        FOpid_control_DW.obj_k.isSetupComplete) {
      Sub_FOpid_control_377.resetSubscriberPtr();//();
    }
  }

  /* End of Terminate for MATLABSystem: '<S37>/SourceBlock' */

  /* Terminate for Atomic SubSystem: '<Root>/Call Service' */
  /* Terminate for MATLABSystem: '<S6>/ServiceCaller' */
  if (!FOpid_control_DW.obj.matlabCodegenIsDeleted) {
    FOpid_control_DW.obj.matlabCodegenIsDeleted = true;
    if ((FOpid_control_DW.obj.isInitialized == 1) &&
        FOpid_control_DW.obj.isSetupComplete) {
      ServCall_FOpid_control_326.resetSvcClientPtr();//();
    }
  }

  /* End of Terminate for MATLABSystem: '<S6>/ServiceCaller' */
  /* End of Terminate for SubSystem: '<Root>/Call Service' */

  /* Terminate for MATLABSystem: '<S46>/SourceBlock' */
  if (!FOpid_control_DW.obj_h.matlabCodegenIsDeleted) {
    FOpid_control_DW.obj_h.matlabCodegenIsDeleted = true;
    if ((FOpid_control_DW.obj_h.isInitialized == 1) &&
        FOpid_control_DW.obj_h.isSetupComplete) {
      Sub_FOpid_control_417.resetSubscriberPtr();//();
    }
  }

  /* End of Terminate for MATLABSystem: '<S46>/SourceBlock' */

  /* Terminate for MATLABSystem: '<S43>/SourceBlock' */
  if (!FOpid_control_DW.obj_h4.matlabCodegenIsDeleted) {
    FOpid_control_DW.obj_h4.matlabCodegenIsDeleted = true;
    if ((FOpid_control_DW.obj_h4.isInitialized == 1) &&
        FOpid_control_DW.obj_h4.isSetupComplete) {
      Sub_FOpid_control_423.resetSubscriberPtr();//();
    }
  }

  /* End of Terminate for MATLABSystem: '<S43>/SourceBlock' */

  /* Terminate for MATLABSystem: '<S44>/SourceBlock' */
  if (!FOpid_control_DW.obj_hy.matlabCodegenIsDeleted) {
    FOpid_control_DW.obj_hy.matlabCodegenIsDeleted = true;
    if ((FOpid_control_DW.obj_hy.isInitialized == 1) &&
        FOpid_control_DW.obj_hy.isSetupComplete) {
      Sub_FOpid_control_443.resetSubscriberPtr();//();
    }
  }

  /* End of Terminate for MATLABSystem: '<S44>/SourceBlock' */

  /* Terminate for MATLABSystem: '<S45>/SourceBlock' */
  if (!FOpid_control_DW.obj_p.matlabCodegenIsDeleted) {
    FOpid_control_DW.obj_p.matlabCodegenIsDeleted = true;
    if ((FOpid_control_DW.obj_p.isInitialized == 1) &&
        FOpid_control_DW.obj_p.isSetupComplete) {
      Sub_FOpid_control_445.resetSubscriberPtr();//();
    }
  }

  /* End of Terminate for MATLABSystem: '<S45>/SourceBlock' */
}

/* Constructor */
FOpid_control::FOpid_control() :
  FOpid_control_B(),
  FOpid_control_DW(),
  FOpid_control_X(),
  FOpid_control_XDis(),
  FOpid_control_PrevZCX(),
  FOpid_control_M()
{
  /* Currently there is no constructor body generated.*/
}

/* Destructor */
FOpid_control::~FOpid_control()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_FOpid_control_T * FOpid_control::getRTM()
{
  return (&FOpid_control_M);
}
