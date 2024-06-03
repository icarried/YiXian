#include "zsxm_yyq.h"

const std::string Card_zsxm_yyq_bengquan_mingye::name = "崩拳·冥夜";
bool Card_zsxm_yyq_bengquan_mingye::registered = BaseCard::registerCard(Card_zsxm_yyq_bengquan_mingye::name, Card_zsxm_yyq_bengquan_mingye::create);

/*
锻玄宗_叶冥冥 专属仙命卡 崩拳·冥夜
！！目前未知升级效果
获得2/3/4层"冥"
持续：使用“崩拳”卡牌攻击时，自身每有1层负面状态，多1攻（最多+6/9/12）
*/
Card_zsxm_yyq_bengquan_mingye::Card_zsxm_yyq_bengquan_mingye(int level, int position) : BaseCard(level, position) {
    card_name = "崩拳·冥夜";
    is_attacking = false;
    card_tag[BENG_QUAN_CARD] = true;
    card_tag[CHI_XU_CARD] = true;
}

Card_zsxm_yyq_bengquan_mingye::Card_zsxm_yyq_bengquan_mingye(const Card_zsxm_yyq_bengquan_mingye& other) : BaseCard(other) {}

Card_zsxm_yyq_bengquan_mingye* Card_zsxm_yyq_bengquan_mingye::Clone() const {
    return new Card_zsxm_yyq_bengquan_mingye(*this);
}

int Card_zsxm_yyq_bengquan_mingye::Effect(Status* my_status, Status* enemy_status) {
    int ming_gain = 1 + level;
    int temp_attack_max = 3 + 3 * level;
    my_status->debuffs[DEBUFF_MING]->add(ming_gain);
    my_status->task_quene_before_effect->addTask(
        [my_status, temp_attack_max](BaseCard* card){
            int temp_attack = DebuffTotal(my_status);
            if (temp_attack > temp_attack_max) temp_attack = temp_attack_max;
            card->card_sp_attr[CARD_SP_ATTR_DUO_GONG] += temp_attack;
            my_status->task_quene_after_effect->addTask(
                [my_status, temp_attack](BaseCard* card){
                    card->card_sp_attr[CARD_SP_ATTR_DUO_GONG] -= temp_attack;
                },
                [](BaseCard* card){ return true; },
                [](BaseCard* card){ return true; }
            );
        },
        [](BaseCard* card){ return card->card_tag[BENG_QUAN_CARD] && card->is_attacking ? true : false; },
        [](BaseCard* card){ return true; },
        REMARK_BENG_QUAN
    );
    return 0;
}

BaseCard* Card_zsxm_yyq_bengquan_mingye::create(int level, int position) {
    return new Card_zsxm_yyq_bengquan_mingye(level, position);
}