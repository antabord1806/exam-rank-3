#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void    free_all(char **grid)
{
    int i = 0;

    while (grid[i])
    {
        free(grid[i]);
        i++;
    }
    free(grid);
}

char    **create_grid(int n)
{
    char **col;
    int i = 0;
    int j = 0;
    col = malloc((n + 1) * sizeof(char *));
    if (!col)
        return NULL;
    while (i < n)
    {
        col[i] = malloc(n + 1);
        if (!col[i])
            return (free_all(col), NULL);
        i++;
    }
    col[n] = NULL;
    int c = 0;
    int l = 0;
    while (c < n)
    {
        while (l < n)
        {
            col[c][l] = '*';
            l++;
        }
        col[c][n] = '\0';
        l = 0;
        c++;
    }
    return (col);
}

void    print_grid(char **grid, int n)
{
    int i = 0;
    //write(1, "\n", 1);
/*     while (i < n)
    {
        fprintf(stdout, "%s\n", grid[i]);
        i++;
    } */
    //printf("ola\n");
    i = 0;
    int j = 0;
    while (i < n)
    {
        j = 0;
        while (j < n)
        {
            if (grid[i][j] == 'Q')
            {
                //printf("%d", j);
                fprintf(stdout, "%d", j);
                break;
            }
            j++;
        }
        i++;
    }
    fprintf(stdout, "\n");
    //fprintf(stdout, "\n");
    return;
}

int     move_check(char **grid, int col, int row, int size)
{
    int i = 0;
    while (i < row)
    {
        if (grid[i][col] == 'Q')
            return (0);
        i++;
    }
    int r = row - 1;
    int c = col - 1;
    while (c >= 0 && r >= 0)
    {
        if (grid[r][c] == 'Q')
            return 0;
        r--;
        c--;
    }
    r = row - 1;
    c = col + 1;
    while (r >= 0 && c < size)
    {
        if (grid[r][c] == 'Q')
            return (0);
        r--;
        c++;
    }
    return (1);
}

void    solve(char **grid, int row, int size)
{
    int col = 0;
    if (row == size)
    {
        print_grid(grid, size);
        return;
    }
    while (col < size)
    {
        //printf("checking moves\n");
        if (move_check(grid, col, row, size))
        {
            grid[row][col] = 'Q';
            solve(grid, row + 1, size);
            grid[row][col] = '*';
        }
        col++;
    }
    return ;
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (0);
    int n = atoi(argv[1]);
    char **grid = create_grid(n);
    //print_grid(grid, n);
    solve(grid, 0, n);
    return (0);
}