#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "custom_types.h"
#include "board.h"

/* This file contains the functions that set up, display, and clean up the board. */

/* Setup, including making the board, placing mines, and calculate the values to be stored at each tile */
void setup(boardStateType* boardState, tile*** board, int seed) {
	*board = makeBoard(*boardState);
	placeMines(boardState, &board, seed);
	calculateSurroundingMines(*boardState, board);
	return;
}

/* Making the board */
tile** makeBoard(boardStateType boardState) {
	int numRows = boardState.numRows;
	int numCols = boardState.numCols;
	
	tile** board = (tile**)malloc(numRows * sizeof(tile*));

	int i, j = 0;

	for (i=0; i<numRows; i++) {
		board[i] = (tile*)malloc(numCols * sizeof(tile));
		for (j=0; j<numCols; j++) {
			board[i][j].minesCount = 0;
			board[i][j].tileStatus = concealed;
		}
	}
		
	return board;
}

/* Placing mines */
void placeMines(boardStateType* boardState, tile**** board, int seed) {
	int numRows = (*boardState).numRows;
	int numCols = (*boardState).numCols;
	int numMines = (*boardState).numMines;
	
	int currentNumMines = 0; // at first there is no mine placed
	int currentRow, currentCol = 0; // location to place each mine
	
	srand(seed); // seed the random number generator
	
	do {
		currentRow = rand() % numRows;
		currentCol = rand() % numCols;
		if ((**board)[currentRow][currentCol].minesCount == -1) {
			continue; // if that tile has placed a mine, do the loop again
		}
		else {
			(**board)[currentRow][currentCol].minesCount = -1;
			currentNumMines++;
			printf("Placing mine at %d, %d\n", currentRow, currentCol);
		}
	} while (currentNumMines < numMines);
	
	(*boardState).numMinesLeft = (*boardState).numMines;
	(*boardState).numSafeTilesLeft = (*boardState).numSafeTiles;
	
	return;
}

/* Calculating the number (indicating number of surrounding mines) in all safe tiles */
void calculateSurroundingMines(boardStateType boardState, tile*** board) {
	int numRows = boardState.numRows;
	int numCols = boardState.numCols;
	int i,j = 0;
	
	for (i=0; i<numRows; i++) {
		for (j=0; j<numCols; j++) {
				(*board)[i][j].minesCount = calculateThisTile(boardState, *board, i, j);
		}
	}
	
	return;
}

/* Calculating the number of surrounding mines in a single tile */
int calculateThisTile(boardStateType boardState, tile** board, int row, int col) {
	int	minesCount = 0;	
	
	if (board[row][col].minesCount == -1) {
		return -1;
	}
	
	else {
		int i, j = 0;
		for (i=row-1; i<=row+1; i++) {
			for (j=col-1; j<=col+1; j++) {
				if (tileExists(boardState, i, j)) {
					if (!(i==row && j==col)) {
						if (board[i][j].minesCount == -1) {minesCount++;}
					}
				}
			}
		}
		return minesCount;
	}
	
}

/* Checking if a column number and a row number exist in a given board */
bool tileExists(boardStateType boardState, int row, int col) {
	int numRows = boardState.numRows;
	int numCols = boardState.numCols;
	return (((row>=0) && (row<=numRows-1)) && ((col>=0) && (col<=numCols-1)));
}

/* Getting the display character for each tile */
char getDisPlayChar(tile thisTile) {
	switch (thisTile.tileStatus) {
		case concealed: return '#'; break;
		case marked: return '!'; break;
		case questioned: return '?'; break;
		case revealed:
			if (thisTile.minesCount == -1) { return '*'; }
			else { return (thisTile.minesCount + '0'); }
			break;
		default: return ' ';
	}
}

/* Printing the board */
void printBoard(boardStateType boardState, tile** board) {
	int i, j = 0;
	int numRows = boardState.numRows;
	int numCols = boardState.numCols;
	
	/* Print all board rows */
	for (i=numRows-1; i>=0; i--) {
		printf("%4d", i); // row number (descending order)
		for (j=0; j<numCols; j++) {
			printf("%4c", getDisPlayChar(board[i][j]));
		}
		printf("\n");
	}
	
	/* Print the last row, with column numbers */
	printf("    ");
	for (j=0; j<numCols; j++) {
			printf("%4d", j);
	}
	printf("\n");
	
	return;
}

/* Printing the numbers of mines left on board */
void printNumMinesLeft(boardStateType boardState) {
	printf("There are %d mines left\n", boardState.numMinesLeft);
	return;
}

/* Freeing the memory when the game is over */
void cleanup(boardStateType boardState, tile*** board) {
	int numRows = boardState.numRows;
	int i = 0;
	
	/* Freeing all the rows */
	for (i=0; i<numRows; i++) {
		free((*board)[i]);
	}
	(*board)[i] = NULL;
	
	/* Finally, freeing the board */
	free(*board);
	*board = NULL;
	
	return;
}
