#include "task.h"


// Constructor
Task::Task(int id, const std::string& title, const std::string& description) 
    : id(id), title(title), description(description), completed(false)
{
    // Initializer used so inside is blank
}
// Getters
const int Task::getID()
{
    return id;
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
void Task::setDescription(const std::string& newDescription)
{
    description = newDescription;
}
void Task::markComplete()
{
    completed = true;
}