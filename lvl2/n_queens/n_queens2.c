#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void    free_all(char **board)
{
    int i = 0;
    while (board[i])
    {
        free(board[i]);
        i++;
    }
    free(board);
}

char **build_board(int size)
{
    char **board = malloc((size + 1) * sizeof(char *));
    if (!board)
        return NULL;
    //printf("ola\n");
    int i = 0;
    while (i < size)
    {
        board[i] = malloc(size + 1);
        if (!board[i])
            return (free_all(board), NULL);
        i++;
    }
    board[size] = NULL;
    int c = 0;
    int l = 0;
    while (c < size)
    {
        while (l < size)
        {
            board[c][l] = '*';
            l++;
        }
        board[c][size] = '\0';
        //printf("%s\n", board[c]);
        l = 0;
        c++;
    }
    return (board);
}

void print_board(char **board, int n)
{
    int i = 0;
    while (i < n)
    {
        printf("%s\n", board[i]);
        i++;
    }
    //printf("\n");
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
    printf("\n");
}

int     move_check(char **s, int n, int col, int row)
{
    int i = 0;
    int j = 0;

    //s[row][col] = '*';
    while (i < row)
    {
        if (s[i][col] == 'Q')
            return (0);
        i++;
    }
    for (i = row - 1, j = col - 1; j >= 0 && i >= 0; j--, i--)
        if (s[i][j] == 'Q')
            return 0;
    for (i = row - 1, j = col + 1; j < n && i >= 0; j++, i--)
        if (s[i][j] == 'Q')
            return 0;
    //s[row][col] = 'Q';
    return (1);
}

void    solve_queens(char **s, int n, int row)
{
    int col = 0;

    if (row == n)
    {
        print_board(s, n);
        return ;
    }
    while (col < n)
    {
        if (move_check(s, n, col, row))
        {
            s[row][col] = 'Q';
            solve_queens(s, n, row + 1);
            s[row][col] = '*';
        }
        col++;
    }
    return ;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        perror("ERROR: invlid args");
        return (1);
    }
    int board_size = atoi(argv[1]);
    if (!board_size)
    {
        perror("ERROR: rip\n");
        return (0);
    }
    char **board = build_board(board_size);
    solve_queens(board, board_size, 0);
    //print_board(board, board_size);
    free_all(board);
    return (0);
}