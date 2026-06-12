#include "task.h"


// Constructor
Task::Task(int id, int priority, bool completed, const std::string& title, const std::string& description) 
    : id(id), priority(priority), title(title), description(description), completed(false)
{
    // Initializer used so inside is blank
}
// Getters
int Task::getID() const
{
    return id;
}
int Task::getPriority() const
{
    return priority;
}
std::string Task::getTitle() const
{
    return title;
}
std::string Task::getDescription() const
{
    return description;
}
bool Task::isCompleted() const
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