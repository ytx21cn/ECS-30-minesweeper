mine_sweeper.out : mine_sweeper.o board.o game_play.o input_validation.o
	gcc -g -o mine_sweeper.out mine_sweeper.o board.o game_play.o input_validation.o

mine_sweeper.o : mine_sweeper.c
	gcc -g -c -Wall -Werror mine_sweeper.c

board.o : board.c board.h
	gcc -g -c -Wall -Werror board.c

game_play.o : game_play.c game_play.h
	gcc -g -c -Wall -Werror game_play.c

input_validation.o : input_validation.c input_validation.h
	gcc -g -c -Wall -Werror input_validation.c

clean :
	rm mine_sweeper.out *.o *.gch .fuse*
