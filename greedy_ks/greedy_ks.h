#include <../main_all.h>

typedef struct {
    int weight;
    int value;
    double ratio;
} Item;
int compare(const void* a, const void* b);
int knapsack(int capacity, Item items[], int n);
AnswerStruct run_greedy(int *weights, int *values, int capacity, int n, LARGE_INTEGER frequency);