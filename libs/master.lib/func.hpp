// Memory model definitions
// ------------------------

#if !defined(MASTER_NEAR) && !defined(MASTER_FAR) && !defined(MASTER_COMPACT) && !defined(MASTER_MEDIUM)
	#if defined(__SMALL__) || defined(__TINY__) || defined(M_I86SM) || defined(M_I86TM)
		#define MASTER_NEAR
	#elif defined(__COMPACT__) || defined(M_I86CM)
		#define MASTER_COMPACT
	#elif defined(__MEDIUM__) || defined(M_I86MM)
		#define MASTER_MEDIUM
	#elif defined(__LARGE__) || defined(__HUGE__) || defined(M_I86LM) || defined(M_I86HM)
		#define MASTER_FAR
	#endif
#endif

#if defined(MASTER_NEAR)
	#define MASTER_RET near pascal
	#define MASTER_CRET near cdecl
	#define MASTER_PTR near
#elif defined(MASTER_FAR)
	#define MASTER_RET far pascal
	#define MASTER_CRET far cdecl
	#define MASTER_PTR far
#elif defined(MASTER_COMPACT)
	#define MASTER_RET near pascal
	#define MASTER_CRET near cdecl
	#define MASTER_PTR far
#elif defined(MASTER_MEDIUM)
	#define MASTER_RET far pascal
	#define MASTER_CRET far cdecl
	#define MASTER_PTR near
#endif

#ifndef MASTER_RET
	#error Memory model for master.lib could not be determined?
#endif
