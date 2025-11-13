#include <stdio.h>

int main() {
    int nBlocks, nProcesses;
    int blockSize[50], tempBlockSize[50], processSize[50], allocation[50];
    int i, j, bestIdx, totalRemaining = 0;

    printf("Enter number of memory blocks: ");
    scanf("%d", &nBlocks);

    printf("Enter sizes of each memory block:\n");
    for (i = 0; i < nBlocks; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
        tempBlockSize[i] = blockSize[i];
    }

    printf("\nEnter number of processes: ");
    scanf("%d", &nProcesses);

    for (i = 0; i < nProcesses; i++) {
        printf("Process %d size: ", i + 1);
        scanf("%d", &processSize[i]);
        allocation[i] = -1; // no allocation yet
    }

    // Best Fit Allocation Logic with iteration + remaining memory display
    printf("\n===== Best Fit Allocation Process =====\n");
    for (i = 0; i < nProcesses; i++) {
        bestIdx = -1;
        printf("\nIteration %d: Trying to allocate Process %d (Size %d)\n",
               i + 1, i + 1, processSize[i]);

        for (j = 0; j < nBlocks; j++) {
            printf("  Checking block (Available %d)... ", blockSize[j]);
            if (blockSize[j] >= processSize[i]) {
                printf("Fits");
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx]) {
                    bestIdx = j;
                    printf(" -> Best so far");
                }
            }
            printf("\n");
        }

        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
            printf("=> Process %d allocated (Remaining in block: %d)\n",
                   i + 1, blockSize[bestIdx]);
        } else {
            printf("=> Process %d could NOT be allocated (No suitable block)\n", i + 1);
        }

        // Show current remaining memory in all blocks
        printf("Current remaining memory in all blocks: ");
        for (j = 0; j < nBlocks; j++) {
            printf("%d ", blockSize[j]);
        }
        printf("\n----------------------------------------\n");
    }

    // Final Output
    printf("\n===== Final Allocation Result =====\n");
    printf("\nMemory Block\tProcesses\tRemaining Memory\n");
    for (i = 0; i < nBlocks; i++) {
        printf("   %d\t\t", tempBlockSize[i]);

        int hasProcess = 0;
        for (j = 0; j < nProcesses; j++) {
            if (allocation[j] == i) {
                printf("%d ", processSize[j]);
                hasProcess = 1;
            }
        }
        if (!hasProcess)
            printf("X");

        printf("\t\t%d\n", blockSize[i]);
        totalRemaining += blockSize[i];
    }

    printf("\nTotal remaining memory available: %d\n", totalRemaining);

    printf("\nProcess Allocation Details:\n");
    for (i = 0; i < nProcesses; i++) {
        if (allocation[i] != -1) {
            printf("Process %d (Size %d) allocated to block of size %d\n",
                   i + 1, processSize[i], tempBlockSize[allocation[i]]);
        } else {
            printf("Process %d (Size %d) not allocated.\n", i + 1, processSize[i]);
        }
    }

    return 0;
}
