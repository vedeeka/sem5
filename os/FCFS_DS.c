#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, total = 0;
    printf("Enter number of requests: ");
    scanf("%d", &n);

    int req[n], seq[n + 1];
    printf("Enter request sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("\n--- FCFS Disk Scheduling ---\n");
    printf("\n%-10s %-10s %-10s\n", "From", "To", "Movement");
    printf("-----------------------------------\n");

    int current = head;
    seq[0] = head;

    for (int i = 0; i < n; i++) {
        int move = abs(current - req[i]);
        printf("%-10d %-10d %-10d\n", current, req[i], move);
        total += move;
        current = req[i];
        seq[i + 1] = current;
    }

    printf("\nSeek Sequence: ");
    for (int i = 0; i <= n; i++)
        printf("%d ", seq[i]);

    printf("\nTotal Head Movement = %d\n", total);
    return 0;
}
