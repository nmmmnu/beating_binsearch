//#include "search.h"

#include <sys/time.h>

#include <cstdint>
#include <random>
#include <iostream>
#include <iomanip>

constexpr const int RANDOM_SEED = 0;
constexpr const int ARRAY_SIZE = 10000000;
constexpr const int TEST_COUNT = 1000000;

#include "linear.h"
#include "binary.h"
#include "improved.h"
#include "improved_unroll.h"
#include "compare.h"

template <class T, class SEARCH>
class SearchTest{
public:
	SearchTest(uint64_t const size) :
			size(size),
			data(new T[size]){
		init();
	}

	~SearchTest(){
		delete[] data;
	}

	uint64_t init(){
		std::mt19937 rand(RANDOM_SEED);

		uint64_t max = 0;

		for(uint64_t i = 0 + 1; i < size; ++i){
			max += 1 + (rand() & 0xFF);
			data[i] = max;
		}

		return max;
	}

	void print(){
		for(uint64_t i = 0; i < size; ++i)
			std::cout
				<< i << "\t"
				<< data[i] << std::endl;
	}

	void process(){
		init();

		std::mt19937				rand(RANDOM_SEED);
		std::uniform_int_distribution<T>	distr(0, size - 1);

		SEARCH search;

		auto start = get_timestamp();
		for (int i = 0; i < TEST_COUNT; ++i){
			uint64_t result;
			uint64_t original = distr(rand);

			char result_comp = search.search(0, size, data, data[original], result );

			if (result_comp != 0 || result != original){
				std::cout
					<< search.title << "\t"
					<< "problem with search algoritm" << std::endl;
				exit(1);
			}
		}
		auto stop  = get_timestamp();

		std::cout
				<< std::setw(40) << search.title << " "
				<< (stop - start) << std::endl;
	}

private:
	uint64_t			size;
	T				*data;

private:
	static uint64_t get_timestamp(){
		struct timeval now;
		gettimeofday (&now, NULL);
		return  now.tv_usec + (uint64_t) now.tv_sec * 1000000;
	}

};



int main(){
	SearchTest<int, LinearSearch<int, Compare<int>> > s1 { ARRAY_SIZE };
//	s1.print();
//	s1.process();

	SearchTest<int, BinarySearch<int, Compare<int>> > s2 { ARRAY_SIZE };
	s2.process();

	SearchTest<int, ImprovedBinarySearch<int, Compare<int>> > s3 { ARRAY_SIZE };
	s3.process();

	SearchTest<int, ImprovedUnrolledBinarySearch<int, Compare<int>> > s4 { ARRAY_SIZE };
	s4.process();

}

