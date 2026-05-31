/*
 * FOpid_control_V4.h
 *
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 *
 * Code generation for model "FOpid_control_V4".
 *
 * Model version              : 13.15
 * Simulink Coder version : 26.1 (R2026a) 20-Nov-2025
 * C++ source code generated on : Sun May 31 11:11:45 2026
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef FOPID_CONTROL_V4_H_
#define FOPID_CONTROL_V4_H_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "FOpid_control_V4_types.h"
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

/* Block signals for system '<S38>/Enabled Subsystem' */
struct B_EnabledSubsystem_FOpid_cont_T {
  SL_Bus_std_msgs_Bool In1;            /* '<S81>/In1' */
};

/* Block signals for system '<S39>/Enabled Subsystem' */
struct B_EnabledSubsystem_FOpid_co_d_T {
  SL_Bus_std_msgs_Float64 In1;         /* '<S82>/In1' */
};

/* Block signals (default storage) */
struct B_FOpid_control_V4_T {
  SL_Bus_nav_msgs_Odometry BusAssignmentODOM;/* '<Root>/Bus Assignment-ODOM' */
  SL_Bus_sensor_msgs_Imu BusAssignmentIMU;/* '<Root>/Bus Assignment-IMU' */
  SL_Bus_gazebo_msgs_SetEntityStateRequest BusAssignmentMODELO;/* '<Root>/Bus Assignment-MODELO' */
  SL_Bus_geometry_msgs_PoseStamped BusAssignmentPoseStaamped;
                                      /* '<Root>/Bus Assignment-PoseStaamped' */
  SL_Bus_geometry_msgs_TwistStamped BusAssignmentTwistStamped;
                                      /* '<Root>/Bus Assignment-TwistStamped' */
  real_T IC[12];                       /* '<S30>/IC' */
  real_T x[12];                        /* '<S30>/Integrator' */
  real_T R[9];
  real_T RotationAnglestoDirectionCo[9];
                        /* '<S30>/Rotation Angles to Direction Cosine Matrix' */
  real_T dv[9];
  char_T b_zeroDelimTopic[26];
  char_T b_zeroDelimTopic_m[25];
  char_T b_zeroDelimTopic_c[25];
  real_T SumOLA1[3];                   /* '<S30>/SumOLA1' */
  real_T XDOT[40];                     /* '<S30>/MATLAB Function - MODEL' */
  real_T wbe_b[3];
  real_T FE1_b[3];
  real_T F_b[3];
  real_T Product_l[3];                 /* '<S74>/Product' */
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
  real_T w[2];                         /* '<S59>/w' */
  real_T w_a[2];                       /* '<S59>/w ' */
  real_T LwgV1[2];                     /* '<S59>/Lwg//V 1' */
  real_T w_g[2];                       /* '<S58>/w' */
  real_T w_e[2];                       /* '<S58>/w ' */
  real_T w1[2];                        /* '<S58>/w 1' */
  real_T w_n[2];                       /* '<S57>/w' */
  real_T w1_c[2];                      /* '<S57>/w1' */
  real_T w_d[2];                       /* '<S56>/w' */
  real_T w_e0[2];                      /* '<S55>/w' */
  real_T UnaryMinus[2];                /* '<S55>/Unary Minus' */
  real_T w_o[2];                       /* '<S54>/w' */
  real_T sigma_w[2];                   /* '<S54>/sigma_w' */
  real_T Lv[2];                        /* '<S50>/Lv' */
  real_T dv1[2];
  real_T GainZ;                        /* '<Root>/Gain-Z' */
  real_T Switch3;                      /* '<Root>/Switch3' */
  real_T Sum2;                         /* '<Root>/Sum2' */
  real_T Switch2;                      /* '<Root>/Switch2' */
  real_T Sum5;                         /* '<Root>/Sum5' */
  real_T Saturation_roll_sp;           /* '<Root>/Saturation_roll_sp' */
  real_T Sum4;                         /* '<Root>/Sum4' */
  real_T RateLimitertheta_sp;          /* '<Root>/Rate Limiter-theta_sp' */
  real_T Sum1;                         /* '<Root>/Sum1' */
  real_T Saturation1;                  /* '<Root>/Saturation1' */
  real_T Sum3;                         /* '<Root>/Sum3' */
  real_T Memory[3];                    /* '<S30>/Memory' */
  real_T Memory1[3];                   /* '<S30>/Memory1' */
  real_T Product[4];                   /* '<S53>/Product' */
  real_T Switch[3];                    /* '<S30>/Switch' */
  real_T Switch1[3];                   /* '<S30>/Switch1' */
  real_T Switch2_i;                    /* '<S30>/Switch2' */
  real_T Output;                       /* '<S33>/Output' */
  real_T Switch3_l;                    /* '<S30>/Switch3' */
  real_T Power;                        /* '<S30>/Product2' */
  real_T Gain3;                        /* '<S30>/Gain3' */
  real_T EnergykWh;                    /* '<S30>/Gain1' */
  real_T powerdemand;                  /* '<S30>/Divide' */
  real_T loadtorque;                   /* '<S30>/Divide1' */
  real_T SumOLA[3];                    /* '<S30>/SumOLA' */
  real_T u;                           /* '<Root>/MATLAB Function - fopid_yaw' */
  real_T u_b;                   /* '<Root>/MATLAB Function - fopid_velocidad' */
  real_T u_d;                        /* '<Root>/MATLAB Function - fopid_roll' */
  real_T u_o;                       /* '<Root>/MATLAB Function - fopid_pitch' */
  real_T u1;
  real_T u2;
  real_T q_aero;
  real_T Q;
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
  real_T u_dy;                     /* '<Root>/MATLAB Function - fopid_altura' */
  real_T FE_b;
  real_T Mcg_b_idx_0;
  real_T FE2_b_idx_0;
  real_T FE2_b_idx_2;
  real_T Fg_b_idx_2;
  real_T rtb_CoordinateTransformationC_l;
  real_T rtb_CoordinateTransformationC_o;
  real_T rtb_CoordinateTransformationC_b;
  real_T rtb_CoordinateTransformationC_n;
  real_T FE_b_idx_0;
  real_T FA_b_idx_0;
  real_T FA_b_idx_1;
  real_T FA_b_idx_2;
  real_T R_tmp;
  real_T R_tmp_b;
  SL_Bus_std_msgs_Float64 SourceBlock_o2_k;/* '<S40>/SourceBlock' */
  SL_Bus_std_msgs_Float64 SourceBlock_o2_p;/* '<S39>/SourceBlock' */
  SL_Bus_std_msgs_Float64 SourceBlock_o2;/* '<S32>/SourceBlock' */
  uint32_T bpIndex[2];
  uint32_T currentLen;                 /* '<Root>/MATLAB Function-Odometry1' */
  uint32_T receivedLen;                /* '<Root>/MATLAB Function-Odometry1' */
  uint32_T currentLen_l;               /* '<Root>/MATLAB Function-Odometry' */
  uint32_T receivedLen_b;              /* '<Root>/MATLAB Function-Odometry' */
  uint32_T lengthOut;                  /* '<Root>/MATLAB Function-MODELO' */
  uint32_T lengthOut_o;                /* '<Root>/MATLAB Function-IMU2' */
  uint32_T lengthOut_l;                /* '<Root>/MATLAB Function' */
  uint8_T str_out[128];                /* '<Root>/MATLAB Function-Odometry1' */
  uint8_T str_out_c[128];              /* '<Root>/MATLAB Function-Odometry' */
  uint8_T stringOut[128];              /* '<Root>/MATLAB Function-MODELO' */
  uint8_T stringOut_c[128];            /* '<Root>/MATLAB Function-IMU2' */
  uint8_T stringOut_b[128];            /* '<Root>/MATLAB Function' */
  boolean_T Compare;                   /* '<S34>/Compare' */
  boolean_T SourceBlock_o1;            /* '<S32>/SourceBlock' */
  boolean_T SourceBlock_o1_o;          /* '<S31>/SourceBlock' */
  boolean_T SourceBlock_o1_h;          /* '<S41>/SourceBlock' */
  boolean_T SourceBlock_o1_d;          /* '<S40>/SourceBlock' */
  boolean_T SourceBlock_o1_c;          /* '<S39>/SourceBlock' */
  boolean_T SourceBlock_o1_k;          /* '<S38>/SourceBlock' */
  B_EnabledSubsystem_FOpid_co_d_T EnabledSubsystem_a;/* '<S32>/Enabled Subsystem' */
  B_EnabledSubsystem_FOpid_co_d_T EnabledSubsystem_b;/* '<S31>/Enabled Subsystem' */
  B_EnabledSubsystem_FOpid_cont_T EnabledSubsystem_pt;/* '<S41>/Enabled Subsystem' */
  B_EnabledSubsystem_FOpid_co_d_T EnabledSubsystem_p;/* '<S40>/Enabled Subsystem' */
  B_EnabledSubsystem_FOpid_co_d_T EnabledSubsystem_k;/* '<S39>/Enabled Subsystem' */
  B_EnabledSubsystem_FOpid_cont_T EnabledSubsystem;/* '<S38>/Enabled Subsystem' */
  B_MATLABFunctionned_to_PoseSt_T sf_MATLABFunctionned_to_TwistSt;
                              /* '<Root>/MATLAB Function-ned_to_TwistStamped' */
  B_MATLABFunctionned_to_PoseSt_T sf_MATLABFunctionned_to_PoseS_b;
                               /* '<Root>/MATLAB Function-ned_to_PoseStamped' */
};

