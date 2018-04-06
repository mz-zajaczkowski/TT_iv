#ifndef LANES_H
#define LANES_H

#include <bitset>
#include <vector>
#include <iostream>
#include <iterator>
#include <cstring>
#include <climits>

using bitset8 = std::bitset<8>;

struct segment
{
    std::vector<char> seg;
    segment(int _val)
    {
        for (int i = 0; i < 8; ++i)
        {
            seg.push_back(static_cast<char>(_val) & (1 << i));
        }
        for (auto elem: seg)
            std::cout << std::bitset<8>(elem) << std::endl;
        std::cout << "============" << std::endl;
    }

    const char& operator [](char index)
    {
        return seg[index];
    }
};

int getShortestPathLen(std::vector<segment>::iterator segListIt, std::vector<segment>::iterator endIt, size_t numSegments)
{
    int minCost = 100000;
    int costMatrix[numSegments][8];
    for (int i = 0; i < numSegments; ++i)
    {
        for(int j = 0; j < 8; ++j)
            costMatrix[i][j] = 100000;
    }
    int segmentCount = 0;

    for (int bit = 0; bit < 8; ++bit)
    {
        if((*segListIt)[bit])
        {

            std::vector<int> adjacents;
            adjacents.push_back(bit);
            costMatrix[0][bit] = 0;
            while (segListIt != endIt && !adjacents.empty())
            {
                ++segListIt;
                ++segmentCount;
                std::vector<int> newAdjacents;
                for (int adj : adjacents)
                {
                    int leftBit = adj + 1;
                    int rightBit = adj - 1;
                    int sourceCost = costMatrix[segmentCount - 1][bit];

                    if (0 == bit && (*segListIt)[leftBit])
                    {
                       (costMatrix[segmentCount])[leftBit] = (sourceCost + 1) <= (costMatrix[segmentCount])[leftBit] ? (sourceCost + 1) : (costMatrix[segmentCount])[leftBit] + 1;
                       newAdjacents.push_back(leftBit);
                    }
                    else if(7 == bit && (*segListIt)[rightBit])
                    {
                        (costMatrix[segmentCount])[rightBit] = (sourceCost + 1) <= (costMatrix[segmentCount])[rightBit] ? (sourceCost + 1) : (costMatrix[segmentCount])[rightBit] + 1;
                        newAdjacents.push_back(rightBit);
                    }

                    if((*segListIt)[bit])
                    {
                        (costMatrix[segmentCount])[adj] = sourceCost < (costMatrix[segmentCount])[adj] ? (sourceCost) : (costMatrix[segmentCount])[adj];
                        newAdjacents.push_back(adj);
                    }
                }
                adjacents.clear();
                adjacents = newAdjacents;
            }
        }
    }
    for(int j = 0; j < 8; ++j)
        minCost = std::min((costMatrix[segmentCount])[j], minCost);
    return minCost;
}

int lanes_solution(vector<int>& A)
{
    if(!A.empty())
    {
        std::vector<segment> segmentList;
        for (int aSeg : A)
            segmentList.push_back(segment(aSeg));

        return getShortestPathLen(segmentList.begin(), segmentList.end(), segmentList.size());
    }
    return -1;
}

#endif // LANES_H

