#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For sleep

#define PAGE_SIZE 4
#define STARTING_PHYSICAL_ADDRESS 2369

void displayMapping(int numPages) {
    printf("\nSimulating Memory Allocation...\n");
    sleep(1);
    for (int i = 0; i < numPages; i++) {
        printf("🔹 Page %d -> Frame %d\n", i, i);
        sleep(1);
    }
    printf("\nMapping Complete! 🎉\n");
}

// Oorike
void simulatePaging(int numPages) {
    int logicalAddress, pageNumber, offset, physicalAddress;
    printf("\nEnter a logical address to access (-1 to quit): ");
    while (scanf("%d", &logicalAddress) && logicalAddress != -1) {
        pageNumber = logicalAddress / PAGE_SIZE; // Calculate page number
        offset = logicalAddress % PAGE_SIZE;    // Calculate offset

        printf("\n🔍 Searching for Page %d...\n", pageNumber);
        sleep(1);

        if (pageNumber >= numPages) {
            printf("❌ Error: Invalid logical address! Page number exceeds logical memory.\n");
            continue;
        }

        // Translate to physical address
        int frameNumber = pageNumber;
        physicalAddress = STARTING_PHYSICAL_ADDRESS + (frameNumber * PAGE_SIZE) + offset;

        printf("✅ Logical Address: %d -> Physical Address: %d\n", logicalAddress, physicalAddress);
        printf("   (Page %d in Frame %d, Offset %d)\n", pageNumber, frameNumber, offset);
        printf("---------------------------------------------------\n");
        sleep(1);
        printf("Enter another logical address (-1 to quit): ");
    }
}

int main() {
    int numPages;
    printf("Enter the number of pages in logical memory: ");
    scanf("%d", &numPages);
    printf("\n📊 Mapping Pages to Frames...\n");
    displayMapping(numPages);
    simulatePaging(numPages);
    return 0;
}
