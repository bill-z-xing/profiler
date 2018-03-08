
#include "profiler.hpp"


int main()
{
	uint64_t result = (uint64_t)&main;
	uint64_t num_iters = 1;
	for (uint64_t number_of_zeros = 0; number_of_zeros < 12; ++number_of_zeros)
	{
		Profiler p(std::to_string(number_of_zeros) + " 0s");
		for (uint64_t i = 0; i < num_iters; ++i)
		{
			result = result ^ (uint64_t)&i;
		}

		num_iters *= 10;
	}

	std::cout << "Result: " << result << std::endl;

	return 0;
}
