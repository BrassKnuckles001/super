#include <stdio.h>
#include <stdbool.h>

void findWaitingTime(int processes[], int n, int bt[], int wt[]) {
    int completed = 0, t = 0, min_index;
    bool isCompleted[n];

    for (int i = 0; i < n; i++)
        isCompleted[i] = false;

    while (completed < n) {
        min_index = -1;
        for (int j = 0; j < n; j++) {
            if (!isCompleted[j] && bt[j] <= t) {
                if (min_index == -1 || bt[j] < bt[min_index])
                    min_index = j;
            }
        }

        if (min_index != -1) {
            wt[min_index] = t - bt[min_index];
            t += bt[min_index];
            isCompleted[min_index] = true;
            completed++;
        } else {
            t++;
        }
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
