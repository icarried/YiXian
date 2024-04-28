#include "status.h"
#include "deck.h"
#include "head.h"

/*
实现：获取Deck中position位置的卡牌指针
*/
BaseCard* Status::GetCard(int position) {
    return deck->GetCard(position);
}

