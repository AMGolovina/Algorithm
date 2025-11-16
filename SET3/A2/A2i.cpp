#include <iostream>
#include <vector>

void insertionSort(std::vector<int> &v, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        int key = v[i];
        int j = i - 1;
        for ( ; j >= left && v[j] > key; --j) {
            v[j + 1] = v[j];
        }
        v[j + 1] = key;
    }
}

void mergeSort(std::vector<int> &v, std::vector<int> &temp, int left, int right) {
    if (right - left + 1 <= 15) {
        insertionSort(v, left, right);
        return;
    }

    int mid = left + (right - left) / 2;
    mergeSort(v, temp, left, mid);
    mergeSort(v, temp, mid + 1, right);

    if (v[mid] <= v[mid + 1]) {
        return;
    }

    int i = left;
    int j = mid + 1;
    int k = left;

    for ( ; i <= mid && j <= right; ++k) {
        if (v[i] <= v[j]) {
            temp[k] = v[i];
            ++i;
        } else {
            temp[k] = v[j];
            ++j;
        }
    }

    for ( ; i <= mid; ++i, ++k) {
        temp[k] = v[i];
    }

    for ( ; j <= right; ++j, ++k) {
        temp[k] = v[j];
    }

    for (int t = left; t <= right; ++t) {
        v[t] = temp[t];
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> v[i];
    }

    std::vector<int> temp(n);
    mergeSort(v, temp, 0, n - 1);

    for (int i = 0; i < n; ++i) {
        std::cout << v[i] << (i + 1 == n ? '\n' : ' ');
    }
}
