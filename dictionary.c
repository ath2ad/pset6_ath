/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

node* hashtable[HASHSIZE] = {NULL};

// for the size function
int totalWords = 0;


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    char worda[LENGTH + 1] = {};
    //sscanf(word, "%s", worda);
    strcpy(worda, word);
    for (int i = 0; i < strlen(worda); i++)
    {   
        if (isalpha(worda[i]))
        {
            worda[i] = tolower(worda[i]);
        }    

    }
    
    int hash = hfunc(worda);
    
    // set up linked list variables at apporiate hash index
    node* curr = hashtable[hash];
    
    // loop word through dictionary until NULL is reached 
    while (curr != NULL)
    {     
        // if a match occurs then the word is spelled correctly, return true
        if (strcmp(worda, curr->word) == 0)
        {
            return true;
        }
        curr = curr->next;        
    } 
       
    // if loop is broke it means EOF is reached: no match found
    return false;      
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // determine word to iterate by taking entire line in dictionary
    FILE* file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    char buffer[LENGTH + 1];
    
    // add word from dictionary to buffer and load
   while (fscanf(file, "%s\n", buffer) != EOF)
    {
        // track words loaded for the Size function
        totalWords++;
        
        // hash for the word
        int hash = hfunc(buffer);
       
        // create a vessel for the word to enter the hashtable's linked lists
        node* new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }
       
        // add buffer to the new_node
        strcpy(new_node->word, buffer); 
        new_node->next = NULL;  
       
        // keep track of current and previous nodes
        node* curr = hashtable[hash];
        node* prev = NULL;
    
        // navigate the linked list  
        while (curr != NULL)
        {                                       
            prev = curr;
            curr = curr->next;
        }

        // insert the node in the correct position
        new_node->next = curr;
        if (prev == NULL)
        {
            hashtable[hash] = new_node;
        }
        else
        {
            prev->next = new_node;
        }    
    }
    fclose(file);  
    return true;          
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return totalWords;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // loop to navigate the hashtable
    for (int i = 0; i < HASHSIZE; i++)
    {
        // navigate the linked list
        node* cursor = hashtable[i];
        while (cursor != NULL)
        {
            node* temp = cursor;
            cursor = cursor->next;
            // free each node
            free(temp);
        }
    }
    return true;
}

/**
* Hash function for referencing dictionary words with document words
* in the speller.c
*/
int hfunc(const char* word)
{
    // TODO
    char reg[LENGTH +1] = {0};
    strcpy(reg, word);
/**    for (int i = 0; i < 4; i++)
    {
        
        if(reg[i] == '\'')
        {
            reg[i] = 27;
        }
        else if(isalpha(reg[i]) == 0)
        {
            reg[i] = 0;
        }
    }
*/    
    int ihash = (reg[0] * 27 * 27 + reg[1] * 27 + reg[2]) % HASHSIZE;  

    return ihash;
}
