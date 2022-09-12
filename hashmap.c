#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
  Pair* p = createPair(key, value);
  size_t i = hash(key, map->capacity);
  while(1){
    if(map->buckets[i] == NULL || map->buckets[i]->key == NULL){
      map->buckets[i] = p;
      map->size++;
      map->current = i;
      break;
    }
    i++;
    if(i == map->capacity){
      i = 0;
    }
  }
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
  HashMap* M = (HashMap*)malloc(sizeof(HashMap)*capacity);
    M->buckets = (Pair**)calloc(capacity,sizeof(Pair));
    M->capacity = capacity;
    M->size = 0;
    M->current = -1;
  return M;
}

void eraseMap(HashMap * map,  char * key) {    
  Pair* eliminatePair = searchMap(map, key);
  if(eliminatePair != NULL){
    eliminatePair->key = NULL;
    map->size--;
  }
}

Pair * searchMap(HashMap * map,  char * key) {   
  size_t cont = 0;
  size_t i = hash(key, map->capacity);
  while(1){
    if(map->buckets[i] == NULL || map->buckets[i]->key == NULL){
      return NULL;
    }
    if(is_equal(key, map->buckets[i]->key)){
      map->current = i;
      return map->buckets[i];
    }
    i++;
    cont++;
    if(cont == map->capacity) 
      break;
    if(i == map->capacity){
      i = 0;
    }
  }
  return NULL;
}
Pair * firstMap(HashMap * map) {
  Pair* aux;
  for(int i=0;i<map->capacity;i++)
    if(map->buckets[i]!=NULL)
      aux=map->buckets[i]
    return aux;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
