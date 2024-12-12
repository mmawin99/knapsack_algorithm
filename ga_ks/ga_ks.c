#include <ga_ks.h>

void merge(chromosomes* pop, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    chromosomes* L = (chromosomes*)malloc(n1 * sizeof(chromosomes));
    chromosomes* R = (chromosomes*)malloc(n2 * sizeof(chromosomes));

    for (int i = 0; i < n1; i++)
        L[i] = pop[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = pop[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].fitness >= R[j].fitness) {
            pop[k++] = L[i++];
        } else {
            pop[k++] = R[j++];
        }
    }

    while (i < n1) pop[k++] = L[i++];
    while (j < n2) pop[k++] = R[j++];

    free(L);
    free(R);
}

void merge_sort(chromosomes* pop, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(pop, left, mid);
        merge_sort(pop, mid + 1, right);
        merge(pop, left, mid, right);
    }
}

void sort_population(chromosomes* pop, int pop_size) {
    merge_sort(pop, 0, pop_size - 1);
}

void cal_fitness(int* chromosome, int n, int max_weight, item* items, chromosomes* chromo) {
    int value = 0, weight = 0;
    for (int i = 0; i < n; i++) {
        value += chromosome[i] * items[i].cost;
        weight += chromosome[i] * items[i].weight;
    }
    chromo->fitness = (weight > max_weight) ? -1 : value;
    chromo->total_weight = weight;
}

chromosomes* initial_pop(int pop_size, int n, int max_weight, item* items) {
    chromosomes* pop = (chromosomes*)malloc(pop_size * sizeof(chromosomes));
    if (pop == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    int i = 0;
    while (i < pop_size) {
        pop[i].chromosome = (int*)malloc(n * sizeof(int));
        if (pop[i].chromosome == NULL) {
            printf("Memory allocation failed.\n");
            exit(1);
        }

        int weight = 0;
        for (int j = 0; j < n; j++) {
            pop[i].chromosome[j] = (rand() % 2 && weight + items[j].weight <= max_weight) ? 1 : 0;
            weight += pop[i].chromosome[j] * items[j].weight;
        }

        cal_fitness(pop[i].chromosome, n, max_weight, items, &pop[i]);
        if (pop[i].fitness < 0) {
            free(pop[i].chromosome);
            continue;
        }

        i++;
    }

    return pop;
}

void free_pop(chromosomes* pop, int pop_size) {
    for (int i = 0; i < pop_size; i++) {
        free(pop[i].chromosome);
    }
    free(pop);
}

int* multi_point_crossover(int* chromosome1, int* chromosome2, int n, int num_points) {
    int* new_chromosome = (int*)malloc(n * sizeof(int));
    bool* crossover_points = (bool*)calloc(n, sizeof(bool));
    for (int i = 0; i < num_points; i++) {
        int point;
        do {
            point = rand() % n;
        } while (crossover_points[point]);
        crossover_points[point] = true;
    }

    bool take_from_chromosome1 = true;
    for (int i = 0; i < n; i++) {
        if (crossover_points[i]) {
            take_from_chromosome1 = !take_from_chromosome1;
        }
        new_chromosome[i] = take_from_chromosome1 ? chromosome1[i] : chromosome2[i];
    }

    free(crossover_points);

    return new_chromosome;
}

int* crossover(int* chromosome1, int* chromosome2, int n) {
    return multi_point_crossover(chromosome1, chromosome2, n, rand() % (int)(n/1.12));
}

int* mutate(int* chromosome, int n) {
    int* new_chromosome = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        new_chromosome[i] = chromosome[i];
    }
    int mutation_point = rand() % n;
    new_chromosome[mutation_point] = 1 - new_chromosome[mutation_point];
    return new_chromosome;
}

int get_generation(int generation){
	if(generation < 10000) return 50;
	else if(generation < 20000) return 30;
	else return 10;
}

chromosomes* tournament_selection(chromosomes* pop, int pop_size, int n, int max_weight, item* items, int generation) {
    chromosomes* new_population = (chromosomes*)malloc(pop_size * sizeof(chromosomes));
    if (new_population == NULL) {
        printf("Memory allocation failed for new population.\n");
        exit(EXIT_FAILURE);
    }
	int elitismRate = ELITISM_RATE;
    for (int i = 0; i < elitismRate; i++) {
        new_population[i].chromosome = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            new_population[i].chromosome[j] = pop[i].chromosome[j];
        }
        new_population[i].fitness = pop[i].fitness;
        new_population[i].total_weight = pop[i].total_weight;
    }

    int index = elitismRate;
    while (index < pop_size) {
        int a = rand() % MAX_POPULATION;
		int b = rand() % MAX_POPULATION;
		int c = rand() % MAX_POPULATION;
        int parent1 = (pop[a].fitness > pop[b].fitness && pop[a].fitness > pop[c].fitness) ? a : (pop[c].fitness > pop[b].fitness ? c : b);

        a = rand() % MAX_POPULATION; 
		b = rand() % MAX_POPULATION;
		c = rand() % MAX_POPULATION;
        int parent2 = (pop[a].fitness > pop[b].fitness && pop[a].fitness > pop[c].fitness) ? a : (pop[c].fitness > pop[b].fitness ? c : b);

        int* child = crossover(pop[parent1].chromosome, pop[parent2].chromosome, n);

        new_population[index].chromosome = child;
        cal_fitness(child, n, max_weight, items, &new_population[index]);

        int mutation_rate = get_generation(generation);
        if ((rand() % 100 < mutation_rate) && (index + 1 < pop_size)) {
            int* mutated_child = mutate(child, n);

            new_population[index + 1].chromosome = mutated_child;
            cal_fitness(mutated_child, n, max_weight, items, &new_population[index + 1]);

            index++;
        }

        index++;
    }

    return new_population;
}

