
PQS_ROOT ?= ../src/include

CXX      = g++-9
CXXFLAGS = -fmax-errors=1 -std=c++2a -fconcepts -I$(PQS_ROOT) -Wno-stringop-overflow
BUILD_DIR = build
BIN_DIR = bin

OBJECTS = $(patsubst %,$(BUILD_DIR)/% , \
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
   conversion_factor_test3.o \
	to_power_test.o \
	type_list_test.o \
   basic_concepts_test.o \
   experimental_test.o \
   base_quantity_test.o \
   scaled_value_test.o \
   binary_op_test.o \
   unit_test1.o \
   unit_binary_op.o \
   sandbox.o \
)

.PHONY : all gcc9_concepts_cpp2a clean 

all : $(BIN_DIR)/test.exe

gcc9_concepts_cpp2a : all

$(BIN_DIR)/test.exe :  $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -O3 -o $@  $(OBJECTS)
	@echo .......................
	./$@
	@echo ....... OK ............

$(BUILD_DIR)/%.o : %.cpp 
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -O3 -c $< -o $@

clean :
	rm -rf $(BUILD_DIR)
	rm -rf $(BIN_DIR)
