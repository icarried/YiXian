#ifndef EFFECT_TASK_QUENE_H
#define EFFECT_TASK_QUENE_H

#include "head.h"
#include <algorithm>
#include <vector>
#include <functional>

class Status; // 前置声明
class BaseCard; // 前置声明

// 定义任务的备注
#define REMARK_NONE "" // 无备注
#define REMARK_BENG_QUAN "beng_quan" // 崩拳

/**
 * 卡牌效果任务队列
 * 围绕卡牌效果的任务队列，用于处理卡牌效果的执行和移除，例如持续效果
 * 也包括卡牌效果执行前后的额外效果
 * 参数为使用的卡牌指针
*/
class EffectTaskQueue {
public:
    EffectTaskQueue(Status *status) : status(status) {}

    // 虚拷贝函数
    virtual EffectTaskQueue* Clone(Status *new_status) {
        return new EffectTaskQueue(*this, new_status);
    }

    // 拷贝构造函数
    EffectTaskQueue(const EffectTaskQueue& other, Status *new_status) {
        status = new_status;
        taskQueue = other.taskQueue; // 任务队列，因为Task是可以拷贝的
        // 新队列无需初始化待移除任务
    }

    // 添加任务到队列
    //
    //使用示例：
    //taskQueue.addTask([my_status, 额外参数](BaseCard*){ do something; }, // 执行函数
    //                  [](BaseCard*){ return true; }, // 执行条件
    //                  [](BaseCard*){ return true; }, // 执行后移除条件，如果不需要移除，如持续牌效果，return false
    //                  （可选）备注 // 例如：REMARK_BENG_QUAN, "xxxxx"
    //                  是否确保所备注任务唯一
    //                 );
    //
    void addTask(std::function<void(BaseCard*)> function,
             std::function<bool(BaseCard*)> executeCondition,
             std::function<bool(BaseCard*)> removeCondition,
             std::string remark = REMARK_NONE,
             bool ensureSingleRemark = false) {
        if (ensureSingleRemark) {
            auto it = std::find_if(taskQueue.begin(), taskQueue.end(), [&](const Task& t) {
                return t.remark == remark;
            });
            if (it != taskQueue.end()) {
                return;
            }
        }
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
        std::string remark;
    };

    std::vector<Task> taskQueue; // 任务队列
    std::vector<Task*> tasksToRemove;
};

#endif // EFFECT_TASK_QUENE_H