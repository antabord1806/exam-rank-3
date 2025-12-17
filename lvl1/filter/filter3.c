#define _GNU_SOURCE 
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

int main(int ac, char **av)
{
    if (ac != 2)
    {
        fprintf(stderr, "ERROR: invalid args\n");
        return (1);
    }
    char    *needle = av[1];
    size_t needle_len = strlen(needle);
    if (!needle_len)
    {
        fprintf(stderr, "ERROR: invalid needle\n");
        return (1);
    }
    char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0)
    {
        char *start = buffer;
        char *found;
        while ((found = memmem(start, bytes_read - (start - buffer), needle, needle_len)) != NULL)
        {
            int i = 0;
            write(STDOUT_FILENO, start, found - start);
            while (i < needle_len)
            {
                write(STDOUT_FILENO, "*", 1);
                i++;
            }
            start = found + needle_len;
        }
        write(STDOUT_FILENO, start, bytes_read - (start - buffer));
    }
    return 0;
}