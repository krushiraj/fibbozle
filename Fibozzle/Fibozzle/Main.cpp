#include"mainmenu.h"
#include "gamesaves.h"

void saveGame(int **board, int size, int moves, char *username)
{
	FILE *ptr;
	char saves[7] = "Saves\\";
	char ext[5] = ".txt";
	char *dir = strcat(saves, username);
	dir = strcat(dir, ext);
	ptr = fopen(dir,"w");
	struct gameState *gs = (struct gameState*)calloc(1, sizeof(struct gameState));
	gs->username = username;
	gs->board = board;
	gs->size = size;
	gs->moves = moves;
	fwrite(gs, sizeof(struct gameState), 1, ptr);
}

void main()
{
	int b[2][2] = { { 0, 1 }, { 0, 1 } };
	saveGame((int **)b, 2, 1, "krushi");
}