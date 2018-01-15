#ifndef INPUT_VALIDATION_H
#define INPUT_VALIDATION_H

	bool isValidFormat(int numArgsRead, int numArgsNeeded);
	
	bool isValidTile(boardStateType boardState, int numArgsRead, int row, int col);
	bool isValidAction(int numArgsRead, tile currentTile, int actionID);

#endif
