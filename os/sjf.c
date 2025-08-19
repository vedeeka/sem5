#include<stdio.h>
#include<string.h>
#define MAX 10


struct process{
char proc_name[MAX];
int bt, at, tat, wt;


};
int atat=0;
int awt=0;
int n;
int ct;


int ind[MAX];
void sjf(struct process pro[]) {
    int completed = 0, visited[MAX] = {0};
    ct = 0;
    atat = 0;
    awt = 0;

    printf("\n");
    printf("%-10s %-10s %-10s %-10s %-10s","Process","AT","BT","TAT","WT");
    printf("\n");

    while (completed < n) {
        int idx = -1;
        int min_bt = 1e9;

        
        for (int i = 0; i < n; i++) {
            if (!visited[i] && pro[i].at <= ct) {
                if (pro[i].bt < min_bt) {
                    min_bt = pro[i].bt;
                    idx = i;
                }
            }
        }

       
        if (idx == -1) {
            ct++;
            continue;
        }

      
        ct += pro[idx].bt;
        pro[idx].tat = ct - pro[idx].at;
        pro[idx].wt = pro[idx].tat - pro[idx].bt;
        atat += pro[idx].tat;
        awt += pro[idx].wt;
        visited[idx] = 1;
        completed++;

        printf(" %-10s %-10d %-10d %-10d %-10d\n",
               pro[idx].proc_name, pro[idx].at, pro[idx].bt, pro[idx].tat, pro[idx].wt);
    }

    atat /= n;
    awt /= n;

    printf("\n--------------------------------------------------\n");
    printf("Average Turn Around Time is %d\n", atat);
    printf("Average Waiting Time is %d\n", awt);
    printf("--------------------------------------------------\n");
}








int main(){


printf("Enter the no of processes :");
scanf("%d",&n);


struct process pro[n];


for(int i=0;i<n;i++){
printf("Enter the name of process :");
scanf("%s",&pro[i].proc_name);


printf("Enter the arrival time of process :");
scanf("%d",&pro[i].at);




printf("Enter the Burst time of process :");
scanf("%d",&pro[i].bt);


pro[i].tat=0;
pro[i].wt=0;


}


sjf(pro);
}


