#include <iostream>
#include <sstream>
#include <chrono>
#include <string>
#include <iomanip>

namespace
{
inline auto now()
{
	auto val = (std::chrono::steady_clock::now().time_since_epoch());
	return val;
}
}

class PROFILER
{

public:

	PROFILER(std::string name) :
		m_start(now()),
		m_name(std::move(name))
	{
		std::ostringstream oss;
		oss << "PROFILER: \"" << m_name << "\" started!" << std::endl;
		std::cout << oss.str();
	}

	~PROFILER()
	{
		double val = std::chrono::duration_cast<std::chrono::nanoseconds>(now() - m_start).count();

		enum UNIT : unsigned                  { NS,   US,   MS,   S };
		const char * unit_names[] =           {"ns", "us", "ms", "s"};

		UNIT current_unit = NS;
		while (val >= 1000.0 && current_unit != S)
		{
			val /= 1000.0;
			current_unit = (UNIT)((uint64_t)current_unit + 1);
		}

		std::ostringstream oss;
		oss << std::setprecision(3) << "PROFILER: \"" << m_name << "\" finished in " << val << unit_names[(uint64_t)current_unit] << std::endl;
		std::cout << oss.str();
	}

private:
	decltype(now()) m_start;
	const std::string m_name;
};


int main()
{
	uint64_t result = (uint64_t)&main;
	uint64_t num_iters = 1;
	for (uint64_t number_of_zeros = 0; number_of_zeros < 12; ++number_of_zeros)
	{
		PROFILER p(std::to_string(number_of_zeros) + " 0s");
		for (uint64_t i = 0; i < num_iters; ++i)
		{
			result = result ^ (uint64_t)&i;
		}

		num_iters *= 10;
	}

	std::cout << "Result: " << result << std::endl;

	return 0;
}
