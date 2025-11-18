#include <iostream>
#include <vector>

void countingSort(std::vector<int>& v) {
    int n = (int)v.size();
    if (n == 0) return;

    int minVal = v[0];
    int maxVal = v[0];
    for (int i = 1; i < n; ++i) {
        if (v[i] < minVal) minVal = v[i];
        if (v[i] > maxVal) maxVal = v[i];
    }

    int range = maxVal - minVal + 1;
    std::vector freq(range, 0);

    for (int x : v) {
        freq[x - minVal]++;
    }

    int pos = 0;
    for (int idx = 0; idx < range; ++idx) {
        int cnt = freq[idx];
        int value = minVal + idx;
        while (cnt--) v[pos++] = value;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> v;
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        v.push_back(x);
    }

    countingSort(v);

    for (auto x : v) {
        std::cout << x << ' ';
    }
}
