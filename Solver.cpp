#include "Solver.h"
#include <iostream>

bool Solver::isValid(int taskIndex, int startTime, vector<Task>& tasks, CSP& csp)
{
    // 1. Precedence Constraint Check
    Task currentTask = tasks[taskIndex];
    for (int depId : currentTask.dependencies)
    {
        if (csp.assignment[depId] == -1)
        {
            return false;
        }
        int finishTime = csp.assignment[depId] + tasks[depId].duration;
        if (startTime < finishTime)
        {
            return false;
        }
    }

    // 2. Resource Constraint Check
    int numTasks = tasks.size() - 1;
    for (int t = startTime; t < startTime + currentTask.duration; t++)
    {
        int sumResources = currentTask.resource_demand;
        for (int otherId = 1; otherId <= numTasks; otherId++)
        {
            if (otherId == taskIndex)
                continue;
            
            if (csp.assignment[otherId] != -1)
            {
                int otherStart = csp.assignment[otherId];
                int otherDuration = tasks[otherId].duration;
                if (t >= otherStart && t < otherStart + otherDuration)
                {
                    sumResources += tasks[otherId].resource_demand;
                }
            }
        }
        if (sumResources > csp.resourceLimit)
        {
            return false;
        }
    }

    return true;
}

int Solver::selectMRVVariable(vector<Task>& tasks, CSP& csp)
{
    int bestTask = -1;
    int smallestDomain = 1000000;
    int numTasks = tasks.size() - 1;

    for (int id = 1; id <= numTasks; id++)
    {
        if (csp.assignment[id] != -1)
        {
            continue;
        }

        bool ready = true;
        for (int depId : tasks[id].dependencies)
        {
            if (csp.assignment[depId] == -1)
            {
                ready = false;
                break;
            }
        }

        if (!ready)
        {
            continue;
        }

        int domainSize = csp.domains[id].size();
        if (domainSize < smallestDomain)
        {
            smallestDomain = domainSize;
            bestTask = id;
        }
    }

    return bestTask;
}

bool Solver::forwardCheck(vector<Task>& tasks, CSP& csp, int taskIndex, int startTime)
{
    int finishTime = startTime + tasks[taskIndex].duration;
    int numTasks = tasks.size() - 1;

    for (int id = 1; id <= numTasks; id++)
    {
        if (csp.assignment[id] != -1)
            continue;

        for (int depId : tasks[id].dependencies)
        {
            if (depId == taskIndex)
            {
                vector<int> newDomain;
                for (int val : csp.domains[id])
                {
                    if (val >= finishTime)
                    {
                        newDomain.push_back(val);
                    }
                }
                csp.domains[id] = newDomain;
                if (csp.domains[id].empty())
                {
                    return false;
                }
            }
        }
    }

    return true;
}

int Solver::selectNextVariable(vector<Task>& tasks, CSP& csp, bool useMRV)
{
    if (useMRV)
    {
        return selectMRVVariable(tasks, csp);
    }

    int numTasks = tasks.size() - 1;
    for (int id = 1; id <= numTasks; id++)
    {
        if (csp.assignment[id] == -1)
        {
            return id;
        }
    }
    return -1;
}

bool Solver::backtrack(vector<Task>& tasks, CSP& csp, bool useMRV, bool useFC)
{
    int numTasks = tasks.size() - 1;
    bool complete = true;

    for (int id = 1; id <= numTasks; id++)
    {
        if (csp.assignment[id] == -1)
        {  
            complete = false;
            break;
        }
    }

    if (complete)
    {
        return true;
    }  

    int nextTask = selectNextVariable(tasks, csp, useMRV);
    if (nextTask == -1)
    {
        return false;
    }

    vector<int> currentDomain = csp.domains[nextTask];

    for (int startTime : currentDomain)
    {
        if (isValid(nextTask, startTime, tasks, csp))
        {
            csp.assignment[nextTask] = startTime;
            vector<vector<int>> savedDomains = csp.domains;

            bool fcOk = true;
            if (useFC)
            {
                fcOk = forwardCheck(tasks, csp, nextTask, startTime);
            }

            if (fcOk)
            {
                if (backtrack(tasks, csp, useMRV, useFC))
                {
                    return true;
                }
            }
            
            csp.domains = savedDomains;
            csp.assignment[nextTask] = -1;
        }
    }

    return false;
}