CXX      := /usr/bin/g++
CXXFLAGS := -std=c++26 -Wall -Wextra -Wpedantic -O0 -g -I include
LDLIBS   := -lstdc++exp $(shell pkg-config --libs libpqxx)

SRCS     := $(shell find src -name '*.cpp')
HEADERS  := $(shell find include -name '*.h')
OBJS     := $(patsubst src/%.cpp,obj/%.o,$(SRCS))
BIN      := bin
TARGET   := $(BIN)/app

.PHONY: all clean run debug valgrind check

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ $(LDLIBS)

obj/%.o: src/%.cpp $(HEADERS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN):
	mkdir -p $(BIN)

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
	cppcheck --enable=all --std=c++26 --suppress=missingIncludeSystem src/ include/
