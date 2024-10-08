
all:
	g++ main.cpp -std=c++11 -lpthread -o main
	g++ main_sequential.cpp -std=c++11 -o main_sequential
	g++ main_threaded.cpp -std=c++11 -lpthread -o main_threaded
	g++ main_threaded_padded.cpp -std=c++11 -lpthread -o main_threaded_padded

clean:
# 	rm *~ main 
	rm *~ main main_sequential main_threaded main_threaded_padded
