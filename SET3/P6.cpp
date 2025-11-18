#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <bitset>

bool place(int col,
               int n,
               std::vector<int>& pos,
               std::bitset<200>& used_col,
               std::bitset<400>& used_d1,
               std::bitset<400>& used_d2,
               std::mt19937& gen)
{
    if (col == n) {
        return true;
    }

    std::vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = i;
    }
    std::shuffle(order.begin(), order.end(), gen);

    for (int r : order) {
        int d1_idx = 200 + r - col;
        int d2_idx = r + col;

        if (used_col[r] || used_d1[d1_idx] || used_d2[d2_idx]) {
            continue;
        }

        pos[col] = r;
        used_col[r] = true;
        used_d1[d1_idx] = true;
        used_d2[d2_idx] = true;

        if (place(col + 1, n, pos, used_col, used_d1, used_d2, gen)) {
            return true;
        }

        used_col[r] = false;
        used_d1[d1_idx] = false;
        used_d2[d2_idx] = false;
    }

    return false;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> pos(n);
    const int max_n = 200;
    std::bitset<max_n> col;
    std::bitset<2 * max_n> d1;
    std::bitset<2 * max_n> d2;

    std::mt19937 gen(40);

    if (place(0, n, pos, col, d1, d2, gen)) {
        for (int col = 0; col < n; ++col) {
            std::cout << pos[col] + 1 << ' ';
        }
    }
}
