#ifndef TASK_H
#define TASK_H
#include<vector>

using namespace std;
struct Task{
    int id;
    int duration;
    int resource;
    vector<int>dependencies;
};
#endif