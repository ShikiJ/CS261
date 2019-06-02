#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    
    int len = strlen(word);
    char * lower = (char*)malloc(len+1);
    lower[len]='\0';
    for (int i =0; i < len; i++)
    {
        lower[i] = tolower(word[i]);
    }
    return lower;
}

/**
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
void loadDictionary(FILE* file, HashMap* map)
{
    // FIXME: implement
    char * word = nextWord(file);
    while (word !=0)
    {
        // if we hash the dictionary we need to 1. hash very word until the end of file 
        // 2. give dummy value
        // we don;t even need to check repeat
        int value = 1000;
        hashMapPut(map, word, value);
        word = nextWord(file); 
        // test 
    }

}

int levenshtein(const char *s, const char *t)
{
	int ls = strlen(s), lt = strlen(t);
	int d[ls + 1][lt + 1];
 
	for (int i = 0; i <= ls; i++)
		for (int j = 0; j <= lt; j++)
			d[i][j] = -1;
 
	int dist(int i, int j) {
		if (d[i][j] >= 0) return d[i][j];
 
		int x;
		if (i == ls)
			x = lt - j;
		else if (j == lt)
			x = ls - i;
		else if (s[i] == t[j])
			x = dist(i + 1, j + 1);
		else {
			x = dist(i + 1, j + 1);
 
			int y;
			if ((y = dist(i, j + 1)) < x) x = y;
			if ((y = dist(i + 1, j)) < x) x = y;
			x++;
		}
		return d[i][j] = x;
	}
	return dist(0, 0);
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
    HashMap* map = hashMapNew(1000);
    
    FILE* file = fopen("dictionary.txt", "r");
    clock_t timer = clock();
    loadDictionary(file, map);
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    //test
    //hashMapPrint(map);
    fclose(file);
    
    char inputBuffer[256];
    int quit = 0;
//	int count =0;
	int indicator = 0; 
    struct HashLink * cur;
//	struct HashLink** similar = malloc(sizeof(struct HashLink*) * 5);
	int arrayInt[5] = {1000,1000,1000,1000,1000};
	char* arrayChar[5]; 
	char* lkey; 
	int lvalue=0;
	int lindex=0;
	int temp;
	while (!quit)
    {
		printf("Enter a word or \"quit\" to quit: ");
        scanf("%s", inputBuffer);
  //  	int bufferHash = HASH_FUNCTION(inputBuffer)%map->capacity;    	 
		for(int i =0; i< 1000; i++)
		{	
			cur = map->table[i];
			//	printf("i is %d \n", i);
			while(cur !=0)
			{
				if (strcmp(cur->key,inputBuffer)==0)
				{
				indicator =1;
				cur= cur->next;				
				}	
        // Implement the spell checker code here..
				else 
				{
					temp = levenshtein ( cur->key, inputBuffer); 
					//cur->value=temp; this is not working! 
					hashMapPut(map, cur->key, temp);
				//	printf("value updated to %d",cur->value);
					lkey =cur->key;
					cur = cur->next;  
					// maybe make a small array for 5 most similar word too ?
					//1.check where and what is the largest value 
					for(int i=0; i< 5;i++)
					{
						if(lvalue<arrayInt[i])
						{
							lvalue=arrayInt[i];
							lindex=i;
						}
					}
					//2.see if temp should be added to array group 
					if(temp < lvalue)
					{
					//	printf("so what is going on?");
						arrayInt[lindex]=temp;
						arrayChar[lindex]=lkey;
						lvalue=temp;
					}
				/*	if(count < 5 && temp == 1)
					{
					//	printf("problem entered %d times ", count+1);
						similar[count] = cur; 
						count++; 
					}
				*/	
				}	
			}
		}
	
	if(indicator == 1)
		{printf("The input word %s is spelled correctly \n", inputBuffer);}
	else
		{	
		printf("The input word %s is spelled incorrectly \n", inputBuffer);
		printf("Did you mean: \n");
		
		for (int i =0; i <5; i++)
			{
				printf("%s \n",arrayChar[i]);
			}
	//	printf("fuck core");
	
		}
    if (strcmp(inputBuffer, "quit") == 0)
        {
            quit = 1;
        }    
    }
    
		hashMapDelete(map);
	
    return 0;

}