
all : main.exe

test : main.exe

main.exe : compile_fail_test.o
	g++-7 -o main.exe  compile_fail_test.o
	echo ............................
	./main.exe
	echo ............................

compile_fail_test.o : compile_fail_test.cpp
	g++-7 -c  compile_fail_test.cpp -o compile_fail_test.o

clean:
	-rm -rf *.o *.exe compile_fail_log.txt
