#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int count = 0;
int end = 0;

void logic(FILE* memcard);
int isnewcard(BYTE arr[512]);
FILE* createfile(void);
void print(FILE* dest, BYTE arr[512], int length);
void read(FILE* memcard, BYTE arr[512], int* legnth);

int main(int argc, char *argv[])
{
    if(argc!=2)
    {
        printf("Only 1 extra cmd line arg");
        return 1;
    }
    FILE* memcard = fopen(argv[1], "r");
        if(memcard==NULL)
    {
        printf("File pointer be null homie");
        return 1;
    }
    logic(memcard);
    return 0;
}

void logic(FILE* memcard)
{
    BYTE arr[512];
    FILE* image = NULL;
    int length = 0;
    while(end==0)
    {
        read(memcard,arr,&length);
        if(isnewcard(arr)==1)
        {
            if(image!=NULL)
            {
                fclose(image);
            }
            image = createfile();
            print(image, arr, length);
        }
        else
        {
            if(count!=0)
            {
                print(image, arr, length);
            }
        }
    }

    if(image!=NULL)
    {
        fclose(image);
    }

    return;
}

    int isnewcard(BYTE arr[512])
{
    if(arr[0]==0xff && arr[1]==0xd8 && arr[2]==0xff)
    {
        if(arr[3]>=0xe0 && arr[3]<=0xf0)
        {
            return 1;
        }
    }
    return 0;
}

FILE* createfile(void)
{
    char* filename = malloc(6*sizeof(char));
    sprintf(filename, "%03i.jpg", count);
    FILE* image = fopen(filename, "a");
    free(filename);
    count++;
    return image;
}
void print(FILE* dest, BYTE arr[], int length)
{
    fwrite(arr, sizeof(arr[0]), length, dest);
    return;
}

void read(FILE* memcard, BYTE arr[512], int* length)
{
    *length = fread(arr, sizeof(arr[0]), sizeof(BYTE[512])/sizeof(arr[0]), memcard);

    if(*length==sizeof(BYTE[512])/sizeof(arr[0]))
    {
        return;
    }
    else
    {
        end = 1;
        return;
    }
}