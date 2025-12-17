#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char *av[])
{
    if (ac != 2)
        return (0);
    int i = 0;
    int k = 1;
    char *str = av[1];
    while (str[i])
    {
        while (str[i + k])
        {
            if (str[i + k] == str[i])
                return (printf("duplicate\n"), 0);
            k++;
        }
        k = 1;
        i++;
    }
    int len = i;
    i = 0;
    k = 0;
    printf("%s\n", str);
    i = 0;
    char tmp;
    int b = 1;
    while (i < len - 1)
    {
        while (str[i + b])
        {
            if (str[i] > str[i + b])
            {
                tmp = str[i];
                str[i] = str[i + b];
                str[i + b] = tmp;
            }
            b++;
        }
        b = 1;
        i++;
    }
    i = 2;
    int result = 1;
    while (i <= len)
    {
        result *= i;
        i++;
    }
    int used[5] = {len};
    char *new = malloc((len + 1) * sizeof(char));
    if (!new)
        return (0);
    back_tracking(str, i, len);
    return (0);
}

void    backtracking(char *str, char *new, int len, int *used)
{
    int i = 0;

    if (!used[i])
        return ;
    else
    {
        used[i] = 0;
        backtracking(str, new, len, &used)
    }
}
