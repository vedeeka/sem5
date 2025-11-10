#include <stdio.h>

int main() {
    int numBlocks, numProcesses;

    printf("Enter number of memory blocks: ");
    scanf("%d", &numBlocks);

    int blockSize[numBlocks], tempBlockSize[numBlocks];

    printf("Enter sizes of memory blocks:\n");
    for (int i = 0; i < numBlocks; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
        tempBlockSize[i] = blockSize[i];
    }

    printf("\nEnter number of processes: ");
    scanf("%d", &numProcesses);

    int processSize[numProcesses];
    for (int i = 0; i < numProcesses; i++) {
        printf("Process %d size: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    int allocation[numProcesses];
    for (int i = 0; i < numProcesses; i++) {
        allocation[i] = -1;

        int worstIdx = -1;
        for (int j = 0; j < numBlocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }

        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }

    int used[numBlocks];
    for (int i = 0; i < numBlocks; i++)
        used[i] = 0;

    int total = 0;

    printf("\nMemory Block\tProcesses\tRemaining Memory\n");
    for (int i = 0; i < numBlocks; i++) {
        printf("   %d\t\t", tempBlockSize[i]);

        int hasProcess = 0;
        for (int j = 0; j < numProcesses; j++) {
            if (allocation[j] == i) {
                used[i] = 1;
                printf("%d  ", processSize[j]);
                hasProcess = 1;
            }
        }
        if (!hasProcess)
            printf("X");

        printf("\t\t%d\n", blockSize[i]);
        total += blockSize[i];
    }

    printf("\nTotal remaining memory available: %d\n\n", total);

    printf("Process Allocation Details:\n");
    for (int i = 0; i < numProcesses; i++) {
        if (allocation[i] != -1)
            printf("Process %d (Size %d) allocated to Block %d (Original Size %d)\n",
                   i + 1, processSize[i], allocation[i] + 1, tempBlockSize[allocation[i]]);
        else
            printf("Process %d (Size %d) not allocated.\n", i + 1, processSize[i]);
    }

    return 0;
}
