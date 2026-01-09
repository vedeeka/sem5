#include <stdio.h>
#include <string.h>
#define MAX 10
#define INF 1000000000

struct process {
    char name[MAX];
    int at, bt, rt, tat, wt;
};

int n, ct = 0;
int atat = 0, awt = 0;

void srtf(struct process p[]) {
    int completed = 0, k = 0;
    char gantt[MAX][MAX];
    int time[MAX];

    for (int i = 0; i < MAX; i++) time[i] = -1;

    while (completed < n) {
        int idx = -1, min = INF;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= ct && p[i].rt > 0 && p[i].rt < min) {
                min = p[i].rt;
                idx = i;
            }
        }

        if (idx == -1) {
            ct++;
            continue;
        }

        p[idx].rt--;

        if (k == 0 || strcmp(gantt[k-1], p[idx].name) != 0) {
            strcpy(gantt[k], p[idx].name);
            time[k++] = ct + 1;
        } else {
            time[k-1] = ct + 1;
        }

        ct++;

        if (p[idx].rt == 0) {
            completed++;
            p[idx].tat = ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            atat += p[idx].tat;
            awt += p[idx].wt;
        }
    }

    printf("\n+------------+----------+----------+----------+----------+\n");
    printf("| %-10s | %-8s | %-8s | %-8s | %-8s |\n","Process","AT","BT","TAT","WT");
    printf("+------------+----------+----------+----------+----------+\n");
    for (int i = 0; i < n; i++)
        printf("| %-10s | %-8d | %-8d | %-8d | %-8d |\n",
               p[i].name, p[i].at, p[i].bt, p[i].tat, p[i].wt);
    printf("+------------+----------+----------+----------+----------+\n");

    printf("\nGantt Chart:\n---------------------------------------------\n| ");
    for (int i = 0; i < k; i++) printf("%-8s | ", gantt[i]);
    printf("\n---------------------------------------------\n0 ");
    for (int i = 0; i < k; i++) printf("%-8d ", time[i]);
    printf("\n---------------------------------------------\n");

    printf("Average Turnaround Time: %.2f\n", (float)atat / n);
    printf("Average Waiting Time   : %.2f\n", (float)awt / n);
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process p[n];

    for (int i = 0; i < n; i++) {
        printf("Process name: ");
        scanf("%s", p[i].name);
        printf("Arrival time: ");
        scanf("%d", &p[i].at);
        printf("Burst time: ");
        scanf("%d", &p[i].bt);

        p[i].rt = p[i].bt;
    }

    srtf(p);
    return 0;
}
