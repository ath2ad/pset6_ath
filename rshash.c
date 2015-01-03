/**
*test--this thing is weird and doesn't really work....
*/

#include <stdio.h>
#include <cs50.h>
#include <string.h>

 int RSHash(char* str, int len);
 int hash = 0;
 int a = 1;
 

int main(void)
{
    while (a != 2)
    {
        printf("input word to hash\n");
        char* str = GetString();
        int len = strlen(str);
    
        RSHash(str, len);
 
        printf("the hash is %i and length is %i \n", hash,len);
        printf("hash another word? 1 if yes, 2 if no\n");
        a = GetInt();
    }    
}

    int RSHash(char* str, int len)
    {
        int b    = 378551;
        int a    = 63689;
        int hash = 0;
        int i    = 0;

        for(i = 0; i < len; str++, i++)
        {
           hash = hash * a + (*str);
           a    = a * b;
        }

        return hash;
    }
