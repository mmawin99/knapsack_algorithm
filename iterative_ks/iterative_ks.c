#include <iterative_ks.h>

// Function to calculate the total value of the current solution
int calculateValue(int values[], int solution[], int n) {
    int totalValue = 0;
    for (int i = 0; i < n; i++) {
        if (solution[i] == 1) {
            totalValue += values[i];
        }
    }
    return totalValue;
}

// Function to calculate the total weight of the current solution
int calculateWeight(int weights[], int solution[], int n) {
    int totalWeight = 0;
    for (int i = 0; i < n; i++) {
        if (solution[i] == 1) {
            totalWeight += weights[i];
        }
    }
    return totalWeight;
}

// Function to initialize the solution using a greedy approach
void initializeGreedy(int weights[], int values[], int solution[], int n, int capacity) {
    double ratio[n];
    for (int i = 0; i < n; i++) {
        ratio[i] = (double)values[i] / weights[i];
    }

    // Sort items based on value-to-weight ratio
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (ratio[i] < ratio[j]) {
                // Swap weights, values, and ratios
                double tempRatio = ratio[i];
                ratio[i] = ratio[j];
                ratio[j] = tempRatio;

                int tempWeight = weights[i];
                weights[i] = weights[j];
                weights[j] = tempWeight;

                int tempValue = values[i];
                values[i] = values[j];
                values[j] = tempValue;
            }
        }
    }

    // Greedy selection
    int currentWeight = 0;
    for (int i = 0; i < n; i++) {
        if (currentWeight + weights[i] <= capacity) {
            solution[i] = 1;
            currentWeight += weights[i];
        } else {
            solution[i] = 0;
        }
    }
}

// Function to improve the solution iteratively
void iterativeImprovement(int weights[], int values[], int solution[], int n, int capacity) {
    int currentWeight = calculateWeight(weights, solution, n);

    int improved = 1;
    while (improved) {
        improved = 0;
        for (int i = 0; i < n; i++) {
            if (solution[i] == 1) { // Try removing item i
                solution[i] = 0;
                currentWeight -= weights[i];
                for (int j = 0; j < n; j++) {
                    if (solution[j] == 0 && currentWeight + weights[j] <= capacity) {
                        // Try adding item j
                        solution[j] = 1;
                        currentWeight += weights[j];
                        int newValue = calculateValue(values, solution, n);
                        int oldValue = calculateValue(values, solution, n);
                        if (newValue > oldValue) {
                            improved = 1;
                        } else {
                            // Revert the swap
                            solution[j] = 0;
                            currentWeight -= weights[j];
                        }
                    }
                }
                solution[i] = 1; // Revert removal of item i
                currentWeight += weights[i];
            }
        }
    }
}

// Main function
AnswerStruct run_iterative(int *weights, int *values, int capacity, int n, LARGE_INTEGER frequency) {
    int solution[n];
	
	long long start_time = get_time();

    initializeGreedy(weights, values, solution, n, capacity);

    iterativeImprovement(weights, values, solution, n, capacity);

	long long end_time = get_time();
	// double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC; 
	double time_taken = convert_to_seconds(start_time, end_time, frequency.QuadPart);
    // printf("Time Used: %.10f\n",time_taken);
	
    int totalValue = calculateValue(values, solution, n);
    int totalWeight = calculateWeight(weights, solution, n);
    // printf("Total value: %d\n", totalValue);
    // printf("Total weight: %d\n", totalWeight);

    AnswerStruct answer;
    answer.running_time = time_taken;
    answer.answer_costs = totalValue;
    answer.testcases_weight = weights;
    answer.testcases_values = values;
    answer.testcases_capacity = capacity;
    answer.testcases_n = n;
    answer.iserror = 0;
    return answer;
}
