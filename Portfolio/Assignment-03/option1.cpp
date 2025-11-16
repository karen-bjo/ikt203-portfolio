#include "option1.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "TEmployee.h"
#include "BST.h"
#include "AVLTree.h"

static bool LoadEmployees(std::vector<TEmployee*>& outEmployees)
{
    std::string filePath = "C:/Users/andre/UIA/3sem/ikt203g25h/ikt203-portfolio/DATA/random_names.txt";

    std::ifstream in(filePath);
    if (!in.is_open())
    {
        std::cout << "Could not open default path '" << filePath << std::endl;
        std::cout << "Enter full path to random_names.txt:" << std::endl;
        std::cout << "> ";
        std::getline(std::cin >> std::ws, filePath);
        in.open(filePath);
        if (!in.is_open())
        {
            std::cout << "Still could not open file. Aborting." << std::endl;
            return false;
        }
    }


    const int MAX_EMPLOYEES = 200;

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::vector<int> usedIds;

    auto generateUniqueId = [&](int minId, int maxId) -> int {
        for (;;)
        {
            int id = minId + std::rand() % (maxId - minId + 1);
            bool exists = false;
            for (int used : usedIds)
            {
                if (used == id)
                {
                    exists = true;
                    break;
                }
            }
            if (!exists)
            {
                usedIds.push_back(id);
                return id;
            }
        }
    };

    std::string line;
    int count = 0;

    while (count < MAX_EMPLOYEES && std::getline(in, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::istringstream iss(line);
        std::string first;
        std::string last;

        // Very simple parsing: "First Last"
        if (!(iss >> first >> last))
        {
            continue;
        }

        // Strip trailing comma from last if present (e.g., "Smith,")
        if (!last.empty() && last.back() == ',')
        {
            last.pop_back();
        }

        TEmployee* e = new TEmployee;
        e->employeeId = generateUniqueId(100000, 999999);
        e->firstName = first;
        e->lastName = last;

        outEmployees.push_back(e);
        ++count;
    }

    std::cout << "Loaded " << outEmployees.size() << " employees." << std::endl;
    return !outEmployees.empty();
}

static void PrintMenu()
{
    std::cout << std::endl;
    std::cout << "--- Employee Directory (BST vs AVL) ---" << std::endl;
    std::cout << "1. Show all employees (BST inorder)" << std::endl;
    std::cout << "2. Show all employees (AVL inorder)" << std::endl;
    std::cout << "3. Search employee by ID" << std::endl;
    std::cout << "4. Delete employee from BST by ID" << std::endl;
    std::cout << "5. Show traversals (BST + AVL)" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Choose: ";
}

int RunApp()
{
    std::cout << "Assignment 03 - Category 3: Trees (BST, AVL & RBT)" << std::endl;
    std::cout << "Option 1 (Standard): Employee Directory (BST vs. AVL)" << std::endl;
    std::cout << std::endl;

    std::vector<TEmployee*> employees;
    if (!LoadEmployees(employees))
    {
        return 1;
    }

    TBST bst;
    TAVLTree avl;

    for (TEmployee* e : employees)
    {
        bst.insert(e->employeeId, e);
        avl.insert(e->employeeId, e);
    }

    int choice = -1;
    while (choice != 0)
    {
        PrintMenu();
        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(1024, '\n');
            continue;
        }

        if (choice == 1)
        {
            std::cout << std::endl;
            std::cout << "--- BST Inorder (sorted by ID) ---" << std::endl;
            bst.inorder();
        }
        else if (choice == 2)
        {
            std::cout << std::endl;
            std::cout << "--- AVL Inorder (sorted by ID) ---" << std::endl;
            avl.inorder();
        }
        else if (choice == 3)
        {
            int id;
            std::cout << "Enter employee ID to search: ";
            std::cin >> id;

            TEmployee* e1 = bst.search(id);
            TEmployee* e2 = avl.search(id);

            std::cout << std::endl;
            std::cout << "BST search:" << std::endl;
            if (e1)
            {
                std::cout << "Found: " << e1->employeeId << " " << e1->firstName << " " << e1->lastName << std::endl;
            }
            else
            {
                std::cout << "Not found in BST." << std::endl;
            }

            std::cout << "AVL search:" << std::endl;
            if (e2)
            {
                std::cout << "Found: " << e2->employeeId << " " << e2->firstName << " " << e2->lastName << std::endl;
            } else
            {
                std::cout << "Not found in AVL." << std::endl;
            }

        }
        else if (choice == 4)
        {
            int id;
            std::cout << "Enter employee ID to delete from BST: ";
            std::cin >> id;
            bst.deleteKey(id);
            std::cout << "BST after deletion (inorder):" << std::endl;
            bst.inorder();
        }
        else if (choice == 5)
        {
            std::cout << std::endl;
            std::cout << "--- BST Traversals ---" << std::endl;
            std::cout << "Inorder:" << std::endl;
            bst.inorder();
            std::cout << std::endl;
            std::cout << "Preorder:" << std::endl;
            bst.preorder();
            std::cout << std::endl;
            std::cout << "Postorder:" << std::endl;
            bst.postorder();
            std::cout << std::endl;
            std::cout << "Level-order:" << std::endl;
            bst.levelOrder();

            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << "--- AVL Traversals ---" << std::endl;
            std::cout << "Inorder:" << std::endl;
            avl.inorder();
            std::cout << std::endl;
            std::cout << "Preorder:" << std::endl;
            avl.preorder();
            std::cout << std::endl;
            std::cout << "Postorder:" << std::endl;
            avl.postorder();
            std::cout << std::endl;
            std::cout << "Level-order:" << std::endl;
            avl.levelOrder();
        }
    }

    // Trees do NOT own employees; free them here
    for (TEmployee* e : employees)
    {
        delete e;
    }

    return 0;
}