#include <stdio.h>
#include <stdlib.h>

static int target;
static int *set;
static int set_size;
static int *subset;

void print_subset(int size)
{
    for (int i = 0; i < size; i++)
    {
        if (i > 0)
            printf(" ");
        printf("%d", subset[i]);
    }
    printf("\n");
}

void dfs(int idx, int sum, int subset_size)
{
    if (idx == set_size)
    {
        if (sum == target)
            print_subset(subset_size);
        return;
    }

    // Option 1: do not take set[idx]
    dfs(idx + 1, sum, subset_size);

    // Option 2: take set[idx]
    subset[subset_size] = set[idx];
    dfs(idx + 1, sum + set[idx], subset_size + 1);
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        return 1;
    }

    target = atoi(argv[1]);
    set_size = argc - 2;

    set = malloc(sizeof(int) * set_size);
    subset = malloc(sizeof(int) * set_size);
    if (!set || !subset)
        return 1;

    for (int i = 0; i < set_size; i++)
        set[i] = atoi(argv[i + 2]);

    dfs(0, 0, 0);

    free(set);
    free(subset);
    return 0;
}