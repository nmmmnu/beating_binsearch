#ifndef _IMPROVED_BINARY_SEARCH_H
#define _IMPROVED_BINARY_SEARCH_H

#include <cstdio>

#include <string>

//#define EXIT_ONLY

template <class T, class COMPARE>
class ImprovedBinarySearch{
private:
	constexpr static const size_t CACHE_LINE	= 64; // bytes
	constexpr static const size_t CACHE_COUNT	= CACHE_LINE / sizeof(T);
	constexpr static const size_t CACHE_COUNT_2	= CACHE_COUNT / 2 - 1;
	constexpr static const size_t CACHE_COUNT_MIN	= CACHE_COUNT;

public:
	const std::string title = "Improved Binary Search";

	char search(uint64_t const start1, uint64_t const end1, const T *data, const T key, uint64_t &index) const{
		/*
		 * Lazy based from Linux kernel...
		 * http://lxr.free-electrons.com/source/lib/bsearch.c
		 */

		uint64_t start = start1;
		uint64_t end   = end1;

		//while (start < end){
		while (end - start > CACHE_COUNT_MIN){
		//	uint64_t mid = start + ((end - start) /  2);
			uint64_t mid = start + ((end - start) >> 1);

			#ifdef EXIT_ONLY
			char cmp = comp.cmp(data[mid], key);
			#else
			char cmp = _linear(mid - CACHE_COUNT_2, mid + CACHE_COUNT_2, data, key, mid);
			#endif

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

		return _linear(start, end, data, key, index);
	}

private:
	__attribute__((always_inline))
	inline char _linear(uint64_t const start, uint64_t const end, const T *data, const T key, uint64_t &index) const{
		for(uint64_t i = start; i < end; ++i){
			char cmp = comp.cmp(data[i], key);

			if (cmp == 0){
				// found
				index = i;
				return 0;
			}

			if (cmp > 0){
				// not found
				index = i;
				return +1;
			}
		}

		index = end - 1;
		return -1;
	}

private:
	COMPARE	comp;
};

#endif

