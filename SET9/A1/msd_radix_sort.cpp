#include <iostream>
#include <string>
#include <vector>

constexpr int abc = 256;

void msdSort(std::vector<std::string>& arr, const int left, const int right, const int pos, std::vector<std::string>& aux) {
    if (left >= right) {
        return;
    }

    std::vector count(abc + 2, 0);

    for (int i = left; i <= right; ++i) {
        const int c = pos < static_cast<int>(arr[i].size())
                ? static_cast<unsigned char>(arr[i][pos])
                : -1;
        ++count[c + 2];
    }

    for (int i = 0; i < abc + 1; ++i) {
        count[i + 1] += count[i];
    }

    const std::vector<int> start = count;

    for (int i = left; i <= right; ++i) {
        const int c = pos < static_cast<int>(arr[i].size())
                ? static_cast<unsigned char>(arr[i][pos])
                : -1;
        aux[left + count[c + 1]++] = arr[i];
    }

    for (int i = left; i <= right; ++i) {
        arr[i] = aux[i];
    }

    for (int c = 0; c < abc; ++c) {
        const int l = left + start[c + 1];
        const int r = left + start[c + 2] - 1;
        if (l < r) {
            msdSort(arr, l, r, pos + 1, aux);
        }
    }
}

void radixSort(std::vector<std::string>& arr) {
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

    for (std::string& s : words) {
        std::cout << s << '\n';
    }

    return 0;
}
