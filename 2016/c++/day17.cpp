#include "md5.hpp"
#include <vector>
#include <algorithm>

const std::string INPUT = "njfxhljp";
const int ROWS = 4;
const int COLS = 4;

struct Node
{
	int x;
	int y;

	bool operator==(const Node &rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}
};

void queue_moves(const std::string &path, const Node &node, std::vector<std::pair<std::string, Node>> &q)
{
	std::string digest = md5(INPUT + path);
	for (int i = 0; i < 4; ++i)
	{
		if (digest[i] > 97 && digest[i] < 103)
		{
			if (i == 0 && node.y != 0)
				q.push_back({path + 'U', Node{node.x, node.y - 1}});
			else if (i == 1 && node.y != ROWS - 1)
				q.push_back({path + 'D', Node{node.x, node.y + 1}});
			else if (i == 2 && node.x != 0)
				q.push_back({path + 'L', Node{node.x - 1, node.y}});
			else if (i == 3 && node.x != COLS - 1)
				q.push_back({path + 'R', Node{node.x + 1, node.y}});
		}
	}
}

void part1()
{
	std::vector<std::pair<std::string, Node>> q;
	const Node START{0, 0};
	const Node GOAL{3, 3};
	q.push_back({"", START});
	auto sort = [](const std::pair<std::string, Node> &rhs, const std::pair<std::string, Node> &lhs)
	{
		return rhs.first.size() > lhs.first.size();
	};
	while (!q.empty())
	{
		std::sort(q.begin(), q.end(), sort);
		auto p = q.back();
		const auto &path = p.first;
		const auto &node = p.second;
		if (node == GOAL)
			break;

		q.pop_back();
		queue_moves(path, node, q);
	}

	std::cout << "Part 1: " << q.back().first << '\n';
}

void part2()
{
	std::vector<std::pair<std::string, Node>> q;
	std::vector<std::string> paths;
	const Node START{0, 0};
	const Node GOAL{3, 3};
	q.push_back({"", START});
	while (!q.empty())
	{
		auto p = q.back();
		q.pop_back();
		const std::string &path = p.first;
		const Node &node = p.second;
		if (node == GOAL)
			paths.push_back(path);
		else
			queue_moves(path, node, q);
	}

	auto sort = [](std::string &rhs, const std::string &lhs)
	{
		return rhs.size() < lhs.size();
	};
	std::sort(paths.begin(), paths.end(), sort); 
	std::cout << "Part 2: " << paths.back().size() << '\n';
}

int main()
{
	part1();
	part2();
}