
all:
	clang++ main.cpp -std=c++11 -pthread -o main

clean:
	rm -f main *~

run:
	time -p ./main 8
	time -p ./main 64
