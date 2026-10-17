#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Function to display the menu
void displayMenu()
{
    cout << "\n To-Do List\n";
    cout << "1. Add Task\n";
    cout << "2. View Tasks\n";
    cout << "3. Remove Task\n";
    cout << "4. Exit\n";
    cout << "Enter your option: ";
}
// Save tasks to a file
void saveTasks(const vector<string>& tasks)
{
    ofstream file("tasks.csv");
    
    if (!file)
    {
        cout << "Unable to save tasks. Try again.\n";
        return;
    }
    file << "Task\n"; // Write header
    for (const string& task : tasks)
    {
        file << task << '\n';
    }
    file.close();
}

// Load tasks from a file
void loadTasks(vector<string>& tasks)
{
    ifstream file("tasks.csv");
    string task;

    if (!file)
    {
        return; // No tasks to load
    }
    getline(file, task); // Skip header
    while (getline(file, task))
    {
        if (!task.empty())
        {
            tasks.push_back(task);
        }
    }
    file.close();
}

// Function to add a task
void addTask(vector<string>& tasks)
{
    string task;
        
    cout << "Enter a task: ";
    getline(cin, task);

    if (task.empty())
    {
        cout << "Task cannot be empty. Please enter a valid task.\n";
        return;
    }
        
    tasks.push_back(task);
    saveTasks(tasks);
    cout << "Task added!\n";
}

// Display all tasks
void viewTasks(const vector<string>& tasks)
{
    if (tasks.empty())
    {
        cout << "You have no tasks yet.\n";
        return;
    }
    cout << "\nYour Tasks:\n";
    for (int i = 0; i < static_cast<int>(tasks.size()); i++)
    {
        cout << i + 1 << ". " << tasks[i] << '\n';
    }
}

// Remove a task by its number
void removeTask(vector<string>& tasks)
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
    vector<string> tasks;
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
            cout << "Thanks for using ToDo++!\n";
        }
        else
        {
            cout << "Invalid option. Please try again.\n";
        }

    } while (choice != 4);

    return 0;
}