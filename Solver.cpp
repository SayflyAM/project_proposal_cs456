#include "Solver.h"

bool Solver::isValid(int taskIndex,int startTime,vector<Task>& tasks,CSP& csp)
{
    Task currentTask = tasks[taskIndex];

    for(int i = 0; i < currentTask.dependencies.size(); i++)
    {
        int depId = currentTask.dependencies[i];

        for(int j = 0; j < tasks.size(); j++)
        {
            if(tasks[j].id == depId)
          {
            if(csp.assignment[j+1] == -1)
            {
              return false;
            }
            int finishTime = csp.assignment[j+1] + tasks[j].duration;
            if(startTime < finishTime)
            {
              return false;
            }
          }
        }
    }

    return true;
}

int Solver::selectMRVVariable(vector<Task>& tasks, CSP& csp)
{
    int bestTask = -1;
    int smallestDomain = 1000000;

    for(int i = 0; i < tasks.size(); i++)
    {
        if(csp.assignment[i + 1] != -1)
        {
            continue;
        }

        bool ready = true;

for(int j = 0; j < tasks[i].dependencies.size(); j++)
{
    int depId = tasks[i].dependencies[j];

    for(int k = 0; k < tasks.size(); k++)
    {
        if(tasks[k].id == depId)
        {
            if(csp.assignment[k + 1] == -1)
            {
                ready = false;
            }
        }
    }
}

if(!ready)
{
    continue;
}

        int domainSize = csp.domains[i + 1].size();

        if(domainSize < smallestDomain)
        {
            smallestDomain = domainSize;
            bestTask = i;
        }
    }

    return bestTask;
}

bool Solver::forwardCheck(vector<Task>& tasks,CSP& csp,int taskIndex,int startTime)
{
    int finishTime = startTime + tasks[taskIndex].duration;

    for(int i = 0; i < tasks.size(); i++)
    {
        for(int j = 0; j < tasks[i].dependencies.size(); j++)
        {
            if(tasks[i].dependencies[j] == tasks[taskIndex].id)
            {
                vector<int> newDomain;

                for(int k = 0; k < csp.domains[i + 1].size();k++)
                {
                    int value = csp.domains[i + 1][k];

                    if(value >= finishTime)
                    {
                        newDomain.push_back(value);
                    }
                }

                csp.domains[i + 1] = newDomain;
                if(csp.domains[i + 1].empty())
                {
                    return false;
                }
            }
        }
    }

    return true;
}

bool Solver::backtrack(vector<Task>& tasks,CSP& csp,int taskIndex)
{
    bool complete = true;

    for(int i = 1; i < csp.assignment.size(); i++)
    {
       if(csp.assignment[i] == -1)
       {  
        complete = false;
        break;
       }
    }

if(complete)
{
    return true;
}  
taskIndex = selectMRVVariable(tasks, csp);

    for(int i = 0; i < csp.domains[taskIndex + 1].size(); i++)
    {
        int startTime = csp.domains[taskIndex + 1][i];

    if(isValid(taskIndex, startTime, tasks, csp))
{
    csp.assignment[taskIndex + 1] = startTime;

    vector<vector<int>> savedDomains = csp.domains;

    if(forwardCheck(tasks, csp, taskIndex, startTime))
    {
        if(backtrack(tasks, csp, -1))
        {
            return true;
        }
    }
    
    csp.domains = savedDomains;
    csp.assignment[taskIndex + 1] = -1;
}
    }

    return false;
}