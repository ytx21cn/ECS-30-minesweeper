# ECS 30 Final Project: Minesweeper

Copyright ytx21cn 2017

All Rights Reserved

**This is a console-based minesweeper game.**

## How to run
Usage: `./mine_sweeper.out num_rows num_cols num_mines [seed]`

If you don't specify a seed, it will automatically seed based on current time.

## Selecting a tile

When you are asked to select a tile, enter the row number followed by the column number. These two numbers are separated by a space.

Only enter a tile that exists on the board. If your input is not valid, or the tile does not exist, the program will keep asking you until you enter a valid tile.

## Action
After you select a tile:

1. If that tile is not revealed, the program will ask you for an action. Follow the prompts on screen and enter the number corresponding to that action. If your input is not valid, the program will ask you to select a tile again, then to select an action again.
	1. If you reveal the tile that contains a mine, you will lose.
	2. If you think that the tile probably has a mine, you can question it. You can also unquestion a questioned tile at any time.
	3. If you think that the tile has a mine, you can mark it. You can also unmark a marked tile at any time. Note that the number of mines displayed on top of the board just compares the number of mines and the number of marks on the board; it does NOT tell you whether you have marked every tile that contains a mine.
    4. If a tile that has no mines surrounding it is revealed, all the tiles around it will be revealed, except the ones that are questioned or marked. Thus, if you see a tile that is next to a tile showing "0" but questioned or marked, you have to manually reveal it.
	5. If you select "Cancel," the program will ask you to select another tile.

2. If that tile is revealed, you will receive a message, and the program will ask you to select another tile.

## How to win
You win the game IF AND ONLY IF all the safe tiles are revealed, AND all the tiles with mines are marked.
