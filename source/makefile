all: chess_test

chess_test: chess_test.cpp chess.o
	g++ -Wall chess.o chess_test.cpp -o chess_test

chess.o: chess.cpp chess.h
	g++ -Wall -c chess.cpp

clean:
	rm -f *.o
	rm -f chess_test
