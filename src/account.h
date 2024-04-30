#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "status.h"

int EffectHealthLoss(Status* losser, int loss_value);
int NonSourseDamage(Status* defender, int damage_value);
int Damage(Status* attacker, Status* defender, int damage_value, int card_sp_attr[], bool is_attacking = false);
int Damage(Status* attacker, Status* defender, int damage_value);
int Attack(Status* attacker, Status* defender, int attack_value, int card_sp_attr[]);
int Attack(Status* attacker, Status* defender, int attack_value);
int HealthSuck(Status* gainer, Status* loser, int suck_value);
int LingQiCostAll(Status* coster);
int LingQiCostMax(Status* coster, int max_cost_value);
int BuffGain(Status* gainer, int buff_type, int gain_value);
int BuffReduce(Status* reducer, int buff_type, int reduce_value);
int DebuffGain(Status* gainer, int debuff_type, int gain_value);
int ReexecuteGain(Status* gainer);
int ReexecuteLoss(Status* losser);
int ReexecuteAlreadyGain(Status* gainer);
int RandomNumber(int min, int max);
int DebuffReduce(Status* reducer, int debuff_type, int reduce_value);
int DebuffTotal(Status* status);
int* DebuffSort(Status* sorter);
int DebuffRandomReduce(Status* reducer, int reduce_value, bool is_transfer_to_enemy = false, Status* enemy = nullptr);

#endif // !ACCOUNT_H