#include <iostream>
#include <vector>
#include <cstring> 

void radixSort(std::vector<int>& v) { 
    const int base = 256;
    const int bits = 8;
    const int passes = static_cast<int>(sizeof(int)); 

    const int n = (int)v.size();
    if (n <= 1) return;

    std::vector<int> b(n);
    int cnt[base];

    for (int p = 0; p < passes; ++p) {
        std::memset(cnt, 0, sizeof(cnt));

        const int cur = p * bits;
        for (int x : v) {
            const int buc = (x >> cur) & (base - 1); 
            ++cnt[buc];
        }

        if (p < passes - 1) {
            int pref = 0;
            for (int k = 0; k < base; ++k) {
                const int c = cnt[k];
                cnt[k] = pref;
                pref += c;
            }
        } else {
            int pos[base];
            int pref = 0;
            for (int k = 128; k < base; ++k) { pos[k] = pref; pref += cnt[k]; }
            for (int k =   0; k < 128; ++k) { pos[k] = pref; pref += cnt[k]; }
            for (int k = 0; k < base; ++k) cnt[k] = pos[k];
        }

        for (int x : v) {
            const int buc = (x >> cur) & (base - 1);
            b[cnt[buc]++] = x;
        }

        v.swap(b);
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

    radixSort(v);

    for (auto x : v) {
        std::cout << x << ' ';
    }
}
