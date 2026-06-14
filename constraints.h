#ifndef CONSTRAINTRS_H
#define CONSTRAINTRS_H

#include <vector>

struct PrecedenceConstraint
{
    int beforeTaskId;
    int afterTaskId;
};

struct ResourceConstraint
{
    int maxCapacity;
};

#endif