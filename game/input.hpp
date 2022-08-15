// Shared input implementation macros.

#define on_condition_if_not_locked(condition, lock, func) { \
	if(condition) { \
		if(lock == false) { \
			func \
		} \
		lock = true; \
	} else { \
		lock = false; \
	} \
}

#define on_condition_if_not_locked_2(condition, lock, func) { \
	if(condition) { \
		if(lock == false) { \
			func \
			lock = true; \
		} \
	} else { \
		lock = false; \
	} \
}
