#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
int main(int argc, string argv[])
{

if(argc != 2)
{
    printf("ERROR");
    return 1;
}

string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
string cipher = argv[1];
int cipherlen = strlen(cipher);
int ciphervalue=0;

for(int i = 0; i<26; i++)
{
	cipher[i]=toupper(cipher[i]);
	ciphervalue = ciphervalue+cipher[i];
}

if(cipherlen!=26) //check length
{
	printf("ERROR");
	return 1;
}
int count = 0;
for(int i = 0; i<26; i++)
{
	count = 0;
	for(int j = 0; j<26; j++)
	{
		if(letters[i]==cipher[j])
		{
			count++;
			if(count>1)
			{
				printf("ERROR");
				return 1;
			}
		}
	}
	if(count==0)
	{
		printf("Error");
		return 1;
	}
}

string text = get_string("plaintext: ");
int len = strlen(text);
for(int j = 0; j<len; j++)
{
	for(int m = 0; m<26; m++)
	{
		if(text[j]==letters[m])
		{
			text[j]=cipher[m];
			break;
		}
		else if(letters[m]+32==text[j])
		{
			text[j]=cipher[m]+32;
			break;
		}
	}
}
printf("ciphertext: ");
printf("%s\n",text);
return 0;
}