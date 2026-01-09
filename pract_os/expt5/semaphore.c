#include <stdio.h>
#include <stdlib.h>

#define SIZE 5  // circular queue size

int queue[SIZE];
int front = -1;
int rear = -1;

int isFull() {
    return (front == (rear + 1) % SIZE);
}

int isEmpty() {
    return (front == -1);
}

// Producer = Insert into circular queue
void enqueue(int value) {
    if (isFull()) {
        printf("Buffer is FULL! Cannot insert %d\n", value);
    } else {
        if (front == -1) front = 0;
        rear = (rear + 1) % SIZE;
        queue[rear] = value;
        printf("Produced (Inserted): %d\n", value);
    }
}

// Consumer = Remove from circular queue
int dequeue() {
    if (isEmpty()) {
        printf("Buffer is EMPTY! Nothing to consume\n");
        return -1;
    } else {
        int value = queue[front];
        if (front == rear) {  // only one element
            front = -1;
            rear = -1;
        } else {
            front = (front + 1) % SIZE;
        }
        printf("Consumed (Removed): %d\n", value);
        return value;
    }
}

// Display queue
void display() {
    if (isEmpty()) {
        printf("Queue is EMPTY!\n");
    } else {
        printf("Queue elements: ");
        int i = front;
        while (1) {
            printf("%d ", queue[i]);
            if (i == rear) break;
            i = (i + 1) % SIZE;
        }
        printf("\n");
    }
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
                   display();
                break;
           
            case 4:
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}
