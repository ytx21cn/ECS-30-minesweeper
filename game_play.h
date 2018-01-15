#ifndef GAME_PLAY_H
#define GAME_PLAY_H

	void getTileAction(boardStateType boardState, tile** board, int* row, int* col, int* actionID);
	void getTile(boardStateType boardState, int* row, int* col);
	void printAvailableActions(tile thisTile);
	int getActionID(tile thisTile, int* actionID);
	actionType getActualAction(tileStatusType tileStatus, int actionID);
	
	void revealTile(boardStateType* boardState, tile** board, tile* thisTile, int row, int col);
	void questionTile(tile* thisTile);
	void unquestionTile(tile* thisTile);
	void markTile(boardStateType* boardState, tile* thisTile);
	void unmarkTile(boardStateType* boardState, tile* thisTile);
	
	void checkIfWon(boardStateType* boardState);
	
	tile** revealAllTiles(boardStateType boardState);

#endif
