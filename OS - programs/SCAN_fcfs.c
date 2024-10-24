#include <stdio.h>
#include <stdlib.h>
#define MAX_REQUESTS 100

void fcfs(int requests[], int n, int head) {
    int total_movement = 0, current = head;
    printf("FCFS Scheduling Order:\n");
    for (int i = 0; i < n; i++) {
        printf("Move from %d to %d\n", current, requests[i]);
        total_movement += abs(current - requests[i]);
        current = requests[i];
    }
    printf("Total head movement: %d\n", total_movement);
}

void scan(int requests[], int n, int head) {
    int total_movement = 0, current = head;
    int sorted_requests[MAX_REQUESTS];

    for (int i = 0; i < n; i++) sorted_requests[i] = requests[i];

    
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (sorted_requests[j] > sorted_requests[j + 1]) {
                int temp = sorted_requests[j];
                sorted_requests[j] = sorted_requests[j + 1];
                sorted_requests[j + 1] = temp;
            }

    printf("SCAN Scheduling Order:\n");
    for (int i = 0; i < n; i++) {
        if (sorted_requests[i] >= current) {
            printf("Move from %d to %d\n", current, sorted_requests[i]);
            total_movement += abs(current - sorted_requests[i]);
            current = sorted_requests[i];
        }
    }
    
    printf("Move from %d to %d\n", current, sorted_requests[n - 1]);
    total_movement += abs(current - sorted_requests[n - 1]);
    current = sorted_requests[n - 1];

    for (int i = n - 1; i >= 0; i--) {
        if (sorted_requests[i] <= current) {
            printf("Move from %d to %d\n", current, sorted_requests[i]);
            total_movement += abs(current - sorted_requests[i]);
            current = sorted_requests[i];
        }
    }
    printf("Total head movement: %d\n", total_movement);
}

int main() {
    int requests[MAX_REQUESTS], n, head;
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    if (n > MAX_REQUESTS) return 1;

    printf("Enter the requests:\n");
    for (int i = 0; i < n; i++) scanf("%d", &requests[i]);
    printf("Enter the initial head position: ");
    scanf("%d", &head);

    fcfs(requests, n, head);
    printf("\n");
    scan(requests, n, head);
    
    return 0;
}
