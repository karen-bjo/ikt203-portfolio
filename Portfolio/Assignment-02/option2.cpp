// Option 2 (Advanced): Combined Corporate Directory.

#include "option2.h"
#include "EmployeeDirectory.h"
#include <iostream>
#include <limits>
#include "SharedLib.h"

int RunApp()
{
    bool running = true;

    while (running)
    {
        std::cout << "\nCombined Corporate Directory:\n";
        std::cout << "1. Load employees from file\n";
        std::cout << "2. Show master roll call (Merge Sort on list)\n";
        std::cout << "3. Show organizational chart (Quick Sort on array)\n";
        std::cout << "4. Look up employee (Binary Search on array)\n";
        std::cout << "5. Exit\n";
        std::cout << "Choice: ";

        int choice = 0;
        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
        {
            std::string filename = "C:/Users/andre/UIA/3sem/ikt203g25h/ikt203-portfolio/DATA/random_names.txt";  //find solution
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
                std::cout << "No employees loaded\n";
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
                std::cout << "Employee not found\n";
            }
            else
            {
                std::cout << "Employee found:\n";
                printEmployee(getSearchArray()[static_cast<std::size_t>(idx)]);
            }
            break;
        }
        case 5:
            running = false;
            break;
        default:
            std::cout << "Invalid choice.\n";
            break;
        }
    }

    clearEmployees();
    return 0;
}