#include <stdio.h>

#define MAX_FRAMES 23
#define MAX_PAGES 69

void fifo(int pages[], int n, int frames[], int frameSize) {
    int head = 0;
    for (int i = 0; i < frameSize; i++)
        frames[i] = -1;
    
    int pageFaults = 0, pageHits = 0;
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frameSize; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                pageHits++;
                break;
            } 
        }
        if (!found) {
            frames[head++ % frameSize] = pages[i];
            pageFaults++;
        }

        printf("%d -> ", pages[i]);
        for (int j = 0; j < frameSize; ++j) {
            if (frames[j] != -1){
                printf("%d ", frames[j]);
            } else {
                printf("_ ");
            }
        }
        printf("%s", found ? "✅" : "❌");
        printf("\n");
    }

    printf("\nTotal Page Hits: %d\n", pageHits);
    printf("Total Page Faults: %d\n", pageFaults);
    printf("Hit Ratio: %.2f\n", (float) pageHits / n);
    printf("Fault Ratio: %.2f\n", (float) pageFaults / n);
}


void main() {
    int pages[MAX_PAGES];
    int frames[MAX_FRAMES];
    int n, frameSize;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    printf("Enter the page references(2 3 4 ... 9 6): ");
    for (int i = 0; i < n; ++i)
        scanf("%d", &pages[i]);

    printf("Enter the number of frames: ");
    scanf("%d", &frameSize);

    fifo(pages, n, frames, frameSize);
}
