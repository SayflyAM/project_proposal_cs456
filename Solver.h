#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include "task.h"
#include "CSP.h"

using namespace std;

class Solver
{
public:
    bool isValid(int taskIndex,int startTime,vector<Task>& tasks,CSP& csp);
    bool backtrack(vector<Task>& tasks,CSP& csp,int taskIndex);
    int selectMRVVariable(vector<Task>& tasks, CSP& csp);
    bool forwardCheck(vector<Task>& tasks,CSP& csp,int taskIndex,int startTime);
};

#endif