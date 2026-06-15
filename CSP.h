#ifndef CSP_H
#define CSP_H
#include <vector>
using namespace std;

struct CSP
{
    std::vector<std::vector<int>> domains;

    void initializeDomains(int numTasks, int maxTime)
    {
        domains.resize(numTasks + 1);

        for (int i = 1; i <= numTasks; ++i)
        {
            for (int t = 0; t <= maxTime; t++)
            {
            domains[i].push_back(t);
            }
        }
    }
};

#endif