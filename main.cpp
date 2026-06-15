#include <iostream>
#include "Parser.h"
#include "CSP.h"
#include "Solver.h"

using namespace std;

int main()
{
    Parser parser;

    vector<Task> tasks =
        parser.readTasks("Testing/valid_input.txt");

    cout << "Number of Tasks = "<< tasks.size()<< endl;

    CSP csp;

    csp.initialize(tasks.size(), 10);

    Solver solver;

    if(solver.backtrack(tasks, csp, 0))
    {
        cout << "Solution Found!" << endl;

        for(int i = 1; i <= tasks.size(); i++)
        {
            cout << "Task "<< i << " Start Time = "<< csp.assignment[i]<< endl;
        }
    }
    else
    {
        cout << "No Solution Found!" << endl;
    }

    return 0;
}