#include <iostream>
#include <string>
#include <limits>
#include "manager.h"

int main() {
    Manager taskManager;

    int choice = 0;

    while (true) {
        std::cout << "\n--- TODO LIST MANAGER ---\n";
        std::cout << "1. Create Task\n";
        std::cout << "2. View Task\n";
        std::cout << "3. Update Task\n";
        std::cout << "4. Delete Task\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";

        std::cin >> choice;

        switch (choice) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}