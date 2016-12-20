#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>

bool triangle(int a, int b, int c)
{
	return a + b > c && b + c > a && a + c > b;
}

void part1()
{
	std::string line;
	int valid = 0;
	while(std::getline(std::cin, line))
	{
		std::istringstream iss(line);
		int sides[3];
		for (int i = 0; i < 3; ++i)
			iss >> sides[i];

		if (triangle(sides[0], sides[1], sides[2]))
			++valid;
	}

	std::cout << "Part 1: " << valid << '\n';
}

void part2()
{
	std::string line[3];
	int valid = 0;
	while(std::getline(std::cin, line[0]) && 
		  std::getline(std::cin, line[1]) && 
		  std::getline(std::cin, line[2]))
	{
		int sides[3][3];
		for (int i = 0; i < 3; ++i)
		{
			std::istringstream iss(line[i]);
			for (int j = 0; j < 3; ++j)
				iss >> sides[j][i];
		}

		for (int i = 0; i < 3; ++i)
			if (triangle(sides[i][0], sides[i][1], sides[i][2]))
				++valid;
	}
	
	std::cout << "Part 2: " << valid << '\n';
}

int main()
{
	//part1();
	part2();
}
