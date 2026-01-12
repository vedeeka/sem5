#include <stdio.h>
#include <stdbool.h>

#define MAX_P 10
#define MAX_R 10

void printMatrix(int a[MAX_P][MAX_R], int n, int m, const char *name) {
    printf("\n%s matrix:\n       ", name);
    for (int j = 0; j < m; j++) printf("R%d   ", j);
    printf("\n-----------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("P%-2d | ", i);
        for (int j = 0; j < m; j++) printf("%-4d ", a[i][j]);
        printf("\n");
    }
}

void printAvailable(int a[MAX_R], int m) {
    printf("\nAvailable resources:\n");
    for (int j = 0; j < m; j++) printf("R%d: %d  ", j, a[j]);
    printf("\n");
}

bool safetyAlgo(int alloc[MAX_P][MAX_R], int need[MAX_P][MAX_R], int avail[MAX_R], int n, int m) {
    int work[MAX_R], seq[MAX_P], c = 0;
    bool finish[MAX_P] = {0};

    for (int j = 0; j < m; j++) work[j] = avail[j];

    while (c < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int j;
               for (j = 0; j < m; j++) {
    if (need[i][j] > work[j])
        break;
}

                if (j == m) {
                    for (int k = 0; k < m; k++) work[k] += alloc[i][k];
                    finish[i] = true;
                    seq[c++] = i;
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
    for (int i = 0; i < n; i++) printf("P%d ", seq[i]);
    printf("\n");
    return true;
}

void requestResources(int alloc[MAX_P][MAX_R], int need[MAX_P][MAX_R], int avail[MAX_R], int n, int m) {
    char ch;
    while (1) {
        printf("\nDo you want to make an immediate request? (y/n): ");
        scanf(" %c", &ch);
        if (ch != 'y' && ch != 'Y') return;

        int p, req[MAX_R];
        printf("Enter process number (0-%d): ", n - 1);
        scanf("%d", &p);

        printf("Enter request for each resource type: ");
        for (int j = 0; j < m; j++) scanf("%d", &req[j]);

        for (int j = 0; j < m; j++)
            if (req[j] > need[p][j] || req[j] > avail[j]) {
                printf("⚠️  Request cannot be granted. Process must wait.\n");
                printMatrix(alloc, n, m, "Allocation");
                printMatrix(need, n, m, "Need");
                printAvailable(avail, m);
                goto next;
            }

        int oldA[MAX_R], oldAlloc[MAX_P][MAX_R], oldNeed[MAX_P][MAX_R];
        for (int j = 0; j < m; j++) oldA[j] = avail[j];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                oldAlloc[i][j] = alloc[i][j], oldNeed[i][j] = need[i][j];

        for (int j = 0; j < m; j++)
            avail[j] -= req[j], alloc[p][j] += req[j], need[p][j] -= req[j];

        if (!safetyAlgo(alloc, need, avail, n, m)) {
            printf("❌ Request cannot be granted (unsafe state).\n");
            for (int j = 0; j < m; j++) avail[j] = oldA[j];
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    alloc[i][j] = oldAlloc[i][j], need[i][j] = oldNeed[i][j];
        } else
            printf("✅ Request granted.\n");

        printMatrix(alloc, n, m, "Allocation");
        printMatrix(need, n, m, "Need");
        printAvailable(avail, m);
    next:;
    }
}

int main() {
    int n, m, alloc[MAX_P][MAX_R], max[MAX_P][MAX_R];
    int need[MAX_P][MAX_R], avail[MAX_R];

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("\nEnter Allocation matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("\nEnter Max matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("\nEnter Available resources:\n");
    for (int j = 0; j < m; j++) scanf("%d", &avail[j]);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    printMatrix(alloc, n, m, "Allocation");
    printMatrix(max, n, m, "Max");
    printMatrix(need, n, m, "Need");
    printAvailable(avail, m);

    printf("\nInitial safety check:\n");
    safetyAlgo(alloc, need, avail, n, m);

    requestResources(alloc, need, avail, n, m);
    return 0;
}
