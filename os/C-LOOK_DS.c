#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                int t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
}

int main() {
    int n, head, prev, total = 0, dir;
    printf("Enter number of requests: ");
    scanf("%d", &n);

    int req[n], seq[n + 1], fwdSeq[n], wrapSeq[n];
    int fwdCount = 0, wrapCount = 0, idx = 1;

    printf("Enter request sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter previous head position: ");
    scanf("%d", &prev);

    // Decide direction automatically
    if (prev < head)
        dir = 1; // moving right
    else
        dir = 0; // moving left

    sort(req, n);

    printf("\n--- C-LOOK Disk Scheduling ---\n");
    printf("Initial Head: %d, Previous Head: %d, Direction: %s\n\n",
           head, prev, dir ? "Right" : "Left");

    printf("%-10s %-10s %-10s\n", "From", "To", "Movement");
    printf("-----------------------------------\n");

    int current = head;
    seq[0] = head;

    // find position of the first request greater than head
    int pos;
    for (pos = 0; pos < n; pos++)
        if (head < req[pos])
            break;

    if (dir == 1) { // moving right first
        // move to the end (right side)
        for (int i = pos; i < n; i++) {
            int move = abs(current - req[i]);
            printf("%-10d %-10d %-10d\n", current, req[i], move);
            total += move;
            current = req[i];
            seq[idx++] = current;
            fwdSeq[fwdCount++] = current;
        }

        // jump to the first request (circular)
        printf("\n>>> Jumping from %d to %d (no movement counted) <<<\n\n",
               current, req[0]);
        current = req[0];

        // continue from beginning to the position before head
        for (int i = 0; i < pos; i++) {
            int move = abs(current - req[i]);
            printf("%-10d %-10d %-10d\n", current, req[i], move);
            total += move;
            current = req[i];
            seq[idx++] = current;
            wrapSeq[wrapCount++] = current;
        }

    } else { // moving left first
        // move to the left end
        for (int i = pos - 1; i >= 0; i--) {
            int move = abs(current - req[i]);
            printf("%-10d %-10d %-10d\n", current, req[i], move);
            total += move;
            current = req[i];
            seq[idx++] = current;
            fwdSeq[fwdCount++] = current;
        }

        // jump to last request (circular)
        printf("\n>>> Jumping from %d to %d (no movement counted) <<<\n\n",
               current, req[n - 1]);
        current = req[n - 1];

        // move from end back toward head position
        for (int i = n - 1; i >= pos; i--) {
            int move = abs(current - req[i]);
            printf("%-10d %-10d %-10d\n", current, req[i], move);
            total += move;
            current = req[i];
            seq[idx++] = current;
            wrapSeq[wrapCount++] = current;
        }
    }

    // Print results
    printf("\nSeek Sequence: ");
    for (int i = 0; i < idx; i++)
        printf("%d ", seq[i]);

    printf("\nForward Sequence (before jump): ");
    for (int i = 0; i < fwdCount; i++)
        printf("%d ", fwdSeq[i]);

    printf("\nWrapped Sequence (after jump): ");
    for (int i = 0; i < wrapCount; i++)
        printf("%d ", wrapSeq[i]);

    printf("\n\nTotal Head Movement = %d\n", total);
    return 0;
}
