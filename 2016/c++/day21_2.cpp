#include <string>
#include <sstream>
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
	rotate(str, x_pos + 1);

	if (x_pos > 3)
		rotate(str, 1);
}

// Original <=> Rotated by a
// a------- <=> -a------ -1
// -a------ <=> ---a---- -2
// --a----- <=> -----a-- -3
// ---a---- <=> -------a -4
// ----a--- <=> --a----- -2
// -----a-- <=> ----a--- +1
// ------a- <=> ------a-  0
// -------a <=> a------- -1

void undo_rotate(std::string &str, char x)
{
	int o_pos[8] = {-1, -1, 2, -2, 1, -3, 0, -4};
	int x_pos = str.find(x);
	rotate(str, o_pos[x_pos]);
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
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(std::cin, line))
		lines.push_back(line);

	std::string part;
	std::string unscramble = "fbgdceah";
	for (auto rit = lines.rbegin(); rit != lines.rend(); ++rit)
	{
		std::istringstream iss(*rit);
		while (iss >> part)
		{
			if (part == "swap")
			{
				iss >> part;
				if (part == "letter")
				{
					char x, y;
					iss >> x >> part >> part >> y;
					swap(unscramble, y, x);
				}
				else // part == "position"
				{
					int x, y;
					iss >> x >> part >> part >> y;
					swap(unscramble, y, x);
				}
	
			}
			else if (part == "rotate")
			{
				iss >> part;
				if (part == "based")
				{
					char x;
					iss >> part >> part >> part >> part >> x;
					undo_rotate(unscramble, x);
				}
				else // part == "left" || part == "right"
				{
					int x;
					iss >> x;
					if (part == "left")
						x *= -1;

					rotate(unscramble, -x);
					iss >> part;
				}
			}
			else if (part == "reverse")
			{
				int x, y;
				iss >> part >> x >> part >> y;
				reverse(unscramble, x, y);
			}
			else if (part == "move")
			{
				int x, y;
				iss >> part >> x >> part >> part >> y;
				move(unscramble, y, x);
			}
		}
	}
	std::cout << "Part 2: " << unscramble << '\n';
}