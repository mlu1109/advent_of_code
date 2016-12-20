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
	std::map<Coord, char> keypad
	{
			{Coord{-1, -1}, '1'}, {Coord{-1,  0}, '2'}, {Coord{-1,  1}, '3'},
			{Coord{ 0, -1}, '4'}, {Coord{ 0,  0}, '5'}, {Coord{ 0,  1}, '6'},
			{Coord{ 1, -1}, '7'}, {Coord{ 1,  0}, '8'}, {Coord{ 1,  1}, '9'}
	};
	std::string line;
	std::string code;
	Coord current{0, 0};
	while (std::cin >> line) 
	{
		for (char c : line)
		{
			if (c == 'U' && current.r > -1)
				current.r -= 1;
			else if (c == 'D' && current.r < 1)
				current.r += 1;
			else if (c == 'R' && current.c < 1)
				current.c += 1;
			else if (c == 'L' && current.c > -1)
				current.c -= 1;
		}

		code += keypad[current];
	}

	std::cout << "Part 1: " << code << '\n';
}

void part2()
{
	std::map<Coord, char> keypad
	{
			{Coord{-2,  0}, '1'},
			{Coord{-1, -1}, '2'}, {Coord{-1,  0}, '3'}, {Coord{-1, 1}, '4'},
			{Coord{ 0, -2}, '5'}, {Coord{ 0, -1}, '6'}, {Coord{ 0, 0}, '7'}, {Coord{0, 1}, '8'}, {Coord{0, 2}, '9'},
			{Coord{ 1, -1}, 'A'}, {Coord{ 1,  0}, 'B'}, {Coord{ 1, 1}, 'C'},
			{Coord{ 2,  0}, 'D'}
	};
	std::string line;
	std::string code;
	Coord current{0, -2};
	while (std::cin >> line)
	{
		for (char c : line)
		{
			if (c == 'U' && std::abs(current.r - 1) + std::abs(current.c) < 3)
				current.r -= 1;
			else if (c == 'D' && std::abs(current.r + 1) + std::abs(current.c) < 3)
				current.r += 1;
			else if (c == 'R' && std::abs(current.r) + std::abs(current.c + 1) < 3)
				current.c += 1;
			else if (c == 'L' && std::abs(current.r) + std::abs(current.c - 1) < 3)
				current.c -= 1;
		}

		code += keypad[current];
	}

	std::cout << "Part 2: " << code << '\n';
}

int main()
{
	part1();
	//part2();
}