#ifndef TASK_H
#define TASK_H
#include <vector>

using namespace std;
struct Task
{
    int id;
    int duration;
    int resource_demand;
    vector<int> dependencies;
};

#endif