#include<stdio.h>
#include <stdlib.h>

void main() {
    int bufferSize, option, currItemCount = 0;
    printf("Enter the size of buffer :");
    scanf("%d" , &bufferSize);
    while (1)
    {
        printf("\n\nChoose an Option (1-produce, 2-consume): ");
        scanf("%d" , &option);
        switch (option) {
            case 1:  // producer
                if(currItemCount < bufferSize) currItemCount++;
                else printf("Please wait buffer is full\n");
                break;
            case 2:  // consumer
                if (currItemCount > 0) currItemCount--;
                else printf("Please wait until the buffer has an item to remove\n\n");
                break;
            default:
                break;
        }
        printf("We have %d items in the buffer" , currItemCount);
    }
}