#ifndef _IMPROVED_UNROLLED_BINARY_SEARCH_H
#define _IMPROVED_UNROLLED_BINARY_SEARCH_H

#include <cstdio>

#include <string>

template <class T, class COMPARE>
class ImprovedUnrolledBinarySearch{
public:
	const std::string title = "Unrolled Improved Binary Search";

	char search(uint64_t const start1, uint64_t const end1, const T *data, const T key, uint64_t &index) const{
		/*
		 * Lazy based from Linux kernel...
		 * http://lxr.free-electrons.com/source/lib/bsearch.c
		 */

		uint64_t start = start1;
		uint64_t end   = end1;

		char cmp = 0;

		//while (start < end){
		while (start < end){
		//	uint64_t mid = start + ((end - start) /  2);
			uint64_t mid = start + ((end - start) >> 1);

			//char cmp = _linear(mid - CACHE_COUNT_2, mid + CACHE_COUNT_2, data, key, mid);

			#define _LINE_HALF_SIZE 7
			#define _LINE(i)			\
			if (i >= end){				\
				start = mid + _LINE_HALF_SIZE + 1;	\
				continue;			\
			}					\
								\
			cmp = comp.cmp(data[i], key);		\
								\
			if (cmp == 0){				\
				index = i;			\
				return 0;			\
			}					\
								\
			if (cmp > 0){				\
				end = i + 1;			\
				continue;			\
			}

			_LINE(mid - 7);
			_LINE(mid - 6);
			_LINE(mid - 5);
			_LINE(mid - 4);
			_LINE(mid - 3);
			_LINE(mid - 2);
			_LINE(mid - 1);
			_LINE(mid    );
			_LINE(mid + 1);
			_LINE(mid + 2);
			_LINE(mid + 3);
			_LINE(mid + 4);
			_LINE(mid + 5);
			_LINE(mid + 6);
			_LINE(mid + 7);

			#undef _LINE

			start = mid + _LINE_HALF_SIZE + 1;
		}

		index = start;
		return cmp;
	}


private:
	COMPARE	comp;
};

#endif

