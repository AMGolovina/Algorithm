#include <iostream>
#include <vector>

void stableSort(std::vector<std::pair<int,int>>& A, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;

    stableSort(A, left, mid);
    stableSort(A, mid + 1, right);

    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<std::pair<int,int>> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = A[left + i];
    for (int j = 0; j < n2; ++j) R[j] = A[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        int lhs = L[i].first * R[j].second;
        int rhs = R[j].first * L[i].second;

        if (lhs < rhs) {
            A[k++] = L[i++];
        } else if (lhs == rhs) {
            A[k++] = L[i++];
        } else {
            A[k++] = R[j++];
        }
    }
    while (i < n1) A[k++] = L[i++];
    while (j < n2) A[k++] = R[j++];
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::pair<int, int>> v;
    v.reserve(n);
    for (int i = 0; i < n; i++) {
        std::string fraction;
        std::cin >> fraction;
        size_t pos = fraction.find('/');
        int num = std::stoi(fraction.substr(0, pos));
        int den = std::stoi(fraction.substr(pos + 1));
        v.emplace_back(num, den);
    }

    stableSort(v, 0, n - 1);

    for (size_t i = 0; i < n; ++i) {
        std::cout << v[i].first << '/' << v[i].second << " ";
    }
}
