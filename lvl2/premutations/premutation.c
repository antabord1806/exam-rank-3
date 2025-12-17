#include <unistd.h>
#include <stdio.h>

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

char *swap(char *str, int i, int j)
{
    char tmp;
    tmp = str[i];
    str[i] = str[j];
    str[j] = tmp;
    return (str);
}

char *sort(char *str)
{
    int i = 0;
    int j = 1;
    char tmp;
    while(str[i])
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

void    trying_prem(char *str, int len, int l)
{
    int i = l;
    if (l == len)
    {
        write (1, str, len);
        write(1, "\n", 1);
        return ;
    }
    while (i < len)
    {
        swap(str, l, i);
        trying_prem(str, len, l + 1);
        swap(str, l, i);
        i++;
    }
}

int main (int ac, char *av[])
{
    if (ac != 2)
        return (0);
    char *str = sort(av[1]);
    //printf("%s", str);
    int len = ft_strlen(str);
    trying_prem(str, len, 0);
    return (0);
}