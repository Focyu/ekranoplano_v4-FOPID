/*
 * FOpid_RL.cpp
 *
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 *
 * Code generation for model "FOpid_RL".
 *
 * Model version              : 13.76
 * Simulink Coder version : 26.2 (R2026b) 22-May-2026
 * C++ source code generated on : Sat Nov 14 23:51:06 2026
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "FOpid_RL.h"
#include "slros2_initialize.h"
#include "rtwtypes.h"
#include "FOpid_RL_types.h"
#include "rmw/qos_profiles.h"
#include <string.h>
#include "FOpid_RL_private.h"
#include <emmintrin.h>
#include <math.h>

extern "C"
{

#include "rt_nonfinite.h"

}

#include <stddef.h>
#include "zero_crossing_types.h"
#include <float.h>
#include "rt_defines.h"

const real_T FOpid_RL_period = 0.01;
real_T look1_binlxpw(real_T u0, const real_T bp0[], const real_T table[],
                     uint32_T maxIndex)
{
  real_T frac;
  real_T yL_0d0;
  uint32_T iLeft;

  /* Column-major Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex]) {
    uint32_T bpIdx;
    uint32_T iRght;

    /* Binary Search */
    bpIdx = maxIndex >> 1U;
    iLeft = 0U;
    iRght = maxIndex;
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex - 1U;
    frac = (u0 - bp0[maxIndex - 1U]) / (bp0[maxIndex] - bp0[maxIndex - 1U]);
  }

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  yL_0d0 = table[iLeft];
  return (table[iLeft + 1U] - yL_0d0) * frac + yL_0d0;
}

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
void FOpid_RL::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
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
  FOpid_RL_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  this->step();
  FOpid_RL_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  this->step();
  FOpid_RL_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  this->step();
  FOpid_RL_derivatives();

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
void FOpid_RL::MATLABFunctionned_to_PoseStampe(B_MATLABFunctionned_to_PoseSt_T
  *localB)
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
 *    '<S44>/Enabled Subsystem'
 *    '<S47>/Enabled Subsystem'
 */
void FOpid_RL::FOpid_RL_EnabledSubsystem_Init(B_EnabledSubsystem_FOpid_RL_T
  *localB)
{
  /* SystemInitialize for SignalConversion generated from: '<S87>/In1' */
  memset(&localB->In1, 0, sizeof(SL_Bus_std_msgs_Bool));
}

/*
 * Output and update for enable system:
 *    '<S44>/Enabled Subsystem'
 *    '<S47>/Enabled Subsystem'
 */
void FOpid_RL::FOpid_RL_EnabledSubsystem(boolean_T rtu_Enable, const
  SL_Bus_std_msgs_Bool *rtu_In1, B_EnabledSubsystem_FOpid_RL_T *localB)
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

/*
 * System initialize for enable system:
 *    '<S45>/Enabled Subsystem'
 *    '<S46>/Enabled Subsystem'
 *    '<S34>/Enabled Subsystem'
 *    '<S35>/Enabled Subsystem'
 */
void FOpid_RL::FOpid_R_EnabledSubsystem_e_Init(B_EnabledSubsystem_FOpid_RL_d_T
  *localB)
{
  /* SystemInitialize for SignalConversion generated from: '<S88>/In1' */
  memset(&localB->In1, 0, sizeof(SL_Bus_std_msgs_Float64));
}

/*
 * Output and update for enable system:
 *    '<S45>/Enabled Subsystem'
 *    '<S46>/Enabled Subsystem'
 *    '<S34>/Enabled Subsystem'
 *    '<S35>/Enabled Subsystem'
 */
void FOpid_RL::FOpid_RL_EnabledSubsystem_k(boolean_T rtu_Enable, const
  SL_Bus_std_msgs_Float64 *rtu_In1, B_EnabledSubsystem_FOpid_RL_d_T *localB)
{
  /* Outputs for Enabled SubSystem: '<S45>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S88>/Enable'
   */
  if (rtu_Enable) {
    /* SignalConversion generated from: '<S88>/In1' */
    localB->In1 = *rtu_In1;
  }

  /* End of Outputs for SubSystem: '<S45>/Enabled Subsystem' */
}

void FOpid_RL::FOpid_RL_Publisher_setupImpl(const
  ros_slros2_internal_block_Pub_T *obj)
{
  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  static const char_T b_zeroDelimTopic[17] = "/ekranoplano/imu";
  qos_profile = rmw_qos_profile_default;

  /* Start for MATLABSystem: '<S27>/SinkBlock' */
  FOpid_RL_B.deadline_j.sec = 0.0;
  FOpid_RL_B.deadline_j.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST, static_cast<
                 size_t>(10.0), RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE, FOpid_RL_B.deadline_j,
                 lifespan, RMW_QOS_POLICY_LIVELINESS_AUTOMATIC,
                 liveliness_lease_duration, (bool)
                 obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i = 0; i < 17; i++) {
    /* Start for MATLABSystem: '<S27>/SinkBlock' */
    FOpid_RL_B.b_zeroDelimTopic_f[i] = b_zeroDelimTopic[i];
  }

  Pub_FOpid_RL_548.createPublisher(&FOpid_RL_B.b_zeroDelimTopic_f[0],
    qos_profile);
}

rmw_qos_profile_t FOpid_RL::FO_ROS2PubSubBase_setQOSProfile(rmw_qos_profile_t
  rmwProfile, real_T qosDepth, real_T qosDeadline, real_T qosLifespan, real_T
  qosLeaseDuration, boolean_T qosAvoidROSNamespaceConventions)
{
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  real_T input;
  real_T sec;
  input = qosDeadline;

  /* Start for MATLABSystem: '<S28>/SinkBlock' */
  if (qosDeadline == (rtInf)) {
    input = 0.0;
  }

  sec = floor(input);
  FOpid_RL_B.deadline_dh.sec = sec;
  FOpid_RL_B.deadline_dh.nsec = (input - sec) * 1.0E+9;
  input = qosLifespan;

  /* Start for MATLABSystem: '<S28>/SinkBlock' */
  if (qosLifespan == (rtInf)) {
    input = 0.0;
  }

  sec = floor(input);
  lifespan.sec = sec;
  lifespan.nsec = (input - sec) * 1.0E+9;
  input = qosLeaseDuration;

  /* Start for MATLABSystem: '<S28>/SinkBlock' */
  if (qosLeaseDuration == (rtInf)) {
    input = 0.0;
  }

  sec = floor(input);
  liveliness_lease_duration.sec = sec;
  liveliness_lease_duration.nsec = (input - sec) * 1.0E+9;
  SET_QOS_VALUES(rmwProfile, RMW_QOS_POLICY_HISTORY_KEEP_LAST,
                 static_cast<size_t>(qosDepth),
                 RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE, FOpid_RL_B.deadline_dh,
                 lifespan, RMW_QOS_POLICY_LIVELINESS_AUTOMATIC,
                 liveliness_lease_duration, (bool)
                 qosAvoidROSNamespaceConventions);
  return rmwProfile;
}

void FOpid_RL::FOpid_RL_Publisher_setupImpl_b(const
  ros_slros2_internal_block_Pub_T *obj)
{
  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  static const char_T b_zeroDelimTopic[25] = "/ekranoplano/PoseStamped";
  qos_profile = rmw_qos_profile_default;

  /* Start for MATLABSystem: '<S29>/SinkBlock' */
  FOpid_RL_B.deadline_g1.sec = 0.0;
  FOpid_RL_B.deadline_g1.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST,
                 static_cast<size_t>(10.0), RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE, FOpid_RL_B.deadline_g1,
                 lifespan, RMW_QOS_POLICY_LIVELINESS_AUTOMATIC,
                 liveliness_lease_duration, (bool)
                 obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i = 0; i < 25; i++) {
    /* Start for MATLABSystem: '<S29>/SinkBlock' */
    FOpid_RL_B.b_zeroDelimTopic_c[i] = b_zeroDelimTopic[i];
  }

  Pub_FOpid_RL_811.createPublisher(&FOpid_RL_B.b_zeroDelimTopic_c[0],
    qos_profile);
}

void FOpid_RL::FOpid_RL_Publisher_setupImpl_bf(const
  ros_slros2_internal_block_Pub_T *obj)
{
  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  static const char_T b_zeroDelimTopic[26] = "/ekranoplano/TwistStamped";
  qos_profile = rmw_qos_profile_default;

  /* Start for MATLABSystem: '<S30>/SinkBlock' */
  FOpid_RL_B.deadline.sec = 0.0;
  FOpid_RL_B.deadline.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST,
                 static_cast<size_t>(10.0), RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE, FOpid_RL_B.deadline,
                 lifespan, RMW_QOS_POLICY_LIVELINESS_AUTOMATIC,
                 liveliness_lease_duration, (bool)
                 obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i = 0; i < 26; i++) {
    /* Start for MATLABSystem: '<S30>/SinkBlock' */
    FOpid_RL_B.b_zeroDelimTopic[i] = b_zeroDelimTopic[i];
  }

  Pub_FOpid_RL_835.createPublisher(&FOpid_RL_B.b_zeroDelimTopic[0], qos_profile);
}

void FOpid_RL::FOpid_Subscriber_setupImpl_bfq4(const
  ros_slros2_internal_block_Sub_T *obj)
{
  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  static const char_T b_zeroDelimTopic[17] = "/setpoint/altura";
  qos_profile = rmw_qos_profile_default;

  /* Start for MATLABSystem: '<S34>/SourceBlock' */
  FOpid_RL_B.deadline_l.sec = 0.0;
  FOpid_RL_B.deadline_l.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST,
                 static_cast<size_t>(10.0), RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE, FOpid_RL_B.deadline_l,
                 lifespan, RMW_QOS_POLICY_LIVELINESS_AUTOMATIC,
                 liveliness_lease_duration, (bool)
                 obj->QOSAvoidROSNamespaceConventions);
  Sub_FOpid_RL_435.setAsyncEnabled("off", "null");
  Sub_FOpid_RL_435.setCallbackGroup("default", "callback_group_1");
  for (int32_T i = 0; i < 17; i++) {
    /* Start for MATLABSystem: '<S34>/SourceBlock' */
    FOpid_RL_B.b_zeroDelimTopic_cv[i] = b_zeroDelimTopic[i];
  }

  Sub_FOpid_RL_435.createSubscriber(&FOpid_RL_B.b_zeroDelimTopic_cv[0],
    qos_profile);
}

void FOpid_RL::FOpi_Subscriber_setupImpl_bfq4p(const
  ros_slros2_internal_block_Sub_T *obj)
{
  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  char_T b_zeroDelimTopic[14];
  static const char_T b_zeroDelimTopic_0[14] = "/setpoint/yaw";
  qos_profile = rmw_qos_profile_default;

  /* Start for MATLABSystem: '<S35>/SourceBlock' */
  FOpid_RL_B.deadline_d.sec = 0.0;
  FOpid_RL_B.deadline_d.nsec = 0.0;
  FOpid_RL_B.lifespan.sec = 0.0;
  FOpid_RL_B.lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST,
                 static_cast<size_t>(10.0), RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE, FOpid_RL_B.deadline_d,
                 FOpid_RL_B.lifespan, RMW_QOS_POLICY_LIVELINESS_AUTOMATIC,
                 liveliness_lease_duration, (bool)
                 obj->QOSAvoidROSNamespaceConventions);
  Sub_FOpid_RL_377.setAsyncEnabled("off", "null");
  Sub_FOpid_RL_377.setCallbackGroup("default", "callback_group_1");
  for (int32_T i = 0; i < 14; i++) {
    /* Start for MATLABSystem: '<S35>/SourceBlock' */
    b_zeroDelimTopic[i] = b_zeroDelimTopic_0[i];
  }

  Sub_FOpid_RL_377.createSubscriber(&b_zeroDelimTopic[0], qos_profile);
}

void FOpid_RL::FOpid_R_ServiceCaller_setupImpl(ros_slros2_internal_block_Ser_T
  *obj)
{
  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  static const char_T b_zeroDelimTopic[25] = "/gazebo/set_entity_state";
  qos_profile = rmw_qos_profile_default;

  /* Start for MATLABSystem: '<S6>/ServiceCaller' */
  FOpid_RL_B.deadline_g.sec = 0.0;
  FOpid_RL_B.deadline_g.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST,
                 static_cast<size_t>(1.0), RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE, FOpid_RL_B.deadline_g,
                 lifespan, RMW_QOS_POLICY_LIVELINESS_AUTOMATIC,
                 liveliness_lease_duration, (bool)
                 obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i = 0; i < 25; i++) {
    /* Start for MATLABSystem: '<S6>/ServiceCaller' */
    FOpid_RL_B.b_zeroDelimTopic_m[i] = b_zeroDelimTopic[i];
  }

  ServCall_FOpid_RL_326.createServiceCaller(&FOpid_RL_B.b_zeroDelimTopic_m[0],
    qos_profile);
}

void FOpid_RL::FOpid_RL_Subscriber_setupImpl(const
  ros_slros2_internal_block_Sub_T *obj)
{
  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  static const char_T b_zeroDelimTopic[22] = "/setpoint/turbulencia";
  qos_profile = rmw_qos_profile_default;

  /* Start for MATLABSystem: '<S44>/SourceBlock' */
  FOpid_RL_B.deadline_n.sec = 0.0;
  FOpid_RL_B.deadline_n.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST,
                 static_cast<size_t>(10.0), RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE, FOpid_RL_B.deadline_n,
                 lifespan, RMW_QOS_POLICY_LIVELINESS_AUTOMATIC,
                 liveliness_lease_duration, (bool)
                 obj->QOSAvoidROSNamespaceConventions);
  Sub_FOpid_RL_423.setAsyncEnabled("off", "null");
  Sub_FOpid_RL_423.setCallbackGroup("default", "callback_group_1");
  for (int32_T i = 0; i < 22; i++) {
    /* Start for MATLABSystem: '<S44>/SourceBlock' */
    FOpid_RL_B.b_zeroDelimTopic_cx[i] = b_zeroDelimTopic[i];
  }

  Sub_FOpid_RL_423.createSubscriber(&FOpid_RL_B.b_zeroDelimTopic_cx[0],
    qos_profile);
}

void FOpid_RL::FOpid_R_Subscriber_setupImpl_bf(const
  ros_slros2_internal_block_Sub_T *obj)
{
  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  static const char_T b_zeroDelimTopic[17] = "/olas/pitch_rate";
  qos_profile = rmw_qos_profile_default;

  /* Start for MATLABSystem: '<S46>/SourceBlock' */
  FOpid_RL_B.deadline_p.sec = 0.0;
  FOpid_RL_B.deadline_p.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST,
                 static_cast<size_t>(10.0), RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE, FOpid_RL_B.deadline_p,
                 lifespan, RMW_QOS_POLICY_LIVELINESS_AUTOMATIC,
                 liveliness_lease_duration, (bool)
                 obj->QOSAvoidROSNamespaceConventions);
  Sub_FOpid_RL_445.setAsyncEnabled("off", "null");
  Sub_FOpid_RL_445.setCallbackGroup("default", "callback_group_1");
  for (int32_T i = 0; i < 17; i++) {
    /* Start for MATLABSystem: '<S46>/SourceBlock' */
    FOpid_RL_B.b_zeroDelimTopic_p[i] = b_zeroDelimTopic[i];
  }

  Sub_FOpid_RL_445.createSubscriber(&FOpid_RL_B.b_zeroDelimTopic_p[0],
    qos_profile);
}

void FOpid_RL::FOpid__Subscriber_setupImpl_bfq(const
  ros_slros2_internal_block_Sub_T *obj)
{
  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  static const char_T b_zeroDelimTopic[22] = "/setpoint/turbulencia";
  qos_profile = rmw_qos_profile_default;

  /* Start for MATLABSystem: '<S47>/SourceBlock' */
  FOpid_RL_B.deadline_m.sec = 0.0;
  FOpid_RL_B.deadline_m.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST,
                 static_cast<size_t>(10.0), RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE, FOpid_RL_B.deadline_m,
                 lifespan, RMW_QOS_POLICY_LIVELINESS_AUTOMATIC,
                 liveliness_lease_duration, (bool)
                 obj->QOSAvoidROSNamespaceConventions);
  Sub_FOpid_RL_417.setAsyncEnabled("off", "null");
  Sub_FOpid_RL_417.setCallbackGroup("default", "callback_group_1");
  for (int32_T i = 0; i < 22; i++) {
    /* Start for MATLABSystem: '<S47>/SourceBlock' */
    FOpid_RL_B.b_zeroDelimTopic_k[i] = b_zeroDelimTopic[i];
  }

  Sub_FOpid_RL_417.createSubscriber(&FOpid_RL_B.b_zeroDelimTopic_k[0],
    qos_profile);
}

void FOpid_RL::FOpid_RL_Subscriber_setupImpl_b(const
  ros_slros2_internal_block_Sub_T *obj)
{
  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  char_T b_zeroDelimTopic[12];
  static const char_T b_zeroDelimTopic_0[12] = "/olas/heave";
  qos_profile = rmw_qos_profile_default;

  /* Start for MATLABSystem: '<S45>/SourceBlock' */
  FOpid_RL_B.deadline_gu.sec = 0.0;
  FOpid_RL_B.deadline_gu.nsec = 0.0;
  FOpid_RL_B.lifespan_l.sec = 0.0;
  FOpid_RL_B.lifespan_l.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST,
                 static_cast<size_t>(10.0), RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE, FOpid_RL_B.deadline_gu,
                 FOpid_RL_B.lifespan_l, RMW_QOS_POLICY_LIVELINESS_AUTOMATIC,
                 liveliness_lease_duration, (bool)
                 obj->QOSAvoidROSNamespaceConventions);
  Sub_FOpid_RL_443.setAsyncEnabled("off", "null");
  Sub_FOpid_RL_443.setCallbackGroup("default", "callback_group_1");
  for (int32_T i = 0; i < 12; i++) {
    /* Start for MATLABSystem: '<S45>/SourceBlock' */
    b_zeroDelimTopic[i] = b_zeroDelimTopic_0[i];
  }

  Sub_FOpid_RL_443.createSubscriber(&b_zeroDelimTopic[0], qos_profile);
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

