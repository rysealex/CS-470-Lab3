// Alex Ryse
// CS 470 - Operating Systems

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int is_completed;
} Process;

int n; // Number of processes
int running; // Running state of SJF algorithm (0 = finished, 1 = running)
int time; // Time stamp of the simulation

// Function to sort the processes by arrival time
void sortArrivalTime(Process proc[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1; j++) {
            // Check if a swap is needed
            if (proc[j].arrival_time > proc[j+1].arrival_time) {
                // Perform the swap
                Process temp = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = temp;
            }
        }
    }
}

// Function to find the index of the process with the current lowest burst time
int findNextProcess(Process proc[], int n) {
    int lowest_burst_time = INT_MAX;
    int index;
    for (int i = 0; i < n; i++) {
        // Check if current process has lower burst time and has not finished
        if (proc[i].burst_time < lowest_burst_time && !(proc[i].is_completed)) {
            lowest_burst_time = proc[i].burst_time;
            index = i;
        }
    }
    return index;
}

// Function to calculate the waiting time for each process
// void calcWaitingTime(Process proc[], int n) {
//     for (int i = 0; i < n; i++) {
//         proc[i].waiting_time = 
//     }
// }

// Function to perform the Shortest Remaining Time First (preemptive) scheduling
void srtf(Process proc[], int n, int running, int time) {
    // Sort the process by arrival time
    sortArrivalTime(proc, n);

    // Calculate the waiting time for each process 

    // First start the process with lowest arrival time
    printf("Time %d: Process %d starts\n", time++, proc[0].process_id);
    // update burst time
    proc[0].burst_time -= 1;

    int current_index;

    // Start the simulation
    while (running) {
        // Increment current time
        time++;

        // Check for current lowest process burst time
        current_index = findNextProcess(proc, n);

        // Update 

        // Check if a process starts or completes


        // Print the current time
        printf("Time %d: ", time);
        
        // Find next process with shortest remaining time

    }
}

// Function to print the processes and their details
void printProcesses(Process proc[], int n) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    // Initialize processes with their IDs, arrival times, and burst times
    Process proc[] = {{1, 5, 8}, {2, 1, 4}, {3, 0, 9}, {4, 3, 5}};
    n = sizeof(proc) / sizeof(proc[0]);
    running = 1;
    time = -1;

    // srtf(proc, n, running, time);
    printProcesses(proc, n);

    return 0;
}
