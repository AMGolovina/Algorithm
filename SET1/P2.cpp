#include <iostream>
#include <set>
#include <vector>

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    std::set<std::vector<int>> uniqueSpin;
    int d = 0;
    int cur_cnt = 0;
    while (d < n) {
        std::vector<int> copyArr(n);
        for (int i = 0; i < n; i++) {
            copyArr[i] = arr[(i + d) % n];
        }
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (copyArr[i] != arr[i]) {
                cnt++;
            }
        }
        if (cnt > cur_cnt) {
            cur_cnt = cnt;
            uniqueSpin.clear();
            uniqueSpin.insert(copyArr);
        } else if (cnt == cur_cnt) {
            uniqueSpin.insert(copyArr);
        }
        d++;
    }
    std::cout << uniqueSpin.size();
}
