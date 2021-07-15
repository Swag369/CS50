#include <stdio.h>
#include <cs50.h>
#include <string.h>
int main(void)
{
    string s = get_string("Text: ");
    int len = strlen(s);

    int letters = 0;
    int wordcount=  0;
    int sentences= 0;

    for(int i = 0; i<len;i++)
    {
        if(s[i]==46||s[i]==33||s[i]==63){
            sentences++;
        }
        if(s[i]==32){
            wordcount++;
        }
        else if(s[i]>=97&&s[i]<=122){
            letters++;
        }
        else if(s[i]>=65&&s[i]<90){
            letters++;
        }
        else{}
    }
    wordcount++;
    double index = 0.0588 * letters/wordcount*100 - 0.296 * sentences/wordcount*100 - 15.8;
    int grade = 0;
    if(index-(int)index>.5){
        grade = (int)index+1;
    }
    else{
        grade = (int) index;
    }
    if(grade<1){
        printf("Before Grade 1\n");
    }
    else if(grade>15){
        printf("Grade 16+\n");
    }
    else{
    printf("Grade %i\n", grade);
    }
}