/* Block states (default storage) for system '<Root>' */
struct DW_FOpid_control_V4_T {
  ros_slros2_internal_block_Ser_T obj; /* '<S6>/ServiceCaller' */
  ros_slros2_internal_block_Pub_T obj_d;/* '<S28>/SinkBlock' */
  ros_slros2_internal_block_Pub_T obj_dl;/* '<S27>/SinkBlock' */
  ros_slros2_internal_block_Pub_T obj_o;/* '<S26>/SinkBlock' */
  ros_slros2_internal_block_Pub_T obj_i;/* '<S25>/SinkBlock' */
  ros_slros2_internal_block_Sub_T obj_k;/* '<S32>/SourceBlock' */
  ros_slros2_internal_block_Sub_T obj_m;/* '<S31>/SourceBlock' */
  ros_slros2_internal_block_Sub_T obj_h;/* '<S41>/SourceBlock' */
  ros_slros2_internal_block_Sub_T obj_p;/* '<S40>/SourceBlock' */
  ros_slros2_internal_block_Sub_T obj_hy;/* '<S39>/SourceBlock' */
  ros_slros2_internal_block_Sub_T obj_h4;/* '<S38>/SourceBlock' */
  real_T UnitDelay3_DSTATE;            /* '<Root>/Unit Delay3' */
  real_T UnitDelay2_DSTATE;            /* '<Root>/Unit Delay2' */
  real_T Memory2_PreviousInput[12];    /* '<S30>/Memory2' */
  real_T PrevY;                        /* '<Root>/Rate Limiter-theta_sp' */
  real_T Memory_PreviousInput[3];      /* '<S30>/Memory' */
  real_T Memory1_PreviousInput[3];     /* '<S30>/Memory1' */
  real_T NextOutput[4];                /* '<S53>/White Noise' */
  real_T NextOutput_k;                 /* '<S33>/White Noise' */
  real_T e1;                          /* '<Root>/MATLAB Function - fopid_yaw' */
  real_T e2;                          /* '<Root>/MATLAB Function - fopid_yaw' */
  real_T e3;                          /* '<Root>/MATLAB Function - fopid_yaw' */
  real_T e4;                          /* '<Root>/MATLAB Function - fopid_yaw' */
  real_T e5;                          /* '<Root>/MATLAB Function - fopid_yaw' */
  real_T y1;                          /* '<Root>/MATLAB Function - fopid_yaw' */
  real_T y2;                          /* '<Root>/MATLAB Function - fopid_yaw' */
  real_T y3;                          /* '<Root>/MATLAB Function - fopid_yaw' */
  real_T y4;                          /* '<Root>/MATLAB Function - fopid_yaw' */
  real_T y5;                          /* '<Root>/MATLAB Function - fopid_yaw' */
  real_T u1;                          /* '<Root>/MATLAB Function - fopid_yaw' */
  real_T e1_o;                  /* '<Root>/MATLAB Function - fopid_velocidad' */
  real_T e2_k;                  /* '<Root>/MATLAB Function - fopid_velocidad' */
  real_T e3_i;                  /* '<Root>/MATLAB Function - fopid_velocidad' */
  real_T e4_m;                  /* '<Root>/MATLAB Function - fopid_velocidad' */
  real_T e5_m;                  /* '<Root>/MATLAB Function - fopid_velocidad' */
  real_T y1_f;                  /* '<Root>/MATLAB Function - fopid_velocidad' */
  real_T y2_n;                  /* '<Root>/MATLAB Function - fopid_velocidad' */
  real_T y3_p;                  /* '<Root>/MATLAB Function - fopid_velocidad' */
  real_T y4_b;                  /* '<Root>/MATLAB Function - fopid_velocidad' */
  real_T y5_k;                  /* '<Root>/MATLAB Function - fopid_velocidad' */
  real_T u1_m;                  /* '<Root>/MATLAB Function - fopid_velocidad' */
  real_T e1_p;                       /* '<Root>/MATLAB Function - fopid_roll' */
  real_T e2_g;                       /* '<Root>/MATLAB Function - fopid_roll' */
  real_T e3_p;                       /* '<Root>/MATLAB Function - fopid_roll' */
  real_T e4_l;                       /* '<Root>/MATLAB Function - fopid_roll' */
  real_T e5_f;                       /* '<Root>/MATLAB Function - fopid_roll' */
  real_T y1_l;                       /* '<Root>/MATLAB Function - fopid_roll' */
  real_T y2_j;                       /* '<Root>/MATLAB Function - fopid_roll' */
  real_T y3_l;                       /* '<Root>/MATLAB Function - fopid_roll' */
  real_T y4_f;                       /* '<Root>/MATLAB Function - fopid_roll' */
  real_T y5_c;                       /* '<Root>/MATLAB Function - fopid_roll' */
  real_T u1_mt;                      /* '<Root>/MATLAB Function - fopid_roll' */
  real_T e1_g;                      /* '<Root>/MATLAB Function - fopid_pitch' */
  real_T e2_o;                      /* '<Root>/MATLAB Function - fopid_pitch' */
  real_T e3_m;                      /* '<Root>/MATLAB Function - fopid_pitch' */
  real_T e4_e;                      /* '<Root>/MATLAB Function - fopid_pitch' */
  real_T e5_o;                      /* '<Root>/MATLAB Function - fopid_pitch' */
  real_T y1_m;                      /* '<Root>/MATLAB Function - fopid_pitch' */
  real_T y2_l;                      /* '<Root>/MATLAB Function - fopid_pitch' */
  real_T y3_m;                      /* '<Root>/MATLAB Function - fopid_pitch' */
  real_T y4_fl;                     /* '<Root>/MATLAB Function - fopid_pitch' */
  real_T y5_cv;                     /* '<Root>/MATLAB Function - fopid_pitch' */
  real_T u_prev;                    /* '<Root>/MATLAB Function - fopid_pitch' */
  real_T e1_j;                     /* '<Root>/MATLAB Function - fopid_altura' */
  real_T e2_i;                     /* '<Root>/MATLAB Function - fopid_altura' */
  real_T e3_c;                     /* '<Root>/MATLAB Function - fopid_altura' */
  real_T e4_p;                     /* '<Root>/MATLAB Function - fopid_altura' */
  real_T e5_b;                     /* '<Root>/MATLAB Function - fopid_altura' */
  real_T y1_h;                     /* '<Root>/MATLAB Function - fopid_altura' */
  real_T y2_a;                     /* '<Root>/MATLAB Function - fopid_altura' */
  real_T y3_h;                     /* '<Root>/MATLAB Function - fopid_altura' */
  real_T y4_p;                     /* '<Root>/MATLAB Function - fopid_altura' */
  real_T y5_f;                     /* '<Root>/MATLAB Function - fopid_altura' */
  real_T u1_d;                     /* '<Root>/MATLAB Function - fopid_altura' */
  uint32_T PreLookUpIndexSearchprobofexcee;
                         /* '<S60>/PreLook-Up Index Search  (prob of exceed)' */
  uint32_T PreLookUpIndexSearchaltitude_DW;
                               /* '<S60>/PreLook-Up Index Search  (altitude)' */
  uint32_T RandSeed[4];                /* '<S53>/White Noise' */
  uint32_T RandSeed_a;                 /* '<S33>/White Noise' */
  robotics_slcore_internal_bloc_T obj_c;
                             /* '<Root>/Coordinate Transformation Conversion' */
  int8_T ifHeightMaxlowaltitudeelseifHei;
  /* '<S49>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
  int8_T ifHeightMaxlowaltitudeelseifH_a;
  /* '<S48>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
  boolean_T IC_FirstOutputTime;        /* '<S30>/IC' */
  boolean_T Integrator_DWORK1;         /* '<S30>/Integrator' */
  boolean_T objisempty;                /* '<S32>/SourceBlock' */
  boolean_T objisempty_g;              /* '<S31>/SourceBlock' */
  boolean_T objisempty_a;              /* '<S41>/SourceBlock' */
  boolean_T objisempty_e;              /* '<S40>/SourceBlock' */
  boolean_T objisempty_l;              /* '<S39>/SourceBlock' */
  boolean_T objisempty_c;              /* '<S38>/SourceBlock' */
  boolean_T objisempty_cr;             /* '<S28>/SinkBlock' */
  boolean_T objisempty_ld;             /* '<S27>/SinkBlock' */
  boolean_T objisempty_ev;             /* '<S26>/SinkBlock' */
  boolean_T objisempty_m;              /* '<S25>/SinkBlock' */
  boolean_T objisempty_d;    /* '<Root>/Coordinate Transformation Conversion' */
  boolean_T fctrlobj_not_empty;
                             /* '<Root>/Coordinate Transformation Conversion' */
  boolean_T objisempty_f;              /* '<S6>/ServiceCaller' */
  e_robotics_core_internal_vali_T fctrlobj;
                             /* '<Root>/Coordinate Transformation Conversion' */
  boolean_T Hwgws_MODE;                /* '<S44>/Hwgw(s)' */
  boolean_T Hvgws_MODE;                /* '<S44>/Hvgw(s)' */
  boolean_T Hugws_MODE;                /* '<S44>/Hugw(s)' */
  boolean_T Hrgw_MODE;                 /* '<S43>/Hrgw' */
  boolean_T Hqgw_MODE;                 /* '<S43>/Hqgw' */
  boolean_T Hpgw_MODE;                 /* '<S43>/Hpgw' */
};

