.PHONY: main bench gen clean

main: main.cpp
	g++ main.cpp -o main && ./main

bench: benchmark.cpp
	g++ benchmark.cpp -o benchmark && ./benchmark

gen: generator.cpp
	g++ generator.cpp -o generator && ./generator

clean:
	rm -f main benchmark generator *.txt


