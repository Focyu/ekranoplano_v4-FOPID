/*
 * FOpid_RL.h
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

#ifndef FOpid_RL_h_
#define FOpid_RL_h_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "FOpid_RL_types.h"
#include "rmw/qos_profiles.h"

extern "C"
{

#include "rt_nonfinite.h"

}

#include <string.h>

extern "C"
{

#include "rtGetInf.h"

}

extern "C"
{

#include "rtGetNaN.h"

}

#include <stddef.h>
#include "zero_crossing_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetContStateDisabled
#define rtmGetContStateDisabled(rtm)   ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
#define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
#define rtmGetContStates(rtm)          ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
#define rtmSetContStates(rtm, val)     ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
#define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
#define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetIntgData
#define rtmGetIntgData(rtm)            ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
#define rtmSetIntgData(rtm, val)       ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
#define rtmGetOdeF(rtm)                ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
#define rtmSetOdeF(rtm, val)           ((rtm)->odeF = (val))
#endif

#ifndef rtmGetOdeY
#define rtmGetOdeY(rtm)                ((rtm)->odeY)
#endif

#ifndef rtmSetOdeY
#define rtmSetOdeY(rtm, val)           ((rtm)->odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
#define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
#define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
#define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
#define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetZCCacheNeedsReset
#define rtmGetZCCacheNeedsReset(rtm)   ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
#define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
#define rtmGetdX(rtm)                  ((rtm)->derivs)
#endif

#ifndef rtmSetdX
#define rtmSetdX(rtm, val)             ((rtm)->derivs = (val))
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

#ifndef rtmGetTStart
#define rtmGetTStart(rtm)              ((rtm)->Timing.tStart)
#endif

/* Block signals for system '<Root>/MATLAB Function-ned_to_PoseStamped' */
struct B_MATLABFunctionned_to_PoseSt_T {
  uint32_T lengthOut;          /* '<Root>/MATLAB Function-ned_to_PoseStamped' */
  uint8_T stringOut[128];      /* '<Root>/MATLAB Function-ned_to_PoseStamped' */
};

/* Block signals for system '<S44>/Enabled Subsystem' */
struct B_EnabledSubsystem_FOpid_RL_T {
  SL_Bus_std_msgs_Bool In1;            /* '<S87>/In1' */
};

/* Block signals for system '<S45>/Enabled Subsystem' */
struct B_EnabledSubsystem_FOpid_RL_d_T {
  SL_Bus_std_msgs_Float64 In1;         /* '<S88>/In1' */
};

