CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -Iinclude

BIN = bin/csv_stats
SRC = src/main.cpp src/csv.cpp src/stats.cpp

all: $(BIN)

$(BIN): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)

clean:
	rm -f $(BIN)
