// Option 2 (Advanced): Combined Corporate Directory.

#include "option2.h"
#include "EmployeeDirectory.h"
#include <iostream>
#include <limits>

#include "DataPath.h"
#include "SharedLib.h"

int RunApp()
{
    bool running = true;

    while (running)
    {
        std::cout << std::endl;
        std::cout << "Combined Corporate Directory:" << std::endl;
        std::cout << "1. Load employees from file" << std::endl;
        std::cout << "2. Show master roll call (Merge Sort on list)" << std::endl;
        std::cout << "3. Show organizational chart (Quick Sort on array)" << std::endl;
        std::cout << "4. Look up employee (Binary Search on array)" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Choice: ";

        int choice = 0;
        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input" << std::endl;
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
        {
            std::string filename = GetDataPath("random_names.txt");
            loadEmployees(filename);
            break;
        }
        case 2:
            printMasterRollCall();
            break;
        case 3:
            printOrganizationalChart();
            break;
        case 4:
        {
            if (!hasEmployees())
            {
                std::cout << "No employees loaded" << std::endl;
                break;
            }

            std::string last, first;
            std::cout << "Enter last name: ";
            std::getline(std::cin, last);
            std::cout << "Enter first name: ";
            std::getline(std::cin, first);

            int idx = binarySearchEmployee(last, first);
            if (idx < 0)
            {
                std::cout << "Employee not found" << std::endl;
            }
            else
            {
                std::cout << "Employee found:" << std::endl;
                printEmployee(getSearchArray()[static_cast<std::size_t>(idx)]);
            }
            break;
        }
        case 5:
            running = false;
            break;
        default:
            std::cout << "Invalid choice." << std::endl;
            break;
        }
    }

    clearEmployees();
    return 0;
}