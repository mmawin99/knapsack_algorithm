#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h> // Include Windows header for high-resolution timing
long long get_time();
double convert_to_seconds(long long start, long long end, double frequency);