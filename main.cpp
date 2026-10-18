#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Task.h"

using namespace std;

// Function to display the menu
void displayMenu()
{
    cout << "\n To-Do List\n";
    cout << "1. Add Task\n";
    cout << "2. View Tasks\n";
    cout << "3. Remove Task\n";
    cout << "4. Complete Task\n";
    cout << "5. Search Tasks\n";
    cout << "6. Exit\n";
    cout << "Enter your option: ";
}
// Save tasks to a file
void saveTasks(const vector<Task>& tasks)
{
    ofstream file("tasks.csv");
    
    if (!file)
    {
        cout << "Unable to save tasks. Try again.\n";
        return;
    }
    file << "Task\n"; // Write header
    for (const Task& task : tasks)
    {
        file << task.getName() << "," << task.isCompleted() << '\n';
    }
    file.close();
}

// Load tasks from a file
void loadTasks(vector<Task>& tasks)
{
    ifstream file("tasks.csv");

    if (!file)
    {
        return; // No tasks to load
    }
    string taskName;
    string completed;

    getline(file, taskName);

    while (getline(file, taskName, ',') && getline(file, completed))
    {
        Task task(taskName);

        if (completed == "1")
        {
            task.complete();
        }

        tasks.push_back(task);
    }
    file.close();
}

// Function to add a task
void addTask(vector<Task>& tasks)
{
    string task;
        
    cout << "Enter a task: ";
    getline(cin, task);

    if (task.empty())
    {
        cout << "Task cannot be empty. Please enter a valid task.\n";
        return;
    }
        
    tasks.push_back(Task(task));
    saveTasks(tasks);
    cout << "Task added!\n";
}

// Display all tasks
void viewTasks(const vector<Task>& tasks)
{
    if (tasks.empty())
    {
        cout << "You have no tasks yet.\n";
        return;
    }
    cout << "\nYour Tasks:\n";
    for (int i = 0; i < static_cast<int>(tasks.size()); i++)
    {
        cout << i + 1 << ". " << tasks[i].getName();

    if (tasks[i].isCompleted())
    {
        cout << " [Completed]";
    }

    cout << '\n';
    }
}
// Mark a task as completed
void completeTask(vector<Task>& tasks)
{
    if (tasks.empty())
    {
        cout << "You have no tasks to complete.\n";
        return;
    }

    viewTasks(tasks);

    int taskNumber;
    cout << "Enter the task number to complete: ";

    cin >> taskNumber;
    cin.ignore(10000, '\n');

    if (taskNumber < 1 || taskNumber > static_cast<int>(tasks.size()))
    {
        cout << "Invalid task number.\n";
        return;
    }

    tasks[taskNumber - 1].complete();

    cout << "Task marked as completed!\n";
}
// Search for tasks by keyword
void searchTasks(const vector<Task>& tasks)
{
    string search;
    cout << "Enter a word to search for: ";
    getline(cin, search);

    bool found = false;

    for (int i = 0; i < static_cast<int>(tasks.size()); i++)
    {
        if (tasks[i].getName().find(search) != string::npos)
        {
            cout << i + 1 << ". " << tasks[i].getName() << '\n';
            found = true;
        }
    }

    if (!found)
    {
        cout << "No tasks found.\n";
    } 
}

// Remove a task by its number
void removeTask(vector<Task>& tasks)
{
    if (tasks.empty())
    {
        cout << "You have no tasks to remove.\n";
        return;
    }

    viewTasks(tasks);
    int taskNumber;
    cout << "Enter the task number to remove: ";
    if (!(cin >> taskNumber))
    {
        cout << "Invalid input. Please enter a valid task number.\n";
        cin.clear(); // Clear the error flag
        cin.ignore(10000, '\n'); // Discard invalid input
        return;
    }
    cin.ignore(10000, '\n'); // Discard the newline character

    if (taskNumber < 1 || taskNumber > static_cast<int>(tasks.size()))
    {
        cout << "Invalid task number. Please try again.\n";
        return;
    }
    tasks.erase(tasks.begin() + taskNumber - 1);
    saveTasks(tasks);
    cout << "Task removed!\n";
}

int main()
{
    vector<Task> tasks;
    loadTasks(tasks); // Load existing tasks from file
    int choice = 0;

    do
    {
        displayMenu();

        if (!(cin >> choice))
        {
            cout << "Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        cin.ignore(10000, '\n');

        if (choice == 1)
        {
            addTask(tasks);
        }
        else if (choice == 2)
        {
            viewTasks(tasks);
        }
        else if (choice == 3)
        {
            removeTask(tasks);
        }
        else if (choice == 4)
        {
            completeTask(tasks);
        
        }
        else if (choice == 5)
        {
            searchTasks(tasks);
        }
        else if (choice == 6)
        {
            cout << "Thanks for using ToDo++!\n";
        }
        else
        {
            cout << "Invalid option. Please try again.\n";
        }

    } while (choice != 6);

    return 0;
}