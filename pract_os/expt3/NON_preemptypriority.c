#include <stdio.h>
#include <string.h>
#define MAX 10

struct process {
    char name[MAX];
    int at, bt, pr, tat, wt, done;
};

int n, ct = 0;
int atat = 0, awt = 0;

void priority_np(struct process p[]) {
    int completed = 0;
    int end[MAX];

    while (completed < n) {
        int idx = -1, best_pr = 1e9;

        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= ct) {
                if (p[i].pr < best_pr) {
                    best_pr = p[i].pr;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            ct++;
            continue;
        }

        ct += p[idx].bt;
        end[completed] = ct;

        p[idx].tat = ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;

        atat += p[idx].tat;
        awt += p[idx].wt;

        p[idx].done = 1;
        completed++;
    }

    printf("\n+------------+----------+----------+----------+----------+\n");
    printf("| %-10s | %-8s | %-8s | %-8s | %-8s |\n",
           "Process","AT","BT","TAT","WT");
    printf("+------------+----------+----------+----------+----------+\n");
    for (int i = 0; i < n; i++)
        printf("| %-10s | %-8d | %-8d | %-8d | %-8d |\n",
               p[i].name, p[i].at, p[i].bt, p[i].tat, p[i].wt);
    printf("+------------+----------+----------+----------+----------+\n");

    printf("\nGantt Chart:\n---------------------------------------------\n| ");
    for (int i = 0; i < n; i++)
        printf("%-8s | ", p[i].name);
    printf("\n---------------------------------------------\n0 ");
    for (int i = 0; i < n; i++)
        printf("%-8d ", end[i]);
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
        printf("Priority: ");
        scanf("%d", &p[i].pr);

        p[i].done = 0;
    }

    priority_np(p);
    return 0;
}
