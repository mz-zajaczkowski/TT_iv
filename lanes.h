#ifndef LANES_H
#define LANES_H

#include <bitset>
#include <vector>
#include <iostream>

using bitset8 = std::bitset<8>;

int lanes_solution(vector<int>& A)
{
    uint32_t cost = 100000;
    std::vector<int> visited(A);

    typedef std::pair<unsigned int, unsigned int> address;
    typedef std::vector<address> path;
    typedef std::pair<path, unsigned int> pathCost;
    if (!A.empty())
    {
        bool naive = false;
        for (auto aElem : A)
        {
            std::cout << bitset8(static_cast<char>(aElem)) << std::endl;
        }
        for(int i = 0; i < 8 && !naive; ++i)
        {
            int mask = 1 << i;
            for(auto segment : A)
            {
                mask = segment & mask;
            }
            if (mask == 1 << i)
                naive = true;
        }
        if(!naive)
        {
            for(int i = 0; i < 8 && !naive; ++i)
            {
                char currentMask = 1 << i;
                char otherMaskLeft = 0;
                char otherMaskRight = 0;
                if (0 == i)
                    otherMaskLeft = 1 << (i + 1);
                else if (7 == i)
                    otherMaskRight = 1 << (i - 1);
                else
                {
                    otherMaskLeft = (1 << (i + 1));
                    otherMaskRight = (1 << (i - 1));
                }
                std::cout << "currentMask: " << bitset8(currentMask) << std::endl;
                std::cout << "otherMaskLeft: " << bitset8(otherMaskLeft) << std::endl;
                std::cout << "otherMaskRight: " << bitset8(otherMaskRight) << std::endl;

            }
        }
        else
            return 0;


    }
    return -1;
}

#endif // LANES_H

