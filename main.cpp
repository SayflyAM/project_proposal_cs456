#include <iostream>
#include "Parser.h"
#include "CSP.h"

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
}