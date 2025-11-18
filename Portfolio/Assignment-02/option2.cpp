// Option 2 (Advanced): Combined Corporate Directory.

#include "option2.h"
#include "EmployeeDirectory.h"
#include <iostream>
#include <limits>

#include "DataPath.h"
#include "SharedLib.h"

int RunApp()
{
    std::string filename = GetDataPath("random_names.txt");
    bool running = true;

    while (running)
    {
        if (!hasEmployees())
        {
            loadEmployees(filename);
        }

        std::cout << std::endl;
        std::cout << "--- Combined Corporate Directory ---" << std::endl;
        std::cout << "1. Show master roll call" << std::endl;
        std::cout << "2. Show organizational chart" << std::endl;
        std::cout << "3. Look up employee" << std::endl;
        std::cout << "4. Exit" << std::endl;
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
            printMasterRollCall();
            break;
        case 2:
            printOrganizationalChart();
            break;
        case 3:
        {
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
        case 4:
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