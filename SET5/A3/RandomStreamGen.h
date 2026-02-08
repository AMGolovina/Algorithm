#pragma once
#include <string>
#include <vector>
#include <random>

class RandomStreamGen {
public:
    RandomStreamGen(std::size_t n, uint64_t seed = 42, std::size_t maxLen = 30)
        : n_(n), maxLen_(maxLen), rng_(seed),
          lenDist_(1, maxLen_), chDist_(0, alphabetSize() - 1) {}

    // Сгенерировать поток целиком
    std::vector<std::string> genStream() {
        std::vector<std::string> s;
        s.reserve(n_);
        for (std::size_t i = 0; i < n_; ++i) s.push_back(genOne());
        return s;
    }

    // Вернуть размеры префиксов
    std::vector<std::size_t> cuts(std::size_t stepPercent) const {
        std::vector<std::size_t> c;
        for (std::size_t p = stepPercent; p <= 100; p += stepPercent) {
            std::size_t k = (n_ * p) / 100;
            if (k == 0) k = 1;
            c.push_back(k);
        }
        if (c.empty() || c.back() != n_) c.push_back(n_);
        return c;
    }

private:
    static constexpr const char* alphabet() {
        return "abcdefghijklmnopqrstuvwxyz"
               "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
               "0123456789"
               "-";
    }
    static constexpr std::size_t alphabetSize() { return 65; }

    std::string genOne() {
        std::size_t len = lenDist_(rng_);
        std::string out(len, '\0');
        for (std::size_t i = 0; i < len; ++i) out[i] = alphabet()[chDist_(rng_)];
        return out;
    }

    std::size_t n_;
    std::size_t maxLen_;
    std::mt19937_64 rng_;
    std::uniform_int_distribution<std::size_t> lenDist_;
    std::uniform_int_distribution<std::size_t> chDist_;
};
