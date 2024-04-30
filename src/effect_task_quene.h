#ifndef EFFECT_TASK_QUENE_H
#define EFFECT_TASK_QUENE_H

#include "head.h"
#include <algorithm>
#include <vector>
#include <functional>

class Status; // 前置声明
class BaseCard; // 前置声明

// 定义任务的备注
#define REMARK_NONE 0 // 无备注
#define REMARK_BENG_QUAN 1 // 崩拳

// 卡牌效果任务队列
class EffectTaskQueue {
public:
    EffectTaskQueue(Status *status) : status(status) {

    }
    // 添加任务到队列
    //
    //使用示例：
    //taskQueue.addTask([my_status, 额外参数](BaseCard*){ do something; }, // 执行函数
    //                  [](BaseCard*){ return true; }, // 执行条件
    //                  [](BaseCard*){ return true; }, // 执行后移除条件，如果不需要移除，如持续牌效果，return false
    //                  （可选）备注 // 例如：REMARK_BENG_QUAN
    //                 );
    //
    void addTask(std::function<void(BaseCard*)> function,
                 std::function<bool(BaseCard*)> executeCondition,
                 std::function<bool(BaseCard*)> removeCondition,
                 int remark = 0) {
        Task task{function, executeCondition, removeCondition, remark};
        taskQueue.push_back(task);
    }

    // 执行任务队列
    void executeTaskQueue(BaseCard* card) {
        tasksToRemove.clear();

        for (auto& task : taskQueue) {
            if (task.executeCondition(card)) {
                task.function(card);
                if (task.removeCondition(card)) {
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
        std::function<void(BaseCard*)> function;
        std::function<bool(BaseCard*)> executeCondition;
        std::function<bool(BaseCard*)> removeCondition;
        int remark;
    };

    std::vector<Task> taskQueue; // 任务队列
    std::vector<Task*> tasksToRemove;
};

#endif // EFFECT_TASK_QUENE_H