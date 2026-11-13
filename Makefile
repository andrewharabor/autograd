CXX := /usr/bin/clang++

EXEC := ex

SRC_DIRS := src example
BUILD_DIR := build
INC_DIRS := $(shell find $(SRC_DIRS) -type d)

CXX_FLAGS := -std=c++20 -g -pedantic -Wall -Wextra -Werror -Wshadow -Wfloat-equal -Wconversion -fdiagnostics-color=always -fsanitize=undefined,address
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
CPP_FLAGS := $(INC_FLAGS) -MMD -MP

SRCS := $(shell find $(SRC_DIRS) -name '*.cpp')
HEADERS := $(shell find $(SRC_DIRS) -name '*.hpp')
OBJS := $(SRCS:%.cpp=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:%.o=%.d)

-include $(DEPS)

$(EXEC): $(OBJS)
	$(CXX) $(CXX_FLAGS) $(OBJS) -o $@

$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPP_FLAGS) $(CXX_FLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(EXEC)
	rm -rf $(BUILD_DIR)

.PHONY: format
format: $(SRCS) $(HEADERS)
	clang-format -i --verbose $^
