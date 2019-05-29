/*
 * CS 261 Data Structures
 * Assignment 5
 * Name: 
 * Date: 
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

int hashFunction1(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += key[i];
    }
    return r;
}

int hashFunction2(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += (i + 1) * key[i];
    }
    return r;
}

/**
 * Creates a new hash table link with a copy of the key string.
 * @param key Key string to copy in the link.
 * @param value Value to set in the link.
 * @param next Pointer to set as the link's next.
 * @return Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
    HashLink* link = malloc(sizeof(HashLink));
    link->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(link->key, key);
    link->value = value;
    link->next = next;
    return link;
}

/**
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * @param link
 */
static void hashLinkDelete(HashLink* link)
{
    free(link->key);
    free(link);
}

/**
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param map
 * @param capacity The number of table buckets.
 */
void hashMapInit(HashMap* map, int capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->table = malloc(sizeof(HashLink*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        map->table[i] = NULL;
    }
}

/**
 * Removes all links in the map and frees all allocated memory. You can use
 * hashLinkDelete to free the links.
 * @param map
 */
void hashMapCleanUp(HashMap* map)
{
    //Done 
    // FIXME: implement
    // 1. loop through the dynArr by size
    // 1.5 figure out how links are linked: based on constructor, I assume the linked list is a _addFront(); 
    // 2. each [i] while loop detele all link until 
    struct HashLink* junk =NULL; 
    struct HashLink* next = NULL;
    for (int i =0; i < map->capacity; i++){
      junk = map->table[i]; 
      while (junk !=NULL){
        next = junk->next; 
        hashLinkDelete(junk); 
        junk = next;
      }
      map->table[i] =NULL;
    }
}


/**
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity The number of buckets.
 * @return The allocated map.
 */
HashMap* hashMapNew(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap));
    hashMapInit(map, capacity);
    return map;
}

/**
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * @param map
 */
void hashMapDelete(HashMap* map)
{
    hashMapCleanUp(map);
    free(map);
}

/**
 * Returns a pointer to the value of the link with the given key  and skip traversing as well. Returns NULL
 * if no link with that key is in the table.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return Link value or NULL if no matching link.
 */
int* hashMapGet(HashMap* map, const char* key)
{   
    //Done 
    // assume using hashFunction1(); 
    int hashNum = hashFunction1(key)%map->capacity;
    struct HashLink* cur = map->table[hashNum]; 
    while (cur != 0){
      if(strcmp(cur->key,key))
      {
         return &cur->value; 
      }
     else{
          cur =cur->next;
      }
    }
    // FIXME: implement
    return NULL;
}

/**
 * Resizes the hash table to have a number of buckets equal to the given 
 * capacity (double of the old capacity). After allocating the new table, 
 * all of the links need to rehashed into it because the capacity has changed.
 * 
 * Remember to free the old table and any old links if you use hashMapPut to
 * rehash them.
 * 
 * @param map
 * @param capacity The new number of buckets.
 */
void resizeTable(HashMap* map, int capacity)
{
    //NOT  DONE YET 
    // FIXME: implement
    // 1. create a new table 
    struct HashLink** newTable = malloc(sizeof(HashLink*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        newTable[i] = NULL;
    }
    //2. rehash everything 
    // 2.1 read from the old table into the junk and then delete junk 
    struct HashLink* next; 
    int rehashNum; 

    for(int i = 0; i < map->capacity; i++){
    struct HashLink* junk = map->table[i]; 
    while(junk !=0){
      rehashNum =  hashFunction1(junk->key)%capacity;
      newTable[rehashNum] = // add Hash link to table 
    }
    }
}

/**
 * Updathe given key-value pair in the hash table. If a link with the given
 * key already exists, this will just update the value and skip traversing. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list. You can use hashLinkNew to create the link.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket.
 * 
 * @param map
 * @param key
 * @param value
 */
void hashMapPut(HashMap* map, const char* key, int value)
{   // Warning: Not sure what does update only the value and skip the travelsing mean when value already exist in the hash map 
    //assume do nothing when exist
    // FIXME: implement
    //1. figure out if key is in the hashmap 
    //2. if not, add to the front of the link 
    if(hashMapContainsKey(key))
    {
        *(hashMapGet(map, key))=value;
        // hashMapGet returns int pointer to the value stored in that pairs, thus dereference it first and change it to vlaue 
    }
    else {
        
    }
}

/**
 * Removes and frees the link with the given key from the table. If no such link
 * exists, this does nothing. Remember to search the entire linked list at the
 * bucket. You can use hashLinkDelete to free the link.
 * @param map
 * @param key
 */
void hashMapRemove(HashMap* map, const char* key)
{
    // FIXME: implement
}

/**
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return 1 if the key is found, 0 otherwise.
 */
int hashMapContainsKey(HashMap* map, const char* key)
{
    //Done 
    // FIXME: implement
    //1. hash the key into value and locate table bucket 
    //2. travels through bucket and find key 
    int hashNum = hashFunction1(key)%map->capacity;
    struct HashLink* cur = map->table[hashNum]; 
    while (cur != 0){
      if(strcmp(cur->key,key))
      {
         return 1; 
      }
     else{
          cur =cur->next;
      }
    }
    return 0;
}

/**
 * Returns the number of links in the table.
 * @param map
 * @return Number of links in the table.
 */
int hashMapSize(HashMap* map)
{
    //Done
    // FIXME: implement
    return map->size;
}

/**
 * Returns the number of buckets in the table.
 * @param map
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map)
{
    //Done 
    // FIXME: implement
    return map->capacity;
}

/**
 * Returns the number of table buckets without any links.
 * @param map
 * @return Number of empty buckets.
 */
int hashMapEmptyBuckets(HashMap* map)
{
    //Done
    // FIXME: implement
    int empty =0; 
    for (int i =0; i < map->capacity; i++ ){
      if (map->table[i] == NULL)
      {
          empty++;
      }
    }
    return empty;
}

/**
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Remember that the buckets are linked lists, so this ratio tells you nothing
 * about the number of empty buckets. Remember also that the load is a floating
 * point number, so don't do integer division.
 * @param map
 * @return Table load.
 */
float hashMapTableLoad(HashMap* map)
{ 
    //Done 
    // FIXME: implement
    float ratio = ((float)map->size)/((float)map->capacity); 
    return ratio;
}

/**
 * Prints all the links in each of the buckets in the table.
 * @param map
 */
void hashMapPrint(HashMap* map)
{
  // FIXME: implement
  struct HashLink* cur = NULL; 
  for(int i =0; i< map->capacity; i++)
  {
       cur = map->table[i]; 
       while(cur != NULL)
       {
           printf("%c ", cur->key);
           printf("%d ",cur->value);
           cur = cur->next;
       }
       prinft("\n");
      // else {//do nothing }
  }
   
}
