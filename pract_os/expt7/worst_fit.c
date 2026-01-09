#include <stdio.h>

int main() {
    int numBlocks, numProcesses;

    printf("Enter number of memory blocks: ");
    scanf("%d", &numBlocks);

    int blockSize[numBlocks], tempBlockSize[numBlocks];

    printf("Enter sizes of memory blocks:\n");
    for (int i = 0; i < numBlocks; i++) {
        scanf("%d", &blockSize[i]);
        tempBlockSize[i] = blockSize[i];
    }

    printf("Enter number of processes: ");
    scanf("%d", &numProcesses);

    int processSize[numProcesses];
    printf("Enter sizes of processes:\n");
    for (int i = 0; i < numProcesses; i++) {
        scanf("%d", &processSize[i]);
    }

    int allocation[numProcesses];
    for (int i = 0; i < numProcesses; i++)
        allocation[i] = -1;

    // Worst Fit Allocation
    for (int i = 0; i < numProcesses; i++) {
        int worstIdx = -1;
        for (int j = 0; j < numBlocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }

    // Final Table
    printf("\nMemory Block\tProcesses\tRemaining\n");
    for (int i = 0; i < numBlocks; i++) {
        printf("%d\t\t", tempBlockSize[i]);
        int printed = 0;
        for (int j = 0; j < numProcesses; j++) {
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
    for (int i = 0; i < numProcesses; i++) {
        if (allocation[i] != -1)
            printf("Process %d (%d) -> Block %d\n",
                   i + 1, processSize[i], allocation[i] + 1);
        else
            printf("Process %d (%d) -> Not Allocated\n",
                   i + 1, processSize[i]);
    }

    return 0;
}
