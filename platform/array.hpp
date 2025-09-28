// std::array polyfill
// -------------------

#if (__cplusplus >= 201103L)
#include <array>
template <class T, size_t N> using Array = std::array<T, N>;
#else
template <class T, int N> struct Array {
	typedef int size_type;

private:
	T v[N];

public:
	size_type count() const {
		return N;
	}

	T* data() {
		return v;
	}

	const T* data() const {
		return v;
	}

	T& operator [](size_type pos) {
		return v[pos];
	}

	const T& operator [](size_type pos) const {
		return v[pos];
	}
};
#endif
