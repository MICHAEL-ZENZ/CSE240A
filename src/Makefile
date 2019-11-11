CXX=g++
CXXFLAGS= -std=c++17 -ggdb -Werror
PREDICTOROBJS=main.o 2bc-gskew.o basicUnit.o gshare.o predictor.o tournament.o


%.o: %.c
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all: $(PREDICTOROBJS)
	$(CXX) $(CXXFLAGS) -o predictor $(PREDICTOROBJS)

.c.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f predictor *.o