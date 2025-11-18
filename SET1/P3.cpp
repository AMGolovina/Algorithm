#include <iostream>
#include <string>

std::string unpack(const std::string& s) {
    std::string result;
    int num = 0;
    int lvl = 0;
    std::string cur_str;

    for (char c : s) {
        if (lvl > 0) {
            if (c == '[') {
                lvl++;
            }
            if (c == ']') {
                lvl--;
            }
            if (lvl > 0) {
                cur_str += c;
            } else {
                std::string unpack_str = unpack(cur_str);

                for (int i = 0; i < num; i++) {
                    result += unpack_str;
                }

                num = 0;
                cur_str.clear();
            }
        } else if (isdigit(c)) {
            num = num * 10 + (c - '0');
        } else if (c == '[') {
            lvl = 1;
        } else {
            result += c;
        }
    }
    return result;
}

int main() {
    std::string input;
    std::getline(std::cin, input);
    std::cout << unpack(input);
}
