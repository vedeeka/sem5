#include <stdio.h>
#define MAX 10
#include <string.h>
struct process {
    char name[MAX];
    int at, bt, tat, wt,pr,rt;
};

int n;

void fcfs(struct process p[]) {
    int ct = 0, atat = 0, awt = 0;
    int end[MAX];
int indx=0;
int min_bt;
int order[MAX];
int done=0;
    char gantt[MAX][MAX];
    int time[MAX], g = 0;
int completed[MAX]={0};
for(int i=0;i<n;i++)
{
    p[i].rt=0;
}
for(int i=0;i<n;i++)
    time[i]=-1;

while (done<n)
{



    indx=-1;
    min_bt=1e9;
    for(int j=0;j<n;j++){
        if(p[j].at<=ct && completed[j]==0){
            if(p[j].bt<min_bt){
                min_bt=p[j].bt;
                indx=j;
            }
        }

    }
        if (indx == -1) {
            ct++;
            continue;
        }

        if (g == 0 || strcmp(gantt[g-1], p[indx].name)) {
            strcpy(gantt[g], p[indx].name);
            time[g++] = ct ;
        }


if(ct < p[indx].at)
    ct = p[indx].at;

ct++;                // execute 1 unit
p[indx].rt++;        // increase executed time

if(p[indx].rt==p[indx].bt){

    p[indx].tat = ct - p[indx].at;
    p[indx].wt = p[indx].tat - p[indx].bt;
    atat += p[indx].tat;
    awt += p[indx].wt;
 
    completed[indx]=1;
    order[done]=indx;
    done++;
}
    
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
    for (int i = 0; i < g; i++)
        printf("%-8s | ", gantt[i]);
    printf("\n---------------------------------------------\n0 ");
    for (int i = 0; i < g; i++)
        printf("%-8d ", time[i]);
    printf("\n---------------------------------------------\n");

    printf("Average Turnaround Time: %.2f\n", (float)atat / n);
    printf("Average Waiting Time   : %.2f\n", (float)awt / n);
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process p[n];

    for (int i = 0; i < n; i++) {
  
        scanf("%s", p[i].name);
       
        scanf("%d", &p[i].at);

        scanf("%d", &p[i].bt);

  
    }

    fcfs(p);
    return 0;
}
