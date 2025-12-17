#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#define BUFFER_SIZE 1

int     ft_strlen(char *str)
{
    if (!str)
        return (0);
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

char    *ft_strjoin(char *tmp, char *buffer, int buffer_len, int tmp_len)
{
    int i = 0;
    int j = 0;
    
    if (!buffer || !buffer_len)
    return (0);
    char *str = malloc(buffer_len + tmp_len + 1);
    if (!str)
    return (0);
    while (i < tmp_len)
    {
        str[i] = tmp[i];
        i++;
    }
    while ((i + j) < (buffer_len + tmp_len))
    {
        str[i + j] = buffer[j];
        j++;
    }
    str[buffer_len + tmp_len] = '\0';
    //printf("%s\n", str);
    return (str);
}

char    *reading_stdin()
{
    char buffer[BUFFER_SIZE + 1];
    int bytes_read = 1;
    char *tmp = NULL;
    char *old_buffer = NULL;

    while ((bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';
        //printf("%s\n %ld\n", buffer, tmp_len);
        old_buffer = tmp;
        tmp = ft_strjoin(tmp, buffer, bytes_read, ft_strlen(tmp));
        //printf("%s\n", tmp);
        if (!tmp)
        {
            perror("rip\n");
            return (NULL);
        }
        free(old_buffer);
    }
    if (!tmp || !(*tmp))
        return (free(tmp), NULL);
    //printf("%s\n", tmp);
    return (tmp);
}

int    starts_here(char *needle, char *haystack)
{
    int i = 0;

    //printf("ola");
    while (needle[i] && haystack[i] && needle[i] == haystack[i])
        i++;
    return (i);
}

void    finding_needle(char *haystack, char *needle, int needle_len)
{
    int i = 0;
    int len = ft_strlen(haystack);

    while (i < len)
    {
        if (starts_here(needle, &haystack[i]) == needle_len)
        {
            for (int j = 0; j < needle_len; j++)
                write(1, "*", 1);
            i += needle_len;
        }
        else
        {
            write(1, &haystack[i], 1);
            i++;
        }
    }
    write(1, "\n", 1);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "ERROR: invlid args\n");
        return (0);
    }
    int len = ft_strlen(argv[1]);
    char *haystack = reading_stdin();
    //printf("%s", haystack);
    finding_needle(haystack, argv[1], len);
    free(haystack);
    return (0);
}