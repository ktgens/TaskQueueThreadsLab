#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <thread>
#include <chrono>

std::mutex coutmutex;

class TaskQueue
{
private:
    std::queue<int> tasks;
    std::mutex mutex;
    std::condition_variable condition;

public:
    bool isFinished = false;

    void AddTask(int i)
    {
        std::lock_guard<std::mutex> lock(mutex);
        tasks.push(i);
        condition.notify_one();
    }

    void Stop()
    {
        std::lock_guard<std::mutex> lock(mutex);
        isFinished = true;

        condition.notify_all();
    }

    bool GetTask(int& res)
    {
        std::unique_lock<std::mutex> lock(mutex);

        condition.wait(lock, [this]() {return !tasks.empty()||isFinished;});

        if (tasks.empty() && isFinished) return false;

        res = tasks.front();
        tasks.pop();

        return true;
    }
};

void ProcessTask(TaskQueue& taskQueue, int threadNum)
{
    int taskNum;

    while (taskQueue.GetTask(taskNum))
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        std::lock_guard<std::mutex> lock(coutmutex);
        std::cout << "[Worker-" << threadNum << "] обработал задачу " << taskNum << '\n';
    }

}

int main()
{
    setlocale(LC_ALL, "ru");

    int n = 5;

    TaskQueue taskQueue;
    std::vector<std::thread> threads;

    for (int i = 0; i < n;i++)
    {
        threads.push_back(std::thread(ProcessTask, std::ref(taskQueue), i));
    }

    for (int i = 1; i <= 20; i++)
    {
        taskQueue.AddTask(i);
    }

    taskQueue.Stop();

    for(auto& thread: threads )
    {
        thread.join();
    }
}

