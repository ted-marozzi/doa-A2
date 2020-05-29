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


// Implements a solution to Problem 1 (a), which reads in from stdin:
//   N M
//   str_1
//   str_2
//   ...
//   str_N
// And outputs (to stdout) the hash values of the N strings 1 per line.
void problem_1_a() {
  // TODO: Implement Me!
	int n, m;
  char c;
  scanf("%d %d\n", &n, &m);
  
  printf("%d %d\n", n, m);
  while((c = getchar()))
  {
    if(c == '\n' || c == ' ')
    {
      break;
    }
    printf("%d\n", characterMapping(c));


  }

  printf("End");
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
}
