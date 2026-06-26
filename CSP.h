#ifndef CSP_H
#define CSP_H
#include <vector>
using namespace std;

struct CSP
{
    vector<vector<int>> domains;
    vector<int> assignment; 
    int resourceLimit;

    void initializeDomains(int numTasks, int maxTime)
    {
        domains.resize(numTasks + 1);
        assignment.resize(numTasks + 1, -1);

        for (int i = 1; i <= numTasks; i++)
        {
            for (int t = 0; t <= maxTime; t++)
            {
                domains[i].push_back(t);
            }
        }
    }
};

#endif