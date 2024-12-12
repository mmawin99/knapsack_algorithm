#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h> // Include Windows header for high-resolution timing
long long get_time();
double convert_to_seconds(long long start, long long end, double frequency);
#ifndef ANSWER_STRUCT_H
#define ANSWER_STRUCT_H

typedef struct AnswerStruct {
    double running_time;
    int* answer_chromosome;
    int answer_generation_stop;
    int answer_costs;
    int* testcases_weight;
    int* testcases_values;
    int testcases_capacity;
    int testcases_n;
    int iserror;
} AnswerStruct;

#endif // ANSWER_STRUCT_H