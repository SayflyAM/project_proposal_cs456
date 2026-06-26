#ifndef CONSTRAINTS_H
#define CONSTRAINTS_H

struct ResourceConstraint
{
    int maxCapacity;
};

struct PrecedenceConstraint
{
    int beforeTaskId;
    int afterTaskId;
};

#endif