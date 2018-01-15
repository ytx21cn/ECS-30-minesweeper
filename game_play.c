#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "custom_types.h"
#include "board.h"
#include "game_play.h"
#include "input_validation.h"

/* This file contains the functions that lead the player to play the game, and show game result. */

/* This function gets the tile and the action. */
void getTileAction(boardStateType boardState, tile** board, int* row, int* col, int* actionID) {

	int numArgsRead_actionID = 0;
	
	do {
		getTile(boardState, row, col);
		if ((boardState.board)[(*row)][(*col)].tileStatus == revealed) {
			printAvailableActions((boardState.board)[(*row)][(*col)]);
			*actionID = -1;
		}
		else {
			numArgsRead_actionID = getActionID((boardState.board)[(*row)][(*col)], actionID);
		}
	} while (!isValidAction(numArgsRead_actionID, (boardState.board)[(*row)][(*col)], *actionID));
	
	return;
}

/* This function gets the tile. */
void getTile(boardStateType boardState, int* row, int* col) {
	int numRows = boardState.numRows;
	int numCols = boardState.numCols;
	
	int numArgsRead = 0;
	
	do {
		printf("Enter row a row between 0-%d and a column between 0-%d: ", numRows-1, numCols-1);
		numArgsRead = scanf("%d %d", row, col);
	} while (!isValidTile(boardState, numArgsRead, *row, *col));
	
	return;
}

/* This function prints the available actions with that tile. */
void printAvailableActions(tile thisTile) {
	switch (thisTile.tileStatus) {
		case concealed:
			printf("Enter Action\n");
			printf("0. Reveal\n");
			printf("1. Question\n");
			printf("2. Mark\n");
			printf("3. Cancel\n");
			break;
		case questioned:
			printf("Enter Action\n");
			printf("0. UnQuestion\n");
			printf("1. Cancel\n");
			break;
		case marked:
			printf("Enter Action\n");
			printf("0. UnMark\n");
			printf("1. Cancel\n");
			break;
		case revealed:
			printf("This tile is already revealed.\n");
			break;
		default:	
			break;
	}
}	
/* This function gets the action ID with the tile given. */
int getActionID(tile thisTile, int* actionID) {
	int numArgsRead = 0;
	
	printAvailableActions(thisTile);
	printf("Action: ");
	numArgsRead = scanf("%d", actionID);

	return numArgsRead;
}

/* This function converts the action ID associated with the tile to an actual action. */
actionType getActualAction(tileStatusType tileStatus, int actionID) {
	switch (tileStatus) {
		case concealed:
			switch (actionID) {
				case 0: return reveal;
				case 1: return question;
				case 2: return mark;
				case 3:
				default: return cancel;
			}
			break;
		case questioned:
			switch (actionID) {
				case 0: return unquestion;
				case 1:
				default: return cancel;
			}
			break;
		case marked:
			switch (actionID) {
				case 0: return unmark;
				case 1:
				default: return cancel;
			}
		case revealed:
		default:
			return cancel;
	}
}

/* This function reveals a tile.
	If you reveal a tile that contains a mine, you loses the game.
	If the tile has no mines around it, all 8 surrounding tiles are revealed as well. */
void revealTile(boardStateType* boardState, tile** board, tile* thisTile, int row, int col) {
	(*thisTile).tileStatus = revealed;
	if ((*thisTile).minesCount == -1) {
		/* You have revealed a mine */
		(*boardState).gameStatus = lost;
		return;
	}
	else {
		/* The tile is safe, so the number of safe tiles left on the board decreases by 1 */
		(*boardState).numSafeTilesLeft--;
		
		/* If this tile's mines count is 0, reveal all surrounding tiles. */
		if ((*thisTile).minesCount == 0) {
			int i, j = 0;
			
			for (i=row-1; i<=row+1; i++) {
				for (j=col-1; j<=col+1; j++) {
					if (tileExists(*boardState, i, j)) {
						if (board[i][j].tileStatus == concealed) {
							revealTile(boardState, board, &(board[i][j]), i, j);
						}
					}
				}
			}

		}
	}
	
	checkIfWon(boardState);
	return;
}

/* This function questions a tile. */
void questionTile(tile* thisTile) {
	(*thisTile).tileStatus = questioned;
	return;
}

/* This function unquestions a tile. */
void unquestionTile(tile* thisTile) {
	(*thisTile).tileStatus = concealed;
	return;
}

/* This function marks a tile. */
void markTile(boardStateType* boardState, tile* thisTile) {
	(*thisTile).tileStatus = marked;
	(*boardState).numMinesLeft--;
	if ((*boardState).numMinesLeft == 0) {
		checkIfWon(boardState);
	}
	return;
}

/* This function unmarks a tile. */
void unmarkTile(boardStateType* boardState, tile* thisTile) {
	(*thisTile).tileStatus = concealed;
	(*boardState).numMinesLeft++;
	return;
}

/* This function checks if the user won at the time that "number of mines left" is 0. */
void checkIfWon(boardStateType* boardState) {
	if ((*boardState).numSafeTilesLeft == 0 && (*boardState).numMinesLeft == 0) {
		(*boardState).gameStatus = won;
	}
	return;
}

/* This function reveals all the tiles. */
tile** revealAllTiles(boardStateType boardState) {
	int numRows = boardState.numRows;
	int numCols = boardState.numCols;
	tile** board = boardState.board;
	
	int i, j = 0;
	
	for (i=0; i<numRows; i++) {
		for (j=0; j<numCols; j++) {
			board[i][j].tileStatus = revealed;
		}
	}
	
	return board;
}
