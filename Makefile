
CC=g++

objects = game.o tictactoe.o

tictactoe : $(objects)

$(objects) : tictactoe.h

.PHONY: clean
clean:
	$(RM) tictactoe *.o




