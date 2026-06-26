#include <iostream>
#include "Parser.h"
#include "CSP.h"
#include "Solver.h"

using namespace std;

int main()
{
    vector<Task> tasks;
    ResourceConstraint resConstraint;
    vector<PrecedenceConstraint> precConstraints;
    int maxTime = 0;

    if (!Parser::parseFile("Testing/final_input.txt", tasks, resConstraint, precConstraints, maxTime))
    {
        cerr << "Failed to parse input file." << endl;
        return 1;
    }

    int actualNumTasks = tasks.size() - 1;

    CSP cspModel;
    cspModel.resourceLimit = resConstraint.maxCapacity;
    cspModel.initializeDomains(actualNumTasks, maxTime);

    Solver solver;

    //  Basic Backtracking
    {
        cout << "--- Running Configuration 1: Basic Backtracking ---" << endl;
        CSP cspBasic = cspModel; // copy initial model
        if (solver.backtrack(tasks, cspBasic, false, false))
        {
            cout << "Solution Found!" << endl;
            for (int i = 1; i <= actualNumTasks; i++)
            {
                cout << "Task " << i << " Start Time = " << cspBasic.assignment[i] << endl;
            }
        }
        else
        {
            cout << "No Solution Found!" << endl;
        }
        cout << endl;
    }

    //  Backtracking with Forward Checking
    {
        cout << "--- Running Configuration 2: Backtracking + Forward Checking ---" << endl;
        CSP cspFC = cspModel;
        if (solver.backtrack(tasks, cspFC, false, true))
        {
            cout << "Solution Found!" << endl;
            for (int i = 1; i <= actualNumTasks; i++)
            {
                cout << "Task " << i << " Start Time = " << cspFC.assignment[i] << endl;
            }
        }
        else
        {
            cout << "No Solution Found!" << endl;
        }
        cout << endl;
    }

    // Backtracking + Forward Checking + MRV Heuristic
    {
        cout << "--- Running Configuration 3: Backtracking + FC + MRV (Full Heuristics) ---" << endl;
        CSP cspFull = cspModel;
        if (solver.backtrack(tasks, cspFull, true, true))
        {
            cout << "Solution Found!" << endl;
            for (int i = 1; i <= actualNumTasks; i++)
            {
                cout << "Task " << i << " Start Time = " << cspFull.assignment[i] << endl;
            }
        }
        else
        {
            cout << "No Solution Found!" << endl;
        }
        cout << endl;
    }

    //  Iterative Makespan Optimization (Phase 7 of the Project Plan)
    {
        cout << "--- Running Configuration 4: Iterative Makespan Optimization ---" << endl;
        int bestMakespan = maxTime;
        vector<int> bestAssignment;
        int currentLimit = maxTime;

        while (true)
        {
            CSP cspIter;
            cspIter.resourceLimit = resConstraint.maxCapacity;
            cspIter.initializeDomains(actualNumTasks, currentLimit);

            // Restrict each task's domain so that: start_time + duration <= currentLimit
            bool possible = true;
            for (int i = 1; i <= actualNumTasks; i++)
            {
                vector<int> filtered;
                for (int t : cspIter.domains[i])
                {
                    if (t + tasks[i].duration <= currentLimit)
                    {
                        filtered.push_back(t);
                    }
                }
                cspIter.domains[i] = filtered;
                if (filtered.empty())
                {
                    possible = false;
                }
            }

            if (!possible)
            {
                break; // No space for some task, cannot optimize further
            }

            // Run backtracking with full heuristics to find a solution within this limit
            if (solver.backtrack(tasks, cspIter, true, true))
            {
                int currentMakespan = 0;
                for (int i = 1; i <= actualNumTasks; i++)
                {
                    int finish = cspIter.assignment[i] + tasks[i].duration;
                    if (finish > currentMakespan)
                    {
                        currentMakespan = finish;
                    }
                }
                bestMakespan = currentMakespan;
                bestAssignment = cspIter.assignment;

                cout << "Found valid schedule with Makespan = " << currentMakespan << ". Tightening limit to " << currentMakespan - 1 << "..." << endl;
                currentLimit = currentMakespan - 1;
            }
            else
            {
                cout << "No solution found with limit " << currentLimit << ". Optimization finished!" << endl;
                break;
            }
        }

        if (!bestAssignment.empty())
        {
            cout << "\n>>> Optimal Schedule Found (Makespan = " << bestMakespan << "):" << endl;
            for (int i = 1; i <= actualNumTasks; i++)
            {
                cout << "Task " << i << " Start Time = " << bestAssignment[i] << " (Finishes at " << bestAssignment[i] + tasks[i].duration << ")" << endl;
            }
        }
        else
        {
            cout << "No Optimal Solution Found!" << endl;
        }
        cout << endl;
    }

    return 0;
}
