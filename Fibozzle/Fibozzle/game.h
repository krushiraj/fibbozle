#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "logic.h"
#include "gamesaves.h"

bool gameover = false;

int chooseBoard()
{
	bool invalid = false;
start:
	system("cls");
	printf("Choose a board type\n1. 2x2 board\n2. 4x4 board\n");
	if (invalid)
	{
		printf("Make sure that you enter a valid choice!\n");
	}
	int choice;
	printf("Enter your choice: ");
	scanf("%d",&choice);
	switch (choice)
	{
	case 1:
		return 2;
	case 2:
		return 4;
	default: invalid = true;
		goto start;
		break;
	}
}

int **createBoard(int size)
{
	int **board = (int **)calloc(size, sizeof(int *));
	for (int i = 0; i < size; i++)
	{
		board[i] = (int *)calloc(size, sizeof(int));
	}
	return board;;
}

void displayBoard(int **board,int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			printf("  %d  ", board[i][j]);
		}
		printf("\n\n");
	}
	printf("| W - Up | A - Left | S - Down | D - Right | Z - Save game |\n");
}

void updateBoard(int **board, int size, bool invalid)
{
	system("cls");
	displayBoard(board, size);
	if (invalid)
	{
		printf("Enter a valid key!");
	}
}

int gameInputhandler()
{
	char input;
	fflush(stdin);
	input = getchar();
	switch (input)
	{
	case 'a':
	case 'A':
		//perform left merge
		return 4;
	case 's':
	case 'S':
		//perform down merge
		return 3;
	case 'd':
	case 'D':
		//perform right merge
		return 2;
	case 'w':
	case 'W':
		//perform top merge
		return 1;
	case 'z':
	case 'Z':
		//perform save
		return 10;
	default:
		return -1;
	}
}

void generateRandom(int **board, int size, int moves)
{
	srand(time(NULL));
	int x, y, tx = -1, ty = -1;
random:
	x = rand() % size;
	y = rand() % size;
	if (moves == 0)
	{
		tx = x;
		ty = y;
		board[x][y] = 1;
	}
	while (x == tx)
	{
		x = rand() % size;
	}
	while (y == ty)
	{
		y = rand() % size;
	}
	if (board[x][y] == 0)
	{
		board[x][y] = 1;
	}
	else
	{
		goto random;
	}
}

void gameHandler(int **board, int size, char *username)
{
	int moves = 0;
	generateRandom(board, size, moves);
	displayBoard(board, size);
	do
	{
		int input = gameInputhandler();
		switch (input)
		{
		case 1:
			performOperation(board, size, 1);
			moves++;
			break;
		case 2:
			performOperation(board, size, 2);
			moves++;
			break;
		case 3:
			performOperation(board, size, 3);
			moves++;
			break;
		case 4:
			performOperation(board, size, 4);
			moves++;
			break;
		case -1:
			updateBoard(board, size, true);
			break;
		case 5:
			//saveGame(board, &size, &moves, username);
			break;
		}
		updateBoard(board, size, false);
		//saveGame(board, size, moves, username);
		generateRandom(board, size, moves);
	} while (!gameover);
}

char *getUserName()
{
	char *name = (char*)calloc(10,sizeof(char));
	system("cls");
	printf("Enter user name(not exceeding 9 characters): ");
	scanf("%s", name);
	return name;
}

void startNewGame()
{
	char *username;// = (char *)calloc(10, sizeof(char));
	username = getUserName();
	int size = chooseBoard();
	createFibLookup(size);
	int **board = createBoard(size);
	gameHandler(board, size, username);
	printf("Start the game!");
}

void startSavedGame()
{
	system("cls");
	printf("Start the saved game!");
}