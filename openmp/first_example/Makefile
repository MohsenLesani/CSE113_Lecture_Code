
all:
	clang++ -std=c++11 -Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include -L/opt/homebrew/opt/libomp/lib -lomp add_arrays.cpp -o add_arrays
# 	clang++ -std=c++11 add_arrays.cpp -o add_arrays
# 	clang++ -std=c++11 -L/opt/homebrew/opt/llvm/lib -I/opt/homebrew/opt/llvm/include -fopenmp add_arrays.cpp -o add_arrays
# 	g++ -fopenmp -std=c++11 add_arrays.cpp -o add_arrays
# 	clang++ -Xpreprocessor -fopenmp -lomp -std=c++11 add_arrays.cpp -o add_arrays
# 	clang++ -Xpreprocessor -fopenmp -std=c++11 -I/opt/homebrew/include -L/opt/homebrew/lib -lomp add_arrays.cpp -o add_arrays


clean:
	rm -f *~ add_arrays

run:
# 	time -p ./add_arrays
	./add_arrays
