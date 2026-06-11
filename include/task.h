#pragma once

#include <string>

class Task {
    private:
        int id;
        int priority;
        bool completed;
        std::string title;
        std::string description;
    public:
        // Constructor
        Task(int id, int priority, const std::string& title, const std::string& description);
        // Getters
        const int getID();
        const int getPriority();
        const std::string getTitle();
        const std::string getDescription();
        const bool isCompleted();
        // Setters
        void setPriority(int newPriority);
        void setTitle(const std::string& newTitle);
        void setDescription(const std::string& newDescription);
        void markComplete();

};