/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
			
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: 	
	post:	
*/
int isBalanced(char* s)
{
	/* FIXME: You will write this function */		
	char* dynArr; 
    int size = 0; 
    int capacity = 50;
    dynArr = (char*)malloc(sizeof(char) * capacity);
   //-------------------------------------------------
    while (*s != '\0')
    {
        switch (*s){
            case '(':
            dynArr[size] = '(' ; 
            size ++;
            break;         
            case '[':
            dynArr[size] = '[' ; 
            size ++;
            break;
            case '{':
            dynArr[size] = '{' ; 
            size ++;
            break;
            case ')':
            dynArr[size] = ')' ; 
            size --;
            break;
            case ']':
            dynArr[size] = ']' ; 
            size --;
            break;
            case '}':
            dynArr[size] = '}' ;
            size --;  
        }
        //-------------------------------------
        //if cpacity is full 
        if (size == capacity)
        {
        char* temp = (char*)malloc(sizeof(char) * capacity);
        capacity = capacity *2;
        for (int i =0; i < size; i++)
        {
            temp[i] = dynArr[i];
        }
        free(dynArr);
        dynArr = (char*)malloc(sizeof(char) * capacity);
        
        for (int i =0; i < size; i++)
        {
            dynArr[i] = temp[i]; 
        }
        free(temp); 
        } 
        s=s+1; 
    }

    if (nextChar(dynArr)!=0)
     {return 1; }
     return 0;

}

int main(int argc, char* argv[]){
	
	char* s=argv[1];	
	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}

