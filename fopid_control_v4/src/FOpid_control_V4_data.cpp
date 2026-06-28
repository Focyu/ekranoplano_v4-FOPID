/*
 * FOpid_control_V4_data.cpp
 *
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 *
 * Code generation for model "FOpid_control_V4".
 *
 * Model version              : 13.44
 * Simulink Coder version : 26.1 (R2026a) 20-Nov-2025
 * C++ source code generated on : Sun Jun 28 19:11:25 2026
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "FOpid_control_V4.h"

/* Invariant block signals (default storage) */
const ConstB_FOpid_control_V4_T FOpid_control_V4_ConstB = {
  0.0
  ,                                    /* '<S42>/Unit Conversion' */
  3.280839895013123
  ,                                    /* '<S52>/Unit Conversion' */
  0.32808398950131235
  ,                                    /* '<S61>/sigma_wg ' */
  16.469816272965875
  ,                                    /* '<S46>/Unit Conversion' */
  1749.9999999999998
  ,                                    /* '<S80>/Unit Conversion' */
  0.0
  ,                      /* '<S60>/PreLook-Up Index Search  (prob of exceed)' */
  1000.0
  ,
  2000.0
  ,
  1000.0
  ,
  2000.0
  ,

  {
    1.7724538509055159
    ,
    1.7724538509055159
    ,
    1.7724538509055159
    ,
    1.7724538509055159
  }
  ,                                    /* '<S53>/Sqrt' */
  0.1
  ,                                    /* '<S53>/Sqrt1' */

  {
    17.724538509055158
    ,
    17.724538509055158
    ,
    17.724538509055158
    ,
    17.724538509055158
  }
  ,                                    /* '<S53>/Divide' */
  767.49108527198644
  ,                                    /* '<S30>/Gain2' */
  1000.0
  ,                                    /* '<S70>/Sum' */
  1000.0
  ,                                    /* '<S62>/Sum' */
  1.7320508075688772
  ,                                    /* '<S59>/sqrt' */
  0.047687123546522367
  ,                                    /* '<S54>/w4' */
  0.60218997480471
  ,                                    /* '<S54>/u^1//6' */
  2U
  /* '<S60>/PreLook-Up Index Search  (prob of exceed)' */
};

/* Constant parameters (default storage) */
const ConstP_FOpid_control_V4_T FOpid_control_V4_ConstP = {
  /* Pooled Parameter (Expression: x_nom)
   * Referenced by:
   *   '<S30>/IC'
   *   '<S30>/Memory2'
   */
  { 16.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.026179938779914945, 0.0, 0.0, 0.0,
    -0.05 },

  /* Expression: h_vec
   * Referenced by: '<S60>/PreLook-Up Index Search  (altitude)'
   */
  { 500.0, 1750.0, 3750.0, 7500.0, 15000.0, 25000.0, 35000.0, 45000.0, 55000.0,
    65000.0, 75000.0, 80000.0 },

  /* Expression: sigma_vec'
   * Referenced by: '<S60>/Medium//High Altitude Intensity'
   */
  { 3.2, 2.2, 1.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 4.2, 3.6, 3.3,
    1.6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 6.6, 6.9, 7.4, 6.7, 4.6, 2.7,
    0.4, 0.0, 0.0, 0.0, 0.0, 0.0, 8.6, 9.6, 10.6, 10.1, 8.0, 6.6, 5.0, 4.2, 2.7,
    0.0, 0.0, 0.0, 11.8, 13.0, 16.0, 15.1, 11.6, 9.7, 8.1, 8.2, 7.9, 4.9, 3.2,
    2.1, 15.6, 17.6, 23.0, 23.6, 22.1, 20.0, 16.0, 15.1, 12.1, 7.9, 6.2, 5.1,
    18.7, 21.5, 28.4, 30.2, 30.7, 31.0, 25.2, 23.1, 17.5, 10.7, 8.4, 7.2 },

  /* Computed Parameter: MediumHighAltitudeIntensity_max
   * Referenced by: '<S60>/Medium//High Altitude Intensity'
   */
  { 11U, 6U }
};
