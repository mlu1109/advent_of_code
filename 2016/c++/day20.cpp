#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

struct Interval
{
	long a, b;
};

int main()
{
	std::vector<Interval> intervals;
	std::string line;
	while(std::getline(std::cin, line))
	{
		auto delim = line.find('-');
		intervals.push_back({
			std::stol(line.substr(0, delim)),
			std::stol(line.substr(delim + 1))
		});
	}

	auto sort = [](const Interval &lhs, const Interval &rhs)
	{
		return lhs.a == rhs.a ? lhs.b > rhs.b : lhs.a < rhs.a; 
	};
	std::sort(intervals.begin(), intervals.end(), sort);
	auto it = intervals.begin();
	long smallest = LONG_MAX;
	long b_max = it->b;
	long allowed = it->a;
	for (++it; it != intervals.end(); ++it)
	{
		if (it->a > b_max + 1)
		{
			if (b_max + 1 < smallest)
				smallest = b_max + 1;

			allowed += it->a - (b_max + 1);
			b_max = it->a;
		}

		if (it->b > b_max)
			b_max = it->b;
	}

	const long MAX = 4294967295;
	allowed += MAX - b_max;
	std::cout << "Part 1: " << smallest << '\n'
			  << "Part 2: " << allowed << '\n';
}  