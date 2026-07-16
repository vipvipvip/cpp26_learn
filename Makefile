CXX      := /usr/bin/g++
CXXFLAGS := -std=c++26 -Wall -Wextra -Wpedantic -O0 -g
LDLIBS   := -lstdc++exp

SRCS     := main.cpp calculator.cpp logger.cpp
HEADERS  := types.h calculator.h logger.h
OBJS     := $(patsubst %.cpp,obj/%.o,$(SRCS))
BIN      := bin
TARGET   := $(BIN)/app

.PHONY: all clean run debug valgrind check

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ $(LDLIBS)

obj/%.o: %.cpp $(HEADERS) | obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN) $(BIN)/:
	mkdir -p $(BIN)

obj:
	mkdir -p obj

run: all
	./$(TARGET)

debug: CXXFLAGS += -fsanitize=address,undefined
debug: LDFLAGS  += -fsanitize=address,undefined
debug: all
	@echo "--- running with sanitizers ---"
	./$(TARGET)

clean:
	rm -rf obj $(BIN)

valgrind: all
	valgrind --leak-check=full --track-origins=yes --error-exitcode=1 ./$(TARGET)

check: $(SRCS) $(HEADERS)
	cppcheck --enable=all --std=c++26 --suppress=missingIncludeSystem $(SRCS)
