#include "EmployeeDirectory.h"
#include "SharedLib.h"
#include <iostream>
#include <limits>
#include <ctime>
#include <utility>

static EmployeeNode* g_masterHead = nullptr;
static std::vector<TEmployee*> g_masterArray;
static std::vector<TEmployee*> g_searchArray;

static bool g_isListSortedByName = false;
static bool g_isArraySortedByDept = false;
static bool g_isSearchBuilt = false;

bool hasEmployees()
{
    return g_masterHead != nullptr;
}

static void appendToMasterList(TEmployee* e)
{
    EmployeeNode* node = new EmployeeNode{ e, nullptr };

    if (!g_masterHead)
    {
        g_masterHead = node;
        return;
    }

    EmployeeNode* cur = g_masterHead;
    while (cur->next) cur = cur->next;
    cur->next = node;
}

void clearEmployees()
{
    EmployeeNode* cur = g_masterHead;
    while (cur)
    {
        EmployeeNode* next = cur->next;
        delete cur->data;
        delete cur;
        cur = next;
    }
    g_masterHead = nullptr;

    g_masterArray.clear();
    g_searchArray.clear();

    g_isListSortedByName = false;
    g_isArraySortedByDept = false;
    g_isSearchBuilt = false;
}

static bool NameReadCallback(const int aIndex, const int aTotalCount, const std::string& aFirstName,
                             const std::string& aLastName)
{
    (void)aIndex;
    (void)aTotalCount;

    TEmployee* emp = new TEmployee;
    emp->firstName = aFirstName;
    emp->lastName = aLastName;
    emp->department = getRandomDepartment();

    appendToMasterList(emp);
    g_masterArray.push_back(emp);

    g_isListSortedByName = false;
    g_isArraySortedByDept = false;
    g_isSearchBuilt = false;

    return true;
}

void loadEmployees(const std::string& filename)
{
    clearEmployees();

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::cout << "Loading employees from: " << filename << std::endl;
    readNamesFromFile(filename, NameReadCallback);
    std::cout << "Done." << std::endl;
}

static void splitList(EmployeeNode* source, EmployeeNode** frontRef, EmployeeNode** backRef)
{
    if (!source || !source->next)
    {
        *frontRef = source;
        *backRef = nullptr;
        return;
    }

    EmployeeNode* slow = source;
    EmployeeNode* fast = source->next;

    while (fast)
    {
        fast = fast->next;
        if (fast)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = nullptr;
}

static EmployeeNode* sortedMerge(EmployeeNode* a, EmployeeNode* b)
{
    if (!a)
        return b;
    if (!b)
        return a;

    EmployeeNode* result = nullptr;

    if (employeeNameLess(a->data, b->data))
    {
        result = a;
        result->next = sortedMerge(a->next, b);
    }
    else
    {
        result = b;
        result->next = sortedMerge(a, b->next);
    }

    return result;
}

static void mergeSortListInternal(EmployeeNode** headRef)
{
    EmployeeNode* head = *headRef;
    if (!head || !head->next) return;

    EmployeeNode* a = nullptr;
    EmployeeNode* b = nullptr;

    splitList(head, &a, &b);
    mergeSortListInternal(&a);
    mergeSortListInternal(&b);

    *headRef = sortedMerge(a, b);
}

void sortMasterListByName()
{
    if (!g_isListSortedByName && g_masterHead)
    {
        mergeSortListInternal(&g_masterHead);
        g_isListSortedByName = true;
        g_isSearchBuilt = false;
    }
}

static int partitionEmployees(int low, int high)
{
    TEmployee* pivot = g_masterArray[high];
    int i = low - 1;

    for (int j = low; j < high; ++j)
    {
        if (employeeDeptCompare(g_masterArray[j], pivot) < 0)
        {
            ++i;
            std::swap(g_masterArray[i], g_masterArray[j]);
        }
    }

    std::swap(g_masterArray[i + 1], g_masterArray[high]);
    return i + 1;
}

static void quickSortEmployees(int low, int high)
{
    if (low >= high) return;

    int p = partitionEmployees(low, high);
    quickSortEmployees(low, p - 1);
    quickSortEmployees(p + 1, high);
}

void sortMasterArrayByDept()
{
    if (!g_isArraySortedByDept && !g_masterArray.empty())
    {
        quickSortEmployees(0, static_cast<int>(g_masterArray.size()) - 1);
        g_isArraySortedByDept = true;
    }
}

void buildSearchArray()
{
    sortMasterListByName();

    g_searchArray.clear();
    EmployeeNode* cur = g_masterHead;
    while (cur)
    {
        g_searchArray.push_back(cur->data);
        cur = cur->next;
    }
    g_isSearchBuilt = true;
}

int binarySearchEmployee(const std::string& last, const std::string& first)
{
    if (!g_isSearchBuilt)
    {
        if (!g_masterHead) return -1;
        buildSearchArray();
    }

    int left  = 0;
    int right = static_cast<int>(g_searchArray.size()) - 1;

    while (left <= right)
    {
        int mid = (left + right) / 2;
        const TEmployee* e = g_searchArray[mid];

        int cmp = employeeCompareToName(e, last, first);
        if (cmp == 0) return mid;
        if (cmp < 0)  left  = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

const std::vector<TEmployee*>& getSearchArray()
{
    return g_searchArray;
}

void printEmployee(const TEmployee* e)
{
    std::cout << e->lastName << ", " << e->firstName << "  [" << departmentToString(e->department) << "]" << std::endl;
}

void printMasterRollCall()
{
    if (!g_masterHead)
    {
        std::cout << "No employees loaded" << std::endl;
        return;
    }

    sortMasterListByName();

    std::cout << std::endl;
    std::cout << "Master Roll Call (Last, First)" << std::endl;
    EmployeeNode* cur = g_masterHead;
    while (cur)
    {
        printEmployee(cur->data);
        cur = cur->next;
    }
    std::cout << "--------------------" << std::endl;
}

void printOrganizationalChart()
{
    if (g_masterArray.empty())
    {
        std::cout << "No employees loaded" << std::endl;
        return;
    }

    sortMasterArrayByDept();

    std::cout << std::endl;
    std::cout << "Organizational Chart (Dept, Last, First)" << std::endl;
    std::string currentDept;

    for (TEmployee* e : g_masterArray)
    {
        std::string deptName = departmentToString(e->department);
        if (deptName != currentDept)
        {
            currentDept = deptName;
            std::cout << std::endl;
            std::cout << "-- " << currentDept << " --" << std::endl;
        }
        printEmployee(e);
    }
    std::cout << "--------------------" << std::endl;
}