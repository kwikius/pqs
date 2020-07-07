

CXXFLAGS = -std=c++2a -fconcepts -I${PQS_ROOT} -Wno-stringop-overflow

all : main.exe

test : main.exe

main.exe : compile_fail_test.o
	g++-9 $(CXXFLAGS) -o main.exe  compile_fail_test.o
	echo ............................
	./main.exe
	echo ............................

compile_fail_test.o : compile_fail_test.cpp
	g++-9 -c $(CXXFLAGS) compile_fail_test.cpp -o compile_fail_test.o

clean:
	-rm -rf *.o *.exe compile_fail_log.txt
