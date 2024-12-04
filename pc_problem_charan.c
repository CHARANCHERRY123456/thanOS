#include<stdio.h>
#include <stdlib.h>

int arr[100];

void main(){
    int bufferSize=5,option,currItemCount=0;
    printf("Etner the size of buffer :");
    scanf("%d" , &bufferSize);
    while (1)
    {
        printf("choose 1-produce , 2-consume :");
        scanf("%d" , &option);
        printf("thank for choosing %d \n" , option);
        switch (option)
        {
        case 1://producer code
            if(currItemCount < bufferSize) currItemCount++;
            else printf("Please wait buffer is full");
            printf("Count = %d , Size = %d \n" , currItemCount , bufferSize);
            break;
        case 2://consumer
            if (currItemCount > 0) currItemCount--;
            else printf("Please wait some has to keep data\n\n");
            printf("now the count = %d , size = %d\n" , currItemCount , bufferSize);
            break;
        default:
            break;
        }
    }


}