#include <stdio.h>
#include <string.h>
#define MAX 10

struct process {
    char proc_name[MAX];
    int bt, at, tat, wt;
    int pr;
    int remaining_bt;
};

int atat = 0;
int awt = 0;
int n;
int ct;
int ind[MAX];

void sortprocess(struct process pro[]) {
    ct = 0;
    for (int i = 0; i < n; i++) {
        ind[i] = i;
    }

    // just to keep execution order
    int arr[MAX];
    for (int i = 0; i < MAX; i++) arr[i] = -1;
    char name_arr[MAX][MAX];
    for (int i = 0; i < MAX; i++) name_arr[i][0] = '\0';

    // initial sort by arrival (for stable handling)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (pro[ind[j]].at > pro[ind[j + 1]].at) {
                int t = ind[j];
                ind[j] = ind[j + 1];
                ind[j + 1] = t;
            }
        }
    }

    int k = 0;
    int completed = 0;

    while (completed < n) {
        int selected = -1;
        int best_pr = 1e9; // lower = higher priority

        // choose process with highest priority available
        for (int i = 0; i < n; i++) {
            if (pro[ind[i]].at <= ct && pro[ind[i]].remaining_bt > 0) {
                if (pro[ind[i]].pr < best_pr) {
                    best_pr = pro[ind[i]].pr;
                    selected = ind[i];
                }
                // tie break by arrival time
                else if (pro[ind[i]].pr == best_pr) {
                    if (pro[ind[i]].at < pro[selected].at) {
                        selected = ind[i];
                    }
                }
            }
        }

        if (selected == -1) {
            ct++;
            continue;
        }

        // run selected process for 1 unit
        pro[selected].remaining_bt--;

        if (k == 0 || strcmp(name_arr[k - 1], pro[selected].proc_name) != 0) {
            strcpy(name_arr[k], pro[selected].proc_name);
            k++;
        }

        arr[k] = ct + 1;
        ct++;

        if (pro[selected].remaining_bt == 0) {
            completed++;
            pro[selected].tat = ct - pro[selected].at;
            pro[selected].wt = pro[selected].tat - pro[selected].bt;
            atat += pro[selected].tat;
            awt += pro[selected].wt;
        }
    }

    atat = atat / n;
    awt = awt / n;

    printf("\n");
    printf("+------------+----------+----------+----------+----------+----------+\n");
    printf("| %-10s | %-8s | %-8s | %-8s | %-8s | %-8s |\n",
           "Process", "AT", "BT", "PR", "TAT", "WT");
    printf("+------------+----------+----------+----------+----------+----------+\n");
    for (int i = 0; i < n; i++) {
        printf("| %-10s | %-8d | %-8d | %-8d | %-8d | %-8d |\n",
               pro[i].proc_name, pro[i].at, pro[i].bt, pro[i].pr,
               pro[i].tat, pro[i].wt);
    }
    printf("+------------+----------+----------+----------+----------+----------+\n\n");

    // Gantt Chart
    printf("Gantt Chart :\n");
    printf("--------------------------------------------------\n");
    int u = 0;
    while (name_arr[u][0] != '\0') {
        printf("| %-10s ", name_arr[u]);
        u++;
    }
    printf("\n");
    printf("--------------------------------------------------\n");
    printf("0");
    int h = 1;
    while (arr[h] != -1 && h < MAX) {
        printf(" %-10d", arr[h]);
        h++;
    }
    printf("\n");
    printf("--------------------------------------------------\n");

    double avg_tat = (double)atat;
    double avg_wt = (double)awt;
    printf("Average Turnaround Time: %.2f\n", avg_tat);
    printf("Average Waiting Time   : %.2f\n", avg_wt);
    printf("--------------------------------------------------\n");
}

int main() {
    printf("Enter the no of processes : ");
    scanf("%d", &n);

    struct process pro[n];

    for (int i = 0; i < n; i++) {
        printf("Enter the name of process: ");
        scanf("%s", pro[i].proc_name);

        printf("Enter the arrival time of process : ");
        scanf("%d", &pro[i].at);

        printf("Enter the burst time of process : ");
        scanf("%d", &pro[i].bt);

        printf("Enter the priority of process : ");
        scanf("%d", &pro[i].pr);

        pro[i].tat = 0;
        pro[i].remaining_bt = pro[i].bt;
        pro[i].wt = 0;
    }

    sortprocess(pro);
    return 0;
}
