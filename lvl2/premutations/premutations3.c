#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int ft_strlen(char *str)
{
    if (!str)
        return 0;
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

char *swap(char *s, int i, int j)
{
    char tmp;

    tmp = s[i];
    s[i] = s[j];
    s[j] = tmp;
    return (s);
}

char *sort(char *str)
{
    int i = 0;
    int j = 1;
    char tmp;

    while (str[i])
    {
        while (str[i + j])
        {
            if (str[i] > str[i + j])
            {
                tmp = str[i];
                str[i] = str[i + j];
                str[i + j] = tmp;
            }
            j++;
        }
        j = 1;
        i++;
    }
    return (str);
}

void    solve(char *str, int len, int l)
{
    int i = l;
    if (l == len)
    {
        write(1, str, len);
        write(1, "\n", 1);
        return ;
    }
    while (i < len)
    {
        swap(str, l, i);
        solve(str, len, l + 1);
        swap(str, l, i);
        i++;
    }
}

int main (int argc, char **argv)
{
    if (argc != 2)
        return (0);
    char *str = sort(argv[1]);
    int len = ft_strlen(str);
    solve(str, len, 0);
    //printf("%s\n", str);
    return (0);
}