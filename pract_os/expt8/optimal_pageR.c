#include <stdio.h>

int main() {
    int pages[50], frames[10], future[10];
    int n, f, i, j, k, pos, faults = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string: ");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for (i = 0; i < f; i++)
        frames[i] = -1;

    for (i = 0; i < n; i++) {
        int hit = 0;

        // Check page hit
        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                hit = 1;
                break;
            }
        }

        if (!hit) {
            pos = -1;

            // Check for empty frame
            for (j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // If no empty frame, apply Optimal logic
            if (pos == -1) {
                for (j = 0; j < f; j++) {
                    future[j] = n;
                    for (k = i + 1; k < n; k++) {
                        if (frames[j] == pages[k]) {
                            future[j] = k;
                            break;
                        }
                    }
                }

                pos = 0;
                for (j = 1; j < f; j++)
                    if (future[j] > future[pos])
                        pos = j;
            }

            frames[pos] = pages[i];
            faults++;
        }

        printf("\n");
        for (j = 0; j < f; j++)
            printf("%d ", frames[j]);
    }

    printf("\n\nTotal Page Faults = %d\n", faults);
    return 0;
}
