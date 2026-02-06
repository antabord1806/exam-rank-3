#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void    free_all(char **arr)
{
    for (int i = 0; arr[i]; i++)
        free(arr[i]);
    free(arr);
}

void print_grid(char **grid, int n)
{
    //write(1, "\n", 1);
    /*for (int i = 0; i < n; i++)
        fprintf(stdout, "%s\n", grid[i]);*/
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j] == 'Q')
                fprintf(stdout, "%d", j);
        }
    }
    //write(1, "\n", 1);
}

char **building_grid(int n)
{
    char **grid = malloc((n + 1) * sizeof(char *));
    if (!grid)
        return NULL;
    int i = 0;
    while (i < n)
    {
        grid[i] = malloc(n + 1);
        if (!grid[i])
        {
            free_all(grid);
            return NULL;
        }
        for (int j = 0; j < n; j++)
            grid[i][j] = '*';
        grid[i][n] = '\0';
        i++;
    }
    grid[n] = NULL;
    return (grid);
}

int move_check(char **grid, int row, int col, int n)
{
    for (int r = row; r >= 0; r--)
    {
        if (grid[r][col] == 'Q')
            return 0;
    }
    for (int r = row - 1 , c = col - 1; r >= 0 && c >= 0; r--, c--)
    {
        if (grid[r][c] == 'Q')
            return 0;
    }
    for (int r = row - 1, c = col + 1; r >= 0 && c < n; r--, c++)
    {
        if (grid[r][c] == 'Q')
            return 0;
    }
    return 1;
}

void    solve(char **grid, int n, int row)
{
    int col = 0;
    if (row == n)
    {
        print_grid(grid, n);
        fprintf(stdout, "\n");
        return ;
    }
    while (col < n)
    {
        if (move_check(grid, row, col, n))
        {
            grid[row][col] = 'Q';
            solve(grid, n, row + 1);
            grid[row][col] = '*';
        }
        col++;
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;
    int n = atoi(argv[1]);
    char **grid = building_grid(n);
    //print_grid(grid, n);
    solve(grid, n, 0);
    free_all(grid);
    return (0);
}