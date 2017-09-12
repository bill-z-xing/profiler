#include <iostream>
#include <chrono>

auto now()
{
	auto val = (std::chrono::steady_clock::now().time_since_epoch());
	return val;
}


class PROFILER
{
public:
	PROFILER(const char * name) :
		_start(now()),
		_name(name)
	{

	}

	~PROFILER()
	{
		std::cout << "Profiler " << _name << " " << std::fixed << std::chrono::duration<double>(now() - _start).count() << "s" << std::endl;
	}
private:

	decltype(now()) _start;
	const char * _name;
};

int main()
{


	{
		PROFILER p("default");

	}


	return 0;
}
