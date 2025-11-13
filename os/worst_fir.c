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

    printf("\n===== Worst Fit Allocation Process =====\n");

    for (int i = 0; i < numProcesses; i++) {
        int worstIdx = -1;
        printf("\nIteration %d: Trying to allocate Process %d (Size %d)\n", i + 1, i + 1, processSize[i]);

        for (int j = 0; j < numBlocks; j++) {
            printf("  Checking block (Available %d)... ", blockSize[j]);
            if (blockSize[j] >= processSize[i]) {
                printf("Fits");
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) {
                    worstIdx = j;
                    printf(" -> Worst so far");
                }
            }
            printf("\n");
        }

        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
            printf("=> Process %d allocated to block (Remaining in that block: %d)\n",
                   i + 1, blockSize[worstIdx]);
        } else {
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
