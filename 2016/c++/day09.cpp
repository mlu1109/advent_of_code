#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

std::pair<int, int> parseMarker(const std::string &line, int &s)
{
	int x = line.find('x', s);
	int e = line.find(')', x);
	auto marker = std::pair<int, int>(
		std::stoi(line.substr(s + 1, x - s - 1)),
		std::stoi(line.substr(x + 1, e - x - 1))
	);
	s = e;
	return marker;
}

void part1()
{
	std::string line;
	int count = 0;
	while(std::getline(std::cin, line))
	{
		for (int i = 0; i < line.size(); ++i)
		{
			if (line[i] == '(')
			{
				auto marker = parseMarker(line, i);
				count += marker.first * marker.second;
				i += marker.first;
			}
			else
				++count;
		}
	}

	std::cout << "Part 1: " << count << '\n';
}


unsigned long long count(std::string line, int mul)
{
	if (line[0] == '(')
	{
		int s = 0;
		auto marker = parseMarker(line, s);
		return count(line.substr(s + 1, marker.first), mul * marker.second) + 
			   count(line.substr(s + marker.first + 1), mul);
	}

	int s = line.find('(');
	if (s == std::string::npos)
		return line.size() * mul;
	else
		return s * mul + count(line.substr(s), mul);
}

void part2()
{
	std::string line;
	unsigned long long cnt = 0;
	while(std::getline(std::cin, line))
		cnt += count(line, 1);
	
	std::cout << "Part 2: " << cnt << '\n';
}


int main()
{
	//part1();
	part2();
}