#ifndef FOPID_CONTROL_V4__VISIBILITY_CONTROL_H_
#define FOPID_CONTROL_V4__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define FOPID_CONTROL_V4_EXPORT __attribute__ ((dllexport))
    #define FOPID_CONTROL_V4_IMPORT __attribute__ ((dllimport))
  #else
    #define FOPID_CONTROL_V4_EXPORT __declspec(dllexport)
    #define FOPID_CONTROL_V4_IMPORT __declspec(dllimport)
  #endif
  #ifdef FOPID_CONTROL_V4_BUILDING_LIBRARY
    #define FOPID_CONTROL_V4_PUBLIC FOPID_CONTROL_V4_EXPORT
  #else
    #define FOPID_CONTROL_V4_PUBLIC FOPID_CONTROL_V4_IMPORT
  #endif
  #define FOPID_CONTROL_V4_PUBLIC_TYPE FOPID_CONTROL_V4_PUBLIC
  #define FOPID_CONTROL_V4_LOCAL
#else
  #define FOPID_CONTROL_V4_EXPORT __attribute__ ((visibility("default")))
  #define FOPID_CONTROL_V4_IMPORT
  #if __GNUC__ >= 4
    #define FOPID_CONTROL_V4_PUBLIC __attribute__ ((visibility("default")))
    #define FOPID_CONTROL_V4_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define FOPID_CONTROL_V4_PUBLIC
    #define FOPID_CONTROL_V4_LOCAL
  #endif
  #define FOPID_CONTROL_V4_PUBLIC_TYPE
#endif
#endif  // FOPID_CONTROL_V4__VISIBILITY_CONTROL_H_
// Generated 04-Jun-2026 13:39:00
 