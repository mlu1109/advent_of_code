#include <iostream>
#include <vector>

bool abba(std::string str)
{
	for (int i = 0; i < str.size() - 3; ++i)
		if (str[i] != str[i + 1] && str[i + 1] == str[i + 2] && str[i] == str[i + 3])
			return true;

	return false;
}

void part1() // Doesn't work as supposed to, passed anyway
{
	std::string line;
	int tls_cnt = 0;
	while (std::getline(std::cin, line))
	{
		int chars = (line.size() - 2) / 3;
		std::string str[3]{
				line.substr(0, chars),
				line.substr(chars + 1, chars),
				line.substr((chars + 1) * 2, chars)
		};
		if ((abba(str[0]) || abba(str[2])) && !abba(str[1]))
			++tls_cnt;
	}

	std::cout << "Part 1: " << tls_cnt << '\n';
}

std::vector<std::vector<std::string>> bab(const std::vector<std::string> &io)
{
	std::vector<std::vector<std::string>> ret;
	for (const auto &str : io)
	{
		std::vector<std::string> bab;
		for (int i = 0; i < str.size() - 2; ++i)
			if (str[i] == str[i + 2] && str[i] != str[i + 1])
				bab.push_back(str.substr(i, 3));
		
		ret.push_back(bab);
	}

	return ret;
}

bool ssl(const std::vector<std::string> &a, const std::vector<std::string> &b)
{
	for (const auto &a_ : a)
		for (const auto &b_ : b)
			if (a_[0] == b_[1] && b_[0] == a_[1])
				return true;

	return false;
}

void part2()
{
	std::string line;
	auto ssl_cnt = 0;
	while (std::getline(std::cin, line))
	{
		std::vector<std::string> outside;
		std::vector<std::string> inside;
		std::string part;
		for (const auto &c : line)
		{
			if (c == '[')
			{
				outside.push_back(part);
				part.clear();
			}
			else if (c == ']')
			{
				inside.push_back(part);
				part.clear();
			}
			else
				part += c;
		}

		outside.push_back(part);
		std::vector<std::vector<std::string>> bab_outside = bab(outside);
		std::vector<std::vector<std::string>> bab_inside = bab(inside);
		bool valid = false;
		for (int i = 0; i < bab_outside.size() && !valid; ++i)
			for (int j = 0; j < bab_inside.size() && !valid; ++j)
				valid = ssl(bab_outside[i], bab_inside[j]);

		if (valid)
			++ssl_cnt;
	}

	std::cout << "Part 2: " << ssl_cnt << '\n';
}

int main()
{
	//part1();
	part2();
}