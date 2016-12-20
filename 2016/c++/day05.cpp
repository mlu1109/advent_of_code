#include <openssl/md5.h>
#include <iostream>
#include <vector>
#include <unordered_map>

const std::string INPUT = "cxdnnyjw";

void part1()
{
	unsigned char md5_result[MD5_DIGEST_LENGTH];
	std::vector<int> password;
	for (auto i = 0; password.size() != 8; ++i)
	{
		std::string digest = INPUT + std::to_string(i);
		MD5((const unsigned char*) digest.c_str(), digest.size(), md5_result);
		if (md5_result[0] == 0 && md5_result[1] == 0 && md5_result[2] < 16)
			password.emplace_back(md5_result[2]);
	}

	std::cout << "Part 1: " << std::hex;
	for (int n : password)
		std::cout << n;

	std::cout << std::dec << '\n';
}

void part2()
{
	unsigned char md5_result[MD5_DIGEST_LENGTH];
	std::unordered_map<int, int> password;
	for (int i = 0; password.size() != 8; ++i)
	{
		std::string digest = INPUT + std::to_string(i);
		MD5((const unsigned char*) digest.c_str(), digest.size(), md5_result);
		if (md5_result[0] == 0 && md5_result[1] == 0 && md5_result[2] < 8)
		{
			auto pos = md5_result[2];
			if (!password.count(pos))
				password[pos] = md5_result[3] >> 4;
		}
	}
	
	std::cout << "Part 2: " << std::hex;
	for (int i = 0; i < 8; ++i)
		std::cout << password[i];
	
	std::cout << std::dec << '\n';
}

int main()
{
	part1();
	part2();
}