/* Continuous states (default storage) */
struct X_FOpid_control_V4_T {
  real_T Integrator_CSTATE[12];        /* '<S30>/Integrator' */
  real_T TransferFcn_CSTATE[2];        /* '<S30>/Transfer Fcn' */
  real_T TransferFcn1_CSTATE;          /* '<S30>/Transfer Fcn1' */
  real_T Integrator1_CSTATE;           /* '<S30>/Integrator1' */
  real_T wg_p1_CSTATE[2];              /* '<S59>/wg_p1' */
  real_T wg_p2_CSTATE[2];              /* '<S59>/wg_p2' */
  real_T vg_p1_CSTATE[2];              /* '<S58>/vg_p1' */
  real_T vgw_p2_CSTATE[2];             /* '<S58>/vgw_p2' */
  real_T ug_p_CSTATE[2];               /* '<S57>/ug_p' */
  real_T rgw_p_CSTATE[2];              /* '<S56>/rgw_p' */
  real_T qgw_p_CSTATE[2];              /* '<S55>/qgw_p' */
  real_T pgw_p_CSTATE[2];              /* '<S54>/pgw_p' */
};

/* State derivatives (default storage) */
struct XDot_FOpid_control_V4_T {
  real_T Integrator_CSTATE[12];        /* '<S30>/Integrator' */
  real_T TransferFcn_CSTATE[2];        /* '<S30>/Transfer Fcn' */
  real_T TransferFcn1_CSTATE;          /* '<S30>/Transfer Fcn1' */
  real_T Integrator1_CSTATE;           /* '<S30>/Integrator1' */
  real_T wg_p1_CSTATE[2];              /* '<S59>/wg_p1' */
  real_T wg_p2_CSTATE[2];              /* '<S59>/wg_p2' */
  real_T vg_p1_CSTATE[2];              /* '<S58>/vg_p1' */
  real_T vgw_p2_CSTATE[2];             /* '<S58>/vgw_p2' */
  real_T ug_p_CSTATE[2];               /* '<S57>/ug_p' */
  real_T rgw_p_CSTATE[2];              /* '<S56>/rgw_p' */
  real_T qgw_p_CSTATE[2];              /* '<S55>/qgw_p' */
  real_T pgw_p_CSTATE[2];              /* '<S54>/pgw_p' */
};

