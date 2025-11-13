#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, total = 0;
    printf("Enter number of requests: ");
    scanf("%d", &n);

    int req[n], done[n], seq[n + 1];
    printf("Enter request sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &req[i]);
        done[i] = 0;
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("\n--- SSTF Disk Scheduling ---\n");
    printf("\n%-10s %-10s %-10s\n", "From", "To", "Movement");
    printf("-----------------------------------\n");

    int current = head;
    seq[0] = head;

    for (int count = 0; count < n; count++) {
        int min = 9999, index = -1;
        for (int i = 0; i < n; i++) {
            if (!done[i]) {
                int dist = abs(current - req[i]);
                if (dist < min) {
                    min = dist;
                    index = i;
                }
            }
        }

        printf("%-10d %-10d %-10d\n", current, req[index], min);
        total += min;
        current = req[index];
        done[index] = 1;
        seq[count + 1] = current;
    }

    printf("\nSeek Sequence: ");
    for (int i = 0; i <= n; i++)
        printf("%d ", seq[i]);

    printf("\nTotal Head Movement = %d\n", total);
    return 0;
}
