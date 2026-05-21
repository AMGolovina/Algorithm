#include <iostream>
#include <string>
#include <vector>

std::pair<int, int> LcpCompare(const std::string& a, const std::string& b, const int k) {
    int i = k;
    const int n = static_cast<int>(a.size());
    const int m = static_cast<int>(b.size());

    while (i < n && i < m && a[i] == b[i]) {
        ++i;
    }

    if (i == n && i == m) return {0, i};
    if (i == n) return {-1, i};
    if (i == m) return {1, i};
    if (static_cast<unsigned char>(a[i]) < static_cast<unsigned char>(b[i])) return {-1, i};
    return {1, i};
}

void mergeLCP(std::vector<std::string>& arr, std::vector<int>& lcp, const int left, const int mid, const int right) {
    const int n1 = mid - left + 1;
    const int n2 = right - mid;

    std::vector<std::string> L(n1);
    std::vector<std::string> R(n2);
    std::vector<int> LL(n1);
    std::vector<int> RL(n2);

    for (int i = 0; i < n1; ++i) {
        L[i] = arr[left + i];
        LL[i] = lcp[left + i];
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = arr[mid + 1 + j];
        RL[j] = lcp[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    int ki = LL[0];
    int pj = RL[0];

    while (i < n1 && j < n2) {
        if (ki > pj) {
            arr[k] = L[i];
            lcp[k] = ki;
            ++i;
            ++k;
            if (i < n1) ki = LL[i];
        } else if (ki < pj) {
            arr[k] = R[j];
            lcp[k] = pj;
            ++j;
            ++k;
            if (j < n2) pj = RL[j];
        } else {
            if (auto [cmp, h] = LcpCompare(L[i], R[j], ki); cmp < 0) {
                arr[k] = L[i];
                lcp[k] = ki;
                ++i;
                ++k;
                if (i < n1) ki = LL[i];
                pj = h;
            } else {
                arr[k] = R[j];
                lcp[k] = pj;
                ++j;
                ++k;
                if (j < n2) pj = RL[j];
                ki = h;
            }
        }
    }

    while (i < n1) {
        arr[k] = L[i];
        lcp[k] = ki;
        ++i;
        ++k;
        if (i < n1) ki = LL[i];
    }

    while (j < n2) {
        arr[k] = R[j];
        lcp[k] = pj;
        ++j;
        ++k;
        if (j < n2) pj = RL[j];
    }

    lcp[left] = 0;
}

void mergeSort(std::vector<std::string>& arr, std::vector<int>& lcp, const int left, const int right) {
    if (left == right) {
        lcp[left] = 0;
        return;
    }

    const int mid = left + (right - left) / 2;
    mergeSort(arr, lcp, left, mid);
    mergeSort(arr, lcp, mid + 1, right);
    mergeLCP(arr, lcp, left, mid, right);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::cin.ignore();

    std::vector<std::string> words(n);
    for (int i = 0; i < n; ++i) {
        getline(std::cin, words[i]);
    }

    std::vector lcp(n, 0);
    mergeSort(words, lcp, 0, n - 1);

    for (int i = 0; i < n; ++i) {
        std::cout << words[i] << '\n';
    }

    return 0;
}
