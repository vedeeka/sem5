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
    }

    printf("\n===== First Fit Allocation Process =====\n");

    for (int i = 0; i < numProcesses; i++) {
        printf("\nIteration %d: Trying to allocate Process %d (Size %d)\n", i + 1, i + 1, processSize[i]);
        for (int j = 0; j < numBlocks; j++) {
            printf("  Checking block (Available %d)... ", blockSize[j]);
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                printf("Fits -> Allocated\n");
                break;
            } else {
                printf("Does not fit\n");
            }
        }

        if (allocation[i] == -1) {
            printf("=> Process %d could NOT be allocated (No suitable block found)\n", i + 1);
        }

        // Show current remaining memory in all blocks
        printf("Current remaining memory in all blocks: ");
        for (int k = 0; k < numBlocks; k++) {
            printf("%d ", blockSize[k]);
        }
        printf("\n----------------------------------------\n");
    }

    int used[numBlocks];
    for (int i = 0; i < numBlocks; i++)
        used[i] = 0;

    int total = 0;

    printf("\n===== Final Allocation Result =====\n");
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

    printf("\nThe total memory available: %d\n\n", total);

    for (int i = 0; i < numProcesses; i++) {
        if (allocation[i] != -1)
            printf("Process %d (size %d) has been allocated block of size %d\n", 
                   i + 1, processSize[i], tempBlockSize[allocation[i]]);
        else
            printf("Process %d (size %d) has not been allocated.\n", 
                   i + 1, processSize[i]);
    }

    return 0;
}
