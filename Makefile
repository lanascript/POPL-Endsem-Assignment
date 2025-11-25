CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I. 

# Test source files
TEST1 = tests/file_reader_test.cpp
TEST2 = tests/search_test.cpp
TEST3 = tests/sort_test.cpp
TEST4 = tests/aggregation_test.cpp
TEST5 = tests/pipeline_test.cpp
MAIN = main.cpp
OUT_MAIN = demo





# Output executables
OUT_TEST1 = file_reader_test
OUT_TEST2 = search_test
OUT_TEST3 = sort_test
OUT_TEST4 = aggregation_test
OUT_TEST5 = pipeline_test
OUT_MAIN = demo

all: $(OUT_TEST1) $(OUT_TEST2) $(OUT_TEST3) $(OUT_TEST4) $(OUT_TEST5) $(OUT_MAIN)

$(OUT_TEST1): $(TEST1)
	$(CXX) $(CXXFLAGS) $(TEST1) -o $(OUT_TEST1)
$(OUT_TEST2): $(TEST2)
	$(CXX) $(CXXFLAGS) $(TEST2) -o $(OUT_TEST2)

$(OUT_TEST3): $(TEST3)
	$(CXX) $(CXXFLAGS) $(TEST3) -o $(OUT_TEST3)

$(OUT_TEST4): $(TEST4)
	$(CXX) $(CXXFLAGS) $(TEST4) -o $(OUT_TEST4)

$(OUT_TEST5): $(TEST5)
	$(CXX) $(CXXFLAGS) $(TEST5) -o $(OUT_TEST5)

$(OUT_MAIN): $(MAIN)
	$(CXX) $(CXXFLAGS) $(MAIN) -o $(OUT_MAIN)


clean:
	rm -f $(OUT_TEST1) $(OUT_TEST2) $(OUT_TEST3) $(OUT_TEST4) $(OUT_TEST5) $(OUT_MAIN)

.PHONY: all clean
