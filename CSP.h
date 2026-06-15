#ifndef CSP_H
#define CSP_H
#include <vector>
using namespace std;

struct CSP
{
<<<<<<< HEAD
    std::vector<std::vector<int>> domains;
=======
    vector<vector<int>> domains;
    vector<int> assignment; 
>>>>>>> bd68843bb30ba30597668316453bfbf9063fc501

    void initializeDomains(int numTasks, int maxTime)
    {
        domains.resize(numTasks + 1);
<<<<<<< HEAD

        for (int i = 1; i <= numTasks; ++i)
=======
        assignment.resize(numTasks + 1, -1);

        for (int i = 1; i <= numTasks; i++)
>>>>>>> bd68843bb30ba30597668316453bfbf9063fc501
        {
            for (int t = 0; t <= maxTime; t++)
            {
            domains[i].push_back(t);
            }
        }
    }
};

#endif