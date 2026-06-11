#include "task.h"


// Constructor
Task::Task(int id, int priority, const std::string& title, const std::string& description) 
    : id(id), priority(priority), title(title), description(description), completed(false)
{
    // Initializer used so inside is blank
}
// Getters
const int Task::getID()
{
    return id;
}
const int Task::getPriority()
{
    return priority;
}
const std::string Task::getTitle()
{
    return title;
}
const std::string Task::getDescription()
{
    return description;
}
const bool Task::isCompleted()
{
    return completed;
}
// Setters
void Task::setTitle(const std::string& newTitle)
{
    title = newTitle;
}
void Task::setPriority(int newPriority)
{
    priority = newPriority;
}
void Task::setDescription(const std::string& newDescription)
{
    description = newDescription;
}
void Task::markComplete()
{
    completed = true;
}