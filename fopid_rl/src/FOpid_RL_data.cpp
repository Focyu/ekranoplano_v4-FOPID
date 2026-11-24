/*
 * FOpid_RL_data.cpp
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

#include "FOpid_RL.h"

/* Invariant block signals (default storage) */
const ConstB_FOpid_RL_T FOpid_RL_ConstB = {
  0.0
  ,                                    /* '<S48>/Unit Conversion' */
  3.280839895013123
  ,                                    /* '<S58>/Unit Conversion' */
  0.32808398950131235
  ,                                    /* '<S67>/sigma_wg ' */
  16.469816272965875
  ,                                    /* '<S52>/Unit Conversion' */
  1749.9999999999998
  ,                                    /* '<S86>/Unit Conversion' */
  0.0
  ,                      /* '<S66>/PreLook-Up Index Search  (prob of exceed)' */
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
  ,                                    /* '<S59>/Sqrt' */
  0.1
  ,                                    /* '<S59>/Sqrt1' */

  {
    17.724538509055158
    ,
    17.724538509055158
    ,
    17.724538509055158
    ,
    17.724538509055158
  }
  ,                                    /* '<S59>/Divide' */
  767.49108527198644
  ,                                    /* '<S33>/Gain2' */
  0.0
  ,                                    /* '<S22>/Demand limits' */
  0.0
  ,                                    /* '<S23>/Demand limits' */
  0.0
  ,                                    /* '<S24>/Demand limits' */
  0.52
  ,                                    /* '<S25>/Demand limits' */
  0.52
  ,                                    /* '<S26>/Demand limits' */
  1000.0
  ,                                    /* '<S76>/Sum' */
  1000.0
  ,                                    /* '<S68>/Sum' */
  1.7320508075688772
  ,                                    /* '<S65>/sqrt' */
  0.047687123546522367
  ,                                    /* '<S60>/w4' */
  0.60218997480471
  ,                                    /* '<S60>/u^1//6' */
  2U
  /* '<S66>/PreLook-Up Index Search  (prob of exceed)' */
};

/* Constant parameters (default storage) */
const ConstP_FOpid_RL_T FOpid_RL_ConstP = {
  /* Pooled Parameter (Expression: x_nom)
   * Referenced by:
   *   '<S33>/IC'
   *   '<S33>/Memory2'
   */
  { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.026179938779914945, 0.0, 0.0, 0.0,
    -0.25 },

  /* Expression: rep_seq_y
   * Referenced by: '<S32>/Look-Up Table1'
   */
  { 0.0, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0, 17.5, 17.5, 17.5, 17.5, 20.0, 20.0,
    20.0, 20.0, 20.0, 20.0 },

  /* Expression: rep_seq_t - min(rep_seq_t)
   * Referenced by: '<S32>/Look-Up Table1'
   */
  { 0.0, 8.0, 20.0, 40.0, 60.0, 80.0, 100.0, 120.0, 140.0, 160.0, 180.0, 200.0,
    220.0, 240.0, 260.0, 280.0, 300.0 },

  /* Expression: h_vec
   * Referenced by: '<S66>/PreLook-Up Index Search  (altitude)'
   */
  { 500.0, 1750.0, 3750.0, 7500.0, 15000.0, 25000.0, 35000.0, 45000.0, 55000.0,
    65000.0, 75000.0, 80000.0 },

  /* Expression: sigma_vec'
   * Referenced by: '<S66>/Medium//High Altitude Intensity'
   */
  { 3.2, 2.2, 1.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 4.2, 3.6, 3.3,
    1.6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 6.6, 6.9, 7.4, 6.7, 4.6, 2.7,
    0.4, 0.0, 0.0, 0.0, 0.0, 0.0, 8.6, 9.6, 10.6, 10.1, 8.0, 6.6, 5.0, 4.2, 2.7,
    0.0, 0.0, 0.0, 11.8, 13.0, 16.0, 15.1, 11.6, 9.7, 8.1, 8.2, 7.9, 4.9, 3.2,
    2.1, 15.6, 17.6, 23.0, 23.6, 22.1, 20.0, 16.0, 15.1, 12.1, 7.9, 6.2, 5.1,
    18.7, 21.5, 28.4, 30.2, 30.7, 31.0, 25.2, 23.1, 17.5, 10.7, 8.4, 7.2 },

  /* Computed Parameter: MediumHighAltitudeIntensity_max
   * Referenced by: '<S66>/Medium//High Altitude Intensity'
   */
  { 11U, 6U }
};
