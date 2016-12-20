#include <string>
#include <iostream>
#include <vector>

const int INPUT = 10;

void part1() 
{
	std::vector<int> elves;
	for (int i = 0; i < INPUT; ++i)
		elves.push_back(1);

	int max_v = 1;
	int max_i = 0;

	for (int i = 0; max_v != INPUT; ++i)
	{
		if (elves[i % INPUT] == 0)
			continue;

		for (int j = i + 1; ; ++j)
		{
			if (elves[j % INPUT] != 0)
			{
				elves[i % INPUT] += elves[j % INPUT];
				elves[j % INPUT] = 0;
				if (elves[i % INPUT] > max_v)
				{
					max_v = elves[i % INPUT];
					max_i = i % INPUT;
				}
				break;
			}
		}
	}

	std::cout << "Part 1: " << max_i + 1 << '\n';
}

void part2()
{
	
}

int main()
{
	part1();
}