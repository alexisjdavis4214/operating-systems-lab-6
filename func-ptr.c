#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>

#include "process.h"
#include "util.h"

#define DEBUG 0  // Change this to 1 to enable verbose output

/**
 * Signature for a function pointer that can compare
 * You need to cast the input into its actual 
 * type and then compare them according to your
 * custom logic
 */
typedef int (*Comparer)(const void *a, const void *b);

/**
 * Compares two processes based on the following criteria:
 * 1. Arrival time (earlier first)
 * 2. Priority (higher first if arrival time is the same)
 * 3. Process ID (lower first if both above are equal)
 */
int my_comparer(const void *this, const void *that)
{
    const Process *p1 = (const Process *)this;
    const Process *p2 = (const Process *)that;

    // Compare by arrival_time
    if (p1->arrival_time != p2->arrival_time)
        return p1->arrival_time - p2->arrival_time;

    // Compare by priority if arrival_time is the same
    if (p1->priority != p2->priority)
        return p2->priority - p1->priority;  // Higher priority first

    // Compare by PID if both arrival_time and priority are the same
    return p1->pid - p2->pid;
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: ./func-ptr <input-file-path>\n");
        fflush(stdout);
        return 1;
    }

    /*******************/
    /* Parse the input */
    /*******************/
    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        fprintf(stderr, "Error: Invalid filepath\n");
        fflush(stdout);
        return 1;
    }

    Process *processes = parse_file(input_file);

    /*******************/
    /* Sort the input  */
    /*******************/
    Comparer process_comparer = &my_comparer;

#if DEBUG
    for (int i = 0; i < P_SIZE; i++) {
        printf("%d (%d, %d) ", processes[i].pid, processes[i].priority, processes[i].arrival_time);
    }
    printf("\n");
#endif

    qsort(processes, P_SIZE, sizeof(Process), process_comparer);

    /**************************/
    /* Print the sorted data  */
    /**************************/
    for (int i = 0; i < P_SIZE; i++) {
        printf("%d (%d, %d)\n", processes[i].pid, processes[i].priority, processes[i].arrival_time);
    }

    fflush(stdout);
    fflush(stderr);

    /************/
    /* Clean up */
    /************/
    free(processes);
    fclose(input_file);
    return 0;
}
