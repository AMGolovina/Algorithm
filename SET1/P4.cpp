#include <iostream>
#include <stack>
#include <vector>

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> cars(n);
    for (int i = 0; i < n; i++) {
        std::cin >> cars[i];
    }
    std::stack<int> deadlock;
    std::vector<std::pair<int, int>> deadlocks;
    int min_num = 1;
    int cnt = 0;
    while (min_num <= n) {
        if (!deadlock.empty() && deadlock.top() == min_num) {
            int cnt_stack = 0;
            while (!deadlock.empty() && deadlock.top() == min_num) {
                deadlock.pop();
                min_num++;
                cnt_stack++;
            }
            deadlocks.emplace_back(2, cnt_stack);
        } else if (cnt < n) {
            int cnt_cars = 0;
            while (cnt < n) {
                deadlock.push(cars[cnt]);
                cnt++;
                cnt_cars++;
                if (deadlock.top() == min_num) {
                    break;
                }
            }
            deadlocks.emplace_back(1, cnt_cars);
        } else {
            std::cout << 0;
            return 0;
        }
    }
    for (auto x : deadlocks) {
        std::cout << x.first << " " << x.second << std::endl;
    }
}
