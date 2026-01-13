#include <stdio.h>
#include <stdlib.h>

#define SIZE 5  // circular queue size

int queue[SIZE];
int front = -1;
int rear = -1;

int isFull() {
 if(front==0 && rear==SIZE-1){
 
    return 1;
 }else{
    if(front==rear+1){

    return 1;
    }else{
        return 0;
    }

 }
}

int isEmpty() {
    if (front == -1 && rear == -1) {
        return 1;
    } else {
        return 0;
    }
}

// Producer = Insert into circular queue
void enqueue(int value) {
if(!isFull()){
            if (front == -1 && rear == -1) {
            front = 0;
            rear = 0;
            queue[rear] = value;
        } else
    if(rear+1==SIZE){
        rear=0;
        queue[rear]=value;
        return;
    }else{
        queue[++rear]=value;
    }
}else{
    printf("full");
    return;
}
}

// Consumer = Remove from circular queue
void dequeue() {
if(!isEmpty()){
    if(front==rear){
        front=-1;
        rear=-1;
    }else{
        if(front==SIZE-1){
            front=0;
        }else{
            front++;
        }
    }
}
}

// Display queue
void display() {
        if (front <= rear) {
        for (int i = front; i <= rear; i++) {
            printf("%d ", queue[i]);
        }
    } else {
for(int i=front;i<SIZE;i++){
    printf("%d ",queue[i]);
}
for(int i=0;i<=rear;i++){
     printf("%d ",queue[i]);
}
    }
return;
}

int main() {
    int choice, value;

    while (1) {
        printf("\n---  (Producer-Consumer ) ---\n");
        printf("1. Produce \n");
        printf("2. Consume \n");

        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to produce: ");
                scanf("%d", &value);
                enqueue(value);
                   display();
                break;
            case 2:
                dequeue();
                printf("Front=%d Rear=%d\n", front, rear);
                   display();
                break;
           
            case 4:
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}
