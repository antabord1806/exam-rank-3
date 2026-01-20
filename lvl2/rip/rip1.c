#include <stdio.h>

int ft_strlen(char *str)
{
    int i = 0;

    while (str[i])
        i++;
    return i;
}

int check_parentesis(char *line)
{
    int i = 0;

    while (line[i])
    {
        if (line[i] != '(' && line[i] != ')')
        {
            //printf("found %c\n", line[i]);
            return 0;
        }
        i++;
    }
    return 1;
}

int is_balanced(char *line, int l, int len)
{
    int i = l;
    int bal = 0;

    while(i < len)
    {
        if (line[i] == ')')
            bal++;
        if (line[i] == '(')
            bal--;
        i++;
    }
    return bal;
}


void    solve(char *str, int l, int len)
{
    int i = l;

    if (i == len)
    {
        puts(str);
        return ;
    }
    while (i < len)
    {
        if (is_balanced(str, i, len) != 0)
        {
            if ()
            solve(str, l + 1, len);
        }
        time_to_balance(str, i, len);
        i++;
    }
}

int main(int argc, char **argv)
{
    int bal = 0;

    if (argc != 2)
    {
        fprintf(stderr, "ERROR: over\n");
        return 1;
    }
    if (!check_parentesis(argv[1]))
    {
        fprintf(stderr, "ERROR: invalid arg\n");
        return 1;
    }
    int line_len = ft_strlen(argv[1]);
    bal = is_balanced(argv[1]);
    if (bal)
    {
        printf("%d gonna solve\n", bal);
        solve(argv[1], 0, line_len);
    }
    else
    {
        printf("%d no need to solve\n", bal);
        puts(argv[1]);
    }
    return (0);
}