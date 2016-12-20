#include "md5.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <unordered_map>

const std::string INPUT = "yjdafjpo";
const int MD5_DIGEST_STR_LENGTH = 32;

bool five_in_a_row(char c, const std::string &md5)
{
	int count = 0;
	for (int i = 0; i < MD5_DIGEST_STR_LENGTH; ++i)
	{
		if (count == 5)
			return true;
		else if (md5[i] == c)
			count += 1;
		else
			count = 0;
	}

	return false;
}

char three_in_a_row(const std::string &md5)
{
	for (int i = 0; i < MD5_DIGEST_STR_LENGTH - 2; ++i)
		if (md5[i] == md5[i + 1] && md5[i] == md5[i + 2])
			return md5[i];

	return '-';
}

void part1()
{
	std::vector<int> key_indices;
	std::string md5_str[2];
	for (int i = 0; key_indices.size() < 64; ++i)
	{
		md5_str[0] = md5(INPUT + std::to_string(i));
		char tiar = three_in_a_row(md5_str[0]);
		if (tiar == '-')
			continue;

		for (int j = i + 1; j < i + 1000; ++j)
		{
			md5_str[1] = md5(INPUT + std::to_string(j));
			if (five_in_a_row(tiar, md5_str[1]))
			{
				key_indices.push_back(i);
				break;
			}
		}
	}

	std::cout << "Part 1: " << key_indices[63] << '\n';
}

std::string hash_2017_times(const std::string &str)
{
	std::string hashed = md5(str);
	for (int i = 0; i < 2016; ++i)
		hashed = md5(hashed);

	return hashed;
}

void part2()
{
	std::vector<int> key_indices;
	std::unordered_map<int, std::string> hashes;
	std::string md5_str[2];
	int reached = 0;
	for (int i = 0; key_indices.size() < 64; ++i)
	{
		if (i < reached)
			md5_str[0] = hashes[i];
		else
			md5_str[0] = hash_2017_times(INPUT + std::to_string(i));

		char tiar = three_in_a_row(md5_str[0]);
		
		if (tiar == '-')
			continue;

		for (int j = i + 1; j < i + 1000; ++j)
		{
			if (j < reached)
				md5_str[1] = hashes[j];
			else
			{
				md5_str[1] = hash_2017_times(INPUT + std::to_string(j));
				hashes[j] = md5_str[1];
				reached = j;
			}

			if (five_in_a_row(tiar, md5_str[1]))
			{
				key_indices.push_back(i);
				break;
			}
		}
	}

	std::cout << "Part 2: " << key_indices[63] << '\n';
} 

int main()
{
	//part1();
	part2();
}