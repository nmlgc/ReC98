/* ReC98
 * -----
 * Platform- and compiler-specific types.
 */

/// <stdint.h>
/// ----------

// __TURBOC__ is #define'd on both "Borland" and "Turbo" editions, unlike
// __BORLANDC__, which is only #define'd on the former.
#if defined(__TURBOC__) && defined(__MSDOS__)
typedef unsigned char bool;
typedef int bool16;
#define false 0
#define  true 1
typedef char int8_t;
typedef int int16_t;
typedef long int32_t;
typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;

// Generic callback function types. Note the difference between function
// distance (nearfunc / farfunc) and pointer variable distance
// (t_near / t_far).
typedef void (near pascal *near nearfunc_t_near)(void);
typedef void ( far pascal *near  farfunc_t_near)(void);
typedef void (near pascal * far  nearfunc_t_far)(void);
typedef void ( far pascal * far   farfunc_t_far)(void);
#else
#error This code can currently only be compiled on Borland's 16-bit DOS compilers. Ideally, you'd only have to declare <stdint.h> types for your compiler here though?
#endif
/// ----------

#if (__cplusplus < 201103L)
#ifdef __LARGE__
#define nullptr 0UL
#else
#define nullptr 0U
#endif
#endif

// Message-less static_assert() wasn't available until C++17
#if (__cplusplus < 201703L)
#define static_assert(condition) ((void)sizeof(char[1 - 2*!(condition)]))
#endif

// Both Turbo C++ and master.lib use uint16_t for segment values throughout
// their APIs instead of the more sensible void __seg*. Maybe, integer
// arithmetic on segment values was widely considered more important than
// dereferencing?
typedef uint16_t seg_t;
