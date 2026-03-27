CXX = g++
CXXFLAGS = -O3 -std=c++17 -Wall

SRC = main.cpp benchmark.cpp
HEADERS = benchmark.h student.h
TARGET = program

all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) *.txt rezultatai.csv

run: $(TARGET)
	./$(TARGET)

debug: CXXFLAGS = -g -std=c++17 -Wall
debug: $(TARGET)

.PHONY: all clean run debug