/* Block signals (default storage) */
struct B_FOpid_RL_T {
  SL_Bus_nav_msgs_Odometry BusAssignmentODOM;/* '<Root>/Bus Assignment-ODOM' */
  SL_Bus_sensor_msgs_Imu BusAssignmentIMU;/* '<Root>/Bus Assignment-IMU' */
  SL_Bus_gazebo_msgs_SetEntityStateRequest BusAssignmentMODELO;/* '<Root>/Bus Assignment-MODELO' */
  SL_Bus_geometry_msgs_PoseStamped BusAssignmentPoseStaamped;
                                      /* '<Root>/Bus Assignment-PoseStaamped' */
  SL_Bus_geometry_msgs_TwistStamped BusAssignmentTwistStamped;
                                      /* '<Root>/Bus Assignment-TwistStamped' */
  real_T IC[12];                       /* '<S33>/IC' */
  real_T x[12];                        /* '<S33>/Integrator' */
  uint8_T str_out[128];                /* '<Root>/MATLAB Function-Odometry1' */
  uint8_T str_out_e[128];              /* '<Root>/MATLAB Function-Odometry' */
  uint8_T stringOut[128];              /* '<Root>/MATLAB Function-MODELO' */
  uint8_T stringOut_n[128];            /* '<Root>/MATLAB Function-IMU2' */
  uint8_T stringOut_d[128];            /* '<Root>/MATLAB Function' */
  real_T R[9];
  real_T RotationAnglestoDirectionCo[9];
                        /* '<S33>/Rotation Angles to Direction Cosine Matrix' */
  real_T dv[9];
  char_T b_zeroDelimTopic[26];
  char_T b_zeroDelimTopic_m[25];
  char_T b_zeroDelimTopic_c[25];
  real_T wbe_b[3];
  real_T FE1_b[3];
  real_T F_b[3];
  real_T Reshape1_b[3];                /* '<S72>/Reshape1' */
  real_T Dtot[3];
  char_T b_zeroDelimTopic_k[22];
  char_T b_zeroDelimTopic_cx[22];
  char_T b_zeroDelimTopic_b[18];
  char_T b_zeroDelimTopic_p[17];
  char_T b_zeroDelimTopic_cv[17];
  char_T b_zeroDelimTopic_f[17];
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF deadline_g;
  sJ4ih70VmKcvCeguWN0mNVF deadline_g1;
  sJ4ih70VmKcvCeguWN0mNVF deadline_m;
  sJ4ih70VmKcvCeguWN0mNVF deadline_n;
  sJ4ih70VmKcvCeguWN0mNVF deadline_p;
  sJ4ih70VmKcvCeguWN0mNVF deadline_l;
  sJ4ih70VmKcvCeguWN0mNVF deadline_j;
  sJ4ih70VmKcvCeguWN0mNVF deadline_d;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF deadline_gu;
  sJ4ih70VmKcvCeguWN0mNVF lifespan_l;
  sJ4ih70VmKcvCeguWN0mNVF deadline_dh;
  real_T Product1_l[2];                /* '<S73>/Product1' */
  real_T dv1[2];
  real_T GainZ;                        /* '<Root>/Gain-Z' */
  real_T Switch3;                      /* '<Root>/Switch3' */
  real_T Sum2;                         /* '<Root>/Sum2' */
  real_T RateLimiter2;                 /* '<Root>/Rate Limiter2' */
  real_T Sum5;                         /* '<Root>/Sum5' */
  real_T Saturation_roll_sp;           /* '<Root>/Saturation_roll_sp' */
  real_T Sum4;                         /* '<Root>/Sum4' */
  real_T RateLimitertheta_sp;          /* '<Root>/Rate Limiter-theta_sp' */
  real_T Sum1;                         /* '<Root>/Sum1' */
  real_T Saturation1;                  /* '<Root>/Saturation1' */
  real_T Sum3;                         /* '<Root>/Sum3' */
  real_T Product[4];                   /* '<S59>/Product' */
  real_T Memory[3];                    /* '<S33>/Memory' */
  real_T Memory1[3];                   /* '<S33>/Memory1' */
  real_T Output;                       /* '<S39>/Output' */
  real_T SumOLA1[3];                   /* '<S33>/SumOLA1' */
  real_T SumOLA[3];                    /* '<S33>/SumOLA' */
  real_T Power;                        /* '<S33>/Product2' */
  real_T Gain3;                        /* '<S33>/Gain3' */
  real_T EnergykWh;                    /* '<S33>/Gain1' */
  real_T powerdemand;                  /* '<S33>/Divide' */
  real_T loadtorque;                   /* '<S33>/Divide1' */
  real_T Sum2_j;                       /* '<S22>/Sum2' */
  real_T Sum2_f;                       /* '<S23>/Sum2' */
  real_T Sum2_b;                       /* '<S24>/Sum2' */
  real_T Sum2_jg;                      /* '<S25>/Sum2' */
  real_T Sum2_ba;                      /* '<S26>/Sum2' */
  real_T startTime;                    /* '<S31>/startTime' */
  real_T u;                            /* '<S38>/MATLAB Function - fopid_yaw' */
  real_T u_b;                         /* '<S37>/MATLAB Function - fopid_roll' */
  real_T u_k;                       /* '<S36>/MATLAB Function - fopid_altura' */
  real_T XDOT[40];                     /* '<S33>/MATLAB Function - MODEL' */
  real_T w[2];                         /* '<S65>/w' */
  real_T w_a[2];                       /* '<S65>/w ' */
  real_T LwgV1[2];                     /* '<S65>/Lwg//V 1' */
  real_T w_g[2];                       /* '<S64>/w' */
  real_T w_e[2];                       /* '<S64>/w ' */
  real_T w1[2];                        /* '<S64>/w 1' */
  real_T w_n[2];                       /* '<S63>/w' */
  real_T w1_c[2];                      /* '<S63>/w1' */
  real_T w_d[2];                       /* '<S62>/w' */
  real_T w_e0[2];                      /* '<S61>/w' */
  real_T UnaryMinus[2];                /* '<S61>/Unary Minus' */
  real_T w_o[2];                       /* '<S60>/w' */
  real_T sigma_w[2];                   /* '<S60>/sigma_w' */
  real_T u_j;                   /* '<Root>/MATLAB Function - fopid_velocidad' */
  real_T u_c;                       /* '<Root>/MATLAB Function - fopid_pitch' */
  real_T u1;
  real_T u2;
  real_T q_aero;
  real_T Q;
  real_T CL_w_IGE;
  real_T CL_h_IGE;
  real_T CD_iw_IGE;
  real_T CD_ih_IGE;
  real_T u2_deg;
  real_T Ltot;
  real_T CQ;
  real_T Cl;
  real_T Vd1;
  real_T L_dec;
  real_T c_phi;
  real_T s_phi;
  real_T c_the;
  real_T s_the;
  real_T c_psi;
  real_T s_psi;
  real_T sina;
  real_T sinb;
  real_T sinc;
  real_T cosa;
  real_T cosb;
  real_T cosc;
  real_T FE_b;
  real_T rtb_CoordinateTransformationC_d;
  real_T rtb_CoordinateTransformationC_l;
  real_T rtb_CoordinateTransformationC_o;
  real_T FE2_b_idx_0;
  real_T FE2_b_idx_2;
  real_T Fg_b_idx_2;
  real_T Mcg_b_idx_0;
  real_T FE_b_idx_0;
  real_T FA_b_idx_0;
  real_T FA_b_idx_1;
  real_T FA_b_idx_2;
  real_T R_tmp;
  real_T R_tmp_b;
  real_T Switch2;                      /* '<Root>/Switch2' */
  SL_Bus_std_msgs_Float64 SourceBlock_o2_d;/* '<S34>/SourceBlock' */
  uint32_T bpIndex[2];
  uint32_T currentLen;                 /* '<Root>/MATLAB Function-Odometry1' */
  uint32_T receivedLen;                /* '<Root>/MATLAB Function-Odometry1' */
  uint32_T currentLen_b;               /* '<Root>/MATLAB Function-Odometry' */
  uint32_T receivedLen_b;              /* '<Root>/MATLAB Function-Odometry' */
  uint32_T lengthOut;                  /* '<Root>/MATLAB Function-MODELO' */
  uint32_T lengthOut_i;                /* '<Root>/MATLAB Function-IMU2' */
  uint32_T lengthOut_g;                /* '<Root>/MATLAB Function' */
  boolean_T Compare;                   /* '<S40>/Compare' */
  boolean_T SourceBlock_o1;            /* '<S35>/SourceBlock' */
  boolean_T SourceBlock_o1_o;          /* '<S34>/SourceBlock' */
  boolean_T SourceBlock_o1_h;          /* '<S47>/SourceBlock' */
  boolean_T SourceBlock_o1_d;          /* '<S46>/SourceBlock' */
  boolean_T SourceBlock_o1_c;          /* '<S45>/SourceBlock' */
  boolean_T SourceBlock_o1_k;          /* '<S44>/SourceBlock' */
  B_EnabledSubsystem_FOpid_RL_d_T EnabledSubsystem_a;/* '<S35>/Enabled Subsystem' */
  B_EnabledSubsystem_FOpid_RL_d_T EnabledSubsystem_b;/* '<S34>/Enabled Subsystem' */
  B_EnabledSubsystem_FOpid_RL_T EnabledSubsystem_pt;/* '<S47>/Enabled Subsystem' */
  B_EnabledSubsystem_FOpid_RL_d_T EnabledSubsystem_p;/* '<S46>/Enabled Subsystem' */
  B_EnabledSubsystem_FOpid_RL_d_T EnabledSubsystem_k;/* '<S45>/Enabled Subsystem' */
  B_EnabledSubsystem_FOpid_RL_T EnabledSubsystem;/* '<S44>/Enabled Subsystem' */
  B_MATLABFunctionned_to_PoseSt_T sf_MATLABFunctionned_to_TwistSt;
                              /* '<Root>/MATLAB Function-ned_to_TwistStamped' */
  B_MATLABFunctionned_to_PoseSt_T sf_MATLABFunctionned_to_PoseS_b;
                               /* '<Root>/MATLAB Function-ned_to_PoseStamped' */
};

