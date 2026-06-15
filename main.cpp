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

    Parser::parseFile("data/test_5_tasks.txt", tasks, resConstraint, precConstraints, maxTime);

    int actualNumTasks = tasks.size() - 1;

    CSP cspModel;

    cspModel.initializeDomains(actualNumTasks, maxTime);

    Solver solver;

    if (solver.backtrack(tasks, csp, 0))
    {
        cout << "Solution Found!" << endl;

        for (int i = 1; i <= tasks.size(); i++)
        {
            cout << "Task " << i << " Start Time = " << csp.assignment[i] << endl;
        }
    }
    else
    {
        cout << "No Solution Found!" << endl;
    }

    return 0;
