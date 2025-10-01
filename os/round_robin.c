#include <stdio.h>
#include <string.h>
#define MAX 10

struct process {
    char proc_name[MAX];
    int bt, at, tat, wt, rbt;
};

int n;
int tq; 

void roundRobin(struct process pro[]) {
    int time = 0, completed = 0;
    int atat = 0, awt = 0;

   
    for (int i = 0; i < n; i++) {
        pro[i].rbt = pro[i].bt;
    }

    printf("\nGantt Chart :\n");
    printf("--------------------------------------------------\n");

  
    int ct[n];

    while (completed < n) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (pro[i].rbt > 0 && pro[i].at <= time) {
                done = 0;
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
            }
        }
       
        if (done) {
            time++;
        }
    }

    printf("|\n");
    printf("--------------------------------------------------\n\n");

    printf("+------------+----------+----------+----------+----------+\n");
    printf("| %-10s | %-8s | %-8s | %-8s | %-8s |\n", "Process", "AT", "BT", "TAT", "WT");
    printf("+------------+----------+----------+----------+----------+\n");
    for (int i = 0; i < n; i++) {
        printf("| %-10s | %-8d | %-8d | %-8d | %-8d |\n",
               pro[i].proc_name, pro[i].at, pro[i].bt, pro[i].tat, pro[i].wt);
    }
    printf("+------------+----------+----------+----------+----------+\n");

    double avg_tat = (double)atat / n;
    double avg_wt = (double)awt / n;
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);
    printf("Average Waiting Time   : %.2f\n", avg_wt);
    printf("--------------------------------------------------\n");
}

int main() {
    printf("Enter the no of processes: ");
    scanf("%d", &n);

    struct process pro[n];

    for (int i = 0; i < n; i++) {
        printf("Enter the name of process: ");
        scanf("%s", pro[i].proc_name);

        printf("Enter the arrival time of process: ");
        scanf("%d", &pro[i].at);

        printf("Enter the burst time of process: ");
        scanf("%d", &pro[i].bt);

        pro[i].tat = 0;
        pro[i].wt = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    roundRobin(pro);
}
