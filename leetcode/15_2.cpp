class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> answer;
        size_t n = nums.size();
        set<pair<int, pair<int, int>>> st;

        sort(nums.begin(), nums.end());

        for (size_t i = 0; i < n; ++i) {
            // Пропускаем одинаковые
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }

            /*
                Пусть на определённом шаге было nums[i] = k.
                Тогда, мы нашли всевозможные тройки, в которых есть хотя бы один k.
                Поэтому, снова искать тройку с k нет смылса.
                Мы начинаем поиск с первого элемента, отличного от k.

                Рассмотрим пример из задания:
                [-1, 0, 1, 2, -1, -4]

                После сортировки получится:
                [-4, -1, -1, 0, 1, 2]

                Когда nums[i] = -1 (при i = 1)
                Мы найдём тройки [-1, -1, 2] и [-1, 0, 1]

                Если начинать с l = 0, тогда на следующей итерации, когда i = 3, nums[i] = 0
                Мы снова получим тройку  [-1, 0, 1].
                Это случится при l = 1, r = 4 и при l = 2, r = 4. 
                Т.е. мы снова будем перебирать одно и то же!!!

                Ещё немного:
                [-4, -1, -1, 0, 1, 2]
                1) Рассматриваем все тройки, где есть -4. Ни одна тройка не подходит
                => -4 вообще никак не можем учавствовать в сумме. Просто будем теперь 
                рассматривать массив без -4.
                [-1, -1, 0, 1, 2]
                2) Рассматриваем все тройки, где есть -1. Подошли две тройки. Больше троек,
                где есть -1 нет. Следовательно, удаляем все -1.
                [0, 1, 2]
                3) И т.д.

                Итого:
                Когда мы рассмотрели nums[i] = k, то мы нашли все тройки, где есть это k.
                Поэтому, нет смысла, чтобы в дальнейшем или nums[l] = k или nums[r] = k, 
                т.к. мы обработали уже эти варианты.
            */
            ssize_t l = i + 1;
            ssize_t r = n - 1;
            ssize_t target = 0 - nums[i];

            while (l < r) {

                if (nums[l] + nums[r] < target) {
                    ++l;
                } else if (nums[l] + nums[r] > target) {
                    --r;
                } else {
                    ssize_t mn = min(nums[i], min(nums[l], nums[r]));
                    ssize_t mx = max(nums[i], max(nums[l], nums[r]));
                    ssize_t md = nums[i] + nums[l] + nums[r] - mn - mx;
                    pair<int, pair<int, int>> pr;
                    pr.first = mn;
                    pr.second.first = md;
                    pr.second.second = mx;
                    st.insert(pr);
                    --r;
                }
            }
        }
        for (auto& pr : st) {
            answer.push_back({pr.first, pr.second.first, pr.second.second});
        }

        return answer;
    }
};