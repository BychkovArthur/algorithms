#include <iostream>
#include <vector>

using namespace std;

std::pair<int, int> partition(vector<int>& vct, int pivot, int l, int r) {
    int i = l;
    int first_ge = l;

    while (i <= r) {
        
        if (vct[i] >= pivot) {
            ++i;
        } else {
            swap(vct[i++], vct[first_ge++]);
        }

    }

    int last_lower_ind = first_ge - 1;
    int first_greater_ind = first_ge;
    
    for (int i = first_ge; i <= r; ++i) {
        if (vct[i] == pivot) {
            swap(vct[first_greater_ind++], vct[i]);
        }
    }
    return {last_lower_ind, first_greater_ind};
}

int quick_select(vector<int>& vct, int k, int l, int r) {

    int pivot_ind = (std::rand() % (r - l + 1)) + l;
    int pivot = vct[pivot_ind];

    // pivot = 555;

    pair<int, int> partition_res = partition(vct, pivot, l, r);
    int last_lower_ind = partition_res.first;
    int first_greater_ind = partition_res.second;


    if (last_lower_ind < k && k < first_greater_ind) {
        return pivot;
    }
    if (l <= k && k <= last_lower_ind) {
        return quick_select(vct, k, l, last_lower_ind);
    }
    return quick_select(vct, k, first_greater_ind, r);
}

int quick_select(vector<int>& vct, int k) {

    if (k < 0 || k >= vct.size()) {
        throw std::out_of_range("Неверный номер статистики!");
    }

    std::srand(time(NULL));
    return quick_select(vct, k, 0, vct.size() - 1);

}


int main() {

    int n, k, a0, a1;
    cin >> n >> k >> a0 >> a1;

    vector<int> vct(n);
    vct[0] = a0;
    vct[1] = a1;
    for (int i = 2; i < n; ++i) {
        vct[i] = (vct[i - 1] * 123 + vct[i - 2] * 45) % (10'000'000 + 4321);
    }

    cout << quick_select(vct, k - 1);
}