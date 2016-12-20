#include <iostream>
#include <vector>
#include <algorithm>

void part2(std::string cipher, int rotations)
{
	for (char &c : cipher)
		c = c == '-' ? ' ' : (char) (((int) c - 97 + rotations) % 26 + 97);
	if (cipher.find("north") != std::string::npos)
		std::cout << "Part 2: " << rotations << '\n';
}

void part1()
{
	std::string line;
	int sum = 0;
	while (std::getline(std::cin, line))
	{
		std::vector<std::pair<char, int>> occurs;
		std::string part;
		int sector_id = 0;
		for (char c_i : line)
		{
			if (c_i == '-')
			{
				for (const auto &c_j : part)
				{
					auto it = std::find_if(
							occurs.begin(),
							occurs.end(),
							[&c_j](const std::pair<char, int> &pair)
							{
								return pair.first == c_j;
							}
					);
					if (it == occurs.end())
						occurs.push_back(std::make_pair(c_j, 1));
					else
						it->second += 1;
				}

				part.clear();
			}

			else if (c_i == '[')
			{
				sector_id = std::stoi(part);
				part.clear();
			}
			else if (c_i != ']')
				part += c_i;
		}

		std::sort(
				occurs.begin(),
				occurs.end(),
				[](const std::pair<char, int> &lhs, const std::pair<char, int> &rhs)
				{
					return lhs.second == rhs.second ? lhs.first < rhs.first : lhs.second > rhs.second;
				}
		);
		bool room = true;
		for (int i = 0; i < part.size(); ++i)
			if (part[i] != occurs[i].first)
				room = false;
		
		if (room)
		{
			sum += sector_id;
			part2(line, sector_id);
		}
	}

	std::cout << "Part 1: " << sum << '\n';
}

int main()
{
	part1();
}