#include <../main_all.h>
#define MAX_POPULATION 4000
#define MAX_GENERATION 5000
#define STOP_CONDITION_FITNESS_STAGNATED 200
#define ELITISM_RATE 400
typedef struct {
    int weight;
    int cost;
} item;

typedef struct {
    int* chromosome;
    int fitness;
    int total_weight;
} chromosomes;
AnswerStruct run_ga(int *weight, int *cost, int capacity, int n, LARGE_INTEGER frequency);
void merge(chromosomes* pop, int left, int mid, int right);
void merge_sort(chromosomes* pop, int left, int right);
void sort_population(chromosomes* pop, int pop_size);
void cal_fitness(int* chromosome, int n, int max_weight, item* items, chromosomes* chromo);
chromosomes* initial_pop(int pop_size, int n, int max_weight, item* items);
void free_pop(chromosomes* pop, int pop_size);
int* multi_point_crossover(int* chromosome1, int* chromosome2, int n, int num_points);
int* crossover(int* chromosome1, int* chromosome2, int n);
int* mutate(int* chromosome, int n);
int get_generation(int generation);
chromosomes* tournament_selection(chromosomes* pop, int pop_size, int n, int max_weight, item* items, int generation, int stagnation);
void print_population(chromosomes* pop, int pop_size, int n);
// item* initialItem(int n, int *weight, int *cost);
int adaptive_mutation_rate(int stagnation, int base_rate);