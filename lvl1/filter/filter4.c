#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif

int     ft_strlen(char *s)
{
    if (!s)
        return (0);
    int i =0;
    while (s[i])
        i++;
    return (i);
}

char *ft_strjoin(char *tmp, char *buffer)
{
    int tmp_len = 0;
    if (tmp)
    {
        while (tmp[tmp_len])
            tmp_len++;
    }
    int buffer_len = 0;
    while (buffer[buffer_len])
        buffer_len++;
    char *str = malloc(tmp_len + buffer_len);
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
    str[tmp_len + buffer_len] = '\0';
    return str;
}

char    *reading_line()
{
    char buffer[BUFFER_SIZE + 1];
    char *tmp = NULL;
    char *old_tmp = NULL;
    int bytes_read = 1;

    while (((bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0))
    {
        buffer[bytes_read] = '\0';
        //printf("buffer:%s\n", buffer);
        old_tmp = tmp;
        tmp = ft_strjoin(tmp, buffer);
        if (!tmp)
            break;
        //printf("tmp: %s\n", tmp);
        free(old_tmp);
    }
    return (tmp);
}

int     starts_here(char *hay, char *needle)
{
    int i = 0;

    while (needle[i] && hay[i] && (hay[i] == needle[i]))
        i++;
    return (i);
}

void    finding_needle(char *hay, int needle_len, char *needle)
{
    int i = 0;
    while (hay[i])
    {
        if (starts_here(&hay[i], needle) == needle_len)
        {
            //printf("ola\n");
            for (int i = 0; i < needle_len; i++)
                write(1, "*", 1);
            i = i + needle_len;
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
        perror("ERROR: invalid args\n");
        return (0);
    }
    char *line = reading_line();
    int needle_len = ft_strlen(argv[1]);
    if (!needle_len)
    {
        perror("ERROR: invalid needle\n");
        return (0);
    }
    finding_needle(line, needle_len, argv[1]);
    return (0);
}
