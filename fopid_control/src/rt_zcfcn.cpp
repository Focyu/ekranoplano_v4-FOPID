/*
 * rt_zcfcn.cpp
 *
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 *
 * Code generation for model "FOpid_control".
 *
 * Model version              : 13.63
 * Simulink Coder version : 26.1 (R2026a) 20-Nov-2025
 * C++ source code generated on : Wed Sep  2 17:14:11 2026
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "zero_crossing_types.h"
#include "rtwtypes.h"
#include "rt_zcfcn.h"
#include "solver_zc.h"

namespace ZCFcnEvent
{
  static boolean_T slZcHadEvent(slZcEventType ev, slZcEventType zcsDir)
  {
    return (((ev) & (zcsDir)) != 0x00 );
  }

  static slZcEventType slZcUnAliasEvents(const slZcEventType evL, slZcEventType
    evR)
  {
    boolean_T hadN2ZAndZ2P = slZcHadEvent(evL, SL_ZCS_EVENT_N2Z) && slZcHadEvent
      (evR, SL_ZCS_EVENT_Z2P);
    boolean_T hadP2ZAndZ2N = slZcHadEvent(evL, SL_ZCS_EVENT_P2Z) && slZcHadEvent
      (evR, SL_ZCS_EVENT_Z2N);
    return (hadN2ZAndZ2P || hadP2ZAndZ2N ) ? SL_ZCS_EVENT_NUL : evR;
  }
}

extern "C"
{
  /* Detect zero crossings events. */
  ZCEventType rt_ZCFcn(ZCDirection zcDir, ZCSigState *prevZc, real_T currValue)
  {
    slZcEventType zcsDir;
    slZcEventType tempEv;
    ZCEventType zcEvent = NO_ZCEVENT;  /* assume */

    /* zcEvent matrix */
    static const slZcEventType eventMatrix[4][4] = {
      /*          ZER              POS              NEG              UNK */
      { SL_ZCS_EVENT_NUL, SL_ZCS_EVENT_Z2P, SL_ZCS_EVENT_Z2N, SL_ZCS_EVENT_NUL },/* ZER */

      { SL_ZCS_EVENT_P2Z, SL_ZCS_EVENT_NUL, SL_ZCS_EVENT_P2N, SL_ZCS_EVENT_NUL },/* POS */

      { SL_ZCS_EVENT_N2Z, SL_ZCS_EVENT_N2P, SL_ZCS_EVENT_NUL, SL_ZCS_EVENT_NUL },/* NEG */

      { SL_ZCS_EVENT_NUL, SL_ZCS_EVENT_NUL, SL_ZCS_EVENT_NUL, SL_ZCS_EVENT_NUL }/* UNK */
    };

    /* get prevZcEvent and prevZcSign from prevZc */
    const slZcEventType prevEv = static_cast<slZcEventType>(static_cast<uint8_T>
      (*prevZc) >> 2);
    const slZcSignalSignType prevSign = (static_cast<slZcSignalSignType>(
      static_cast<uint8_T>(*prevZc) & static_cast<uint8_T>(0x03)));

    /* get current zcSignal sign from current zcSignal value */
    const slZcSignalSignType currSign = static_cast<slZcSignalSignType>
      (currValue > 0.0 ? SL_ZCS_SIGN_POS : (currValue < 0.0 ? SL_ZCS_SIGN_NEG :
        SL_ZCS_SIGN_ZERO));

    /* get current zcEvent based on prev and current zcSignal value */
    slZcEventType currEv = eventMatrix[prevSign][currSign];

    /* get slZcEventType from ZCDirection */
    switch (zcDir) {
     case ANY_ZERO_CROSSING:
      zcsDir = SL_ZCS_EVENT_ALL;
      break;

     case FALLING_ZERO_CROSSING:
      zcsDir = SL_ZCS_EVENT_ALL_DN;
      break;

     case RISING_ZERO_CROSSING:
      zcsDir = SL_ZCS_EVENT_ALL_UP;
      break;

     default:
      zcsDir = SL_ZCS_EVENT_NUL;
      break;
    }

    /* had event, check if zc happened */
    if (ZCFcnEvent::slZcHadEvent(currEv, zcsDir)) {
      currEv = static_cast<slZcEventType>(ZCFcnEvent::slZcUnAliasEvents(prevEv,
        currEv));
    } else {
      currEv = SL_ZCS_EVENT_NUL;
    }

    /* Update prevZc */
    tempEv = static_cast<slZcEventType>(currEv << 2);/* shift left by 2 bits */
    *prevZc = static_cast<ZCSigState>(currSign | tempEv);
    if ((currEv & SL_ZCS_EVENT_ALL_DN) != 0) {
      zcEvent = FALLING_ZCEVENT;
    } else if ((currEv & SL_ZCS_EVENT_ALL_UP) != 0) {
      zcEvent = RISING_ZCEVENT;
    } else {
      zcEvent = NO_ZCEVENT;
    }

    return zcEvent;
  }                                    /* rt_ZCFcn */
}
