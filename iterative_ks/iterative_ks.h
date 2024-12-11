#include <../main_all.h>
int calculateValue(int values[], int solution[], int n);
int calculateWeight(int weights[], int solution[], int n);
void initializeGreedy(int weights[], int values[], int solution[], int n, int capacity);
void iterativeImprovement(int weights[], int values[], int solution[], int n, int capacity);
int run_iterative(int *weights, int *values, int capacity, int n, LARGE_INTEGER frequency);