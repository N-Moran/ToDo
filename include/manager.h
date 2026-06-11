#pragma once

#include "task.h"
#include <vector>
#include <string>
#include <unordered_map>

class Manager {
    private:
        std::unordered_map<int, Task> taskManager;
        std::vector<int> taskPriority;
}