#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <numeric>

#include "RandomStreamGen.h"
#include "HashFuncGen.h"
#include "HyperLogLog.h"

#include <unordered_set>

static std::size_t exactDistinctPrefix(const std::vector<std::string>& S, std::size_t k) {
    std::unordered_set<std::string> st;
    st.reserve(k * 2);
    for (std::size_t i = 0; i < k; ++i) st.insert(S[i]);
    return st.size();
}

static double mean(const std::vector<double>& a) {
    return std::accumulate(a.begin(), a.end(), 0.0) / a.size();
}

static double stdev_sample(const std::vector<double>& a) {
    if (a.size() < 2) return 0.0;
    double m = mean(a);
    double ss = 0.0;
    for (double x : a) ss += (x - m) * (x - m);
    return std::sqrt(ss / (a.size() - 1));
}

int main() {
    const int B = 10;                 // m = 1024 регистров
    const std::size_t streamSize = 50000;
    const std::size_t streamsR = 20;  // сколько независимых потоков
    const std::size_t stepPercent = 10;

    RandomStreamGen cutGen(streamSize, 123, 30);
    auto cuts = cutGen.cuts(stepPercent);

    // Для CSV
    std::vector<std::vector<double>> estByT(cuts.size());
    std::vector<std::vector<double>> trueByT(cuts.size());

    for (std::size_t r = 0; r < streamsR; ++r) {
        RandomStreamGen gen(streamSize, 1000 + r, 30);
        auto S = gen.genStream();

        HashFuncGen h(777);
        HyperLogLog<HashFuncGen> hll(B, h);

        std::size_t prev = 0;
        for (std::size_t ti = 0; ti < cuts.size(); ++ti) {
            std::size_t k = cuts[ti];

            for (std::size_t i = prev; i < k; ++i) hll.add(S[i]);
            prev = k;

            std::size_t exact = exactDistinctPrefix(S, k);
            double est = hll.estimate();

            trueByT[ti].push_back(static_cast<double>(exact));
            estByT[ti].push_back(est);
        }
    }

    // CSV для графиков
    std::ofstream out("results.csv");
    out << "t_index,prefix_size,F0_mean,Nt_mean,Nt_std,Nt_minus,Nt_plus\n";
    for (std::size_t ti = 0; ti < cuts.size(); ++ti) {
        double f0m = mean(trueByT[ti]);
        double ntm = mean(estByT[ti]);
        double nts = stdev_sample(estByT[ti]);
        out << ti << "," << cuts[ti] << ","
            << f0m << "," << ntm << "," << nts << ","
            << (ntm - nts) << "," << (ntm + nts) << "\n";
    }
}
