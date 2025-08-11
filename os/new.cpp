#include<stdio.h>
int n=4;
int main() {
for(int i=0; i<n; i++) {
for(int j=0;j<i+1;j++){
    printf("*");
}

for(int j=0;j<n-i-1;j++){
    printf(" ");
}
for(int j=0;j<n-i-1;j++){
    printf(" ");
}
for(int j=0;j<i+1;j++){
    printf("*");
}
printf("\n");
}

 for(int i=n; i>0; i--) {
for(int j=0;j<i;j++){
    printf("*");
}

for(int j=0;j<n-i;j++){
    printf(" ");
}
for(int j=0;j<n-i;j++){
    printf(" ");
}
for(int j=0;j<i;j++){
    printf("*");
}
printf("\n");
}
    
    return 0;
}