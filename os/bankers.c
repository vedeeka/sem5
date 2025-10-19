#include <stdio.h>
#include <stdbool.h>

#define MAX_P 10
#define MAX_R 10

int n, m;
int available[MAX_R];
int max[MAX_P][MAX_R];
int allocation[MAX_P][MAX_R];
int need[MAX_P][MAX_R];
int work2D[MAX_P][MAX_R]; // stores available after each process finishes
int safeSeq[MAX_P];        // stores the safe sequence

void calculateNeed() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
            if (need[i][j] < 0) need[i][j] = 0;
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

    printf("\nProcess finishing sequence and available updates:\n");

    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < m; j++)
                    if (need[i][j] > work[j])
                        break;

                if (j == m) { // process i can finish
                    for (int k = 0; k < m; k++)
                        work[k] += allocation[i][k];

                    finish[i] = true;
                    safeSeq[count] = i;

                    for (int k = 0; k < m; k++)
                        work2D[count][k] = work[k]; // store available after finishing

                    printf("Process P%d finished. Available: ", i + 1);
                    for (int k = 0; k < m; k++)
                        printf("%d ", work[k]);
                    printf("\n");

                    count++;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("\n❌ System is in an UNSAFE state.\n");
            return false;
        }
    }

    printf("\n✅ System is in a SAFE state.\nSafe Sequence: ");
    for (int i = 0; i < n; i++)
        printf("P%d ", safeSeq[i] + 1);
    printf("\n");

    return true;
}

void resourceRequestAlgorithm() {
    int process;
    int request[MAX_R];

    printf("\nEnter process number making request (1-%d): ", n);
    scanf("%d", &process);
    process--;

    printf("Enter request vector (%d values): ", m);
    for (int i = 0; i < m; i++)
        scanf("%d", &request[i]);

    for (int i = 0; i < m; i++) {
        if (request[i] > need[process][i]) {
            printf("❌ Error: Request exceeds maximum claim.\n");
            return;
        }
        if (request[i] > available[i]) {
            printf("⚠️ Not enough resources available. Process must wait.\n");
            return;
        }
    }

    // pretend allocation
    for (int i = 0; i < m; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    printf("\nPretend allocation done. Checking safety...\n");
    if (safetyAlgorithm()) {
        printf("✅ Request can be safely granted.\n");
    } else {
        printf("❌ Request leads to unsafe state. Rolling back.\n");
        for (int i = 0; i < m; i++) {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
    }
}

void displayData() {
    printf("\n-------------------------------------------------------------\n");
    printf("Process | Allocation\t | Max\t\t | Need\t\t | Available\n");
    printf("-------------------------------------------------------------\n");

    // display in the order of safe sequence
    for (int i = 0; i < n; i++) {
        int p = safeSeq[i]; // process index in safe sequence
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
            printf("%d ", work2D[i][j]); // available after process finishes
        printf("\n");
    }
    printf("-------------------------------------------------------------\n");
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
    safetyAlgorithm(); // calculate safe sequence
    displayData();     // display table in safe sequence order

    char choice;
    printf("\nDo you want to make a resource request? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        resourceRequestAlgorithm();
        displayData();
    }

    return 0;
}
