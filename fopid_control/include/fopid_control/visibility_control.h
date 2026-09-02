#ifndef FOPID_CONTROL__VISIBILITY_CONTROL_H_
#define FOPID_CONTROL__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define FOPID_CONTROL_EXPORT __attribute__ ((dllexport))
    #define FOPID_CONTROL_IMPORT __attribute__ ((dllimport))
  #else
    #define FOPID_CONTROL_EXPORT __declspec(dllexport)
    #define FOPID_CONTROL_IMPORT __declspec(dllimport)
  #endif
  #ifdef FOPID_CONTROL_BUILDING_LIBRARY
    #define FOPID_CONTROL_PUBLIC FOPID_CONTROL_EXPORT
  #else
    #define FOPID_CONTROL_PUBLIC FOPID_CONTROL_IMPORT
  #endif
  #define FOPID_CONTROL_PUBLIC_TYPE FOPID_CONTROL_PUBLIC
  #define FOPID_CONTROL_LOCAL
#else
  #define FOPID_CONTROL_EXPORT __attribute__ ((visibility("default")))
  #define FOPID_CONTROL_IMPORT
  #if __GNUC__ >= 4
    #define FOPID_CONTROL_PUBLIC __attribute__ ((visibility("default")))
    #define FOPID_CONTROL_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define FOPID_CONTROL_PUBLIC
    #define FOPID_CONTROL_LOCAL
  #endif
  #define FOPID_CONTROL_PUBLIC_TYPE
#endif
#endif  // FOPID_CONTROL__VISIBILITY_CONTROL_H_
// Generated 02-Sep-2026 17:14:23
 