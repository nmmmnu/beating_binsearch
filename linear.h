#ifndef _LINEAR_SEARCH_H
#define _LINEAR_SEARCH_H

#include <string>

template <class T, class COMPARE>
struct LinearSearch{
	const std::string title = "Linear Search";

	char search(uint64_t const start, uint64_t const end, const T *data, const T key, uint64_t &index) const{
		char cmp = -1;

		uint64_t i;
		for(i = start; i < end; ++i){
			cmp = comp.cmp(data[i], key);

			if (cmp == 0){
				// found
				index = i;
				return 0;
			}

			if (cmp > 0)
				break;
		}

		index = i;
		return cmp;
	}

private:
	COMPARE	comp;
};

#endif

