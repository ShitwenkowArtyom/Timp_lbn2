CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

all: gronsfeld transposition

gronsfeld: main_gronsfeld.o modAlphaCipher.o
	$(CXX) $(CXXFLAGS) -o $@ $^

transposition: main_transposition.o transpositionCipher.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main_gronsfeld.o: main_gronsfeld.cpp modAlphaCipher.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

modAlphaCipher.o: modAlphaCipher.cpp modAlphaCipher.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

main_transposition.o: main_transposition.cpp transpositionCipher.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

transpositionCipher.o: transpositionCipher.cpp transpositionCipher.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o gronsfeld transposition

.PHONY: all clean
