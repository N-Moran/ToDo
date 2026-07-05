#include <iostream>
#include <string>
#include <limits>
#include "manager.h"

int main() {
    Manager taskManager;

    int choice = 0;

    while (true) {

        int priority;
        std::string title;
        std::string description;

        char displayChoice;

        int upID;
        char upChoice;

        std::cout << "\n--- TODO LIST MANAGER ---\n";
        std::cout << "1. Create Task\n";
        std::cout << "2. View Tasks\n";
        std::cout << "3. Update Task\n";
        std::cout << "4. Delete Task\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";

        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "What is the priority level of the task? (1-3 high to low).\n";
                std::cin >> priority;

                std::cout << "What is the title of your task? (i.e. Find Book)\n";
                std::cin >> title;

                std::cout << "What is the description of your task?\n";
                std::cin >> description;

                taskManager.CreateTask(priority, title, description);
                std::cout << "Task successfully created.\n";
                break;
            case 2:
                std::cout << "Would you like to view the tasks in order of priority or linearlly?(P or L)\n";
                std::cin >> displayChoice;

                if (std::toupper(displayChoice) == 'P')
                {
                    taskManager.displayAllByPriority();
                }
                else if (std::toupper(displayChoice) == 'L')
                {
                    taskManager.displayAllLinear();
                }
                else
                {
                    std::cout << "Improper input, please try again.";
                }

                break;
            case 3:
                taskManager.displayAllLinear();
                
                std::cout << "\nWhich task would you like to update?(ID).\n";
                std::cin >> upID;

                const Task& task = taskManager.readTask(upID);

                const std::string& status = task.isCompleted() ? "[X]" : "[ ]";
                std::cout << "  " << status << " ID: " << task.getID()
                          << " | " << task.getTitle() << "\n";
                if (!task.getDescription().empty()) {
                    std::cout << "      Desc: " << task.getDescription() << "\n";
                }

                std::cout << "What part of the task would you like to change? ((C)ompletion, (T)itle, (D)escription)";
                std::cin >> upChoice;

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