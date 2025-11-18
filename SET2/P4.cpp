#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

struct IntervalData {
    std::vector<int> T;
    std::vector<int> V;
    std::vector<int> sumTime;
    std::vector<int> sumDist;
    int totalTime;
    int N;
    int L;
};

IntervalData initialize(int L_val, int N_val) {
    IntervalData data;
    data.L = L_val;
    data.N = N_val;

    data.T.resize(N_val);
    data.V.resize(N_val);
    data.totalTime = 0;

    for (int i = 0; i < N_val; i++) {
        std::cin >> data.T[i] >> data.V[i];
        data.totalTime += data.T[i];
    }

    data.sumTime.resize(N_val + 1, 0);
    data.sumDist.resize(N_val + 1, 0);

    for (int i = 0; i < N_val; i++) {
        data.sumTime[i + 1] = data.sumTime[i] + data.T[i];
        data.sumDist[i + 1] = data.sumDist[i] + data.T[i] * data.V[i];
    }

    return data;
}

double getPosition(const IntervalData& data, double time) {
    if (time <= 0) {
        return 0.0;
    }
    if (time >= data.totalTime) {
        return data.sumDist[data.N];
    }

    int start = 0;
    int end = data.N;

    while (start < end) {
        int mid = (start + end) / 2;
        if (time >= data.sumTime[mid + 1]) {
            start = mid + 1;
        } else {
            end = mid;
        }
    }
    int i = start;
    return data.sumDist[i] + (time - data.sumTime[i]) * data.V[i];
}

bool isValidInterval(const IntervalData& data, double inter) {
    std::vector<double> points;
    points.push_back(0.0);
    points.push_back(data.totalTime - inter);

    for (int i = 0; i <= data.N; i++) {
        double start = data.sumTime[i];
        if (0 <= start && start <= data.totalTime - inter) {
            points.push_back(start);
        }

        double shift = data.sumTime[i] - inter;
        if (0 <= shift && shift <= data.totalTime - inter) {
            points.push_back(shift);
        }
    }

    std::sort(points.begin(), points.end());
    points.erase(std::unique(points.begin(), points.end()), points.end());

    double min_dist = 1e18;
    for (double s : points) {
        if (s < 0 || s > data.totalTime - inter) {
            continue;
        }

        double gap = getPosition(data, s + inter) - getPosition(data, s);
        if (gap < min_dist) {
            min_dist = gap;
        }
    }
    return min_dist >= data.L - 1e-9;
}

double findMinInterval(const IntervalData& data) {
    double min_val = 0.0;
    double max_val = data.totalTime;

    for (int iter = 0; iter < 60; iter++) {
        double mid = (min_val + max_val) / 2;
        if (isValidInterval(data, mid)) {
            max_val = mid;
        } else {
            min_val = mid;
        }
    }

    return max_val;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int L_val, N_val;
    std::cin >> L_val >> N_val;

    IntervalData data = initialize(L_val, N_val);
    double result = findMinInterval(data);
    std::cout << std::fixed << std::setprecision(6) << result << '\n';
    return 0;
}