/* Block states (default storage) for system '<Root>' */
struct DW_FOpid_RL_T {
  ros_slros2_internal_block_Ser_T obj; /* '<S6>/ServiceCaller' */
  ros_slros2_internal_block_Pub_T obj_d;/* '<S30>/SinkBlock' */
  ros_slros2_internal_block_Pub_T obj_dl;/* '<S29>/SinkBlock' */
  ros_slros2_internal_block_Pub_T obj_o;/* '<S28>/SinkBlock' */
  ros_slros2_internal_block_Pub_T obj_i;/* '<S27>/SinkBlock' */
  ros_slros2_internal_block_Sub_T obj_k;/* '<S35>/SourceBlock' */
  ros_slros2_internal_block_Sub_T obj_m;/* '<S34>/SourceBlock' */
  ros_slros2_internal_block_Sub_T obj_h;/* '<S47>/SourceBlock' */
  ros_slros2_internal_block_Sub_T obj_p;/* '<S46>/SourceBlock' */
  ros_slros2_internal_block_Sub_T obj_hy;/* '<S45>/SourceBlock' */
  ros_slros2_internal_block_Sub_T obj_h4;/* '<S44>/SourceBlock' */
  real_T UnitDelay3_DSTATE;            /* '<Root>/Unit Delay3' */
  real_T UnitDelay2_DSTATE;            /* '<Root>/Unit Delay2' */
  real_T Memory2_PreviousInput[12];    /* '<S33>/Memory2' */
  real_T PrevY;                        /* '<Root>/Rate Limiter2' */
  real_T PrevY_e;                      /* '<Root>/Rate Limiter3' */
  real_T PrevY_g;                      /* '<Root>/Rate Limiter-theta_sp' */
  real_T NextOutput[4];                /* '<S59>/White Noise' */
  real_T Memory_PreviousInput[3];      /* '<S33>/Memory' */
  real_T Memory1_PreviousInput[3];     /* '<S33>/Memory1' */
  real_T NextOutput_k;                 /* '<S39>/White Noise' */
  real_T e1;                           /* '<S38>/MATLAB Function - fopid_yaw' */
  real_T e2;                           /* '<S38>/MATLAB Function - fopid_yaw' */
  real_T e3;                           /* '<S38>/MATLAB Function - fopid_yaw' */
  real_T e4;                           /* '<S38>/MATLAB Function - fopid_yaw' */
  real_T e5;                           /* '<S38>/MATLAB Function - fopid_yaw' */
  real_T e6;                           /* '<S38>/MATLAB Function - fopid_yaw' */
  real_T e7;                           /* '<S38>/MATLAB Function - fopid_yaw' */
  real_T y1;                           /* '<S38>/MATLAB Function - fopid_yaw' */
  real_T y2;                           /* '<S38>/MATLAB Function - fopid_yaw' */
  real_T y3;                           /* '<S38>/MATLAB Function - fopid_yaw' */
  real_T y4;                           /* '<S38>/MATLAB Function - fopid_yaw' */
  real_T y5;                           /* '<S38>/MATLAB Function - fopid_yaw' */
  real_T y6;                           /* '<S38>/MATLAB Function - fopid_yaw' */
  real_T y7;                           /* '<S38>/MATLAB Function - fopid_yaw' */
  real_T u_prev;                       /* '<S38>/MATLAB Function - fopid_yaw' */
  real_T e1_p;                        /* '<S37>/MATLAB Function - fopid_roll' */
  real_T e2_b;                        /* '<S37>/MATLAB Function - fopid_roll' */
  real_T e3_m;                        /* '<S37>/MATLAB Function - fopid_roll' */
  real_T e4_o;                        /* '<S37>/MATLAB Function - fopid_roll' */
  real_T e5_m;                        /* '<S37>/MATLAB Function - fopid_roll' */
  real_T e6_g;                        /* '<S37>/MATLAB Function - fopid_roll' */
  real_T e7_m;                        /* '<S37>/MATLAB Function - fopid_roll' */
  real_T y1_g;                        /* '<S37>/MATLAB Function - fopid_roll' */
  real_T y2_e;                        /* '<S37>/MATLAB Function - fopid_roll' */
  real_T y3_a;                        /* '<S37>/MATLAB Function - fopid_roll' */
  real_T y4_j;                        /* '<S37>/MATLAB Function - fopid_roll' */
  real_T y5_k;                        /* '<S37>/MATLAB Function - fopid_roll' */
  real_T y6_k;                        /* '<S37>/MATLAB Function - fopid_roll' */
  real_T y7_p;                        /* '<S37>/MATLAB Function - fopid_roll' */
  real_T u_prev_e;                    /* '<S37>/MATLAB Function - fopid_roll' */
  real_T e1_f;                      /* '<S36>/MATLAB Function - fopid_altura' */
  real_T e2_m;                      /* '<S36>/MATLAB Function - fopid_altura' */
  real_T e3_n;                      /* '<S36>/MATLAB Function - fopid_altura' */
  real_T e4_j;                      /* '<S36>/MATLAB Function - fopid_altura' */
  real_T e5_c;                      /* '<S36>/MATLAB Function - fopid_altura' */
  real_T e6_m;                      /* '<S36>/MATLAB Function - fopid_altura' */
  real_T e7_i;                      /* '<S36>/MATLAB Function - fopid_altura' */
  real_T y1_p;                      /* '<S36>/MATLAB Function - fopid_altura' */
  real_T y2_c;                      /* '<S36>/MATLAB Function - fopid_altura' */
  real_T y3_b;                      /* '<S36>/MATLAB Function - fopid_altura' */
  real_T y4_b;                      /* '<S36>/MATLAB Function - fopid_altura' */
  real_T y5_c;                      /* '<S36>/MATLAB Function - fopid_altura' */
  real_T y6_d;                      /* '<S36>/MATLAB Function - fopid_altura' */
  real_T y7_o;                      /* '<S36>/MATLAB Function - fopid_altura' */
  real_T u_prev_f;                  /* '<S36>/MATLAB Function - fopid_altura' */
  real_T e1_c;                  /* '<Root>/MATLAB Function - fopid_velocidad' */
  real_T e2_j;                  /* '<Root>/MATLAB Function - fopid_velocidad' */
  real_T e3_o;                  /* '<Root>/MATLAB Function - fopid_velocidad' */
  real_T e4_os;                 /* '<Root>/MATLAB Function - fopid_velocidad' */
  real_T e5_mk;                 /* '<Root>/MATLAB Function - fopid_velocidad' */
  real_T e6_p;                  /* '<Root>/MATLAB Function - fopid_velocidad' */
  real_T e7_l;                  /* '<Root>/MATLAB Function - fopid_velocidad' */
  real_T y1_g4;                 /* '<Root>/MATLAB Function - fopid_velocidad' */
  real_T y2_d;                  /* '<Root>/MATLAB Function - fopid_velocidad' */
  real_T y3_d;                  /* '<Root>/MATLAB Function - fopid_velocidad' */
  real_T y4_f;                  /* '<Root>/MATLAB Function - fopid_velocidad' */
  real_T y5_l;                  /* '<Root>/MATLAB Function - fopid_velocidad' */
  real_T y6_a;                  /* '<Root>/MATLAB Function - fopid_velocidad' */
  real_T y7_e;                  /* '<Root>/MATLAB Function - fopid_velocidad' */
  real_T u_prev_a;              /* '<Root>/MATLAB Function - fopid_velocidad' */
  real_T e1_o;                      /* '<Root>/MATLAB Function - fopid_pitch' */
  real_T e2_h;                      /* '<Root>/MATLAB Function - fopid_pitch' */
  real_T e3_g;                      /* '<Root>/MATLAB Function - fopid_pitch' */
  real_T e4_m;                      /* '<Root>/MATLAB Function - fopid_pitch' */
  real_T e5_b;                      /* '<Root>/MATLAB Function - fopid_pitch' */
  real_T e6_h;                      /* '<Root>/MATLAB Function - fopid_pitch' */
  real_T e7_f;                      /* '<Root>/MATLAB Function - fopid_pitch' */
  real_T y1_a;                      /* '<Root>/MATLAB Function - fopid_pitch' */
  real_T y2_du;                     /* '<Root>/MATLAB Function - fopid_pitch' */
  real_T y3_h;                      /* '<Root>/MATLAB Function - fopid_pitch' */
  real_T y4_p;                      /* '<Root>/MATLAB Function - fopid_pitch' */
  real_T y5_ca;                     /* '<Root>/MATLAB Function - fopid_pitch' */
  real_T y6_f;                      /* '<Root>/MATLAB Function - fopid_pitch' */
  real_T y7_l;                      /* '<Root>/MATLAB Function - fopid_pitch' */
  real_T u_prev_fo;                 /* '<Root>/MATLAB Function - fopid_pitch' */
  uint32_T PreLookUpIndexSearchprobofexcee;
                         /* '<S66>/PreLook-Up Index Search  (prob of exceed)' */
  uint32_T PreLookUpIndexSearchaltitude_DW;
                               /* '<S66>/PreLook-Up Index Search  (altitude)' */
  uint32_T RandSeed[4];                /* '<S59>/White Noise' */
  uint32_T RandSeed_a;                 /* '<S39>/White Noise' */
  robotics_slcore_internal_bloc_T obj_c;
                             /* '<Root>/Coordinate Transformation Conversion' */
  int_T IntegratorSecondOrderLimited_MO;
                                  /* '<S22>/Integrator, Second-Order Limited' */
  int_T IntegratorSecondOrderLimited__h;
                                  /* '<S23>/Integrator, Second-Order Limited' */
  int_T IntegratorSecondOrderLimited__b;
                                  /* '<S24>/Integrator, Second-Order Limited' */
  int_T IntegratorSecondOrderLimited__o;
                                  /* '<S25>/Integrator, Second-Order Limited' */
  int_T IntegratorSecondOrderLimited_h4;
                                  /* '<S26>/Integrator, Second-Order Limited' */
  int8_T ifHeightMaxlowaltitudeelseifHei;
  /* '<S54>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
  int8_T ifHeightMaxlowaltitudeelseifH_k;
  /* '<S55>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
  boolean_T IC_FirstOutputTime;        /* '<S33>/IC' */
  boolean_T Integrator_DWORK1;         /* '<S33>/Integrator' */
  boolean_T RelayEnableFlight_Mode;    /* '<Root>/Relay-Enable-Flight' */
  boolean_T IntegratorSecondOrderLimited_DW;
                                  /* '<S22>/Integrator, Second-Order Limited' */
  boolean_T IntegratorSecondOrderLimited__k;
                                  /* '<S23>/Integrator, Second-Order Limited' */
  boolean_T IntegratorSecondOrderLimited_be;
                                  /* '<S24>/Integrator, Second-Order Limited' */
  boolean_T IntegratorSecondOrderLimited__m;
                                  /* '<S25>/Integrator, Second-Order Limited' */
  boolean_T IntegratorSecondOrderLimited__l;
                                  /* '<S26>/Integrator, Second-Order Limited' */
  boolean_T objisempty;                /* '<S35>/SourceBlock' */
  boolean_T objisempty_g;              /* '<S34>/SourceBlock' */
  boolean_T objisempty_a;              /* '<S47>/SourceBlock' */
  boolean_T objisempty_e;              /* '<S46>/SourceBlock' */
  boolean_T objisempty_l;              /* '<S45>/SourceBlock' */
  boolean_T objisempty_c;              /* '<S44>/SourceBlock' */
  boolean_T objisempty_cr;             /* '<S30>/SinkBlock' */
  boolean_T objisempty_ld;             /* '<S29>/SinkBlock' */
  boolean_T objisempty_ev;             /* '<S28>/SinkBlock' */
  boolean_T objisempty_m;              /* '<S27>/SinkBlock' */
  boolean_T objisempty_d;    /* '<Root>/Coordinate Transformation Conversion' */
  boolean_T regObj_not_empty;/* '<Root>/Coordinate Transformation Conversion' */
  boolean_T objisempty_f;              /* '<S6>/ServiceCaller' */
  e_robotics_core_internal_vali_T regObj;
                             /* '<Root>/Coordinate Transformation Conversion' */
  boolean_T Hwgws_MODE;                /* '<S50>/Hwgw(s)' */
  boolean_T Hvgws_MODE;                /* '<S50>/Hvgw(s)' */
  boolean_T Hugws_MODE;                /* '<S50>/Hugw(s)' */
  boolean_T Hrgw_MODE;                 /* '<S49>/Hrgw' */
  boolean_T Hqgw_MODE;                 /* '<S49>/Hqgw' */
  boolean_T Hpgw_MODE;                 /* '<S49>/Hpgw' */
};

