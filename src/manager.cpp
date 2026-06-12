#include "manager.h"
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

        taskManager[id] = loadedTask;

        int index = getBucketIndex(priority);
        taskPriority[index].push_back(id);
    }
}