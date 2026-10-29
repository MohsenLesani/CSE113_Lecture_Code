
all:
# 	g++ -O3 -fopenmp main1.cpp -o main1
# 	g++ -fopenmp -std=c++11 main1.cpp -o main1
	clang++ -O2 -std=c++11 -Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include -L/opt/homebrew/opt/libomp/lib -lomp main1.cpp -o main1


clean:
	rm -f *~ main1
