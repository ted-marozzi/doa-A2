/* * * * * * *
 * Hashing module for Assignment 2.
 *
 * created for COMP20007 Design of Algorithms 2020
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by <Insert Name Here>
 */

#include "hash.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>


//TODO: Header
// Implements a solution to Problem 1 (a), which reads in from stdin:
//   N M
//   str_1
//   str_2
//   ...
//   str_N
// And outputs (to stdout) the hash values of the N strings 1 per line.
void problem_1_a() {
  // TODO: Implement Me!
  hash_string_t* string = malloc(sizeof(*string));
  int n, m, i;
  initialiseHashString(string);
  scanf("%d %d\n", &n, &m);
  // For each word
  
  for(i = 0; i < n ; i++)
  {
    calculateHash(string, m);
    printf("%d\n", string->sum);
  }
  

  free(string->stringArr);
  free(string);


}

void initialiseHashString(hash_string_t* string)
{
  
  string->size = -1;
  string->stringArr = malloc(sizeof(string -> stringArr)*0);
  string->sum = -1;

}

void getString(hash_string_t* string)
{
  char c;
  int j = 0;

  // For each char in each word
  while((c = getchar()))
  {
    if(c == '\n' || c == ' ')
    {
      break;
    }
    string->stringArr = realloc(string->stringArr, sizeof(char*)*(j+1));
    string->stringArr[j] = c;
    j++;

  }

  string->size = j;


}


// Returns array of hash and string length;
void calculateHash(hash_string_t *string, int m)
{
  int k, sum = 0;

  getString(string);

  sum = characterMapping(string -> stringArr[0]);


  for(k = 1; k < string->size; k++)
  {
    sum = ((sum*64%m)+characterMapping(string -> stringArr[k])%m );
  }
  sum = sum%m;


  string->sum = sum;

}


int characterMapping(char c)
{
  
  if(isLower(c))
  {
    c = c - 'a';
  }
  else if (isUpper(c))
  {
    c = c - 'A' + 26;
  
  }
  else
  {
    c = c + 4;
  }
  
  return c;
}


int isLower(char c)
{
  if(c >= 'a' && c <= 'z')
  {
    return true;
  }
  return false;

}

int isUpper(char c)
{
  if(c >= 'A' && c <= 'Z')
  {
    return true;
  }
  return false;
}


// Implements a solution to Problem 1 (b), which reads in from stdin:
//   N M K
//   str_1
//   str_2
//   ...
//   str_N
// Each string is inputed (in the given order) into a hash table with size
// M. The collision resolution strategy must be linear probing with step
// size K. If an element cannot be inserted then the table size should be
// doubled and all elements should be re-hashed (in index order) before
// the element is re-inserted.
//
// This function must output the state of the hash table after all insertions
// are performed, in the following format
//   0: str_k
//   1:
//   2: str_l
//   3: str_p
//   4:
//   ...
//   (M-2): str_q
//   (M-1):
void problem_1_b() {
  // TODO: Implement Me!
  // TODO: scanf saftety checks
  int n, m, k, i, j;
  
  hash_string_t* hash_table;

  hash_string_t *string = malloc(sizeof(*string));

  initialiseHashString(string);
  


  scanf("%d %d %d\n", &n, &m, &k);
  hash_table = malloc(sizeof(hash_string_t)*m);
  int* indexes = malloc(sizeof(int)*n);

  for(i = 0; i < m ; i++ )
  {

    hash_table[i].size = string->size;
    for(j = 0; j < hash_table[i].size; j++)
    {
      hash_table[i].stringArr[j] = string->stringArr[j];
    }
    hash_table[i].sum = string->sum;

  }


  for(i = 0; i < n; i++)
  {
    calculateHash(string, m);
    indexes[i] = string->sum;

    if(hash_table[string->sum].size == -1)
    {
      hash_table[string->sum].size = string->size;
      hash_table[string->sum].stringArr = malloc(sizeof(char)*string->size);
      for(j = 0; j < string->size; j++)
      {
        
        hash_table[string->sum].stringArr[j] = string->stringArr[j];
      }
      hash_table[string->sum].sum = string->sum;
    }
      

  }
  
  //pscp *.c *.h tests/*.txt Makefile emarozzi@dimefox.eng.unimelb.edu.au:COMP20007/A2/
  

  
  for(i = 0; i < n; i++)
  {
    print_string(hash_table[indexes[i]]);
    free(hash_table[indexes[i]].stringArr);
  }


  free(string->stringArr);
  free(hash_table);
  free(string);
  free(indexes);
}

void print_string(hash_string_t string)
{
  int i;

  for(i = 0 ; i < string.size ; i++)
  {
    printf("%c", string.stringArr[i]);
  }

  printf("\n");


}

