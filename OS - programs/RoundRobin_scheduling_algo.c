#include <stdio.h>
#include <stdbool.h> // Include this header for boolean type

void findAvgTime(int processes[], int n, int bt[], int quantum) {
    int wt[n], tat[n], rem_bt[n];
    
    for (int i = 0; i < n; i++)
        rem_bt[i] = bt[i];

    int t = 0; // Current time
    while (1) {
        bool done = true; // Set done to true at the start of each round
        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {
                done = false; // There is a pending process
                if (rem_bt[i] > quantum) {
                    t += quantum;
                    rem_bt[i] -= quantum;
                } else {
                    t = t + rem_bt[i];
                    wt[i] = t - bt[i];
                    rem_bt[i] = 0;
                }
            }
        }
        if (done) break; // All processes are done
    }

    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];

    for (int i = 0; i < n; i++) {
        printf("Process %d\n", processes[i]);
        printf("Burst Time: %d\n", bt[i]);
        printf("Waiting Time: %d\n", wt[i]);
        printf("Turnaround Time: %d\n\n", tat[i]);
    }
}

int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int processes[n];
    int burstTime[n];
    
    for (int i = 0; i < n; i++) {
        processes[i] = i; // Assign process ID
        printf("Enter burst time for process %d: ", i);
        scanf("%d", &burstTime[i]);
    }
    
    printf("Enter time quantum for Round Robin: ");
    scanf("%d", &quantum);

    findAvgTime(processes, n, burstTime, quantum);
    return 0;
}
