#include "manager.h"
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdexcept>

Manager::Manager()
{
    loadFromFile();
}

int Manager::getBucketIndex(int priority) const
{
    if (priority < 1 || priority > 3) {
        throw std::out_of_range("Priority must be between 1 and 3.");
    }
    return priority - 1;
}

void Manager::saveToFile() const
{
    std::ofstream outFile("tasks.txt");
    if (!outFile) {
        std::cerr << "Error opening file for write." << std::endl;
        return;
    }
    for (const auto& pair : taskManager) {
        const Task& task = pair.second;

        outFile << task.getID() << "|" 
            << task.getPriority() << "|"
            << task.isCompleted() << "|"
            << task.getTitle() << "|"
            << task.getDescription() << "\n";
    }

    outFile.close();
}

bool Manager::isEmpty() const {
    return taskManager.empty();
}

void Manager::loadFromFile()
{
    std::ifstream inFile("tasks.txt");
    if (!inFile) {
        std::cerr << "Error opening file to read." << std::endl;
        return;
    }

    std::string line;

    while (std::getline(inFile, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);

        std::string idStr, priorityStr, compStr, title, description;

        std::getline(ss, idStr, '|');
        std::getline(ss, priorityStr, '|');
        std::getline(ss, compStr, '|');
        std::getline(ss, title, '|');
        std::getline(ss, description, '\n');

        int id = std::stoi(idStr);
        int priority = std::stoi(priorityStr);
        bool completed = (compStr == "1");

        Task loadedTask(id, priority, completed, title, description);

        taskManager.insert_or_assign(id, loadedTask);

        int index = getBucketIndex(priority);
        taskPriority[index].push_back(id);

        if (id >= nextID) {
            nextID = id + 1;
        }
    }

    inFile.close();
}

void Manager::CreateTask(int priority, const std::string& title, const std::string& description)
{
    Task newTask(nextID, priority, false, title, description);

    taskManager.insert_or_assign(nextID, newTask);

    int index = getBucketIndex(priority);
    taskPriority[index].push_back(nextID);

    nextID++;

    saveToFile();
}

const Task& Manager::readTask(int id) const
{
    auto it = taskManager.find(id);

    if (it == taskManager.end()) {
        throw std::out_of_range("Task with that ID not found in system.");
    }

    return it->second;
}

void Manager::updateTaskTitle(int id, const std::string& newTitle)
{
    auto it = taskManager.find(id);

    if (it == taskManager.end()) {
        throw std::out_of_range("Task with that ID not found in system.");
    }

    it->second.setTitle(newTitle);
    saveToFile();
}

void Manager::updateTaskPriority(int id, int newPriority)
{
    auto it = taskManager.find(id);

    if (it == taskManager.end()) {
        throw std::out_of_range("Task with that ID not found in system.");
    }

    int oldPriority = it->second.getPriority();

    if (oldPriority != newPriority) {
        int oldIdx = getBucketIndex(oldPriority);
        auto& oldBucket = taskPriority[oldIdx];
        oldBucket.erase(std::remove(oldBucket.begin(), oldBucket.end(), id), oldBucket.end());

        int newIdx = getBucketIndex(newPriority);
        taskPriority[newIdx].push_back(id);

        it->second.setPriority(newPriority);
        saveToFile();
    }
}

void Manager::updateCompletionStatus(int id)
{
    auto it = taskManager.find(id);

    if (it == taskManager.end()) {
        throw std::out_of_range("Task with that ID not found in system.");
    }

    it->second.markComplete();
    saveToFile();
}

void Manager::updateTaskDescription(int id, const std::string& newDescription)
{
    auto it = taskManager.find(id);

    if (it == taskManager.end()) {
        throw std::out_of_range("Task with that ID not found in system.");
    }

    it->second.setDescription(newDescription);
    saveToFile();
}

void Manager::deleteTask(int id)
{
    auto it = taskManager.find(id);

    if (it == taskManager.end()) {
        throw std::out_of_range("Task with that ID not found in system.");
    }

    int index = getBucketIndex(it->second.getPriority());
    auto& bucket = taskPriority[index];
    bucket.erase(std::remove(bucket.begin(), bucket.end(), id), bucket.end());

    taskManager.erase(id);
    saveToFile();
}

void Manager::displayAllByPriority() const
{
    std::cout << "\n====================\n";
    std::cout << "      TO-DO LIST    \n";
    std::cout << "====================\n";
    
    for (int i = 0; i < 3; ++i) {

        if (i == 0) {
            std::cout << "\n====================\n";
            std::cout << "      High Priority    \n";
            std::cout << "====================\n";
        }
        else if (i == 1) {
            std::cout << "\n====================\n";
            std::cout << "     Medium Priority    \n";
            std::cout << "====================\n";
        }
        else {
            std::cout << "\n====================\n";
            std::cout << "      Low Priority    \n";
            std::cout << "====================\n";
        }

        const auto& bucket = taskPriority[i];

        if (bucket.empty()) {
            std::cout << " (No tasks in this category)\n";
            continue;
        }

        for (int id : bucket) {
            auto it = taskManager.find(id);
            if (it != taskManager.end()) {
                const Task& task = it->second;

                std::string status = task.isCompleted() ? "[X]" : "[ ]";
                std::cout << "  " << status << " ID: " << task.getID()
                          << " | " << task.getTitle() << "\n";
                if (!task.getDescription().empty()) {
                    std::cout << "      Desc: " << task.getDescription() << "\n";
                }
            }
        }
    }
}

void Manager::displayAllLinear() const 
{
    std::cout << "\n====================\n";
    std::cout << "      TO-DO LIST    \n";
    std::cout << "====================\n";

    if (taskManager.empty()) {
        std::cout << "No tasks found.\n";
        return;
    }

    for (const auto& pair : taskManager) {
        const Task& task = pair.second;

        std::string status = task.isCompleted() ? "[X]" : "[ ]";
        std::cout << "  " << status << " ID: " << task.getID()
                  << " | " << task.getTitle() << "\n";
        if (!task.getDescription().empty()) {
            std::cout << "      Desc: " << task.getDescription() << "\n";
        }
    }
}