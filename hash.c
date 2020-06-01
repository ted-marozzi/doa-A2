/* * * * * * *
 * Hashing module for Assignment 2.
 *
 * created for COMP20007 Design of Algorithms 2020
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by <Insert Name Here>
 */


//pscp *.c *.h Makefile emarozzi@dimefox.eng.unimelb.edu.au:COMP20007/A2/


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
  init_h_string(h_string);
  scanf("%d %d\n", &n, &m);
  // For each word
  
  for(i = 0; i < n ; i++)
  {
    get_string(h_string);
    calculate_hash(h_string, m);
    printf("%d\n", h_string->sum);
  }
  

  free(h_string->string_arr);
  free(h_string);


}

void init_h_string(h_string_t* h_string)
{
  
  h_string->size = -1;
  h_string->string_arr = NULL;
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

    if(h_string->string_arr == NULL)
    {
      h_string->string_arr = malloc(sizeof(char)*(j+1));
    }
    else
    {
      h_string->string_arr = realloc(h_string->string_arr, sizeof(char)*(j+1));
    }
    
    
    h_string->string_arr[j] = c;
    j++;

  }

  h_string->size = j;


}


// Returns array of hash and h_string length;
void calculate_hash(h_string_t *h_string, int m)
{
  int k, sum = 0;
    

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
  int n, m, k, i;
  
  h_string_t* hash_table;

  h_string_t *h_string = malloc(sizeof(*h_string));

  init_h_string(h_string);
  


  scanf("%d %d %d\n", &n, &m, &k);
  hash_table = malloc(sizeof(h_string_t)*m);


  for(i = 0; i < m ; i++ )
  {
    init_h_string(&hash_table[i]);
  }


  for(i = 0; i < n; i++)
  {
    get_string(h_string);
    
    hash_table = h_insert(hash_table, h_string, i, &m, k);

  }

  print_hash_table(hash_table, m);
  free(h_string->string_arr);
  free(h_string);

  for(i = 0 ; i< m; i++)
  {
    if(hash_table[i].string_arr != NULL)
    {
      free(hash_table[i].string_arr);
    }
    
  }

  free(hash_table);
  



}

void print_hash_table(h_string_t* hash_table, int m)
{
  for(int i = 0; i<m ; i++)
  {
    printf("%d: ", i);

    print_string(hash_table[i]);
  }

  printf("\n");


}

h_string_t* h_insert(h_string_t* hash_table, h_string_t* h_string, int i, int* m, int k)
{
  int trys = 1;
  

  calculate_hash(h_string, *m);
    


  while(true)
  {

    if(hash_table[h_string->sum].string_arr == NULL)
    {
  
      copy_h_string(&hash_table[h_string->sum], h_string);
      



      break;
      
    }
    // Check if next key is empty if not 
    else if(hash_table[(h_string->sum+k*trys)%*m].string_arr == NULL)
    {

      copy_h_string(&hash_table[(h_string->sum+k*trys)%*m], h_string);
      hash_table[(h_string->sum+k*trys)%*m].sum = (h_string->sum+k*trys)%*m;


      
      break;
    }
    else if((h_string->sum+k*trys)%*m == h_string->sum)
    {
      

      *m = 2 * (*m);
      hash_table = rehash(hash_table, i , m , k);

      h_insert(hash_table, h_string, i, m, k);

      
      break;
    }
    
    
    trys++;

  }

  return hash_table;
  
}

h_string_t* rehash(h_string_t* hash_table, int i, int* m , int k)
{
  int j, l = 0;
  h_string_t* h_strings = malloc(sizeof(h_string_t)**m/2);

  for(int j = 0; j < (*m)/2 ; j++)
  { 
    init_h_string(&h_strings[j]);

 
  }

  for(j = 0; j<*m/2; j++)
  {
    
    if(hash_table[j].string_arr!=NULL)
    {
      
     
      copy_h_string(&h_strings[l], &hash_table[j]);
      l++;
    }

  }


  for(j = 0; j<*m/2; j++)
  {
    free(hash_table[j].string_arr);
    //initialise_h_string(&hash_table[j]);
  }

  hash_table = realloc(hash_table, sizeof(h_string_t)**m);

  for(j=0; j< *m; j++)
  {
    init_h_string(&hash_table[j]);
  }

  for(j = 0 ; j < l; j++)
  {
    h_insert(hash_table, &h_strings[j], j, m, k);

  }

  for(j = 0; j<*m/2; j++)
  {
    
    if(h_strings[j].string_arr!=NULL)
    {
      free(h_strings[j].string_arr);
    }

  }

  free(h_strings);


  return hash_table;
}





void print_string(h_string_t h_string)
{
  int i;
  
  if(h_string.string_arr != NULL)
  {
    for(i = 0 ; i < h_string.size ; i++)
    {
      printf("%c", h_string.string_arr[i]);
    }
  }
      
  printf("\n");


}

void copy_h_string(h_string_t* h_string, h_string_t* h_string_old)
{
  
  if(h_string->string_arr == NULL)
  {
    h_string->string_arr = malloc(sizeof(char)*h_string_old->size);
  }
  else
  {
    free(h_string->string_arr);
    h_string->string_arr = malloc(sizeof(char)*h_string_old->size);
  }
  

  
  

  h_string->size = h_string_old->size;

  for(int j = 0; j < h_string_old->size; j++)
  {
    h_string->string_arr[j] = h_string_old->string_arr[j];
  }
  h_string->sum = h_string_old->sum;
  
}

