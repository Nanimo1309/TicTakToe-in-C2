#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 3

void displayTable(char table[SIZE][SIZE])
{
#ifdef __unix__
    system("clear");
#else
    system("cls");
#endif

    for (int y = 0; y < SIZE; ++y)
    {
        printf(" %c | %c | %c\n", table[y][0], table[y][1], table[y][2]);

        if (y < SIZE - 1)
            printf("---+---+---\n");
    }
}

void tableInput(char table[SIZE][SIZE], char curPlayer)
{
    while (true)
    {
        printf("Where would Player %c like to place their letter?\n", curPlayer);

        unsigned int x, y;
        int scanfRet = scanf(" %u %u", &x, &y);

        while (getchar() != '\n')
            ;

        if (scanfRet != 2)
        {
            printf("Invalid Move.\n");
            printf("Please select a new location for ex. 0 0\n");
        }
        else if (x >= SIZE || y >= SIZE)
        {
            printf("Invalid Move, space [%d, %d] is out of scope.\n", x, y);
            printf("Please select a new location for ex. 0 0\n");
        }
        else if (table[y][x] != ' ')
        {
            printf("Invalid Move, space [%d, %d] is occupied.\n", x, y);
            printf("Please select a new location for ex. 0 0\n");
        }
        else
        {
            table[y][x] = curPlayer;
            return;
        }
    }
}

char checkStatus(char table[SIZE][SIZE])
{
    for (int y = 0; y < SIZE; ++y)
        if (table[y][0] != ' ' && table[y][0] == table[y][1] && table[y][1] == table[y][2])
            return table[y][0];

    for (int x = 0; x < SIZE; ++x)
        if (table[0][x] != ' ' && table[0][x] == table[1][x] && table[1][x] == table[2][x])
            return table[0][x];

    if (table[1][1] != ' ')
    {
        if (table[0][0] == table[1][1] && table[1][1] == table[2][2])
            return table[1][1];

        if (table[0][2] == table[1][1] && table[1][1] == table[2][0])
            return table[1][1];
    }

    for (int y = 0; y < SIZE; ++y)
        for (int x = 0; x < SIZE; ++x)
            if (table[y][x] == ' ')
                return ' ';

    return 'D';
}

void game()
{
    char table[SIZE][SIZE];

    for (int y = 0; y < SIZE; ++y)
        for (int x = 0; x < SIZE; ++x)
            table[y][x] = ' ';

    char curPlayer = 'X';

    while (true)
    {
        displayTable(table);
        tableInput(table, curPlayer);

        char winner = checkStatus(table);

        if (winner == 'X' || winner == 'O')
        {
            printf("\n%c is the winner\n", winner);
            return;
        }
        else if (winner == 'D')
        {
            printf("\nIt's a Draw\n");
            return;
        }

        if (curPlayer == 'X')
            curPlayer = 'O';
        else
            curPlayer = 'X';
    }
}

int main()
{
    int MaxRounds;
    printf("How many rounds you wanna play?\n");
    scanf(" %d", &MaxRounds);

    for (int rounds = 0; rounds < MaxRounds; ++rounds)
    {
        game();

        printf("Press any key to play again or exit\n");
        while (getchar() != '\n')
            ;
    }
}
