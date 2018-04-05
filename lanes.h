#ifndef LANES_H
#define LANES_H

#include <bitset>
#include <vector>
#include <iostream>
#include <iterator>

using bitset8 = std::bitset<8>;
struct vertex
{
    int row;
    int col;
    vertex(int _r, int _c)
        : row(_r)
        , col(_c)
    {}
    vertex()
    {
        row = 0;
        col = 0;
    }

    bool operator ==(const vertex &other)
    {
        if (this == &other
                || (row == other.row
                    && col == other.col))
            return true;
        return false;
    }

    bool operator !=(const vertex &other)
    {
        return !(this == &other);
    }
};
struct edge
{
    vertex from;
    vertex to;
    int weight;
    edge(vertex _f, vertex _t, int _w)
        : from(_f)
        , to(_t)
        , weight(_w)
    {}
};

struct graph
{
    void addVertice(vertex v)
    {
        if (!vertices.empty())
        {
            for (vertex vv : vertices)
            {
                if (vv == v)
                    return;
            }
        }

        vertices.push_back(v);
    }

    bool addEdge(edge edge)
    {
        bool vFound = false, uFound = false;
        for(vertex vv : vertices)
        {
            if(edge.from == vv)
                vFound = true;
            if(edge.to == vv)
                uFound = true;
        }

        return vFound && uFound;
    }
    graph() {}

private:
    std::vector<vertex> vertices;
    //                            weight
    std::vector<edge> edges;
};

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
std::vector<vertex> addAdjacents(graph &G, std::vector<segment>::iterator segListIt, int segmentCount, vertex source, char bit)
{
    segment currentSeg = *segListIt;
    char leftBit = bit + 1;
    char rightBit = bit - 1;
    vertex adj, leftAdj, rightAdj;
    std::vector<vertex> adjacents;

    if (0 == bit && (*segListIt)[leftBit])
    {
       leftAdj = {segmentCount, leftBit};
       G.addVertice(leftAdj);
       G.addEdge(edge(source, leftAdj, 1));
       adjacents.push_back(leftAdj);
    }
    else if(7 == bit && currentSeg[rightBit])
    {
        rightAdj = {segmentCount, rightBit};
        G.addVertice(rightAdj);
        G.addEdge(edge(source, rightAdj, 1));
        adjacents.push_back(rightAdj);
    }

    if(currentSeg[bit])
    {
        adj = {segmentCount, bit};
        G.addVertice(adj);
        G.addEdge(edge(source, adj, 0));
        adjacents.push_back(adj);
    }
    return adjacents;
}

graph constructGraph(std::vector<segment> segmentList, char bit)
{
    graph G;
    auto segListIt = segmentList.begin();
    int segmentCount = 0;
    if((*segListIt)[bit])
    {
        vertex source(0, bit);
        G.addVertice(source);
        ++segListIt;
        ++segmentCount;
        std::vector<vertex> adjacents = addAdjacents(G, segListIt, segmentCount, source, bit);

        while (segListIt != segmentList.end() && !adjacents.empty())
        {
            ++segListIt;
            ++segmentCount;
            std::vector<vertex> newAdjacents;
            for (vertex adj : adjacents)
            {
                std::vector<vertex> tmpAdjacents = addAdjacents(G, segListIt, segmentCount, adj, bit);
                newAdjacents.insert(newAdjacents.end(), tmpAdjacents.begin(), tmpAdjacents.end());
            }
            adjacents.clear();
            adjacents = newAdjacents;
        }
    }
}

int lanes_solution(vector<int>& A)
{
    std::vector<segment> segmentList;
    std::vector<graph> graphList;
    for (int aSeg : A)
        segmentList.push_back(segment(aSeg));
    for (int bit = 0; bit < 8; ++bit)
    {
        int segCount = 0;
        for(segment seg : segmentList)
        {
            if(seg[bit] > 0)
            {
                graph G;
                G.addVertice(vertex(segCount, bit));
            }
            ++segCount;
        }
    }
    return -1;
}

#endif // LANES_H

