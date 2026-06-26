// Parser.h
#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Task.h"
#include "Constraints.h"

using namespace std;

class Parser
{
public:
    static vector<Task> readTasks(string filename);

    static bool parseFile(const std::string &filename,
                          vector<Task> &tasks,
                          ResourceConstraint &resConstraint,
                          vector<PrecedenceConstraint> &precConstraints,
                          int &maxTime)
    {

        std::ifstream file(filename);
        if (!file.is_open())
        {
            cerr << "Error: Could not open file " << filename << std::endl;
            return false;
        }

        std::string line;
        int numTasks = 0;
        maxTime = 0;

        while (std::getline(file, line))
        {
            if (line.empty())
                continue;

            std::stringstream ss(line);
            std::string key;
            ss >> key;

            if (key == "TASKS")
            {
                ss >> numTasks;
                tasks.resize(numTasks + 1);
            }
            else if (key == "RESOURCE_LIMIT")
            {
                ss >> resConstraint.maxCapacity;
            }
            else if (key == "TASK")
            {
                Task t;
                string temp;

                ss >> t.id;
                ss >> temp >> t.duration;
                ss >> temp >> t.resource_demand;

                if (t.duration < 0 || t.resource_demand < 0)
                {
                    cerr << "Validation Error: Task " << t.id << " has negative values!\n";
                    return false;
                }

                ss >> temp;
                string dep;
                while (ss >> dep)
                {
                    if (dep != "-")
                    {
                        t.dependencies.push_back(std::stoi(dep));

                        PrecedenceConstraint m;
                        m.beforeTaskId = std::stoi(dep);
                        m.afterTaskId = t.id;
                        precConstraints.push_back(m);
                    }
                }

                maxTime += t.duration;
                tasks[t.id] = t;
            }
        }

        file.close();
        return true;
    }
};

#endif