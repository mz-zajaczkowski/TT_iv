#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cassert>
#include "intersections.h"
#include "lanes.h"
using namespace std;

struct InstalledPackage
{
    string region;
    uint32_t version;
};
struct CatalogEntry: public InstalledPackage
{
    uint32_t size;

    friend ostream& operator <<(ostream& os, CatalogEntry& entry)
    {
        os << "region: " << entry.region << endl;
        os << "version: " << entry.version << endl;
        os << "size: " << entry.size << endl;
        return os;
    }
};
typedef vector<CatalogEntry> Catalog;
typedef vector<InstalledPackage> PackageList;
int solution(string& S, string& T, string& U)
{
    stringstream ssCat {S};
    stringstream ssPackages {T};
    string sRegion {U};
    string sCatEntry;
    Catalog catalog;
    PackageList packageList;
    uint32_t upgradeSize = 0;
    while(std::getline(ssCat, sCatEntry))
    {
        CatalogEntry entry;
        std::replace(sCatEntry.begin(), sCatEntry.end(), ',', ' ');
        cout << sCatEntry << endl;
        istringstream iss {sCatEntry};
        iss >> entry.region;
        string tmp;
        iss >> tmp;
        entry.version = stoul(tmp);
        tmp.clear();
        iss >> tmp;
        entry.size = stoul(tmp);
        cout << entry;
        //make sure it's the same region
        if (0 == sRegion.compare(entry.region))
            catalog.push_back(entry);
    }
    string sPack;
    while(std::getline(ssPackages, sPack))
    {
        std::replace(sPack.begin(), sPack.end(), ',', ' ');
        InstalledPackage package;
        istringstream packStream {sPack};
        packStream >> package.region;
        string tmpVer;
        packStream >> tmpVer;
        package.version = stoul(tmpVer);
        //save only if in the same region
        if (0 == sRegion.compare(package.region))
            packageList.push_back(package);
    }
    if (catalog.empty() || packageList.empty())
        return -1;
    else
    {
        for(auto package: packageList)
        {
            for(auto entry: catalog)
            {
                if (package.version < entry.version)
                    upgradeSize += entry.size;
            }
        }
    }

    return upgradeSize;
}

void check_intersections(int X, int Y, int expectedResult)
{
    cout << "(" << X << ", " << Y << "): " << intersection_solution(X, Y) << endl;
    assert(intersection_solution(X, Y) == expectedResult);
}

void check_lanes(vector<int> A, int expectedResult)
{
    cout << "A: [ ";
    std::copy(A.begin(), A.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << " ]" << endl;
    std::cout << "Expected result: " << expectedResult << endl;
    assert(lanes_solution(A) == expectedResult);
}

int main()
{
    string S {"Netherlands,1,25000"};
    string T {"Netherlands,1\nBelgium,2"};
    string U {"Netherlands"};
//    cout << solution(S, T, U) << endl;

    check_intersections(270, 29, -90);
    check_intersections(29, 270, 90);
    check_intersections(290, 270, 180);
    check_intersections(270, 290, 180);
    check_intersections(270, 135, 30);
    check_intersections(135, 270, -30);
    check_intersections(170, 120, 135);
    check_intersections(120, 170, -135);
    check_intersections(5, 200, 0);
    check_intersections(200, 5, 0);


    vector<int> emptyVec;
    check_lanes(emptyVec, -1);
    vector<int> A {7, 11, 10, 4};
    check_lanes(A, 1);
    vector<int> B {9, 11, 10, 8};
    check_lanes(B, 0);
    return 0;
}
