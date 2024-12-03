#include <stdio.h>

#define MAX_FRAMES 23
#define MAX_PAGES 69

typedef struct {
    int page;
    int lastAccessTime;
} Frame;


int findLRU(Frame frames[], int frameSize) {
    int minTime = frames[0].lastAccessTime;
    int pos = 0;
    for (int i = 1; i < frameSize; i++) {
        if (frames[i].lastAccessTime < minTime) {
            minTime = frames[i].lastAccessTime;
            pos = i;
        }
    }
    return pos;
}

void LRU(int pages[], int n, Frame frames[], int frameSize) {
    int time = 0;

    for (int i = 0; i < frameSize; i++){
        frames[i].page = -1;
        frames[i].lastAccessTime = -1;
    }
    
    int pageFaults = 0, pageHits = 0;

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < frameSize; ++j) {
            if (frames[j].page == pages[i]) {
                found = 1;
                pageHits++;
                frames[j].lastAccessTime = time++;
                break;
            } 
        }

        if (!found) {
            int pos = i < frameSize ? i : findLRU(frames, frameSize);
            frames[pos].page = pages[i];
            frames[pos].lastAccessTime = time++;
            pageFaults++;
        }


        printf("%d -> ", pages[i]);
        for (int j = 0; j < frameSize; ++j) {
            if (frames[j].page != -1){
                printf("%d ", frames[j].page);
            }else {
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
    Frame frames[MAX_FRAMES];
    int n, frameSize;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    printf("Enter the page references(2 3 4 ... 9 6): ");
    for (int i = 0; i < n; ++i) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &frameSize);

    LRU(pages, n, frames, frameSize);
}
