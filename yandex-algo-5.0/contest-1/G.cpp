#include <iostream>
#include <algorithm>

using namespace std;


/*
    x - количество наших солдат
    y - здоровье вражеской казармы
    p - сколько казарма происходит врагов
    k - текущее количество врагов


    1) Если x <= 1/2 * k -> мы проиграли
    2) 


    *) Если врагов стало больше чем было, значит на прошлом шаге
    мы не убили всех врагов, но еще появились новые. Т.к. враги
    на прошлом шаге остались мы потеряли солдат. В итоге,
    количество врагов стало больше, а нас стало меньше.


    **) Отношение x/k с каждым шагом не должно уменьшаться.
    Если это отношение уменьшается, то оно станет еще меньше и на следующем шаге.
    В итоге дойдёт до того, что x/k <= 1/2 и мы просто проиграем сразу.

    Значит, мы должны посылать ровно столько солдат, чтобы на следующем шаге отношение
    не уменьшилось. Иначе, мы проиграем.

*/


int main() {

    int our_soldiers = 0;
    int enemy_soldiers = 0;
    int barraks_hp = 0;
    int enemy_soldiers_per_round = 0;

    cin >> our_soldiers >> barraks_hp >> enemy_soldiers_per_round;

    int steps = 0;



    /*
        Первый шаг, просто атакуем казарму.
    */
    barraks_hp -= our_soldiers;
    enemy_soldiers += enemy_soldiers_per_round;
    ++steps;

    while (true) {

        bool is_good_move = false;
        
        for (int soldiers_to_attack_barrack = min(barraks_hp, our_soldiers); soldiers_to_attack_barrack >= 0 ; --soldiers_to_attack_barrack) {

            // не может быть < 0
            int soldiers_to_attack_enemy = our_soldiers - soldiers_to_attack_barrack;

            int enemyes_after_my_attack = enemy_soldiers - soldiers_to_attack_enemy;          // mb < 0. Причём, такое возможно только в том случае, когда я ломаю казарму => победа.
            int our_soldiers_after_enemy_attack = our_soldiers - enemyes_after_my_attack;     // mb < 0. ГГ.

            int new_barrack_hp = barraks_hp - soldiers_to_attack_barrack;


            if (new_barrack_hp != 0 && new_barrack_hp == barraks_hp) { // Мы ничего не сделали...
                continue;
            }
            if (enemyes_after_my_attack <= 0)


            if (new_barrack_hp) {
                enemyes_after_my_attack += enemy_soldiers_per_round;
            }


            if (our_soldiers_after_enemy_attack * enemy_soldiers >= soldiers_to_attack_enemy * enemyes_after_my_attack) {
                is_good_move = true;
                barraks_hp
                break;
            }


            // if (soldiers_to_attack_enemy * enemyes_after_my_attack >= enemy_soldiers * our_soldiers_after_enemy_attack) {
                
            // }

        }

    }
    


}