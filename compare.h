#ifndef _COMPARE_H
#define _COMPARE_H

template <class T>
struct Compare{
	__attribute__((always_inline))
	inline char cmp(const T a, const T b) const{
		if (a == b)
			return 0;

		return a > b ? +1 : -1;
	}
};

#endif

