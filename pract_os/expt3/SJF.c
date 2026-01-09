#include <stdio.h>
#define MAX 10

struct process {
    char name[MAX];
    int at, bt, tat, wt;
};

int n;

void sjf(struct process p[]) {
    int ct = 0, done = 0, atat = 0, awt = 0;
    int completed[MAX] = {0};
    int end[MAX], order[MAX];

    while (done < n) {
        int idx = -1, min_bt = 1e9;

        // pick shortest job available
        for (int i = 0; i < n; i++) {
            if (!completed[i] && p[i].at <= ct && p[i].bt < min_bt) {
                min_bt = p[i].bt;
                idx = i;
            }
        }

        if (idx == -1) {
            ct++;
            continue;
        }

        ct += p[idx].bt;
        end[done] = ct;
        order[done] = idx;

        p[idx].tat = ct - p[idx].at;
        p[idx].wt  = p[idx].tat - p[idx].bt;

        atat += p[idx].tat;
        awt  += p[idx].wt;

        completed[idx] = 1;
        done++;
    }

    // table
    printf("\n+------------+----------+----------+----------+----------+\n");
    printf("| %-10s | %-8s | %-8s | %-8s | %-8s |\n",
           "Process","AT","BT","TAT","WT");
    printf("+------------+----------+----------+----------+----------+\n");
    for (int i = 0; i < n; i++)
        printf("| %-10s | %-8d | %-8d | %-8d | %-8d |\n",
               p[i].name, p[i].at, p[i].bt, p[i].tat, p[i].wt);
    printf("+------------+----------+----------+----------+----------+\n");

    // Gantt chart
    printf("\nGantt Chart:\n---------------------------------------------\n| ");
    for (int i = 0; i < n; i++)
        printf("%-8s | ", p[order[i]].name);
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
    }

    sjf(p);
    return 0;
}
