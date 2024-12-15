#include <main.h>

long long get_time(){
    LARGE_INTEGER time;
    QueryPerformanceCounter(&time); // Get the current time
    return time.QuadPart;           // Return the time as a high-resolution counter value
}
double convert_to_seconds(long long start, long long end, double frequency){
    return (double)(end - start) / frequency; // Convert to seconds
}