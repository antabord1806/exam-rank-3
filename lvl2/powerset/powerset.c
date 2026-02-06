#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void    print_subset(int *arr, int subset_size)
{
    for (int i = 0; i < subset_size; i++)
        printf("%d", arr[i]);
    printf("\n");
}

void    backtracking(int target, int *set, int set_size, int pos, int sum, int *subset, int subset_size)
{
    if (sum == target)
    {
        print_subset(subset, subset_size);
        return ;
    }
    if (pos >= set_size || sum > target)
        return ;
    subset[subset_size] = set[pos];
    backtracking(target, set, set_size, pos + 1, sum + set[pos], subset, subset_size + 1);
    backtracking(target, set, set_size, pos + 1, sum, subset, subset_size);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        write(1, "\n", 1);
        return 0;
    }
    int target = atoi(argv[1]);
    int *set = malloc((argc - 2) * sizeof(int));
    if (!set)
        return 1;
    for (int i = 0; i < argc - 2; i++)
        set[i] = atoi(argv[2 + i]);
    int *subset = malloc((argc - 2) *sizeof(int));
    if (!subset)
        return 1;
    backtracking(target, set, argc - 2, 0, 0, subset, 0);
    free(subset);
    free(set);
}