/* State disabled  */
struct XDis_FOpid_control_V4_T {
  boolean_T Integrator_CSTATE[12];     /* '<S30>/Integrator' */
  boolean_T TransferFcn_CSTATE[2];     /* '<S30>/Transfer Fcn' */
  boolean_T TransferFcn1_CSTATE;       /* '<S30>/Transfer Fcn1' */
  boolean_T Integrator1_CSTATE;        /* '<S30>/Integrator1' */
  boolean_T wg_p1_CSTATE[2];           /* '<S59>/wg_p1' */
  boolean_T wg_p2_CSTATE[2];           /* '<S59>/wg_p2' */
  boolean_T vg_p1_CSTATE[2];           /* '<S58>/vg_p1' */
  boolean_T vgw_p2_CSTATE[2];          /* '<S58>/vgw_p2' */
  boolean_T ug_p_CSTATE[2];            /* '<S57>/ug_p' */
  boolean_T rgw_p_CSTATE[2];           /* '<S56>/rgw_p' */
  boolean_T qgw_p_CSTATE[2];           /* '<S55>/qgw_p' */
  boolean_T pgw_p_CSTATE[2];           /* '<S54>/pgw_p' */
};

/* Zero-crossing (trigger) state */
struct PrevZCX_FOpid_control_V4_T {
  ZCSigState Integrator_Reset_ZCE;     /* '<S30>/Integrator' */
};

