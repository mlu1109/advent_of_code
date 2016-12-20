#include <string>
#include <vector>
#include <iostream>
#include <fstream>

struct Screen
{
	bool pixels[6][50] = {{false}};
	void rect(int col, int row) 
	{
		row %= 7;
		col %= 51;
		for (int r = 0; r < row; ++r)
			for (int c = 0; c < col; ++c)
				pixels[r][c] = true;
	}

	void rotCol(int col, int rot)
	{
		rot %= 6;
		while (rot-- > 0)
		{
			bool last = pixels[5][col];
			for (int r = 5; r > 0; --r)
				pixels[r][col] = pixels[r - 1][col];

			pixels[0][col] = last;
		}
	}

	void rotRow(int row, int rot)
	{
		rot %= 50;
		while (rot-- > 0)
		{
			bool last = pixels[row][49];
			for (int c = 49; c > 0; --c)
				pixels[row][c] = pixels[row][c - 1];

			pixels[row][0] = last;
		}
	}

	void print()
	{
		for (int r = 0; r < 6; ++r)
		{
			for (int c = 0; c < 50; ++c)
				std::cout << (pixels[r][c] ? '#' : '.');

			std::cout << '\n';
		}
	}

	void count()
	{
		int cnt = 0;
		for (int r = 0; r < 6; ++r)
			for (int c = 0; c < 50; ++c)
				if (pixels[r][c])
					++cnt;

		std::cout << cnt << '\n';
	}
};

int main(int argc, char const *argv[])
{
	std::string cmd;
	Screen scr;
	while (std::cin >> cmd)
	{
		if (cmd == "rect")
		{
			std::cin >> cmd;
			auto x = cmd.find('x');
			scr.rect(
				std::stoi(cmd.substr(0, x)),
				std::stoi(cmd.substr(x + 1))
			);
		}
		else // cmd == rotate
		{
			std::string dir;
			std::cin >> dir;
			std::cin >> cmd;
			int rc = std::stoi(cmd.substr(2));
			std::cin >> cmd >> cmd;
			int rot = std::stoi(cmd);
			if (dir == "column")
				scr.rotCol(rc, rot);
			else // dir == row
				scr.rotRow(rc, rot);
		}
	}

	std::cout << "Part 1: ";
	scr.count();
	std::cout << "Part 2\n------\n";
	scr.print();
}