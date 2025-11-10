#include <stdio.h>
#include <stdbool.h>

#define MAX_P 10
#define MAX_R 10

int n, m;
int available[MAX_R];
int max[MAX_P][MAX_R];
int allocation[MAX_P][MAX_R];
int need[MAX_P][MAX_R];
int work2D[MAX_P][MAX_R];
int safeSeq[MAX_P];


int prevAvailable[MAX_R];
int prevAllocation[MAX_P][MAX_R];
int prevNeed[MAX_P][MAX_R];
int prevWork2D[MAX_P][MAX_R];
int prevSafeSeq[MAX_P];

void calculateNeed() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
            if (need[i][j] < 0)
                need[i][j] = 0;
        }
}

bool safetyAlgorithm() {
    int work[MAX_R];
    bool finish[MAX_P];
    int count = 0;

    for (int i = 0; i < m; i++)
        work[i] = available[i];

    for (int i = 0; i < n; i++)
        finish[i] = false;

    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < m; j++)
                    if (need[i][j] > work[j])
                        break;

                if (j == m) {
                    for (int k = 0; k < m; k++)
                        work[k] += allocation[i][k];
                    finish[i] = true;
                    safeSeq[count] = i;
                    for (int k = 0; k < m; k++)
                        work2D[count][k] = work[k];
                    count++;
                    found = true;
                }
            }
        }
        if (!found)
            return false;
    }
    return true;
}

void displayData() {
    printf("\n-------------------------------------------------------------\n");
    printf("Process | Allocation\t | Max\t\t | Need\t\t | Available After\n");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        int p = safeSeq[i];
        printf("P%d\t | ", p + 1);
        for (int j = 0; j < m; j++)
            printf("%d ", allocation[p][j]);
        printf("\t | ");
        for (int j = 0; j < m; j++)
            printf("%d ", max[p][j]);
        printf("\t | ");
        for (int j = 0; j < m; j++)
            printf("%d ", need[p][j]);
        printf("\t | ");
        for (int j = 0; j < m; j++)
            printf("%d ", work2D[i][j]);
        printf("\n");
    }
    printf("-------------------------------------------------------------\n");

    printf("Safe Sequence: ");
    for (int i = 0; i < n; i++)
        printf("P%d ", safeSeq[i] + 1);
    printf("\n System is in a SAFE state.\n");
}

void backupState() {
    for (int i = 0; i < m; i++)
        prevAvailable[i] = available[i];
    for (int i = 0; i < n; i++) {
        prevSafeSeq[i] = safeSeq[i];
        for (int j = 0; j < m; j++) {
            prevAllocation[i][j] = allocation[i][j];
            prevNeed[i][j] = need[i][j];
            prevWork2D[i][j] = work2D[i][j];
        }
    }
}

void restoreState() {
    for (int i = 0; i < m; i++)
        available[i] = prevAvailable[i];
    for (int i = 0; i < n; i++) {
        safeSeq[i] = prevSafeSeq[i];
        for (int j = 0; j < m; j++) {
            allocation[i][j] = prevAllocation[i][j];
            need[i][j] = prevNeed[i][j];
            work2D[i][j] = prevWork2D[i][j];
        }
    }
}

void showPreviousSafeState() {
    printf("\nReverting to previous safe state:\n");
    restoreState();
    displayData();
}

void resourceRequestAlgorithm() {
    int process, request[MAX_R];

    printf("\nEnter process number making request (1-%d): ", n);
    scanf("%d", &process);
    process--;

    printf("Enter request vector (%d values): ", m);
    for (int i = 0; i < m; i++)
        scanf("%d", &request[i]);

    // Check 1: Request <= Need
    for (int i = 0; i < m; i++) {
        if (request[i] > need[process][i]) {
            printf("Request exceeds process maximum Need.\n");
            showPreviousSafeState();
            return;
        }
    }

    // Check 2: Request <= Available
    for (int i = 0; i < m; i++) {
        if (request[i] > available[i]) {
            printf("Not enough resources available. \n");
            showPreviousSafeState();
            return;
        }
    }

    // Backup current safe state
    backupState();

    // Pretend allocation
    for (int i = 0; i < m; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    printf("\nPretend allocation done. Checking safety...\n");

    if (safetyAlgorithm()) {
        printf(" Request can be safely granted.\n");
        displayData();
        backupState(); // update last safe state
    } else {
        printf(" Request leads to an UNSAFE state. Rolling back...\n");
        showPreviousSafeState();
    }
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("\nEnter Available resources:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &available[i]);

    printf("\nEnter Max matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("\nEnter Allocation matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);

    calculateNeed();

    printf("\nInitial System State:\n");
    if (safetyAlgorithm()) {
        printf("\n System is initially in a SAFE state.\n");
        displayData();
        backupState();
    } else {
        printf("\n Initial system state is UNSAFE. Exiting.\n");
        return 0;
    }

    char choice;
    while (1) {
        printf("\nDo you want to make a new resource request? (y/n): ");
        scanf(" %c", &choice);
        if (choice == 'y' || choice == 'Y') {
            resourceRequestAlgorithm();
        } else {
            printf("\nExiting...\n");
            break;
        }
    }

    return 0;
}
