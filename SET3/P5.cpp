#include <iostream>
#include <vector>
#include <string>
#include <random>

using std::vector;
using std::string;

vector<int> hexToBin(const string& number, unsigned widthBits, unsigned digitCount) {
    vector<int> binary(widthBits, 0);
    unsigned totalBits = digitCount << 2;
    unsigned toDrop = totalBits > widthBits ? totalBits - widthBits : 0;
    unsigned idx = widthBits ? widthBits - 1 : 0;

    unsigned processed = 0;
    for (int i = static_cast<int>(number.size()) - 1; i >= 0 && totalBits > 0; --i) {
        unsigned ch = static_cast<unsigned char>(number[i]);
        if ('0' <= ch && ch <= '9') ch -= '0';
        else if ('A' <= ch && ch <= 'F') ch = ch - 'A' + 10;
        else if ('a' <= ch && ch <= 'f') ch = ch - 'a' + 10;
        else continue;

        for (int j = 0; j < 4 && totalBits > 0; ++j, --totalBits) {
            if (toDrop > 0) {
                --toDrop;
            } else if (processed < widthBits) {
                binary[idx--] = ch & 1;
                ++processed;
            }
            ch >>= 1;
        }
    }
    return binary;
}

std::vector<std::vector<int>> readMatrix(unsigned n) {
    unsigned digitCountPerRow = (n + 3) / 4;
    unsigned rowWidthBits = n;

    std::vector<std::vector<int>> M(n, std::vector<int>(n));
    for (unsigned row = 0; row < n; ++row) {
        string block;
        vector<int> bitsRow(rowWidthBits);
        unsigned col = 0;
        for (unsigned blk = 0; blk < n; ++blk) {
            std::cin >> block;
            auto bits = hexToBin(block, rowWidthBits, digitCountPerRow);
            bitsRow = bits;
            ++col;
            break;
        }
        M[row] = bitsRow;
    }
    return M;
}

vector<int> multiplyMatVec(const std::vector<std::vector<int>>& M,
                           const vector<int>& v) {
    unsigned n = static_cast<unsigned>(M.size());
    vector<int> res(n, 0);
    for (unsigned i = 0; i < n; ++i) {
        int acc = 0;
        for (unsigned j = 0; j < n; ++j) {
            acc ^= (M[i][j] & v[j]);
        }
        res[i] = acc & 1;
    }
    return res;
}

bool check(const std::vector<std::vector<int>>& A,
               const std::vector<std::vector<int>>& B,
               const std::vector<std::vector<int>>& C,
               int iterations = 10) {
    unsigned n = static_cast<unsigned>(A.size());
    std::mt19937 gen(100);
    std::uniform_int_distribution<int> bin(0, 1);

    for (int t = 0; t < iterations; ++t) {
        vector<int> r(n);
        for (unsigned i = 0; i < n; ++i) {
            r[i] = bin(gen);
        }

        vector<int> Br  = multiplyMatVec(B, r);
        vector<int> ABr = multiplyMatVec(A, Br);
        vector<int> Cr  = multiplyMatVec(C, r);

        if (ABr != Cr) {
            return false;
        }
    }
    return true;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned n;
    if (!(std::cin >> n)) {
        return 0;
    }

    auto A = readMatrix(n);
    auto B = readMatrix(n);
    auto C = readMatrix(n);

    if (check(A, B, C)) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }

    return 0;
}
