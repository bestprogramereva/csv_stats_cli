#include "csv.hpp"
#include <string> 
#include <vector>


std::vector<std::string> split_csv_line(const std::string& line) {
    std::vector<std::string> cells;
    std::string cur;
    bool in_quotes = false;

    for (char c : line) {
        if (c == '"') {
            in_quotes = !in_quotes; // Toggle the in_quotes flag
        } else if (c == ',' && !in_quotes) {
            cells.push_back(cur);
            cur.clear();
        } else {
            cur.push_back(c);
        }
    }
    cells.push_back(cur); // Add the last field
    return cells;;
}