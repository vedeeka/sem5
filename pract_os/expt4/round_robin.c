#include <stdio.h>
#include <string.h>
#define MAX 10

struct process {
    char proc_name[MAX];
    int bt, at, tat, wt, rbt;
};

int n, tq;

void roundRobin(struct process pro[]) {
    int time = 0, completed = 0;
    int atat = 0, awt = 0;
    int queue[100], front = 0, rear = 0;
    int visited[n];
    int order[100], times[101];
    int k = 0;

    for (int i = 0; i < n; i++) {
        pro[i].rbt = pro[i].bt;
        visited[i] = 0;
    }

    // Find first process (with min arrival time)
    int first = 0;
    for (int i = 1; i < n; i++)
        if (pro[i].at < pro[first].at)
            first = i;

    time = pro[first].at;
    queue[rear++] = first;
    visited[first] = 1;
    times[k] = time;

    printf("\nGantt Chart:\n");
    printf("--------------------------------------------------\n");

    while (front < rear) {
        int i = queue[front++];
        printf("| %-10s ", pro[i].proc_name);

        if (pro[i].rbt > tq) {
            time += tq;
            pro[i].rbt -= tq;
        } else {
            time += pro[i].rbt;
            pro[i].tat = time - pro[i].at;
            pro[i].wt = pro[i].tat - pro[i].bt;
            atat += pro[i].tat;
            awt += pro[i].wt;
            pro[i].rbt = 0;
            completed++;
        }

        times[++k] = time;

        // Add newly arrived processes
        for (int j = 0; j < n; j++) {
            if (!visited[j] && pro[j].at <= time && pro[j].rbt > 0) {
                queue[rear++] = j;
                visited[j] = 1;
            }
        }

        // Re-add current process if not finished
        if (pro[i].rbt > 0)
            queue[rear++] = i;
    }

    printf("|\n");
    printf("--------------------------------------------------\n");

    // Print time line
    for (int i = 0; i <= k; i++)
        printf("%-12d", times[i]);
    printf("\n--------------------------------------------------\n\n");

    // Table output
    printf("+------------+----------+----------+----------+----------+\n");
    printf("| %-10s | %-8s | %-8s | %-8s | %-8s |\n", "Process", "AT", "BT", "TAT", "WT");
    printf("+------------+----------+----------+----------+----------+\n");

    for (int i = 0; i < n; i++)
        printf("| %-10s | %-8d | %-8d | %-8d | %-8d |\n",
               pro[i].proc_name, pro[i].at, pro[i].bt, pro[i].tat, pro[i].wt);

    printf("+------------+----------+----------+----------+----------+\n");

    double avg_tat = (double)atat / n;
    double avg_wt = (double)awt / n;
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);
    printf("Average Waiting Time   : %.2f\n", avg_wt);
    printf("--------------------------------------------------\n");
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process pro[n];

    for (int i = 0; i < n; i++) {
        printf("Enter the name of process: ");
        scanf("%s", pro[i].proc_name);
        printf("Enter the arrival time of process: ");
        scanf("%d", &pro[i].at);
        printf("Enter the burst time of process: ");
        scanf("%d", &pro[i].bt);
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    roundRobin(pro);
}
