#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "custom_types.h"
#include "board.h"
#include "input_validation.h"

/* This function checks if the format is valid (i.e. number of arguments read matches number of arguments needed). */
bool isValidFormat(int numArgsRead, int numArgsNeeded) {
	char newLine = '\n';
	bool isValid = true;
	if (numArgsRead != numArgsNeeded) { // didn't fill in all the format specifiers
		isValid = false; // format is incorrect
	}
	else {
		do {
			scanf("%c", &newLine);
			if (!isspace(newLine)) {
				isValid = false; // will return false if found one non-whitespace character after the integer
			}
		} while (newLine != '\n');
	}
	return isValid;
}

/* This function checks if the tile is valid */
bool isValidTile(boardStateType boardState, int numArgsRead, int row, int col) {
	return (isValidFormat(numArgsRead, 2) && tileExists(boardState, row, col));
}

/* This function checks if the tile is valid */
bool isValidAction(int numArgsRead, tile currentTile, int actionID) {
	if (!isValidFormat(numArgsRead, 1)) {
		return false;
	}
	else {
		switch (currentTile.tileStatus) {
			case concealed:
				return ((actionID>=0) && (actionID<=3)); break;
			case marked:
			case questioned:
				return ((actionID>=0) && (actionID<=1)); break;
			case revealed:
			default:
				return false; break;
		}
	}
}
