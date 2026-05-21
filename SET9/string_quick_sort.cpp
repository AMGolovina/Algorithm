#include <iostream>
#include <string>
#include <vector>

void quickString(std::vector<std::string>& arr, const int left, const int right, const int d) {
    if (left >= right) {
        return;
    }

    int lt = left;
    int gt = right;
    int v;

    if (d == static_cast<int>(arr[left].size())) {
        v = -1;
    } else {
        v = static_cast<unsigned char>(arr[left][d]);
    }

    int i = left + 1;

    while (i <= gt) {
        int t;
        if (d == static_cast<int>(arr[i].size())) {
            t = -1;
        } else {
            t = static_cast<unsigned char>(arr[i][d]);
        }

        if (t < v) {
            const std::string temp = arr[lt];
            arr[lt] = arr[i];
            arr[i] = temp;
            ++lt;
            ++i;
        } else if (t > v) {
            const std::string temp = arr[i];
            arr[i] = arr[gt];
            arr[gt] = temp;
            --gt;
        } else {
            ++i;
        }
    }

    quickString(arr, left, lt - 1, d);

    if (v != -1) {
        quickString(arr, lt, gt, d + 1);
    }

    quickString(arr, gt + 1, right, d);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::string> words(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> words[i];
    }

    quickString(words, 0, n - 1, 0);

    for (int i = 0; i < n; ++i) {
        std::cout << words[i] << '\n';
    }

    return 0;
}
