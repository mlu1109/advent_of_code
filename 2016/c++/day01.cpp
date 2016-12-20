#include <iostream>
#include <map>

struct Coord
{
	int r;
	int c;
};

bool operator<(const Coord &lhs, const Coord &rhs)
{
	return lhs.c == rhs.c ? lhs.r < rhs.r : lhs.c < rhs.c;
}

void part1()
{
	Coord current{0, 0};
	int facing = 0; // N: 0 E: 1 S: 2 W: 3
	std::string directions;
	while (std::cin >> directions)
	{
		if (directions.back() == ',')
			directions.pop_back();

		facing += directions[0] == 'R' ? 1 : 3;
		facing %= 4;
		int steps = std::stoi(directions.substr(1));
		if (facing % 2 == 0)
			current.r += facing == 0 ? 1 * steps : -1 * steps;
		else
			current.c += facing == 1 ? 1 * steps : -1 * steps;
	}

	std::cout << "Part 1: " << std::abs(current.r) + std::abs(current.c) << '\n';
}

void part2()
{
	std::map<Coord, bool> visited;
	Coord current{0, 0};
	int facing = 0; // N: 0 E: 1 S: 2 W: 3
	visited[current] = true;
	std::string directions;
	while (std::cin >> directions)
	{
		if (directions.back() == ',')
			directions.pop_back();

		facing += directions[0] == 'R' ? 1 : 3;
		facing %= 4;
		int steps = std::stoi(directions.substr(1));
		for (int i = 0; i < steps; ++i)
		{
			if (facing % 2 == 0)
				current.r += facing == 0 ? 1 : -1;
			else
				current.c += facing == 1 ? 1 : -1;
			
			if (visited[current])
			{
				std::cout << "Part 2: " << std::abs(current.r) + std::abs(current.c) << '\n';
				return;
			}

			visited[current] = true;
		}
	}

	std::cout << "Part 2 failed\n";
}

int main()
{
	//part1();
	part2();
}
