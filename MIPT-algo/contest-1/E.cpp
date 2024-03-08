#include <iostream>
#include <vector>

using namespace std;

void swap(pair<int, int>& a, pair<int, int>& b) {
    pair<int, int> tmp = a;
    a = b;
    b = tmp;
}

int partition(vector<pair<int, int>>& a, pair<int, int> pivot, int l, int r) {
    int i = l;
    int first_ge = l;

    while (i <= r) {
        if (a[i] >= pivot) {
            ++i;
        } else {
            swap(a[i++], a[first_ge++]);
        }
    }

    return first_ge;
}


void quick_sort(vector<pair<int, int>>& a, int l, int r) {
    if (l >= r) {
        return;
    }

    

    int pivot_ind = (std::rand() % (r - l + 1)) + l;
    pair<int, int> pivot = a[pivot_ind];

    // wall - по сути, количество чисел, строго меньших pivot.
    int wall = partition(a, pivot, l, r);
    /*
        Теперь надо выделить только те элементы, которые сторого больше.
        Для этого, расположем все pivot посередине, а так же, подсчитаем их количество.
    */
    int pivot_cnt = 0;

    for (int i = wall; i <= r; ++i) {
        if (a[i] == pivot) {
            swap(a[i], a[wall + pivot_cnt++]);
        }
    }

    quick_sort(a, l, wall - 1);
    quick_sort(a, wall + pivot_cnt, r);
}


void quick_sort(vector<pair<int, int>>& a) {
    std::srand(time(NULL));
    quick_sort(a, 0, a.size() - 1);
}

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);


    for (int i = 0; i < n; ++i) {
        int x1, x2;
        cin >> x1 >> x2;
        pair<int, int> pr {x1, x2};
        a[i] = pr;
    }

    quick_sort(a);
    // for (int i = 0; i < n; ++i) {
    //     cout << a[i].first << ' ' << a[i].second << '\n';
    // }
    int st = a[0].first;
    int end = a[0].second;

    vector<pair<int, int>> ans;

    for (int i = 1; i < n; ++i) {
        // cout << "a[i].fisrt = " << a[i].first << ' ' << "a[i].second = " << a[i].second << endl;
        // cout << "st = " << st << ' ' << "end = " << end << endl << endl;
        if (a[i].first <= end) {
            end = std::max(a[i].second, end);
        } else {
            // cout << "HERE!!" << endl;
            ans.push_back({st, end});
            st = a[i].first;
            end = a[i].second;
        }
    }
    ans.push_back({st, end});
    cout << ans.size() << '\n';
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i].first << ' ' << ans[i].second << '\n';
    }

}