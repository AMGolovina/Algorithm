#include <iostream>
#include <vector>

struct Interval {
    int left;
    int right;

    size_t length() const {
        return right - left + 1;
    }

    Interval overlap(const Interval& other) const {
        int newLeft = std::max(left, other.left);
        int newRight = std::min(right, other.right);
        if (newLeft > newRight)
            return {0, -1};
        return {newLeft, newRight};
    }

    bool operator<(const Interval& other) const {
        if (left != other.left)
            return left < other.left;
        return right < other.right;
    }
};

void merge(std::vector<Interval>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<Interval> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] < R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(std::vector<Interval>& arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    if (n == 0) {
        std::cout << 0;
        return 0;
    }

    std::vector<Interval> arr(n);
    for (int i = 0; i < n; ++i)
        std::cin >> arr[i].left >> arr[i].right;

    mergeSort(arr, 0, n - 1);

    size_t maxLen = 0;
    int x = 0;
    int y = 0;

    int maxRight = arr[0].right;
    int bestIntervalIdx = 0;

    for (int i = 1; i < n; ++i) {
        Interval inter = arr[i].overlap(arr[bestIntervalIdx]);
        size_t len = inter.length();

        if (len > maxLen || (len == maxLen && (inter.left < x ||
            (inter.left == x && inter.right < y)))) {
            maxLen = len;
            x = inter.left;
            y = inter.right;
            }
        if (arr[i].right > maxRight) {
            maxRight = arr[i].right;
            bestIntervalIdx = i;
        }
    }


    std::cout << maxLen << std::endl;
    if (maxLen > 0) {
        std::cout << x << " " << y;
    }
}
