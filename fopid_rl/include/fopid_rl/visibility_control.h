#ifndef FOPID_RL__VISIBILITY_CONTROL_H_
#define FOPID_RL__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define FOPID_RL_EXPORT __attribute__ ((dllexport))
    #define FOPID_RL_IMPORT __attribute__ ((dllimport))
  #else
    #define FOPID_RL_EXPORT __declspec(dllexport)
    #define FOPID_RL_IMPORT __declspec(dllimport)
  #endif
  #ifdef FOPID_RL_BUILDING_LIBRARY
    #define FOPID_RL_PUBLIC FOPID_RL_EXPORT
  #else
    #define FOPID_RL_PUBLIC FOPID_RL_IMPORT
  #endif
  #define FOPID_RL_PUBLIC_TYPE FOPID_RL_PUBLIC
  #define FOPID_RL_LOCAL
#else
  #define FOPID_RL_EXPORT __attribute__ ((visibility("default")))
  #define FOPID_RL_IMPORT
  #if __GNUC__ >= 4
    #define FOPID_RL_PUBLIC __attribute__ ((visibility("default")))
    #define FOPID_RL_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define FOPID_RL_PUBLIC
    #define FOPID_RL_LOCAL
  #endif
  #define FOPID_RL_PUBLIC_TYPE
#endif
#endif  // FOPID_RL__VISIBILITY_CONTROL_H_
// Generated 14-Nov-2026 23:51:21
 