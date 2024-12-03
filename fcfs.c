#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;        
    int arrivalTime;
    int burstTime;
    int completionTime;
} Process;

// Function to compare processes by arrival time for qsort
int compareArrivalTime(const void* a, const void* b) {
    Process* p1 = (Process*)a;
    Process* p2 = (Process*)b;
    return p1->arrivalTime - p2->arrivalTime;
}

void fcfs(Process processes[], int n) {
    qsort(processes, n, sizeof(Process), compareArrivalTime);
    for (int i = 0, time = 0; i < n; i++) {
        if (time < processes[i].arrivalTime)
            time = processes[i].arrivalTime;
        time += processes[i].burstTime;
        processes[i].completionTime = time;
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
    fcfs(processes, n);

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
