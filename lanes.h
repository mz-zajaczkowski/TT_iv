#ifndef LANES_H
#define LANES_H

#include <bitset>
#include <vector>
#include <iostream>

struct segment
{
    std::vector<char> seg;
    segment(int _val)
    {
        for (int i = 0; i < 8; ++i)
        {
            seg.push_back(_val & (1 << i));
        }
        for (auto elem: seg)
            std::cout << std::bitset<8>(elem) << std::endl;
        std::cout << "============" << std::endl;
    }

    const char& operator [](unsigned int& index)
    {
        return seg[index];
    }
};

int lanes_solution(vector<int>& A)
{
    std::vector<segment> lanes;
    for (auto aElem : A)
    {
        segment seg(aElem);
        lanes.push_back(seg);
    }
    return -1;
}

#endif // LANES_H

