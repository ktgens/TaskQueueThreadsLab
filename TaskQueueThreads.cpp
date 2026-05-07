#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include <chrono>

class TaskQueue
{
private:
    std::queue<int> tasks;
    std::mutex mutex;
    std::condition_variable condition;

public:
    void AddTask(int i)
    {
        mutex.lock();
        tasks.push(i);
        condition.notify_one();
    }

    void GetTask()
    {

    }
};

void Process(int i)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "[Worker-" << i << "] обработал задачу " << i;
}

int main()
{
    TaskQueue taskQueue;
    for (int i = 1; i <= 20; i++)
    {
        taskQueue.AddTask(i);
    }
}