void print_population(chromosomes* pop, int pop_size, int n) {
    int printFront = 10;
    for (int i = 0; i < pop_size; i++) {
        if(i >= printFront && i <= n - printFront) continue;
        printf("Chromosome %d: ", i + 1);
        for (int j = 0; j < n; j++) {
            printf("%d", pop[i].chromosome[j]);
        }
        printf(" | Fitness: %d | Total Weight: %d\n", pop[i].fitness, pop[i].total_weight);
    }
}

item* initialItem(int n, int *weight, int *cost) {
    // Correct memory allocation
    item* items = (item*) malloc(n * sizeof(item)); 
    if (items == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        items[i].weight = weight[i];
        items[i].cost = cost[i];
    }
    return items;
}


AnswerStruct run_ga(int *weight, int *cost, int capacity, int n, LARGE_INTEGER frequency){
    long long start_time = get_time();
    int pop_size = MAX_POPULATION;
    item* items = (item*) malloc(n * sizeof(item)); 
    if (items == NULL) {
        printf("Error: Items allocation failed.\n");
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        items[i].weight = weight[i];
        items[i].cost = cost[i];
    }
    if (items == NULL) {
        printf("Error: Items initialization failed.\n");
        printf("Terminated Genetic Algorithm: Knapsack Solver(run_ga).\n");
        AnswerStruct answer;
        answer.running_time = 0;
        answer.answer_chromosome = NULL;
        answer.answer_costs = 0;
        answer.testcases_weight = weight;
        answer.testcases_values = cost;
        answer.testcases_capacity = capacity;
        answer.testcases_n = n;
        answer.iserror = 1;
        return answer;
    }
    chromosomes* population = initial_pop(pop_size, n, capacity, items);
    printf("Initial population success....\n");
	long long end_time = get_time();

    double time_taken = convert_to_seconds(start_time, end_time, frequency.QuadPart);
    printf("Time taken to generate %d population: %.10f seconds\n", pop_size, time_taken);

    int max_fitness = -1;
    int no_change_count = 0;
    int generation = 0;
    while (generation < MAX_GENERATION) {
        sort_population(population, pop_size);

        if (population[0].fitness == max_fitness) {
            no_change_count++;
        } else {
            max_fitness = population[0].fitness;
            no_change_count = 0;
        }
        if (no_change_count >= STOP_CONDITION_FITNESS_STAGNATED) {
            printf("[Stopping] Fitness stagnated for %d generations.\n", STOP_CONDITION_FITNESS_STAGNATED);
            break;
        }
		
        chromosomes* new_population = tournament_selection(population, pop_size, n, capacity, items, generation);
        end_time = get_time();

	    time_taken = convert_to_seconds(start_time, end_time, frequency.QuadPart);
		// printf("[%.5f sec]#%5d Generation [Dup: #%4d] Fitness: %6d, Weight: %6d\n",time_taken, generation, no_change_count, population[0].fitness, population[0].total_weight);
		printf("[%06.3fsec][GEN #%05d][Dup: #%05d] Fitness: %6d, Weight: %6d\n",time_taken, generation, no_change_count, population[0].fitness, population[0].total_weight);
        free_pop(population, pop_size);
        population = new_population;
		
        generation++;
    }
	end_time = get_time();

    time_taken = convert_to_seconds(start_time, end_time, frequency.QuadPart);
    // printf("Optimal solution found with fitness %d in generation %d.\n", max_fitness, generation);
    // print_population(population, 2, n);
	// printf("Time used: %.10f seconds.\n", time_taken);
    AnswerStruct answer;
    answer.running_time = time_taken;
    answer.answer_chromosome = (int*)malloc(n * sizeof(int));
    answer.testcases_weight = (int *)malloc(n * sizeof(int));
    answer.testcases_values = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        answer.answer_chromosome[i] = population[0].chromosome[i];
        answer.testcases_weight[i] = weight[i];
        answer.testcases_values[i] = cost[i];
    }
    answer.answer_generation_stop = generation;
    answer.answer_costs = max_fitness;
    answer.testcases_capacity = capacity;
    answer.testcases_n = n;
    answer.iserror = 0;
    free_pop(population, pop_size);
    return answer;
}