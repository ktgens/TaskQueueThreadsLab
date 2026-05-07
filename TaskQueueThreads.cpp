#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>

class TaskQueue
{
private:
    std::queue<int> tasks;
    std::mutex mutex;
    std::condition_variable condition;

public:
    void AddTask(int i)
    {

    }

    void RemoveTask()
    {

    }
};

int main()
{
    TaskQueue taskQueue;
    for (int i = 1; i <= 20; i++)
    {
        taskQueue.AddTask(i);
    }
}

