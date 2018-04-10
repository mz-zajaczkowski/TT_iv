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
//        for (auto elem: seg)
//            std::cout << std::bitset<8>(elem) << std::endl;
//        std::cout << "============" << std::endl;
    }

    const char& operator [](char index)
    {
        return seg[index];
    }
};

int getShortestPathLen(std::vector<segment> segmentList)
{
    int minCost = 100000;
    int numSegments = segmentList.size();
    int costMatrix[numSegments][8];
    std::vector<segment>::iterator segListIt = segmentList.begin();
    std::vector<segment>::iterator endIt = segmentList.end();
    for (int i = 0; i < numSegments; ++i)
    {
        for(int j = 0; j < 8; ++j)
            costMatrix[i][j] = 100000;
    }
    int segmentCount = 0;

    for (int bit = 0; bit < 8; ++bit)
    {
        segListIt = segmentList.begin();
        segmentCount = 0;
        if((*segListIt)[bit])
        {

            std::vector<int> adjacents;
            adjacents.push_back(bit);
            costMatrix[0][bit] = 0;
            while ((segListIt != (endIt - 1)) && !adjacents.empty())
            {
                ++segListIt;
                ++segmentCount;
                std::vector<int> newAdjacents;
                for (int adj : adjacents)
                {
                    int leftBit = adj + 1;
                    int rightBit = adj - 1;
                    int sourceCost = costMatrix[segmentCount - 1][adj];

                    if (0 == adj && (*segListIt)[leftBit])
                    {
                        if ((sourceCost + 1) < (costMatrix[segmentCount])[leftBit])
                            (costMatrix[segmentCount])[leftBit] = sourceCost + 1;
                        newAdjacents.push_back(leftBit);
                    }
                    else if(7 == adj && (*segListIt)[rightBit])
                    {
                        if ((sourceCost + 1) < (costMatrix[segmentCount])[rightBit])
                            (costMatrix[segmentCount])[rightBit] = sourceCost + 1;
                        newAdjacents.push_back(rightBit);
                    }
                    else
                    {
                        if((*segListIt)[rightBit])
                        {
                            if ((sourceCost + 1) < (costMatrix[segmentCount])[rightBit])
                                (costMatrix[segmentCount])[rightBit] = sourceCost + 1;
                            newAdjacents.push_back(rightBit);
                        }
                        if((*segListIt)[leftBit])
                        {
                            if ((sourceCost + 1) < (costMatrix[segmentCount])[leftBit])
                                (costMatrix[segmentCount])[leftBit] = sourceCost + 1;
                            newAdjacents.push_back(leftBit);
                        }
                    }
                    if((*segListIt)[adj])
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
        minCost = std::min((costMatrix[numSegments - 1])[j], minCost);
    return minCost;
}

int lanes_solution(vector<int>& A)
{
    if(!A.empty())
    {
        std::vector<segment> segmentList;
        for (int aSeg : A)
        {
            std::cout << bitset8(aSeg) << "\n";
            segmentList.push_back(segment(aSeg));
        }

        return getShortestPathLen(segmentList);
    }
    return -1;
}

#endif // LANES_H

