/* ReC98
 * -----
 * Platform- and compiler-specific types.
 */

/// <stdint.h>
/// ----------
// __TURBOC__ is #define'd on both "Borland" and "Turbo" editions, unlike
// __BORLANDC__, which is only #define'd on the former.
#if defined(__TURBOC__) && defined(__MSDOS__)
# ifdef __cplusplus
typedef char bool;
# define false 0
# define  true 1
#endif
typedef char int8_t;
typedef short int16_t;
typedef long int32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
#else
# error This code can currently only be compiled on Borland's 16-bit DOS compilers. Ideally, you'd only have to declare <stdint.h> types for your compiler here though?
#endif
/// ----------

// Both Turbo C++ and master.lib use uint16_t for segment values throughout
// their APIs instead of the more sensible void __seg*. Maybe, integer
// arithmetic on segment values was widely considered more important than
// dereferencing?
typedef uint16_t seg_t;
