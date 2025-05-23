CXX = g++
CXXFLAGS = -std=c++20 -Ofast -Wall -Wextra

all: runMovies

runMovies: movies.o utilities.o main.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp movies.h utilities.h
	$(CXX) $(CXXFLAGS) -c main.cpp

movies.o: movies.cpp movies.h
	$(CXX) $(CXXFLAGS) -c movies.cpp

utilities.o: utilities.cpp utilities.h
	$(CXX) $(CXXFLAGS) -c utilities.cpp

clean:
	rm -f *.o
	rm -f runMovies