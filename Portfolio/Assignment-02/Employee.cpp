#include "Employee.h"
#include <cstdlib>

std::string departmentToString(EDepartment d)
{
    switch (d)
    {
        case EDepartment::IT:        return "IT";
        case EDepartment::Finance:   return "Finance";
        case EDepartment::HR:        return "HR";
        case EDepartment::Sales:     return "Sales";
        case EDepartment::Marketing: return "Marketing";
        default:                     return "Unknown";
    }
}

EDepartment getRandomDepartment()
{
    int r = std::rand() % static_cast<int>(EDepartment::Count);
    return static_cast<EDepartment>(r);
}

bool employeeNameLess(const TEmployee* a, const TEmployee* b)
{
    if (a->lastName < b->lastName) return true;
    if (a->lastName > b->lastName) return false;
    return a->firstName < b->firstName;
}

int employeeDeptCompare(const TEmployee* a, const TEmployee* b)
{
    std::string da = departmentToString(a->department);
    std::string db = departmentToString(b->department);

    if (da < db) return -1;
    if (da > db) return 1;

    if (a->lastName < b->lastName) return -1;
    if (a->lastName > b->lastName) return 1;

    if (a->firstName < b->firstName) return -1;
    if (a->firstName > b->firstName) return 1;

    return 0;
}

int employeeCompareToName(const TEmployee* e,
                          const std::string& last,
                          const std::string& first)
{
    if (e->lastName < last) return -1;
    if (e->lastName > last) return 1;

    if (e->firstName < first) return -1;
    if (e->firstName > first) return 1;

    return 0;
}