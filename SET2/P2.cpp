#include <iostream>
#include <string>
#include <vector>
#include <complex>
#include <cmath>

void transform(std::vector<std::complex<double>>& a, bool invert) {
    const double PI = acos(-1.0);
    int n = a.size();
    if (n == 1) return;

    std::vector<std::complex<double>> even(n / 2), odd(n / 2);
    for (int i = 0; i < n / 2; ++i) {
        even[i] = a[2 * i];
        odd[i]  = a[2 * i + 1];
    }

    transform(even, invert);
    transform(odd, invert);

    double ang = 2 * PI / n * (invert ? -1 : 1);
    std::complex<double> w(1), wn(cos(ang), sin(ang));

    for (int i = 0; i < n / 2; ++i) {
        std::complex<double> u = even[i];
        std::complex<double> v = w * odd[i];
        a[i] = u + v;
        a[i + n / 2] = u - v;
        if (invert) {
            a[i] /= 2;
            a[i + n / 2] /= 2;
        }
        w *= wn;
    }
}

std::string multiply(const std::string& s1, const std::string& s2) {
    if (s1 == "0" || s2 == "0") return "0";

    int n1 = s1.size(), n2 = s2.size();
    int n = 1;
    while (n < n1 + n2) n <<= 1;

    std::vector<std::complex<double>> A(n), B(n);

    for (int i = 0; i < n1; ++i)
        A[i] = std::complex<double>(s1[n1 - 1 - i] - '0', 0);
    for (int i = 0; i < n2; ++i)
        B[i] = std::complex<double>(s2[n2 - 1 - i] - '0', 0);

    transform(A, false);
    transform(B, false);

    for (int i = 0; i < n; ++i)
        A[i] *= B[i];

    transform(A, true);

    std::vector<int> res(n);
    long long carry = 0;
    for (int i = 0; i < n; ++i) {
        long long val = llround(A[i].real()) + carry;
        res[i] = val % 10;
        carry = val / 10;
    }

    while (carry > 0) {
        res.push_back(carry % 10);
        carry /= 10;
    }

    while (res.size() > 1 && res.back() == 0)
        res.pop_back();

    std::string result;
    for (int i = res.size() - 1; i >= 0; --i)
        result.push_back('0' + res[i]);

    return result;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string a;
    std::string b;
    std::cin >> a >> b;

    std::cout << multiply(a, b);
}
