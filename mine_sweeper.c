#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include "custom_types.h"
#include "board.h"
#include "game_play.h"

/* This is the main code file for the minesweeper project. */

/* Function for game play */
void playMineSweeper(int numRows, int numCols, int numMines, int seed) {

	boardStateType boardState;
	
	boardState.numRows = numRows;
	boardState.numCols = numCols;
	boardState.numMines = numMines;
	boardState.numSafeTiles = numRows * numCols - numMines;
	boardState.gameStatus = playing;
	boardState.board = NULL; // board
	
	int row, col, actionID = 0;
	
	actionType action = cancel;
	
	/* Game starts, setup the board */
	setup(&boardState, &(boardState.board), seed);
	
	while (boardState.gameStatus == playing) {
		/* Print the number of mines left and the board */
		printNumMinesLeft(boardState);
		printBoard(boardState, boardState.board);
		
		/* Ask user for tile and action */
		do {
			getTileAction(boardState, boardState.board, &row, &col, &actionID);
			action = getActualAction((boardState.board)[row][col].tileStatus, actionID);
		} while (action == cancel);
		
		/* Perform the corresponding action */
		switch (action) {
			case reveal: revealTile(&boardState, boardState.board, &((boardState.board)[row][col]), row, col); break;
			case question: questionTile(&((boardState.board)[row][col])); break;
			case unquestion: unquestionTile(&((boardState.board)[row][col])); break;
			case mark: markTile(&boardState, &((boardState.board)[row][col])); break;
			case unmark: unmarkTile(&boardState, &((boardState.board)[row][col])); break;
			default: break;
		}
	}

	/* Game ends, display message and cleanup the memory*/
	boardState.board = revealAllTiles(boardState); // when the game ends, reveal all tiles
	printBoard(boardState, boardState.board); // print the board with all revealed tiles
	if (boardState.gameStatus == lost) { // if the user lost the game
		printf("You Lost :(");
	}
	else { // if the user won the game
		printf("You Won!!");
	}
	printf("\n");
	
	cleanup(boardState, &(boardState.board));
	
	return;
}

/* Main execution */
int main(int argc, char* argv[]) {
	
	/* Arguments needed: 
	1. number of rows
	2. number of columns
	3. number of mines
	4. [optional] seed to generate mines	*/

	if (argc < 4) { // not enough arguments
		printf("Not enough arguments. Usage: ./mine_sweeper.out num_rows num_cols num_mines [seed])\n");
	}

	else if ((argc == 4) || (argc == 5)) { // correct number of arguments
		int numRows = atoi(argv[1]);
		int numCols = atoi(argv[2]);
		int numMines = atoi(argv[3]);
		int seed;
		
		if (argc == 4) { // no random seeds
			seed = (int)time(0);
		}
		else { // with random seeds
			seed = atoi(argv[4]);
		}
		
		if (numMines < numRows*numCols) {
			playMineSweeper(numRows, numCols, numMines, seed);
		}
		else {
			printf("numMines should be less than total number of tiles.\n");
		}
	}
	
	else if (argc > 5) { // Too many arguments
		printf("Too many arguments. Usage: ./mine_sweeper.out num_rows num_cols num_mines [seed])");
	}
	
	return 0;
}
