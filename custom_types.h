#ifndef CUSTOM_TYPES_H
#define CUSTOM_TYPES_H
	
	typedef enum { playing, lost, won } gameStatusType;
	
	typedef enum { concealed, questioned, marked, revealed } tileStatusType;

	typedef enum { reveal, question, unquestion, mark, unmark, cancel } actionType;
	
	typedef struct tile_struct {
		int minesCount; // number of mines surrounding it, or is -1 if it is a mine
		tileStatusType tileStatus;
	} tile;
	
	typedef struct boardStateType_struct {
		int numRows;
		int numCols;
		int numMines;
		int numMinesLeft;
		int numSafeTiles;
		int numSafeTilesLeft;
		gameStatusType gameStatus;
		tile** board;
	} boardStateType;
	
#endif
