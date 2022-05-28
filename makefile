OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
GXX = g++
LD = g++
COMP_FLAGS = -std=c++17 -Wall -pedantic

.PHONY: all
.PHONY: clean
.PHONY: update

all: update cal
cal: $(OBJS)
	$(LD) $^ -o $@

%.o: %.cpp
	$(GXX) $(COMP_FLAGS) $< -c -o $@

clean:
	rm -rf $(OBJS) cal

# update:
# 	g++ -MM *.cpp > dependencies.mk

-include dependencies.mk



# cal: main.o interface.o event.o datetime.o calendar.o
# 	g++ -std=c++17 -Wall -pedantic main.o interface.o event.o datetime.o calendar.o -o cal

# main.o: main.cpp
# 	g++ -std=c++17 -Wall -pedantic -c main.cpp

# interface.o:
# 	g++ -std=c++17 -Wall -pedantic -c interface.cpp

# event.o:
# 	g++ -std=c++17 -Wall -pedantic -c event.cpp

# datetime.o:
# 	g++ -std=c++17 -Wall -pedantic -c datetime.cpp

# calendar.o:
# 	g++ -std=c++17 -Wall -pedantic -c calendar.cpp

# clean:
# 	rm *.o cal