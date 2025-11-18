#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <climits>
#include <cstdint>

long long calcDistSq(std::pair<int, int> a, std::pair<int, int> b) {
    long long dx = (long long)a.first - b.first;
    long long dy = (long long)a.second - b.second;
    return dx * dx + dy * dy;
}

long long closestPair(std::vector<std::pair<int, int>>& points, int left, int right) {
    if (right - left <= 3) {
        long long minDistSq = LLONG_MAX;
        for (int i = left; i <= right; ++i) {
            for (int j = i + 1; j <= right; ++j) {
                minDistSq = std::min(minDistSq, calcDistSq(points[i], points[j]));
            }
        }
        return minDistSq;
    }

    int mid = (left + right) / 2;
    long long leftDistSq = closestPair(points, left, mid);
    long long rightDistSq = closestPair(points, mid + 1, right);
    long long bestDistSq = std::min(leftDistSq, rightDistSq);

    std::vector<std::pair<int, int>> strip;
    int midX = points[mid].first;

    for (int i = left; i <= right; ++i) {
        long long dx = (long long)points[i].first - midX;
        if (dx * dx < bestDistSq) {
            strip.push_back(points[i]);
        }
    }

    std::sort(strip.begin(), strip.end(),
              [](const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
                  return p1.second < p2.second;
              });

    for (int i = 0; i < (int)strip.size(); ++i) {
        for (int j = i + 1; j < (int)strip.size(); ++j) {
            long long dy = (long long)strip[j].second - strip[i].second;
            if (dy * dy >= bestDistSq) break;

            long long curDistSq = calcDistSq(strip[i], strip[j]);
            if (curDistSq < bestDistSq) {
                bestDistSq = curDistSq;
            }
        }
    }

    return bestDistSq;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::vector<std::pair<int, int>> points;
    int x;
    int y;

    while (std::cin >> x >> y) {
        points.emplace_back(x, y);
    }

    std::sort(points.begin(), points.end());

    long long minDistSq = closestPair(points, 0, points.size() - 1);
    std::cout << (int)std::sqrt(minDistSq);
}
