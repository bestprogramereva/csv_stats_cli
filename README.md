# CSV Stats CLI

A lightweight C++ command-line program that parses a CSV file and computes descriptive statistics for a given numeric column.

## Features
- Mean, median, mode, min, max, standard deviation
- Robust error handling (missing files, non-numeric cells)
- Simple Makefile build system

## Build & Run
```bash
make
./bin/csv_stats --file data/sample.csv --column price
