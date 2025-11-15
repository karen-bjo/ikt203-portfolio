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

static bool LoadEmployees(std::vector<TEmployee*>& outEmployees) {
    std::string filePath = "C:/Users/andre/UIA/3sem/ikt203g25h/ikt203-portfolio/DATA/random_names.txt";

    std::ifstream in(filePath);
    if (!in.is_open()) {
        std::cout << "Could not open default path '" << filePath << "'.\n";
        std::cout << "Enter full path to random_names.txt:\n> ";
        std::getline(std::cin >> std::ws, filePath);
        in.open(filePath);
        if (!in.is_open()) {
            std::cout << "Still could not open file. Aborting.\n";
            return false;
        }
    }


    const int MAX_EMPLOYEES = 200;

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::vector<int> usedIds;

    auto generateUniqueId = [&](int minId, int maxId) -> int {
        for (;;) {
            int id = minId + std::rand() % (maxId - minId + 1);
            bool exists = false;
            for (int used : usedIds) {
                if (used == id) {
                    exists = true;
                    break;
                }
            }
            if (!exists) {
                usedIds.push_back(id);
                return id;
            }
        }
    };

    std::string line;
    int count = 0;

    while (count < MAX_EMPLOYEES && std::getline(in, line)) {
        if (line.empty()) {
            continue;
        }

        std::istringstream iss(line);
        std::string first;
        std::string last;

        // Very simple parsing: "First Last"
        if (!(iss >> first >> last)) {
            continue;
        }

        // Strip trailing comma from last if present (e.g., "Smith,")
        if (!last.empty() && last.back() == ',') {
            last.pop_back();
        }

        TEmployee* e = new TEmployee;
        e->employeeId = generateUniqueId(100000, 999999);
        e->firstName = first;
        e->lastName = last;

        outEmployees.push_back(e);
        ++count;
    }

    std::cout << "Loaded " << outEmployees.size() << " employees.\n";
    return !outEmployees.empty();
}

static void PrintMenu() {
    std::cout << "\n=== Employee Directory (BST vs AVL) ===\n";
    std::cout << "1. Show all employees (BST inorder)\n";
    std::cout << "2. Show all employees (AVL inorder)\n";
    std::cout << "3. Search employee by ID\n";
    std::cout << "4. Delete employee from BST by ID\n";
    std::cout << "5. Show traversals (BST + AVL)\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose: ";
}

int RunApp() {
    std::cout << "Assignment 03 - Category 3: Trees (BST, AVL & RBT)\n";
    std::cout << "Option 1 (Standard): Employee Directory (BST vs. AVL)\n\n";

    std::vector<TEmployee*> employees;
    if (!LoadEmployees(employees)) {
        return 1;
    }

    TBST bst;
    TAVLTree avl;

    for (TEmployee* e : employees) {
        bst.insert(e->employeeId, e);
        avl.insert(e->employeeId, e);
    }

    int choice = -1;
    while (choice != 0) {
        PrintMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1024, '\n');
            continue;
        }

        if (choice == 1) {
            std::cout << "\n--- BST Inorder (sorted by ID) ---\n";
            bst.inorder();
        } else if (choice == 2) {
            std::cout << "\n--- AVL Inorder (sorted by ID) ---\n";
            avl.inorder();
        } else if (choice == 3) {
            int id;
            std::cout << "Enter employee ID to search: ";
            std::cin >> id;

            TEmployee* e1 = bst.search(id);
            TEmployee* e2 = avl.search(id);

            std::cout << "\nBST search:\n";
            if (e1) {
                std::cout << "Found: " << e1->employeeId << " "
                          << e1->firstName << " " << e1->lastName << "\n";
            } else {
                std::cout << "Not found in BST.\n";
            }

            std::cout << "AVL search:\n";
            if (e2) {
                std::cout << "Found: " << e2->employeeId << " "
                          << e2->firstName << " " << e2->lastName << "\n";
            } else {
                std::cout << "Not found in AVL.\n";
            }

        } else if (choice == 4) {
            int id;
            std::cout << "Enter employee ID to delete from BST: ";
            std::cin >> id;
            bst.deleteKey(id);
            std::cout << "BST after deletion (inorder):\n";
            bst.inorder();
        } else if (choice == 5) {
            std::cout << "\n--- BST Traversals ---\n";
            std::cout << "Inorder:\n";
            bst.inorder();
            std::cout << "\nPreorder:\n";
            bst.preorder();
            std::cout << "\nPostorder:\n";
            bst.postorder();
            std::cout << "\nLevel-order:\n";
            bst.levelOrder();

            std::cout << "\n\n--- AVL Traversals ---\n";
            std::cout << "Inorder:\n";
            avl.inorder();
            std::cout << "\nPreorder:\n";
            avl.preorder();
            std::cout << "\nPostorder:\n";
            avl.postorder();
            std::cout << "\nLevel-order:\n";
            avl.levelOrder();
        }
    }

    // Trees do NOT own employees; free them here
    for (TEmployee* e : employees) {
        delete e;
    }

    std::cout << "Goodbye.\n";
    return 0;
}