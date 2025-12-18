#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 3

#endif

char    *line_extraction(char *tmp, char *buffer)
{
    int tmp_len = 0;
    while (tmp[tmp_len] && (tmp[tmp_len] != '\n'))
        tmp_len++;
    if (tmp[tmp_len] == '\n')
        tmp_len++;
    char *line = malloc(tmp_len + 1);
    if (!line)
        return NULL;
    for (int i = 0; i < tmp_len; i++)
        line[i] = tmp[i];
    line[tmp_len] = '\0';
    int i = 0;
    while (tmp[tmp_len + i])
    {
        buffer[i] = tmp[tmp_len + i];
        i++;
    }
    //printf("%s", buffer);
    buffer[i] = '\0';
    //printf("%s\n", line);
    return (line);
}

char    *ft_strjoin(char *tmp, char *buffer)
{
    int tmp_len = 0;
    if (tmp)
    {
        while (tmp[tmp_len])
            tmp_len++;
    }
    if (!buffer)
        return NULL;
    int buffer_len = 0;
    while (buffer[buffer_len])
        buffer_len++;
    char *str = malloc((tmp_len + buffer_len + 1) * sizeof(char));
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
        str[tmp_len + j] = buffer[j];
        j++;
    }
    str[tmp_len + buffer_len] = '\0';
    return (str);
}

int     finding_nl(char *str)
{
    int i = 0;
    if (!str)
        return (1);
    while (str[i])
    {
        if (str[i] == '\n')
            return 0;
        i++;
    }
    return (1);
}

char    *gnl(int fd)
{
    static char buffer[BUFFER_SIZE + 1];
    char *tmp = NULL;
    char *old_tmp = NULL;
    int bytes_read = 1;

    if (buffer[0])
    {
        tmp = ft_strjoin(NULL, buffer);
        buffer[0] = '\0';
    }
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';
        old_tmp = tmp;
        tmp = ft_strjoin(tmp, buffer);
        if (!tmp)
            break;
        //printf("%s", tmp);
        free(old_tmp);
        if (!finding_nl(tmp))
            break;
    }
    if (tmp && !finding_nl(tmp))
    {
        char *line = line_extraction(tmp, buffer);
        free(tmp);
        return (line);
    }
    if (!bytes_read && tmp)
        return tmp;
    free(tmp);
    return (NULL);
}

int main(void)
{
    int fd = open("text.txt", O_RDONLY);
    if (fd < 0)
        return (0);
    char *line = NULL;
    while ((line = gnl(fd)))
    {
        printf("%s", line);
        free(line);
    }
    return (0);
}