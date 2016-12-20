#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <bitset>
#include <algorithm>

const int INPUT = 1358;
const int STEPS_MAX = 50;
const uint64_t STEP_X = 1;
const uint64_t STEP_Y = 0x100000000;

uint64_t node(uint32_t x, uint32_t y)
{
	return ((uint64_t) y << 32) | x;
}

uint32_t get_x(uint64_t node)
{
	return node & 0xFFFFFFFF;
}

uint32_t get_y(uint64_t node)
{
	return node >> 32;
}

bool wall(uint64_t node)
{
	auto x = get_x(node);
	auto y = get_y(node);
	auto sum = (x * x + 3 * x) + (2 * x * y) + (y + y * y) + INPUT;
	std::bitset<sizeof(sum) * 8> bits(sum);
	int set_bits = 0;
	for (int i = 0; i < bits.size(); ++i)
		if (bits[i])
			set_bits += 1;
	
	return set_bits % 2;
}

void insert_node(uint64_t node, uint64_t prev, std::unordered_map<uint64_t, int> &steps, std::queue<uint64_t> &q)
{
	if (!wall(node) && !steps[node])
	{
		steps[node] = steps[prev] + 1;
		q.push(node);
	}
}

int main()
{
	std::unordered_map<uint64_t, int> steps;
	std::queue<uint64_t> q;
	auto start = node(1, 1);
	q.push(start);
	steps[start] = 1;
	while (!q.empty())
	{
		auto cur = q.front();
		q.pop();

		if (steps[cur] == STEPS_MAX + 1)
			continue;

		if (get_x(cur) != 0)
			insert_node(cur - STEP_X, cur, steps, q);

		if (get_y(cur) != 0)
			insert_node(cur - STEP_Y, cur, steps, q);

		insert_node(cur + STEP_X, cur, steps, q);
		insert_node(cur + STEP_Y, cur, steps, q);

	}

	std::cout << "Part 2: " << steps.size() << '\n'; 

}