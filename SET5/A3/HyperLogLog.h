#pragma once
#include <vector>
#include <cstdint>
#include <string>
#include <algorithm>

template <class Hash32>
class SimpleHLL {
public:
    // B: число бит на индекс регистра, m = 2^B
    SimpleHLL(int B, Hash32 hash)
        : B_(B), m_(1u << B), hash_(hash), reg_(m_, 0) {}

    void add(const std::string& x) {
        uint32_t h = hash_(x);

        // первые B бит
        uint32_t j = h >> (32 - B_);

        // оставшиеся биты
        uint32_t w = h << B_;

        uint8_t r = rho(w, 32 - B_);
        reg_[j] = std::max(reg_[j], r);
    }

    double estimate() const {
        double sum = 0.0;
        int V = 0; // число нулевых регистров

        for (uint8_t v : reg_) {
            sum += std::ldexp(1.0, -static_cast<int>(v)); // 2^{-v}
            if (v == 0) ++V;
        }

        double E = alpha_m(m_) * static_cast<double>(m_) * static_cast<double>(m_) / sum;

        if (E < 2.5 * m_ && V > 0) {
            return static_cast<double>(m_) * std::log(static_cast<double>(m_) / static_cast<double>(V));
        }
        return E;
    }

    void reset() {
        std::fill(reg_.begin(), reg_.end(), 0);
    }

private:
    // число ведущих нулей + 1
    static uint8_t rho(uint32_t w, int bits) {
        // bits = 32 - B
        if (w == 0) {
            return static_cast<uint8_t>(bits + 1);
        }

        uint8_t r = 1;
        while ((w & 0x80000000u) == 0) {
            w <<= 1;
            ++r;
        }
        return r;
    }

    static double alpha_m(uint32_t m) {
        if (m == 16) {
            return 0.673;
        }
        if (m == 32) {
            return 0.697;
        }
        if (m == 64) {
            return 0.709;
        }
        return 0.7213 / (1.0 + 1.079 / (double)m);
    }

    int B_;
    uint32_t m_;
    Hash32 hash_;
    std::vector<uint8_t> reg_;
};
