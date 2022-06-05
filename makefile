OBJS = $(patsubst $(SRC_DIR)/%.cpp,%.o,$(wildcard $(SRC_DIR)/*.cpp))
CXXFLAGS = g++ -std=c++17 -Wall -pedantic
SRC_DIR = src
BUILD = saikamda

.PHONY: all
.PHONY: clean
.PHONY: update
.PHONY: run
.PHONY: doc

all: compile doc

compile: $(OBJS)
	$(CXXFLAGS) -MM $(SRC_DIR)/*.cpp > dependencies.mk
	$(CXXFLAGS) -o $(BUILD) $^ -lstdc++fs

%.o: $(SRC_DIR)/%.cpp
	$(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(BUILD) dependencies.mk doc

run:
	./$(BUILD)

doc:
	doxygen doxyConfig

-include dependencies.mk