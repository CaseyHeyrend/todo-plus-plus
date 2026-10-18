#ifndef TASK_H
#define TASK_H

#include <string>
using namespace std;

class Task
{
private:
    string name;
    bool completed;

public:
    Task(string taskName)
    {
        name = taskName;
        completed = false;
    }

    string getName() const
    {
        return name;
    }

    bool isCompleted() const
    {
        return completed;
    }

    void complete()
    {
        completed = true;
    }
};

#endif