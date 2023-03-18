#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int number(char *s)
{
	int result = 0;
	int i;

	i = 0;
	while (s[i])
	{
		result *= 10;
		result += s[i] - 48;
		i++;
	}
	return (result);
}

int generateRandomNumber() {
    srand(time(0)); // seed the random number generator with the current time
    int randomNumber = rand() % 8; // generate a random number between 0 and 2
    return randomNumber;
}

int check_winner(char board[3][3], char player)
{
	int i, j;
	int check_win = 0;

	for (i = 0; i < 3; i++)
	{
		if (board[i][i] == player)
			check_win += 1;
	}
	if (check_win == 3)
		return (1);
	for (i = 0; i < 3; i++)
	{
		check_win = 0;
		for(j = 0; j < 3; j++)
		{
			if (board[i][j] == player)
				check_win += 1;
		}
		if (check_win == 3)
			return (1);
	}
	for (i = 0; i < 3; i++)
	{
		check_win = 0;
		for(j = 0; j < 3; j++)
		{
			if (board[j][i] == player)
				check_win += 1;
		}
		if (check_win == 3)
			return (1);
	}
	if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
		return (1);
	return (0);
}

int Check_Empty(char board[3][3])
{
	int i, j;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (board[i][j] == ' ')
				return (0);
		}
	}
	return (1);
}

int play(char board[3][3], int position, char user)
{
	if (board[position / 10][position % 10] == ' ')
	{
		board[position / 10][position % 10] = user;
		return (1);
	}
	return (0);
}

void printBoard(char board[3][3])
{
	printf(" %c | %c | %c\n", board[0][0], board[0][1], board[0][2]);
	printf("---+---+---\n");
	printf(" %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
	printf("---+---+---\n");
	printf(" %c | %c | %c\n", board[2][0], board[2][1], board[2][2]);
}

void gameplay()
{
	int positions[9] = {00, 01, 02, 10, 11, 12, 20, 21, 22}; 
	char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
	char *position_ai;
	int i, position, check;
	int x;
	int play_again = 1;
	int playing_with_player = 0;

	printf("do you want to play: \n");
	scanf("%d", &play_again);
	if (play_again == 0)
		exit(98);
	printf("do you want to play with a human '0' or AI '1': \n");
	scanf("%d", &playing_with_player);
	position_ai = malloc(3 * sizeof(char));
	while (Check_Empty(board) == 0)
	{
		check = 0;
		while(check == 0)
		{
			printf("x choose position: \n");
			scanf("%d", &position);
			if (play(board, position, 'x') == 1)
			{
				play(board, position, 'x');
				check = 1;
			}
		}
		printBoard(board);
		if (check_winner(board, 'x') == 1)
		{    
			
			printf("x won\n");
			gameplay();
		}
		if (Check_Empty(board) != 1)
		{
			check = 0;
			while(check == 0)
			{
				if (playing_with_player == 0)
				{	
					printf("o choose position: \n");
					scanf("%d", &position);
					if (play(board, position, 'o') == 1)
					{
						play(board, position, 'o');
						check = 1;
					}
					printBoard(board);
				}
				else
				{
					while (1)
					{
						x = generateRandomNumber();
						printf("%d", x);
						position = positions[x];
						positions[x] = 4;
						break;
					}
					if (play(board, position, 'o') == 1)
					{
						play(board, position, 'o');
						printf("AI played:\n");
						printBoard(board);
						check = 1;
					}
				}
			}
			if (check_winner(board, 'o') == 1)
			{    
				printf("o won\n");
				gameplay();
			}
		}
	}
	printf("DRAW\n");
}
int main(void)
{
	gameplay();

	return (0);
}