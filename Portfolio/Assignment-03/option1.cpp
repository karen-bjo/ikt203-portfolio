#include "option1.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <limits>

#include "TEmployee.h"
#include "BST.h"
#include "AVLTree.h"
#include "DataPath.h"
#include "SharedLib.h"

static std::vector<TEmployee*> gEmployees;
static TBST gBst;
static TAVLTree gAvl;

static bool OnNameRead(const int aIndex, const int aTotalCount, const std::string& aFirstName, const std::string& aLastName)
{
    if (aIndex >= 200)
        return false;

    auto* employee = new TEmployee{};
    employee->firstName = aFirstName;
    employee->lastName  = aLastName;

    int id = 0;
    bool isUnique = false;

    while (!isUnique)
    {
        id = 100000 + std::rand();
        isUnique = true;

        for (TEmployee* existing : gEmployees)
        {
            if (existing->employeeId == id)
            {
                isUnique = false;
                break;
            }
        }
    }

    employee->employeeId = id;

    gEmployees.push_back(employee);
    gBst.insert(id, employee);
    gAvl.insert(id, employee);

    return true;
}

static void PrintMenu()
{
    std::cout << std::endl;
    std::cout << "--- Employee Directory (BST vs. AVL) ---" << std::endl;
    std::cout << "1) Print BST traversals" << std::endl;
    std::cout << "2) Print AVL traversals" << std::endl;
    std::cout << "3) Search for employee by ID" << std::endl;
    std::cout << "4) Exit" << std::endl;
}

static void PrintBSTTraversals()
{
    std::cout << std::endl;
    std::cout << "--- BST Traversals ---" << std::endl;

    std::cout << "Inorder:" << std::endl;
    gBst.inorder();
    std::cout << std::endl;

    std::cout << "Preorder:" << std::endl;
    gBst.preorder();
    std::cout << std::endl;

    std::cout << "Postorder:" << std::endl;
    gBst.postorder();
    std::cout << std::endl;

    std::cout << "Level-order:" << std::endl;
    gBst.levelOrder();
    std::cout << std::endl;
}

static void PrintAVLTraversals()
{
    std::cout << std::endl;
    std::cout << "--- AVL Traversals ---" << std::endl;

    std::cout << "Inorder:" << std::endl;
    gAvl.inorder();
    std::cout << std::endl;

    std::cout << "Preorder:" << std::endl;
    gAvl.preorder();
    std::cout << std::endl;

    std::cout << "Postorder:" << std::endl;
    gAvl.postorder();
    std::cout << std::endl;

    std::cout << "Level-order:" << std::endl;
    gAvl.levelOrder();
    std::cout << std::endl;
}

int RunApp()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    const std::string filename = GetDataPath("random_names.txt");
    readNamesFromFile(filename, OnNameRead);

    if (gEmployees.empty())
    {
        std::cout << "No employees were loaded. Exiting." << std::endl;
        return 0;
    }

    bool running = true;

    while (running)
    {
        PrintMenu();

        int choice = 0;
        std::cout << "Choose an option: ";

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
                PrintBSTTraversals();
                break;

            case 2:
                PrintAVLTraversals();
                break;

            case 3:
            {
                int id = 0;
                std::cout << "Enter employee ID: ";

                if (!(std::cin >> id))
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid ID" << std::endl;
                    break;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


                TEmployee* bstResult = gBst.search(id);
                TEmployee* avlResult = gAvl.search(id);

                if (bstResult)
                {
                    std::cout << "[BST] Found: ID " << bstResult->employeeId << " | " << bstResult->firstName << " "
                              << bstResult->lastName << std::endl;
                }
                else
                {
                    std::cout << "[BST] Employee not found." << std::endl;
                }

                if (avlResult)
                {
                    std::cout << "[AVL] Found: ID " << avlResult->employeeId << " | " << avlResult->firstName << " "
                              << avlResult->lastName << std::endl;
                }
                else
                {
                    std::cout << "[AVL] Employee not found." << std::endl;
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

    for (TEmployee* employee : gEmployees)
    {
        delete employee;
    }
    gEmployees.clear();

    return 0;
}