/* Continuous states (default storage) */
struct X_FOpid_RL_T {
  real_T Integrator_CSTATE[12];        /* '<S33>/Integrator' */
  real_T TransferFcn1_CSTATE;          /* '<S33>/Transfer Fcn1' */
  real_T TransferFcn_CSTATE[2];        /* '<S33>/Transfer Fcn' */
  real_T Integrator1_CSTATE;           /* '<S33>/Integrator1' */
  real_T IntegratorSecondOrderLimited_CS[2];
                                  /* '<S22>/Integrator, Second-Order Limited' */
  real_T IntegratorSecondOrderLimited__n[2];
                                  /* '<S23>/Integrator, Second-Order Limited' */
  real_T IntegratorSecondOrderLimited__a[2];
                                  /* '<S24>/Integrator, Second-Order Limited' */
  real_T IntegratorSecondOrderLimited__i[2];
                                  /* '<S25>/Integrator, Second-Order Limited' */
  real_T IntegratorSecondOrderLimited__f[2];
                                  /* '<S26>/Integrator, Second-Order Limited' */
  real_T wg_p1_CSTATE[2];              /* '<S65>/wg_p1' */
  real_T wg_p2_CSTATE[2];              /* '<S65>/wg_p2' */
  real_T vg_p1_CSTATE[2];              /* '<S64>/vg_p1' */
  real_T vgw_p2_CSTATE[2];             /* '<S64>/vgw_p2' */
  real_T ug_p_CSTATE[2];               /* '<S63>/ug_p' */
  real_T rgw_p_CSTATE[2];              /* '<S62>/rgw_p' */
  real_T qgw_p_CSTATE[2];              /* '<S61>/qgw_p' */
  real_T pgw_p_CSTATE[2];              /* '<S60>/pgw_p' */
};

