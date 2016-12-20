#include <iostream>
#include <string>
#include <queue>
#include <unordered_set>
#include <array>
#include <time.h>

const int ITEMS = 14;
 
struct Floors
{
    uint8_t elevator_ = 0;              // Floor number of elevator
    uint64_t bin_rep_;
//  std::array<uint8_t, ITEMS> items_{  // Floor number of item
//      {1, 0, 2, 0}
//  };
 
//  std::array<uint8_t, ITEMS> items_{
//      {0, 0, 1, 2, 1, 2, 1, 2, 1, 2}
//  };
 
    std::array<uint8_t, ITEMS> items_{
        {0, 0, 1, 2, 1, 2, 1, 2, 1, 2, 0, 0, 0, 0}
    };
 
    Floors() { };
 
    Floors(uint64_t state)
    {
        elevator_ = (uint8_t) (state >> 60);
        for (int i = 0; i < ITEMS; ++i)
            items_[i] = (uint8_t) ((state >> 4 * i) & 0xF);
    }
 
    bool goal()
    {
        for (int i = 0; i < ITEMS; ++i)
            if (items_[i] != 3)
                return false;
 
        return true;
    }
 
    bool valid(uint8_t elevator, const std::array<uint8_t, ITEMS> &items)
    {
        if (elevator > 3)
            return false;
 
        for (int i = 1; i < ITEMS; i += 2)
        {
            if (items[i - 1] == items[i])
                continue;
           
            for (int j = 0; j < ITEMS; j += 2)
                if (items[i] == items[j])
                    return false;              
        }

        return true;
    }
 
    uint64_t bin_rep(uint8_t elevator, const std::array<uint8_t, ITEMS> &items)
    {
        uint64_t rep = (uint64_t) elevator << 60;
        for (int i = 0; i < ITEMS; ++i)
            rep |= (uint64_t) items[i] << i * 4;
 
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
        for (int i = 0; i < ITEMS; ++i)
        {
            // No item on floor, skip
            if (elevator_ != items_[i])
                continue;
 
            items[i] += 1;
            if (valid(elevator, items))
                states.push_back(bin_rep(elevator, items));

            // Move two up
            for (int j = i + 1; j < ITEMS; ++j)
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
        for (int i = 0; i < ITEMS; ++i)
        {
            // No item on floor, skip
            if (elevator_ != items_[i])
                continue;
 
            items[i] -= 1;
            if (valid(elevator, items))
                states.push_back(bin_rep(elevator, items));
           
            // Move two down
            for (int j = i + 1; j < ITEMS; ++j)
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
 
    void print()
    {
        for (int r = 0; r < 4; ++r)
        {
            std::cout << "F" << r << (r == elevator_ ? " E " : " - ");
            for (int c = 0; c < ITEMS; ++c)
                std::cout << (items_[c] == r ? (c % 2 == 0 ? 'G' : 'M') : '-') << " ";
            
            std::cout << '\n';
        }
    }
};
 
int main()
{
    auto begin_t = clock();
    std::queue<std::pair<uint64_t, int>> q;
    std::unordered_set<uint64_t> visited;
    q.push({Floors().bin_rep(), 0});
    int iter = 0;
    while (!q.empty())
    {
        auto p = q.front();
        Floors cur(p.first);
        if (cur.goal())
            break;

        q.pop();
        std::vector<uint64_t> moves = cur.valid_states();
        for (uint64_t bin_rep : moves)
        {
            if (!visited.count(bin_rep))
            {
                q.push({bin_rep, p.second + 1});
                visited.insert(bin_rep);
            }
        }
 
        iter += 1;
    }
 
    std::cout << "Steps: " << q.front().second << '\n'
              << "Iterations: " << iter << '\n'
              << "Runtime: " << double(clock() - begin_t) / CLOCKS_PER_SEC << '\n';
}