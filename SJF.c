// Alex Ryse
// CS 470 - Operating Systems

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Constant for the number of processes
#define NUM_PROCESSES 4

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time; // Used to track CPU Scheduling
    int waiting_time;
    int turnaround_time;
    int is_completed;
} Process;

// Function to find the index of the next process to run based on Shortest Time Remaining First (preemptive)
// Finds the process with the minimum remaining time for all processes that have arrived and not finished
int findNextProcess(Process proc[], int n, int current_time) {
    int lowest_remaining_time = INT_MAX;
    int index = -1;

    for (int i = 0; i < n; i++) {
        // Check if current process has:
        // Arrived
        // Not finished
        // Minimum remaining time
        if (proc[i].arrival_time <= current_time && !proc[i].is_completed) {
            if (proc[i].remaining_time < lowest_remaining_time) {
                // Update lowest remaining time and index trackers
                lowest_remaining_time = proc[i].remaining_time;
                index = i;
            }
        }
    }
    // Return the index, will return -1 only if no processes are ready
    return index;
}

// Function to check if all the processes have finished
int allProcessesFinished(Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        // Check if any process is not finished
        if (!proc[i].is_completed) {
            return 0;
        }
    }
    // Return 1 only if all processes have finished
    return 1;
}

// Function to perform the Shortest Remaining Time First (preemptive) scheduling
void srtf(Process proc[], int n) {
    int time = 0; // Time tracker for simulation
    int prev_process_index = -1; // Index of previous process in simulation
    
    // Continue the simulation until all processes have finished
    while (!allProcessesFinished(proc, n)) {
        // Find current process to run
        int curr_process_index = findNextProcess(proc, n, time);

        // Skip current time if no processes are ready
        if (curr_process_index == -1) {
            time++;
            continue;
        }

        // Check if current process is different from previous process
        if (curr_process_index != prev_process_index) {
            // Display the current process has started
            printf("Time %d: Process %d starts\n", time, proc[curr_process_index].process_id);
        }

        // Update current process remaining time
        proc[curr_process_index].remaining_time--;

        // Check if current process has finished
        if (proc[curr_process_index].remaining_time == 0) {
            // Set current process as finished
            proc[curr_process_index].is_completed = 1;

            // Calculate the Waiting Time and Turnaround Time
            // Waiting Time: Current Time (time+1) - Arrival Time - Burst Time
            proc[curr_process_index].waiting_time = 
                time + 1 - proc[curr_process_index].arrival_time - proc[curr_process_index].burst_time;
            // Turnaround Time: Current Time (time+1) - Arrival Time
            proc[curr_process_index].turnaround_time = time + 1 - proc[curr_process_index].arrival_time;

            // Display the current process finishes
            printf("Time %d: Process %d finishes\n", time + 1, proc[curr_process_index].process_id);

            // Reset previous process index back to -1
            prev_process_index = -1;
        } else {
            // Update previous process index for next iteration
            prev_process_index = curr_process_index;
        }
        // Update the time to keep the simulation running
        time++;
    }
}

// Function to calculate the average waiting time and turnaround time
void calcAvg(Process proc[], int n) {
    float avg_waiting_time = 0;
    float avg_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        avg_waiting_time += proc[i].waiting_time;
        avg_turnaround_time += proc[i].turnaround_time;
    }
    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    // Display the averages results
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

// Function to print the processes and their details
void printProcesses(Process proc[], int n) {
    printf("\nProcess ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    // Initialize processes with their IDs, arrival times, and burst times
    Process proc[NUM_PROCESSES] = {
        {1, 0, 8, 8, 0, 0, 0}, 
        {2, 1, 4, 4, 0, 0, 0}, 
        {3, 2, 9, 9, 0, 0, 0}, 
        {4, 3, 5, 5, 0, 0, 0}
    };

    srtf(proc, NUM_PROCESSES);
    printProcesses(proc, NUM_PROCESSES);
    calcAvg(proc, NUM_PROCESSES);

    return 0;
}
