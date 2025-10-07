#include "stats.hpp"
#include <algorithm>
#include <numeric>
#include <cmath>
#include <unordered_map>
#include <cstdint>

Stats compute_stats(const std::vector<double>& v) {
    Stats s; s.count = v.size();
    if (v.empty()) return s;

    s.min = *std::min_element(v.begin(), v.end());
    s.max = *std::max_element(v.begin(), v.end());
    s.mean = std::accumulate(v.begin(), v.end(), 0.0) / v.size();

    // median
    std::vector<double> w = v;
    std::nth_element(w.begin(), w.begin()+w.size()/2, w.end());
    if (w.size() % 2) s.median = w[w.size()/2];
    else {
        auto m2 = w[w.size()/2];
        auto m1 = *std::max_element(w.begin(), w.begin()+w.size()/2);
        s.median = (m1 + m2) / 2.0;
    }

    // mode (bucket to 3 decimals)
    std::unordered_map<long long,int> freq;
    for (double x : v) freq[llround(x*1000.0)]++;
    int bestc=-1; long long bestk=0;
    for (auto& p : freq) if (p.second > bestc) { bestc=p.second; bestk=p.first; }
    s.mode = bestk / 1000.0;

    // population stddev
    double sq=0.0; for (double x : v) sq += (x-s.mean)*(x-s.mean);
    s.stddev = std::sqrt(sq / (double)v.size());
    return s;
}