/* Invariant block signals (default storage) */
struct ConstB_FOpid_control_V4_T {
  real_T UnitConversion;               /* '<S42>/Unit Conversion' */
  real_T UnitConversion_k;             /* '<S52>/Unit Conversion' */
  real_T sigma_wg;                     /* '<S61>/sigma_wg ' */
  real_T UnitConversion_n;             /* '<S46>/Unit Conversion' */
  real_T UnitConversion_c;             /* '<S80>/Unit Conversion' */
  real_T PreLookUpIndexSearchprobofe;
                         /* '<S60>/PreLook-Up Index Search  (prob of exceed)' */
  real_T constBlockForifHeightMaxlow;
  real_T constBlockForifHeightMaxl_e;
  real_T constBlockForifHeightMaxl_l;
  real_T constBlockForifHeightMax_eh;
  real_T Sqrt[4];                      /* '<S53>/Sqrt' */
  real_T Sqrt1;                        /* '<S53>/Sqrt1' */
  real_T Divide[4];                    /* '<S53>/Divide' */
  real_T motorspeed;                   /* '<S30>/Gain2' */
  real_T Sum;                          /* '<S70>/Sum' */
  real_T Sum_a;                        /* '<S62>/Sum' */
  real_T sqrt_a;                       /* '<S59>/sqrt' */
  real_T w4;                           /* '<S54>/w4' */
  real_T u16;                          /* '<S54>/u^1//6' */
  uint32_T PreLookUpIndexSearchprobo_g;
                         /* '<S60>/PreLook-Up Index Search  (prob of exceed)' */
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
struct ConstP_FOpid_control_V4_T {
  /* Pooled Parameter (Expression: x_nom)
   * Referenced by:
   *   '<S30>/IC'
   *   '<S30>/Memory2'
   */
  real_T pooled11[12];

