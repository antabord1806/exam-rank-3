#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 4
#endif

int ft_strlen(char *str)
{
    int i = 0;

    if (!str)
        return (0);
    while (str[i])
        i++;
    return (i);
}

char *ft_strjoin(char *tmp, char *buffer)
{
    int tmp_len = 0;
    if (tmp)
        tmp_len = ft_strlen(tmp);
    if (!buffer)
        return (0);
    int buffer_len = ft_strlen(buffer);
    char *str = malloc(tmp_len + buffer_len + 1);
    if (!str)
        return NULL;
    int i = 0;
    while (i < tmp_len)
    {
        str[i] = tmp[i];
        i++;
    }
    int j = 0;
    while (j < buffer_len)
    {
        str[i + j] = buffer[j];
        j++;
    }
    //printf("%s\n", str);
    str[tmp_len + buffer_len] = '\0';
    return (str);
}

char    *get_line(void)
{
    char buffer[BUFFER_SIZE + 1];
    int bytes_read = 1;
    char    *tmp = NULL;
    char    *old_tmp = NULL;

    while (((bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0))
    {
        buffer[bytes_read] = '\0';
        //printf("buffer :%s\n", buffer);
        old_tmp = tmp;
        tmp = ft_strjoin(tmp, buffer);
        free(old_tmp);
        if (!tmp)
            return NULL;
        //printf("tmp: %s", tmp);
    }
    return (tmp);
}

int    starts_here(char *hay, char *needle)
{
    int i = 0;
    while (needle[i] && hay[i] && (hay[i] == needle[i]))
        i++;
    return (i);
}

void    finding_needle(char *hay, char *need, int n_len)
{
    int i = 0;
    int j = 0;
    int hay_len = ft_strlen(hay);

    //printf("ola\n");
    while (hay[i])
    {
        if ((starts_here(&hay[i], need)) == n_len)
        {
            for (int i = 0; i < n_len; i++)
                write(1, "*", 1);
            i = n_len + i;
        }
        else
        {
            write(1, &hay[i], 1);
            i++;
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("rip\n");
        return (1);
    }
    char *hay = get_line();
    if (!hay)
    {
        fprintf(stderr, "ERROR no line");
        return 1;
    }
    //printf("ola\n");
    int needle_len = ft_strlen(argv[1]);
    finding_needle(hay, argv[1], needle_len);
    return (0);
}