#include <unistd.h>
#include <stdio.h>

int ft_strlen(char *str)
{
    if (!str)
        return 0;
    int i = 0;
    while (str[i])
        i++;
    return i;
}

char *swap(char *str, int i, int j)
{
    char tmp = str[i];
    str[i] = str[j];
    str[j] = tmp;
    return str;
}

char *sort(char *str, int start)
{
    int i = start;
    int j = 1;

    while (str[i])
    {
        while (str[i + j])
        {
            if (str[i] > str[i + j])
                swap(str, i, i + j);
            j++;
        }
        j = 1;
        i++;
    }
    return str;
}

int next_permutation(char *str, int len)
{
    int pivot = len - 2;

    while (pivot >= 0)
    {
        if (str[pivot] < str[pivot + 1])
            break;
        pivot--;
    }
    if (pivot == -1)
        return 0;
    int sucessor = len - 1;
    while (sucessor > pivot)
    {
        if (str[sucessor] > str[pivot])
            break;
        sucessor--;
    }
    swap(str, pivot, sucessor);
    sort(str, pivot + 1);
    return 1;
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;
    char *str = sort(argv[1], 0);
    int len = ft_strlen(str);
    write(1, str, len);
    write(1, "\n", 1);
    while (next_permutation(str, len))
    {
        write(1, str, len);
        write(1, "\n", 1);
    }
    return 0;
}