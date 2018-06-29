#include <stdio.h>
#include <stdlib.h>
#include "leaderboard.h"
#include "game.h"

void displayStartMenu(bool invalid)
{
	system("cls");
	printf("\t\t*Fibozzle*\t\t\n");
	printf("1.Play new game\n2.Play saved game\n3.Leaderboards\n");
	if (invalid){ printf("Enter a valid option!"); }
	printf("Enter your choice: ");
}

void menuInputHandler()
{
	int choice;
	scanf("%d", &choice);
	switch (choice)
	{
	case 1: startNewGame();
		break;
	case 2: startSavedGame();
		break;
	case 3: viewLeaderBoard();
		break;
	default: displayStartMenu(true);
		break;
	}
}

void mainMenuHandler()
{
	displayStartMenu(false);
	do
	{
		menuInputHandler();
	} while (true);
}
