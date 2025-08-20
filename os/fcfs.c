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
void sortprocess(struct process pro[]){
ct=0;
for(int i=0;i<n;i++){
    ind[i]=i;
}

int arr[n];
for(int i=0;i<n;i++){
for(int j=0;j<n-1;j++){
if(pro[ind[j]].at > pro[ind[j+1]].at  ){
int t=ind[j];
ind[j]=ind[j+1];
ind[j+1]=t;
}
}

}






for(int i=0;i<n;i++){


if(ct < pro[ind[i]].at) {
   ct = pro[ind[i]].at;

}

ct += pro[ind[i]].bt;
arr[i]=ct;

pro[ind[i]].tat=ct-pro[ind[i]].at;
atat+=pro[ind[i]].tat;
}


for(int i=0;i<n;i++){
pro[ind[i]].wt=pro[ind[i]].tat-pro[ind[i]].bt;
awt+=pro[ind[i]].wt;
}


atat=atat/n;
awt=awt/n;
printf("\n");
printf("%-10s %-10s %-10s %-10s %-10s","Process","AT","BT","TAT","WT");
printf("\n");
for(int i=0;i<n;i++){
   printf(" %-10s %-10d %-10d %-10d %-10d",pro[i].proc_name, pro[i].at, pro[i].bt, pro[i].tat, pro[i].wt);
   printf("\n");
}
printf("\n");
printf("--------------------------------------------------\n");
for(int i=0;i<n;i++){
   printf("| %-10s |",pro[ind[i]].proc_name);
}
printf("\n");
printf("--------------------------------------------------\n");


for(int i=0;i<n;i++){
   printf("  %-10d  ",arr[i]);
}


printf("\n");
printf("--------------------------------------------------\n");
printf("Average Turn Around Time is %d\n",atat);
printf("Average Waiting Time is %d\n",awt);
printf("--------------------------------------------------\n");



}


int main(){

printf("Enter the no of processes");
scanf("%d",&n);

struct process pro[n];

for(int i=0;i<n;i++){
printf("Enter the name of process");
scanf("%s",&pro[i].proc_name);

printf("Enter the arrival time of process");
scanf("%d",&pro[i].at);

printf("Enter the burst time of process");
scanf("%d",&pro[i].bt);

pro[i].tat=0;

pro[i].wt=0;
}

sortprocess(pro);
}

