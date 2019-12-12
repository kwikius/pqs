
PQS_ROOT = ../src/include



OBJECTS = \
	base_dimension_ratio_test.o \
	dimension_test.o \
	eval_if_test.o \
	main.o \
	ratio_exp_test1.o \
	ratio_exp_test2.o \
	syntax_test1.o \
	syntax_test2.o \
	to_power_test.o \
	type_list_test.o

.PHONY : all test gcc7_cpp11 gcc9_cpp2a clean 

all : gcc7_cpp11

gcc7_cpp11 : CXX      = g++-7
gcc7_cpp11 : CXXFLAGS = -std=c++11 -I${PQS_ROOT}
gcc7_cpp11 : test.exe

gcc9_cpp2a : CXX      = g++-9
gcc9_cpp2a : CXXFLAGS = -std=c++2a -I${PQS_ROOT}
gcc9_cpp2a : test.exe

test.exe : $(OBJECTS)
	$(CXX) $(CXXFLAGS) -O3 -o $@  $(OBJECTS)
	@echo .......................
	./$@
	@echo ....... OK ............

%.o : %.cpp 
	$(CXX) $(CXXFLAGS) -O3 -c $<

clean :
	rm -rf *.o
	rm -rf *.exe
