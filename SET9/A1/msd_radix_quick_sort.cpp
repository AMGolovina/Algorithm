#include <iostream>
#include <string>
#include <vector>

constexpr int abc = 74;
constexpr int radix = 256;

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

void msdSort(std::vector<std::string>& arr, const int left, const int right, const int d, std::vector<std::string>& aux) {
    if (left >= right) {
        return;
    }

    if (right - left + 1 < abc) {
        quickString(arr, left, right, d);
        return;
    }

    std::vector count(radix + 2, 0);

    for (int i = left; i <= right; ++i) {
        int c;
        if (d == static_cast<int>(arr[i].size())) {
            c = -1;
        } else {
            c = static_cast<unsigned char>(arr[i][d]);
        }
        ++count[c + 2];
    }

    for (int i = 0; i < radix + 1; ++i) {
        count[i + 1] += count[i];
    }

    const std::vector<int> start = count;

    for (int i = left; i <= right; ++i) {
        int c;
        if (d == static_cast<int>(arr[i].size())) {
            c = -1;
        } else {
            c = static_cast<unsigned char>(arr[i][d]);
        }
        aux[left + count[c + 1]++] = arr[i];
    }

    for (int i = left; i <= right; ++i) {
        arr[i] = aux[i];
    }

    for (int c = 0; c < radix; ++c) {
        const int l = left + start[c + 1];
        const int r = left + start[c + 2] - 1;
        if (l < r) {
            msdSort(arr, l, r, d + 1, aux);
        }
    }
}

void radixSort(std::vector<std::string>& arr) {
    if (arr.empty()) {
        return;
    }

    std::vector<std::string> aux(arr.size());
    msdSort(arr, 0, static_cast<int>(arr.size()) - 1, 0, aux);
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

    radixSort(words);

    for (int i = 0; i < n; ++i) {
        std::cout << words[i] << '\n';
    }

    return 0;
}
