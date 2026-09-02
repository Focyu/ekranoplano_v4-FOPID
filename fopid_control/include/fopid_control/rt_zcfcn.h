/*
 * rt_zcfcn.h
 *
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 *
 * Code generation for model "FOpid_control".
 *
 * Model version              : 13.62
 * Simulink Coder version : 26.1 (R2026a) 20-Nov-2025
 * C++ source code generated on : Tue Sep  1 18:34:30 2026
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RT_ZCFCN_H_
#define RT_ZCFCN_H_
#include "zero_crossing_types.h"
#include "rtwtypes.h"
#ifdef __cplusplus

extern "C"
{

#endif

  extern ZCEventType rt_ZCFcn(ZCDirection zcDir, ZCSigState *prevZc, real_T
    currValue);

#ifdef __cplusplus

}                                      /* extern "C" */

#endif
#endif                                 /* RT_ZCFCN_H_ */
