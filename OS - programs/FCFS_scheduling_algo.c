#include <stdio.h>

void findWaitingTime(int processes[], int n, int bt[], int wt[]) {
    wt[0] = 0; // First process has no waiting time
    for (int i = 1; i < n; i++) {
        wt[i] = bt[i - 1] + wt[i - 1]; // Waiting time = previous burst time + previous waiting time
    }
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i]; // Turnaround time = burst time + waiting time
    }
}

void findAvgTime(int processes[], int n, int bt[]) {
    int wt[n], tat[n];
    findWaitingTime(processes, n, bt, wt);
    findTurnAroundTime(processes, n, bt, wt, tat);
    
    for (int i = 0; i < n; i++) {
        printf("Process %d\n", processes[i]);
        printf("Burst Time: %d\n", bt[i]);
        printf("Waiting Time: %d\n", wt[i]);
        printf("Turnaround Time: %d\n\n", tat[i]);
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int processes[n];
    int burstTime[n];
    
    for (int i = 0; i < n; i++) {
        processes[i] = i; // Assign process ID
        printf("Enter burst time for process %d: ", i);
        scanf("%d", &burstTime[i]);
    }

    findAvgTime(processes, n, burstTime);
    return 0;
}
