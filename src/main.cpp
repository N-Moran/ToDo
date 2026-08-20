#include <iostream>
#include <string>
#include <limits>
#include "../include/manager.h"

int getValidInt(const std::string& prompt, int minVal = std::numeric_limits<int>::min(), int maxVal = std::numeric_limits<int>::max()) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= minVal && value <= maxVal) {
            return value;
        }
        std::cout << "Invalid input. Please enter a number";
        if (minVal != std::numeric_limits<int>::min() || maxVal != std::numeric_limits<int>::max()) {
            std::cout << " between " << minVal << " and " << maxVal;
        }
        std::cout << ".\n";

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string getValidString(const std::string& prompt) {
    std::string value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin >> std::ws, value);
        if (!value.empty()) {
            return value;
        }
        std::cout << "Input vannot be empty. Please try again.\n";
    }
}

char getValidChar(const std::string& prompt, const std::string& validChoices) {
    char value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            value = static_cast<char>(std::toupper(value));
            if (validChoices.find(value) != std::string::npos) {
                return value;
            }
        }

        std::cout << "Invalid input. Please try again.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main() {
    Manager taskManager;

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

        int choice = getValidInt("Enter your choice: ", 1, 5);

        switch (choice) {
            case 1:
            {
                int priority = getValidInt("What is the priority level of the task? (1-3 high to low): ", 1, 3);

                std::string title = getValidString("What is the title of your task? (i.e. Find Book): ");

                std::string description = getValidString("What is the description of your task?: ");

                taskManager.CreateTask(priority, title, description);
                std::cout << "Task successfully created.\n";
                break;
            }
            case 2:
            {
                char displayChoice = getValidChar("Would you like to view the tasks in order of priority or linearly?(P or L): ", "PL");

                if (std::toupper(displayChoice) == 'P')
                {
                    taskManager.displayAllByPriority();
                }
                else if (std::toupper(displayChoice) == 'L')
                {
                    taskManager.displayAllLinear();
                }

                break;
            }
            case 3:
            {
                taskManager.displayAllLinear();
                int upID = getValidInt("\nWhich task would you like to update? (ID): ");

                const Task& task = taskManager.readTask(upID);

                const std::string& status = task.isCompleted() ? "[X]" : "[ ]";
                std::cout << "  " << "Priority: " << task.getPriority() << "\n";
                std::cout << "  " << status << " ID: " << task.getID()
                          << " | " << task.getTitle() << "\n";
                if (!task.getDescription().empty()) {
                    std::cout << "      Desc: " << task.getDescription() << "\n";
                }

                char upChoice = getValidChar("What part of the task would you like to change? ((P)riority, (C)ompletion, (T)itle, (D)escription): ", "PCTD");

                if (upChoice == 'P')
                {
                    int priority = getValidInt("What is the new level of priority? (1-3): ", 1, 3);
                    taskManager.updateTaskPriority(upID, priority);
                }
                else if (upChoice == 'C')
                {
                    taskManager.updateCompletionStatus(upID);
                    std::cout << "Completion status updated.\n";
                }
                else if (upChoice == 'T')
                {
                    std::string title = getValidString("What would you like the new title to be?: ");
                    taskManager.updateTaskTitle(upID, title);
                }
                else if (std::toupper(upChoice) == 'D')
                {
                    std::string description = getValidString("What would you like the new description to be?: ");
                    taskManager.updateTaskDescription(upID, description);
                }
                break;
            }
            case 4:
            {
                taskManager.displayAllLinear();

                if (taskManager.isEmpty()) {
                    break;
                }

                std::cout << "\nWhich task would you like to delete?(ID).\n";
                std::cin >> upID;

                const Task& task = taskManager.readTask(upID);

                const std::string& status = task.isCompleted() ? "[X]" : "[ ]";
                std::cout << "  " << "Priority: " << task.getPriority() << "\n";
                std::cout << "  " << status << " ID: " << task.getID()
                          << " | " << task.getTitle() << "\n";
                if (!task.getDescription().empty()) {
                    std::cout << "      Desc: " << task.getDescription() << "\n";
                }

                char confirm = getValidChar("Are you sure you want to delete this task? (Y or N): ", "YN");

                if (confirm == 'Y')
                {
                    taskManager.deleteTask(upID);
                    std::cout << "Task deleted...\n";
                }
                else
                {
                    std::cout << "Process aborted...\n";
                }
                break;
            }
            case 5:
            {
                std::cout << "Exiting program...." << "\n";
                return 0;
            }
            default:
            {
                std::cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    }
}