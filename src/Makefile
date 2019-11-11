CXX=g++
CXXFLAGS= -std=c++11 -ggdb -Werror
PREDICTOROBJS=main.o 2bc-gskew.o basicUnit.o gshare.o predictor.o tournament.o

default: test

%.o: %.c
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all: $(PREDICTOROBJS)
	$(CXX) $(CXXFLAGS) -o predictor $(PREDICTOROBJS)

.c.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: testCompile.o
	$(CXX) $(CXXFLAGS) -lm -o predictor testCompile.o

testCompile.o:  testCompile.cc
	$(CXX) $(CXXFLAGS) -c testCompile.cc

clean:
	rm -f predictor *.o