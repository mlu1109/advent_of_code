#include <string>
#include <iostream>
#include <vector>

struct Node
{
	int x;
	int y;
	int size;
	int used;
	int avail;

	bool operator!=(const Node &rhs)
	{
		return rhs.x != x || rhs.y != y;
	}
};

std::ostream& operator<<(std::ostream &os, const Node &n)
{
	os << '(' << n.x << ", " << n.y << "): " << n.size << "T " << n.used << "T " << n.avail << 'T'; 
	return os;
}

int main()
{
	std::string part;
	std::getline(std::cin, part);
	std::getline(std::cin, part);
	std::vector<Node> nodes;
	while(std::cin >> part)
	{
		int delim_0 = part.find('-');
		int delim_1 = part.find('-', delim_0 + 1);
		int x = std::stoi(part.substr(delim_0 + 2, delim_1 - delim_0 - 2));
		int y = std::stoi(part.substr(delim_1 + 2));
		std::cin >> part;
		part.pop_back();
		int size = std::stoi(part);
		std::cin >> part;
		part.pop_back();
		int used = std::stoi(part);
		std::cin >> part;
		part.pop_back();
		int avail = std::stoi(part);
		std::cin >> part;
		nodes.push_back(Node{x, y, size, used, avail});
	}

	int viable_pairs = 0;
	for (int a = 0; a < nodes.size(); ++a)
		for (int b = 0; b < nodes.size(); ++b)
			if (nodes[a].used > 0 && nodes[b].avail >= nodes[a].used && nodes[a] != nodes[b])
				++viable_pairs;

	std::cout << "Part 1: " << viable_pairs << '\n';

}