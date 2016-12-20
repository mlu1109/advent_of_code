#include <iostream>
#include <string>

std::string INPUT = "01110110101001000";
const int DISK_SIZE = 35651584;

std::string reverse_flip_bits(const std::string &bits)
{
	std::string result;
	for (auto rit = bits.rbegin(); rit != bits.rend(); ++rit)
		result.push_back(*rit == '0' ? '1' : '0');

	return result;
}

std::string fill_disk(const std::string &bits)
{
	std::string a = bits;
	while (a.size() < DISK_SIZE)
	{
		std::string b = reverse_flip_bits(a);
		a += '0' + b;
	}

	a = a.substr(0, DISK_SIZE);
	return a;
}

int main()
{
	std::string disk = fill_disk(INPUT);
	int iter = 0;
	std::string checksum;
	while (checksum.size() % 2 == 0 && disk.size() % 2 == 0)
	{
		const std::string &s = iter % 2 == 0 ? disk : checksum;
		std::string &d = iter % 2 == 0 ? checksum : disk;
		d.clear();
		for (int i = 0; i < s.size(); i += 2)
			d += s[i] == s[i + 1] ? '1' : '0';

		++iter;
	}

	std::cout << (disk.size() < checksum.size() ? disk : checksum) << '\n';

}