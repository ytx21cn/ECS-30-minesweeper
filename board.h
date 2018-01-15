#ifndef BOARD_H
#define BOARD_H

	void setup(boardStateType* boardState, tile*** board, int seed);
	
	tile** makeBoard(boardStateType boardState);
	
	void placeMines(boardStateType* boardState, tile**** board, int seed);
	void calculateSurroundingMines(boardStateType boardState, tile*** board);
	int calculateThisTile(boardStateType boardState, tile** board, int row, int col);
	bool tileExists(boardStateType boardState, int row, int col);
	
	char getDisPlayChar(tile thisTile);
	void printNumMinesLeft(boardStateType boardState);
	void printBoard(boardStateType boardState, tile** board);
	
	void cleanup(boardStateType boardState, tile*** board);
	
#endif
