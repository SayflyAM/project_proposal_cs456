#ifndef PARSER_H
#define PARSER_H

#include<vector>
#include<string>
#include"task.h"

using namespace std;
class Parser
{
public:
    vector<Task>readTasks(string filename);
};
#endif