  /* Expression: h_vec
   * Referenced by: '<S60>/PreLook-Up Index Search  (altitude)'
   */
  real_T PreLookUpIndexSearchaltitude_Br[12];

  /* Expression: sigma_vec'
   * Referenced by: '<S60>/Medium//High Altitude Intensity'
   */
  real_T MediumHighAltitudeIntensity_Tab[84];

  /* Computed Parameter: MediumHighAltitudeIntensity_max
   * Referenced by: '<S60>/Medium//High Altitude Intensity'
   */
  uint32_T MediumHighAltitudeIntensity_max[2];
};

/* Real-time Model Data Structure */
struct tag_RTM_FOpid_control_V4_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_FOpid_control_V4_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_FOpid_control_V4_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[32];
  real_T odeF[4][32];
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

extern const ConstB_FOpid_control_V4_T FOpid_control_V4_ConstB;/* constant block i/o */

/* Constant parameters (default storage) */
extern const ConstP_FOpid_control_V4_T FOpid_control_V4_ConstP;

/* Class declaration for model FOpid_control_V4 */
class FOpid_control_V4
{
  /* public data and function members */
 public:
  /* Real-Time Model get method */
  RT_MODEL_FOpid_control_V4_T * getRTM();
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
  FOpid_control_V4();

  /* Destructor */
  ~FOpid_control_V4();

  /* private data and function members */
 private:
  /* Block signals */
  B_FOpid_control_V4_T FOpid_control_V4_B;

  /* Block states */
  DW_FOpid_control_V4_T FOpid_control_V4_DW;

  /* Block continuous states */
  X_FOpid_control_V4_T FOpid_control_V4_X;

  /* Block Continuous state disabled vector */
  XDis_FOpid_control_V4_T FOpid_control_V4_XDis;

  /* Triggered events */
  PrevZCX_FOpid_control_V4_T FOpid_control_V4_PrevZCX;

  /* private member function(s) for subsystem '<Root>/MATLAB Function-ned_to_PoseStamped'*/
  static void MATLABFunctionned_to_PoseStampe(B_MATLABFunctionned_to_PoseSt_T
    *localB);

  /* private member function(s) for subsystem '<S38>/Enabled Subsystem'*/
  static void FOpid_con_EnabledSubsystem_Init(B_EnabledSubsystem_FOpid_cont_T
    *localB);
  static void FOpid_control__EnabledSubsystem(boolean_T rtu_Enable, const
    SL_Bus_std_msgs_Bool *rtu_In1, B_EnabledSubsystem_FOpid_cont_T *localB);

  /* private member function(s) for subsystem '<S39>/Enabled Subsystem'*/
  static void FOpid_c_EnabledSubsystem_g_Init(B_EnabledSubsystem_FOpid_co_d_T
    *localB);
  static void FOpid_contro_EnabledSubsystem_k(boolean_T rtu_Enable, const
    SL_Bus_std_msgs_Float64 *rtu_In1, B_EnabledSubsystem_FOpid_co_d_T *localB);

