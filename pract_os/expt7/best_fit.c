#include <stdio.h>

int main() {
    int nBlocks, nProcesses;
    int blockSize[50], tempBlockSize[50], processSize[50], allocation[50];

    printf("Enter number of memory blocks: ");
    scanf("%d", &nBlocks);

    printf("Enter sizes of memory blocks:\n");
    for (int i = 0; i < nBlocks; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
        tempBlockSize[i] = blockSize[i];
    }

    printf("Enter number of processes: ");
    scanf("%d", &nProcesses);

    printf("Enter sizes of processes:\n");
    for (int i = 0; i < nProcesses; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
        allocation[i] = -1;
    }

    // Best Fit Allocation
    for (int i = 0; i < nProcesses; i++) {
        int bestIdx = -1;
        for (int j = 0; j < nBlocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    // Final Table
    printf("\nMemory Block\tProcesses\tRemaining\n");
    for (int i = 0; i < nBlocks; i++) {
        printf("%d\t\t", tempBlockSize[i]);
        int printed = 0;
        for (int j = 0; j < nProcesses; j++) {
            if (allocation[j] == i) {
                printf("%d ", processSize[j]);
                printed = 1;
            }
        }
        if (!printed) printf("X");
        printf("\t\t%d\n", blockSize[i]);
    }

    // Process Allocation Details
    printf("\nProcess Allocation Details:\n");
    for (int i = 0; i < nProcesses; i++) {
        if (allocation[i] != -1)
            printf("Process %d (%d) -> Block %d\n",
                   i + 1, processSize[i], allocation[i] + 1);
        else
            printf("Process %d (%d) -> Not Allocated\n",
                   i + 1, processSize[i]);
    }

    return 0;
}
