#include <main.h>
int main(){
    int input_mode; // 1 for manual input, 2 for file input
    int error = 0;
    int capacity;
    int *weights = NULL, *values = NULL;
    int n;
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    printf("|-- Algorithm for solving Knapsack problem --|\n");
    printf("choose input mode: 1 for manual input, 2 for file input\n");
    printf("Enter your choice: ");
    scanf("%d", &input_mode);
    if(input_mode == 1){
        printf("Enter the number of items: ");
        scanf("%d", &n);
        weights = (int*)malloc(n * sizeof(int));
        values = (int*)malloc(n * sizeof(int));
        for(int i = 0; i < n; i++){
            printf("Enter the weight and costs of item %d: ", i+1);
            scanf("%d %d", &weights[i], &values[i]);
        }
        printf("Enter the capacity of the knapsack: ");
        scanf("%d", &capacity);
    }else if(input_mode == 2){
        char filename [100];
        char filedir [100] = "./testcases/";
        FILE* fileptr;
        FILE* logfileptr;
        printf("Enter Input File Name in folder testcases: ");
        scanf("%s", filename);
        strcat(filedir, filename);
        strcat(filedir, ".txt");
        fileptr = fopen(filedir, "r");
        if (fileptr == NULL) {
            printf("\n! ERROR: CAN\'T OPEN THE INPUT FILE, PLEASE TRY AGAIN\n\n");
            return 1;
        }else{
            fscanf(fileptr ,"%d", &n);
            weights = (int*)malloc(n * sizeof(int));
            values = (int*)malloc(n * sizeof(int));

            for (int i = 0; i < n; i++) {
                fscanf(fileptr, "%d %d", &weights[i], &values[i]);
            }
            fscanf(fileptr, "%d", &capacity);
        }
    }else{
        printf("Invalid input mode\n");
        return 1;
    }
    int algorithmSelector; // 1 ga, 2,dp, 3.greedy, 4.iterative

    printf("Choose the algorithm to solve the knapsack problem:\n 1. Genetic Algorithm\n 2. Iterative Improvement Algorithm\n 3. Greedy Algorithm\n 4. Dynamic Programming Algorithm\n");
    printf("Enter your choice: ");
    scanf("%d", &algorithmSelector);
    if(algorithmSelector == 1){
        printf("====================================================================\n");
        printf("Running Genetic Algorithm\n");
        int answer_ga = run_ga(weights, values, capacity, n, frequency);
        printf("====================================================================\n");
        printf("The maximum value that can be obtained is: %d\n", answer_ga);
        return 0;
    }else if(algorithmSelector == 2){
        printf("====================================================================\n");
        printf("Running Iterative Improvement Algorithm\n");
        int answer_iterative = run_iterative(weights, values, capacity, n, frequency);
        printf("====================================================================\n");
        printf("The maximum value that can be obtained is: %d\n", answer_iterative);
        return 0;
    }else if(algorithmSelector == 3){
        printf("====================================================================\n");
        printf("Running Greedy Algorithm\n");
        int answer_greedy = run_greedy(weights, values, capacity, n, frequency);
        printf("====================================================================\n");
        printf("The maximum value that can be obtained is: %d\n", answer_greedy);
        return 0;
    }else if(algorithmSelector == 4){
        printf("====================================================================\n");
        printf("Running Dynamic Programming Algorithm\n");
        int answer_dynamic = run_dynamic(weights, values, capacity, n, frequency);
        printf("====================================================================\n");
        printf("The maximum value that can be obtained is: %d\n", answer_dynamic);
        return 0;
    }
    return 0;
}