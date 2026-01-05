#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 6
#endif

int ft_strlen(char *str)
{
    if (!str)
        return (0);
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

char    *ft_strjoin(char *tmp, char *buffer)
{
    int tmp_len = 0;
    if (tmp)
        tmp_len = ft_strlen(tmp);
    if (!buffer)
        return (0);
    //printf("%d\n", tmp_len);
    int buffer_len = ft_strlen(buffer);
    char *str = malloc(tmp_len + buffer_len + 1);
    if (!str)
        return 0;
    for (int i = 0; i < tmp_len; i++)
        str[i] = tmp[i];
    for (int i = 0; i < buffer_len; i++)
        str[tmp_len + i] = buffer[i];
    str[buffer_len + tmp_len] = '\0';
    //printf("str: %s\n", str);
    return (str);
}

int finding_nl(char *tmp)
{
    if (!tmp)
        return (1);
    int i = 0;
    while (tmp[i])
    {
        if (tmp[i] == '\n')
            return (0);
        i++;
    }
    return (1);
}

char    *line_getter(char *tmp, char *buffer)
{
    int tmp_len = 0;

    while (tmp[tmp_len] && tmp[tmp_len] != '\n')
        tmp_len++;
    if (tmp[tmp_len] == '\n')
        tmp_len++;
    char *line = malloc(tmp_len + 1);
    if (!line)
        return NULL;
    int i = 0;
    while (i < tmp_len)
    {
        line[i] = tmp[i];
        i++;
    }
    line[tmp_len] = '\0';
    int j = 0;
    while (tmp[tmp_len + j])
    {
        buffer[j] = tmp[tmp_len + j];
        j++;
    }
    buffer[j] = '\0';
    return (line);
}

char    *gnl(int fd)
{
    int bytes_read = 1;
    static char buffer[BUFFER_SIZE + 1];
    char *tmp = NULL;
    char *old_tmp = NULL;

    if (buffer[0])
    {
        tmp = ft_strjoin(NULL, buffer);
        buffer[0] = '\0';
    }
    while((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';
        //printf("buffer: %s\n", buffer);
        old_tmp = tmp;
        tmp = ft_strjoin(tmp, buffer);
        if (!tmp)
            break;
        //printf("tmp; %s\n", tmp);
        free(old_tmp);
        if (!finding_nl(tmp))
            break;
    }
    if (tmp && !finding_nl(tmp))
    {
        char *line = line_getter(tmp, buffer);
        free(tmp);
        return (line);
    }
    if (!bytes_read && tmp)
        return (tmp);
    free(tmp);
    return (NULL);

}

int main(void)
{
    int fd = open("text.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("rip\n");
        return (0);
    }
    char *line = NULL;
    while ((line = gnl(fd)) != NULL)
    {
        //printf("line:\n");
        printf("%s", line);
        free(line);
    }
    return (0);
}
