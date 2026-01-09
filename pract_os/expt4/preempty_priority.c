#include <stdio.h>
#include <string.h>
#define MAX 10
#define INF 1000000000

struct process {
    char name[MAX];
    int at, bt, pr, rt, tat, wt;
};

int n, ct = 0, atat = 0, awt = 0;

void schedule(struct process p[]) {
    char gantt[MAX][MAX];
    int time[MAX], g = 0, done = 0;

    for (int i = 0; i < MAX; i++) time[i] = -1;

    while (done < n) {
        int sel = -1, best = INF;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= ct && p[i].rt > 0) {
                if (p[i].pr < best ||
                   (p[i].pr == best && p[i].at < p[sel].at)) {
                    best = p[i].pr;
                    sel = i;
                }
            }
        }

        if (sel == -1) { ct++; continue; }

        p[sel].rt--;

        if (g == 0 || strcmp(gantt[g-1], p[sel].name)) {
            strcpy(gantt[g], p[sel].name);
            time[g++] = ct + 1;
        }
        ct++;

        if (p[sel].rt == 0) {
            done++;
            p[sel].tat = ct - p[sel].at;
            p[sel].wt = p[sel].tat - p[sel].bt;
            atat += p[sel].tat;
            awt += p[sel].wt;
        }
    }

    printf("\n+------------+----------+----------+----------+----------+----------+\n");
    printf("| %-10s | %-8s | %-8s | %-8s | %-8s | %-8s |\n",
           "Process","AT","BT","PR","TAT","WT");
    printf("+------------+----------+----------+----------+----------+----------+\n");
    for (int i = 0; i < n; i++)
        printf("| %-10s | %-8d | %-8d | %-8d | %-8d | %-8d |\n",
               p[i].name, p[i].at, p[i].bt, p[i].pr, p[i].tat, p[i].wt);
    printf("+------------+----------+----------+----------+----------+----------+\n");

    printf("\nGantt Chart:\n--------------------------------------------------\n");
    for (int i = 0; i < g; i++) printf("| %-10s ", gantt[i]);
    printf("\n--------------------------------------------------\n0");
    for (int i = 0; i < g; i++) printf(" %-10d", time[i]);
    printf("\n--------------------------------------------------\n");

    printf("Average Turnaround Time: %.2f\n", (double)atat / n);
    printf("Average Waiting Time   : %.2f\n", (double)awt / n);
    printf("--------------------------------------------------\n");
}

int main() {
    printf("Enter the no of processes: ");
    scanf("%d", &n);

    struct process p[n];

    for (int i = 0; i < n; i++) {
        printf("Enter process name: ");
        scanf("%s", p[i].name);
        printf("Arrival time: ");
        scanf("%d", &p[i].at);
        printf("Burst time: ");
        scanf("%d", &p[i].bt);
        printf("Priority: ");
        scanf("%d", &p[i].pr);
        p[i].rt = p[i].bt;
    }

    schedule(p);
    return 0;
}
