#include <stdio.h>
#define MAX 10

struct process {
    char name[MAX];
    int at, bt, tat, wt;
};

int n;

void fcfs(struct process p[]) {
    int ct = 0, atat = 0, awt = 0;
    int end[MAX];

    // sort by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                struct process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // FCFS execution
    for (int i = 0; i < n; i++) {
        if (ct < p[i].at)
            ct = p[i].at;

        ct += p[i].bt;
        end[i] = ct;

        p[i].tat = ct - p[i].at;
        p[i].wt  = p[i].tat - p[i].bt;

        atat += p[i].tat;
        awt  += p[i].wt;
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
    }

    fcfs(p);
    return 0;
}
