#pragma once
#include <string>

enum class EDepartment
{
    IT = 0,
    Finance,
    HR,
    Sales,
    Marketing,
    Count
};

struct TEmployee
{
    std::string firstName;
    std::string lastName;
    EDepartment department;
};

bool employeeNameLess(const TEmployee* a, const TEmployee* b);

int employeeDeptCompare(const TEmployee* a, const TEmployee* b);

int employeeCompareToName(const TEmployee* e,
                          const std::string& last,
                          const std::string& first);

std::string departmentToString(EDepartment d);
EDepartment getRandomDepartment();