/*
 * multiword_types.h
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

#ifndef MULTIWORD_TYPES_H
#define MULTIWORD_TYPES_H
#include "rtwtypes.h"

/*
 * MultiWord supporting definitions
 */
typedef long int long_T;

/*
 * MultiWord types
 */
#ifndef INT128M_T
#define INT128M_T

typedef struct {
  uint64_T chunks[2];
} int128m_T;

#endif

#ifndef CINT128M_T
#define CINT128M_T

typedef struct {
  int128m_T re;
  int128m_T im;
} cint128m_T;

#endif

#ifndef UINT128M_T
#define UINT128M_T

typedef struct {
  uint64_T chunks[2];
} uint128m_T;

#endif

#ifndef CUINT128M_T
#define CUINT128M_T

typedef struct {
  uint128m_T re;
  uint128m_T im;
} cuint128m_T;

#endif

#ifndef INT192M_T
#define INT192M_T

typedef struct {
  uint64_T chunks[3];
} int192m_T;

#endif

#ifndef CINT192M_T
#define CINT192M_T

typedef struct {
  int192m_T re;
  int192m_T im;
} cint192m_T;

#endif

#ifndef UINT192M_T
#define UINT192M_T

typedef struct {
  uint64_T chunks[3];
} uint192m_T;

#endif

#ifndef CUINT192M_T
#define CUINT192M_T

typedef struct {
  uint192m_T re;
  uint192m_T im;
} cuint192m_T;

#endif

#ifndef INT256M_T
#define INT256M_T

typedef struct {
  uint64_T chunks[4];
} int256m_T;

#endif

#ifndef CINT256M_T
#define CINT256M_T

typedef struct {
  int256m_T re;
  int256m_T im;
} cint256m_T;

#endif

#ifndef UINT256M_T
#define UINT256M_T

typedef struct {
  uint64_T chunks[4];
} uint256m_T;

#endif

#ifndef CUINT256M_T
#define CUINT256M_T

typedef struct {
  uint256m_T re;
  uint256m_T im;
} cuint256m_T;

#endif
#endif                                 /* MULTIWORD_TYPES_H */
