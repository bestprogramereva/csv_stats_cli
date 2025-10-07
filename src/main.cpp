#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>   // strtod
#include "csv.hpp"
#include <iomanip>
#include "stats.hpp"

static void usage() {
    std::cerr << "Usage: csv_stats --file <path> --column <name>\n";
}

static std::string trim(std::string s) {
    auto l = s.find_first_not_of(" \t\r\n");
    auto r = s.find_last_not_of(" \t\r\n");
    if (l == std::string::npos) return "";
    return s.substr(l, r - l + 1);
}

int main(int argc, char** argv) {
    std::string file, column;
    for (int i = 1; i < argc; ++i) {
        std::string a = argv[i];
        if (a == "--file" && i + 1 < argc) file = argv[++i];
        else if (a == "--column" && i + 1 < argc) column = argv[++i];
    }
    if (file.empty() || column.empty()) { usage(); return 1; }

    std::ifstream fin(file);
    if (!fin) { std::cerr << "Error: cannot open file: " << file << "\n"; return 2; }

    std::string header;
    if (!std::getline(fin, header)) { std::cerr << "Error: empty file.\n"; return 3; }

    auto headers = split_csv_line(header);
    int col = -1;
    for (size_t i = 0; i < headers.size(); ++i) {
        if (trim(headers[i]) == column) { col = (int)i; break; }
    }
    if (col < 0) { std::cerr << "Error: column '" << column << "' not found.\n"; return 4; }

    std::vector<double> values;
    std::string line; size_t row = 1;
    while (std::getline(fin, line)) {
        ++row;
        auto cells = split_csv_line(line);
        if ((int)cells.size() <= col) continue;
        const std::string& cell = cells[col];
        if (cell.empty()) continue;

        char* endp = nullptr;
        double x = std::strtod(cell.c_str(), &endp);
        if (endp == cell.c_str() || *endp != '\0') continue; // skip non-numeric
        values.push_back(x);
    }

    if (values.empty()) {
    std::cerr << "Error: no numeric values found in column.\n";
    return 5;
}

Stats s = compute_stats(values);
std::cout << std::fixed << std::setprecision(3);
std::cout << "count:  " << s.count  << "\n";
std::cout << "mean:   " << s.mean   << "\n";
std::cout << "median: " << s.median << "\n";
std::cout << "mode:   " << s.mode   << "\n";
std::cout << "min:    " << s.min    << "\n";
std::cout << "max:    " << s.max    << "\n";
std::cout << "stddev: " << s.stddev << "\n";

    return 0;

}
