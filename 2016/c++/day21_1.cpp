#include <string>
#include <iostream>
#include <algorithm>

int modulo(int lhs, int rhs)
{
	int result = lhs % rhs;
	if (result < 0)
		result = rhs + result;

	return result;
}

void swap(std::string &str, int x, int y)
{
	std::swap(str[x], str[y]);
}

void swap(std::string &str, char x, char y)
{
	int x_pos = str.find(x);
	int y_pos = str.find(y);
	swap(str, x_pos, y_pos);
}

void rotate(std::string &str, int x)
{
	std::string rotated;
	for (int i = 0; i < str.size(); ++i)
		rotated += str[modulo(i - x, str.size())];

	str = rotated;
}

void rotate(std::string &str, char x)
{
	int x_pos = str.find(x);
	rotate(str, 1);
	rotate(str, x_pos);
	if (x_pos > 3)
		rotate(str, 1);
}

void reverse(std::string &str, int x, int y)
{
	auto x_it = str.begin() + x;
	auto y_it = str.begin() + y + 1;
	std::reverse(x_it, y_it);
}

void move(std::string &str, int x, int y)
{
	char c = str[x];
	str.erase(x, 1);
	str.insert(y, 1, c);
}

int main()
{
	std::string part;
	std::string scramble = "abcdefgh";
	while (std::cin >> part)
	{
		if (part == "swap")
		{
			std::cin >> part;
			if (part == "letter")
			{
				char x, y;
				std::cin >> x >> part >> part >> y;
				swap(scramble, x, y);
			}
			else // part == "position"
			{
				int x, y;
				std::cin >> x >> part >> part >> y;
				swap(scramble, x, y);
			}

		}
		else if (part == "rotate")
		{
			std::cin >> part;
			if (part == "based")
			{
				char x;
				std::cin >> part >> part >> part >> part >> x;
				rotate(scramble, x);
			}
			else // part == "left" || part == "right"
			{
				int x;
				std::cin >> x;
				if (part == "left")
					x *= -1;

				rotate(scramble, x);
				std::cin >> part;
			}
		}
		else if (part == "reverse")
		{
			int x, y;
			std::cin >> part >> x >> part >> y;
			reverse(scramble, x, y);
		}
		else if (part == "move")
		{
			int x, y;
			std::cin >> part >> x >> part >> part >> y;
			move(scramble, x, y);
		}
	}
	std::cout << "Part 1: " << scramble << '\n';
}