#include <iostream>
#include <vector>

using namespace std;

void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

int partition(vector<int>& a, int pivot, int l, int r) {
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


void quick_sort(vector<int>& a, int l, int r) {
    if (l >= r) {
        return;
    }

    

    int pivot_ind = (std::rand() % (r - l + 1)) + l;
    int pivot = a[pivot_ind];

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


void quick_sort(vector<int>& a) {
    std::srand(time(NULL));
    quick_sort(a, 0, a.size() - 1);
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);


    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    quick_sort(a);
    for (int i = 0; i < n; ++i) {
        cout << a[i] << ' ';
    }
    cout << endl;
}