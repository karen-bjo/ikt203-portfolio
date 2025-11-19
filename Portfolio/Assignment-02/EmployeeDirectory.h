#ifndef IKT203_COURSE_ASSIGNMENTS_EMPLOYEE_DIRECTORY_H
#define IKT203_COURSE_ASSIGNMENTS_EMPLOYEE_DIRECTORY_H

#include <vector>
#include <string>
#include "Employee.h"

struct EmployeeNode
{
    TEmployee*   data = nullptr;
    EmployeeNode* next = nullptr;
};

bool hasEmployees();

void loadEmployees(const std::string& filename);
void clearEmployees();

void sortMasterListByName();
void sortMasterArrayByDept();

void buildSearchArray();

int binarySearchEmployee(const std::string& last, const std::string& first);

void printEmployee(const TEmployee* e);
void printMasterRollCall();
void printOrganizationalChart();

const std::vector<TEmployee*>& getSearchArray();

#endif // IKT203_COURSE_ASSIGNMENTS_EMPLOYEE_DIRECTORY_H