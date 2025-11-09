// Alex Ryse
// CS 470 - Operating Systems

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Constant for the number of processes
#define NUM_PROCESSES 3

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
} Process;

// Function to calculate waiting times, turnaround times, and execution order for all processes
void calculateWaitingTimeAndTurnaroundTimeAndExecutionOrder(Process proc[], int n, int quantum) {
    int time = 0; // Time tracker for simulation
    int num_finished = 0; // Number of processes finished

    // Display execution order prefix
    printf("Execution Order: ");

    // Continue the simulation untill all processes have finished
    while (num_finished < n) {
        // Iterate through each process equally
        for (int i = 0; i < n; i++) {
            // Check if the current process is not finished
            if (proc[i].remaining_time > 0) {
                // Display the current process
                printf("P%d ", proc[i].process_id);

                // Determine the execution time of current process
                // Check if execution time is smaller than time quantum
                // Update the time to keep the simulation running
                if (proc[i].remaining_time < quantum) {
                    time += proc[i].remaining_time;
                    proc[i].remaining_time -= proc[i].remaining_time;
                } else {
                    time += quantum;
                    proc[i].remaining_time -= quantum;
                }

                // Check if the current process has finished
                if (proc[i].remaining_time <= 0) {
                    // Update number of processes finished
                    num_finished++;

                    // Calculate the turnaround time and waiting time of current process
                    // Turnaround Time: Current Time (time) - Arrival Time
                    proc[i].turnaround_time = time - proc[i].arrival_time;
                    // Waiting Time: Turnaround Time - Burst Time
                    proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
                }
            }
        }
    }
}

// Function to perform the Round Robin (preemptive) scheduling
void roundRobin(Process proc[], int n, int quantum) {
    calculateWaitingTimeAndTurnaroundTimeAndExecutionOrder(proc, n, quantum);
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
    printf("\n\nProcess ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    Process proc[NUM_PROCESSES] = {
        {1, 0, 24, 24, 0, 0}, 
        {2, 0, 3, 3, 0, 0}, 
        {3, 0, 3, 3, 0, 0}
    };
    int quantum = 4; // Time quantum for Round Robin scheduling

    roundRobin(proc, NUM_PROCESSES, quantum);
    printProcesses(proc, NUM_PROCESSES);
    calcAvg(proc, NUM_PROCESSES);

    return 0;
}
