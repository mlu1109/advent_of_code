#include <iostream>
#include <string>
#include <queue>
#include <array>
#include <ctime>	// clock
#include <unordered_map>
#include <unistd.h> // usleep

const int ITEMS = 14;
const uint64_t MAX = 0xFFFFFFFFFFFFFFFF;

struct Floors
{
	uint8_t elevator_ = 0; 				// Floor number of elevator
// 	std::array<uint8_t, ITEMS> items_{ 	// Floor number of item
// 		{1, 0, 2, 0}
// 	};

//	std::array<uint8_t, ITEMS> items_{
//		{0, 0, 1, 2, 1, 2, 1, 2, 1, 2}
//	};

	std::array<uint8_t, ITEMS> items_{
		{0, 0, 1, 2, 1, 2, 1, 2, 1, 2, 0, 0, 0, 0}
	};

	Floors() { };

	Floors(uint64_t state) 
	{
		elevator_ = (uint8_t) (state >> 60);
		for (auto i = 0; i < ITEMS; ++i)
			items_[i] = (uint8_t) ((state >> (4 * i)) & 0xF);
	}

	bool goal()
	{
		for (auto i = 0; i < ITEMS; ++i)
			if (items_[i] != 3)
				return false;

		return true;
	}

	bool valid(uint8_t elevator, const std::array<uint8_t, ITEMS> &items)
	{
		if (elevator > 3)
			return false;

		for (auto i = 1; i < ITEMS; i += 2)
		{
			if (items[i - 1] == items[i])
				continue;
			
			for (auto j = 0; j < ITEMS; j += 2)
				if (items[i] == items[j])
					return false;				
		}
		return true;
	}

	uint64_t bin_rep(uint8_t elevator, const std::array<uint8_t, ITEMS> &items)
	{
		uint64_t rep = (uint64_t) elevator << 60;
		for (auto i = 0; i < ITEMS; ++i)
			rep |= (uint64_t) items[i] << (i * 4);

		return rep;
	}

	uint64_t bin_rep()
	{
		return bin_rep(elevator_, items_);
	}

	std::vector<uint64_t> valid_states()
	{
		uint8_t elevator = elevator_;
		std::array<uint8_t, ITEMS> items = items_;
		std::vector<uint64_t> states;

		// Move one up
		elevator += 1;
		for (auto i = 0; i < ITEMS; ++i)
		{
			// No item on floor, skip
			if (elevator_ != items_[i])	
				continue;

			items[i] += 1;
			if (valid(elevator, items))
				states.push_back(bin_rep(elevator, items));

			// Move two up
			for (auto j = i + 1; j < ITEMS; ++j)
			{
				if (elevator_ != items_[j])	
					continue;
				
				items[j] += 1;
				if (valid(elevator, items))
					states.push_back(bin_rep(elevator, items));
				
				items[j] -= 1;
			}

			items[i] -= 1;
		}

		// Move one down
		elevator -= 2;
		for (auto i = 0; i < ITEMS; ++i)
		{
			// No item on floor, skip
			if (elevator_ != items_[i])	
				continue;

			items[i] -= 1;
			if (valid(elevator, items))
				states.push_back(bin_rep(elevator, items));
			
			// Move two down
			for (auto j = i + 1; j < ITEMS; ++j)
			{
				if (elevator_ != items_[j])	
					continue;

				items[j] -= 1;
				if (valid(elevator, items))
					states.push_back(bin_rep(elevator, items));
				
				items[j] += 1;
			}

			items[i] += 1;
		}

		return states;
	}

    void print() const
    {
        for (auto r = 4; r > 0; --r)
        {
            std::cout << "F" << r << ((r - 1) == elevator_ ? " E " : " . ");
            for (auto c = 0; c < ITEMS; ++c)
                std::cout << (items_[c] == (r - 1) ? (c % 2 == 0 ? 'G' : 'M') : '.') << " ";
            
            std::cout << '\n';
        }
    }

};

int main()
{
	auto begin_t = clock();
	std::unordered_map<uint64_t, uint64_t> parent;
	std::queue<uint64_t> q;
	q.push(Floors().bin_rep());
	parent[Floors().bin_rep()] = MAX;
	auto iter = 0;

	while (!q.empty())
	{
		auto p = q.front();
		Floors cur(p);
		if (cur.goal())
			break;

		q.pop();
		std::vector<uint64_t> moves = cur.valid_states();
		for (auto bin_rep : moves)
		{
			if (!parent[bin_rep])
			{
				parent[bin_rep] = p;
				q.push(bin_rep);
			}
		}

		iter += 1;
	}	

	std::vector<Floors> path;
	Floors cur(q.front());
	while (parent[cur.bin_rep()] != MAX)
	{
		path.push_back(cur);
		cur = Floors(parent[cur.bin_rep()]);
	}

	auto runtime = double(clock() - begin_t) / CLOCKS_PER_SEC;
	for (auto rit = path.rbegin(); rit != path.rend(); ++rit)
	{
		system("clear");
		std::cout << std::string(4 + ITEMS * 2, '-') << '\n';
		rit->print();
		std::cout << std::string(4 + ITEMS * 2, '-') << '\n'
				  << "Steps: " << path.size() << '\n'
			  	  << "Iterations: " << iter << '\n'
			      << "Runtime: " << runtime << "s\n";
		usleep(500000);
	}
}
