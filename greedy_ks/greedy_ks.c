#include <greedy_ks.h>

int compare(const void* a, const void* b) {
    Item* itemA = (Item*)a;
    Item* itemB = (Item*)b;
    if (itemB->ratio > itemA->ratio) return 1;
    else if (itemB->ratio < itemA->ratio) return -1;
    else return 0;
}


int knapsack(int capacity, Item items[], int n) {
	clock_t start_time = clock(); // Start timing
    qsort(items, n, sizeof(Item), compare);

    int totalValue = 0;
    for (int i = 0; i < n; i++) {
        if (items[i].weight <= capacity) {
            
            capacity -= items[i].weight;
            totalValue += items[i].value;
        }
        clock_t end_time = clock();
		double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC; 
		// printf("Time Complexity: %f\n",time_taken);
    }
    	
    return totalValue;
}

AnswerStruct run_greedy(int *weight, int *cost, int capacity, int n, LARGE_INTEGER frequency) {

    Item items[n];
    // printf("Enter weight and value of each item:\n");
    for (int i = 0; i < n; i++) {
        items[i].weight = weight[i];
        items[i].value = cost[i];
        items[i].ratio = (double)items[i].value / items[i].weight;
    }
	long long start_time = get_time();
    int maxValue = knapsack(capacity, items, n);
    // printf("Maximum value in knapsack = %d\n", maxValue);
    long long end_time = get_time();
	double time_taken = convert_to_seconds(start_time, end_time, frequency.QuadPart);
    // printf("Time Used: %.10f\n",time_taken);
    AnswerStruct answer;
    answer.running_time = time_taken;
    answer.answer_costs = maxValue;
    answer.testcases_weight = weight;
    answer.testcases_values = cost;
    answer.testcases_capacity = capacity;
    answer.testcases_n = n;
    answer.iserror = 0;
    return answer;
}