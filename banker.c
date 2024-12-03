#include <stdio.h>
#include <unistd.h>

#define INT_MAX 1000000
#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int processes[MAX_PROCESSES];
int alloc[MAX_PROCESSES][MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int avail[MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];

int safetyChecking(int n, int r) {
    int safeSeq[n];
    for (int i = 0; i < n; i++) safeSeq[i] = -1;
    for (int count = 0; count < n; count++) {
        for (int i = 0; i < n; i++) {
            int j = 0;
            for (; j < r; j++) {
                if (need[i][j] > avail[j])
                    break;
            }
            // check if we can allocate
            if (j == r) {
                safeSeq[count] = i;
                for (int j = 0; j < r; j++) {
                    avail[j] += alloc[i][j];
                    need[i][j] = INT_MAX; 
                }
                break;
            }
        }
        if (safeSeq[count] == -1) {
            printf("NOT SAFE 💀");
            return 0;
        }
    }
    printf("SAFE 🎉\nSafe sequence: ");
    for (int i = 0; i < n; i++) 
        printf("%d ", safeSeq[i]);
    return 1;
}

int main() {
    int n, r;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &r);

    for (int i = 0; i < n; i++) processes[i] = i;

    printf("Enter allocation matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter max matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < r; j++) {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    printf("Enter available resources:\n");
    for (int i = 0; i < r; i++)
        scanf("%d", &avail[i]);
    
    printf("\nChecking safety...\n");
    sleep(2);
    safetyChecking(n, r);

    return 0;
}