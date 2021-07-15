// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"
#include <string.h>
#include <stdio.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

int dictcount = 0;

char* findnextword(const char* dictionary);
void destroylist(node* temp);
void placeinlist(node* temp, int index);
bool endofchain(node element);
bool checkeachnode(node* ptr, char* input);
void lower(char* input, int length);

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N] = {0};

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int index = hash(word);
    if(index<0||index>25)
    {
        return false;
    }
    char malleable[LENGTH+1];
    strcpy((char*)malleable, word);
    lower((char*)malleable, strlen(word));
    if(checkeachnode(table[index], malleable))
    {
        return true;
    }
    return false;
}
bool checkeachnode(node* ptr, char* input)
{

    if(ptr==NULL)
    {
        return false;
    }
    else if(strcmp(ptr->word, input)==0)
    {
        return true;
    }
    return checkeachnode(ptr->next, input);
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int index = 0;
    index=tolower(word[0])-'a';
    return index;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    int index = 0;
    char holder[LENGTH+1];
    FILE* file=fopen(dictionary, "r");
    while (fgets(holder, sizeof(holder), file)!=NULL)
    {
        index=holder[0]-'a';
        if(index<0||index>=N)
        {
            continue;
        }
        int len=strlen(holder);
        if(holder[len-1]=='\r'||holder[len-1]=='\n')
        {
            holder[len-1]='\0';
        }
        node* temp=malloc(sizeof(node));
        temp->next=NULL;
        strcpy(temp->word, holder);
        placeinlist(temp, index);
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if(dictcount==0)
    {
    return 0;
    }
    return dictcount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for(int i = 0; i<N; i++)
    {
        destroylist(table[i]);
        table[i]=NULL;
    }
    return true;
}

void placeinlist(node* temp, int index)
{
    if(table[index]!=NULL)
    {
        temp->next = table[index];
    }
    table[index]=temp;
    dictcount++;
    return;
}


void destroylist(node* temp)
{
    if(temp==NULL)
    {
        return;
    }
    else
    {
        destroylist(temp->next);
        free(temp);
    }
}

void lower(char* input, int length)
{
    for(int i = 0; i < length; i++)
    {
        input[i] = tolower(input[i]);
    }
    return;
}

