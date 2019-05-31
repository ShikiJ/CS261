#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <ctype.h>

/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
//Fix me: Do the necessary change to make the implementation //case-insensitive  
   while (1) 
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')  
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            // .............
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
	
	int len= strlen(word);
    char * lowerWord = (char*)malloc(len+1);
	lowerWord[len] = '\0';
	for(int i =0; i < len; i++)
	{
		lowerWord[i] = tolower(word[i]);
	}
	return lowerWord;
}

/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    // FIXME: implement
    const char* fileName = "input1.txt";
    if (argc > 1)
    {
        fileName = argv[1];
    }
    printf("Opening file: %s\n", fileName);
    
    clock_t timer = clock();
    
    HashMap* map = hashMapNew(10);
   
    char *word; 

    FILE* fptr; 
    fptr =fopen(fileName,"r");
    
	word = nextWord(fptr);
    while(word != 0)
    {
	 //   printf("int the loop ");
//   printf(" \n %s ",word);
//  	printf(" \n add word to hashMap");
	// 1. chekc if contains yes, value = hashMGet(); not value =0; 
	//2. hashMapPut(map,key, value)
	int value = 1 ; 
	
	if (hashMapContainsKey(map,word))
	{
		value = *hashMapGet(map,word) + 1; 
	}
	hashMapPut(map, word,value);
	
	word = nextWord(fptr);
    }
 //   fscanf(fptr, "%s", str); 
 //   printf("%s",str);
    hashMapPrint(map);
	free(word);
	fclose(fptr);

    // --- Concordance code begins here ---
    // Be sure to free the word after you are done with it here.
    // --- Concordance code ends here ---
    
    
    
    timer = clock() - timer;
    printf("\nRan in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    printf("Empty buckets: %d\n", hashMapEmptyBuckets(map));
    printf("Number of links: %d\n", hashMapSize(map));
    printf("Number of buckets: %d\n", hashMapCapacity(map));
    printf("Table load: %f\n", hashMapTableLoad(map));
    
    hashMapDelete(map);
    return 0;
}
