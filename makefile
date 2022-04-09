all: KTask.cpp
	g++ -o main_test.exe -std=c++17 KTask.cpp 
clean:
	rm *.o
