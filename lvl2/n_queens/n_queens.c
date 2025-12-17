#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

void    free_all(char **tab)
{
    int i = 0;

    while(tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

void print_board(char **board, int n)
{
    /*int i = 0;
    while (i < n)
    {
        printf("%s\n", board[i]);
        i++;
    }
    printf("\n");*/
    int row = 0;
    int col = 0;
    while (row < n)
    {
        col = 0;
        while (col < n)
        {
            if (board[row][col] == 'Q')
            {
                printf("%d", col);
                break;
            }
            col++;
        }
        row++;
    }
    printf("\n");
}

char    **building_board(int n)
{
    char *row;
    char **grid = malloc((n + 1) * sizeof(char *));
    if (!grid)
        return (NULL);
    int i = 0;
    while (i < n)
    {
        grid[i] = malloc((n + 1) * sizeof(char));
        if (!grid[i])
            return (grid[i] = NULL, free_all(grid), NULL);
        //printf("%d creating grid\n", i);
        i++;
    }
    grid[n] = '\0';
    i = 0;
    int k = 0;
    while (i < n)
    {
        //printf("filling grid\n");
        while (k < n)
        {
            grid[i][k] = '*';
            k++;
        }
        grid[i][n] = '\0';
        k = 0;
        i++;
    }
    //printf("grid filled\n");
    return (grid);
}

int move_check(char **board, int n, int row, int col)
{
    int i = 0;

    while (i < row)
    {
        if (board[i][col] == 'Q')
            return (0);
        i++;
    }
    i = row - 1;
    int j = col - 1;
    while (j >= 0 && i >= 0)
    {
        if (board[i][j] == 'Q')
            return (0);
        i--;
        j--;
    }
    i = row - 1;
    j = col + 1;
    while (j <= n && i > 0)
    {
        if (board[i][j] == 'Q')
            return (0);
        i--;
        j++;
    }
}

void  solve_queen(char **board, int n, int row)
{
    int col = 0;

    if (row == n)
    {
        print_board(board, n);
        return ;
    }
    while (col < n)
    {
        if (move_check(board, n, row, col))
        {
            board[row][col] = 'Q';
            solve_queen(board, n, row + 1);
            board[row][col] = '*';
        }
        col++;
    }
    return ;
}


int main(int ac, char *av[])
{
    if (ac != 2)
        return (0);
    int n = atoi(av[1]);
    char **board = building_board(n);
    solve_queen(board, n, 0);
    free_all(board);
    return (0);
}