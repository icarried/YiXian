#include "base_card.h"

void BaseCard::DisplayCountMatrixGrid() {
        auto& registered_objects = BaseCard::getRegisteredObjectBySoVJRealmId();

        // 创建一个map来保存每个sovj和realm的计数
        std::map<std::string, std::map<int, int>> countMatrix;

        // 遍历字典，填充计数矩阵
        for (const auto& obj : registered_objects) {
            std::string sovj = std::get<0>(obj.first);
            int realm = std::get<1>(obj.first);

            // 检查是否存在对应的sovj，如果不存在则创建
            if (countMatrix.find(sovj) == countMatrix.end()) {
                countMatrix[sovj] = std::map<int, int>();
            }

            // 设置计数值
            countMatrix[sovj][realm]++;
        }
        
        // 获取sovj的最大长度
        int max_sovj_length = 0;
        for (const auto& kvp : countMatrix) {
            if (kvp.first.size() > max_sovj_length) {
                max_sovj_length = kvp.first.size();
            }
        }

        // 打印计数矩阵表格网格形式
        std::cout << "卡牌计数矩阵:" << std::endl;

        // 打印连接行
        std::cout << "---------";
        for (const auto& kvp : countMatrix.begin()->second) {
            std::cout << "---------";
        }
        std::cout << std::endl;

        // 打印第一行的realm标题
        std::cout << "| 境界";
        std::string realm_name = "境界";
        for (int i = 0; i < max_sovj_length - realm_name.size(); i++) {
                std::cout << " ";
            }
        std::cout << " |";
        for (const auto& kvp : countMatrix.begin()->second) {
            std::cout << " " << RealmToStr(kvp.first) << " |";
        }
        std::cout << std::endl;

        // 打印连接行
        std::cout << "---------";
        for (const auto& kvp : countMatrix.begin()->second) {
            std::cout << "---------";
        }
        std::cout << std::endl;

        // 打印sovj和计数值
        for (const auto& kvp : countMatrix) {
            std::cout << "| " << kvp.first;
            std::string sovj_name = kvp.first;
            for (int i = 0; i < max_sovj_length - sovj_name.size(); i++) {
                std::cout << " ";
            }
            std::cout << " |   ";
            for (const auto& entry : kvp.second) {
                std::cout << entry.second ;
                if (entry.second < 10) {
                    std::cout << "    |   ";
                }
                else {
                    std::cout << "   |   ";
                }
            }
            std::cout << std::endl;

            // 打印分隔行
            std::cout << "---------";
            for (const auto& entry : kvp.second) {
                std::cout << "---------";
            }
            std::cout << std::endl;
        }
    }