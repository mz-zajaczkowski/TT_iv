#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
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
    stringstream sCat {S};
    stringstream sPackages {T};
    string region {U};
    string sCatEntry;
    Catalog catalog;
    PackageList packageList;
    uint32_t upgradeSize = 0;
    while(std::getline(sCat, sCatEntry))
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
        if (0 == region.compare(entry.region))
            catalog.push_back(entry);
    }
    string sPack;
    while(std::getline(sPackages, sPack))
    {
        std::replace(sPack.begin(), sPack.end(), ',', ' ');
        InstalledPackage package;
        istringstream packStream {sPack};
        packStream >> package.region;
        string tmpVer;
        packStream >> tmpVer;
        package.version = stoul(tmpVer);
        //save only if in the same region
        if (0 == region.compare(package.region))
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

int main()
{
    string S {"Netherlands,1,25000\nNetherlands,2,3000\nNetherlands,3,1000\nBelgium,4,50000"};
    string T {"Netherlands,1\nBelgium,2"};
    string U {"Belgium"};
    cout << solution(S, T, U) << endl;
    return 0;
}
