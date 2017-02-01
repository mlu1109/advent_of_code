#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Value
{
	int val;
	bool imm;
};

struct Instruction
{
	char op;
	Value x;
	Value y;
};

bool is_reg(const std::string &val) 
{ 
	return val.find_first_of("abcd") != std::string::npos; 
}

int reg_to_int(const std::string &reg)
{ 
	return reg[0] - 97; 
}

void exec(int *regs, const std::vector<Instruction> &inst)
{
	for (int pc = 0; pc < inst.size(); ++pc)
	{
		const auto &ins = inst[pc];
		auto x = ins.x.imm ? ins.x.val : regs[ins.x.val];
		auto y = ins.y.imm ? ins.y.val : regs[ins.y.val];
		switch(ins.op)
		{
			case 'c':
				regs[ins.y.val] = x;
				break;
			case 'i':
				regs[ins.x.val] += 1;
				break;
			case 'd':
				regs[ins.x.val] -= 1;
				break;
			case 'j':
				if (x != 0) 
					pc += y - 1;
				break;
			default:
				throw;
		}
	}
}

int main()
{
	std::vector<Instruction> inst;
	std::string line;
	
	while (std::getline(std::cin, line))
	{
		std::istringstream iss(line);
		std::string token[3];
		for (int i = 0; iss >> token[i]; ++i);
		
		Value x;
		x.imm = !is_reg(token[1]);
		x.val = x.imm ? std::stoi(token[1]) : reg_to_int(token[1]);
		Value y;
		if (!token[2].empty())
		{
			y.imm = !is_reg(token[2]);
			y.val = y.imm ? std::stoi(token[2]) : reg_to_int(token[2]);
		}
		
		inst.push_back(Instruction{token[0][0], x, y});
	}

	int regs_1[4] {0, 0, 0, 0};
	exec(regs_1, inst);
	int regs_2[4] {0, 0, 1, 0};
	exec(regs_2, inst);
	std::cout << "Part 1: " << regs_1[0] << '\n' 
		      << "Part 2: " << regs_2[0] << '\n';
}