/* State derivatives (default storage) */
struct XDot_FOpid_RL_T {
  real_T Integrator_CSTATE[12];        /* '<S33>/Integrator' */
  real_T TransferFcn1_CSTATE;          /* '<S33>/Transfer Fcn1' */
  real_T TransferFcn_CSTATE[2];        /* '<S33>/Transfer Fcn' */
  real_T Integrator1_CSTATE;           /* '<S33>/Integrator1' */
  real_T IntegratorSecondOrderLimited_CS[2];
                                  /* '<S22>/Integrator, Second-Order Limited' */
  real_T IntegratorSecondOrderLimited__n[2];
                                  /* '<S23>/Integrator, Second-Order Limited' */
  real_T IntegratorSecondOrderLimited__a[2];
                                  /* '<S24>/Integrator, Second-Order Limited' */
  real_T IntegratorSecondOrderLimited__i[2];
                                  /* '<S25>/Integrator, Second-Order Limited' */
  real_T IntegratorSecondOrderLimited__f[2];
                                  /* '<S26>/Integrator, Second-Order Limited' */
  real_T wg_p1_CSTATE[2];              /* '<S65>/wg_p1' */
  real_T wg_p2_CSTATE[2];              /* '<S65>/wg_p2' */
  real_T vg_p1_CSTATE[2];              /* '<S64>/vg_p1' */
  real_T vgw_p2_CSTATE[2];             /* '<S64>/vgw_p2' */
  real_T ug_p_CSTATE[2];               /* '<S63>/ug_p' */
  real_T rgw_p_CSTATE[2];              /* '<S62>/rgw_p' */
  real_T qgw_p_CSTATE[2];              /* '<S61>/qgw_p' */
  real_T pgw_p_CSTATE[2];              /* '<S60>/pgw_p' */
};

/* State disabled  */
struct XDis_FOpid_RL_T {
  boolean_T Integrator_CSTATE[12];     /* '<S33>/Integrator' */
  boolean_T TransferFcn1_CSTATE;       /* '<S33>/Transfer Fcn1' */
  boolean_T TransferFcn_CSTATE[2];     /* '<S33>/Transfer Fcn' */
  boolean_T Integrator1_CSTATE;        /* '<S33>/Integrator1' */
  boolean_T IntegratorSecondOrderLimited_CS[2];
                                  /* '<S22>/Integrator, Second-Order Limited' */
  boolean_T IntegratorSecondOrderLimited__n[2];
                                  /* '<S23>/Integrator, Second-Order Limited' */
  boolean_T IntegratorSecondOrderLimited__a[2];
                                  /* '<S24>/Integrator, Second-Order Limited' */
  boolean_T IntegratorSecondOrderLimited__i[2];
                                  /* '<S25>/Integrator, Second-Order Limited' */
  boolean_T IntegratorSecondOrderLimited__f[2];
                                  /* '<S26>/Integrator, Second-Order Limited' */
  boolean_T wg_p1_CSTATE[2];           /* '<S65>/wg_p1' */
  boolean_T wg_p2_CSTATE[2];           /* '<S65>/wg_p2' */
  boolean_T vg_p1_CSTATE[2];           /* '<S64>/vg_p1' */
  boolean_T vgw_p2_CSTATE[2];          /* '<S64>/vgw_p2' */
  boolean_T ug_p_CSTATE[2];            /* '<S63>/ug_p' */
  boolean_T rgw_p_CSTATE[2];           /* '<S62>/rgw_p' */
  boolean_T qgw_p_CSTATE[2];           /* '<S61>/qgw_p' */
  boolean_T pgw_p_CSTATE[2];           /* '<S60>/pgw_p' */
};

