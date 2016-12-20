#include <string>
#include <iostream>
#include <algorithm>

const std::string INPUT = ".^..^....^....^^.^^.^.^^.^.....^.^..^...^^^^^^.^^^^.^.^^^^^^^.^^^^^..^.^^^.^^..^.^^.^....^.^...^^.^.";
const int COLS = INPUT.size();
const int ROWS = 400000;

bool left(int r, int c, const std::string &tiles)
{
	return (c == 0 ? false : tiles[(r - 1) * COLS + c - 1] == '^');
}

bool center(int r, int c, const std::string &tiles)
{
	return tiles[(r - 1) * COLS + c] == '^';
}

bool right(int r, int c, const std::string &tiles)
{
	return (c == COLS - 1 ? false : tiles[(r - 1) * COLS + c + 1] == '^');
}

bool is_trap(int r, int c, const std::string &tiles)
{
	if (left(r, c, tiles) && center(r, c, tiles) && !right(r, c, tiles))
		return true;
	else if (center(r, c, tiles) && right(r, c, tiles) && !left(r, c, tiles))
		return true;
	else if (left(r, c, tiles) && !center(r, c, tiles) && !right(r, c, tiles))
		return true;
	else if (right(r, c, tiles) && !left(r, c, tiles) && !center(r, c, tiles))
		return true;

	return false;
}

int main()
{
	std::string tiles = INPUT;
	for (int r = 1; r < ROWS; ++r)
		for (int c = 0; c < COLS; ++c)
			tiles += is_trap(r, c, tiles) ? '^' : '.';

	int safe = 0;
	for (const auto &c : tiles)
		if (c == '.')
			safe += 1;

	std::cout << safe << '\n';
}