#include <stdio.h>
#include <stdlib.h>

#define INF 10000000

typedef struct {
    int pid;        
    int arrivalTime;
    int burstTime;
    int completionTime;
    int isInReadyQ;
    int finished;
} Process;

// Function to compare processes by arrival time for qsort
int compareArrivalTime(const void* a, const void* b) {
    Process* p1 = (Process*)a;
    Process* p2 = (Process*)b;
    return p1->arrivalTime - p2->arrivalTime;
}


int findMinimumBurstTime(Process processes[], int n) {
    int min = INF, pos = -1;
    for (int i = 0; i < n; i++) {
        if (processes[i].isInReadyQ && processes[i].burstTime < min) {
            min = processes[i].burstTime;
            pos = i;
        }
    }
    return pos;
}

void addNewProcessesToReadyQ(Process processes[], int n, int time) {
    for (int i = 0; i < n; i++) {
        if (processes[i].arrivalTime <= time && !processes[i].finished) {
            processes[i].isInReadyQ = 1;
        }
    }
}

void sjf(Process processes[], int n) {
    qsort(processes, n, sizeof(Process), compareArrivalTime);
    int time = processes[0].arrivalTime;
    processes[0].isInReadyQ = 1;
    int i = 0;
    while ((i = findMinimumBurstTime(processes, n)) != -1) {
        time += processes[i].burstTime;
        processes[i].completionTime = time;
        processes[i].finished = 1;
        processes[i].isInReadyQ = 0;
        addNewProcessesToReadyQ(processes, n, time);   
    }
}

void main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
    }

    for (int i = 0; i < n; i++) {
        processes[i].isInReadyQ = 0;
        processes[i].finished = 0;
    }

    sjf(processes, n);

    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\t Turnaround Time\n");
    int totalWaitingTime = 0, totalTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        int turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        int waitingTime = turnaroundTime - processes[i].burstTime;
        totalWaitingTime += waitingTime;
        totalTurnaroundTime += turnaroundTime;
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrivalTime, processes[i].burstTime, processes[i].completionTime, waitingTime, turnaroundTime);
    }
    printf("Average Waiting Time: %.2fms\n", (float) totalWaitingTime / n);
    printf("Average Turnaround Time: %.2fms\n", (float) totalTurnaroundTime / n);
}