/* Zero-crossing (trigger) state */
struct PrevZCX_FOpid_RL_T {
  ZCSigState Integrator_Reset_ZCE;     /* '<S33>/Integrator' */
};

/* Invariant block signals (default storage) */
struct ConstB_FOpid_RL_T {
  real_T UnitConversion;               /* '<S48>/Unit Conversion' */
  real_T UnitConversion_k;             /* '<S58>/Unit Conversion' */
  real_T sigma_wg;                     /* '<S67>/sigma_wg ' */
  real_T UnitConversion_n;             /* '<S52>/Unit Conversion' */
  real_T UnitConversion_c;             /* '<S86>/Unit Conversion' */
  real_T PreLookUpIndexSearchprobofe;
                         /* '<S66>/PreLook-Up Index Search  (prob of exceed)' */
  real_T constBlockForifHeightMaxlow;
  real_T constBlockForifHeightMaxl_e;
  real_T constBlockForifHeightMaxl_l;
  real_T constBlockForifHeightMax_eh;
  real_T Sqrt[4];                      /* '<S59>/Sqrt' */
  real_T Sqrt1;                        /* '<S59>/Sqrt1' */
  real_T Divide[4];                    /* '<S59>/Divide' */
  real_T motorspeed;                   /* '<S33>/Gain2' */
  real_T Demandlimits;                 /* '<S22>/Demand limits' */
  real_T Demandlimits_c;               /* '<S23>/Demand limits' */
  real_T Demandlimits_n;               /* '<S24>/Demand limits' */
  real_T Demandlimits_g;               /* '<S25>/Demand limits' */
  real_T Demandlimits_p;               /* '<S26>/Demand limits' */
  real_T Sum;                          /* '<S76>/Sum' */
  real_T Sum_a;                        /* '<S68>/Sum' */
  real_T sqrt_a;                       /* '<S65>/sqrt' */
  real_T w4;                           /* '<S60>/w4' */
  real_T u16;                          /* '<S60>/u^1//6' */
  uint32_T PreLookUpIndexSearchprobo_g;
                         /* '<S66>/PreLook-Up Index Search  (prob of exceed)' */
};

#ifndef ODE4_INTG
#define ODE4_INTG

/* ODE4 Integration Data */
struct ODE4_IntgData {
  real_T *y;                           /* output */
  real_T *f[4];                        /* derivatives */
};

#endif

/* Constant parameters (default storage) */
struct ConstP_FOpid_RL_T {
  /* Pooled Parameter (Expression: x_nom)
   * Referenced by:
   *   '<S33>/IC'
   *   '<S33>/Memory2'
   */
  real_T pooled14[12];

  /* Expression: rep_seq_y
   * Referenced by: '<S32>/Look-Up Table1'
   */
  real_T LookUpTable1_tableData[17];

  /* Expression: rep_seq_t - min(rep_seq_t)
   * Referenced by: '<S32>/Look-Up Table1'
   */
  real_T LookUpTable1_bp01Data[17];

  /* Expression: h_vec
   * Referenced by: '<S66>/PreLook-Up Index Search  (altitude)'
   */
  real_T PreLookUpIndexSearchaltitude_Br[12];

  /* Expression: sigma_vec'
   * Referenced by: '<S66>/Medium//High Altitude Intensity'
   */
  real_T MediumHighAltitudeIntensity_Tab[84];

  /* Computed Parameter: MediumHighAltitudeIntensity_max
   * Referenced by: '<S66>/Medium//High Altitude Intensity'
   */
  uint32_T MediumHighAltitudeIntensity_max[2];
};

/* Real-time Model Data Structure */
struct tag_RTM_FOpid_RL_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_FOpid_RL_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_FOpid_RL_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[42];
  real_T odeF[4][42];
  ODE4_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    boolean_T firstInitCondFlag;
    struct {
      uint8_T TID[2];
    } TaskCounters;

    time_T tStart;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

extern const ConstB_FOpid_RL_T FOpid_RL_ConstB;/* constant block i/o */

/* Constant parameters (default storage) */
extern const ConstP_FOpid_RL_T FOpid_RL_ConstP;

/* Class declaration for model FOpid_RL */
class FOpid_RL
{
  /* public data and function members */
 public:
  /* Real-Time Model get method */
  RT_MODEL_FOpid_RL_T * getRTM();
  void ModelPrevZCStateInit();

  /* model start function */
  void start();

  /* Initial conditions function */
  void initialize();

  /* model step function */
  void step();

  /* model terminate function */
  void terminate();

  /* Constructor */
  FOpid_RL();

  /* Destructor */
  ~FOpid_RL();

  /* private data and function members */
 private:
  /* Block signals */
  B_FOpid_RL_T FOpid_RL_B;

  /* Block states */
  DW_FOpid_RL_T FOpid_RL_DW;

  /* Block continuous states */
  X_FOpid_RL_T FOpid_RL_X;

  /* Block Continuous state disabled vector */
  XDis_FOpid_RL_T FOpid_RL_XDis;

  /* Triggered events */
  PrevZCX_FOpid_RL_T FOpid_RL_PrevZCX;

  /* private member function(s) for subsystem '<Root>/MATLAB Function-ned_to_PoseStamped'*/
  static void MATLABFunctionned_to_PoseStampe(B_MATLABFunctionned_to_PoseSt_T
    *localB);

