#include <iostream>
#include <vector>

void heapify(std::vector<int> &v, int n, int i) {
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int largest = i;
    if (l < n && v[l] > v[i]) {
        largest = l;
    }
    if (r < n && v[r] > v[largest]) {
        largest = r;
    }
    if (largest != i) {
        std::swap(v[largest], v[i]);
        heapify(v, n,largest);
    }
}

void buildMaxHeap(std::vector<int> &v) {
    int N = v.size();
    for (int i = N / 2; i >= 0; --i) {
        heapify(v, N, i);
    }
}

void heapSort(std::vector<int> &v) {
    int N = v.size();
    buildMaxHeap(v);
    for (int i = N; i > 1; --i) {
        std::swap(v[0], v[i - 1]);
        heapify(v, i - 1, 0);
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

    heapSort(v);

    for (auto x : v) {
        std::cout << x << ' ';
    }
}
