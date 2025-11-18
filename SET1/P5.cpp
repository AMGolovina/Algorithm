#include <iostream>
#include <deque>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::deque<int> firstPart;
    std::deque<int> secondPart;
    std::vector<int> result;

    for (int i = 0; i < n; i++) {
        char cmd;
        int x;
        std::cin >> cmd;

        if (cmd == '+' || cmd == '*') {
            std::cin >> x;
        }

        if (cmd == '+') {
            secondPart.push_back(x);
        }
        else if (cmd == '*') {
            if (firstPart.size() == secondPart.size()) {
                firstPart.push_back(x);
            } else {
                secondPart.push_front(x);
            }
        }
        else if (cmd == '-') {
            if (!firstPart.empty()) {
                result.push_back(firstPart.front());
                firstPart.pop_front();
            }
        }

        if (firstPart.size() < secondPart.size()) {
            firstPart.push_back(secondPart.front());
            secondPart.pop_front();
        }
    }

    for (int x : result) {
        std::cout << x << std::endl;
    }
}
