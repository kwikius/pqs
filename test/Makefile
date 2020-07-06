
PQS_ROOT ?= ../src/include

CXXFLAGS = -fmax-errors=1

OBJECTS = \
   output_test.o \
   dimension_test3.o \
   basic_quantity_test.o \
 	base_quantity_exp_test.o \
   dimension_test.o \
   dimension_test1.o \
   dimension_test2.o \
   syntax_test.o \
	eval_if_test.o \
	main.o \
	conversion_factor_test1.o \
	conversion_factor_test2.o \
	to_power_test.o \
	type_list_test.o \
   basic_concepts_test.o \
   experimental_test.o \
   base_quantity_test.o \
   scaled_value_test.o \
   binary_op_test.o \
   sandbox.o

.PHONY : all test gcc7_cpp11 gcc9_cpp17 gcc9_concepts_cpp2a clean 

all : gcc7_cpp11

gcc7_cpp11 : CXX      = g++-7
gcc7_cpp11 : CXXFLAGS += -std=c++11 -I${PQS_ROOT}
gcc7_cpp11 : test.exe

gcc9_cpp17 : CXX      = g++-9
gcc9_cpp17 : CXXFLAGS += --std=c++17 -I${PQS_ROOT}
gcc9_cpp17 : test.exe

gcc9_concepts_cpp2a : CXX      = g++-9
gcc9_concepts_cpp2a : CXXFLAGS += -std=c++2a -fconcepts -I${PQS_ROOT} -Wno-stringop-overflow
gcc9_concepts_cpp2a : test.exe

test.exe : $(OBJECTS)
	$(CXX) $(CXXFLAGS) -O3 -o $@  $(OBJECTS)
	@echo .......................
	./$@
	@echo ....... OK ............

%.o : %.cpp 
	$(CXX) $(CXXFLAGS) -O3 -c $< -o $@

clean :
	rm -rf *.o exposition/*.o
	rm -rf *.exe
