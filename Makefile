SHELL := /usr/bin/bash
CXX := /usr/bin/g++
CXXFLAGS := -std=c++23 -fconcepts -g -pedantic -Wall -Wextra -Werror -Wshadow -Wconversion -Wfloat-equal -fdiagnostics-color=always -fsanitize=undefined,address

TARGET_EXEC := main
BUILD_DIR := build
SRC_DIRS := src example

# Find all the C++ files we want to compile
# Note the single quotes around the `*` expressions because we want to send the `*` directly to the find command
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp')

# Prepends `BUILD_DIR` and changes suffix of every source file to `.o`
OBJS := $(SRCS:%.cpp=$(BUILD_DIR)/%.o)

# Changes suffix of every object file to `.d`
DEPS := $(OBJS:%.o=%.d)

# Every folder in `src` will need to be passed to `g++` so that it can find header files
# Recursively find all directories in `SRC_DIRS` and add the `-I` prefix (`g++` understands this flag)
INC_FLAGS := $(addprefix -I,$(shell find $(SRC_DIRS) -type d))

# The `-MMD` and `-MP` flags together generate Makefiles
# These files will have `.d` instead of `.o` as the output
CPPFLAGS := $(INC_FLAGS) -MMD -MP

# The final build step
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# Build step for C++ source
$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

# Include the `.d` makefiles. The `-` at the front suppresses the errors of missing Makefiles
# Initially, all the `.d` files will be missing, and we don't want those errors to show up.
-include $(DEPS)
