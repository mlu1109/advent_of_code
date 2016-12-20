#include <iostream>
#include <vector>
#include <sstream>
#include <utility>

struct Bot
{
	int val = -1;
	bool low_output = false;
	int low = -1;
	bool high_output = false;
	int high = -1;
};

void goes_to(int bot_nr, int val, std::vector<Bot> &bots, std::vector<int> &outputs)
{
	Bot &cur_bot = bots[bot_nr];
	if (cur_bot.val == -1)
		cur_bot.val = val;
	else
	{
		int highest = val < cur_bot.val ? cur_bot.val : val;
		int lowest = val < cur_bot.val ? val : cur_bot.val;
		if (highest == 61 && lowest == 17)
			std::cout << "Part 1: " << bot_nr << '\n';

		cur_bot.val = -1;

		if (cur_bot.low_output)
			outputs[cur_bot.low] += lowest;
		else
			goes_to(cur_bot.low, lowest, bots, outputs);

		if (cur_bot.high_output)
			outputs[cur_bot.high] += highest;
		else
			goes_to(cur_bot.high, highest, bots, outputs);
	}
}

int main()
{	
	std::vector<Bot> bots(300);
	std::vector<std::pair<int, int>> goes;
	std::string line;
	while (std::getline(std::cin, line))
	{
		std::string part;
		std::istringstream iss(line);
		iss >> part;
		if (part == "value")
		{
			int bot_nr;
			int val;
			iss >> val >> part >> part >> part >> bot_nr;
			goes.push_back(std::pair<int, int>(bot_nr, val));
		}
		else if (part == "bot")
		{
			int bot_nr;
			int low;
			int high;
			std::string low_goes;
			std::string high_goes;
			iss >> bot_nr >> part >> part >> part >> low_goes
				>> low >> part >> part >> part >> high_goes
				>> high;
			bots[bot_nr].low_output = low_goes == "output";
			bots[bot_nr].low = low;
			bots[bot_nr].high_output = high_goes == "output";
			bots[bot_nr].high = high;
		}
	}

	std::vector<int> outputs(20);
	for (auto &v : goes)
		goes_to(v.first, v.second, bots, outputs);

	std::cout << "Part 2: " << outputs[0] * outputs[1] * outputs[2] << '\n';
}