#pragma once

#include "task.h"
#include <vector>
#include <string>
#include <unordered_map>

class Manager {
    private:
        std::unordered_map<int, Task> taskManager;
        std::vector<int> taskPriority[3];
        int nextID = 1;

        // Internal Tools
        int getBucketIndex(int priority) const;
        void saveToFile() const;
        void loadFromFile();
    public:
        Manager();

        // CRUD functionality
        void CreateTask(const std::string& title, const std::string& description, int priority);
        Task readTask(int id) const;
        void updateTaskTitle(int id, const std::string& newTitle);
        void updateTaskPriority(int id, int newPriority);
        void updateTaskDescription(int id, const std::string& newDescription);
        void deleteTask(int id);

        // Display fucntionality
        void displayAllByPriority() const;
        void displayAllLinear() const;
};