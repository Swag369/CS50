#include <stdio.h>
#include <cs50.h>
int main (void){
    int maxblockcount = get_int("Height:");
    while(maxblockcount>8||maxblockcount<1){
        maxblockcount=get_int("Height:");
    }
    for(int linecount = 1; linecount<=maxblockcount;linecount++){
        int spacecount = maxblockcount-linecount;
        for (int i = 1; i<= spacecount; i++){
        printf(" ");
        }
        for (int i = 0; i<linecount; i++){
            printf("%c", '#');
        }
        printf("  ");
        for (int i = 0; i<linecount; i++){
            printf("%c", '#');
        }
        printf("\n");
    }
}