/*
    Пусть мы вставляем число k.

    Рассмотрим 4 варианта:
    1) Чисел k + 1 и k - 1 нет в map => кладём в map пару <k, 1>. Ответ не меняем,
    не появилось новой последовательности длины больше предыдущей (изначально ответ
    равен 1, т.к. всегда есть последовательность длины 1)

    2) Есть только число k + 1. Тогда у k + 1 в словаре в качестве значения 
    записано, сколько идёт чисел в последовательность. Пусть их m - штук.
    
    Т.е. есть последовательность:
    k, k + 1, k + 2, ..., k + m, где m >= 1.

    Значение ключа k + m увеличим на 1.
    Значение ключа k сделаем равным значению ключа k + m.

    Теперь у нас оба конца отображают верную информацию о последовательности.
    Если мы в дальнейшем к этой последовательности будем прибавлять ещё что-то,
    то всё будет ок.

    3) Если есть только k - 1.

    В k - 1 записано m. Значит есть последовательность:

    k - m, k - m + 1, ...., k - 2, k - 1
    Допишем к последовательности k:

    Увеличим значение под ключом k - m на 1
    В ключ k положим такое же значение


    4) Есть оба:

    В k - 1 записано m'
    В k + 1 записано m

    В k - m' запишем m' + 1 + m
    В k + m запишем m' + 1 + m 
*/


class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int n = nums.size();
        if (!n) {
            return 0;
        }

        int ans = 1;

        unordered_map<int, int> mp;

        for (int num : nums) {
            if (!mp.contains(num)) {

                if (!mp.contains(num - 1) && !mp.contains(num + 1)) {
                    mp[num] = 1;
                } else if (!mp.contains(num - 1) && mp.contains(num + 1)) {
                    int m = mp[num + 1];

                    ++mp[num + m];
                    mp[num] = mp[num + m];
                    ans = max(ans, mp[num]);
                } else if (mp.contains(num - 1) && !mp.contains(num + 1)) {
                    int m = mp[num - 1];

                    ++mp[num - m];
                    mp[num] = mp[num - m];
                    ans = max(ans, mp[num]);
                } else {
                    int m_left = mp[num - 1];
                    int m_right = mp[num + 1];

                    mp[num - m_left] += m_right + 1;
                    mp[num + m_right] = mp[num - m_left];
                    mp[num] = mp[num - m_left];
                    ans = max(ans, mp[num + m_right]);
                }
            }
        }

        return ans;
    }
};