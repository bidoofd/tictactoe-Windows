#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

static inline void printTitle()
{
	printf(" _______  _______   _______\t _______   _____     _______\t _______    _____    _______\n");
	printf("|__   __||__   __| /  _____|\t|__   __| /  _  \\   /  _____|\t|__   __|  /  _  \\  |  _____|\n");
	printf("   | |      | |   |  /     \t   | |   |  /_\\  | |  /     \t   | |    |  | |  | | |___\n");
	printf("   | |      | |   | |     \t   | |   |   _   | | |\t           | |    |  | |  | |  ___|\n");
	printf("   | |    __| |__ |  \\_____\t   | |   |  | |  | |  \\_____\t   | |    |  |_|  | | |_____\n");
	printf("   |_|   |_______| \\_______|\t   |_|   |__| |__|  \\_______|\t   |_|     \\_____/  |_______|\n");
}

static inline void printGame(char* slots[])
{
	printf("\t|\t|\t\n");
	printf("    %s   |   %s   |   %s   \n", slots[0],slots[1],slots[2]);
	printf("\t|\t|\t\n");
	printf(" -------+-------+-------\n");
	printf("\t|\t|\t\n");
	printf("    %s   |   %s   |   %s   \n", slots[3],slots[4],slots[5]);
	printf("\t|\t|\t\n");
	printf(" -------+-------+-------\n");
	printf("\t|\t|\t\n");
	printf("    %s   |   %s   |   %s   \n", slots[6],slots[7],slots[8]);
	printf("\t|\t|\t\n");
}

static inline int boardCheck(char* slots[], int test)
{
	int flag = 0;
	for(int a = 0; a < 9; a++)
	{
		if(atoi(slots[a]) == test)
		{
			flag = 1;
		}
	}
	return flag;
}

static inline int checkTie(char* slots[])
{
	for(int a = 0; a < 9; a++)
	{
		if(atoi(slots[a]) != 0)
		{
			return 0;
		}
	}
	return 1;
}


void cpu(char* slots[], char* symChoice)
{
	srand(time(0));

	int flag = 1;
	while(flag != 0)
	{
		for(int a = 0; a < 9; a++)
		{
			int val = 1 + (rand() % 9);
			if(atoi(slots[a]) == val)
			{
				if(strcmp(symChoice, "o") == 0)
				{
					slots[a] = "x";
					flag = 0;
					break;
				}
				else
				{
					slots[a] = "o";
					flag = 0;
					break;
				}
			}
		}
	}
}

void play(char* slots[], char* symChoice)
{
	int val = 0;
	int flag = 0;

	printGame(slots);

	printf("Choose a position to place your marker (1-9).\n");
	while(flag != 1)
	{
		scanf("%d", &val);
		if(val > 0 && val < 10)
		{
			if(boardCheck(slots, val) == 1)
			{
				slots[val-1] = symChoice;
				flag = 1;
				break;
			}
			else
			{
				printf("Not a valid spot.\n");
				printf("Enter in different position\n");
			}
		}
		else
		{
			printf("Not a valid choice.\n");
			printf("Enter in different position\n");
		}
	}
}

int checkWin(char* slots[], int winFlag)
{
	for(int a = 0; a < 9; a+=3)
	{
		if((strcmp(slots[a], slots[a+1]) == 0) && (strcmp(slots[a+1], slots[a+2]) == 0))
		{
			winFlag = 1;
		}
	}
	for(int a = 0; a < 3; a++)
	{
		if((strcmp(slots[a], slots[a+3]) == 0) && (strcmp(slots[a+3], slots[a+6]) == 0))
		{
			winFlag = 1;
		}
	}
	if(((strcmp(slots[0], slots[4])) == 0 && (strcmp(slots[4], slots[8]) == 0)) || ((strcmp(slots[2], slots[4])) == 0 && (strcmp(slots[4], slots[6]) == 0)))
	{
		winFlag = 1;
	}
	if(winFlag == 0 && checkTie(slots) == 1)
	{
		winFlag = 2;
	}

	return winFlag;
}

int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	char *symChoice[1];
	int choice = 0;
	int winFlag = 0;

	printTitle();

	while(choice != 1 && choice != 2)
	{
		printf("Would you like to play Player vs. Computer, or Player vs. Player?\n");
		printf("1. Player vs. CPU\n");
		printf("2. Player vs. Player\n");
		printf("0. To Exit\n");
		scanf("%d", &choice);
		if(choice == 0)
		{
			break;
		}
		else if(choice != 1 && choice != 2)
		{
			printf("Not a valid choice.\n");
		}
	}
	char *slots[10] = {"1","2","3","4","5","6","7","8","9"};

	if(choice == 1)
	{
		printf("Would you like to be X or O?\n");
		printf("X moves first, O moves second.\n");
		scanf("%s", symChoice);
		strlwr(symChoice);

		while(winFlag != 1 && winFlag != 2)
		{
			if(strcmp(symChoice, "x") == 0)
			{
				play(slots, symChoice);
				winFlag = checkWin(slots, winFlag);
				if(winFlag == 0)
				{
					cpu(slots, symChoice);
					winFlag = checkWin(slots, winFlag);
					if(winFlag != 0)
					{
						symChoice[0] = 'o';
						printGame(slots);
						break;
					}
				}
				else
				{
					printGame(slots);
					break;
				}
			}
			else if(strcmp(symChoice, "o") == 0)
			{
				cpu(slots, symChoice);
				winFlag = checkWin(slots, winFlag);
				if(winFlag == 0)
				{
					play(slots, symChoice);
					winFlag = checkWin(slots, winFlag);
					if(winFlag != 0)
					{
						symChoice[0] = 'x';
						printGame(slots);
						break;
					}
				}
				else
				{
					printGame(slots);
					break;
				}
			}
		}
	}
	else if(choice == 2)
	{
		printf("Player One:\n");
		printf("Would you like to be X or O?\n");
		printf("X moves first, O moves second.\n");
		scanf("%s", symChoice);
		strlwr(symChoice);

		while(winFlag != 1 && winFlag != 2)
		{
			if(strcmp(symChoice, "x") == 0)
			{
				char symChoice2[1] = {'o'};
				play(slots, symChoice);
				winFlag = checkWin(slots, winFlag);
				if(winFlag == 0)
				{
					play(slots, symChoice2);
					winFlag = checkWin(slots, winFlag);
					if(winFlag != 0)
					{
						symChoice[0] = symChoice2[0];
						printGame(slots);
						break;
					}
				}
				else
				{
					printGame(slots);
					break;
				}
			}
			else if(strcmp(symChoice, "o") == 0)
			{
				char symChoice2[1] = {'x'};
				play(slots, symChoice);
				winFlag = checkWin(slots, winFlag);
				if(winFlag == 0)
				{
					play(slots, symChoice2);
					winFlag = checkWin(slots, winFlag);
					if(winFlag != 0)
					{
						symChoice[0] = symChoice2[0];
						printGame(slots);
						break;
					}
				}
				else
				{
					printGame(slots);
					break;
				}
			}
		}
	}
	if(winFlag == 1)
	{
		printf("The winner is %c!\n", symChoice[0]);
	}
	else if(winFlag == 2)
	{
		printf("The game is a tie.\n");
	}
	system("pause");
	return 0;
}
