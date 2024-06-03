#ifndef ACCOUNT_TASK_QUENE_H
#define ACCOUNT_TASK_QUENE_H

#include "head.h"
#include <vector>
#include <functional>

class Status; // 前置声明

// 定义任务的备注
// #define REMARK_NONE "" // 无备注

/**
 * 结算效果任务队列
 * 围绕状态的一系列结算，包括状态值、buff、debuff等
 * 参数为状态指针
*/
class AccountTaskQueue {
public:
    AccountTaskQueue(Status *status) : status(status) {}

    // 虚拷贝函数
    virtual AccountTaskQueue* Clone(Status *new_status) {
        return new AccountTaskQueue(*this, new_status);
    }

    // 拷贝构造函数
    AccountTaskQueue(const AccountTaskQueue& other, Status *new_status) {
        status = new_status;
        taskQueue = other.taskQueue; // 任务队列，因为Task是可以拷贝的
        // 新队列无需初始化待移除任务
    }

    // 添加任务到队列
    //
    //使用示例：
    //taskQueue.addTask([my_status, 额外参数](int){ do something; }, // 执行函数
    //                  [](int){ return true; }, // 执行条件
    //                  [](int){ return true; }, // 执行后移除条件，如果不需要移除，return false
    //                  （可选）备注
    //                 );
    //
    void addTask(std::function<void(int)> function,
                 std::function<bool(int)> executeCondition,
                 std::function<bool(int)> removeCondition,
                 std::string remark = "") {
        Task task{function, executeCondition, removeCondition, remark};
        taskQueue.push_back(task);
    }

    // 执行任务队列
    void executeTaskQueue(int value) {
        tasksToRemove.clear();

        for (auto& task : taskQueue) {
            if (task.executeCondition(value)) {
                task.function(value);
                if (task.removeCondition(value)) {
                    tasksToRemove.push_back(&task);
                }
            }
        }

        for (auto taskPtr : tasksToRemove) {
            auto it = std::find_if(taskQueue.begin(), taskQueue.end(), [&](const Task& t) {
                return &t == taskPtr;
            });
            if (it != taskQueue.end()) {
                taskQueue.erase(it);
            }
        }
    }


    Status *status;
    // 任务结构体
    struct Task {
        std::function<void(int)> function;
        std::function<bool(int)> executeCondition;
        std::function<bool(int)> removeCondition;
        std::string remark;
    };

    std::vector<Task> taskQueue; // 任务队列
    std::vector<Task*> tasksToRemove;
};

#endif // ACCOUNT_TASK_QUENE_H