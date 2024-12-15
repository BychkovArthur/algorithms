#include <vector>
#include <iostream>
#include <optional>
#include <algorithm>


std::optional<int> find_row_index(const std::vector<std::vector<double>>& matrix, const std::vector<int>& prices, int column_index) {
    int min_cost = 1e9;
    std::optional<int> min_index;

    for (int i = column_index; i < matrix.size(); ++i) {
        if (matrix[i][column_index] != 0 && prices[i] < min_cost) {
            min_index = i;
            min_cost = prices[i];
        }
    }
    return min_index;
}

void do_substraction(std::vector<std::vector<double>>& matrix, int base) {
    for (int i = base + 1; i < matrix.size(); ++i) {
        double coef = matrix[i][base] / matrix[base][base];
        for (int j = base; j < matrix[0].size() - 1; ++j) {
            matrix[i][j] -= matrix[base][j] * coef;
        }
    }
}


int main() {
    int n, m;
    std::cin >> m >> n;
    std::vector<std::vector<double>> matrix(m, std::vector<double>(n + 1));
    std::vector<int> prices(m);
    int ans = 0;
    std::vector<int> lines;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> matrix[i][j];
        }
        matrix[i][n] = i;
        std::cin >> prices[i];
    }

    if (m < n) {
        std::cout << -1;
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        auto min_index = find_row_index(matrix, prices, i);
        if (!min_index) {
            std::cout << -1;
            return 0;
        }
        std::swap(matrix[i], matrix[min_index.value()]);
        std::swap(prices[i], prices[min_index.value()]);
        ans += prices[i];
        lines.push_back(matrix[i][n]);
        do_substraction(matrix, i);
    }

    std::sort(lines.begin(), lines.end());
    for (const auto& el : lines) {
        std::cout << el + 1 << ' ';
    }
}