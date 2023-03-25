#makefile final version

test:	src/tests.cpp src/multithreading.cpp include/multithreading.h
	g++ -o test src/tests.cpp src/multithreading.cpp include/multithreading.h -I /usr/src/gtest/lib -lgtest -pthread -std=c++14 

main_exe: main.o
	g++ -o main_exe -pthread -std=c++14 main.o multithreading.o

main.o : src/main.cpp include/multithreading.h src/multithreading.cpp
	g++ -c -pthread -std=c++14 src/main.cpp src/multithreading.cpp -I /include/multithreading.h 

clean: 
	rm *.o main_exe test





