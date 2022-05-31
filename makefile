OBJS = $(patsubst $(SRCDIR)/%.cpp,%.o,$(wildcard $(SRCDIR)/*.cpp))
GXX = g++
CFLAGS = -std=c++17 -Wall -pedantic
SRCDIR = src
BINDIR = saikamda

.PHONY: all
.PHONY: clean
.PHONY: update

all: update compile doc

compile: $(OBJS)
	$(GXX) $^ -o $(BINDIR)/pcalendar

%.o: $(SRCDIR)/%.cpp
	$(GXX) $(CFLAGS) $< -c -o $@

clean:
	rm -rf $(OBJS) $(BINDIR) dependencies.mk doc

update:
	mkdir -p $(BINDIR)
	g++ -MM $(SRCDIR)/*.cpp > dependencies.mk

run:
	$(BINDIR)/pcalendar

doc:
	doxygen doxyConfig

-include dependencies.mk