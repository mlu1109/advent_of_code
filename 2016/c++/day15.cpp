#include <string>
#include <iostream>
#include <vector>
#include <sstream>

struct Disc
{
	int tot_pos;
	int t0_pos;
};

void solve(const std::vector<Disc> &discs)
{
	bool done = false;
	for (int t = 0; !done; ++t)
	{
		for (int i = 0; i < discs.size(); ++i)
		{
			if ((discs[i].t0_pos + t + (i + 1)) % discs[i].tot_pos != 0)
				break;

			if (i == discs.size() - 1)
			{
				done = true;
				std::cout << t << '\n';
			}
		}
	}
}

int main()
{
	std::vector<Disc> discs;
	std::string line;
	while (std::getline(std::cin, line))
	{
		std::istringstream iss(line);
		std::string part;
		int tot_pos;
		int t0_pos;
		iss >> part >> part >> part >> tot_pos >> part >> part
			>> part >> part >> part >> part >> part >> part;
		part.pop_back();
		t0_pos = std::stoi(part);
		discs.push_back({tot_pos, t0_pos});
	}

	std::cout << "Part 1: "; 
	solve(discs);
	discs.push_back({11, 0});
	std::cout << "Part 2: ";
	solve(discs);
}