  /* private member function(s) for subsystem '<Root>'*/
  void FOpid_contr_Publisher_setupImpl(const ros_slros2_internal_block_Pub_T
    *obj);
  rmw_qos_profile_t FO_ROS2PubSubBase_setQOSProfile(rmw_qos_profile_t rmwProfile,
    real_T qosDepth, real_T qosDeadline, real_T qosLifespan, real_T
    qosLeaseDuration, boolean_T qosAvoidROSNamespaceConventions);
  void FOpid_con_Publisher_setupImpl_b(const ros_slros2_internal_block_Pub_T
    *obj);
  void FOpid_co_Publisher_setupImpl_bg(const ros_slros2_internal_block_Pub_T
    *obj);
  void FOpid_Subscriber_setupImpl_bgmt(const ros_slros2_internal_block_Sub_T
    *obj);
  void FOpi_Subscriber_setupImpl_bgmtj(const ros_slros2_internal_block_Sub_T
    *obj);
  void FOpid_c_ServiceCaller_setupImpl(ros_slros2_internal_block_Ser_T *obj);
  void FOpid__Subscriber_setupImpl_bgm(const ros_slros2_internal_block_Sub_T
    *obj);
  void FOpid_cont_Subscriber_setupImpl(const ros_slros2_internal_block_Sub_T
    *obj);
  void FOpid_co_Subscriber_setupImpl_b(const ros_slros2_internal_block_Sub_T
    *obj);
  void FOpid_c_Subscriber_setupImpl_bg(const ros_slros2_internal_block_Sub_T
    *obj);

  /* Global mass matrix */

  /* Continuous states update member function*/
  void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si );

  /* Derivatives member function */
  void FOpid_control_V4_derivatives();

  /* Real-Time Model */
  RT_MODEL_FOpid_control_V4_T FOpid_control_V4_M;
};

extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Display' : Unused code path elimination
 * Block '<S30>/Gain4' : Unused code path elimination
 * Block '<Root>/Manual Switch' : Eliminated due to constant selection input
 * Block '<S35>/Cast' : Eliminate redundant data type conversion
 * Block '<S35>/Cast To Double' : Eliminate redundant data type conversion
 * Block '<S35>/Cast To Double1' : Eliminate redundant data type conversion
 * Block '<S35>/Cast To Double2' : Eliminate redundant data type conversion
 * Block '<S35>/Cast To Double3' : Eliminate redundant data type conversion
 * Block '<S35>/Cast To Double4' : Eliminate redundant data type conversion
 * Block '<S66>/Reshape' : Reshape block reduction
 * Block '<S66>/Reshape1' : Reshape block reduction
 * Block '<S68>/Reshape' : Reshape block reduction
 * Block '<S74>/Reshape' : Reshape block reduction
 * Block '<S74>/Reshape1' : Reshape block reduction
 * Block '<S76>/Reshape' : Reshape block reduction
 * Block '<Root>/Constant_U' : Unused code path elimination
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
 * '<Root>' : 'FOpid_control_V4'
 * '<S1>'   : 'FOpid_control_V4/Blank Message'
 * '<S2>'   : 'FOpid_control_V4/Blank Message1'
 * '<S3>'   : 'FOpid_control_V4/Blank Message2'
 * '<S4>'   : 'FOpid_control_V4/Blank Message3'
 * '<S5>'   : 'FOpid_control_V4/Blank Message4'
 * '<S6>'   : 'FOpid_control_V4/Call Service'
 * '<S7>'   : 'FOpid_control_V4/MATLAB Function'
 * '<S8>'   : 'FOpid_control_V4/MATLAB Function - fopid_altura'
 * '<S9>'   : 'FOpid_control_V4/MATLAB Function - fopid_pitch'
 * '<S10>'  : 'FOpid_control_V4/MATLAB Function - fopid_roll'
 * '<S11>'  : 'FOpid_control_V4/MATLAB Function - fopid_velocidad'
 * '<S12>'  : 'FOpid_control_V4/MATLAB Function - fopid_yaw'
 * '<S13>'  : 'FOpid_control_V4/MATLAB Function-IMU2'
 * '<S14>'  : 'FOpid_control_V4/MATLAB Function-MODELO'
 * '<S15>'  : 'FOpid_control_V4/MATLAB Function-Odometry'
 * '<S16>'  : 'FOpid_control_V4/MATLAB Function-Odometry1'
 * '<S17>'  : 'FOpid_control_V4/MATLAB Function-clocl'
 * '<S18>'  : 'FOpid_control_V4/MATLAB Function-ned_to_PoseStaamped'
 * '<S19>'  : 'FOpid_control_V4/MATLAB Function-ned_to_PoseStamped'
 * '<S20>'  : 'FOpid_control_V4/MATLAB Function-ned_to_TwistStamped'
 * '<S21>'  : 'FOpid_control_V4/MATLAB Function-ned_to_gazebo'
 * '<S22>'  : 'FOpid_control_V4/MATLAB Function-ned_to_imu'
 * '<S23>'  : 'FOpid_control_V4/MATLAB Function-ned_to_odometry'
 * '<S24>'  : 'FOpid_control_V4/MATLAB Function2'
 * '<S25>'  : 'FOpid_control_V4/Publish'
 * '<S26>'  : 'FOpid_control_V4/Publish1'
 * '<S27>'  : 'FOpid_control_V4/Publish2'
 * '<S28>'  : 'FOpid_control_V4/Publish3'
 * '<S29>'  : 'FOpid_control_V4/Ramp'
 * '<S30>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL'
 * '<S31>'  : 'FOpid_control_V4/Subscribe-ALTURA'
 * '<S32>'  : 'FOpid_control_V4/Subscribe-YAW'
 * '<S33>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Band-Limited White Noise'
 * '<S34>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Compare To Constant'
 * '<S35>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))'
 * '<S36>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/MATLAB Function - MODEL'
 * '<S37>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/MATLAB Function-reset'
 * '<S38>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Subscribe1_TURBULENCIA1'
 * '<S39>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Subscribe_HEAVE'
 * '<S40>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Subscribe_RATE'
 * '<S41>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Subscribe_TURBULENCIA'
 * '<S42>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Angle Conversion'
 * '<S43>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Filters on angular rates'
 * '<S44>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Filters on velocities'
 * '<S45>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Length Conversion'
 * '<S46>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Length Conversion1'
 * '<S47>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/RMS turbulence  intensities'
 * '<S48>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates'
 * '<S49>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities'
 * '<S50>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Turbulence scale lengths'
 * '<S51>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Velocity Conversion'
 * '<S52>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Velocity Conversion2'
 * '<S53>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/White Noise'
 * '<S54>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Filters on angular rates/Hpgw'
 * '<S55>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Filters on angular rates/Hqgw'
 * '<S56>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Filters on angular rates/Hrgw'
 * '<S57>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Filters on velocities/Hugw(s)'
 * '<S58>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Filters on velocities/Hvgw(s)'
 * '<S59>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Filters on velocities/Hwgw(s)'
 * '<S60>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/RMS turbulence  intensities/High Altitude Intensity'
 * '<S61>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/RMS turbulence  intensities/Low Altitude Intensity'
 * '<S62>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates/Interpolate  rates'
 * '<S63>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates/Low altitude  rates'
 * '<S64>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates/Medium//High  altitude rates'
 * '<S65>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates/Merge Subsystems'
 * '<S66>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates/Interpolate  rates/wind to body transformation'
 * '<S67>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates/Interpolate  rates/wind to body transformation/convert to earth coords'
 * '<S68>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates/Low altitude  rates/wind to body transformation'
 * '<S69>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates/Low altitude  rates/wind to body transformation/convert to earth coords'
 * '<S70>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities/Interpolate  velocities'
 * '<S71>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities/Low altitude  velocities'
 * '<S72>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities/Medium//High  altitude velocities'
 * '<S73>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities/Merge Subsystems'
 * '<S74>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities/Interpolate  velocities/wind to body transformation'
 * '<S75>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities/Interpolate  velocities/wind to body transformation/convert to earth coords'
 * '<S76>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities/Low altitude  velocities/wind to body transformation'
 * '<S77>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities/Low altitude  velocities/wind to body transformation/convert to earth coords'
 * '<S78>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Turbulence scale lengths/Low altitude scale length'
 * '<S79>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Turbulence scale lengths/Medium//High altitude scale length'
 * '<S80>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Dryden Wind Turbulence Model  (Continuous (-q +r))/Turbulence scale lengths/Medium//High altitude scale length/Length Conversion'
 * '<S81>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Subscribe1_TURBULENCIA1/Enabled Subsystem'
 * '<S82>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Subscribe_HEAVE/Enabled Subsystem'
 * '<S83>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Subscribe_RATE/Enabled Subsystem'
 * '<S84>'  : 'FOpid_control_V4/SUBSYSTEM_MODEL/Subscribe_TURBULENCIA/Enabled Subsystem'
 * '<S85>'  : 'FOpid_control_V4/Subscribe-ALTURA/Enabled Subsystem'
 * '<S86>'  : 'FOpid_control_V4/Subscribe-YAW/Enabled Subsystem'
 */
#endif                                 /* FOPID_CONTROL_V4_H_ */