real_T rt_remd_snf(real_T u0, real_T u1)
{
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1) || rtIsInf(u0)) {
    y = (rtNaN);
  } else if (rtIsInf(u1)) {
    y = u0;
  } else {
    real_T q;
    if (u1 < 0.0) {
      q = ceil(u1);
    } else {
      q = floor(u1);
    }

    if ((u1 != 0.0) && (u1 != q)) {
      q = fabs(u0 / u1);
      if (!(fabs(q - floor(q + 0.5)) > DBL_EPSILON * q)) {
        y = 0.0 * u0;
      } else {
        y = fmod(u0, u1);
      }
    } else {
      y = fmod(u0, u1);
    }
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
void FOpid_RL::step()
{
  /* local block i/o variables */
  SL_Bus_std_msgs_Float64 rtb_SourceBlock_o2;
  SL_Bus_std_msgs_Float64 rtb_SourceBlock_o2_k;
  SL_Bus_std_msgs_Float64 rtb_SourceBlock_o2_p;
  SL_Bus_std_msgs_Bool rtb_SourceBlock_o2_j;
  SL_Bus_std_msgs_Bool rtb_SourceBlock_o2_dd;
  if (rtmIsMajorTimeStep((&FOpid_RL_M))) {
    /* set solver stop time */
    if (!((&FOpid_RL_M)->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&(&FOpid_RL_M)->solverInfo, (((&FOpid_RL_M)
        ->Timing.clockTickH0 + 1) * (&FOpid_RL_M)->Timing.stepSize0 *
        4294967296.0));
    } else {
      rtsiSetSolverStopTime(&(&FOpid_RL_M)->solverInfo, (((&FOpid_RL_M)
        ->Timing.clockTick0 + 1) * (&FOpid_RL_M)->Timing.stepSize0 +
        (&FOpid_RL_M)->Timing.clockTickH0 * (&FOpid_RL_M)->Timing.stepSize0 *
        4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&FOpid_RL_M))) {
    (&FOpid_RL_M)->Timing.t[0] = rtsiGetT(&(&FOpid_RL_M)->solverInfo);
  }

  {
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
    memset(&FOpid_RL_B.BusAssignmentIMU, 0, sizeof(SL_Bus_sensor_msgs_Imu));

    /* RelationalOperator: '<S40>/Compare' incorporates:
     *  Constant: '<S40>/Constant'
     */
    FOpid_RL_B.Compare = (FOpid_RL_X.Integrator_CSTATE[11] >= 0.18);

    /* Outputs for Enabled SubSystem: '<S50>/Hugw(s)' incorporates:
     *  EnablePort: '<S63>/Enable'
     */
    /* Outputs for Enabled SubSystem: '<S49>/Hrgw' incorporates:
     *  EnablePort: '<S62>/Enable'
     */
    /* Outputs for Enabled SubSystem: '<S50>/Hvgw(s)' incorporates:
     *  EnablePort: '<S64>/Enable'
     */
    /* Outputs for Enabled SubSystem: '<S49>/Hqgw' incorporates:
     *  EnablePort: '<S61>/Enable'
     */
    /* Outputs for Enabled SubSystem: '<S50>/Hwgw(s)' incorporates:
     *  EnablePort: '<S65>/Enable'
     */
    /* Outputs for Enabled SubSystem: '<S49>/Hpgw' incorporates:
     *  EnablePort: '<S60>/Enable'
     */
    tmp_0 = (rtmIsMajorTimeStep((&FOpid_RL_M)) &&
             (&FOpid_RL_M)->Timing.TaskCounters.TID[1] == 0);

    /* End of Outputs for SubSystem: '<S49>/Hpgw' */
    /* End of Outputs for SubSystem: '<S50>/Hwgw(s)' */
    /* End of Outputs for SubSystem: '<S49>/Hqgw' */
    /* End of Outputs for SubSystem: '<S50>/Hvgw(s)' */
    /* End of Outputs for SubSystem: '<S49>/Hrgw' */
    /* End of Outputs for SubSystem: '<S50>/Hugw(s)' */
    if (tmp_0) {
      /* MATLAB Function: '<S33>/MATLAB Function-reset' incorporates:
       *  Memory: '<S33>/Memory2'
       */
      memcpy(&FOpid_RL_B.IC[0], &FOpid_RL_DW.Memory2_PreviousInput[0], 12U *
             sizeof(real_T));
      FOpid_RL_B.IC[2] = 0.0;
      FOpid_RL_B.IC[11] = 0.0;

      /* InitialCondition: '<S33>/IC' */
      if (FOpid_RL_DW.IC_FirstOutputTime) {
        FOpid_RL_DW.IC_FirstOutputTime = false;

        /* InitialCondition: '<S33>/IC' */
        memcpy(&FOpid_RL_B.IC[0], &FOpid_RL_ConstP.pooled14[0], 12U * sizeof
               (real_T));
      }

      /* End of InitialCondition: '<S33>/IC' */
    }

    /* Integrator: '<S33>/Integrator' incorporates:
     *  InitialCondition: '<S33>/IC'
     */
    if (rtsiIsModeUpdateTimeStep(&(&FOpid_RL_M)->solverInfo)) {
      serverAvailableOnTime = (((FOpid_RL_PrevZCX.Integrator_Reset_ZCE ==
        POS_ZCSIG) != FOpid_RL_B.Compare) &&
        (FOpid_RL_PrevZCX.Integrator_Reset_ZCE != UNINITIALIZED_ZCSIG));
      FOpid_RL_PrevZCX.Integrator_Reset_ZCE = FOpid_RL_B.Compare;

      /* evaluate zero-crossings and the level of the reset signal */
      if (serverAvailableOnTime || FOpid_RL_B.Compare ||
          FOpid_RL_DW.Integrator_DWORK1) {
        memcpy(&FOpid_RL_X.Integrator_CSTATE[0], &FOpid_RL_B.IC[0], 12U * sizeof
               (real_T));
        rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)->solverInfo,
          true);
        rtsiSetContTimeOutputInconsistentWithStateAtMajorStep(&(&FOpid_RL_M)
          ->solverInfo, true);
      }
    }

    /* Integrator: '<S33>/Integrator' */
    memcpy(&FOpid_RL_B.x[0], &FOpid_RL_X.Integrator_CSTATE[0], 12U * sizeof
           (real_T));

    /* MATLABSystem: '<Root>/Coordinate Transformation Conversion' */
    if (!FOpid_RL_DW.regObj_not_empty) {
      FOpid_RL_DW.regObj.FeatureControlFlag = true;
      FOpid_RL_DW.regObj_not_empty = true;
    }

    /* SignalConversion generated from: '<Root>/Coordinate Transformation Conversion' incorporates:
     *  MATLABSystem: '<Root>/Coordinate Transformation Conversion'
     */
    _mm_storeu_pd(&FOpid_RL_B.wbe_b[0], _mm_div_pd(_mm_set_pd(FOpid_RL_B.x[6],
      FOpid_RL_B.x[8]), _mm_set1_pd(2.0)));

    /* MATLABSystem: '<Root>/Coordinate Transformation Conversion' incorporates:
     *  SignalConversion generated from: '<Root>/Coordinate Transformation Conversion'
     */
    FOpid_RL_B.wbe_b[2] = FOpid_RL_B.x[7] / 2.0;
    FOpid_RL_B.sina = sin(FOpid_RL_B.wbe_b[0]);
    FOpid_RL_B.sinb = sin(FOpid_RL_B.wbe_b[1]);
    FOpid_RL_B.sinc = sin(FOpid_RL_B.wbe_b[2]);
    FOpid_RL_B.cosa = cos(FOpid_RL_B.wbe_b[0]);
    FOpid_RL_B.cosb = cos(FOpid_RL_B.wbe_b[1]);
    FOpid_RL_B.cosc = cos(FOpid_RL_B.wbe_b[2]);
    FOpid_RL_B.rtb_CoordinateTransformationC_l = FOpid_RL_B.cosa *
      FOpid_RL_B.cosb;
    FOpid_RL_B.rtb_CoordinateTransformationC_d = FOpid_RL_B.sina *
      FOpid_RL_B.sinb * FOpid_RL_B.sinc +
      FOpid_RL_B.rtb_CoordinateTransformationC_l * FOpid_RL_B.cosc;
    FOpid_RL_B.rtb_CoordinateTransformationC_l =
      FOpid_RL_B.rtb_CoordinateTransformationC_l * FOpid_RL_B.sinc -
      FOpid_RL_B.cosc * FOpid_RL_B.sina * FOpid_RL_B.sinb;
    FOpid_RL_B.rtb_CoordinateTransformationC_o = FOpid_RL_B.cosa *
      FOpid_RL_B.cosc * FOpid_RL_B.sinb + FOpid_RL_B.cosb * FOpid_RL_B.sina *
      FOpid_RL_B.sinc;
    FOpid_RL_B.cosc = FOpid_RL_B.cosb * FOpid_RL_B.cosc * FOpid_RL_B.sina -
      FOpid_RL_B.cosa * FOpid_RL_B.sinb * FOpid_RL_B.sinc;
    if (tmp_0) {
      /* MATLAB Function: '<Root>/MATLAB Function-IMU2' */
      memset(&FOpid_RL_B.stringOut_n[0], 0, sizeof(uint8_T) << 7U);
      for (i = 0; i < 15; i++) {
        FOpid_RL_B.stringOut_n[i] = b[i];
      }

      FOpid_RL_B.lengthOut_i = 15U;

      /* End of MATLAB Function: '<Root>/MATLAB Function-IMU2' */
    }

    /* MATLAB Function: '<Root>/MATLAB Function-ned_to_imu' incorporates:
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_gazebo'
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_odometry'
     */
    FOpid_RL_B.cosa = 0.0 * FOpid_RL_B.rtb_CoordinateTransformationC_o +
      FOpid_RL_B.rtb_CoordinateTransformationC_l;

    /* BusAssignment: '<Root>/Bus Assignment-IMU' incorporates:
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_imu'
     */
    FOpid_RL_B.BusAssignmentIMU.orientation.x = -FOpid_RL_B.cosa;

    /* MATLAB Function: '<Root>/MATLAB Function-ned_to_imu' incorporates:
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_gazebo'
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_odometry'
     */
    FOpid_RL_B.sina = 0.0 * FOpid_RL_B.rtb_CoordinateTransformationC_l -
      FOpid_RL_B.rtb_CoordinateTransformationC_o;

    /* BusAssignment: '<Root>/Bus Assignment-IMU' incorporates:
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_imu'
     */
    FOpid_RL_B.BusAssignmentIMU.orientation.y = FOpid_RL_B.sina;

    /* MATLAB Function: '<Root>/MATLAB Function-ned_to_imu' incorporates:
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_gazebo'
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_odometry'
     */
    FOpid_RL_B.sinb = 0.0 * FOpid_RL_B.rtb_CoordinateTransformationC_d -
      FOpid_RL_B.cosc;

    /* BusAssignment: '<Root>/Bus Assignment-IMU' incorporates:
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_imu'
     */
    FOpid_RL_B.BusAssignmentIMU.orientation.z = -FOpid_RL_B.sinb;

    /* MATLAB Function: '<Root>/MATLAB Function-ned_to_imu' incorporates:
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_gazebo'
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_odometry'
     */
    FOpid_RL_B.sinc = 0.0 * FOpid_RL_B.cosc +
      FOpid_RL_B.rtb_CoordinateTransformationC_d;

    /* BusAssignment: '<Root>/Bus Assignment-IMU' incorporates:
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_imu'
     */
    FOpid_RL_B.BusAssignmentIMU.orientation.w = FOpid_RL_B.sinc;
    FOpid_RL_B.BusAssignmentIMU.angular_velocity.x = FOpid_RL_B.x[0];
    FOpid_RL_B.BusAssignmentIMU.angular_velocity.y = FOpid_RL_B.x[1];
    FOpid_RL_B.BusAssignmentIMU.angular_velocity.z = FOpid_RL_B.x[2];
    memcpy(&FOpid_RL_B.BusAssignmentIMU.header.frame_id[0],
           &FOpid_RL_B.stringOut_n[0], sizeof(uint8_T) << 7U);
    FOpid_RL_B.BusAssignmentIMU.header.frame_id_SL_Info.CurrentLength =
      FOpid_RL_B.lengthOut_i;

    /* MATLABSystem: '<S27>/SinkBlock' */
    Pub_FOpid_RL_548.publish(&FOpid_RL_B.BusAssignmentIMU);

    /* Gain: '<Root>/Gain-Z' */
    FOpid_RL_B.GainZ = -FOpid_RL_B.x[11];
    if (tmp_0) {
      /* MATLAB Function: '<Root>/MATLAB Function-Odometry' */
      memset(&FOpid_RL_B.str_out_e[0], 0, sizeof(uint8_T) << 7U);
      for (i = 0; i < 5; i++) {
        FOpid_RL_B.str_out_e[i] = b_0[i];
      }

      FOpid_RL_B.currentLen_b = 5U;
      FOpid_RL_B.receivedLen_b = 5U;

      /* End of MATLAB Function: '<Root>/MATLAB Function-Odometry' */

      /* MATLAB Function: '<Root>/MATLAB Function-Odometry1' */
      memset(&FOpid_RL_B.str_out[0], 0, sizeof(uint8_T) << 7U);
      for (i = 0; i < 11; i++) {
        FOpid_RL_B.str_out[i] = b_1[i];
      }

      FOpid_RL_B.currentLen = 11U;
      FOpid_RL_B.receivedLen = 11U;

      /* End of MATLAB Function: '<Root>/MATLAB Function-Odometry1' */
    }

    /* Clock: '<Root>/Clock' incorporates:
     *  Clock: '<S32>/Clock'
     */
    FOpid_RL_B.cosb = (&FOpid_RL_M)->Timing.t[0];

    /* MATLAB Function: '<Root>/MATLAB Function-clocl' incorporates:
     *  Clock: '<Root>/Clock'
     */
    FOpid_RL_B.CL_w_IGE = floor(FOpid_RL_B.cosb);

    /* BusAssignment: '<Root>/Bus Assignment-ODOM' */
    memset(&FOpid_RL_B.BusAssignmentODOM, 0, sizeof(SL_Bus_nav_msgs_Odometry));

    /* MATLAB Function: '<Root>/MATLAB Function-clocl' incorporates:
     *  Clock: '<Root>/Clock'
     */
    if (FOpid_RL_B.CL_w_IGE < 2.147483648E+9) {
      if (FOpid_RL_B.CL_w_IGE >= -2.147483648E+9) {
        i = static_cast<int32_T>(FOpid_RL_B.CL_w_IGE);
      } else {
        i = MIN_int32_T;
      }
    } else {
      i = MAX_int32_T;
    }

    FOpid_RL_B.CL_w_IGE = rt_roundd_snf((FOpid_RL_B.cosb - FOpid_RL_B.CL_w_IGE) *
      1.0E+9);
    if (FOpid_RL_B.CL_w_IGE < 4.294967296E+9) {
      if (FOpid_RL_B.CL_w_IGE >= 0.0) {
        rtb_nsec_0 = static_cast<uint32_T>(FOpid_RL_B.CL_w_IGE);
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
    FOpid_RL_B.BusAssignmentODOM.pose.pose.position.x = FOpid_RL_B.x[10];
    FOpid_RL_B.BusAssignmentODOM.pose.pose.position.y = FOpid_RL_B.x[9];
    FOpid_RL_B.BusAssignmentODOM.pose.pose.position.z = -FOpid_RL_B.GainZ;

    /* MATLAB Function: '<Root>/MATLAB Function-ned_to_odometry' */
    FOpid_RL_B.CL_w_IGE = 0.7071 * FOpid_RL_B.sina;
    FOpid_RL_B.CL_h_IGE = 0.7071 * -FOpid_RL_B.cosa;

    /* BusAssignment: '<Root>/Bus Assignment-ODOM' incorporates:
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_odometry'
     */
    FOpid_RL_B.BusAssignmentODOM.pose.pose.orientation.x = FOpid_RL_B.CL_h_IGE +
      FOpid_RL_B.CL_w_IGE;
    FOpid_RL_B.BusAssignmentODOM.pose.pose.orientation.y = FOpid_RL_B.CL_w_IGE -
      FOpid_RL_B.CL_h_IGE;

    /* MATLAB Function: '<Root>/MATLAB Function-ned_to_odometry' */
    FOpid_RL_B.CL_w_IGE = 0.7071 * FOpid_RL_B.sinc;
    FOpid_RL_B.CL_h_IGE = 0.7071 * FOpid_RL_B.sinb;

    /* BusAssignment: '<Root>/Bus Assignment-ODOM' incorporates:
     *  MATLAB Function: '<Root>/MATLAB Function-clocl'
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_odometry'
     */
    FOpid_RL_B.BusAssignmentODOM.pose.pose.orientation.z = FOpid_RL_B.CL_h_IGE +
      FOpid_RL_B.CL_w_IGE;
    FOpid_RL_B.BusAssignmentODOM.pose.pose.orientation.w = FOpid_RL_B.CL_w_IGE -
      FOpid_RL_B.CL_h_IGE;
    FOpid_RL_B.BusAssignmentODOM.header.frame_id_SL_Info.CurrentLength =
      FOpid_RL_B.currentLen_b;
    FOpid_RL_B.BusAssignmentODOM.header.frame_id_SL_Info.ReceivedLength =
      FOpid_RL_B.receivedLen_b;
    memcpy(&FOpid_RL_B.BusAssignmentODOM.header.frame_id[0],
           &FOpid_RL_B.str_out_e[0], sizeof(uint8_T) << 7U);
    memcpy(&FOpid_RL_B.BusAssignmentODOM.child_frame_id[0], &FOpid_RL_B.str_out
           [0], sizeof(uint8_T) << 7U);
    FOpid_RL_B.BusAssignmentODOM.child_frame_id_SL_Info.CurrentLength =
      FOpid_RL_B.currentLen;
    FOpid_RL_B.BusAssignmentODOM.child_frame_id_SL_Info.ReceivedLength =
      FOpid_RL_B.receivedLen;
    FOpid_RL_B.BusAssignmentODOM.header.stamp.sec = i;
    FOpid_RL_B.BusAssignmentODOM.header.stamp.nanosec = rtb_nsec_0;

    /* MATLABSystem: '<S28>/SinkBlock' */
    Pub_FOpid_RL_697.publish(&FOpid_RL_B.BusAssignmentODOM);
    if (tmp_0) {
      /* MATLAB Function: '<Root>/MATLAB Function-ned_to_PoseStamped' */
      MATLABFunctionned_to_PoseStampe
        (&FOpid_RL_B.sf_MATLABFunctionned_to_PoseS_b);
    }

    /* BusAssignment: '<Root>/Bus Assignment-PoseStaamped' incorporates:
     *  MATLAB Function: '<Root>/MATLAB Function-clocl'
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_PoseStaamped'
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_gazebo'
     */
    memset(&FOpid_RL_B.BusAssignmentPoseStaamped, 0, sizeof
           (SL_Bus_geometry_msgs_PoseStamped));
    memcpy(&FOpid_RL_B.BusAssignmentPoseStaamped.header.frame_id[0],
           &FOpid_RL_B.sf_MATLABFunctionned_to_PoseS_b.stringOut[0], sizeof
           (uint8_T) << 7U);
    FOpid_RL_B.BusAssignmentPoseStaamped.header.frame_id_SL_Info.CurrentLength =
      FOpid_RL_B.sf_MATLABFunctionned_to_PoseS_b.lengthOut;
    FOpid_RL_B.BusAssignmentPoseStaamped.pose.position.x = -FOpid_RL_B.x[10];
    FOpid_RL_B.BusAssignmentPoseStaamped.pose.position.y = FOpid_RL_B.x[9];
    FOpid_RL_B.BusAssignmentPoseStaamped.pose.position.z = -FOpid_RL_B.GainZ;
    FOpid_RL_B.BusAssignmentPoseStaamped.pose.orientation.x = 0.7071 *
      FOpid_RL_B.rtb_CoordinateTransformationC_o + -0.7071 *
      FOpid_RL_B.rtb_CoordinateTransformationC_l;
    FOpid_RL_B.BusAssignmentPoseStaamped.pose.orientation.y = 0.7071 *
      FOpid_RL_B.rtb_CoordinateTransformationC_l - -0.7071 *
      FOpid_RL_B.rtb_CoordinateTransformationC_o;
    FOpid_RL_B.BusAssignmentPoseStaamped.pose.orientation.z = -(0.7071 *
      FOpid_RL_B.cosc + -0.7071 * FOpid_RL_B.rtb_CoordinateTransformationC_d);
    FOpid_RL_B.BusAssignmentPoseStaamped.pose.orientation.w = 0.7071 *
      FOpid_RL_B.rtb_CoordinateTransformationC_d - -0.7071 * FOpid_RL_B.cosc;
    FOpid_RL_B.BusAssignmentPoseStaamped.header.stamp.sec = i;
    FOpid_RL_B.BusAssignmentPoseStaamped.header.stamp.nanosec = rtb_nsec_0;

    /* MATLABSystem: '<S29>/SinkBlock' */
    Pub_FOpid_RL_811.publish(&FOpid_RL_B.BusAssignmentPoseStaamped);
    if (tmp_0) {
      /* MATLAB Function: '<Root>/MATLAB Function-ned_to_TwistStamped' */
      MATLABFunctionned_to_PoseStampe
        (&FOpid_RL_B.sf_MATLABFunctionned_to_TwistSt);
    }

    /* BusAssignment: '<Root>/Bus Assignment-TwistStamped' incorporates:
     *  MATLAB Function: '<Root>/MATLAB Function-clocl'
     *  MATLAB Function: '<Root>/MATLAB Function2'
     */
    memset(&FOpid_RL_B.BusAssignmentTwistStamped, 0, sizeof
           (SL_Bus_geometry_msgs_TwistStamped));
    memcpy(&FOpid_RL_B.BusAssignmentTwistStamped.header.frame_id[0],
           &FOpid_RL_B.sf_MATLABFunctionned_to_TwistSt.stringOut[0], sizeof
           (uint8_T) << 7U);
    FOpid_RL_B.BusAssignmentTwistStamped.header.frame_id_SL_Info.CurrentLength =
      FOpid_RL_B.sf_MATLABFunctionned_to_TwistSt.lengthOut;
    FOpid_RL_B.BusAssignmentTwistStamped.twist.linear.x = FOpid_RL_B.x[1];
    FOpid_RL_B.BusAssignmentTwistStamped.twist.linear.y = FOpid_RL_B.x[0];
    FOpid_RL_B.BusAssignmentTwistStamped.twist.linear.z = -FOpid_RL_B.x[2];
    FOpid_RL_B.BusAssignmentTwistStamped.header.stamp.sec = i;
    FOpid_RL_B.BusAssignmentTwistStamped.header.stamp.nanosec = rtb_nsec_0;

    /* MATLABSystem: '<S30>/SinkBlock' */
    Pub_FOpid_RL_835.publish(&FOpid_RL_B.BusAssignmentTwistStamped);
    if (tmp_0) {
      /* MATLABSystem: '<S34>/SourceBlock' */
      FOpid_RL_B.SourceBlock_o1_o = Sub_FOpid_RL_435.getLatestMessage
        (&FOpid_RL_B.SourceBlock_o2_d);

      /* Outputs for Enabled SubSystem: '<S34>/Enabled Subsystem' */
      FOpid_RL_EnabledSubsystem_k(FOpid_RL_B.SourceBlock_o1_o,
        &FOpid_RL_B.SourceBlock_o2_d, &FOpid_RL_B.EnabledSubsystem_b);

      /* End of Outputs for SubSystem: '<S34>/Enabled Subsystem' */

      /* Switch: '<Root>/Switch3' */
      if (FOpid_RL_B.SourceBlock_o1_o) {
        /* Switch: '<Root>/Switch3' */
        FOpid_RL_B.Switch3 = FOpid_RL_B.EnabledSubsystem_b.In1.data;
      } else {
        /* Switch: '<Root>/Switch3' incorporates:
         *  UnitDelay: '<Root>/Unit Delay3'
         */
        FOpid_RL_B.Switch3 = FOpid_RL_DW.UnitDelay3_DSTATE;
      }

      /* End of Switch: '<Root>/Switch3' */
    }

    /* Sum: '<Root>/Sum2' */
    FOpid_RL_B.Sum2 = FOpid_RL_B.Switch3 - FOpid_RL_B.GainZ;

    /* Relay: '<Root>/Relay-Enable-Flight' */
    if (rtsiIsModeUpdateTimeStep(&(&FOpid_RL_M)->solverInfo)) {
      FOpid_RL_DW.RelayEnableFlight_Mode = ((FOpid_RL_B.x[0] >= 15.0) ||
        (!(FOpid_RL_B.x[0] <= 12.0) && FOpid_RL_DW.RelayEnableFlight_Mode));
    }

    if (FOpid_RL_DW.RelayEnableFlight_Mode) {
      i = 1;
    } else {
      i = 0;
    }

    /* End of Relay: '<Root>/Relay-Enable-Flight' */
    if (tmp_0) {
      /* Outputs for Enabled SubSystem: '<Root>/Subsystem1' incorporates:
       *  EnablePort: '<S36>/Enable'
       */
      if (i > 0) {
        /* MATLAB Function: '<S36>/MATLAB Function - fopid_altura' incorporates:
         *  Constant: '<Root>/Constant3'
         *  Constant: '<Root>/Constant4'
         *  Constant: '<Root>/Constant5'
         */
        FOpid_RL_B.u_k = ((((((((FOpid_RL_DW.y1_p - 2.0 * FOpid_RL_DW.y2_c) +
          FOpid_RL_DW.y3_b) * -1.8 + ((FOpid_RL_B.GainZ - 2.0 * FOpid_RL_DW.y1_p)
          + FOpid_RL_DW.y2_c)) + ((FOpid_RL_DW.y2_c - 2.0 * FOpid_RL_DW.y3_b) +
          FOpid_RL_DW.y4_b) * 1.62) + ((FOpid_RL_DW.y3_b - 2.0 *
          FOpid_RL_DW.y4_b) + FOpid_RL_DW.y5_c) * -1.572) + ((FOpid_RL_DW.y4_b -
          2.0 * FOpid_RL_DW.y5_c) + FOpid_RL_DW.y6_d) * 1.5174) +
                           ((FOpid_RL_DW.y5_c - 2.0 * FOpid_RL_DW.y6_d) +
                            FOpid_RL_DW.y7_o) * -1.489464) * 0.0 +
                          ((FOpid_RL_B.Sum2 - FOpid_RL_DW.e1_f) * 0.5 +
                           FOpid_RL_DW.u_prev_f)) + (((((((2.0 *
          FOpid_RL_DW.e2_m + FOpid_RL_DW.e1_f) + FOpid_RL_DW.e3_n) *
          -0.6000000000000001 + ((2.0 * FOpid_RL_DW.e1_f + FOpid_RL_B.Sum2) +
          FOpid_RL_DW.e2_m)) + ((2.0 * FOpid_RL_DW.e3_n + FOpid_RL_DW.e2_m) +
          FOpid_RL_DW.e4_j) * 0.18000000000000005) + ((2.0 * FOpid_RL_DW.e4_j +
          FOpid_RL_DW.e3_n) + FOpid_RL_DW.e5_c) * -0.23600000000000004) + ((2.0 *
          FOpid_RL_DW.e5_c + FOpid_RL_DW.e4_j) + FOpid_RL_DW.e6_m) *
          0.12540000000000004) + ((2.0 * FOpid_RL_DW.e6_m + FOpid_RL_DW.e5_c) +
          FOpid_RL_DW.e7_i) * -0.15664800000000004) * 0.002450651390205588;
        if (!(FOpid_RL_B.u_k <= 0.2)) {
          FOpid_RL_B.u_k = 0.2;
        }

        if (!(FOpid_RL_B.u_k >= -0.2)) {
          FOpid_RL_B.u_k = -0.2;
        }

        FOpid_RL_DW.u_prev_f = FOpid_RL_B.u_k;
        FOpid_RL_DW.e7_i = FOpid_RL_DW.e6_m;
        FOpid_RL_DW.e6_m = FOpid_RL_DW.e5_c;
        FOpid_RL_DW.e5_c = FOpid_RL_DW.e4_j;
        FOpid_RL_DW.e4_j = FOpid_RL_DW.e3_n;
        FOpid_RL_DW.e3_n = FOpid_RL_DW.e2_m;
        FOpid_RL_DW.e2_m = FOpid_RL_DW.e1_f;
        FOpid_RL_DW.e1_f = FOpid_RL_B.Sum2;
        FOpid_RL_DW.y7_o = FOpid_RL_DW.y6_d;
        FOpid_RL_DW.y6_d = FOpid_RL_DW.y5_c;
        FOpid_RL_DW.y5_c = FOpid_RL_DW.y4_b;
        FOpid_RL_DW.y4_b = FOpid_RL_DW.y3_b;
        FOpid_RL_DW.y3_b = FOpid_RL_DW.y2_c;
        FOpid_RL_DW.y2_c = FOpid_RL_DW.y1_p;
        FOpid_RL_DW.y1_p = FOpid_RL_B.GainZ;

        /* End of MATLAB Function: '<S36>/MATLAB Function - fopid_altura' */
      }

      /* End of Outputs for SubSystem: '<Root>/Subsystem1' */

      /* MATLABSystem: '<S35>/SourceBlock' */
      FOpid_RL_B.SourceBlock_o1 = Sub_FOpid_RL_377.getLatestMessage
        (&rtb_SourceBlock_o2);

      /* Outputs for Enabled SubSystem: '<S35>/Enabled Subsystem' */
      FOpid_RL_EnabledSubsystem_k(FOpid_RL_B.SourceBlock_o1, &rtb_SourceBlock_o2,
        &FOpid_RL_B.EnabledSubsystem_a);

      /* End of Outputs for SubSystem: '<S35>/Enabled Subsystem' */

      /* Switch: '<Root>/Switch2' */
      if (FOpid_RL_B.SourceBlock_o1) {
        /* Switch: '<Root>/Switch2' */
        FOpid_RL_B.Switch2 = FOpid_RL_B.EnabledSubsystem_a.In1.data;
      } else {
        /* Switch: '<Root>/Switch2' incorporates:
         *  UnitDelay: '<Root>/Unit Delay2'
         */
        FOpid_RL_B.Switch2 = FOpid_RL_DW.UnitDelay2_DSTATE;
      }

      /* End of Switch: '<Root>/Switch2' */

      /* RateLimiter: '<Root>/Rate Limiter2' */
      FOpid_RL_B.rtb_CoordinateTransformationC_d = FOpid_RL_B.Switch2 -
        FOpid_RL_DW.PrevY;
      if (FOpid_RL_B.rtb_CoordinateTransformationC_d > 0.005) {
        /* RateLimiter: '<Root>/Rate Limiter2' */
        FOpid_RL_B.RateLimiter2 = FOpid_RL_DW.PrevY + 0.005;
      } else if (FOpid_RL_B.rtb_CoordinateTransformationC_d < -0.005) {
        /* RateLimiter: '<Root>/Rate Limiter2' */
        FOpid_RL_B.RateLimiter2 = FOpid_RL_DW.PrevY - 0.005;
      } else {
        /* RateLimiter: '<Root>/Rate Limiter2' */
        FOpid_RL_B.RateLimiter2 = FOpid_RL_B.Switch2;
      }

      FOpid_RL_DW.PrevY = FOpid_RL_B.RateLimiter2;

      /* End of RateLimiter: '<Root>/Rate Limiter2' */
    }

    /* Sum: '<Root>/Sum5' */
    FOpid_RL_B.Sum5 = FOpid_RL_B.RateLimiter2 - FOpid_RL_B.x[8];
    if (tmp_0) {
      /* Outputs for Enabled SubSystem: '<Root>/Subsystem3' incorporates:
       *  EnablePort: '<S38>/Enable'
       */
      if (i > 0) {
        /* MATLAB Function: '<S38>/MATLAB Function - fopid_yaw' incorporates:
         *  Constant: '<Root>/Constant10'
         *  Constant: '<Root>/Constant11'
         */
        FOpid_RL_B.u = ((((((((FOpid_RL_B.x[8] - 2.0 * FOpid_RL_DW.y1) +
                              FOpid_RL_DW.y2) - ((FOpid_RL_DW.y1 - 2.0 *
          FOpid_RL_DW.y2) + FOpid_RL_DW.y3)) + ((FOpid_RL_DW.y2 - 2.0 *
          FOpid_RL_DW.y3) + FOpid_RL_DW.y4) * 0.5) + ((FOpid_RL_DW.y3 - 2.0 *
          FOpid_RL_DW.y4) + FOpid_RL_DW.y5) * -0.5) + ((FOpid_RL_DW.y4 - 2.0 *
          FOpid_RL_DW.y5) + FOpid_RL_DW.y6) * 0.375) + ((FOpid_RL_DW.y5 - 2.0 *
          FOpid_RL_DW.y6) + FOpid_RL_DW.y7) * -0.375) * -0.0 +
                        (FOpid_RL_DW.u_prev - (FOpid_RL_B.Sum5 - FOpid_RL_DW.e1)))
          + (((((((2.0 * FOpid_RL_DW.e2 + FOpid_RL_DW.e1) + FOpid_RL_DW.e3) *
                 -0.6000000000000001 + ((2.0 * FOpid_RL_DW.e1 + FOpid_RL_B.Sum5)
                  + FOpid_RL_DW.e2)) + ((2.0 * FOpid_RL_DW.e3 + FOpid_RL_DW.e2)
                 + FOpid_RL_DW.e4) * 0.18000000000000005) + ((2.0 *
                 FOpid_RL_DW.e4 + FOpid_RL_DW.e3) + FOpid_RL_DW.e5) *
               -0.23600000000000004) + ((2.0 * FOpid_RL_DW.e5 + FOpid_RL_DW.e4)
               + FOpid_RL_DW.e6) * 0.12540000000000004) + ((2.0 * FOpid_RL_DW.e6
               + FOpid_RL_DW.e5) + FOpid_RL_DW.e7) * -0.15664800000000004) *
          -0.002450651390205588;
        if (!(FOpid_RL_B.u <= 0.09)) {
          FOpid_RL_B.u = 0.09;
        }

        if (!(FOpid_RL_B.u >= -0.09)) {
          FOpid_RL_B.u = -0.09;
        }

        FOpid_RL_DW.u_prev = FOpid_RL_B.u;
        FOpid_RL_DW.e7 = FOpid_RL_DW.e6;
        FOpid_RL_DW.e6 = FOpid_RL_DW.e5;
        FOpid_RL_DW.e5 = FOpid_RL_DW.e4;
        FOpid_RL_DW.e4 = FOpid_RL_DW.e3;
        FOpid_RL_DW.e3 = FOpid_RL_DW.e2;
        FOpid_RL_DW.e2 = FOpid_RL_DW.e1;
        FOpid_RL_DW.e1 = FOpid_RL_B.Sum5;
        FOpid_RL_DW.y7 = FOpid_RL_DW.y6;
        FOpid_RL_DW.y6 = FOpid_RL_DW.y5;
        FOpid_RL_DW.y5 = FOpid_RL_DW.y4;
        FOpid_RL_DW.y4 = FOpid_RL_DW.y3;
        FOpid_RL_DW.y3 = FOpid_RL_DW.y2;
        FOpid_RL_DW.y2 = FOpid_RL_DW.y1;
        FOpid_RL_DW.y1 = FOpid_RL_B.x[8];

        /* End of MATLAB Function: '<S38>/MATLAB Function - fopid_yaw' */
      }

      /* End of Outputs for SubSystem: '<Root>/Subsystem3' */

      /* Gain: '<Root>/Gain2' incorporates:
       *  Gain: '<Root>/Gain-roll_sp'
       */
      FOpid_RL_B.Saturation_roll_sp = -FOpid_RL_B.u;

      /* RateLimiter: '<Root>/Rate Limiter3' incorporates:
       *  Gain: '<Root>/Gain-roll_sp'
       */
      FOpid_RL_B.rtb_CoordinateTransformationC_d = -FOpid_RL_B.u -
        FOpid_RL_DW.PrevY_e;
      if (FOpid_RL_B.rtb_CoordinateTransformationC_d > FOpid_RL_period) {
        /* Gain: '<Root>/Gain2' */
        FOpid_RL_B.Saturation_roll_sp = FOpid_RL_DW.PrevY_e + FOpid_RL_period;
      } else if (FOpid_RL_B.rtb_CoordinateTransformationC_d < -0.01) {
        /* Gain: '<Root>/Gain2' */
        FOpid_RL_B.Saturation_roll_sp = FOpid_RL_DW.PrevY_e - 0.01;
      }

      FOpid_RL_DW.PrevY_e = FOpid_RL_B.Saturation_roll_sp;

      /* End of RateLimiter: '<Root>/Rate Limiter3' */

      /* Saturate: '<Root>/Saturation_roll_sp' */
      if (FOpid_RL_B.Saturation_roll_sp > 0.1) {
        /* Gain: '<Root>/Gain2' incorporates:
         *  Saturate: '<Root>/Saturation_roll_sp'
         */
        FOpid_RL_B.Saturation_roll_sp = 0.1;
      } else if (FOpid_RL_B.Saturation_roll_sp < -0.1) {
        /* Gain: '<Root>/Gain2' incorporates:
         *  Saturate: '<Root>/Saturation_roll_sp'
         */
        FOpid_RL_B.Saturation_roll_sp = -0.1;
      }

      /* End of Saturate: '<Root>/Saturation_roll_sp' */
    }

    /* Sum: '<Root>/Sum4' */
    FOpid_RL_B.Sum4 = FOpid_RL_B.Saturation_roll_sp - FOpid_RL_B.x[6];
    if (tmp_0) {
      /* Outputs for Enabled SubSystem: '<Root>/Subsystem2' incorporates:
       *  EnablePort: '<S37>/Enable'
       */
      if (i > 0) {
        /* MATLAB Function: '<S37>/MATLAB Function - fopid_roll' incorporates:
         *  Constant: '<Root>/Constant'
         *  Constant: '<Root>/Constant1'
         *  Constant: '<Root>/Constant2'
         */
        FOpid_RL_B.u_b = ((((((((FOpid_RL_DW.y1_g - 2.0 * FOpid_RL_DW.y2_e) +
          FOpid_RL_DW.y3_a) * -1.8 + ((FOpid_RL_B.x[6] - 2.0 * FOpid_RL_DW.y1_g)
          + FOpid_RL_DW.y2_e)) + ((FOpid_RL_DW.y2_e - 2.0 * FOpid_RL_DW.y3_a) +
          FOpid_RL_DW.y4_j) * 1.62) + ((FOpid_RL_DW.y3_a - 2.0 *
          FOpid_RL_DW.y4_j) + FOpid_RL_DW.y5_k) * -1.572) + ((FOpid_RL_DW.y4_j -
          2.0 * FOpid_RL_DW.y5_k) + FOpid_RL_DW.y6_k) * 1.5174) +
                           ((FOpid_RL_DW.y5_k - 2.0 * FOpid_RL_DW.y6_k) +
                            FOpid_RL_DW.y7_p) * -1.489464) * -0.0 +
                          ((FOpid_RL_B.Sum4 - FOpid_RL_DW.e1_p) * -0.9 +
                           FOpid_RL_DW.u_prev_e)) + (((((((2.0 *
          FOpid_RL_DW.e2_b + FOpid_RL_DW.e1_p) + FOpid_RL_DW.e3_m) *
          -0.6000000000000001 + ((2.0 * FOpid_RL_DW.e1_p + FOpid_RL_B.Sum4) +
          FOpid_RL_DW.e2_b)) + ((2.0 * FOpid_RL_DW.e3_m + FOpid_RL_DW.e2_b) +
          FOpid_RL_DW.e4_o) * 0.18000000000000005) + ((2.0 * FOpid_RL_DW.e4_o +
          FOpid_RL_DW.e3_m) + FOpid_RL_DW.e5_m) * -0.23600000000000004) + ((2.0 *
          FOpid_RL_DW.e5_m + FOpid_RL_DW.e4_o) + FOpid_RL_DW.e6_g) *
          0.12540000000000004) + ((2.0 * FOpid_RL_DW.e6_g + FOpid_RL_DW.e5_m) +
          FOpid_RL_DW.e7_m) * -0.15664800000000004) * -0.001225325695102794;
        if (!(FOpid_RL_B.u_b <= 0.1)) {
          FOpid_RL_B.u_b = 0.1;
        }

        if (!(FOpid_RL_B.u_b >= -0.1)) {
          FOpid_RL_B.u_b = -0.1;
        }

        FOpid_RL_DW.u_prev_e = FOpid_RL_B.u_b;
        FOpid_RL_DW.e7_m = FOpid_RL_DW.e6_g;
        FOpid_RL_DW.e6_g = FOpid_RL_DW.e5_m;
        FOpid_RL_DW.e5_m = FOpid_RL_DW.e4_o;
        FOpid_RL_DW.e4_o = FOpid_RL_DW.e3_m;
        FOpid_RL_DW.e3_m = FOpid_RL_DW.e2_b;
        FOpid_RL_DW.e2_b = FOpid_RL_DW.e1_p;
        FOpid_RL_DW.e1_p = FOpid_RL_B.Sum4;
        FOpid_RL_DW.y7_p = FOpid_RL_DW.y6_k;
        FOpid_RL_DW.y6_k = FOpid_RL_DW.y5_k;
        FOpid_RL_DW.y5_k = FOpid_RL_DW.y4_j;
        FOpid_RL_DW.y4_j = FOpid_RL_DW.y3_a;
        FOpid_RL_DW.y3_a = FOpid_RL_DW.y2_e;
        FOpid_RL_DW.y2_e = FOpid_RL_DW.y1_g;
        FOpid_RL_DW.y1_g = FOpid_RL_B.x[6];

        /* End of MATLAB Function: '<S37>/MATLAB Function - fopid_roll' */
      }

      /* End of Outputs for SubSystem: '<Root>/Subsystem2' */

      /* Saturate: '<Root>/Saturation2' */
      if (FOpid_RL_B.u_k > 0.1) {
        /* Gain: '<Root>/Gain3' */
        FOpid_RL_B.RateLimitertheta_sp = 0.1;
      } else if (FOpid_RL_B.u_k < -0.1) {
        /* Gain: '<Root>/Gain3' */
        FOpid_RL_B.RateLimitertheta_sp = -0.1;
      } else {
        /* Gain: '<Root>/Gain3' */
        FOpid_RL_B.RateLimitertheta_sp = FOpid_RL_B.u_k;
      }

      /* End of Saturate: '<Root>/Saturation2' */

      /* RateLimiter: '<Root>/Rate Limiter-theta_sp' */
      FOpid_RL_B.rtb_CoordinateTransformationC_d =
        FOpid_RL_B.RateLimitertheta_sp - FOpid_RL_DW.PrevY_g;
      if (FOpid_RL_B.rtb_CoordinateTransformationC_d > 0.004) {
        /* Gain: '<Root>/Gain3' incorporates:
         *  RateLimiter: '<Root>/Rate Limiter-theta_sp'
         */
        FOpid_RL_B.RateLimitertheta_sp = FOpid_RL_DW.PrevY_g + 0.004;
      } else if (FOpid_RL_B.rtb_CoordinateTransformationC_d < -0.004) {
        /* Gain: '<Root>/Gain3' incorporates:
         *  RateLimiter: '<Root>/Rate Limiter-theta_sp'
         */
        FOpid_RL_B.RateLimitertheta_sp = FOpid_RL_DW.PrevY_g - 0.004;
      }

      FOpid_RL_DW.PrevY_g = FOpid_RL_B.RateLimitertheta_sp;

      /* End of RateLimiter: '<Root>/Rate Limiter-theta_sp' */
    }

    /* Sum: '<Root>/Sum1' */
    FOpid_RL_B.Sum1 = FOpid_RL_B.RateLimitertheta_sp - FOpid_RL_B.x[7];
    if (tmp_0) {
      /* MATLAB Function: '<Root>/MATLAB Function - fopid_pitch' incorporates:
       *  Constant: '<Root>/Constant6'
       *  Constant: '<Root>/Constant7'
       *  Constant: '<Root>/Constant8'
       */
      FOpid_RL_B.u_c = ((((((((FOpid_RL_DW.y1_a - 2.0 * FOpid_RL_DW.y2_du) +
        FOpid_RL_DW.y3_h) * -1.8 + ((FOpid_RL_B.x[7] - 2.0 * FOpid_RL_DW.y1_a) +
        FOpid_RL_DW.y2_du)) + ((FOpid_RL_DW.y2_du - 2.0 * FOpid_RL_DW.y3_h) +
        FOpid_RL_DW.y4_p) * 1.62) + ((FOpid_RL_DW.y3_h - 2.0 * FOpid_RL_DW.y4_p)
        + FOpid_RL_DW.y5_ca) * -1.572) + ((FOpid_RL_DW.y4_p - 2.0 *
        FOpid_RL_DW.y5_ca) + FOpid_RL_DW.y6_f) * 1.5174) + ((FOpid_RL_DW.y5_ca -
        2.0 * FOpid_RL_DW.y6_f) + FOpid_RL_DW.y7_l) * -1.489464) *
                        -1.1773992067262726 + ((FOpid_RL_B.Sum1 -
        FOpid_RL_DW.e1_o) * -0.9 + FOpid_RL_DW.u_prev_fo)) + (((((((2.0 *
        FOpid_RL_DW.e2_h + FOpid_RL_DW.e1_o) + FOpid_RL_DW.e3_g) * -0.8 + ((2.0 *
        FOpid_RL_DW.e1_o + FOpid_RL_B.Sum1) + FOpid_RL_DW.e2_h)) + ((2.0 *
        FOpid_RL_DW.e3_g + FOpid_RL_DW.e2_h) + FOpid_RL_DW.e4_m) *
        0.32000000000000006) + ((2.0 * FOpid_RL_DW.e4_m + FOpid_RL_DW.e3_g) +
        FOpid_RL_DW.e5_b) * -0.35200000000000004) + ((2.0 * FOpid_RL_DW.e5_b +
        FOpid_RL_DW.e4_m) + FOpid_RL_DW.e6_h) * 0.23040000000000005) + ((2.0 *
        FOpid_RL_DW.e6_h + FOpid_RL_DW.e5_b) + FOpid_RL_DW.e7_f) *
        -0.24806400000000003) * -0.003330229480810401;
      if (!(FOpid_RL_B.u_c <= 0.1)) {
        FOpid_RL_B.u_c = 0.1;
      }

      if (!(FOpid_RL_B.u_c >= -0.1)) {
        FOpid_RL_B.u_c = -0.1;
      }

      FOpid_RL_DW.u_prev_fo = FOpid_RL_B.u_c;
      FOpid_RL_DW.e7_f = FOpid_RL_DW.e6_h;
      FOpid_RL_DW.e6_h = FOpid_RL_DW.e5_b;
      FOpid_RL_DW.e5_b = FOpid_RL_DW.e4_m;
      FOpid_RL_DW.e4_m = FOpid_RL_DW.e3_g;
      FOpid_RL_DW.e3_g = FOpid_RL_DW.e2_h;
      FOpid_RL_DW.e2_h = FOpid_RL_DW.e1_o;
      FOpid_RL_DW.e1_o = FOpid_RL_B.Sum1;
      FOpid_RL_DW.y7_l = FOpid_RL_DW.y6_f;
      FOpid_RL_DW.y6_f = FOpid_RL_DW.y5_ca;
      FOpid_RL_DW.y5_ca = FOpid_RL_DW.y4_p;
      FOpid_RL_DW.y4_p = FOpid_RL_DW.y3_h;
      FOpid_RL_DW.y3_h = FOpid_RL_DW.y2_du;
      FOpid_RL_DW.y2_du = FOpid_RL_DW.y1_a;
      FOpid_RL_DW.y1_a = FOpid_RL_B.x[7];

      /* End of MATLAB Function: '<Root>/MATLAB Function - fopid_pitch' */
    }

    /* Math: '<S32>/Math Function' incorporates:
     *  Constant: '<S32>/Constant'
     *  S-Function (sfun_tstart): '<S32>/startTime'
     *  Sum: '<S32>/Sum'
     */
    FOpid_RL_B.rtb_CoordinateTransformationC_d = rt_remd_snf(FOpid_RL_B.cosb -
      (0.0), 300.0);

    /* Lookup_n-D: '<S32>/Look-Up Table1' incorporates:
     *  Math: '<S33>/Square2'
     */
    FOpid_RL_B.Saturation1 = look1_binlxpw
      (FOpid_RL_B.rtb_CoordinateTransformationC_d,
       FOpid_RL_ConstP.LookUpTable1_bp01Data,
       FOpid_RL_ConstP.LookUpTable1_tableData, 16U);

    /* BusAssignment: '<Root>/Bus Assignment-MODELO' */
    memset(&FOpid_RL_B.BusAssignmentMODELO, 0, sizeof
           (SL_Bus_gazebo_msgs_SetEntityStateRequest));

    /* Saturate: '<Root>/Saturation1' */
    if (FOpid_RL_B.Saturation1 > 25.0) {
      /* Lookup_n-D: '<S32>/Look-Up Table1' incorporates:
       *  Saturate: '<Root>/Saturation1'
       */
      FOpid_RL_B.Saturation1 = 25.0;
    } else if (FOpid_RL_B.Saturation1 < 0.0) {
      /* Lookup_n-D: '<S32>/Look-Up Table1' incorporates:
       *  Saturate: '<Root>/Saturation1'
       */
      FOpid_RL_B.Saturation1 = 0.0;
    }

    /* End of Saturate: '<Root>/Saturation1' */

    /* Sum: '<Root>/Sum3' */
    FOpid_RL_B.Sum3 = FOpid_RL_B.Saturation1 - FOpid_RL_B.x[0];
    if (tmp_0) {
      /* MATLAB Function: '<Root>/MATLAB Function - fopid_velocidad' incorporates:
       *  Constant: '<Root>/Constant12'
       *  Constant: '<Root>/Constant13'
       *  Constant: '<Root>/Constant14'
       */
      FOpid_RL_B.u_j = ((((((((FOpid_RL_B.x[0] - 2.0 * FOpid_RL_DW.y1_g4) +
        FOpid_RL_DW.y2_d) - ((FOpid_RL_DW.y1_g4 - 2.0 * FOpid_RL_DW.y2_d) +
        FOpid_RL_DW.y3_d)) + ((FOpid_RL_DW.y2_d - 2.0 * FOpid_RL_DW.y3_d) +
        FOpid_RL_DW.y4_f) * 0.5) + ((FOpid_RL_DW.y3_d - 2.0 * FOpid_RL_DW.y4_f)
        + FOpid_RL_DW.y5_l) * -0.5) + ((FOpid_RL_DW.y4_f - 2.0 *
        FOpid_RL_DW.y5_l) + FOpid_RL_DW.y6_a) * 0.375) + ((FOpid_RL_DW.y5_l -
        2.0 * FOpid_RL_DW.y6_a) + FOpid_RL_DW.y7_e) * -0.375) * 0.0 +
                        ((FOpid_RL_B.Sum3 - FOpid_RL_DW.e1_c) * 0.095 +
                         FOpid_RL_DW.u_prev_a)) + (((((((2.0 * FOpid_RL_DW.e2_j
        + FOpid_RL_DW.e1_c) + FOpid_RL_DW.e3_o) * -0.6000000000000001 + ((2.0 *
        FOpid_RL_DW.e1_c + FOpid_RL_B.Sum3) + FOpid_RL_DW.e2_j)) + ((2.0 *
        FOpid_RL_DW.e3_o + FOpid_RL_DW.e2_j) + FOpid_RL_DW.e4_os) *
        0.18000000000000005) + ((2.0 * FOpid_RL_DW.e4_os + FOpid_RL_DW.e3_o) +
        FOpid_RL_DW.e5_mk) * -0.23600000000000004) + ((2.0 * FOpid_RL_DW.e5_mk +
        FOpid_RL_DW.e4_os) + FOpid_RL_DW.e6_p) * 0.12540000000000004) + ((2.0 *
        FOpid_RL_DW.e6_p + FOpid_RL_DW.e5_mk) + FOpid_RL_DW.e7_l) *
        -0.15664800000000004) * 0.0004901302780411177;
      if (!(FOpid_RL_B.u_j <= 0.8)) {
        FOpid_RL_B.u_j = 0.8;
      }

      if (!(FOpid_RL_B.u_j >= 0.0)) {
        FOpid_RL_B.u_j = 0.0;
      }

      FOpid_RL_DW.u_prev_a = FOpid_RL_B.u_j;
      FOpid_RL_DW.e7_l = FOpid_RL_DW.e6_p;
      FOpid_RL_DW.e6_p = FOpid_RL_DW.e5_mk;
      FOpid_RL_DW.e5_mk = FOpid_RL_DW.e4_os;
      FOpid_RL_DW.e4_os = FOpid_RL_DW.e3_o;
      FOpid_RL_DW.e3_o = FOpid_RL_DW.e2_j;
      FOpid_RL_DW.e2_j = FOpid_RL_DW.e1_c;
      FOpid_RL_DW.e1_c = FOpid_RL_B.Sum3;
      FOpid_RL_DW.y7_e = FOpid_RL_DW.y6_a;
      FOpid_RL_DW.y6_a = FOpid_RL_DW.y5_l;
      FOpid_RL_DW.y5_l = FOpid_RL_DW.y4_f;
      FOpid_RL_DW.y4_f = FOpid_RL_DW.y3_d;
      FOpid_RL_DW.y3_d = FOpid_RL_DW.y2_d;
      FOpid_RL_DW.y2_d = FOpid_RL_DW.y1_g4;
      FOpid_RL_DW.y1_g4 = FOpid_RL_B.x[0];

      /* End of MATLAB Function: '<Root>/MATLAB Function - fopid_velocidad' */

      /* MATLAB Function: '<Root>/MATLAB Function' */
      memset(&FOpid_RL_B.stringOut_d[0], 0, sizeof(uint8_T) << 7U);
      for (i = 0; i < 11; i++) {
        FOpid_RL_B.stringOut_d[i] = b_1[i];
      }

      FOpid_RL_B.lengthOut_g = 11U;

      /* End of MATLAB Function: '<Root>/MATLAB Function' */

      /* MATLAB Function: '<Root>/MATLAB Function-MODELO' */
      memset(&FOpid_RL_B.stringOut[0], 0, sizeof(uint8_T) << 7U);
      for (i = 0; i < 5; i++) {
        FOpid_RL_B.stringOut[i] = b_0[i];
      }

      FOpid_RL_B.lengthOut = 5U;

      /* End of MATLAB Function: '<Root>/MATLAB Function-MODELO' */
    }

    /* BusAssignment: '<Root>/Bus Assignment-MODELO' incorporates:
     *  MATLAB Function: '<Root>/MATLAB Function-ned_to_gazebo'
     */
    FOpid_RL_B.BusAssignmentMODELO.state.name_SL_Info.CurrentLength =
      FOpid_RL_B.lengthOut_g;
    FOpid_RL_B.BusAssignmentMODELO.state.pose.position.x = -FOpid_RL_B.x[10];
    FOpid_RL_B.BusAssignmentMODELO.state.pose.position.y = FOpid_RL_B.x[9];
    FOpid_RL_B.BusAssignmentMODELO.state.pose.position.z = FOpid_RL_B.GainZ;
    FOpid_RL_B.BusAssignmentMODELO.state.pose.orientation.w = FOpid_RL_B.sinb;
    FOpid_RL_B.BusAssignmentMODELO.state.pose.orientation.z = FOpid_RL_B.sinc;
    FOpid_RL_B.BusAssignmentMODELO.state.pose.orientation.y = FOpid_RL_B.cosa;
    FOpid_RL_B.BusAssignmentMODELO.state.pose.orientation.x = FOpid_RL_B.sina;
    memcpy(&FOpid_RL_B.BusAssignmentMODELO.state.name[0],
           &FOpid_RL_B.stringOut_d[0], sizeof(uint8_T) << 7U);
    memcpy(&FOpid_RL_B.BusAssignmentMODELO.state.reference_frame[0],
           &FOpid_RL_B.stringOut[0], sizeof(uint8_T) << 7U);
    FOpid_RL_B.BusAssignmentMODELO.state.reference_frame_SL_Info.CurrentLength =
      FOpid_RL_B.lengthOut;

    /* Outputs for Atomic SubSystem: '<Root>/Call Service' */
    /* MATLABSystem: '<S6>/ServiceCaller' */
    serverAvailableOnTime = ServCall_FOpid_RL_326.waitForServer(5.0);
    if (serverAvailableOnTime) {
      ServCall_FOpid_RL_326.call(&FOpid_RL_B.BusAssignmentMODELO, &tmp);
    }

    /* End of MATLABSystem: '<S6>/ServiceCaller' */
    /* End of Outputs for SubSystem: '<Root>/Call Service' */

    /* UnitConversion: '<S51>/Unit Conversion' */
    /* Unit Conversion - from: m to: ft
       Expression: output = (3.28084*input) + (0) */
    FOpid_RL_B.sina = 3.280839895013123 * FOpid_RL_B.x[11];

    /* Saturate: '<S84>/Limit Function 10ft to 1000ft' */
    if (FOpid_RL_B.sina > 1000.0) {
      FOpid_RL_B.rtb_CoordinateTransformationC_d = 1000.0;
    } else if (FOpid_RL_B.sina < 10.0) {
      FOpid_RL_B.rtb_CoordinateTransformationC_d = 10.0;
    } else {
      FOpid_RL_B.rtb_CoordinateTransformationC_d = FOpid_RL_B.sina;
    }

    /* End of Saturate: '<S84>/Limit Function 10ft to 1000ft' */

    /* Gain: '<S56>/Lw' */
    FOpid_RL_B.sinc = FOpid_RL_ConstB.UnitConversion_c;

    /* Interpolation_n-D: '<S66>/Medium//High Altitude Intensity' incorporates:
     *  PreLookup: '<S66>/PreLook-Up Index Search  (altitude)'
     *  PreLookup: '<S66>/PreLook-Up Index Search  (prob of exceed)'
     *  UnitConversion: '<S51>/Unit Conversion'
     */
    FOpid_RL_B.bpIndex[0] = plook_bincpa(FOpid_RL_B.sina,
      FOpid_RL_ConstP.PreLookUpIndexSearchaltitude_Br, 11U,
      &FOpid_RL_B.Product1_l[0], &FOpid_RL_DW.PreLookUpIndexSearchaltitude_DW);
    FOpid_RL_B.bpIndex[1] = FOpid_RL_ConstB.PreLookUpIndexSearchprobo_g;
    FOpid_RL_B.Product1_l[1] = FOpid_RL_ConstB.PreLookUpIndexSearchprobofe;
    FOpid_RL_B.sinb = intrp2d_la_pw(FOpid_RL_B.bpIndex, FOpid_RL_B.Product1_l,
      FOpid_RL_ConstP.MediumHighAltitudeIntensity_Tab, 12U,
      FOpid_RL_ConstP.MediumHighAltitudeIntensity_max);
    if (tmp_0) {
      /* Product: '<S59>/Product' incorporates:
       *  Product: '<S59>/Divide'
       *  RandomNumber: '<S59>/White Noise'
       */
      _mm_storeu_pd(&FOpid_RL_B.Product[0], _mm_mul_pd(_mm_loadu_pd
        (&FOpid_RL_ConstB.Divide[0]), _mm_loadu_pd(&FOpid_RL_DW.NextOutput[0])));
      _mm_storeu_pd(&FOpid_RL_B.Product[2], _mm_mul_pd(_mm_loadu_pd
        (&FOpid_RL_ConstB.Divide[2]), _mm_loadu_pd(&FOpid_RL_DW.NextOutput[2])));

      /* Memory: '<S33>/Memory' */
      FOpid_RL_B.Memory[0] = FOpid_RL_DW.Memory_PreviousInput[0];

      /* Memory: '<S33>/Memory1' */
      FOpid_RL_B.Memory1[0] = FOpid_RL_DW.Memory1_PreviousInput[0];

      /* Memory: '<S33>/Memory' */
      FOpid_RL_B.Memory[1] = FOpid_RL_DW.Memory_PreviousInput[1];

      /* Memory: '<S33>/Memory1' */
      FOpid_RL_B.Memory1[1] = FOpid_RL_DW.Memory1_PreviousInput[1];

      /* Memory: '<S33>/Memory' */
      FOpid_RL_B.Memory[2] = FOpid_RL_DW.Memory_PreviousInput[2];

      /* Memory: '<S33>/Memory1' */
      FOpid_RL_B.Memory1[2] = FOpid_RL_DW.Memory1_PreviousInput[2];
    }

    /* MATLAB Function: '<S33>/MATLAB Function - MODEL' incorporates:
     *  Memory: '<S33>/Memory'
     *  Memory: '<S33>/Memory1'
     *  SignalConversion generated from: '<S42>/ SFunction '
     */
    if (FOpid_RL_B.u_b <= 0.3490658503988659) {
      FOpid_RL_B.u1 = FOpid_RL_B.u_b;
    } else {
      FOpid_RL_B.u1 = 0.3490658503988659;
    }

    if (!(FOpid_RL_B.u1 >= -0.3490658503988659)) {
      FOpid_RL_B.u1 = -0.3490658503988659;
    }

    if (FOpid_RL_B.u_c <= 0.3490658503988659) {
      FOpid_RL_B.u2 = FOpid_RL_B.u_c;
    } else {
      FOpid_RL_B.u2 = 0.3490658503988659;
    }

    if (!(FOpid_RL_B.u2 >= -0.3490658503988659)) {
      FOpid_RL_B.u2 = -0.3490658503988659;
    }

    _mm_storeu_pd(&FOpid_RL_B.dv1[0], _mm_add_pd(_mm_loadu_pd(&FOpid_RL_B.x[0]),
      _mm_loadu_pd(&FOpid_RL_B.Memory[0])));
    FOpid_RL_B.cosa = FOpid_RL_B.x[2] + FOpid_RL_B.Memory[2];
    FOpid_RL_B.rtb_CoordinateTransformationC_l = sqrt((FOpid_RL_B.dv1[0] *
      FOpid_RL_B.dv1[0] + FOpid_RL_B.dv1[1] * FOpid_RL_B.dv1[1]) +
      FOpid_RL_B.cosa * FOpid_RL_B.cosa);
    if (FOpid_RL_B.rtb_CoordinateTransformationC_l < 0.5) {
      FOpid_RL_B.rtb_CoordinateTransformationC_l = 0.5;
      FOpid_RL_B.cosa = 0.0;
      FOpid_RL_B.rtb_CoordinateTransformationC_o = 0.0;
    } else {
      FOpid_RL_B.cosa = rt_atan2d_snf(FOpid_RL_B.cosa, FOpid_RL_B.dv1[0]);
      FOpid_RL_B.rtb_CoordinateTransformationC_o = FOpid_RL_B.dv1[1] /
        FOpid_RL_B.rtb_CoordinateTransformationC_l;
      if ((FOpid_RL_B.rtb_CoordinateTransformationC_o >= 1.0) || rtIsNaN
          (FOpid_RL_B.rtb_CoordinateTransformationC_o)) {
        FOpid_RL_B.rtb_CoordinateTransformationC_o = 1.0;
      }

      if (FOpid_RL_B.rtb_CoordinateTransformationC_o <= -1.0) {
        FOpid_RL_B.rtb_CoordinateTransformationC_o = -1.0;
      }

      FOpid_RL_B.rtb_CoordinateTransformationC_o = asin
        (FOpid_RL_B.rtb_CoordinateTransformationC_o);
    }

    FOpid_RL_B.q_aero = FOpid_RL_B.Memory1[1] + FOpid_RL_B.x[4];
    if ((-FOpid_RL_B.x[11] - 0.0505 <= 0.001) || rtIsNaN(-FOpid_RL_B.x[11] -
         0.0505)) {
      FOpid_RL_B.cosc = 0.001;
    } else {
      FOpid_RL_B.cosc = -FOpid_RL_B.x[11] - 0.0505;
    }

    if ((-FOpid_RL_B.x[11] + 0.3475 <= 0.001) || rtIsNaN(-FOpid_RL_B.x[11] +
         0.3475)) {
      FOpid_RL_B.cosb = 0.001;
    } else {
      FOpid_RL_B.cosb = -FOpid_RL_B.x[11] + 0.3475;
    }

    FOpid_RL_B.Q = FOpid_RL_B.rtb_CoordinateTransformationC_l *
      FOpid_RL_B.rtb_CoordinateTransformationC_l * 0.6125;
    FOpid_RL_B.wbe_b[0] = FOpid_RL_B.x[3];
    FOpid_RL_B.wbe_b[1] = FOpid_RL_B.x[4];
    FOpid_RL_B.wbe_b[2] = FOpid_RL_B.x[5];
    FOpid_RL_B.Vd1 = FOpid_RL_B.cosc / 0.6977;
    FOpid_RL_B.CD_ih_IGE = FOpid_RL_B.cosb / 0.3808;
    FOpid_RL_B.cosb = ((FOpid_RL_B.cosa - -0.06544984694978735) +
                       0.02617993877991494) * 4.960409453036515;
    FOpid_RL_B.cosc = (((FOpid_RL_B.cosa - -0.04363323129985824) +
                        0.008726646259971648) - (0.56 /
      FOpid_RL_B.rtb_CoordinateTransformationC_l * 0.35 * FOpid_RL_B.q_aero +
      (FOpid_RL_B.cosa - -0.06544984694978735) * 0.35)) * 4.838774891736003;
    FOpid_RL_B.CL_w_IGE = (rt_powd_snf(FOpid_RL_B.Vd1, 0.787) * 288.0 * exp
      (rt_powd_snf(FOpid_RL_B.Vd1, 0.327) * -9.14) * 0.9798630886207249 /
      5.912947654095886 + 1.0) * FOpid_RL_B.cosb;
    FOpid_RL_B.CL_h_IGE = (rt_powd_snf(FOpid_RL_B.CD_ih_IGE, 0.787) * 288.0 *
      exp(rt_powd_snf(FOpid_RL_B.CD_ih_IGE, 0.327) * -9.14) * 0.9562859020012823
      / 5.35300902982722 + 1.0) * FOpid_RL_B.cosc;
    FOpid_RL_B.CD_iw_IGE = ((1.0 - exp(rt_powd_snf(FOpid_RL_B.Vd1, 0.814) *
      -4.74) * 0.9791664172678959) - exp(rt_powd_snf(FOpid_RL_B.Vd1, 0.758) *
      -3.88) * (FOpid_RL_B.Vd1 * FOpid_RL_B.Vd1)) * (FOpid_RL_B.CL_w_IGE *
      FOpid_RL_B.CL_w_IGE / 21.205750411731103);
    FOpid_RL_B.CD_ih_IGE = ((1.0 - exp(rt_powd_snf(FOpid_RL_B.CD_ih_IGE, 0.814) *
      -4.74) * 0.9677063475148586) - exp(rt_powd_snf(FOpid_RL_B.CD_ih_IGE, 0.758)
      * -3.88) * (FOpid_RL_B.CD_ih_IGE * FOpid_RL_B.CD_ih_IGE)) *
      (FOpid_RL_B.CL_h_IGE * FOpid_RL_B.CL_h_IGE / 18.943803701146454);
    FOpid_RL_B.u2_deg = FOpid_RL_B.u2 * 180.0 / 3.141592653589793;
    FOpid_RL_B.u2_deg = ((FOpid_RL_B.u2_deg * FOpid_RL_B.u2_deg * -1.08E-5 +
                          0.000715 * FOpid_RL_B.u2_deg) * 0.02164 +
                         ((FOpid_RL_B.CD_iw_IGE * 0.0649 + 0.0027258) +
                          FOpid_RL_B.CD_ih_IGE * 0.02164)) * FOpid_RL_B.Q;
    FOpid_RL_B.Ltot = (FOpid_RL_B.CL_w_IGE * 0.0649 + FOpid_RL_B.CL_h_IGE *
                       0.02164) * FOpid_RL_B.Q;
    FOpid_RL_B.CQ = -0.019 * FOpid_RL_B.rtb_CoordinateTransformationC_o * 180.0 /
      3.141592653589793;
    FOpid_RL_B.FA_b_idx_0 = sin(FOpid_RL_B.cosa);
    FOpid_RL_B.FA_b_idx_1 = cos(FOpid_RL_B.cosa);
    FOpid_RL_B.R[0] = FOpid_RL_B.FA_b_idx_1;
    FOpid_RL_B.R[3] = 0.0;
    FOpid_RL_B.R[6] = -FOpid_RL_B.FA_b_idx_0;
    FOpid_RL_B.R[2] = FOpid_RL_B.FA_b_idx_0;
    FOpid_RL_B.R[5] = 0.0;
    FOpid_RL_B.R[8] = FOpid_RL_B.FA_b_idx_1;
    FOpid_RL_B.Dtot[0] = -FOpid_RL_B.u2_deg;
    FOpid_RL_B.Dtot[1] = FOpid_RL_B.CQ * FOpid_RL_B.Q * 0.0649;
    FOpid_RL_B.Dtot[2] = -FOpid_RL_B.Ltot;
    FOpid_RL_B.R[1] = 0.0;
    FOpid_RL_B.FA_b_idx_0 = 0.0;
    FOpid_RL_B.R[4] = 1.0;
    FOpid_RL_B.FA_b_idx_1 = 0.0;
    FOpid_RL_B.R[7] = 0.0;
    FOpid_RL_B.FA_b_idx_2 = 0.0;
    for (i = 0; i < 3; i++) {
      _mm_storeu_pd(&FOpid_RL_B.dv1[0], _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
        (&FOpid_RL_B.R[3 * i]), _mm_set1_pd(FOpid_RL_B.Dtot[i])), _mm_set_pd
        (FOpid_RL_B.FA_b_idx_1, FOpid_RL_B.FA_b_idx_0)));
      FOpid_RL_B.FA_b_idx_0 = FOpid_RL_B.dv1[0];
      FOpid_RL_B.FA_b_idx_1 = FOpid_RL_B.dv1[1];
      FOpid_RL_B.FA_b_idx_2 += FOpid_RL_B.R[3 * i + 2] * FOpid_RL_B.Dtot[i];
    }

    FOpid_RL_B.Fg_b_idx_2 = 2.0 * FOpid_RL_B.rtb_CoordinateTransformationC_l;
    FOpid_RL_B.Cl = ((FOpid_RL_B.Memory1[0] + FOpid_RL_B.x[3]) * 0.6977 /
                     FOpid_RL_B.Fg_b_idx_2 * -2.0 + -0.12 *
                     FOpid_RL_B.rtb_CoordinateTransformationC_o) + -0.5 *
      FOpid_RL_B.u1;
    FOpid_RL_B.u2 = ((exp(FOpid_RL_B.Vd1 * -4.0) * -0.05 + -1.14 *
                      FOpid_RL_B.cosa) + FOpid_RL_B.q_aero * 0.093 /
                     FOpid_RL_B.Fg_b_idx_2 * -5.0) + -3.0 * FOpid_RL_B.u2;
    if (FOpid_RL_B.u <= 0.2617993877991494) {
      FOpid_RL_B.q_aero = FOpid_RL_B.u;
    } else {
      FOpid_RL_B.q_aero = 0.2617993877991494;
    }

    if (!(FOpid_RL_B.q_aero >= -0.2617993877991494)) {
      FOpid_RL_B.q_aero = -0.2617993877991494;
    }

    FOpid_RL_B.u1 = (((FOpid_RL_B.Memory1[2] + FOpid_RL_B.x[5]) * 0.6977 /
                      FOpid_RL_B.Fg_b_idx_2 * -1.5 + -0.1146 *
                      FOpid_RL_B.rtb_CoordinateTransformationC_o) + -0.3 *
                     FOpid_RL_B.q_aero) + -0.05 * FOpid_RL_B.u1;
    if (FOpid_RL_B.u_j <= 1.0) {
      FOpid_RL_B.q_aero = FOpid_RL_B.u_j;
    } else {
      FOpid_RL_B.q_aero = 1.0;
    }

    if (!(FOpid_RL_B.q_aero >= 0.0)) {
      FOpid_RL_B.q_aero = 0.0;
    }

    FOpid_RL_B.Vd1 = (32.0 - FOpid_RL_B.rtb_CoordinateTransformationC_l) *
      FOpid_RL_B.q_aero + FOpid_RL_B.rtb_CoordinateTransformationC_l;
    if (FOpid_RL_B.u_j <= 1.0) {
      FOpid_RL_B.q_aero = FOpid_RL_B.u_j;
    } else {
      FOpid_RL_B.q_aero = 1.0;
    }

    if (!(FOpid_RL_B.q_aero >= 0.0)) {
      FOpid_RL_B.q_aero = 0.0;
    }

    FOpid_RL_B.q_aero = (32.0 - FOpid_RL_B.rtb_CoordinateTransformationC_l) *
      FOpid_RL_B.q_aero + FOpid_RL_B.rtb_CoordinateTransformationC_l;
    FOpid_RL_B.Vd1 = 0.004422606215997847 * FOpid_RL_B.Vd1 * (FOpid_RL_B.Vd1 -
      FOpid_RL_B.rtb_CoordinateTransformationC_l);
    FOpid_RL_B.q_aero = 0.004422606215997847 * FOpid_RL_B.q_aero *
      (FOpid_RL_B.q_aero - FOpid_RL_B.rtb_CoordinateTransformationC_l);
    FOpid_RL_B.FE1_b[0] = FOpid_RL_B.Vd1 * 0.9961946980917455;
    FOpid_RL_B.FE1_b[2] = -FOpid_RL_B.Vd1 * 0.08715574274765817;
    FOpid_RL_B.FE2_b_idx_0 = FOpid_RL_B.q_aero * 0.9961946980917455;
    FOpid_RL_B.FE2_b_idx_2 = -FOpid_RL_B.q_aero * 0.08715574274765817;
    FOpid_RL_B.q_aero = -9.81 * sin(FOpid_RL_B.x[7]) * 1.2;
    _mm_storeu_pd(&FOpid_RL_B.dv1[0], _mm_mul_pd(_mm_mul_pd(_mm_mul_pd
      (_mm_set1_pd(9.81), _mm_set1_pd(cos(FOpid_RL_B.x[7]))), _mm_set_pd(cos
      (FOpid_RL_B.x[6]), sin(FOpid_RL_B.x[6]))), _mm_set1_pd(1.2)));
    FOpid_RL_B.Vd1 = FOpid_RL_B.dv1[0];
    FOpid_RL_B.Fg_b_idx_2 = FOpid_RL_B.dv1[1];
    FOpid_RL_B.FE_b = FOpid_RL_B.FE1_b[0] + FOpid_RL_B.FE2_b_idx_0;
    FOpid_RL_B.FE_b_idx_0 = FOpid_RL_B.FE_b;
    FOpid_RL_B.F_b[0] = (FOpid_RL_B.q_aero + FOpid_RL_B.FE_b) +
      FOpid_RL_B.FA_b_idx_0;
    FOpid_RL_B.F_b[1] = FOpid_RL_B.dv1[0] + FOpid_RL_B.FA_b_idx_1;
    FOpid_RL_B.FE_b = FOpid_RL_B.FE1_b[2] + FOpid_RL_B.FE2_b_idx_2;
    FOpid_RL_B.F_b[2] = (FOpid_RL_B.dv1[1] + FOpid_RL_B.FE_b) +
      FOpid_RL_B.FA_b_idx_2;
    FOpid_RL_B.L_dec = 0.6977 * FOpid_RL_B.Q * 0.0649;
    FOpid_RL_B.Mcg_b_idx_0 = (0.0834 * FOpid_RL_B.FE1_b[2] + -0.0834 *
      FOpid_RL_B.FE2_b_idx_2) + FOpid_RL_B.L_dec * FOpid_RL_B.Cl;
    FOpid_RL_B.Q = 0.093 * FOpid_RL_B.Q * 0.0649 * FOpid_RL_B.u2 + ((-0.0396 *
      FOpid_RL_B.FE1_b[0] - 0.0721 * FOpid_RL_B.FE1_b[2]) + (-0.0396 *
      FOpid_RL_B.FE2_b_idx_0 - 0.0721 * FOpid_RL_B.FE2_b_idx_2));
    FOpid_RL_B.FE2_b_idx_0 = ((0.0 - 0.0834 * FOpid_RL_B.FE1_b[0]) + (0.0 -
      -0.0834 * FOpid_RL_B.FE2_b_idx_0)) + FOpid_RL_B.L_dec * FOpid_RL_B.u1;
    FOpid_RL_B.L_dec = FOpid_RL_B.Mcg_b_idx_0 - 0.07841480417423635 *
      FOpid_RL_B.FE2_b_idx_0;
    FOpid_RL_B.FE2_b_idx_2 = FOpid_RL_B.FE2_b_idx_0 - 0.2258731897286114 *
      FOpid_RL_B.Mcg_b_idx_0;
    memcpy(&FOpid_RL_B.R[0], &FOpid_RL_B.x[0], 9U * sizeof(real_T));
    FOpid_RL_B.FE1_b[0] = FOpid_RL_B.R[0];
    FOpid_RL_B.FE1_b[1] = FOpid_RL_B.R[1];
    FOpid_RL_B.FE1_b[2] = FOpid_RL_B.R[2];
    FOpid_RL_B.c_phi = cos(FOpid_RL_B.R[6]);
    FOpid_RL_B.s_phi = sin(FOpid_RL_B.R[6]);
    FOpid_RL_B.c_the = cos(FOpid_RL_B.R[7]);
    FOpid_RL_B.s_the = sin(FOpid_RL_B.R[7]);
    FOpid_RL_B.c_psi = cos(FOpid_RL_B.R[8]);
    FOpid_RL_B.s_psi = sin(FOpid_RL_B.R[8]);
    FOpid_RL_B.R[0] = FOpid_RL_B.c_the * FOpid_RL_B.c_psi;
    FOpid_RL_B.R_tmp = FOpid_RL_B.s_phi * FOpid_RL_B.s_the;
    FOpid_RL_B.R[3] = FOpid_RL_B.R_tmp * FOpid_RL_B.c_psi - FOpid_RL_B.c_phi *
      FOpid_RL_B.s_psi;
    FOpid_RL_B.R_tmp_b = FOpid_RL_B.c_phi * FOpid_RL_B.s_the;
    FOpid_RL_B.R[6] = FOpid_RL_B.R_tmp_b * FOpid_RL_B.c_psi + FOpid_RL_B.s_phi *
      FOpid_RL_B.s_psi;
    FOpid_RL_B.R[1] = FOpid_RL_B.c_the * FOpid_RL_B.s_psi;
    FOpid_RL_B.R[4] = FOpid_RL_B.R_tmp * FOpid_RL_B.s_psi + FOpid_RL_B.c_phi *
      FOpid_RL_B.c_psi;
    FOpid_RL_B.R[7] = FOpid_RL_B.R_tmp_b * FOpid_RL_B.s_psi - FOpid_RL_B.s_phi *
      FOpid_RL_B.c_psi;
    FOpid_RL_B.R[2] = -FOpid_RL_B.s_the;
    FOpid_RL_B.R[5] = FOpid_RL_B.s_phi * FOpid_RL_B.c_the;
    FOpid_RL_B.R[8] = FOpid_RL_B.c_phi * FOpid_RL_B.c_the;
    _mm_storeu_pd(&FOpid_RL_B.Dtot[0], _mm_sub_pd(_mm_mul_pd(_mm_set_pd
      (FOpid_RL_B.x[0], FOpid_RL_B.x[2]), _mm_loadu_pd(&FOpid_RL_B.x[4])),
      _mm_mul_pd(_mm_loadu_pd(&FOpid_RL_B.x[1]), _mm_set_pd(FOpid_RL_B.x[3],
      FOpid_RL_B.x[5]))));
    FOpid_RL_B.Dtot[2] = FOpid_RL_B.x[1] * FOpid_RL_B.x[3] - FOpid_RL_B.x[0] *
      FOpid_RL_B.x[4];
    FOpid_RL_B.dv[0] = 1.0;
    _mm_storeu_pd(&FOpid_RL_B.dv1[0], _mm_mul_pd(_mm_set_pd(cos(FOpid_RL_B.x[6]),
      sin(FOpid_RL_B.x[6])), _mm_set1_pd(tan(FOpid_RL_B.x[7]))));
    FOpid_RL_B.dv[3] = FOpid_RL_B.dv1[0];
    FOpid_RL_B.dv[6] = FOpid_RL_B.dv1[1];
    FOpid_RL_B.dv[1] = 0.0;
    FOpid_RL_B.dv[4] = cos(FOpid_RL_B.x[6]);
    FOpid_RL_B.dv[7] = -sin(FOpid_RL_B.x[6]);
    FOpid_RL_B.dv[2] = 0.0;
    _mm_storeu_pd(&FOpid_RL_B.dv1[0], _mm_div_pd(_mm_set_pd(cos(FOpid_RL_B.x[6]),
      sin(FOpid_RL_B.x[6])), _mm_set1_pd(cos(FOpid_RL_B.x[7]))));
    FOpid_RL_B.dv[5] = FOpid_RL_B.dv1[0];
    FOpid_RL_B.dv[8] = FOpid_RL_B.dv1[1];
    FOpid_RL_B.c_phi = 0.0;
    FOpid_RL_B.s_phi = 0.0;
    FOpid_RL_B.c_the = 0.0;
    FOpid_RL_B.s_the = 0.0;
    FOpid_RL_B.c_psi = 0.0;
    FOpid_RL_B.s_psi = 0.0;
    for (i = 0; i < 3; i++) {
      _mm_storeu_pd(&FOpid_RL_B.dv1[0], _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
        (&FOpid_RL_B.dv[3 * i]), _mm_set1_pd(FOpid_RL_B.wbe_b[i])), _mm_set_pd
        (FOpid_RL_B.s_phi, FOpid_RL_B.c_phi)));
      FOpid_RL_B.c_phi = FOpid_RL_B.dv1[0];
      FOpid_RL_B.s_phi = FOpid_RL_B.dv1[1];
      _mm_storeu_pd(&FOpid_RL_B.dv1[0], _mm_add_pd(_mm_mul_pd(_mm_set_pd
        (FOpid_RL_B.R[3 * i], FOpid_RL_B.dv[3 * i + 2]), _mm_set_pd
        (FOpid_RL_B.FE1_b[i], FOpid_RL_B.wbe_b[i])), _mm_set_pd(FOpid_RL_B.s_the,
        FOpid_RL_B.c_the)));
      FOpid_RL_B.c_the = FOpid_RL_B.dv1[0];
      FOpid_RL_B.s_the = FOpid_RL_B.dv1[1];
      _mm_storeu_pd(&FOpid_RL_B.dv1[0], _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
        (&FOpid_RL_B.R[3 * i + 1]), _mm_set1_pd(FOpid_RL_B.FE1_b[i])),
        _mm_set_pd(FOpid_RL_B.s_psi, FOpid_RL_B.c_psi)));
      FOpid_RL_B.c_psi = FOpid_RL_B.dv1[0];
      FOpid_RL_B.s_psi = FOpid_RL_B.dv1[1];
      FOpid_RL_B.XDOT[i] = 0.8333333333333334 * FOpid_RL_B.F_b[i] -
        FOpid_RL_B.Dtot[i];
    }

    FOpid_RL_B.XDOT[3] = ((0.023669 * FOpid_RL_B.L_dec + 0.001856 *
      FOpid_RL_B.FE2_b_idx_2) - (-2.6338496E-5 * FOpid_RL_B.x[3] +
      0.000144843342 * FOpid_RL_B.x[5]) * FOpid_RL_B.x[4]) / 0.000191043437;
    FOpid_RL_B.XDOT[4] = ((FOpid_RL_B.Q - -0.015451999999999999 * FOpid_RL_B.x[3]
      * FOpid_RL_B.x[5]) - (FOpid_RL_B.x[3] * FOpid_RL_B.x[3] - FOpid_RL_B.x[5] *
      FOpid_RL_B.x[5]) * 0.001856) / 0.017695;
    FOpid_RL_B.XDOT[5] = ((-2.6338496E-5 * FOpid_RL_B.x[5] +
      -7.443598999999999E-5 * FOpid_RL_B.x[3]) * FOpid_RL_B.x[4] + (0.001856 *
      FOpid_RL_B.L_dec + 0.008217 * FOpid_RL_B.FE2_b_idx_2)) / 0.000191043437;
    FOpid_RL_B.XDOT[9] = FOpid_RL_B.s_the;
    FOpid_RL_B.XDOT[10] = FOpid_RL_B.c_psi;
    FOpid_RL_B.XDOT[11] = FOpid_RL_B.s_psi;
    if (!(FOpid_RL_B.u2_deg >= 0.001)) {
      FOpid_RL_B.u2_deg = 0.001;
    }

    FOpid_RL_B.XDOT[12] = FOpid_RL_B.Ltot / FOpid_RL_B.u2_deg;
    FOpid_RL_B.XDOT[19] = FOpid_RL_B.CQ;
    FOpid_RL_B.XDOT[20] = FOpid_RL_B.Cl;
    FOpid_RL_B.XDOT[21] = FOpid_RL_B.u2;
    FOpid_RL_B.XDOT[22] = FOpid_RL_B.u1;
    FOpid_RL_B.XDOT[23] = FOpid_RL_B.cosa;
    FOpid_RL_B.XDOT[24] = FOpid_RL_B.rtb_CoordinateTransformationC_o;
    FOpid_RL_B.XDOT[25] = FOpid_RL_B.cosb;
    FOpid_RL_B.XDOT[26] = FOpid_RL_B.cosc;
    FOpid_RL_B.XDOT[27] = FOpid_RL_B.CL_w_IGE;
    FOpid_RL_B.XDOT[28] = FOpid_RL_B.CL_h_IGE;
    FOpid_RL_B.XDOT[29] = FOpid_RL_B.CD_iw_IGE;
    FOpid_RL_B.XDOT[30] = FOpid_RL_B.CD_ih_IGE;
    FOpid_RL_B.XDOT[6] = FOpid_RL_B.c_phi;
    FOpid_RL_B.XDOT[13] = FOpid_RL_B.F_b[0];
    FOpid_RL_B.XDOT[16] = FOpid_RL_B.Mcg_b_idx_0;
    FOpid_RL_B.XDOT[31] = FOpid_RL_B.q_aero;
    FOpid_RL_B.XDOT[34] = FOpid_RL_B.FE_b_idx_0;
    FOpid_RL_B.XDOT[37] = FOpid_RL_B.FA_b_idx_0;
    FOpid_RL_B.XDOT[7] = FOpid_RL_B.s_phi;
    FOpid_RL_B.XDOT[14] = FOpid_RL_B.F_b[1];
    FOpid_RL_B.XDOT[17] = FOpid_RL_B.Q;
    FOpid_RL_B.XDOT[32] = FOpid_RL_B.Vd1;
    FOpid_RL_B.XDOT[35] = 0.0;
    FOpid_RL_B.XDOT[38] = FOpid_RL_B.FA_b_idx_1;
    FOpid_RL_B.XDOT[8] = FOpid_RL_B.c_the;
    FOpid_RL_B.XDOT[15] = FOpid_RL_B.F_b[2];
    FOpid_RL_B.XDOT[18] = FOpid_RL_B.FE2_b_idx_0;
    FOpid_RL_B.XDOT[33] = FOpid_RL_B.Fg_b_idx_2;
    FOpid_RL_B.XDOT[36] = FOpid_RL_B.FE_b;
    FOpid_RL_B.XDOT[39] = FOpid_RL_B.FA_b_idx_2;

    /* UnitConversion: '<S57>/Unit Conversion' incorporates:
     *  MATLAB Function: '<S33>/MATLAB Function - MODEL'
     */
    /* Unit Conversion - from: m/s to: ft/s
       Expression: output = (3.28084*input) + (0) */
    FOpid_RL_B.rtb_CoordinateTransformationC_l *= 3.280839895013123;

    /* Outputs for Enabled SubSystem: '<S49>/Hpgw' incorporates:
     *  EnablePort: '<S60>/Enable'
     */
    if (tmp_0 && rtsiIsModeUpdateTimeStep(&(&FOpid_RL_M)->solverInfo) &&
        !FOpid_RL_DW.Hpgw_MODE) {
      (void) memset(&(FOpid_RL_XDis.pgw_p_CSTATE), 0,
                    2*sizeof(boolean_T));

      /* InitializeConditions for Integrator: '<S60>/pgw_p' */
      FOpid_RL_X.pgw_p_CSTATE[0] = 0.0;
      FOpid_RL_X.pgw_p_CSTATE[1] = 0.0;
      FOpid_RL_DW.Hpgw_MODE = true;
    }

    if (FOpid_RL_DW.Hpgw_MODE) {
      /* Fcn: '<S60>/sqrt(0.8//V)' */
      FOpid_RL_B.cosa = sqrt(0.8 / FOpid_RL_B.rtb_CoordinateTransformationC_l);

      /* Product: '<S60>/w3' */
      FOpid_RL_B.rtb_CoordinateTransformationC_o =
        FOpid_RL_B.rtb_CoordinateTransformationC_l * FOpid_RL_ConstB.w4;

      /* Product: '<S60>/w' incorporates:
       *  Fcn: '<S60>/sqrt(0.8//V)'
       *  Gain: '<S56>/Lw'
       *  Integrator: '<S60>/pgw_p'
       *  Math: '<S60>/L^1//3'
       *  Product: '<S60>/Lug//V1'
       *  Product: '<S60>/w1'
       *  Product: '<S60>/w2'
       *  Sum: '<S60>/Sum'
       */
      FOpid_RL_B.w_o[0] = (FOpid_RL_B.cosa / rt_powd_snf
                           (FOpid_RL_B.rtb_CoordinateTransformationC_d,
                            0.3333333333333333) * FOpid_RL_ConstB.u16 *
                           FOpid_RL_B.Product[3] - FOpid_RL_X.pgw_p_CSTATE[0]) *
        FOpid_RL_B.rtb_CoordinateTransformationC_o;

      /* Math: '<S60>/L^1//3' */
      if (FOpid_RL_B.sinc < 0.0) {
        FOpid_RL_B.q_aero = -rt_powd_snf(-FOpid_RL_B.sinc, 0.3333333333333333);
      } else {
        FOpid_RL_B.q_aero = rt_powd_snf(FOpid_RL_B.sinc, 0.3333333333333333);
      }

      /* Product: '<S60>/w' incorporates:
       *  Fcn: '<S60>/sqrt(0.8//V)'
       *  Integrator: '<S60>/pgw_p'
       *  Product: '<S60>/Lug//V1'
       *  Product: '<S60>/w1'
       *  Product: '<S60>/w2'
       *  Sum: '<S60>/Sum'
       */
      FOpid_RL_B.w_o[1] = (FOpid_RL_B.cosa / FOpid_RL_B.q_aero *
                           FOpid_RL_ConstB.u16 * FOpid_RL_B.Product[3] -
                           FOpid_RL_X.pgw_p_CSTATE[1]) *
        FOpid_RL_B.rtb_CoordinateTransformationC_o;

      /* Product: '<S60>/sigma_w' incorporates:
       *  Integrator: '<S60>/pgw_p'
       */
      _mm_storeu_pd(&FOpid_RL_B.sigma_w[0], _mm_mul_pd(_mm_set_pd
        (FOpid_RL_B.sinb, FOpid_RL_ConstB.sigma_wg), _mm_loadu_pd
        (&FOpid_RL_X.pgw_p_CSTATE[0])));
    }

    /* End of Outputs for SubSystem: '<S49>/Hpgw' */

    /* Outputs for Enabled SubSystem: '<S50>/Hwgw(s)' incorporates:
     *  EnablePort: '<S65>/Enable'
     */
    if (tmp_0 && rtsiIsModeUpdateTimeStep(&(&FOpid_RL_M)->solverInfo) &&
        !FOpid_RL_DW.Hwgws_MODE) {
      (void) memset(&(FOpid_RL_XDis.wg_p1_CSTATE), 0,
                    4*sizeof(boolean_T));

      /* InitializeConditions for Integrator: '<S65>/wg_p1' */
      FOpid_RL_X.wg_p1_CSTATE[0] = 0.0;

      /* InitializeConditions for Integrator: '<S65>/wg_p2' */
      FOpid_RL_X.wg_p2_CSTATE[0] = 0.0;

      /* InitializeConditions for Integrator: '<S65>/wg_p1' */
      FOpid_RL_X.wg_p1_CSTATE[1] = 0.0;

      /* InitializeConditions for Integrator: '<S65>/wg_p2' */
      FOpid_RL_X.wg_p2_CSTATE[1] = 0.0;
      FOpid_RL_DW.Hwgws_MODE = true;
    }

    if (FOpid_RL_DW.Hwgws_MODE) {
      /* Product: '<S65>/Lwg//V' incorporates:
       *  Gain: '<S56>/Lw'
       */
      FOpid_RL_B.rtb_CoordinateTransformationC_o =
        FOpid_RL_B.rtb_CoordinateTransformationC_d /
        FOpid_RL_B.rtb_CoordinateTransformationC_l;

      /* Product: '<S65>/w' incorporates:
       *  Gain: '<S65>/1//pi'
       *  Integrator: '<S65>/wg_p1'
       *  Product: '<S65>/Lug//V1'
       *  Sqrt: '<S65>/sqrt1'
       *  Sum: '<S65>/Sum'
       */
      FOpid_RL_B.cosa = (sqrt(0.3183098861837907 *
        FOpid_RL_B.rtb_CoordinateTransformationC_o) * FOpid_RL_B.Product[2] -
                         FOpid_RL_X.wg_p1_CSTATE[0]) /
        FOpid_RL_B.rtb_CoordinateTransformationC_o;
      FOpid_RL_B.w[0] = FOpid_RL_B.cosa;

      /* Product: '<S65>/w ' incorporates:
       *  Integrator: '<S65>/wg_p1'
       *  Integrator: '<S65>/wg_p2'
       *  Product: '<S65>/Lwg//V '
       *  Sum: '<S65>/Sum1'
       */
      FOpid_RL_B.w_a[0] = (FOpid_RL_B.cosa * FOpid_RL_ConstB.sqrt_a *
                           FOpid_RL_B.rtb_CoordinateTransformationC_o +
                           (FOpid_RL_X.wg_p1_CSTATE[0] -
                            FOpid_RL_X.wg_p2_CSTATE[0])) /
        FOpid_RL_B.rtb_CoordinateTransformationC_o;

      /* Product: '<S65>/Lwg//V' */
      FOpid_RL_B.rtb_CoordinateTransformationC_o = FOpid_RL_B.sinc /
        FOpid_RL_B.rtb_CoordinateTransformationC_l;

      /* Product: '<S65>/w' incorporates:
       *  Gain: '<S65>/1//pi'
       *  Integrator: '<S65>/wg_p1'
       *  Product: '<S65>/Lug//V1'
       *  Sqrt: '<S65>/sqrt1'
       *  Sum: '<S65>/Sum'
       */
      FOpid_RL_B.cosa = (sqrt(0.3183098861837907 *
        FOpid_RL_B.rtb_CoordinateTransformationC_o) * FOpid_RL_B.Product[2] -
                         FOpid_RL_X.wg_p1_CSTATE[1]) /
        FOpid_RL_B.rtb_CoordinateTransformationC_o;
      FOpid_RL_B.w[1] = FOpid_RL_B.cosa;

      /* Product: '<S65>/w ' incorporates:
       *  Integrator: '<S65>/wg_p1'
       *  Integrator: '<S65>/wg_p2'
       *  Product: '<S65>/Lwg//V '
       *  Sum: '<S65>/Sum1'
       */
      FOpid_RL_B.w_a[1] = (FOpid_RL_B.cosa * FOpid_RL_ConstB.sqrt_a *
                           FOpid_RL_B.rtb_CoordinateTransformationC_o +
                           (FOpid_RL_X.wg_p1_CSTATE[1] -
                            FOpid_RL_X.wg_p2_CSTATE[1])) /
        FOpid_RL_B.rtb_CoordinateTransformationC_o;

      /* Product: '<S65>/Lwg//V 1' incorporates:
       *  Integrator: '<S65>/wg_p2'
       */
      _mm_storeu_pd(&FOpid_RL_B.LwgV1[0], _mm_mul_pd(_mm_set_pd(FOpid_RL_B.sinb,
        FOpid_RL_ConstB.sigma_wg), _mm_loadu_pd(&FOpid_RL_X.wg_p2_CSTATE[0])));
    }

    /* End of Outputs for SubSystem: '<S50>/Hwgw(s)' */

    /* Outputs for Enabled SubSystem: '<S49>/Hqgw' incorporates:
     *  EnablePort: '<S61>/Enable'
     */
    if (tmp_0 && rtsiIsModeUpdateTimeStep(&(&FOpid_RL_M)->solverInfo) &&
        !FOpid_RL_DW.Hqgw_MODE) {
      (void) memset(&(FOpid_RL_XDis.qgw_p_CSTATE), 0,
                    2*sizeof(boolean_T));

      /* InitializeConditions for Integrator: '<S61>/qgw_p' */
      FOpid_RL_X.qgw_p_CSTATE[0] = 0.0;
      FOpid_RL_X.qgw_p_CSTATE[1] = 0.0;
      FOpid_RL_DW.Hqgw_MODE = true;
    }

    if (FOpid_RL_DW.Hqgw_MODE) {
      /* Gain: '<S61>/pi//4' */
      FOpid_RL_B.sinc = 0.7853981633974483 *
        FOpid_RL_B.rtb_CoordinateTransformationC_l;

      /* Product: '<S61>/w' incorporates:
       *  Integrator: '<S61>/qgw_p'
       *  Product: '<S61>/wg//V'
       *  Sum: '<S61>/Sum'
       */
      FOpid_RL_B.cosa = (FOpid_RL_B.LwgV1[0] /
                         FOpid_RL_B.rtb_CoordinateTransformationC_l -
                         FOpid_RL_X.qgw_p_CSTATE[0]) * (FOpid_RL_B.sinc /
        FOpid_RL_ConstB.UnitConversion_n);
      FOpid_RL_B.w_e0[0] = FOpid_RL_B.cosa;

      /* UnaryMinus: '<S61>/Unary Minus' */
      FOpid_RL_B.UnaryMinus[0] = -FOpid_RL_B.cosa;

      /* Product: '<S61>/w' incorporates:
       *  Integrator: '<S61>/qgw_p'
       *  Product: '<S61>/wg//V'
       *  Sum: '<S61>/Sum'
       */
      FOpid_RL_B.cosa = (FOpid_RL_B.LwgV1[1] /
                         FOpid_RL_B.rtb_CoordinateTransformationC_l -
                         FOpid_RL_X.qgw_p_CSTATE[1]) * (FOpid_RL_B.sinc /
        FOpid_RL_ConstB.UnitConversion_n);
      FOpid_RL_B.w_e0[1] = FOpid_RL_B.cosa;

      /* UnaryMinus: '<S61>/Unary Minus' */
      FOpid_RL_B.UnaryMinus[1] = -FOpid_RL_B.cosa;
    }

    /* End of Outputs for SubSystem: '<S49>/Hqgw' */

    /* Saturate: '<S67>/Limit Height h<1000ft' */
    if (FOpid_RL_B.sina > 1000.0) {
      FOpid_RL_B.cosa = 1000.0;
    } else if (FOpid_RL_B.sina < 0.0) {
      FOpid_RL_B.cosa = 0.0;
    } else {
      FOpid_RL_B.cosa = FOpid_RL_B.sina;
    }

    /* Product: '<S67>/sigma_ug, sigma_vg' incorporates:
     *  Fcn: '<S67>/Low Altitude Intensity'
     *  Saturate: '<S67>/Limit Height h<1000ft'
     */
    FOpid_RL_B.cosa = 1.0 / rt_powd_snf(0.000823 * FOpid_RL_B.cosa + 0.177, 0.4)
      * FOpid_RL_ConstB.sigma_wg;

    /* Fcn: '<S84>/Low Altitude Scale Length' */
    FOpid_RL_B.rtb_CoordinateTransformationC_d /= rt_powd_snf(0.000823 *
      FOpid_RL_B.rtb_CoordinateTransformationC_d + 0.177, 1.2);

    /* Gain: '<S56>/Lv' */
    FOpid_RL_B.sinc = FOpid_RL_ConstB.UnitConversion_c;

    /* Outputs for Enabled SubSystem: '<S50>/Hvgw(s)' incorporates:
     *  EnablePort: '<S64>/Enable'
     */
    if (tmp_0 && rtsiIsModeUpdateTimeStep(&(&FOpid_RL_M)->solverInfo) &&
        !FOpid_RL_DW.Hvgws_MODE) {
      (void) memset(&(FOpid_RL_XDis.vg_p1_CSTATE), 0,
                    4*sizeof(boolean_T));

      /* InitializeConditions for Integrator: '<S64>/vg_p1' */
      FOpid_RL_X.vg_p1_CSTATE[0] = 0.0;

      /* InitializeConditions for Integrator: '<S64>/vgw_p2' */
      FOpid_RL_X.vgw_p2_CSTATE[0] = 0.0;

      /* InitializeConditions for Integrator: '<S64>/vg_p1' */
      FOpid_RL_X.vg_p1_CSTATE[1] = 0.0;

      /* InitializeConditions for Integrator: '<S64>/vgw_p2' */
      FOpid_RL_X.vgw_p2_CSTATE[1] = 0.0;
      FOpid_RL_DW.Hvgws_MODE = true;
    }

    if (FOpid_RL_DW.Hvgws_MODE) {
      /* Product: '<S64>/Lvg//V' incorporates:
       *  Gain: '<S56>/Lv'
       */
      FOpid_RL_B.rtb_CoordinateTransformationC_o =
        FOpid_RL_B.rtb_CoordinateTransformationC_d /
        FOpid_RL_B.rtb_CoordinateTransformationC_l;

      /* Product: '<S64>/w' incorporates:
       *  Gain: '<S64>/(1//pi)'
       *  Integrator: '<S64>/vg_p1'
       *  Product: '<S64>/Lug//V1'
       *  Sqrt: '<S64>/sqrt'
       *  Sum: '<S64>/Sum'
       */
      FOpid_RL_B.cosb = (sqrt(0.3183098861837907 *
        FOpid_RL_B.rtb_CoordinateTransformationC_o) * FOpid_RL_B.Product[1] -
                         FOpid_RL_X.vg_p1_CSTATE[0]) /
        FOpid_RL_B.rtb_CoordinateTransformationC_o;
      FOpid_RL_B.w_g[0] = FOpid_RL_B.cosb;

      /* Product: '<S64>/w ' incorporates:
       *  Gain: '<S64>/sqrt(3)'
       *  Integrator: '<S64>/vg_p1'
       *  Integrator: '<S64>/vgw_p2'
       *  Product: '<S64>/Lvg//V '
       *  Sum: '<S64>/Sum1'
       */
      FOpid_RL_B.w_e[0] = (FOpid_RL_B.cosb *
                           FOpid_RL_B.rtb_CoordinateTransformationC_o *
                           1.7320508075688772 + (FOpid_RL_X.vg_p1_CSTATE[0] -
        FOpid_RL_X.vgw_p2_CSTATE[0])) /
        FOpid_RL_B.rtb_CoordinateTransformationC_o;

      /* Product: '<S64>/Lvg//V' */
      FOpid_RL_B.rtb_CoordinateTransformationC_o = FOpid_RL_B.sinc /
        FOpid_RL_B.rtb_CoordinateTransformationC_l;

      /* Product: '<S64>/w' incorporates:
       *  Gain: '<S64>/(1//pi)'
       *  Integrator: '<S64>/vg_p1'
       *  Product: '<S64>/Lug//V1'
       *  Sqrt: '<S64>/sqrt'
       *  Sum: '<S64>/Sum'
       */
      FOpid_RL_B.cosb = (sqrt(0.3183098861837907 *
        FOpid_RL_B.rtb_CoordinateTransformationC_o) * FOpid_RL_B.Product[1] -
                         FOpid_RL_X.vg_p1_CSTATE[1]) /
        FOpid_RL_B.rtb_CoordinateTransformationC_o;
      FOpid_RL_B.w_g[1] = FOpid_RL_B.cosb;

      /* Product: '<S64>/w ' incorporates:
       *  Gain: '<S64>/sqrt(3)'
       *  Integrator: '<S64>/vg_p1'
       *  Integrator: '<S64>/vgw_p2'
       *  Product: '<S64>/Lvg//V '
       *  Sum: '<S64>/Sum1'
       */
      FOpid_RL_B.w_e[1] = (FOpid_RL_B.cosb *
                           FOpid_RL_B.rtb_CoordinateTransformationC_o *
                           1.7320508075688772 + (FOpid_RL_X.vg_p1_CSTATE[1] -
        FOpid_RL_X.vgw_p2_CSTATE[1])) /
        FOpid_RL_B.rtb_CoordinateTransformationC_o;

      /* Product: '<S64>/w 1' incorporates:
       *  Integrator: '<S64>/vgw_p2'
       */
      _mm_storeu_pd(&FOpid_RL_B.w1[0], _mm_mul_pd(_mm_set_pd(FOpid_RL_B.sinb,
        FOpid_RL_B.cosa), _mm_loadu_pd(&FOpid_RL_X.vgw_p2_CSTATE[0])));
    }

    /* End of Outputs for SubSystem: '<S50>/Hvgw(s)' */

    /* Outputs for Enabled SubSystem: '<S49>/Hrgw' incorporates:
     *  EnablePort: '<S62>/Enable'
     */
    if (tmp_0 && rtsiIsModeUpdateTimeStep(&(&FOpid_RL_M)->solverInfo) &&
        !FOpid_RL_DW.Hrgw_MODE) {
      (void) memset(&(FOpid_RL_XDis.rgw_p_CSTATE), 0,
                    2*sizeof(boolean_T));

      /* InitializeConditions for Integrator: '<S62>/rgw_p' */
      FOpid_RL_X.rgw_p_CSTATE[0] = 0.0;
      FOpid_RL_X.rgw_p_CSTATE[1] = 0.0;
      FOpid_RL_DW.Hrgw_MODE = true;
    }

    if (FOpid_RL_DW.Hrgw_MODE) {
      /* Product: '<S62>/w' incorporates:
       *  Gain: '<S62>/pi//3'
       *  Integrator: '<S62>/rgw_p'
       *  Product: '<S62>/vg//V'
       */
      _mm_storeu_pd(&FOpid_RL_B.w_d[0], _mm_mul_pd(_mm_sub_pd(_mm_div_pd
        (_mm_loadu_pd(&FOpid_RL_B.w1[0]), _mm_set1_pd
         (FOpid_RL_B.rtb_CoordinateTransformationC_l)), _mm_loadu_pd
        (&FOpid_RL_X.rgw_p_CSTATE[0])), _mm_div_pd(_mm_set1_pd
        (1.0471975511965976 * FOpid_RL_B.rtb_CoordinateTransformationC_l),
        _mm_set1_pd(FOpid_RL_ConstB.UnitConversion_n))));
    }

    /* End of Outputs for SubSystem: '<S49>/Hrgw' */

    /* Angle2Dcm: '<S33>/Rotation Angles to Direction Cosine Matrix' */
    FOpid_RL_B.sinc = cos(FOpid_RL_B.x[6]);
    FOpid_RL_B.rtb_CoordinateTransformationC_o = sin(FOpid_RL_B.x[6]);
    FOpid_RL_B.cosb = -sin(FOpid_RL_B.x[6]);
    FOpid_RL_B.cosc = cos(FOpid_RL_B.x[6]);
    FOpid_RL_B.FA_b_idx_0 = cos(FOpid_RL_B.x[7]);
    FOpid_RL_B.u2 = -sin(FOpid_RL_B.x[7]);
    FOpid_RL_B.CL_w_IGE = sin(FOpid_RL_B.x[7]);
    FOpid_RL_B.CL_h_IGE = cos(FOpid_RL_B.x[7]);
    FOpid_RL_B.CD_iw_IGE = cos(FOpid_RL_B.x[8]);
    FOpid_RL_B.CD_ih_IGE = sin(FOpid_RL_B.x[8]);
    FOpid_RL_B.u2_deg = -sin(FOpid_RL_B.x[8]);
    FOpid_RL_B.FA_b_idx_1 = cos(FOpid_RL_B.x[8]);
    FOpid_RL_B.Ltot = 0.0 * FOpid_RL_B.CL_w_IGE + FOpid_RL_B.FA_b_idx_0;
    FOpid_RL_B.CQ = 0.0 * FOpid_RL_B.CL_h_IGE + FOpid_RL_B.u2;
    FOpid_RL_B.FA_b_idx_2 = FOpid_RL_B.CD_iw_IGE * 0.0;
    FOpid_RL_B.Cl = 0.0 * FOpid_RL_B.FA_b_idx_0;
    FOpid_RL_B.FA_b_idx_0 = (FOpid_RL_B.Cl + FOpid_RL_B.FA_b_idx_2) +
      FOpid_RL_B.CD_ih_IGE * FOpid_RL_B.CL_w_IGE;
    FOpid_RL_B.CD_iw_IGE += FOpid_RL_B.CD_ih_IGE * 0.0;
    FOpid_RL_B.u2 *= 0.0;
    FOpid_RL_B.CD_ih_IGE = (FOpid_RL_B.u2 + FOpid_RL_B.FA_b_idx_2) +
      FOpid_RL_B.CD_ih_IGE * FOpid_RL_B.CL_h_IGE;
    FOpid_RL_B.FA_b_idx_2 = FOpid_RL_B.u2_deg * 0.0;
    FOpid_RL_B.CL_w_IGE = (FOpid_RL_B.Cl + FOpid_RL_B.FA_b_idx_2) +
      FOpid_RL_B.CL_w_IGE * FOpid_RL_B.FA_b_idx_1;
    FOpid_RL_B.u2_deg += FOpid_RL_B.FA_b_idx_1 * 0.0;
    FOpid_RL_B.CL_h_IGE = (FOpid_RL_B.u2 + FOpid_RL_B.FA_b_idx_2) +
      FOpid_RL_B.FA_b_idx_1 * FOpid_RL_B.CL_h_IGE;
    FOpid_RL_B.FA_b_idx_1 = FOpid_RL_B.CQ * 0.0;
    FOpid_RL_B.RotationAnglestoDirectionCo[0] = (FOpid_RL_B.Ltot *
      FOpid_RL_B.sinc + 0.0 * FOpid_RL_B.cosb) + FOpid_RL_B.FA_b_idx_1;
    FOpid_RL_B.FA_b_idx_2 = FOpid_RL_B.CD_ih_IGE * 0.0;
    FOpid_RL_B.RotationAnglestoDirectionCo[1] = (FOpid_RL_B.sinc *
      FOpid_RL_B.FA_b_idx_0 + FOpid_RL_B.cosb * FOpid_RL_B.CD_iw_IGE) +
      FOpid_RL_B.FA_b_idx_2;
    FOpid_RL_B.Cl = FOpid_RL_B.CL_h_IGE * 0.0;
    FOpid_RL_B.RotationAnglestoDirectionCo[2] = (FOpid_RL_B.sinc *
      FOpid_RL_B.CL_w_IGE + FOpid_RL_B.cosb * FOpid_RL_B.u2_deg) + FOpid_RL_B.Cl;
    FOpid_RL_B.RotationAnglestoDirectionCo[3] = (FOpid_RL_B.Ltot *
      FOpid_RL_B.rtb_CoordinateTransformationC_o + 0.0 * FOpid_RL_B.cosc) +
      FOpid_RL_B.FA_b_idx_1;
    FOpid_RL_B.RotationAnglestoDirectionCo[4] =
      (FOpid_RL_B.rtb_CoordinateTransformationC_o * FOpid_RL_B.FA_b_idx_0 +
       FOpid_RL_B.CD_iw_IGE * FOpid_RL_B.cosc) + FOpid_RL_B.FA_b_idx_2;
    FOpid_RL_B.RotationAnglestoDirectionCo[5] =
      (FOpid_RL_B.rtb_CoordinateTransformationC_o * FOpid_RL_B.CL_w_IGE +
       FOpid_RL_B.cosc * FOpid_RL_B.u2_deg) + FOpid_RL_B.Cl;
    FOpid_RL_B.RotationAnglestoDirectionCo[6] = FOpid_RL_B.Ltot * 0.0 +
      FOpid_RL_B.CQ;
    FOpid_RL_B.RotationAnglestoDirectionCo[7] = (FOpid_RL_B.FA_b_idx_0 * 0.0 +
      FOpid_RL_B.CD_iw_IGE * 0.0) + FOpid_RL_B.CD_ih_IGE;
    FOpid_RL_B.RotationAnglestoDirectionCo[8] = (FOpid_RL_B.CL_w_IGE * 0.0 +
      FOpid_RL_B.u2_deg * 0.0) + FOpid_RL_B.CL_h_IGE;

    /* If: '<S54>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' incorporates:
     *  Constant: '<S68>/max_height_low'
     *  Product: '<S68>/Product1'
     *  Product: '<S73>/Product1'
     *  Product: '<S73>/Product2'
     *  Product: '<S75>/Product1'
     *  Product: '<S75>/Product2'
     *  Sum: '<S68>/Sum1'
     *  Sum: '<S68>/Sum2'
     *  Sum: '<S68>/Sum3'
     *  Sum: '<S73>/Sum'
     *  Sum: '<S75>/Sum'
     */
    rtPrevAction = FOpid_RL_DW.ifHeightMaxlowaltitudeelseifHei;
    if (rtsiIsModeUpdateTimeStep(&(&FOpid_RL_M)->solverInfo)) {
      if (FOpid_RL_B.sina <= 1000.0) {
        rtAction = 0;
      } else if (FOpid_RL_B.sina >= 2000.0) {
        rtAction = 1;
      } else {
        rtAction = 2;
      }

      FOpid_RL_DW.ifHeightMaxlowaltitudeelseifHei = rtAction;
    } else {
      rtAction = FOpid_RL_DW.ifHeightMaxlowaltitudeelseifHei;
    }

    if (rtPrevAction != rtAction) {
      rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)->solverInfo,
        true);
    }

    switch (rtAction) {
     case 0:
      /* Outputs for IfAction SubSystem: '<S54>/Low altitude  rates' incorporates:
       *  ActionPort: '<S69>/Action Port'
       */
      /* SignalConversion generated from: '<S74>/Vector Concatenate' */
      FOpid_RL_B.Reshape1_b[2] = FOpid_RL_B.w_d[0];

      /* Trigonometry: '<S75>/Trigonometric Function1' */
      FOpid_RL_B.sinc = sin(FOpid_RL_ConstB.UnitConversion);
      FOpid_RL_B.rtb_CoordinateTransformationC_o = cos
        (FOpid_RL_ConstB.UnitConversion);
      _mm_storeu_pd(&FOpid_RL_B.Reshape1_b[0], _mm_add_pd(_mm_mul_pd(_mm_set_pd
        (FOpid_RL_B.sinc, FOpid_RL_B.sigma_w[0]), _mm_set_pd(FOpid_RL_B.sigma_w
        [0], FOpid_RL_B.rtb_CoordinateTransformationC_o)), _mm_mul_pd(_mm_mul_pd
        (_mm_set_pd(FOpid_RL_B.UnaryMinus[0], FOpid_RL_B.sinc), _mm_set_pd
         (FOpid_RL_B.rtb_CoordinateTransformationC_o, FOpid_RL_B.UnaryMinus[0])),
        _mm_set_pd(1.0, -1.0))));

      /* Product: '<S74>/Product' incorporates:
       *  Angle2Dcm: '<S33>/Rotation Angles to Direction Cosine Matrix'
       *  Product: '<S75>/Product1'
       *  Product: '<S75>/Product2'
       *  Reshape: '<S74>/Reshape'
       *  Reshape: '<S74>/Reshape1'
       *  Sum: '<S75>/Sum'
       */
      FOpid_RL_B.sinc = 0.0;
      FOpid_RL_B.rtb_CoordinateTransformationC_o = 0.0;
      FOpid_RL_B.cosb = 0.0;
      for (i = 0; i < 3; i++) {
        _mm_storeu_pd(&FOpid_RL_B.dv1[0], _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
          (&FOpid_RL_B.RotationAnglestoDirectionCo[3 * i]), _mm_set1_pd
          (FOpid_RL_B.Reshape1_b[i])), _mm_set_pd
          (FOpid_RL_B.rtb_CoordinateTransformationC_o, FOpid_RL_B.sinc)));
        FOpid_RL_B.sinc = FOpid_RL_B.dv1[0];
        FOpid_RL_B.rtb_CoordinateTransformationC_o = FOpid_RL_B.dv1[1];
        FOpid_RL_B.cosb += FOpid_RL_B.RotationAnglestoDirectionCo[3 * i + 2] *
          FOpid_RL_B.Reshape1_b[i];
      }

      FOpid_RL_B.wbe_b[2] = FOpid_RL_B.cosb;
      FOpid_RL_B.wbe_b[1] = FOpid_RL_B.rtb_CoordinateTransformationC_o;
      FOpid_RL_B.wbe_b[0] = FOpid_RL_B.sinc;

      /* End of Product: '<S74>/Product' */
      /* End of Outputs for SubSystem: '<S54>/Low altitude  rates' */
      break;

     case 1:
      /* Outputs for IfAction SubSystem: '<S54>/Medium//High  altitude rates' incorporates:
       *  ActionPort: '<S70>/Action Port'
       */
      /* Gain: '<S70>/Gain' */
      FOpid_RL_B.wbe_b[0] = FOpid_RL_B.sigma_w[1];
      FOpid_RL_B.wbe_b[1] = FOpid_RL_B.UnaryMinus[1];
      FOpid_RL_B.wbe_b[2] = FOpid_RL_B.w_d[1];

      /* End of Outputs for SubSystem: '<S54>/Medium//High  altitude rates' */
      break;

     default:
      /* Outputs for IfAction SubSystem: '<S54>/Interpolate  rates' incorporates:
       *  ActionPort: '<S68>/Action Port'
       */
      /* Trigonometry: '<S73>/Trigonometric Function' */
      FOpid_RL_B.sinc = sin(FOpid_RL_ConstB.UnitConversion);
      FOpid_RL_B.rtb_CoordinateTransformationC_o = cos
        (FOpid_RL_ConstB.UnitConversion);
      _mm_storeu_pd(&FOpid_RL_B.wbe_b[0], _mm_add_pd(_mm_mul_pd(_mm_set_pd
        (FOpid_RL_B.sinc, FOpid_RL_B.sigma_w[0]), _mm_set_pd(FOpid_RL_B.sigma_w
        [0], FOpid_RL_B.rtb_CoordinateTransformationC_o)), _mm_mul_pd(_mm_mul_pd
        (_mm_set_pd(FOpid_RL_B.UnaryMinus[0], FOpid_RL_B.sinc), _mm_set_pd
         (FOpid_RL_B.rtb_CoordinateTransformationC_o, FOpid_RL_B.UnaryMinus[0])),
        _mm_set_pd(1.0, -1.0))));

      /* SignalConversion generated from: '<S72>/Vector Concatenate' incorporates:
       *  Product: '<S73>/Product1'
       *  Product: '<S73>/Product2'
       *  Sum: '<S73>/Sum'
       */
      FOpid_RL_B.wbe_b[2] = FOpid_RL_B.w_d[0];

      /* Product: '<S72>/Product' incorporates:
       *  Angle2Dcm: '<S33>/Rotation Angles to Direction Cosine Matrix'
       *  Reshape: '<S72>/Reshape'
       *  Reshape: '<S72>/Reshape1'
       */
      FOpid_RL_B.sinc = 0.0;
      FOpid_RL_B.rtb_CoordinateTransformationC_o = 0.0;
      FOpid_RL_B.cosb = 0.0;
      for (i = 0; i < 3; i++) {
        _mm_storeu_pd(&FOpid_RL_B.dv1[0], _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
          (&FOpid_RL_B.RotationAnglestoDirectionCo[3 * i]), _mm_set1_pd
          (FOpid_RL_B.wbe_b[i])), _mm_set_pd
          (FOpid_RL_B.rtb_CoordinateTransformationC_o, FOpid_RL_B.sinc)));
        FOpid_RL_B.sinc = FOpid_RL_B.dv1[0];
        FOpid_RL_B.rtb_CoordinateTransformationC_o = FOpid_RL_B.dv1[1];
        FOpid_RL_B.cosb += FOpid_RL_B.RotationAnglestoDirectionCo[3 * i + 2] *
          FOpid_RL_B.wbe_b[i];
      }

      FOpid_RL_B.Reshape1_b[2] = FOpid_RL_B.cosb;
      FOpid_RL_B.Reshape1_b[1] = FOpid_RL_B.rtb_CoordinateTransformationC_o;
      FOpid_RL_B.Reshape1_b[0] = FOpid_RL_B.sinc;
      _mm_storeu_pd(&FOpid_RL_B.wbe_b[0], _mm_add_pd(_mm_div_pd(_mm_mul_pd
        (_mm_sub_pd(_mm_set_pd(FOpid_RL_B.UnaryMinus[1], FOpid_RL_B.sigma_w[1]),
                    _mm_loadu_pd(&FOpid_RL_B.Reshape1_b[0])), _mm_sub_pd
         (_mm_set1_pd(FOpid_RL_B.sina), _mm_set1_pd(1000.0))), _mm_set1_pd
        (FOpid_RL_ConstB.Sum_a)), _mm_loadu_pd(&FOpid_RL_B.Reshape1_b[0])));

      /* Sum: '<S68>/Sum3' incorporates:
       *  Constant: '<S68>/max_height_low'
       *  Product: '<S68>/Product1'
       *  Product: '<S72>/Product'
       *  Reshape: '<S72>/Reshape1'
       *  Sum: '<S68>/Sum1'
       *  Sum: '<S68>/Sum2'
       */
      FOpid_RL_B.wbe_b[2] = (FOpid_RL_B.w_d[1] - FOpid_RL_B.cosb) *
        (FOpid_RL_B.sina - 1000.0) / FOpid_RL_ConstB.Sum_a + FOpid_RL_B.cosb;

      /* End of Outputs for SubSystem: '<S54>/Interpolate  rates' */
      break;
    }

    /* End of If: '<S54>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
    if (tmp_0) {
      /* MATLABSystem: '<S44>/SourceBlock' */
      FOpid_RL_B.SourceBlock_o1_k = Sub_FOpid_RL_423.getLatestMessage
        (&rtb_SourceBlock_o2_dd);

      /* Outputs for Enabled SubSystem: '<S44>/Enabled Subsystem' */
      FOpid_RL_EnabledSubsystem(FOpid_RL_B.SourceBlock_o1_k,
        &rtb_SourceBlock_o2_dd, &FOpid_RL_B.EnabledSubsystem);

      /* End of Outputs for SubSystem: '<S44>/Enabled Subsystem' */

      /* Gain: '<S39>/Output' incorporates:
       *  RandomNumber: '<S39>/White Noise'
       */
      FOpid_RL_B.Output = 10.0 * FOpid_RL_DW.NextOutput_k;
    }

    /* Switch: '<S33>/Switch1' incorporates:
     *  Constant: '<S33>/Constant2'
     */
    if (!FOpid_RL_B.EnabledSubsystem.In1.data) {
      FOpid_RL_B.wbe_b[0] = 0.0;
      FOpid_RL_B.wbe_b[1] = 0.0;
      FOpid_RL_B.wbe_b[2] = 0.0;
    }

    /* End of Switch: '<S33>/Switch1' */

    /* TransferFcn: '<S33>/Transfer Fcn1' */
    FOpid_RL_B.sinc = -0.0003571 * FOpid_RL_X.TransferFcn1_CSTATE + 0.03571 *
      FOpid_RL_B.Output;
    if (tmp_0) {
      /* MATLABSystem: '<S46>/SourceBlock' */
      FOpid_RL_B.SourceBlock_o1_d = Sub_FOpid_RL_445.getLatestMessage
        (&rtb_SourceBlock_o2_k);

      /* Outputs for Enabled SubSystem: '<S46>/Enabled Subsystem' */
      FOpid_RL_EnabledSubsystem_k(FOpid_RL_B.SourceBlock_o1_d,
        &rtb_SourceBlock_o2_k, &FOpid_RL_B.EnabledSubsystem_p);

      /* End of Outputs for SubSystem: '<S46>/Enabled Subsystem' */
    }

    /* Switch: '<S33>/Switch3' incorporates:
     *  Constant: '<S33>/Constant4'
     */
    if (!(FOpid_RL_B.EnabledSubsystem_p.In1.data != 0.0)) {
      FOpid_RL_B.sinc = 0.0;
    }

    /* End of Switch: '<S33>/Switch3' */

    /* Sum: '<S33>/SumOLA1' */
    FOpid_RL_B.SumOLA1[0] = FOpid_RL_B.wbe_b[0];
    FOpid_RL_B.SumOLA1[1] = FOpid_RL_B.wbe_b[1] + FOpid_RL_B.sinc;
    FOpid_RL_B.SumOLA1[2] = FOpid_RL_B.wbe_b[2];

    /* Outputs for Enabled SubSystem: '<S50>/Hugw(s)' incorporates:
     *  EnablePort: '<S63>/Enable'
     */
    if (tmp_0 && rtsiIsModeUpdateTimeStep(&(&FOpid_RL_M)->solverInfo) &&
        !FOpid_RL_DW.Hugws_MODE) {
      (void) memset(&(FOpid_RL_XDis.ug_p_CSTATE), 0,
                    2*sizeof(boolean_T));

      /* InitializeConditions for Integrator: '<S63>/ug_p' */
      FOpid_RL_X.ug_p_CSTATE[0] = 0.0;
      FOpid_RL_X.ug_p_CSTATE[1] = 0.0;
      FOpid_RL_DW.Hugws_MODE = true;
    }

    if (FOpid_RL_DW.Hugws_MODE) {
      /* Product: '<S63>/Lug//V' */
      FOpid_RL_B.rtb_CoordinateTransformationC_d /=
        FOpid_RL_B.rtb_CoordinateTransformationC_l;
      FOpid_RL_B.sinc = FOpid_RL_ConstB.UnitConversion_c /
        FOpid_RL_B.rtb_CoordinateTransformationC_l;

      /* Product: '<S63>/w' incorporates:
       *  Gain: '<S63>/(2//pi)'
       *  Integrator: '<S63>/ug_p'
       *  Product: '<S63>/Lug//V1'
       *  Sqrt: '<S63>/sqrt'
       */
      _mm_storeu_pd(&FOpid_RL_B.w_n[0], _mm_div_pd(_mm_sub_pd(_mm_mul_pd
        (_mm_set_pd(sqrt(0.6366197723675814 * FOpid_RL_B.sinc), sqrt
                    (0.6366197723675814 *
                     FOpid_RL_B.rtb_CoordinateTransformationC_d)), _mm_set1_pd
         (FOpid_RL_B.Product[0])), _mm_loadu_pd(&FOpid_RL_X.ug_p_CSTATE[0])),
        _mm_set_pd(FOpid_RL_B.sinc, FOpid_RL_B.rtb_CoordinateTransformationC_d)));

      /* Product: '<S63>/w1' incorporates:
       *  Integrator: '<S63>/ug_p'
       */
      _mm_storeu_pd(&FOpid_RL_B.w1_c[0], _mm_mul_pd(_mm_loadu_pd
        (&FOpid_RL_X.ug_p_CSTATE[0]), _mm_set_pd(FOpid_RL_B.sinb,
        FOpid_RL_B.cosa)));
    }

    /* End of Outputs for SubSystem: '<S50>/Hugw(s)' */

    /* If: '<S55>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' incorporates:
     *  Constant: '<S76>/max_height_low'
     *  Product: '<S76>/Product1'
     *  Product: '<S81>/Product1'
     *  Product: '<S81>/Product2'
     *  Product: '<S83>/Product1'
     *  Product: '<S83>/Product2'
     *  Sum: '<S76>/Sum1'
     *  Sum: '<S76>/Sum2'
     *  Sum: '<S76>/Sum3'
     *  Sum: '<S81>/Sum'
     *  Sum: '<S83>/Sum'
     */
    rtPrevAction = FOpid_RL_DW.ifHeightMaxlowaltitudeelseifH_k;
    if (rtsiIsModeUpdateTimeStep(&(&FOpid_RL_M)->solverInfo)) {
      if (FOpid_RL_B.sina <= 1000.0) {
        rtAction = 0;
      } else if (FOpid_RL_B.sina >= 2000.0) {
        rtAction = 1;
      } else {
        rtAction = 2;
      }

      FOpid_RL_DW.ifHeightMaxlowaltitudeelseifH_k = rtAction;
    } else {
      rtAction = FOpid_RL_DW.ifHeightMaxlowaltitudeelseifH_k;
    }

    if (rtPrevAction != rtAction) {
      rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)->solverInfo,
        true);
    }

    switch (rtAction) {
     case 0:
      /* Outputs for IfAction SubSystem: '<S55>/Low altitude  velocities' incorporates:
       *  ActionPort: '<S77>/Action Port'
       */
      /* SignalConversion generated from: '<S82>/Vector Concatenate' */
      FOpid_RL_B.Reshape1_b[2] = FOpid_RL_B.LwgV1[0];

      /* Trigonometry: '<S83>/Trigonometric Function' */
      FOpid_RL_B.sina = sin(FOpid_RL_ConstB.UnitConversion);
      FOpid_RL_B.sinb = cos(FOpid_RL_ConstB.UnitConversion);
      _mm_storeu_pd(&FOpid_RL_B.Reshape1_b[0], _mm_add_pd(_mm_mul_pd(_mm_set_pd
        (FOpid_RL_B.sina, FOpid_RL_B.w1_c[0]), _mm_set_pd(FOpid_RL_B.w1_c[0],
        FOpid_RL_B.sinb)), _mm_mul_pd(_mm_mul_pd(_mm_set_pd(FOpid_RL_B.w1[0],
        FOpid_RL_B.sina), _mm_set_pd(FOpid_RL_B.sinb, FOpid_RL_B.w1[0])),
        _mm_set_pd(1.0, -1.0))));

      /* Product: '<S82>/Product' incorporates:
       *  Angle2Dcm: '<S33>/Rotation Angles to Direction Cosine Matrix'
       *  Product: '<S83>/Product1'
       *  Product: '<S83>/Product2'
       *  Reshape: '<S82>/Reshape'
       *  Reshape: '<S82>/Reshape1'
       *  Sum: '<S83>/Sum'
       */
      FOpid_RL_B.sinc = 0.0;
      FOpid_RL_B.rtb_CoordinateTransformationC_o = 0.0;
      FOpid_RL_B.cosb = 0.0;
      for (i = 0; i < 3; i++) {
        _mm_storeu_pd(&FOpid_RL_B.dv1[0], _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
          (&FOpid_RL_B.RotationAnglestoDirectionCo[3 * i]), _mm_set1_pd
          (FOpid_RL_B.Reshape1_b[i])), _mm_set_pd
          (FOpid_RL_B.rtb_CoordinateTransformationC_o, FOpid_RL_B.sinc)));
        FOpid_RL_B.sinc = FOpid_RL_B.dv1[0];
        FOpid_RL_B.rtb_CoordinateTransformationC_o = FOpid_RL_B.dv1[1];
        FOpid_RL_B.cosb += FOpid_RL_B.RotationAnglestoDirectionCo[3 * i + 2] *
          FOpid_RL_B.Reshape1_b[i];
      }

      FOpid_RL_B.wbe_b[2] = FOpid_RL_B.cosb;
      FOpid_RL_B.wbe_b[1] = FOpid_RL_B.rtb_CoordinateTransformationC_o;
      FOpid_RL_B.wbe_b[0] = FOpid_RL_B.sinc;

      /* End of Product: '<S82>/Product' */
      /* End of Outputs for SubSystem: '<S55>/Low altitude  velocities' */
      break;

     case 1:
      /* Outputs for IfAction SubSystem: '<S55>/Medium//High  altitude velocities' incorporates:
       *  ActionPort: '<S78>/Action Port'
       */
      /* Gain: '<S78>/Gain' */
      FOpid_RL_B.wbe_b[0] = FOpid_RL_B.w1_c[1];
      FOpid_RL_B.wbe_b[1] = FOpid_RL_B.w1[1];
      FOpid_RL_B.wbe_b[2] = FOpid_RL_B.LwgV1[1];

      /* End of Outputs for SubSystem: '<S55>/Medium//High  altitude velocities' */
      break;

     default:
      /* Outputs for IfAction SubSystem: '<S55>/Interpolate  velocities' incorporates:
       *  ActionPort: '<S76>/Action Port'
       */
      /* Trigonometry: '<S81>/Trigonometric Function' */
      FOpid_RL_B.sinb = sin(FOpid_RL_ConstB.UnitConversion);
      FOpid_RL_B.rtb_CoordinateTransformationC_d = cos
        (FOpid_RL_ConstB.UnitConversion);
      _mm_storeu_pd(&FOpid_RL_B.wbe_b[0], _mm_add_pd(_mm_mul_pd(_mm_set_pd
        (FOpid_RL_B.sinb, FOpid_RL_B.w1_c[0]), _mm_set_pd(FOpid_RL_B.w1_c[0],
        FOpid_RL_B.rtb_CoordinateTransformationC_d)), _mm_mul_pd(_mm_mul_pd
        (_mm_set_pd(FOpid_RL_B.w1[0], FOpid_RL_B.sinb), _mm_set_pd
         (FOpid_RL_B.rtb_CoordinateTransformationC_d, FOpid_RL_B.w1[0])),
        _mm_set_pd(1.0, -1.0))));

      /* SignalConversion generated from: '<S80>/Vector Concatenate' incorporates:
       *  Product: '<S81>/Product1'
       *  Product: '<S81>/Product2'
       *  Sum: '<S81>/Sum'
       */
      FOpid_RL_B.wbe_b[2] = FOpid_RL_B.LwgV1[0];

      /* Product: '<S80>/Product' incorporates:
       *  Angle2Dcm: '<S33>/Rotation Angles to Direction Cosine Matrix'
       *  Reshape: '<S80>/Reshape'
       *  Reshape: '<S80>/Reshape1'
       */
      FOpid_RL_B.sinc = 0.0;
      FOpid_RL_B.rtb_CoordinateTransformationC_o = 0.0;
      FOpid_RL_B.cosb = 0.0;
      for (i = 0; i < 3; i++) {
        _mm_storeu_pd(&FOpid_RL_B.dv1[0], _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
          (&FOpid_RL_B.RotationAnglestoDirectionCo[3 * i]), _mm_set1_pd
          (FOpid_RL_B.wbe_b[i])), _mm_set_pd
          (FOpid_RL_B.rtb_CoordinateTransformationC_o, FOpid_RL_B.sinc)));
        FOpid_RL_B.sinc = FOpid_RL_B.dv1[0];
        FOpid_RL_B.rtb_CoordinateTransformationC_o = FOpid_RL_B.dv1[1];
        FOpid_RL_B.cosb += FOpid_RL_B.RotationAnglestoDirectionCo[3 * i + 2] *
          FOpid_RL_B.wbe_b[i];
      }

      FOpid_RL_B.Reshape1_b[2] = FOpid_RL_B.cosb;
      FOpid_RL_B.Reshape1_b[1] = FOpid_RL_B.rtb_CoordinateTransformationC_o;
      FOpid_RL_B.Reshape1_b[0] = FOpid_RL_B.sinc;
      _mm_storeu_pd(&FOpid_RL_B.wbe_b[0], _mm_add_pd(_mm_div_pd(_mm_mul_pd
        (_mm_sub_pd(_mm_set_pd(FOpid_RL_B.w1[1], FOpid_RL_B.w1_c[1]),
                    _mm_loadu_pd(&FOpid_RL_B.Reshape1_b[0])), _mm_sub_pd
         (_mm_set1_pd(FOpid_RL_B.sina), _mm_set1_pd(1000.0))), _mm_set1_pd
        (FOpid_RL_ConstB.Sum)), _mm_loadu_pd(&FOpid_RL_B.Reshape1_b[0])));

      /* Sum: '<S76>/Sum3' incorporates:
       *  Constant: '<S76>/max_height_low'
       *  Product: '<S76>/Product1'
       *  Product: '<S80>/Product'
       *  Reshape: '<S80>/Reshape1'
       *  Sum: '<S76>/Sum1'
       *  Sum: '<S76>/Sum2'
       */
      FOpid_RL_B.wbe_b[2] = (FOpid_RL_B.LwgV1[1] - FOpid_RL_B.cosb) *
        (FOpid_RL_B.sina - 1000.0) / FOpid_RL_ConstB.Sum + FOpid_RL_B.cosb;

      /* End of Outputs for SubSystem: '<S55>/Interpolate  velocities' */
      break;
    }

    /* End of If: '<S55>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
    /* Unit Conversion - from: ft/s to: m/s
       Expression: output = (0.3048*input) + (0) */
    if (tmp_0) {
      /* MATLABSystem: '<S47>/SourceBlock' */
      FOpid_RL_B.SourceBlock_o1_h = Sub_FOpid_RL_417.getLatestMessage
        (&rtb_SourceBlock_o2_j);

      /* Outputs for Enabled SubSystem: '<S47>/Enabled Subsystem' */
      FOpid_RL_EnabledSubsystem(FOpid_RL_B.SourceBlock_o1_h,
        &rtb_SourceBlock_o2_j, &FOpid_RL_B.EnabledSubsystem_pt);

      /* End of Outputs for SubSystem: '<S47>/Enabled Subsystem' */
    }

    /* Switch: '<S33>/Switch' incorporates:
     *  Constant: '<S33>/Constant'
     *  UnitConversion: '<S41>/Unit Conversion'
     */
    if (FOpid_RL_B.EnabledSubsystem_pt.In1.data) {
      _mm_storeu_pd(&FOpid_RL_B.wbe_b[0], _mm_mul_pd(_mm_set1_pd(0.3048),
        _mm_loadu_pd(&FOpid_RL_B.wbe_b[0])));
      FOpid_RL_B.wbe_b[2] *= 0.3048;
    } else {
      FOpid_RL_B.wbe_b[0] = 0.0;
      FOpid_RL_B.wbe_b[1] = 0.0;
      FOpid_RL_B.wbe_b[2] = 0.0;
    }

    /* End of Switch: '<S33>/Switch' */
    if (tmp_0) {
      /* MATLABSystem: '<S45>/SourceBlock' */
      FOpid_RL_B.SourceBlock_o1_c = Sub_FOpid_RL_443.getLatestMessage
        (&rtb_SourceBlock_o2_p);

      /* Outputs for Enabled SubSystem: '<S45>/Enabled Subsystem' */
      FOpid_RL_EnabledSubsystem_k(FOpid_RL_B.SourceBlock_o1_c,
        &rtb_SourceBlock_o2_p, &FOpid_RL_B.EnabledSubsystem_k);

      /* End of Outputs for SubSystem: '<S45>/Enabled Subsystem' */
    }

    /* Sum: '<S33>/SumOLA' */
    FOpid_RL_B.SumOLA[0] = FOpid_RL_B.wbe_b[0];

    /* Switch: '<S33>/Switch2' incorporates:
     *  Constant: '<S33>/Constant3'
     *  TransferFcn: '<S33>/Transfer Fcn'
     */
    if (FOpid_RL_B.EnabledSubsystem_k.In1.data != 0.0) {
      FOpid_RL_B.cosa = 0.5303 * FOpid_RL_X.TransferFcn_CSTATE[0] + 0.0 *
        FOpid_RL_X.TransferFcn_CSTATE[1];
    } else {
      FOpid_RL_B.cosa = 0.0;
    }

    /* Sum: '<S33>/SumOLA' incorporates:
     *  Switch: '<S33>/Switch2'
     */
    FOpid_RL_B.SumOLA[1] = FOpid_RL_B.wbe_b[1] + FOpid_RL_B.cosa;
    FOpid_RL_B.SumOLA[2] = FOpid_RL_B.wbe_b[2];

    /* Product: '<S33>/Product2' incorporates:
     *  Math: '<S33>/Square'
     *  Math: '<S33>/Square1'
     *  Math: '<S33>/Square2'
     *  Sqrt: '<S33>/Sqrt'
     *  Sum: '<S33>/Sum2'
     */
    FOpid_RL_B.Power = sqrt((FOpid_RL_B.x[0] * FOpid_RL_B.x[0] + FOpid_RL_B.x[1]
      * FOpid_RL_B.x[1]) + FOpid_RL_B.x[2] * FOpid_RL_B.x[2]) * FOpid_RL_B.XDOT
      [34];

    /* Gain: '<S33>/Gain3' */
    FOpid_RL_B.Gain3 = 0.001 * FOpid_RL_B.Power;

    /* Gain: '<S33>/Gain1' incorporates:
     *  Integrator: '<S33>/Integrator1'
     */
    FOpid_RL_B.EnergykWh = 2.7777777777777776E-7 * FOpid_RL_X.Integrator1_CSTATE;

    /* Product: '<S33>/Divide' incorporates:
     *  Constant: '<S33>/thrust efficiency Cp?'
     */
    FOpid_RL_B.powerdemand = FOpid_RL_B.Gain3 / 0.57;

    /* Product: '<S33>/Divide1' */
    FOpid_RL_B.loadtorque = FOpid_RL_B.powerdemand / FOpid_RL_ConstB.motorspeed;

    /* SecondOrderIntegrator: '<S22>/Integrator, Second-Order Limited' */
    if (rtsiIsModeUpdateTimeStep(&(&FOpid_RL_M)->solverInfo)) {
      switch (FOpid_RL_DW.IntegratorSecondOrderLimited_MO) {
       case 0:
        if (FOpid_RL_X.IntegratorSecondOrderLimited_CS[0] <= -0.3490658503988659)
        {
          FOpid_RL_X.IntegratorSecondOrderLimited_CS[0] = -0.3490658503988659;
          if (FOpid_RL_X.IntegratorSecondOrderLimited_CS[1] > 0.0) {
            FOpid_RL_DW.IntegratorSecondOrderLimited_MO = 0;
          } else {
            FOpid_RL_X.IntegratorSecondOrderLimited_CS[1] = 0.0;
            FOpid_RL_DW.IntegratorSecondOrderLimited_MO = 1;
          }

          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)
            ->solverInfo, true);
        }

        if (FOpid_RL_X.IntegratorSecondOrderLimited_CS[0] >= 0.2617993877991494)
        {
          FOpid_RL_X.IntegratorSecondOrderLimited_CS[0] = 0.2617993877991494;
          if (FOpid_RL_X.IntegratorSecondOrderLimited_CS[1] < 0.0) {
            FOpid_RL_DW.IntegratorSecondOrderLimited_MO = 0;
          } else {
            FOpid_RL_X.IntegratorSecondOrderLimited_CS[1] = 0.0;
            FOpid_RL_DW.IntegratorSecondOrderLimited_MO = 2;
          }

          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)
            ->solverInfo, true);
        }

        if (FOpid_RL_X.IntegratorSecondOrderLimited_CS[1] <= -1.7453292519943295)
        {
          FOpid_RL_X.IntegratorSecondOrderLimited_CS[1] = -1.7453292519943295;
          FOpid_RL_DW.IntegratorSecondOrderLimited_MO = 3;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)
            ->solverInfo, true);
        }

        if (FOpid_RL_X.IntegratorSecondOrderLimited_CS[1] >= 1.7453292519943295)
        {
          FOpid_RL_X.IntegratorSecondOrderLimited_CS[1] = 1.7453292519943295;
          FOpid_RL_DW.IntegratorSecondOrderLimited_MO = 4;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)
            ->solverInfo, true);
        }
        break;

       case 1:
        if (FOpid_RL_X.IntegratorSecondOrderLimited_CS[0] > -0.3490658503988659)
        {
          if (FOpid_RL_X.IntegratorSecondOrderLimited_CS[0] >=
              0.2617993877991494) {
            FOpid_RL_DW.IntegratorSecondOrderLimited_MO = 2;
            FOpid_RL_X.IntegratorSecondOrderLimited_CS[0] = 0.2617993877991494;
          } else {
            FOpid_RL_DW.IntegratorSecondOrderLimited_MO = 0;
          }
        } else {
          FOpid_RL_X.IntegratorSecondOrderLimited_CS[0] = -0.3490658503988659;
          FOpid_RL_X.IntegratorSecondOrderLimited_CS[1] = 0.0;
        }
        break;

       case 2:
        if (FOpid_RL_X.IntegratorSecondOrderLimited_CS[0] < 0.2617993877991494)
        {
          if (FOpid_RL_X.IntegratorSecondOrderLimited_CS[0] <=
              -0.3490658503988659) {
            FOpid_RL_DW.IntegratorSecondOrderLimited_MO = 1;
            FOpid_RL_X.IntegratorSecondOrderLimited_CS[0] = -0.3490658503988659;
          } else {
            FOpid_RL_DW.IntegratorSecondOrderLimited_MO = 0;
          }
        } else {
          FOpid_RL_X.IntegratorSecondOrderLimited_CS[0] = 0.2617993877991494;
          FOpid_RL_X.IntegratorSecondOrderLimited_CS[1] = 0.0;
        }
        break;

       case 3:
        if (FOpid_RL_X.IntegratorSecondOrderLimited_CS[1] > -1.7453292519943295)
        {
          if (FOpid_RL_X.IntegratorSecondOrderLimited_CS[1] >=
              1.7453292519943295) {
            FOpid_RL_DW.IntegratorSecondOrderLimited_MO = 4;
            FOpid_RL_X.IntegratorSecondOrderLimited_CS[1] = 1.7453292519943295;
          } else {
            FOpid_RL_DW.IntegratorSecondOrderLimited_MO = 0;
          }
        } else {
          FOpid_RL_X.IntegratorSecondOrderLimited_CS[1] = -1.7453292519943295;
        }

        if (FOpid_RL_X.IntegratorSecondOrderLimited_CS[0] <= -0.3490658503988659)
        {
          FOpid_RL_X.IntegratorSecondOrderLimited_CS[0] = -0.3490658503988659;
          FOpid_RL_X.IntegratorSecondOrderLimited_CS[1] = 0.0;
          FOpid_RL_DW.IntegratorSecondOrderLimited_MO = 1;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)
            ->solverInfo, true);
        }
        break;

       case 4:
        if (FOpid_RL_X.IntegratorSecondOrderLimited_CS[1] < 1.7453292519943295)
        {
          if (FOpid_RL_X.IntegratorSecondOrderLimited_CS[1] <=
              -1.7453292519943295) {
            FOpid_RL_DW.IntegratorSecondOrderLimited_MO = 3;
            FOpid_RL_X.IntegratorSecondOrderLimited_CS[1] = -1.7453292519943295;
          } else {
            FOpid_RL_DW.IntegratorSecondOrderLimited_MO = 0;
          }
        } else {
          FOpid_RL_X.IntegratorSecondOrderLimited_CS[1] = 1.7453292519943295;
        }

        if (FOpid_RL_X.IntegratorSecondOrderLimited_CS[0] >= 0.2617993877991494)
        {
          FOpid_RL_X.IntegratorSecondOrderLimited_CS[0] = 0.2617993877991494;
          FOpid_RL_X.IntegratorSecondOrderLimited_CS[1] = 0.0;
          FOpid_RL_DW.IntegratorSecondOrderLimited_MO = 2;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)
            ->solverInfo, true);
        }
        break;
      }
    }

    if (FOpid_RL_X.IntegratorSecondOrderLimited_CS[0] < -0.3490658503988659) {
      FOpid_RL_B.cosa = -0.3490658503988659;
    } else if (FOpid_RL_X.IntegratorSecondOrderLimited_CS[0] >
               0.2617993877991494) {
      FOpid_RL_B.cosa = 0.2617993877991494;
    } else {
      FOpid_RL_B.cosa = FOpid_RL_X.IntegratorSecondOrderLimited_CS[0];
    }

    /* Sum: '<S22>/Sum3' incorporates:
     *  SecondOrderIntegrator: '<S22>/Integrator, Second-Order Limited'
     */
    FOpid_RL_B.sina = FOpid_RL_ConstB.Demandlimits - FOpid_RL_B.cosa;

    /* Saturate: '<S22>/rate limit*2*zeta//wn' */
    if (FOpid_RL_B.sina > 1.0471975511965976) {
      FOpid_RL_B.sina = 1.0471975511965976;
    } else if (FOpid_RL_B.sina < -1.0471975511965976) {
      FOpid_RL_B.sina = -1.0471975511965976;
    }

    /* SecondOrderIntegrator: '<S22>/Integrator, Second-Order Limited' */
    if (FOpid_RL_X.IntegratorSecondOrderLimited_CS[1] < -1.7453292519943295) {
      FOpid_RL_B.cosa = -1.7453292519943295;
    } else if (FOpid_RL_X.IntegratorSecondOrderLimited_CS[1] >
               1.7453292519943295) {
      FOpid_RL_B.cosa = 1.7453292519943295;
    } else {
      FOpid_RL_B.cosa = FOpid_RL_X.IntegratorSecondOrderLimited_CS[1];
    }

    /* Sum: '<S22>/Sum2' incorporates:
     *  Gain: '<S22>/2*zeta * wn'
     *  Saturate: '<S22>/rate limit*2*zeta//wn'
     *  SecondOrderIntegrator: '<S22>/Integrator, Second-Order Limited'
     */
    FOpid_RL_B.Sum2_j = FOpid_RL_B.sina - 0.6 * FOpid_RL_B.cosa;

    /* SecondOrderIntegrator: '<S23>/Integrator, Second-Order Limited' */
    if (rtsiIsModeUpdateTimeStep(&(&FOpid_RL_M)->solverInfo)) {
      switch (FOpid_RL_DW.IntegratorSecondOrderLimited__h) {
       case 0:
        if (FOpid_RL_X.IntegratorSecondOrderLimited__n[0] <= -0.3490658503988659)
        {
          FOpid_RL_X.IntegratorSecondOrderLimited__n[0] = -0.3490658503988659;
          if (FOpid_RL_X.IntegratorSecondOrderLimited__n[1] > 0.0) {
            FOpid_RL_DW.IntegratorSecondOrderLimited__h = 0;
          } else {
            FOpid_RL_X.IntegratorSecondOrderLimited__n[1] = 0.0;
            FOpid_RL_DW.IntegratorSecondOrderLimited__h = 1;
          }

          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)
            ->solverInfo, true);
        }

        if (FOpid_RL_X.IntegratorSecondOrderLimited__n[0] >= 0.3490658503988659)
        {
          FOpid_RL_X.IntegratorSecondOrderLimited__n[0] = 0.3490658503988659;
          if (FOpid_RL_X.IntegratorSecondOrderLimited__n[1] < 0.0) {
            FOpid_RL_DW.IntegratorSecondOrderLimited__h = 0;
          } else {
            FOpid_RL_X.IntegratorSecondOrderLimited__n[1] = 0.0;
            FOpid_RL_DW.IntegratorSecondOrderLimited__h = 2;
          }

          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)
            ->solverInfo, true);
        }

        if (FOpid_RL_X.IntegratorSecondOrderLimited__n[1] <= -8.726646259971647)
        {
          FOpid_RL_X.IntegratorSecondOrderLimited__n[1] = -8.726646259971647;
          FOpid_RL_DW.IntegratorSecondOrderLimited__h = 3;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)
            ->solverInfo, true);
        }

        if (FOpid_RL_X.IntegratorSecondOrderLimited__n[1] >= 8.726646259971647)
        {
          FOpid_RL_X.IntegratorSecondOrderLimited__n[1] = 8.726646259971647;
          FOpid_RL_DW.IntegratorSecondOrderLimited__h = 4;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)
            ->solverInfo, true);
        }
        break;

       case 1:
        if (FOpid_RL_X.IntegratorSecondOrderLimited__n[0] > -0.3490658503988659)
        {
          if (FOpid_RL_X.IntegratorSecondOrderLimited__n[0] >=
              0.3490658503988659) {
            FOpid_RL_DW.IntegratorSecondOrderLimited__h = 2;
            FOpid_RL_X.IntegratorSecondOrderLimited__n[0] = 0.3490658503988659;
          } else {
            FOpid_RL_DW.IntegratorSecondOrderLimited__h = 0;
          }
        } else {
          FOpid_RL_X.IntegratorSecondOrderLimited__n[0] = -0.3490658503988659;
          FOpid_RL_X.IntegratorSecondOrderLimited__n[1] = 0.0;
        }
        break;

       case 2:
        if (FOpid_RL_X.IntegratorSecondOrderLimited__n[0] < 0.3490658503988659)
        {
          if (FOpid_RL_X.IntegratorSecondOrderLimited__n[0] <=
              -0.3490658503988659) {
            FOpid_RL_DW.IntegratorSecondOrderLimited__h = 1;
            FOpid_RL_X.IntegratorSecondOrderLimited__n[0] = -0.3490658503988659;
          } else {
            FOpid_RL_DW.IntegratorSecondOrderLimited__h = 0;
          }
        } else {
          FOpid_RL_X.IntegratorSecondOrderLimited__n[0] = 0.3490658503988659;
          FOpid_RL_X.IntegratorSecondOrderLimited__n[1] = 0.0;
        }
        break;

       case 3:
        if (FOpid_RL_X.IntegratorSecondOrderLimited__n[1] > -8.726646259971647)
        {
          if (FOpid_RL_X.IntegratorSecondOrderLimited__n[1] >= 8.726646259971647)
          {
            FOpid_RL_DW.IntegratorSecondOrderLimited__h = 4;
            FOpid_RL_X.IntegratorSecondOrderLimited__n[1] = 8.726646259971647;
          } else {
            FOpid_RL_DW.IntegratorSecondOrderLimited__h = 0;
          }
        } else {
          FOpid_RL_X.IntegratorSecondOrderLimited__n[1] = -8.726646259971647;
        }

        if (FOpid_RL_X.IntegratorSecondOrderLimited__n[0] <= -0.3490658503988659)
        {
          FOpid_RL_X.IntegratorSecondOrderLimited__n[0] = -0.3490658503988659;
          FOpid_RL_X.IntegratorSecondOrderLimited__n[1] = 0.0;
          FOpid_RL_DW.IntegratorSecondOrderLimited__h = 1;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)
            ->solverInfo, true);
        }
        break;

       case 4:
        if (FOpid_RL_X.IntegratorSecondOrderLimited__n[1] < 8.726646259971647) {
          if (FOpid_RL_X.IntegratorSecondOrderLimited__n[1] <=
              -8.726646259971647) {
            FOpid_RL_DW.IntegratorSecondOrderLimited__h = 3;
            FOpid_RL_X.IntegratorSecondOrderLimited__n[1] = -8.726646259971647;
          } else {
            FOpid_RL_DW.IntegratorSecondOrderLimited__h = 0;
          }
        } else {
          FOpid_RL_X.IntegratorSecondOrderLimited__n[1] = 8.726646259971647;
        }

        if (FOpid_RL_X.IntegratorSecondOrderLimited__n[0] >= 0.3490658503988659)
        {
          FOpid_RL_X.IntegratorSecondOrderLimited__n[0] = 0.3490658503988659;
          FOpid_RL_X.IntegratorSecondOrderLimited__n[1] = 0.0;
          FOpid_RL_DW.IntegratorSecondOrderLimited__h = 2;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)
            ->solverInfo, true);
        }
        break;
      }
    }

    if (FOpid_RL_X.IntegratorSecondOrderLimited__n[0] < -0.3490658503988659) {
      FOpid_RL_B.cosa = -0.3490658503988659;
    } else if (FOpid_RL_X.IntegratorSecondOrderLimited__n[0] >
               0.3490658503988659) {
      FOpid_RL_B.cosa = 0.3490658503988659;
    } else {
      FOpid_RL_B.cosa = FOpid_RL_X.IntegratorSecondOrderLimited__n[0];
    }

    /* Sum: '<S23>/Sum3' incorporates:
     *  SecondOrderIntegrator: '<S23>/Integrator, Second-Order Limited'
     */
    FOpid_RL_B.sina = FOpid_RL_ConstB.Demandlimits_c - FOpid_RL_B.cosa;

    /* Saturate: '<S23>/rate limit*2*zeta//wn' */
    if (FOpid_RL_B.sina > 5.235987755982988) {
      FOpid_RL_B.sina = 5.235987755982988;
    } else if (FOpid_RL_B.sina < -5.235987755982988) {
      FOpid_RL_B.sina = -5.235987755982988;
    }

    /* SecondOrderIntegrator: '<S23>/Integrator, Second-Order Limited' */
    if (FOpid_RL_X.IntegratorSecondOrderLimited__n[1] < -8.726646259971647) {
      FOpid_RL_B.cosa = -8.726646259971647;
    } else if (FOpid_RL_X.IntegratorSecondOrderLimited__n[1] > 8.726646259971647)
    {
      FOpid_RL_B.cosa = 8.726646259971647;
    } else {
      FOpid_RL_B.cosa = FOpid_RL_X.IntegratorSecondOrderLimited__n[1];
    }

    /* Sum: '<S23>/Sum2' incorporates:
     *  Gain: '<S23>/2*zeta * wn'
     *  Saturate: '<S23>/rate limit*2*zeta//wn'
     *  SecondOrderIntegrator: '<S23>/Integrator, Second-Order Limited'
     */
    FOpid_RL_B.Sum2_f = FOpid_RL_B.sina - 0.6 * FOpid_RL_B.cosa;

    /* SecondOrderIntegrator: '<S24>/Integrator, Second-Order Limited' */
    if (rtsiIsModeUpdateTimeStep(&(&FOpid_RL_M)->solverInfo)) {
      switch (FOpid_RL_DW.IntegratorSecondOrderLimited__b) {
       case 0:
        if (FOpid_RL_X.IntegratorSecondOrderLimited__a[0] <= -0.2617993877991494)
        {
          FOpid_RL_X.IntegratorSecondOrderLimited__a[0] = -0.2617993877991494;
          if (FOpid_RL_X.IntegratorSecondOrderLimited__a[1] > 0.0) {
            FOpid_RL_DW.IntegratorSecondOrderLimited__b = 0;
          } else {
            FOpid_RL_X.IntegratorSecondOrderLimited__a[1] = 0.0;
            FOpid_RL_DW.IntegratorSecondOrderLimited__b = 1;
          }

          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)
            ->solverInfo, true);
        }

        if (FOpid_RL_X.IntegratorSecondOrderLimited__a[0] >= 0.2617993877991494)
        {
          FOpid_RL_X.IntegratorSecondOrderLimited__a[0] = 0.2617993877991494;
          if (FOpid_RL_X.IntegratorSecondOrderLimited__a[1] < 0.0) {
            FOpid_RL_DW.IntegratorSecondOrderLimited__b = 0;
          } else {
            FOpid_RL_X.IntegratorSecondOrderLimited__a[1] = 0.0;
            FOpid_RL_DW.IntegratorSecondOrderLimited__b = 2;
          }

          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)
            ->solverInfo, true);
        }

        if (FOpid_RL_X.IntegratorSecondOrderLimited__a[1] <= -8.726646259971647)
        {
          FOpid_RL_X.IntegratorSecondOrderLimited__a[1] = -8.726646259971647;
          FOpid_RL_DW.IntegratorSecondOrderLimited__b = 3;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)
            ->solverInfo, true);
        }

        if (FOpid_RL_X.IntegratorSecondOrderLimited__a[1] >= 8.726646259971647)
        {
          FOpid_RL_X.IntegratorSecondOrderLimited__a[1] = 8.726646259971647;
          FOpid_RL_DW.IntegratorSecondOrderLimited__b = 4;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)
            ->solverInfo, true);
        }
        break;

       case 1:
        if (FOpid_RL_X.IntegratorSecondOrderLimited__a[0] > -0.2617993877991494)
        {
          if (FOpid_RL_X.IntegratorSecondOrderLimited__a[0] >=
              0.2617993877991494) {
            FOpid_RL_DW.IntegratorSecondOrderLimited__b = 2;
            FOpid_RL_X.IntegratorSecondOrderLimited__a[0] = 0.2617993877991494;
          } else {
            FOpid_RL_DW.IntegratorSecondOrderLimited__b = 0;
          }
        } else {
          FOpid_RL_X.IntegratorSecondOrderLimited__a[0] = -0.2617993877991494;
          FOpid_RL_X.IntegratorSecondOrderLimited__a[1] = 0.0;
        }
        break;

       case 2:
        if (FOpid_RL_X.IntegratorSecondOrderLimited__a[0] < 0.2617993877991494)
        {
          if (FOpid_RL_X.IntegratorSecondOrderLimited__a[0] <=
              -0.2617993877991494) {
            FOpid_RL_DW.IntegratorSecondOrderLimited__b = 1;
            FOpid_RL_X.IntegratorSecondOrderLimited__a[0] = -0.2617993877991494;
          } else {
            FOpid_RL_DW.IntegratorSecondOrderLimited__b = 0;
          }
        } else {
          FOpid_RL_X.IntegratorSecondOrderLimited__a[0] = 0.2617993877991494;
          FOpid_RL_X.IntegratorSecondOrderLimited__a[1] = 0.0;
        }
        break;

       case 3:
        if (FOpid_RL_X.IntegratorSecondOrderLimited__a[1] > -8.726646259971647)
        {
          if (FOpid_RL_X.IntegratorSecondOrderLimited__a[1] >= 8.726646259971647)
          {
            FOpid_RL_DW.IntegratorSecondOrderLimited__b = 4;
            FOpid_RL_X.IntegratorSecondOrderLimited__a[1] = 8.726646259971647;
          } else {
            FOpid_RL_DW.IntegratorSecondOrderLimited__b = 0;
          }
        } else {
          FOpid_RL_X.IntegratorSecondOrderLimited__a[1] = -8.726646259971647;
        }

        if (FOpid_RL_X.IntegratorSecondOrderLimited__a[0] <= -0.2617993877991494)
        {
          FOpid_RL_X.IntegratorSecondOrderLimited__a[0] = -0.2617993877991494;
          FOpid_RL_X.IntegratorSecondOrderLimited__a[1] = 0.0;
          FOpid_RL_DW.IntegratorSecondOrderLimited__b = 1;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)
            ->solverInfo, true);
        }
        break;

       case 4:
        if (FOpid_RL_X.IntegratorSecondOrderLimited__a[1] < 8.726646259971647) {
          if (FOpid_RL_X.IntegratorSecondOrderLimited__a[1] <=
              -8.726646259971647) {
            FOpid_RL_DW.IntegratorSecondOrderLimited__b = 3;
            FOpid_RL_X.IntegratorSecondOrderLimited__a[1] = -8.726646259971647;
          } else {
            FOpid_RL_DW.IntegratorSecondOrderLimited__b = 0;
          }
        } else {
          FOpid_RL_X.IntegratorSecondOrderLimited__a[1] = 8.726646259971647;
        }

        if (FOpid_RL_X.IntegratorSecondOrderLimited__a[0] >= 0.2617993877991494)
        {
          FOpid_RL_X.IntegratorSecondOrderLimited__a[0] = 0.2617993877991494;
          FOpid_RL_X.IntegratorSecondOrderLimited__a[1] = 0.0;
          FOpid_RL_DW.IntegratorSecondOrderLimited__b = 2;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)
            ->solverInfo, true);
        }
        break;
      }
    }

    if (FOpid_RL_X.IntegratorSecondOrderLimited__a[0] < -0.2617993877991494) {
      FOpid_RL_B.cosa = -0.2617993877991494;
    } else if (FOpid_RL_X.IntegratorSecondOrderLimited__a[0] >
               0.2617993877991494) {
      FOpid_RL_B.cosa = 0.2617993877991494;
    } else {
      FOpid_RL_B.cosa = FOpid_RL_X.IntegratorSecondOrderLimited__a[0];
    }

    /* Sum: '<S24>/Sum3' incorporates:
     *  SecondOrderIntegrator: '<S24>/Integrator, Second-Order Limited'
     */
    FOpid_RL_B.sina = FOpid_RL_ConstB.Demandlimits_n - FOpid_RL_B.cosa;

    /* Saturate: '<S24>/rate limit*2*zeta//wn' */
    if (FOpid_RL_B.sina > 5.235987755982988) {
      FOpid_RL_B.sina = 5.235987755982988;
    } else if (FOpid_RL_B.sina < -5.235987755982988) {
      FOpid_RL_B.sina = -5.235987755982988;
    }

    /* SecondOrderIntegrator: '<S24>/Integrator, Second-Order Limited' */
    if (FOpid_RL_X.IntegratorSecondOrderLimited__a[1] < -8.726646259971647) {
      FOpid_RL_B.cosa = -8.726646259971647;
    } else if (FOpid_RL_X.IntegratorSecondOrderLimited__a[1] > 8.726646259971647)
    {
      FOpid_RL_B.cosa = 8.726646259971647;
    } else {
      FOpid_RL_B.cosa = FOpid_RL_X.IntegratorSecondOrderLimited__a[1];
    }

    /* Sum: '<S24>/Sum2' incorporates:
     *  Gain: '<S24>/2*zeta * wn'
     *  Saturate: '<S24>/rate limit*2*zeta//wn'
     *  SecondOrderIntegrator: '<S24>/Integrator, Second-Order Limited'
     */
    FOpid_RL_B.Sum2_b = FOpid_RL_B.sina - 0.6 * FOpid_RL_B.cosa;

    /* SecondOrderIntegrator: '<S25>/Integrator, Second-Order Limited' */
    if (rtsiIsModeUpdateTimeStep(&(&FOpid_RL_M)->solverInfo)) {
      switch (FOpid_RL_DW.IntegratorSecondOrderLimited__o) {
       case 0:
        if (FOpid_RL_X.IntegratorSecondOrderLimited__i[0] <= 0.0) {
          FOpid_RL_X.IntegratorSecondOrderLimited__i[0] = 0.0;
          if (FOpid_RL_X.IntegratorSecondOrderLimited__i[1] > 0.0) {
            FOpid_RL_DW.IntegratorSecondOrderLimited__o = 0;
          } else {
            FOpid_RL_X.IntegratorSecondOrderLimited__i[1] = 0.0;
            FOpid_RL_DW.IntegratorSecondOrderLimited__o = 1;
          }

          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)
            ->solverInfo, true);
        }

        if (FOpid_RL_X.IntegratorSecondOrderLimited__i[0] >= 100.0) {
          FOpid_RL_X.IntegratorSecondOrderLimited__i[0] = 100.0;
          if (FOpid_RL_X.IntegratorSecondOrderLimited__i[1] < 0.0) {
            FOpid_RL_DW.IntegratorSecondOrderLimited__o = 0;
          } else {
            FOpid_RL_X.IntegratorSecondOrderLimited__i[1] = 0.0;
            FOpid_RL_DW.IntegratorSecondOrderLimited__o = 2;
          }

          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)
            ->solverInfo, true);
        }

        if (FOpid_RL_X.IntegratorSecondOrderLimited__i[1] <= -8.726646259971647)
        {
          FOpid_RL_X.IntegratorSecondOrderLimited__i[1] = -8.726646259971647;
          FOpid_RL_DW.IntegratorSecondOrderLimited__o = 3;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)
            ->solverInfo, true);
        }

        if (FOpid_RL_X.IntegratorSecondOrderLimited__i[1] >= 8.726646259971647)
        {
          FOpid_RL_X.IntegratorSecondOrderLimited__i[1] = 8.726646259971647;
          FOpid_RL_DW.IntegratorSecondOrderLimited__o = 4;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)
            ->solverInfo, true);
        }
        break;

       case 1:
        if (FOpid_RL_X.IntegratorSecondOrderLimited__i[0] > 0.0) {
          if (FOpid_RL_X.IntegratorSecondOrderLimited__i[0] >= 100.0) {
            FOpid_RL_DW.IntegratorSecondOrderLimited__o = 2;
            FOpid_RL_X.IntegratorSecondOrderLimited__i[0] = 100.0;
          } else {
            FOpid_RL_DW.IntegratorSecondOrderLimited__o = 0;
          }
        } else {
          FOpid_RL_X.IntegratorSecondOrderLimited__i[0] = 0.0;
          FOpid_RL_X.IntegratorSecondOrderLimited__i[1] = 0.0;
        }
        break;

       case 2:
        if (FOpid_RL_X.IntegratorSecondOrderLimited__i[0] < 100.0) {
          if (FOpid_RL_X.IntegratorSecondOrderLimited__i[0] <= 0.0) {
            FOpid_RL_DW.IntegratorSecondOrderLimited__o = 1;
            FOpid_RL_X.IntegratorSecondOrderLimited__i[0] = 0.0;
          } else {
            FOpid_RL_DW.IntegratorSecondOrderLimited__o = 0;
          }
        } else {
          FOpid_RL_X.IntegratorSecondOrderLimited__i[0] = 100.0;
          FOpid_RL_X.IntegratorSecondOrderLimited__i[1] = 0.0;
        }
        break;

       case 3:
        if (FOpid_RL_X.IntegratorSecondOrderLimited__i[1] > -8.726646259971647)
        {
          if (FOpid_RL_X.IntegratorSecondOrderLimited__i[1] >= 8.726646259971647)
          {
            FOpid_RL_DW.IntegratorSecondOrderLimited__o = 4;
            FOpid_RL_X.IntegratorSecondOrderLimited__i[1] = 8.726646259971647;
          } else {
            FOpid_RL_DW.IntegratorSecondOrderLimited__o = 0;
          }
        } else {
          FOpid_RL_X.IntegratorSecondOrderLimited__i[1] = -8.726646259971647;
        }

        if (FOpid_RL_X.IntegratorSecondOrderLimited__i[0] <= 0.0) {
          FOpid_RL_X.IntegratorSecondOrderLimited__i[0] = 0.0;
          FOpid_RL_X.IntegratorSecondOrderLimited__i[1] = 0.0;
          FOpid_RL_DW.IntegratorSecondOrderLimited__o = 1;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)
            ->solverInfo, true);
        }
        break;

       case 4:
        if (FOpid_RL_X.IntegratorSecondOrderLimited__i[1] < 8.726646259971647) {
          if (FOpid_RL_X.IntegratorSecondOrderLimited__i[1] <=
              -8.726646259971647) {
            FOpid_RL_DW.IntegratorSecondOrderLimited__o = 3;
            FOpid_RL_X.IntegratorSecondOrderLimited__i[1] = -8.726646259971647;
          } else {
            FOpid_RL_DW.IntegratorSecondOrderLimited__o = 0;
          }
        } else {
          FOpid_RL_X.IntegratorSecondOrderLimited__i[1] = 8.726646259971647;
        }

        if (FOpid_RL_X.IntegratorSecondOrderLimited__i[0] >= 100.0) {
          FOpid_RL_X.IntegratorSecondOrderLimited__i[0] = 100.0;
          FOpid_RL_X.IntegratorSecondOrderLimited__i[1] = 0.0;
          FOpid_RL_DW.IntegratorSecondOrderLimited__o = 2;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)
            ->solverInfo, true);
        }
        break;
      }
    }

    if (FOpid_RL_X.IntegratorSecondOrderLimited__i[0] < 0.0) {
      FOpid_RL_B.cosa = 0.0;
    } else if (FOpid_RL_X.IntegratorSecondOrderLimited__i[0] > 100.0) {
      FOpid_RL_B.cosa = 100.0;
    } else {
      FOpid_RL_B.cosa = FOpid_RL_X.IntegratorSecondOrderLimited__i[0];
    }

    /* Sum: '<S25>/Sum3' incorporates:
     *  SecondOrderIntegrator: '<S25>/Integrator, Second-Order Limited'
     */
    FOpid_RL_B.sina = FOpid_RL_ConstB.Demandlimits_g - FOpid_RL_B.cosa;

    /* Saturate: '<S25>/rate limit*2*zeta//wn' */
    if (FOpid_RL_B.sina > 5.235987755982988) {
      FOpid_RL_B.sina = 5.235987755982988;
    } else if (FOpid_RL_B.sina < -5.235987755982988) {
      FOpid_RL_B.sina = -5.235987755982988;
    }

    /* SecondOrderIntegrator: '<S25>/Integrator, Second-Order Limited' */
    if (FOpid_RL_X.IntegratorSecondOrderLimited__i[1] < -8.726646259971647) {
      FOpid_RL_B.cosa = -8.726646259971647;
    } else if (FOpid_RL_X.IntegratorSecondOrderLimited__i[1] > 8.726646259971647)
    {
      FOpid_RL_B.cosa = 8.726646259971647;
    } else {
      FOpid_RL_B.cosa = FOpid_RL_X.IntegratorSecondOrderLimited__i[1];
    }

    /* Sum: '<S25>/Sum2' incorporates:
     *  Gain: '<S25>/2*zeta * wn'
     *  Saturate: '<S25>/rate limit*2*zeta//wn'
     *  SecondOrderIntegrator: '<S25>/Integrator, Second-Order Limited'
     */
    FOpid_RL_B.Sum2_jg = FOpid_RL_B.sina - 0.6 * FOpid_RL_B.cosa;

    /* SecondOrderIntegrator: '<S26>/Integrator, Second-Order Limited' */
    if (rtsiIsModeUpdateTimeStep(&(&FOpid_RL_M)->solverInfo)) {
      switch (FOpid_RL_DW.IntegratorSecondOrderLimited_h4) {
       case 0:
        if (FOpid_RL_X.IntegratorSecondOrderLimited__f[0] <= 0.0) {
          FOpid_RL_X.IntegratorSecondOrderLimited__f[0] = 0.0;
          if (FOpid_RL_X.IntegratorSecondOrderLimited__f[1] > 0.0) {
            FOpid_RL_DW.IntegratorSecondOrderLimited_h4 = 0;
          } else {
            FOpid_RL_X.IntegratorSecondOrderLimited__f[1] = 0.0;
            FOpid_RL_DW.IntegratorSecondOrderLimited_h4 = 1;
          }

          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)
            ->solverInfo, true);
        }

        if (FOpid_RL_X.IntegratorSecondOrderLimited__f[0] >= 100.0) {
          FOpid_RL_X.IntegratorSecondOrderLimited__f[0] = 100.0;
          if (FOpid_RL_X.IntegratorSecondOrderLimited__f[1] < 0.0) {
            FOpid_RL_DW.IntegratorSecondOrderLimited_h4 = 0;
          } else {
            FOpid_RL_X.IntegratorSecondOrderLimited__f[1] = 0.0;
            FOpid_RL_DW.IntegratorSecondOrderLimited_h4 = 2;
          }

          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)
            ->solverInfo, true);
        }

        if (FOpid_RL_X.IntegratorSecondOrderLimited__f[1] <= -8.726646259971647)
        {
          FOpid_RL_X.IntegratorSecondOrderLimited__f[1] = -8.726646259971647;
          FOpid_RL_DW.IntegratorSecondOrderLimited_h4 = 3;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)
            ->solverInfo, true);
        }

        if (FOpid_RL_X.IntegratorSecondOrderLimited__f[1] >= 8.726646259971647)
        {
          FOpid_RL_X.IntegratorSecondOrderLimited__f[1] = 8.726646259971647;
          FOpid_RL_DW.IntegratorSecondOrderLimited_h4 = 4;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)
            ->solverInfo, true);
        }
        break;

       case 1:
        if (FOpid_RL_X.IntegratorSecondOrderLimited__f[0] > 0.0) {
          if (FOpid_RL_X.IntegratorSecondOrderLimited__f[0] >= 100.0) {
            FOpid_RL_DW.IntegratorSecondOrderLimited_h4 = 2;
            FOpid_RL_X.IntegratorSecondOrderLimited__f[0] = 100.0;
          } else {
            FOpid_RL_DW.IntegratorSecondOrderLimited_h4 = 0;
          }
        } else {
          FOpid_RL_X.IntegratorSecondOrderLimited__f[0] = 0.0;
          FOpid_RL_X.IntegratorSecondOrderLimited__f[1] = 0.0;
        }
        break;

       case 2:
        if (FOpid_RL_X.IntegratorSecondOrderLimited__f[0] < 100.0) {
          if (FOpid_RL_X.IntegratorSecondOrderLimited__f[0] <= 0.0) {
            FOpid_RL_DW.IntegratorSecondOrderLimited_h4 = 1;
            FOpid_RL_X.IntegratorSecondOrderLimited__f[0] = 0.0;
          } else {
            FOpid_RL_DW.IntegratorSecondOrderLimited_h4 = 0;
          }
        } else {
          FOpid_RL_X.IntegratorSecondOrderLimited__f[0] = 100.0;
          FOpid_RL_X.IntegratorSecondOrderLimited__f[1] = 0.0;
        }
        break;

       case 3:
        if (FOpid_RL_X.IntegratorSecondOrderLimited__f[1] > -8.726646259971647)
        {
          if (FOpid_RL_X.IntegratorSecondOrderLimited__f[1] >= 8.726646259971647)
          {
            FOpid_RL_DW.IntegratorSecondOrderLimited_h4 = 4;
            FOpid_RL_X.IntegratorSecondOrderLimited__f[1] = 8.726646259971647;
          } else {
            FOpid_RL_DW.IntegratorSecondOrderLimited_h4 = 0;
          }
        } else {
          FOpid_RL_X.IntegratorSecondOrderLimited__f[1] = -8.726646259971647;
        }

        if (FOpid_RL_X.IntegratorSecondOrderLimited__f[0] <= 0.0) {
          FOpid_RL_X.IntegratorSecondOrderLimited__f[0] = 0.0;
          FOpid_RL_X.IntegratorSecondOrderLimited__f[1] = 0.0;
          FOpid_RL_DW.IntegratorSecondOrderLimited_h4 = 1;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)
            ->solverInfo, true);
        }
        break;

       case 4:
        if (FOpid_RL_X.IntegratorSecondOrderLimited__f[1] < 8.726646259971647) {
          if (FOpid_RL_X.IntegratorSecondOrderLimited__f[1] <=
              -8.726646259971647) {
            FOpid_RL_DW.IntegratorSecondOrderLimited_h4 = 3;
            FOpid_RL_X.IntegratorSecondOrderLimited__f[1] = -8.726646259971647;
          } else {
            FOpid_RL_DW.IntegratorSecondOrderLimited_h4 = 0;
          }
        } else {
          FOpid_RL_X.IntegratorSecondOrderLimited__f[1] = 8.726646259971647;
        }

        if (FOpid_RL_X.IntegratorSecondOrderLimited__f[0] >= 100.0) {
          FOpid_RL_X.IntegratorSecondOrderLimited__f[0] = 100.0;
          FOpid_RL_X.IntegratorSecondOrderLimited__f[1] = 0.0;
          FOpid_RL_DW.IntegratorSecondOrderLimited_h4 = 2;
          rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)
            ->solverInfo, true);
        }
        break;
      }
    }

    if (FOpid_RL_X.IntegratorSecondOrderLimited__f[0] < 0.0) {
      FOpid_RL_B.cosa = 0.0;
    } else if (FOpid_RL_X.IntegratorSecondOrderLimited__f[0] > 100.0) {
      FOpid_RL_B.cosa = 100.0;
    } else {
      FOpid_RL_B.cosa = FOpid_RL_X.IntegratorSecondOrderLimited__f[0];
    }

    /* Sum: '<S26>/Sum3' incorporates:
     *  SecondOrderIntegrator: '<S26>/Integrator, Second-Order Limited'
     */
    FOpid_RL_B.sina = FOpid_RL_ConstB.Demandlimits_p - FOpid_RL_B.cosa;

    /* Saturate: '<S26>/rate limit*2*zeta//wn' */
    if (FOpid_RL_B.sina > 5.235987755982988) {
      FOpid_RL_B.sina = 5.235987755982988;
    } else if (FOpid_RL_B.sina < -5.235987755982988) {
      FOpid_RL_B.sina = -5.235987755982988;
    }

    /* SecondOrderIntegrator: '<S26>/Integrator, Second-Order Limited' */
    if (FOpid_RL_X.IntegratorSecondOrderLimited__f[1] < -8.726646259971647) {
      FOpid_RL_B.cosa = -8.726646259971647;
    } else if (FOpid_RL_X.IntegratorSecondOrderLimited__f[1] > 8.726646259971647)
    {
      FOpid_RL_B.cosa = 8.726646259971647;
    } else {
      FOpid_RL_B.cosa = FOpid_RL_X.IntegratorSecondOrderLimited__f[1];
    }

    /* Sum: '<S26>/Sum2' incorporates:
     *  Gain: '<S26>/2*zeta * wn'
     *  Saturate: '<S26>/rate limit*2*zeta//wn'
     *  SecondOrderIntegrator: '<S26>/Integrator, Second-Order Limited'
     */
    FOpid_RL_B.Sum2_ba = FOpid_RL_B.sina - 0.6 * FOpid_RL_B.cosa;

    /* S-Function (sfun_tstart): '<S31>/startTime' */
    FOpid_RL_B.startTime = 0.0;
  }

  if (rtmIsMajorTimeStep((&FOpid_RL_M))) {
    int32_T i;

    /* Update for Integrator: '<S33>/Integrator' */
    FOpid_RL_DW.Integrator_DWORK1 = false;
    if (rtmIsMajorTimeStep((&FOpid_RL_M)) &&
        (&FOpid_RL_M)->Timing.TaskCounters.TID[1] == 0) {
      /* Update for Memory: '<S33>/Memory2' incorporates:
       *  Integrator: '<S33>/Integrator'
       */
      memcpy(&FOpid_RL_DW.Memory2_PreviousInput[0], &FOpid_RL_B.x[0], 12U *
             sizeof(real_T));

      /* Update for UnitDelay: '<Root>/Unit Delay3' */
      FOpid_RL_DW.UnitDelay3_DSTATE = FOpid_RL_B.Switch3;

      /* Update for UnitDelay: '<Root>/Unit Delay2' */
      FOpid_RL_DW.UnitDelay2_DSTATE = FOpid_RL_B.Switch2;

      /* Update for RandomNumber: '<S59>/White Noise' */
      FOpid_RL_DW.NextOutput[0] = rt_nrand_Upu32_Yd_f_pw_snf
        (&FOpid_RL_DW.RandSeed[0]);
      FOpid_RL_DW.NextOutput[1] = rt_nrand_Upu32_Yd_f_pw_snf
        (&FOpid_RL_DW.RandSeed[1]);
      FOpid_RL_DW.NextOutput[2] = rt_nrand_Upu32_Yd_f_pw_snf
        (&FOpid_RL_DW.RandSeed[2]);
      FOpid_RL_DW.NextOutput[3] = rt_nrand_Upu32_Yd_f_pw_snf
        (&FOpid_RL_DW.RandSeed[3]);

      /* Update for Memory: '<S33>/Memory' incorporates:
       *  Sum: '<S33>/SumOLA'
       */
      FOpid_RL_DW.Memory_PreviousInput[0] = FOpid_RL_B.SumOLA[0];

      /* Update for Memory: '<S33>/Memory1' incorporates:
       *  Sum: '<S33>/SumOLA1'
       */
      FOpid_RL_DW.Memory1_PreviousInput[0] = FOpid_RL_B.SumOLA1[0];

      /* Update for Memory: '<S33>/Memory' incorporates:
       *  Sum: '<S33>/SumOLA'
       */
      FOpid_RL_DW.Memory_PreviousInput[1] = FOpid_RL_B.SumOLA[1];

      /* Update for Memory: '<S33>/Memory1' incorporates:
       *  Sum: '<S33>/SumOLA1'
       */
      FOpid_RL_DW.Memory1_PreviousInput[1] = FOpid_RL_B.SumOLA1[1];

      /* Update for Memory: '<S33>/Memory' incorporates:
       *  Sum: '<S33>/SumOLA'
       */
      FOpid_RL_DW.Memory_PreviousInput[2] = FOpid_RL_B.SumOLA[2];

      /* Update for Memory: '<S33>/Memory1' incorporates:
       *  Sum: '<S33>/SumOLA1'
       */
      FOpid_RL_DW.Memory1_PreviousInput[2] = FOpid_RL_B.SumOLA1[2];

      /* Update for RandomNumber: '<S39>/White Noise' */
      FOpid_RL_DW.NextOutput_k = rt_nrand_Upu32_Yd_f_pw_snf
        (&FOpid_RL_DW.RandSeed_a);
    }

    /* Update for SecondOrderIntegrator: '<S22>/Integrator, Second-Order Limited' */
    i = FOpid_RL_DW.IntegratorSecondOrderLimited_MO;
    if ((((FOpid_RL_DW.IntegratorSecondOrderLimited_MO == 1) ||
          (FOpid_RL_DW.IntegratorSecondOrderLimited_MO == 3)) &&
         (FOpid_RL_B.Sum2_j > 0.0)) ||
        (((FOpid_RL_DW.IntegratorSecondOrderLimited_MO == 2) ||
          (FOpid_RL_DW.IntegratorSecondOrderLimited_MO == 4)) &&
         (FOpid_RL_B.Sum2_j < 0.0))) {
      i = 0;
    }

    if (FOpid_RL_DW.IntegratorSecondOrderLimited_MO != i) {
      FOpid_RL_DW.IntegratorSecondOrderLimited_MO = i;
      rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)->solverInfo,
        true);
    }

    /* End of Update for SecondOrderIntegrator: '<S22>/Integrator, Second-Order Limited' */

    /* Update for SecondOrderIntegrator: '<S23>/Integrator, Second-Order Limited' */
    i = FOpid_RL_DW.IntegratorSecondOrderLimited__h;
    if ((((FOpid_RL_DW.IntegratorSecondOrderLimited__h == 1) ||
          (FOpid_RL_DW.IntegratorSecondOrderLimited__h == 3)) &&
         (FOpid_RL_B.Sum2_f > 0.0)) ||
        (((FOpid_RL_DW.IntegratorSecondOrderLimited__h == 2) ||
          (FOpid_RL_DW.IntegratorSecondOrderLimited__h == 4)) &&
         (FOpid_RL_B.Sum2_f < 0.0))) {
      i = 0;
    }

    if (FOpid_RL_DW.IntegratorSecondOrderLimited__h != i) {
      FOpid_RL_DW.IntegratorSecondOrderLimited__h = i;
      rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)->solverInfo,
        true);
    }

    /* End of Update for SecondOrderIntegrator: '<S23>/Integrator, Second-Order Limited' */

    /* Update for SecondOrderIntegrator: '<S24>/Integrator, Second-Order Limited' */
    i = FOpid_RL_DW.IntegratorSecondOrderLimited__b;
    if ((((FOpid_RL_DW.IntegratorSecondOrderLimited__b == 1) ||
          (FOpid_RL_DW.IntegratorSecondOrderLimited__b == 3)) &&
         (FOpid_RL_B.Sum2_b > 0.0)) ||
        (((FOpid_RL_DW.IntegratorSecondOrderLimited__b == 2) ||
          (FOpid_RL_DW.IntegratorSecondOrderLimited__b == 4)) &&
         (FOpid_RL_B.Sum2_b < 0.0))) {
      i = 0;
    }

    if (FOpid_RL_DW.IntegratorSecondOrderLimited__b != i) {
      FOpid_RL_DW.IntegratorSecondOrderLimited__b = i;
      rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)->solverInfo,
        true);
    }

    /* End of Update for SecondOrderIntegrator: '<S24>/Integrator, Second-Order Limited' */

    /* Update for SecondOrderIntegrator: '<S25>/Integrator, Second-Order Limited' */
    i = FOpid_RL_DW.IntegratorSecondOrderLimited__o;
    if ((((FOpid_RL_DW.IntegratorSecondOrderLimited__o == 1) ||
          (FOpid_RL_DW.IntegratorSecondOrderLimited__o == 3)) &&
         (FOpid_RL_B.Sum2_jg > 0.0)) ||
        (((FOpid_RL_DW.IntegratorSecondOrderLimited__o == 2) ||
          (FOpid_RL_DW.IntegratorSecondOrderLimited__o == 4)) &&
         (FOpid_RL_B.Sum2_jg < 0.0))) {
      i = 0;
    }

    if (FOpid_RL_DW.IntegratorSecondOrderLimited__o != i) {
      FOpid_RL_DW.IntegratorSecondOrderLimited__o = i;
      rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)->solverInfo,
        true);
    }

    /* End of Update for SecondOrderIntegrator: '<S25>/Integrator, Second-Order Limited' */

    /* Update for SecondOrderIntegrator: '<S26>/Integrator, Second-Order Limited' */
    i = FOpid_RL_DW.IntegratorSecondOrderLimited_h4;
    if ((((FOpid_RL_DW.IntegratorSecondOrderLimited_h4 == 1) ||
          (FOpid_RL_DW.IntegratorSecondOrderLimited_h4 == 3)) &&
         (FOpid_RL_B.Sum2_ba > 0.0)) ||
        (((FOpid_RL_DW.IntegratorSecondOrderLimited_h4 == 2) ||
          (FOpid_RL_DW.IntegratorSecondOrderLimited_h4 == 4)) &&
         (FOpid_RL_B.Sum2_ba < 0.0))) {
      i = 0;
    }

    if (FOpid_RL_DW.IntegratorSecondOrderLimited_h4 != i) {
      FOpid_RL_DW.IntegratorSecondOrderLimited_h4 = i;
      rtsiSetBlockStateForSolverChangedAtMajorStep(&(&FOpid_RL_M)->solverInfo,
        true);
    }

    /* End of Update for SecondOrderIntegrator: '<S26>/Integrator, Second-Order Limited' */

    /* ContTimeOutputInconsistentWithStateAtMajorOutputFlag is set, need to run a minor output */
    if (rtmIsMajorTimeStep((&FOpid_RL_M))) {
      if (rtsiGetContTimeOutputInconsistentWithStateAtMajorStep(&(&FOpid_RL_M)
           ->solverInfo)) {
        rtsiSetSimTimeStep(&(&FOpid_RL_M)->solverInfo,MINOR_TIME_STEP);
        rtsiSetContTimeOutputInconsistentWithStateAtMajorStep(&(&FOpid_RL_M)
          ->solverInfo, false);
        FOpid_RL::step();
        rtsiSetSimTimeStep(&(&FOpid_RL_M)->solverInfo, MAJOR_TIME_STEP);
      }
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep((&FOpid_RL_M))) {
    rt_ertODEUpdateContinuousStates(&(&FOpid_RL_M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if ((++(&FOpid_RL_M)->Timing.clockTick0)==0) {
      ++(&FOpid_RL_M)->Timing.clockTickH0;
    }

    (&FOpid_RL_M)->Timing.t[0] = rtsiGetSolverStopTime(&(&FOpid_RL_M)
      ->solverInfo);

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
      (&FOpid_RL_M)->Timing.clockTick1++;
      if ((&FOpid_RL_M)->Timing.clockTick1==0) {
        (&FOpid_RL_M)->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void FOpid_RL::FOpid_RL_derivatives()
{
  XDot_FOpid_RL_T *_rtXdot;
  real_T tmp[2];
  _rtXdot = ((XDot_FOpid_RL_T *) (&FOpid_RL_M)->derivs);

  /* Derivatives for Integrator: '<S33>/Integrator' */
  if (!FOpid_RL_B.Compare) {
    memcpy(&_rtXdot->Integrator_CSTATE[0], &FOpid_RL_B.XDOT[0], 12U * sizeof
           (real_T));
  } else {
    /* level reset is active */
    memset(&_rtXdot->Integrator_CSTATE[0], 0, 12U * sizeof(real_T));
  }

  /* End of Derivatives for Integrator: '<S33>/Integrator' */

  /* Derivatives for Enabled SubSystem: '<S49>/Hpgw' */
  if (FOpid_RL_DW.Hpgw_MODE) {
    /* Derivatives for Integrator: '<S60>/pgw_p' */
    _rtXdot->pgw_p_CSTATE[0] = FOpid_RL_B.w_o[0];
    _rtXdot->pgw_p_CSTATE[1] = FOpid_RL_B.w_o[1];
  } else {
    {
      real_T *dx;
      int_T i1;
      dx = &(((XDot_FOpid_RL_T *) (&FOpid_RL_M)->derivs)->pgw_p_CSTATE[0]);
      for (i1=0; i1 < 2; i1++) {
        dx[i1] = 0.0;
      }
    }
  }

  /* End of Derivatives for SubSystem: '<S49>/Hpgw' */

  /* Derivatives for Enabled SubSystem: '<S50>/Hwgw(s)' */
  if (FOpid_RL_DW.Hwgws_MODE) {
    /* Derivatives for Integrator: '<S65>/wg_p1' */
    _rtXdot->wg_p1_CSTATE[0] = FOpid_RL_B.w[0];

    /* Derivatives for Integrator: '<S65>/wg_p2' */
    _rtXdot->wg_p2_CSTATE[0] = FOpid_RL_B.w_a[0];

    /* Derivatives for Integrator: '<S65>/wg_p1' */
    _rtXdot->wg_p1_CSTATE[1] = FOpid_RL_B.w[1];

    /* Derivatives for Integrator: '<S65>/wg_p2' */
    _rtXdot->wg_p2_CSTATE[1] = FOpid_RL_B.w_a[1];
  } else {
    {
      real_T *dx;
      int_T i1;
      dx = &(((XDot_FOpid_RL_T *) (&FOpid_RL_M)->derivs)->wg_p1_CSTATE[0]);
      for (i1=0; i1 < 4; i1++) {
        dx[i1] = 0.0;
      }
    }
  }

  /* End of Derivatives for SubSystem: '<S50>/Hwgw(s)' */

  /* Derivatives for Enabled SubSystem: '<S49>/Hqgw' */
  if (FOpid_RL_DW.Hqgw_MODE) {
    /* Derivatives for Integrator: '<S61>/qgw_p' */
    _rtXdot->qgw_p_CSTATE[0] = FOpid_RL_B.w_e0[0];
    _rtXdot->qgw_p_CSTATE[1] = FOpid_RL_B.w_e0[1];
  } else {
    {
      real_T *dx;
      int_T i1;
      dx = &(((XDot_FOpid_RL_T *) (&FOpid_RL_M)->derivs)->qgw_p_CSTATE[0]);
      for (i1=0; i1 < 2; i1++) {
        dx[i1] = 0.0;
      }
    }
  }

  /* End of Derivatives for SubSystem: '<S49>/Hqgw' */

  /* Derivatives for Enabled SubSystem: '<S50>/Hvgw(s)' */
  if (FOpid_RL_DW.Hvgws_MODE) {
    /* Derivatives for Integrator: '<S64>/vg_p1' */
    _rtXdot->vg_p1_CSTATE[0] = FOpid_RL_B.w_g[0];

    /* Derivatives for Integrator: '<S64>/vgw_p2' */
    _rtXdot->vgw_p2_CSTATE[0] = FOpid_RL_B.w_e[0];

    /* Derivatives for Integrator: '<S64>/vg_p1' */
    _rtXdot->vg_p1_CSTATE[1] = FOpid_RL_B.w_g[1];

    /* Derivatives for Integrator: '<S64>/vgw_p2' */
    _rtXdot->vgw_p2_CSTATE[1] = FOpid_RL_B.w_e[1];
  } else {
    {
      real_T *dx;
      int_T i1;
      dx = &(((XDot_FOpid_RL_T *) (&FOpid_RL_M)->derivs)->vg_p1_CSTATE[0]);
      for (i1=0; i1 < 4; i1++) {
        dx[i1] = 0.0;
      }
    }
  }

  /* End of Derivatives for SubSystem: '<S50>/Hvgw(s)' */

  /* Derivatives for Enabled SubSystem: '<S49>/Hrgw' */
  if (FOpid_RL_DW.Hrgw_MODE) {
    /* Derivatives for Integrator: '<S62>/rgw_p' */
    _rtXdot->rgw_p_CSTATE[0] = FOpid_RL_B.w_d[0];
    _rtXdot->rgw_p_CSTATE[1] = FOpid_RL_B.w_d[1];
  } else {
    {
      real_T *dx;
      int_T i1;
      dx = &(((XDot_FOpid_RL_T *) (&FOpid_RL_M)->derivs)->rgw_p_CSTATE[0]);
      for (i1=0; i1 < 2; i1++) {
        dx[i1] = 0.0;
      }
    }
  }

  /* End of Derivatives for SubSystem: '<S49>/Hrgw' */

  /* Derivatives for TransferFcn: '<S33>/Transfer Fcn1' */
  _rtXdot->TransferFcn1_CSTATE = 0.0;
  _rtXdot->TransferFcn1_CSTATE += -0.01 * FOpid_RL_X.TransferFcn1_CSTATE;
  _rtXdot->TransferFcn1_CSTATE += FOpid_RL_B.Output;

  /* Derivatives for Enabled SubSystem: '<S50>/Hugw(s)' */
  if (FOpid_RL_DW.Hugws_MODE) {
    /* Derivatives for Integrator: '<S63>/ug_p' */
    _rtXdot->ug_p_CSTATE[0] = FOpid_RL_B.w_n[0];
    _rtXdot->ug_p_CSTATE[1] = FOpid_RL_B.w_n[1];
  } else {
    {
      real_T *dx;
      int_T i1;
      dx = &(((XDot_FOpid_RL_T *) (&FOpid_RL_M)->derivs)->ug_p_CSTATE[0]);
      for (i1=0; i1 < 2; i1++) {
        dx[i1] = 0.0;
      }
    }
  }

  /* End of Derivatives for SubSystem: '<S50>/Hugw(s)' */

  /* Derivatives for TransferFcn: '<S33>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE[0] = 0.0;
  _rtXdot->TransferFcn_CSTATE[0] += -0.898 * FOpid_RL_X.TransferFcn_CSTATE[0];
  _rtXdot->TransferFcn_CSTATE[1] = 0.0;
  _rtXdot->TransferFcn_CSTATE[0] += -0.806 * FOpid_RL_X.TransferFcn_CSTATE[1];
  _mm_storeu_pd(&tmp[0], _mm_add_pd(_mm_set_pd(_rtXdot->TransferFcn_CSTATE[0],
    FOpid_RL_X.TransferFcn_CSTATE[0]), _mm_set_pd(FOpid_RL_B.Output,
    _rtXdot->TransferFcn_CSTATE[1])));
  _rtXdot->TransferFcn_CSTATE[1] = tmp[0];
  _rtXdot->TransferFcn_CSTATE[0] = tmp[1];

  /* Derivatives for Integrator: '<S33>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = FOpid_RL_B.Power;

  /* Derivatives for SecondOrderIntegrator: '<S22>/Integrator, Second-Order Limited' */
  switch (FOpid_RL_DW.IntegratorSecondOrderLimited_MO) {
   case 0:
    _rtXdot->IntegratorSecondOrderLimited_CS[0] =
      FOpid_RL_X.IntegratorSecondOrderLimited_CS[1];
    _rtXdot->IntegratorSecondOrderLimited_CS[1] = FOpid_RL_B.Sum2_j;
    break;

   case 3:
    _rtXdot->IntegratorSecondOrderLimited_CS[0] =
      FOpid_RL_X.IntegratorSecondOrderLimited_CS[1];
    _rtXdot->IntegratorSecondOrderLimited_CS[1] = 0.0;
    break;

   case 4:
    _rtXdot->IntegratorSecondOrderLimited_CS[0] =
      FOpid_RL_X.IntegratorSecondOrderLimited_CS[1];
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

  /* End of Derivatives for SecondOrderIntegrator: '<S22>/Integrator, Second-Order Limited' */

  /* Derivatives for SecondOrderIntegrator: '<S23>/Integrator, Second-Order Limited' */
  switch (FOpid_RL_DW.IntegratorSecondOrderLimited__h) {
   case 0:
    _rtXdot->IntegratorSecondOrderLimited__n[0] =
      FOpid_RL_X.IntegratorSecondOrderLimited__n[1];
    _rtXdot->IntegratorSecondOrderLimited__n[1] = FOpid_RL_B.Sum2_f;
    break;

   case 3:
    _rtXdot->IntegratorSecondOrderLimited__n[0] =
      FOpid_RL_X.IntegratorSecondOrderLimited__n[1];
    _rtXdot->IntegratorSecondOrderLimited__n[1] = 0.0;
    break;

   case 4:
    _rtXdot->IntegratorSecondOrderLimited__n[0] =
      FOpid_RL_X.IntegratorSecondOrderLimited__n[1];
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

  /* End of Derivatives for SecondOrderIntegrator: '<S23>/Integrator, Second-Order Limited' */

  /* Derivatives for SecondOrderIntegrator: '<S24>/Integrator, Second-Order Limited' */
  switch (FOpid_RL_DW.IntegratorSecondOrderLimited__b) {
   case 0:
    _rtXdot->IntegratorSecondOrderLimited__a[0] =
      FOpid_RL_X.IntegratorSecondOrderLimited__a[1];
    _rtXdot->IntegratorSecondOrderLimited__a[1] = FOpid_RL_B.Sum2_b;
    break;

   case 3:
    _rtXdot->IntegratorSecondOrderLimited__a[0] =
      FOpid_RL_X.IntegratorSecondOrderLimited__a[1];
    _rtXdot->IntegratorSecondOrderLimited__a[1] = 0.0;
    break;

   case 4:
    _rtXdot->IntegratorSecondOrderLimited__a[0] =
      FOpid_RL_X.IntegratorSecondOrderLimited__a[1];
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

  /* End of Derivatives for SecondOrderIntegrator: '<S24>/Integrator, Second-Order Limited' */

  /* Derivatives for SecondOrderIntegrator: '<S25>/Integrator, Second-Order Limited' */
  switch (FOpid_RL_DW.IntegratorSecondOrderLimited__o) {
   case 0:
    _rtXdot->IntegratorSecondOrderLimited__i[0] =
      FOpid_RL_X.IntegratorSecondOrderLimited__i[1];
    _rtXdot->IntegratorSecondOrderLimited__i[1] = FOpid_RL_B.Sum2_jg;
    break;

   case 3:
    _rtXdot->IntegratorSecondOrderLimited__i[0] =
      FOpid_RL_X.IntegratorSecondOrderLimited__i[1];
    _rtXdot->IntegratorSecondOrderLimited__i[1] = 0.0;
    break;

   case 4:
    _rtXdot->IntegratorSecondOrderLimited__i[0] =
      FOpid_RL_X.IntegratorSecondOrderLimited__i[1];
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

  /* End of Derivatives for SecondOrderIntegrator: '<S25>/Integrator, Second-Order Limited' */

  /* Derivatives for SecondOrderIntegrator: '<S26>/Integrator, Second-Order Limited' */
  switch (FOpid_RL_DW.IntegratorSecondOrderLimited_h4) {
   case 0:
    _rtXdot->IntegratorSecondOrderLimited__f[0] =
      FOpid_RL_X.IntegratorSecondOrderLimited__f[1];
    _rtXdot->IntegratorSecondOrderLimited__f[1] = FOpid_RL_B.Sum2_ba;
    break;

   case 3:
    _rtXdot->IntegratorSecondOrderLimited__f[0] =
      FOpid_RL_X.IntegratorSecondOrderLimited__f[1];
    _rtXdot->IntegratorSecondOrderLimited__f[1] = 0.0;
    break;

   case 4:
    _rtXdot->IntegratorSecondOrderLimited__f[0] =
      FOpid_RL_X.IntegratorSecondOrderLimited__f[1];
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

  /* End of Derivatives for SecondOrderIntegrator: '<S26>/Integrator, Second-Order Limited' */
}

/* Model initialize function */
void FOpid_RL::initialize()
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&FOpid_RL_M)->solverInfo, &(&FOpid_RL_M)
                          ->Timing.simTimeStep);
    rtsiSetTPtr(&(&FOpid_RL_M)->solverInfo, &rtmGetTPtr((&FOpid_RL_M)));
    rtsiSetStepSizePtr(&(&FOpid_RL_M)->solverInfo, &(&FOpid_RL_M)
                       ->Timing.stepSize0);
    rtsiSetdXPtr(&(&FOpid_RL_M)->solverInfo, &(&FOpid_RL_M)->derivs);
    rtsiSetContStatesPtr(&(&FOpid_RL_M)->solverInfo, (real_T **) &(&FOpid_RL_M
                         )->contStates);
    rtsiSetNumContStatesPtr(&(&FOpid_RL_M)->solverInfo, &(&FOpid_RL_M)
      ->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&FOpid_RL_M)->solverInfo, &(&FOpid_RL_M)
      ->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&FOpid_RL_M)->solverInfo, &(&FOpid_RL_M)
      ->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&FOpid_RL_M)->solverInfo, &(&FOpid_RL_M
      )->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&(&FOpid_RL_M)->solverInfo, (boolean_T**)
      &(&FOpid_RL_M)->contStateDisabled);
    rtsiSetErrorStatusPtr(&(&FOpid_RL_M)->solverInfo, (&rtmGetErrorStatus
      ((&FOpid_RL_M))));
    rtsiSetRTModelPtr(&(&FOpid_RL_M)->solverInfo, (&FOpid_RL_M));
  }

  rtsiSetSimTimeStep(&(&FOpid_RL_M)->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&(&FOpid_RL_M)->solverInfo, false);
  rtsiSetIsContModeFrozen(&(&FOpid_RL_M)->solverInfo, false);
  (&FOpid_RL_M)->intgData.y = (&FOpid_RL_M)->odeY;
  (&FOpid_RL_M)->intgData.f[0] = (&FOpid_RL_M)->odeF[0];
  (&FOpid_RL_M)->intgData.f[1] = (&FOpid_RL_M)->odeF[1];
  (&FOpid_RL_M)->intgData.f[2] = (&FOpid_RL_M)->odeF[2];
  (&FOpid_RL_M)->intgData.f[3] = (&FOpid_RL_M)->odeF[3];
  (&FOpid_RL_M)->contStates = ((X_FOpid_RL_T *) &FOpid_RL_X);
  (&FOpid_RL_M)->contStateDisabled = ((XDis_FOpid_RL_T *) &FOpid_RL_XDis);
  (&FOpid_RL_M)->Timing.tStart = (0.0);
  rtsiSetSolverData(&(&FOpid_RL_M)->solverInfo, static_cast<void *>
                    (&(&FOpid_RL_M)->intgData));
  rtsiSetSolverName(&(&FOpid_RL_M)->solverInfo,"ode4");
  rtmSetTPtr((&FOpid_RL_M), &(&FOpid_RL_M)->Timing.tArray[0]);
  (&FOpid_RL_M)->Timing.stepSize0 = 0.01;
  rtmSetFirstInitCond((&FOpid_RL_M), 1);

  {
    rmw_qos_profile_t qos_profile;
    int32_T i;
    static const char_T b_zeroDelimTopic[18] = "/ekranoplano/odom";

    /* Start for InitialCondition: '<S33>/IC' */
    memcpy(&FOpid_RL_B.IC[0], &FOpid_RL_ConstP.pooled14[0], 12U * sizeof(real_T));

    /* Start for InitialCondition: '<S33>/IC' */
    FOpid_RL_DW.IC_FirstOutputTime = true;

    /* Start for MATLABSystem: '<Root>/Coordinate Transformation Conversion' */
    FOpid_RL_DW.objisempty_d = true;
    FOpid_RL_DW.obj_c.isInitialized = 1;

    /* Start for MATLABSystem: '<S27>/SinkBlock' */
    FOpid_RL_DW.obj_i.QOSAvoidROSNamespaceConventions = false;
    FOpid_RL_DW.obj_i.matlabCodegenIsDeleted = false;
    FOpid_RL_DW.objisempty_m = true;
    FOpid_RL_DW.obj_i.isSetupComplete = false;
    FOpid_RL_DW.obj_i.isInitialized = 1;
    FOpid_RL_Publisher_setupImpl(&FOpid_RL_DW.obj_i);
    FOpid_RL_DW.obj_i.isSetupComplete = true;

    /* Start for MATLABSystem: '<S28>/SinkBlock' */
    FOpid_RL_DW.obj_o.QOSAvoidROSNamespaceConventions = false;
    FOpid_RL_DW.obj_o.matlabCodegenIsDeleted = false;
    FOpid_RL_DW.objisempty_ev = true;
    FOpid_RL_DW.obj_o.isSetupComplete = false;
    FOpid_RL_DW.obj_o.isInitialized = 1;
    qos_profile = FO_ROS2PubSubBase_setQOSProfile(rmw_qos_profile_default, 10.0,
      (rtInf), (rtInf), (rtInf),
      FOpid_RL_DW.obj_o.QOSAvoidROSNamespaceConventions);
    for (i = 0; i < 18; i++) {
      FOpid_RL_B.b_zeroDelimTopic_b[i] = b_zeroDelimTopic[i];
    }

    Pub_FOpid_RL_697.createPublisher(&FOpid_RL_B.b_zeroDelimTopic_b[0],
      qos_profile);
    FOpid_RL_DW.obj_o.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S28>/SinkBlock' */

    /* Start for MATLABSystem: '<S29>/SinkBlock' */
    FOpid_RL_DW.obj_dl.QOSAvoidROSNamespaceConventions = false;
    FOpid_RL_DW.obj_dl.matlabCodegenIsDeleted = false;
    FOpid_RL_DW.objisempty_ld = true;
    FOpid_RL_DW.obj_dl.isSetupComplete = false;
    FOpid_RL_DW.obj_dl.isInitialized = 1;
    FOpid_RL_Publisher_setupImpl_b(&FOpid_RL_DW.obj_dl);
    FOpid_RL_DW.obj_dl.isSetupComplete = true;

    /* Start for MATLABSystem: '<S30>/SinkBlock' */
    FOpid_RL_DW.obj_d.QOSAvoidROSNamespaceConventions = false;
    FOpid_RL_DW.obj_d.matlabCodegenIsDeleted = false;
    FOpid_RL_DW.objisempty_cr = true;
    FOpid_RL_DW.obj_d.isSetupComplete = false;
    FOpid_RL_DW.obj_d.isInitialized = 1;
    FOpid_RL_Publisher_setupImpl_bf(&FOpid_RL_DW.obj_d);
    FOpid_RL_DW.obj_d.isSetupComplete = true;

    /* Start for MATLABSystem: '<S34>/SourceBlock' */
    FOpid_RL_DW.obj_m.QOSAvoidROSNamespaceConventions = false;
    FOpid_RL_DW.obj_m.matlabCodegenIsDeleted = false;
    FOpid_RL_DW.objisempty_g = true;
    FOpid_RL_DW.obj_m.isSetupComplete = false;
    FOpid_RL_DW.obj_m.isInitialized = 1;
    FOpid_Subscriber_setupImpl_bfq4(&FOpid_RL_DW.obj_m);
    FOpid_RL_DW.obj_m.isSetupComplete = true;

    /* Start for MATLABSystem: '<S35>/SourceBlock' */
    FOpid_RL_DW.obj_k.QOSAvoidROSNamespaceConventions = false;
    FOpid_RL_DW.obj_k.matlabCodegenIsDeleted = false;
    FOpid_RL_DW.objisempty = true;
    FOpid_RL_DW.obj_k.isSetupComplete = false;
    FOpid_RL_DW.obj_k.isInitialized = 1;
    FOpi_Subscriber_setupImpl_bfq4p(&FOpid_RL_DW.obj_k);
    FOpid_RL_DW.obj_k.isSetupComplete = true;

    /* Start for Atomic SubSystem: '<Root>/Call Service' */
    /* Start for MATLABSystem: '<S6>/ServiceCaller' */
    FOpid_RL_DW.obj.QOSAvoidROSNamespaceConventions = false;
    FOpid_RL_DW.obj.matlabCodegenIsDeleted = false;
    FOpid_RL_DW.objisempty_f = true;
    FOpid_RL_DW.obj.isSetupComplete = false;
    FOpid_RL_DW.obj.isInitialized = 1;
    FOpid_R_ServiceCaller_setupImpl(&FOpid_RL_DW.obj);
    FOpid_RL_DW.obj.isSetupComplete = true;

    /* End of Start for SubSystem: '<Root>/Call Service' */

    /* Start for Enabled SubSystem: '<S49>/Hpgw' */
    (void) memset(&(FOpid_RL_XDis.pgw_p_CSTATE), 1,
                  2*sizeof(boolean_T));

    /* End of Start for SubSystem: '<S49>/Hpgw' */

    /* Start for Enabled SubSystem: '<S50>/Hwgw(s)' */
    (void) memset(&(FOpid_RL_XDis.wg_p1_CSTATE), 1,
                  4*sizeof(boolean_T));

    /* End of Start for SubSystem: '<S50>/Hwgw(s)' */

    /* Start for Enabled SubSystem: '<S49>/Hqgw' */
    (void) memset(&(FOpid_RL_XDis.qgw_p_CSTATE), 1,
                  2*sizeof(boolean_T));

    /* End of Start for SubSystem: '<S49>/Hqgw' */

    /* Start for Enabled SubSystem: '<S50>/Hvgw(s)' */
    (void) memset(&(FOpid_RL_XDis.vg_p1_CSTATE), 1,
                  4*sizeof(boolean_T));

    /* End of Start for SubSystem: '<S50>/Hvgw(s)' */

    /* Start for Enabled SubSystem: '<S49>/Hrgw' */
    (void) memset(&(FOpid_RL_XDis.rgw_p_CSTATE), 1,
                  2*sizeof(boolean_T));

    /* End of Start for SubSystem: '<S49>/Hrgw' */

    /* Start for If: '<S54>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
    FOpid_RL_DW.ifHeightMaxlowaltitudeelseifHei = -1;

    /* Start for MATLABSystem: '<S44>/SourceBlock' */
    FOpid_RL_DW.obj_h4.QOSAvoidROSNamespaceConventions = false;
    FOpid_RL_DW.obj_h4.matlabCodegenIsDeleted = false;
    FOpid_RL_DW.objisempty_c = true;
    FOpid_RL_DW.obj_h4.isSetupComplete = false;
    FOpid_RL_DW.obj_h4.isInitialized = 1;
    FOpid_RL_Subscriber_setupImpl(&FOpid_RL_DW.obj_h4);
    FOpid_RL_DW.obj_h4.isSetupComplete = true;

    /* Start for MATLABSystem: '<S46>/SourceBlock' */
    FOpid_RL_DW.obj_p.QOSAvoidROSNamespaceConventions = false;
    FOpid_RL_DW.obj_p.matlabCodegenIsDeleted = false;
    FOpid_RL_DW.objisempty_e = true;
    FOpid_RL_DW.obj_p.isSetupComplete = false;
    FOpid_RL_DW.obj_p.isInitialized = 1;
    FOpid_R_Subscriber_setupImpl_bf(&FOpid_RL_DW.obj_p);
    FOpid_RL_DW.obj_p.isSetupComplete = true;

    /* Start for Enabled SubSystem: '<S50>/Hugw(s)' */
    (void) memset(&(FOpid_RL_XDis.ug_p_CSTATE), 1,
                  2*sizeof(boolean_T));

    /* End of Start for SubSystem: '<S50>/Hugw(s)' */

    /* Start for If: '<S55>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
    FOpid_RL_DW.ifHeightMaxlowaltitudeelseifH_k = -1;

    /* Start for MATLABSystem: '<S47>/SourceBlock' */
    FOpid_RL_DW.obj_h.QOSAvoidROSNamespaceConventions = false;
    FOpid_RL_DW.obj_h.matlabCodegenIsDeleted = false;
    FOpid_RL_DW.objisempty_a = true;
    FOpid_RL_DW.obj_h.isSetupComplete = false;
    FOpid_RL_DW.obj_h.isInitialized = 1;
    FOpid__Subscriber_setupImpl_bfq(&FOpid_RL_DW.obj_h);
    FOpid_RL_DW.obj_h.isSetupComplete = true;

    /* Start for MATLABSystem: '<S45>/SourceBlock' */
    FOpid_RL_DW.obj_hy.QOSAvoidROSNamespaceConventions = false;
    FOpid_RL_DW.obj_hy.matlabCodegenIsDeleted = false;
    FOpid_RL_DW.objisempty_l = true;
    FOpid_RL_DW.obj_hy.isSetupComplete = false;
    FOpid_RL_DW.obj_hy.isInitialized = 1;
    FOpid_RL_Subscriber_setupImpl_b(&FOpid_RL_DW.obj_hy);
    FOpid_RL_DW.obj_hy.isSetupComplete = true;
  }

  FOpid_RL_PrevZCX.Integrator_Reset_ZCE = UNINITIALIZED_ZCSIG;

  /* InitializeConditions for Memory: '<S33>/Memory2' */
  memcpy(&FOpid_RL_DW.Memory2_PreviousInput[0], &FOpid_RL_ConstP.pooled14[0],
         12U * sizeof(real_T));

  /* InitializeConditions for Integrator: '<S33>/Integrator' */
  if (rtmIsFirstInitCond((&FOpid_RL_M))) {
    FOpid_RL_X.Integrator_CSTATE[0] = 1.0;
    FOpid_RL_X.Integrator_CSTATE[1] = 0.0;
    FOpid_RL_X.Integrator_CSTATE[2] = 0.0;
    FOpid_RL_X.Integrator_CSTATE[3] = 0.0;
    FOpid_RL_X.Integrator_CSTATE[4] = 0.0;
    FOpid_RL_X.Integrator_CSTATE[5] = 0.0;
    FOpid_RL_X.Integrator_CSTATE[6] = 0.0;
    FOpid_RL_X.Integrator_CSTATE[7] = -0.026179938779914945;
    FOpid_RL_X.Integrator_CSTATE[8] = 0.0;
    FOpid_RL_X.Integrator_CSTATE[9] = 0.0;
    FOpid_RL_X.Integrator_CSTATE[10] = 0.0;
    FOpid_RL_X.Integrator_CSTATE[11] = -0.25;
  }

  FOpid_RL_DW.Integrator_DWORK1 = true;

  /* End of InitializeConditions for Integrator: '<S33>/Integrator' */

  /* InitializeConditions for UnitDelay: '<Root>/Unit Delay3' */
  FOpid_RL_DW.UnitDelay3_DSTATE = 0.8;

  /* InitializeConditions for RandomNumber: '<S59>/White Noise' */
  FOpid_RL_DW.RandSeed[0] = 1529675776U;
  FOpid_RL_DW.NextOutput[0] = rt_nrand_Upu32_Yd_f_pw_snf(&FOpid_RL_DW.RandSeed[0]);
  FOpid_RL_DW.RandSeed[1] = 1529741312U;
  FOpid_RL_DW.NextOutput[1] = rt_nrand_Upu32_Yd_f_pw_snf(&FOpid_RL_DW.RandSeed[1]);
  FOpid_RL_DW.RandSeed[2] = 1529806848U;
  FOpid_RL_DW.NextOutput[2] = rt_nrand_Upu32_Yd_f_pw_snf(&FOpid_RL_DW.RandSeed[2]);
  FOpid_RL_DW.RandSeed[3] = 1529872384U;
  FOpid_RL_DW.NextOutput[3] = rt_nrand_Upu32_Yd_f_pw_snf(&FOpid_RL_DW.RandSeed[3]);

  /* InitializeConditions for RandomNumber: '<S39>/White Noise' */
  FOpid_RL_DW.RandSeed_a = 1529675776U;
  FOpid_RL_DW.NextOutput_k = rt_nrand_Upu32_Yd_f_pw_snf(&FOpid_RL_DW.RandSeed_a);

  /* InitializeConditions for TransferFcn: '<S33>/Transfer Fcn1' */
  FOpid_RL_X.TransferFcn1_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S33>/Transfer Fcn' */
  FOpid_RL_X.TransferFcn_CSTATE[0] = 0.0;
  FOpid_RL_X.TransferFcn_CSTATE[1] = 0.0;

  /* InitializeConditions for Integrator: '<S33>/Integrator1' */
  FOpid_RL_X.Integrator1_CSTATE = 0.0;

  /* InitializeConditions for SecondOrderIntegrator: '<S22>/Integrator, Second-Order Limited' */
  FOpid_RL_X.IntegratorSecondOrderLimited_CS[0] = 0.0;
  FOpid_RL_X.IntegratorSecondOrderLimited_CS[1] = 0.0;

  /* InitializeConditions for SecondOrderIntegrator: '<S23>/Integrator, Second-Order Limited' */
  FOpid_RL_X.IntegratorSecondOrderLimited__n[0] = 0.0;
  FOpid_RL_X.IntegratorSecondOrderLimited__n[1] = 0.0;

  /* InitializeConditions for SecondOrderIntegrator: '<S24>/Integrator, Second-Order Limited' */
  FOpid_RL_X.IntegratorSecondOrderLimited__a[0] = 0.0;
  FOpid_RL_X.IntegratorSecondOrderLimited__a[1] = 0.0;

  /* InitializeConditions for SecondOrderIntegrator: '<S25>/Integrator, Second-Order Limited' */
  FOpid_RL_X.IntegratorSecondOrderLimited__i[0] = 0.0;
  FOpid_RL_X.IntegratorSecondOrderLimited__i[1] = 0.0;

  /* InitializeConditions for SecondOrderIntegrator: '<S26>/Integrator, Second-Order Limited' */
  FOpid_RL_X.IntegratorSecondOrderLimited__f[0] = 0.0;
  FOpid_RL_X.IntegratorSecondOrderLimited__f[1] = 0.0;

  /* SystemInitialize for Enabled SubSystem: '<S34>/Enabled Subsystem' */
  FOpid_R_EnabledSubsystem_e_Init(&FOpid_RL_B.EnabledSubsystem_b);

  /* End of SystemInitialize for SubSystem: '<S34>/Enabled Subsystem' */

  /* SystemInitialize for Enabled SubSystem: '<S35>/Enabled Subsystem' */
  FOpid_R_EnabledSubsystem_e_Init(&FOpid_RL_B.EnabledSubsystem_a);

  /* End of SystemInitialize for SubSystem: '<S35>/Enabled Subsystem' */

  /* SystemInitialize for Enabled SubSystem: '<S49>/Hpgw' */
  /* InitializeConditions for Integrator: '<S60>/pgw_p' */
  FOpid_RL_X.pgw_p_CSTATE[0] = 0.0;

  /* End of SystemInitialize for SubSystem: '<S49>/Hpgw' */

  /* SystemInitialize for Enabled SubSystem: '<S50>/Hwgw(s)' */
  /* InitializeConditions for Integrator: '<S65>/wg_p1' */
  FOpid_RL_X.wg_p1_CSTATE[0] = 0.0;

  /* InitializeConditions for Integrator: '<S65>/wg_p2' */
  FOpid_RL_X.wg_p2_CSTATE[0] = 0.0;

  /* End of SystemInitialize for SubSystem: '<S50>/Hwgw(s)' */

  /* SystemInitialize for Enabled SubSystem: '<S49>/Hqgw' */
  /* InitializeConditions for Integrator: '<S61>/qgw_p' */
  FOpid_RL_X.qgw_p_CSTATE[0] = 0.0;

  /* End of SystemInitialize for SubSystem: '<S49>/Hqgw' */

  /* SystemInitialize for Enabled SubSystem: '<S50>/Hvgw(s)' */
  /* InitializeConditions for Integrator: '<S64>/vg_p1' */
  FOpid_RL_X.vg_p1_CSTATE[0] = 0.0;

  /* InitializeConditions for Integrator: '<S64>/vgw_p2' */
  FOpid_RL_X.vgw_p2_CSTATE[0] = 0.0;

  /* End of SystemInitialize for SubSystem: '<S50>/Hvgw(s)' */

  /* SystemInitialize for Enabled SubSystem: '<S49>/Hrgw' */
  /* InitializeConditions for Integrator: '<S62>/rgw_p' */
  FOpid_RL_X.rgw_p_CSTATE[0] = 0.0;

  /* End of SystemInitialize for SubSystem: '<S49>/Hrgw' */

  /* SystemInitialize for Enabled SubSystem: '<S49>/Hpgw' */
  /* InitializeConditions for Integrator: '<S60>/pgw_p' */
  FOpid_RL_X.pgw_p_CSTATE[1] = 0.0;

  /* End of SystemInitialize for SubSystem: '<S49>/Hpgw' */

  /* SystemInitialize for Enabled SubSystem: '<S50>/Hwgw(s)' */
  /* InitializeConditions for Integrator: '<S65>/wg_p1' */
  FOpid_RL_X.wg_p1_CSTATE[1] = 0.0;

  /* InitializeConditions for Integrator: '<S65>/wg_p2' */
  FOpid_RL_X.wg_p2_CSTATE[1] = 0.0;

  /* End of SystemInitialize for SubSystem: '<S50>/Hwgw(s)' */

  /* SystemInitialize for Enabled SubSystem: '<S49>/Hqgw' */
  /* InitializeConditions for Integrator: '<S61>/qgw_p' */
  FOpid_RL_X.qgw_p_CSTATE[1] = 0.0;

  /* End of SystemInitialize for SubSystem: '<S49>/Hqgw' */

  /* SystemInitialize for Enabled SubSystem: '<S50>/Hvgw(s)' */
  /* InitializeConditions for Integrator: '<S64>/vg_p1' */
  FOpid_RL_X.vg_p1_CSTATE[1] = 0.0;

  /* InitializeConditions for Integrator: '<S64>/vgw_p2' */
  FOpid_RL_X.vgw_p2_CSTATE[1] = 0.0;

  /* End of SystemInitialize for SubSystem: '<S50>/Hvgw(s)' */

  /* SystemInitialize for Enabled SubSystem: '<S49>/Hrgw' */
  /* InitializeConditions for Integrator: '<S62>/rgw_p' */
  FOpid_RL_X.rgw_p_CSTATE[1] = 0.0;

  /* End of SystemInitialize for SubSystem: '<S49>/Hrgw' */

  /* SystemInitialize for Enabled SubSystem: '<S44>/Enabled Subsystem' */
  FOpid_RL_EnabledSubsystem_Init(&FOpid_RL_B.EnabledSubsystem);

  /* End of SystemInitialize for SubSystem: '<S44>/Enabled Subsystem' */

  /* SystemInitialize for Enabled SubSystem: '<S46>/Enabled Subsystem' */
  FOpid_R_EnabledSubsystem_e_Init(&FOpid_RL_B.EnabledSubsystem_p);

  /* End of SystemInitialize for SubSystem: '<S46>/Enabled Subsystem' */

  /* SystemInitialize for Enabled SubSystem: '<S50>/Hugw(s)' */
  /* InitializeConditions for Integrator: '<S63>/ug_p' */
  FOpid_RL_X.ug_p_CSTATE[0] = 0.0;
  FOpid_RL_X.ug_p_CSTATE[1] = 0.0;

  /* End of SystemInitialize for SubSystem: '<S50>/Hugw(s)' */

  /* SystemInitialize for Enabled SubSystem: '<S47>/Enabled Subsystem' */
  FOpid_RL_EnabledSubsystem_Init(&FOpid_RL_B.EnabledSubsystem_pt);

  /* End of SystemInitialize for SubSystem: '<S47>/Enabled Subsystem' */

  /* SystemInitialize for Enabled SubSystem: '<S45>/Enabled Subsystem' */
  FOpid_R_EnabledSubsystem_e_Init(&FOpid_RL_B.EnabledSubsystem_k);

  /* End of SystemInitialize for SubSystem: '<S45>/Enabled Subsystem' */

  /* set "at time zero" to false */
  if (rtmIsFirstInitCond((&FOpid_RL_M))) {
    rtmSetFirstInitCond((&FOpid_RL_M), 0);
  }
}

/* Model terminate function */
void FOpid_RL::terminate()
{
  /* Terminate for MATLABSystem: '<S27>/SinkBlock' */
  if (!FOpid_RL_DW.obj_i.matlabCodegenIsDeleted) {
    FOpid_RL_DW.obj_i.matlabCodegenIsDeleted = true;
    if ((FOpid_RL_DW.obj_i.isInitialized == 1) &&
        FOpid_RL_DW.obj_i.isSetupComplete) {
      Pub_FOpid_RL_548.resetPublisherPtr();//();
    }
  }

  /* End of Terminate for MATLABSystem: '<S27>/SinkBlock' */

  /* Terminate for MATLABSystem: '<S28>/SinkBlock' */
  if (!FOpid_RL_DW.obj_o.matlabCodegenIsDeleted) {
    FOpid_RL_DW.obj_o.matlabCodegenIsDeleted = true;
    if ((FOpid_RL_DW.obj_o.isInitialized == 1) &&
        FOpid_RL_DW.obj_o.isSetupComplete) {
      Pub_FOpid_RL_697.resetPublisherPtr();//();
    }
  }

  /* End of Terminate for MATLABSystem: '<S28>/SinkBlock' */

  /* Terminate for MATLABSystem: '<S29>/SinkBlock' */
  if (!FOpid_RL_DW.obj_dl.matlabCodegenIsDeleted) {
    FOpid_RL_DW.obj_dl.matlabCodegenIsDeleted = true;
    if ((FOpid_RL_DW.obj_dl.isInitialized == 1) &&
        FOpid_RL_DW.obj_dl.isSetupComplete) {
      Pub_FOpid_RL_811.resetPublisherPtr();//();
    }
  }

  /* End of Terminate for MATLABSystem: '<S29>/SinkBlock' */

  /* Terminate for MATLABSystem: '<S30>/SinkBlock' */
  if (!FOpid_RL_DW.obj_d.matlabCodegenIsDeleted) {
    FOpid_RL_DW.obj_d.matlabCodegenIsDeleted = true;
    if ((FOpid_RL_DW.obj_d.isInitialized == 1) &&
        FOpid_RL_DW.obj_d.isSetupComplete) {
      Pub_FOpid_RL_835.resetPublisherPtr();//();
    }
  }

  /* End of Terminate for MATLABSystem: '<S30>/SinkBlock' */

  /* Terminate for MATLABSystem: '<S34>/SourceBlock' */
  if (!FOpid_RL_DW.obj_m.matlabCodegenIsDeleted) {
    FOpid_RL_DW.obj_m.matlabCodegenIsDeleted = true;
    if ((FOpid_RL_DW.obj_m.isInitialized == 1) &&
        FOpid_RL_DW.obj_m.isSetupComplete) {
      Sub_FOpid_RL_435.resetSubscriberPtr();//();
    }
  }

  /* End of Terminate for MATLABSystem: '<S34>/SourceBlock' */

  /* Terminate for MATLABSystem: '<S35>/SourceBlock' */
  if (!FOpid_RL_DW.obj_k.matlabCodegenIsDeleted) {
    FOpid_RL_DW.obj_k.matlabCodegenIsDeleted = true;
    if ((FOpid_RL_DW.obj_k.isInitialized == 1) &&
        FOpid_RL_DW.obj_k.isSetupComplete) {
      Sub_FOpid_RL_377.resetSubscriberPtr();//();
    }
  }

  /* End of Terminate for MATLABSystem: '<S35>/SourceBlock' */

  /* Terminate for Atomic SubSystem: '<Root>/Call Service' */
  /* Terminate for MATLABSystem: '<S6>/ServiceCaller' */
  if (!FOpid_RL_DW.obj.matlabCodegenIsDeleted) {
    FOpid_RL_DW.obj.matlabCodegenIsDeleted = true;
    if ((FOpid_RL_DW.obj.isInitialized == 1) && FOpid_RL_DW.obj.isSetupComplete)
    {
      ServCall_FOpid_RL_326.resetSvcClientPtr();//();
    }
  }

  /* End of Terminate for MATLABSystem: '<S6>/ServiceCaller' */
  /* End of Terminate for SubSystem: '<Root>/Call Service' */

  /* Terminate for MATLABSystem: '<S44>/SourceBlock' */
  if (!FOpid_RL_DW.obj_h4.matlabCodegenIsDeleted) {
    FOpid_RL_DW.obj_h4.matlabCodegenIsDeleted = true;
    if ((FOpid_RL_DW.obj_h4.isInitialized == 1) &&
        FOpid_RL_DW.obj_h4.isSetupComplete) {
      Sub_FOpid_RL_423.resetSubscriberPtr();//();
    }
  }

  /* End of Terminate for MATLABSystem: '<S44>/SourceBlock' */

  /* Terminate for MATLABSystem: '<S46>/SourceBlock' */
  if (!FOpid_RL_DW.obj_p.matlabCodegenIsDeleted) {
    FOpid_RL_DW.obj_p.matlabCodegenIsDeleted = true;
    if ((FOpid_RL_DW.obj_p.isInitialized == 1) &&
        FOpid_RL_DW.obj_p.isSetupComplete) {
      Sub_FOpid_RL_445.resetSubscriberPtr();//();
    }
  }

  /* End of Terminate for MATLABSystem: '<S46>/SourceBlock' */

  /* Terminate for MATLABSystem: '<S47>/SourceBlock' */
  if (!FOpid_RL_DW.obj_h.matlabCodegenIsDeleted) {
    FOpid_RL_DW.obj_h.matlabCodegenIsDeleted = true;
    if ((FOpid_RL_DW.obj_h.isInitialized == 1) &&
        FOpid_RL_DW.obj_h.isSetupComplete) {
      Sub_FOpid_RL_417.resetSubscriberPtr();//();
    }
  }

  /* End of Terminate for MATLABSystem: '<S47>/SourceBlock' */

  /* Terminate for MATLABSystem: '<S45>/SourceBlock' */
  if (!FOpid_RL_DW.obj_hy.matlabCodegenIsDeleted) {
    FOpid_RL_DW.obj_hy.matlabCodegenIsDeleted = true;
    if ((FOpid_RL_DW.obj_hy.isInitialized == 1) &&
        FOpid_RL_DW.obj_hy.isSetupComplete) {
      Sub_FOpid_RL_443.resetSubscriberPtr();//();
    }
  }

  /* End of Terminate for MATLABSystem: '<S45>/SourceBlock' */
}

/* Constructor */
FOpid_RL::FOpid_RL() :
  FOpid_RL_B(),
  FOpid_RL_DW(),
  FOpid_RL_X(),
  FOpid_RL_XDis(),
  FOpid_RL_PrevZCX(),
  FOpid_RL_M()
{
  /* Currently there is no constructor body generated.*/
}

/* Destructor */
FOpid_RL::~FOpid_RL()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_FOpid_RL_T * FOpid_RL::getRTM()
{
  return (&FOpid_RL_M);
}
