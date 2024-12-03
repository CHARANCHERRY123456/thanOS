#include <stdio.h>

void worstFit(int blockSizes[], int numBlocks, int processSizes[], int numProcesses) {
    for (int i = 0; i < numProcesses; i++) {
        int worstIndex = -1;
        for (int j = 0; j < numBlocks; j++) {
            if (blockSizes[j] >= processSizes[i]) {
                if (worstIndex == -1 || blockSizes[j] > blockSizes[worstIndex]) {
                    worstIndex = j;
                }
            }
        }
        if (worstIndex != -1) {
            blockSizes[worstIndex] -= processSizes[i];
            printf("✅ Process %d (Size: %d KB) allocated to Block %d (Remaining: %d KB)\n",
                   i + 1, processSizes[i], worstIndex + 1, blockSizes[worstIndex]);
        } else {
            printf("❌ Process %d (Size: %d KB) could not be allocated.\n", i + 1, processSizes[i]);
        }
    }
}

int main() {
    int numBlocks, numProcesses;
    printf("Enter the number of memory blocks: ");
    scanf("%d", &numBlocks);
    int blocks[numBlocks];
    printf("Enter the sizes of the memory blocks (in KB):\n");
    for (int i = 0; i < numBlocks; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blocks[i]);
    }

    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);
    int processes[numProcesses];
    printf("Enter the sizes of the processes (in KB):\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processes[i]);
    }

    worstFit(blocks, numBlocks, processes, numProcesses);
    return 0;   
}