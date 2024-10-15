
all:
# 	clang++ main.cpp -lpthread -o main
	clang++ main.cpp -g -fsanitize=thread -lpthread -o main

clean:
	rm -rf *~ main a.out

run:
	time -p ./main
