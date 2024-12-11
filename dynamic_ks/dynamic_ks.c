#include <dynamic_ks.h>
int knapsack_dp(int capacity, int weights[], int values[], int n) {
    clock_t start_time = clock(); // Start timing
    int *dp = (int *)calloc(capacity + 1, sizeof(int));

    for (int i = 0; i < n; i++) {
        for (int w = capacity; w >= weights[i]; w--) {
            dp[w] = dp[w] > (values[i] + dp[w - weights[i]]) 
                    ? dp[w] 
                    : (values[i] + dp[w - weights[i]]);
        }
        clock_t end_time = clock();
        double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        printf("Time Complexity: %f\n",time_taken); 
    }

    int result = dp[capacity];
    free(dp);
    
    
    return result;
}

int run_dynamic(int *weights, int *values, int capacity, int n, LARGE_INTEGER frequency) {
    long long start_time = get_time();
    int maxValue = knapsack_dp(capacity, weights, values, n);
    printf("Maximum value in the knapsack: %d\n", maxValue);
    long long end_time = get_time();
	double time_taken = convert_to_seconds(start_time, end_time, frequency.QuadPart);
    printf("Time Used: %.10f\n",time_taken);
    free(weights);
    free(values);

    return maxValue;
}