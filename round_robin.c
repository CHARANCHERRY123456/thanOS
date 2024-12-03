#include <stdio.h>
#include <stdlib.h>

#define INF 10000000

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

int findNextProcess(int queuePositions[], int n) {
    int min = INF, pos = -1;
    for (int i = 0; i < n; i++) {
        if (queuePositions[i] < min) {
            min = queuePositions[i];
            pos = i;
        }
    }
    return pos;
}

void roundRobin(Process processes[], int n, int quantum) {
    qsort(processes, n, sizeof(Process), compareArrivalTime);
    int time = processes[0].arrivalTime;

    // queuePositions[i] stores the position of the process i in the queue
    // the queue is not implemented here, we just store the position of the process in the queue
    int queuePositions[n];
    for (int i = 0; i < n; i++) queuePositions[i] = INF; // INF means the process is not in the queue
    int pos = 0; // stores the next empty position in the queue
    queuePositions[0] = pos++; // First process is in the queue

    int remainingBurstTime[n];
    for (int i = 0; i < n; i++) remainingBurstTime[i] = processes[i].burstTime;

    while (1) {
        // find the next process in the queue
        int pidx = findNextProcess(queuePositions, n); 
        if (pidx == -1) return; // all values in queuePositions are INF
        
        time += (remainingBurstTime[pidx] < quantum) ? remainingBurstTime[pidx] : quantum;  // time += min(remainingBurstTime[pidx], quantum)
        remainingBurstTime[pidx] -= quantum;

        if (remainingBurstTime[pidx] <= 0) { // process completed
            processes[pidx].completionTime = time;
        }

        // add new processes to the queue
        for (int i = 0; i < n; i++) {
            if (remainingBurstTime[i] > 0 && queuePositions[i] == INF && processes[i].arrivalTime <= time) {
                queuePositions[i] = pos++;
            }
        }
        // if the process is not completed, add it to the end of the queue else remove it
        queuePositions[pidx] = remainingBurstTime[pidx] > 0 ? pos++ : INF;
    }
}

void main() {
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
    }

    roundRobin(processes, n, quantum);

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