  /* private member function(s) for subsystem '<S44>/Enabled Subsystem'*/
  static void FOpid_RL_EnabledSubsystem_Init(B_EnabledSubsystem_FOpid_RL_T
    *localB);
  static void FOpid_RL_EnabledSubsystem(boolean_T rtu_Enable, const
    SL_Bus_std_msgs_Bool *rtu_In1, B_EnabledSubsystem_FOpid_RL_T *localB);

  /* private member function(s) for subsystem '<S45>/Enabled Subsystem'*/
  static void FOpid_R_EnabledSubsystem_e_Init(B_EnabledSubsystem_FOpid_RL_d_T
    *localB);
  static void FOpid_RL_EnabledSubsystem_k(boolean_T rtu_Enable, const
    SL_Bus_std_msgs_Float64 *rtu_In1, B_EnabledSubsystem_FOpid_RL_d_T *localB);

  /* private member function(s) for subsystem '<Root>'*/
  void FOpid_RL_Publisher_setupImpl(const ros_slros2_internal_block_Pub_T *obj);
  rmw_qos_profile_t FO_ROS2PubSubBase_setQOSProfile(rmw_qos_profile_t rmwProfile,
    real_T qosDepth, real_T qosDeadline, real_T qosLifespan, real_T
    qosLeaseDuration, boolean_T qosAvoidROSNamespaceConventions);
  void FOpid_RL_Publisher_setupImpl_b(const ros_slros2_internal_block_Pub_T *obj);
  void FOpid_RL_Publisher_setupImpl_bf(const ros_slros2_internal_block_Pub_T
    *obj);
  void FOpid_Subscriber_setupImpl_bfq4(const ros_slros2_internal_block_Sub_T
    *obj);
  void FOpi_Subscriber_setupImpl_bfq4p(const ros_slros2_internal_block_Sub_T
    *obj);
  void FOpid_R_ServiceCaller_setupImpl(ros_slros2_internal_block_Ser_T *obj);
  void FOpid_RL_Subscriber_setupImpl(const ros_slros2_internal_block_Sub_T *obj);
  void FOpid_R_Subscriber_setupImpl_bf(const ros_slros2_internal_block_Sub_T
    *obj);
  void FOpid__Subscriber_setupImpl_bfq(const ros_slros2_internal_block_Sub_T
    *obj);
  void FOpid_RL_Subscriber_setupImpl_b(const ros_slros2_internal_block_Sub_T
    *obj);

  /* Global mass matrix */

  /* Continuous states update member function*/
  void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si );

  /* Derivatives member function */
  void FOpid_RL_derivatives();

  /* Real-Time Model */
  RT_MODEL_FOpid_RL_T FOpid_RL_M;
};

extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Display' : Unused code path elimination
 * Block '<S33>/Gain4' : Unused code path elimination
 * Block '<S44>/OnNewReqCall' : Unused code path elimination
 * Block '<S45>/OnNewReqCall' : Unused code path elimination
 * Block '<S46>/OnNewReqCall' : Unused code path elimination
 * Block '<S47>/OnNewReqCall' : Unused code path elimination
 * Block '<S34>/OnNewReqCall' : Unused code path elimination
 * Block '<S35>/OnNewReqCall' : Unused code path elimination
 * Block '<Root>/Gain1' : Eliminated nontunable gain of 1
 * Block '<Root>/Gain5' : Eliminated nontunable gain of 1
 * Block '<Root>/Manual Switch' : Eliminated due to constant selection input
 * Block '<Root>/Manual Switch1' : Eliminated due to constant selection input
 * Block '<S22>/wn^2' : Eliminated nontunable gain of 1
 * Block '<S23>/wn^2' : Eliminated nontunable gain of 1
 * Block '<S24>/wn^2' : Eliminated nontunable gain of 1
 * Block '<S25>/wn^2' : Eliminated nontunable gain of 1
 * Block '<S26>/wn^2' : Eliminated nontunable gain of 1
 * Block '<S31>/Output' : Eliminate redundant signal conversion block
 * Block '<S32>/Output' : Eliminate redundant signal conversion block
 * Block '<S41>/Cast' : Eliminate redundant data type conversion
 * Block '<S41>/Cast To Double' : Eliminate redundant data type conversion
 * Block '<S41>/Cast To Double1' : Eliminate redundant data type conversion
 * Block '<S41>/Cast To Double2' : Eliminate redundant data type conversion
 * Block '<S41>/Cast To Double3' : Eliminate redundant data type conversion
 * Block '<S41>/Cast To Double4' : Eliminate redundant data type conversion
 * Block '<Root>/Constant_U' : Unused code path elimination
 * Block '<S31>/Clock' : Unused code path elimination
 * Block '<S31>/Constant' : Unused code path elimination
 * Block '<S31>/Look-Up Table1' : Unused code path elimination
 * Block '<S31>/Math Function' : Unused code path elimination
 * Block '<S31>/Sum' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'FOpid_RL'
 * '<S1>'   : 'FOpid_RL/Blank Message'
 * '<S2>'   : 'FOpid_RL/Blank Message1'
 * '<S3>'   : 'FOpid_RL/Blank Message2'
 * '<S4>'   : 'FOpid_RL/Blank Message3'
 * '<S5>'   : 'FOpid_RL/Blank Message4'
 * '<S6>'   : 'FOpid_RL/Call Service'
 * '<S7>'   : 'FOpid_RL/MATLAB Function'
 * '<S8>'   : 'FOpid_RL/MATLAB Function - fopid_pitch'
 * '<S9>'   : 'FOpid_RL/MATLAB Function - fopid_velocidad'
 * '<S10>'  : 'FOpid_RL/MATLAB Function-IMU2'
 * '<S11>'  : 'FOpid_RL/MATLAB Function-MODELO'
 * '<S12>'  : 'FOpid_RL/MATLAB Function-Odometry'
 * '<S13>'  : 'FOpid_RL/MATLAB Function-Odometry1'
 * '<S14>'  : 'FOpid_RL/MATLAB Function-clocl'
 * '<S15>'  : 'FOpid_RL/MATLAB Function-ned_to_PoseStaamped'
 * '<S16>'  : 'FOpid_RL/MATLAB Function-ned_to_PoseStamped'
 * '<S17>'  : 'FOpid_RL/MATLAB Function-ned_to_TwistStamped'
 * '<S18>'  : 'FOpid_RL/MATLAB Function-ned_to_gazebo'
 * '<S19>'  : 'FOpid_RL/MATLAB Function-ned_to_imu'
 * '<S20>'  : 'FOpid_RL/MATLAB Function-ned_to_odometry'
 * '<S21>'  : 'FOpid_RL/MATLAB Function2'
 * '<S22>'  : 'FOpid_RL/Nonlinear Second-Order Actuator'
 * '<S23>'  : 'FOpid_RL/Nonlinear Second-Order Actuator1'
 * '<S24>'  : 'FOpid_RL/Nonlinear Second-Order Actuator2'
 * '<S25>'  : 'FOpid_RL/Nonlinear Second-Order Actuator3'
 * '<S26>'  : 'FOpid_RL/Nonlinear Second-Order Actuator4'
 * '<S27>'  : 'FOpid_RL/Publish'
 * '<S28>'  : 'FOpid_RL/Publish1'
 * '<S29>'  : 'FOpid_RL/Publish2'
 * '<S30>'  : 'FOpid_RL/Publish3'
 * '<S31>'  : 'FOpid_RL/Repeating Sequence'
 * '<S32>'  : 'FOpid_RL/Repeating Sequence1'
 * '<S33>'  : 'FOpid_RL/SUBSYSTEM_MODEL'
 * '<S34>'  : 'FOpid_RL/Subscribe-ALTURA'
 * '<S35>'  : 'FOpid_RL/Subscribe-YAW'
 * '<S36>'  : 'FOpid_RL/Subsystem1'
 * '<S37>'  : 'FOpid_RL/Subsystem2'
 * '<S38>'  : 'FOpid_RL/Subsystem3'
 * '<S39>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Band-Limited White Noise'
 * '<S40>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Compare To Constant'
 * '<S41>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))'
 * '<S42>'  : 'FOpid_RL/SUBSYSTEM_MODEL/MATLAB Function - MODEL'
 * '<S43>'  : 'FOpid_RL/SUBSYSTEM_MODEL/MATLAB Function-reset'
 * '<S44>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Subscribe1_TURBULENCIA1'
 * '<S45>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Subscribe_HEAVE'
 * '<S46>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Subscribe_RATE'
 * '<S47>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Subscribe_TURBULENCIA'
 * '<S48>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Angle Conversion'
 * '<S49>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Filters on angular rates'
 * '<S50>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Filters on velocities'
 * '<S51>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Length Conversion'
 * '<S52>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Length Conversion1'
 * '<S53>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/RMS turbulence  intensities'
 * '<S54>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates'
 * '<S55>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities'
 * '<S56>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Turbulence scale lengths'
 * '<S57>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Velocity Conversion'
 * '<S58>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Velocity Conversion2'
 * '<S59>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/White Noise'
 * '<S60>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Filters on angular rates/Hpgw'
 * '<S61>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Filters on angular rates/Hqgw'
 * '<S62>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Filters on angular rates/Hrgw'
 * '<S63>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Filters on velocities/Hugw(s)'
 * '<S64>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Filters on velocities/Hvgw(s)'
 * '<S65>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Filters on velocities/Hwgw(s)'
 * '<S66>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/RMS turbulence  intensities/High Altitude Intensity'
 * '<S67>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/RMS turbulence  intensities/Low Altitude Intensity'
 * '<S68>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates/Interpolate  rates'
 * '<S69>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates/Low altitude  rates'
 * '<S70>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates/Medium//High  altitude rates'
 * '<S71>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates/Merge Subsystems'
 * '<S72>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates/Interpolate  rates/wind to body transformation'
 * '<S73>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates/Interpolate  rates/wind to body transformation/convert to earth coords'
 * '<S74>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates/Low altitude  rates/wind to body transformation'
 * '<S75>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates/Low altitude  rates/wind to body transformation/convert to earth coords'
 * '<S76>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities/Interpolate  velocities'
 * '<S77>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities/Low altitude  velocities'
 * '<S78>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities/Medium//High  altitude velocities'
 * '<S79>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities/Merge Subsystems'
 * '<S80>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities/Interpolate  velocities/wind to body transformation'
 * '<S81>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities/Interpolate  velocities/wind to body transformation/convert to earth coords'
 * '<S82>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities/Low altitude  velocities/wind to body transformation'
 * '<S83>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities/Low altitude  velocities/wind to body transformation/convert to earth coords'
 * '<S84>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Turbulence scale lengths/Low altitude scale length'
 * '<S85>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Turbulence scale lengths/Medium//High altitude scale length'
 * '<S86>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Turbulence scale lengths/Medium//High altitude scale length/Length Conversion'
 * '<S87>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Subscribe1_TURBULENCIA1/Enabled Subsystem'
 * '<S88>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Subscribe_HEAVE/Enabled Subsystem'
 * '<S89>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Subscribe_RATE/Enabled Subsystem'
 * '<S90>'  : 'FOpid_RL/SUBSYSTEM_MODEL/Subscribe_TURBULENCIA/Enabled Subsystem'
 * '<S91>'  : 'FOpid_RL/Subscribe-ALTURA/Enabled Subsystem'
 * '<S92>'  : 'FOpid_RL/Subscribe-YAW/Enabled Subsystem'
 * '<S93>'  : 'FOpid_RL/Subsystem1/MATLAB Function - fopid_altura'
 * '<S94>'  : 'FOpid_RL/Subsystem2/MATLAB Function - fopid_roll'
 * '<S95>'  : 'FOpid_RL/Subsystem3/MATLAB Function - fopid_yaw'
 */
#endif                                 /* FOpid_RL_h_ */
