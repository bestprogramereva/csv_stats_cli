#pragma once
#include <vector>
#include "stats.hpp"
struct Stats{
    double mean = 0, median = 0, mode = 0, stddev = 0, min = 0, max = 0;
    size_t count = 0;
};
Stats compute_stats(const std::vector<double>& v);