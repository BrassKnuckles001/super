#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100
#define MAX_PROCESSES 100

void worstFit(int blockSize[], int numBlocks, int processSize[], int numProcesses) {
    int allocation[MAX_PROCESSES];
    for (int i = 0; i < numProcesses; i++) allocation[i] = -1;

    for (int i = 0; i < numProcesses; i++) {
        int largestBlockIndex = -1;
        for (int j = 0; j < numBlocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (largestBlockIndex == -1 || blockSize[largestBlockIndex] < blockSize[j])
                    largestBlockIndex = j;
            }
        }
        if (largestBlockIndex != -1) {
            allocation[i] = largestBlockIndex;
            blockSize[largestBlockIndex] -= processSize[i];
        }
    }

    printf("Worst Fit Allocation:\n");
    for (int i = 0; i < numProcesses; i++)
        printf("Process %d allocated to Block %d\n", i, allocation[i]);
}

void bestFit(int blockSize[], int numBlocks, int processSize[], int numProcesses) {
    int allocation[MAX_PROCESSES];
    for (int i = 0; i < numProcesses; i++) allocation[i] = -1;

    for (int i = 0; i < numProcesses; i++) {
        int bestBlockIndex = -1;
        for (int j = 0; j < numBlocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestBlockIndex == -1 || blockSize[bestBlockIndex] > blockSize[j])
                    bestBlockIndex = j;
            }
        }
        if (bestBlockIndex != -1) {
            allocation[i] = bestBlockIndex;
            blockSize[bestBlockIndex] -= processSize[i];
        }
    }

    printf("Best Fit Allocation:\n");
    for (int i = 0; i < numProcesses; i++)
        printf("Process %d allocated to Block %d\n", i, allocation[i]);
}

void firstFit(int blockSize[], int numBlocks, int processSize[], int numProcesses) {
    int allocation[MAX_PROCESSES];
    for (int i = 0; i < numProcesses; i++) allocation[i] = -1;

    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numBlocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    printf("First Fit Allocation:\n");
    for (int i = 0; i < numProcesses; i++)
        printf("Process %d allocated to Block %d\n", i, allocation[i]);
}

int main() {
    int blockSize[MAX_BLOCKS], processSize[MAX_PROCESSES];
    int numBlocks, numProcesses;

    printf("Enter the number of memory blocks: ");
    scanf("%d", &numBlocks);
    printf("Enter the sizes of memory blocks:\n");
    for (int i = 0; i < numBlocks; i++) {
        printf("Block %d: ", i);
        scanf("%d", &blockSize[i]);
    }

    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);
    printf("Enter the sizes of processes:\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("Process %d: ", i);
        scanf("%d", &processSize[i]);
    }

    worstFit(blockSize, numBlocks, processSize, numProcesses);
    printf("\n");
    bestFit(blockSize, numBlocks, processSize, numProcesses);
    printf("\n");
    firstFit(blockSize, numBlocks, processSize, numProcesses);

    return 0;
}
