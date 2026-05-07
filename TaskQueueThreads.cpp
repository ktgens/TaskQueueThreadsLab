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
        std::lock_guard<std::mutex> lock(mutex);
        tasks.push(i);
        condition.notify_one();
    }

    void GetTask()
    {

    }
};

void ProcessTask(TaskQueue& taskQueue)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "[Worker-" << 2 << "] обработал задачу " << 2;
}

int main()
{
    setlocale(LC_ALL, "ru");

    int n = 5;

    TaskQueue taskQueue;
    std::vector<std::thread> threads;

    for (int i = 0; i < n;i++)
    {
        threads.push_back(std::thread(ProcessTask, std::ref(taskQueue)));
    }

    for (int i = 1; i <= 20; i++)
    {
        taskQueue.AddTask(i);
    }

    for(auto& thread: threads )
    {
        thread.join();
    }
}

