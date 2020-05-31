/* * * * * * *
 * Hashing module for Assignment 2.
 *
 * created for COMP20007 Design of Algorithms 2020
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by <Insert Name Here>
 */


//pscp *.c *.h tests/*.txt Makefile emarozzi@dimefox.eng.unimelb.edu.au:COMP20007/A2/


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
  h_string_t* h_string = malloc(sizeof(*h_string));
  int n, m, i;
  initialise_h_string(h_string);
  scanf("%d %d\n", &n, &m);
  // For each word
  
  for(i = 0; i < n ; i++)
  {
    calculate_hash(h_string, m);
    printf("%d\n", h_string->sum);
  }
  

  free(h_string->string_arr);
  free(h_string);


}

void initialise_h_string(h_string_t* h_string)
{
  
  h_string->size = -1;
  h_string->string_arr = malloc(sizeof(h_string -> string_arr)*0);
  h_string->sum = -1;

}

void get_string(h_string_t* h_string)
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
    h_string->string_arr = realloc(h_string->string_arr, sizeof(char*)*(j+1));
    h_string->string_arr[j] = c;
    j++;

  }

  h_string->size = j;


}


// Returns array of hash and h_string length;
void calculate_hash(h_string_t *h_string, int m)
{
  int k, sum = 0;

  get_string(h_string);

  sum = character_mapping(h_string -> string_arr[0]);


  for(k = 1; k < h_string->size; k++)
  {
    sum = ((sum*64%m)+character_mapping(h_string -> string_arr[k])%m );
  }
  sum = sum%m;


  h_string->sum = sum;

}


int character_mapping(char c)
{
  
  if(is_lower(c))
  {
    c = c - 'a';
  }
  else if (is_upper(c))
  {
    c = c - 'A' + 26;
  
  }
  else
  {
    c = c + 4;
  }
  
  return c;
}


int is_lower(char c)
{
  if(c >= 'a' && c <= 'z')
  {
    return true;
  }
  return false;

}

int is_upper(char c)
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
// Each h_string is inputed (in the given order) into a hash table with size
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
  
  h_string_t* hash_table;

  h_string_t *h_string = malloc(sizeof(*h_string));

  initialise_h_string(h_string);
  


  scanf("%d %d %d\n", &n, &m, &k);
  hash_table = malloc(sizeof(h_string_t)*m);
  int* indexes = malloc(sizeof(int)*n);

  for(i = 0; i < m ; i++ )
  {

    copy_h_string(&hash_table[i], h_string);

  }


  for(i = 0; i < n; i++)
  {
    calculate_hash(h_string, m);
    indexes[i] = h_string->sum;

    if(hash_table[h_string->sum].size == -1)
    {
      hash_table[h_string->sum].size = h_string->size;
      hash_table[h_string->sum].string_arr = malloc(sizeof(char)*h_string->size);
      for(j = 0; j < h_string->size; j++)
      {
        
        hash_table[h_string->sum].string_arr[j] = h_string->string_arr[j];
      }
      hash_table[h_string->sum].sum = h_string->sum;
    }
      

  }
  

  
  for(i = 0; i < n; i++)
  {
    print_string(hash_table[indexes[i]]);
    free(hash_table[indexes[i]].string_arr);
  }


  free(h_string->string_arr);
  free(hash_table);
  free(h_string);
  free(indexes);
}

void print_string(h_string_t h_string)
{
  int i;

  for(i = 0 ; i < h_string.size ; i++)
  {
    printf("%c", h_string.string_arr[i]);
  }

  printf("\n");


}

void copy_h_string(h_string_t* h_string, h_string_t* h_string_old)
{
  int j;
  h_string->size = h_string_old->size;

  for(j = 0; j < h_string_old->size; j++)
  {
    h_string->string_arr[j] = h_string_old->string_arr[j];
  }
  h_string->sum = h_string_old->sum;
  
}

