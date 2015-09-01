#ifndef _BINARY_SEARCH_H
#define _BINARY_SEARCH_H

#include <string>

template <class T, class COMPARE>
struct BinarySearch{
	const std::string title = "Binary Search";

	char search(uint64_t const start1, uint64_t const end1, const T *data, const T key, uint64_t &index) const{
		/*
		 * Lazy based from Linux kernel...
		 * http://lxr.free-electrons.com/source/lib/bsearch.c
		 */

		uint64_t start = start1;
		uint64_t end   = end1;

		char cmp = 0;

		while (start < end){
		//	uint64_t mid = start + ((end - start) /  2);
			uint64_t mid = start + ((end - start) >> 1);

			cmp = comp.cmp(data[mid], key);

			if (cmp == 0){
				// found
				index = mid;
				return 0;
			}

			if (cmp < 0){
				// go right
				start = mid + 1;
			}else{
				// go left
				end = mid;
			}
		}

		index = start;
		return cmp;
	}

private:
	COMPARE	comp;
};

#endif

