#include <stdio.h>
#include <stdbool.h>

#define MAX_P 10
#define MAX_R 10

// Function to print a matrix
void printMatrix(int mat[MAX_P][MAX_R], int n, int m, const char* name) {
    printf("\n%s matrix:\n", name);
    printf("       ");
    for (int j = 0; j < m; j++)
        printf("R%d   ", j);
    printf("\n-----------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("P%-2d | ", i);
        for (int j = 0; j < m; j++)
            printf("%-4d ", mat[i][j]);
        printf("\n");
    }
}

// Function to print available resources
void printAvailable(int avail[MAX_R], int m) {
    printf("\nAvailable resources:\n");
    for (int j = 0; j < m; j++)
        printf("R%d: %d  ", j, avail[j]);
    printf("\n");
}

// Safety algorithm
bool safetyAlgo(int alloc[MAX_P][MAX_R], int need[MAX_P][MAX_R], int avail[MAX_R], int n, int m) {
    int work[MAX_R];
    bool finish[MAX_P] = {false};
    int safeSeq[MAX_P];
    int count = 0;

    for (int i = 0; i < m; i++)
        work[i] = avail[i];

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
                        work[k] += alloc[i][k];
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            printf("\n⚠️  System is NOT in a safe state.\n");
            return false;
        }
    }

    printf("\n✅ System is in a SAFE state.\nSafe sequence: ");
    for (int i = 0; i < n; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");
    return true;
}

// Function to handle resource requests
void requestResources(int alloc[MAX_P][MAX_R], int max[MAX_P][MAX_R],
                      int need[MAX_P][MAX_R], int avail[MAX_R], int n, int m) {
    char choice;
    while (1) {
        printf("\nDo you want to make an immediate request? (y/n): ");
        scanf(" %c", &choice);
        if (choice != 'y' && choice != 'Y')
            break;

        int p;
        printf("Enter process number (0-%d): ", n - 1);
        scanf("%d", &p);
        if (p < 0 || p >= n) {
            printf("❌ Invalid process number.\n");
            continue;
        }

        int req[MAX_R];
        printf("Enter request for each resource type: ");
        for (int j = 0; j < m; j++)
            scanf("%d", &req[j]);

        // Check request ≤ need
        bool valid = true;
        for (int j = 0; j < m; j++) {
            if (req[j] > need[p][j]) {
                printf("⚠️  Process P%d is asking for more than its declared maximum need.\n", p);
                printf("Process must wait -- resources are busy.\n");
                valid = false;
                break;
            }
        }
        if (!valid) {
            printMatrix(alloc, n, m, "Allocation");
            printMatrix(need, n, m, "Need");
            printAvailable(avail, m);
            continue;
        }

        // Check request ≤ available
        for (int j = 0; j < m; j++) {
            if (req[j] > avail[j]) {
                printf("\n⚠️  Resources not available right now.\n");
                printf("Process P%d must wait.\n", p);
                valid = false;
                break;
            }
        }
        if (!valid) {
            printMatrix(alloc, n, m, "Allocation");
            printMatrix(need, n, m, "Need");
            printAvailable(avail, m);
            continue;
        }

        // Check if all available will become zero
        bool allAvailableZero = true;
        for (int j = 0; j < m; j++) {
            if (avail[j] - req[j] != 0)
                allAvailableZero = false;
        }
        if (allAvailableZero) {
            printf("\n⚠️  Request violates Banker's algorithm!\n");
            printf("Process must wait -- resources are busy.\n");
            printMatrix(alloc, n, m, "Allocation");
            printMatrix(need, n, m, "Need");
            printAvailable(avail, m);
            continue;
        }

        // Save old state
        int oldAvail[MAX_R];
        int oldAlloc[MAX_P][MAX_R];
        int oldNeed[MAX_P][MAX_R];

        for (int j = 0; j < m; j++)
            oldAvail[j] = avail[j];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                oldAlloc[i][j] = alloc[i][j];
                oldNeed[i][j] = need[i][j];
            }

        // Pretend to allocate
        for (int j = 0; j < m; j++) {
            avail[j] -= req[j];
            alloc[p][j] += req[j];
            need[p][j] -= req[j];
        }

        // Check safety
        if (safetyAlgo(alloc, need, avail, n, m))
            printf("✅ Request granted.\n");
        else {
            printf("❌ Request cannot be granted (unsafe state).\n");
            for (int j = 0; j < m; j++)
                avail[j] = oldAvail[j];
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++) {
                    alloc[i][j] = oldAlloc[i][j];
                    need[i][j] = oldNeed[i][j];
                }
        }

        // Display updated matrices
        printMatrix(alloc, n, m, "Allocation");
        printMatrix(need, n, m, "Need");
        printAvailable(avail, m);
    }
}

int main() {
    int n, m;
    int alloc[MAX_P][MAX_R], max[MAX_P][MAX_R], need[MAX_P][MAX_R], avail[MAX_R];

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("\nEnter Allocation matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("\nEnter Max matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("\nEnter Available resources (%d values):\n", m);
    for (int j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    // Compute Need matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Display matrices
    printMatrix(alloc, n, m, "Allocation");
    printMatrix(max, n, m, "Max");
    printMatrix(need, n, m, "Need");
    printAvailable(avail, m);

    // Initial safety check
    printf("\nInitial safety check:\n");
    safetyAlgo(alloc, need, avail, n, m);

    // Handle requests
    requestResources(alloc, max, need, avail, n, m);

    return 0;
}
