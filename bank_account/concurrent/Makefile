
all:
# 	clang++ main.cpp -o main -lpthread
	clang++ main.cpp -o main -g -fsanitize=thread -lpthread

clean:
	rm -rf *~ main

run:
	time -p ./main
