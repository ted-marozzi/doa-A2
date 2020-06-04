/* * * * * * *
 * Hashing module for Assignment 2.
 *
 * created for COMP20007 Design of Algorithms 2020
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by Edward Marozzi - 910193
 */
#include "hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stddef.h>
#define POW2_6 64
#define CHAR_OFFSET 26

// Implements a solution to Problem 1 (a), which reads in from stdin:
//   N M
//   str_1
//   str_2
//   ...
//   str_N
// And outputs (to stdout) the hash values of the N strings 1 per line.
void problem_1_a()
{
  // Used as a temp variable to copy data between strings;
  h_string_t *h_string = malloc(sizeof(*h_string));
  int n, m, i;
  init_h_string(h_string);
  scanf("%d %d\n", &n, &m);

  // For each word
  for (i = 0; i < n; i++)
  {
    // Get the string from std in
    get_h_string(h_string);
    // Calculate its hash value
    calculate_hash(h_string, m);
    // Print the result
    printf("%d\n", h_string->key);
  }
  // Clean up
  free_h_string(h_string);
}

// frees a hash string and its characters
void free_h_string(h_string_t *h_string)
{
  if (h_string->string_arr != NULL)
  {
    free(h_string->string_arr);
    free(h_string);
  }
}

// Creates a hash string
void init_h_string(h_string_t *h_string)
{

  h_string->size = -1;
  h_string->string_arr = NULL;
  h_string->key = -1;
}

// gets a string from stdio and puts it in a h_string
void get_h_string(h_string_t *h_string)
{
  char c;
  int j = 0;

  // For each char in each word
  while ((c = getchar()))
  {
    // String ended
    if (c == '\n' || c == ' ')
    {
      break;
    }

    // If string is empty then give it some memory
    if (h_string->string_arr == NULL)
    {
      h_string->string_arr = malloc(sizeof(char) * (j + 1));
    }
    else
    {
      // Dynamically add memory for each chare
      h_string->string_arr = realloc(h_string->string_arr, sizeof(char) * (j + 1));
    }

    h_string->string_arr[j] = c;
    j++;
  }

  h_string->size = j;
}

void assertPtr(void* ptr)
{
  if(ptr == NULL)
  {
    printf("Pointer assertion failed\n");
    exit(EXIT_FAILURE);
  }
}

// Returns array of hash and h_string length;
void calculate_hash(h_string_t *h_string, int m)
{
  int k, sum = 0;

  sum = character_mapping(h_string->string_arr[0]);

  for (k = 1; k < h_string->size; k++)
  {
    sum = ((sum * POW2_6 % m) + character_mapping(h_string->string_arr[k]) % m);
  }
  sum = sum % m;

  h_string->key = sum;
}

// Calculates the value of a character
int character_mapping(char c)
{
  // Follows the key given to us
  if (is_lower(c))
  {
    c = c - 'a';
  }
  else if (is_upper(c))
  {
    c = c - 'A' + CHAR_OFFSET;
  }
  else
  {
    c = c + 4;
  }

  return c;
}

// checks if lower case
int is_lower(char c)
{
  if (c >= 'a' && c <= 'z')
  {
    return true;
  }
  return false;
}

// checks if upper case
int is_upper(char c)
{
  if (c >= 'A' && c <= 'Z')
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
void problem_1_b()
{
  int n, m, k, i;

  h_string_t *hash_table;

  h_string_t *h_string = malloc(sizeof(*h_string));

  init_h_string(h_string);

  // n is num of strings, m is inital table size, k is step size
  int numScan = scanf("%d %d %d\n", &n, &m, &k);

  if (numScan != 3)
  {
    printf("Invalid input\n");
    exit(EXIT_FAILURE);
  }

  hash_table = malloc(sizeof(h_string_t) * m);
  assertPtr(hash_table);

  // Fills each h_string with null for memory safety checks
  for (i = 0; i < m; i++)
  {
    init_h_string(&hash_table[i]);
  }

  // For each string simply get it then insert it
  for (i = 0; i < n; i++)
  {
    get_h_string(h_string);

    hash_table = h_insert(hash_table, h_string, i, &m, k);
  }

  // Print the new hash table
  print_hash_table(hash_table, m);

  // Clean up
  free_h_string(h_string);

  for (i = 0; i < m; i++)
  {

    if (hash_table[i].string_arr != NULL)
    {
      free(hash_table[i].string_arr);
    }
  }

  free(hash_table);
}

// Self explanitory
void print_hash_table(h_string_t *hash_table, int m)
{
  assertPtr(hash_table);
  for (int i = 0; i < m; i++)
  {
    printf("%d: ", i);

    print_string(hash_table[i]);
  }

  printf("\n");
}

// Prints a h_string
void print_string(h_string_t h_string)
{
  int i;
  // Ensures that if its null it just prints a new line
  if (h_string.string_arr != NULL)
  {
    for (i = 0; i < h_string.size; i++)
    {
      printf("%c", h_string.string_arr[i]);
    }
  }

  printf("\n");
}

// Recursively inserts 1 element, I say recursivly because if a resize is needed
// it calls itselft to insert the elements again
h_string_t *
h_insert(h_string_t *hash_table, h_string_t *h_string, int i, int *m, int k)
{
  int trys = 1;

  // Calculates a strings hash value
  calculate_hash(h_string, *m);

  while (true)
  {
    // If the key is empty copy contents of our h_string place holder to the key spot
    if (hash_table[h_string->key].string_arr == NULL)
    {
      copy_h_string(&hash_table[h_string->key], h_string);
      break;
    }
    // Check if next key to try is empty
    else if (hash_table[(h_string->key + k * trys) % *m].string_arr == NULL)
    {
      copy_h_string(&hash_table[(h_string->key + k * trys) % *m], h_string);
      hash_table[(h_string->key + k * trys) % *m].key = (h_string->key + k * trys) % *m;

      break;
    }
    // If we are back at where we started then we need to resize
    else if ((h_string->key + k * trys) % *m == h_string->key)
    {
      // M needs to get doubled
      *m = 2 * (*m);
      // Re hash resizes the table and re inserts the data
      hash_table = rehash(hash_table, i, m, k);
      // Finally we recursivly call h_insert to make sure we put the value
      // in the right spot.
      h_insert(hash_table, h_string, i, m, k);

      break;
    }
    // Insertion trys
    trys++;
  }
  // Returns the table
  return hash_table;
}

// Re sizes/ rehashes
h_string_t *rehash(h_string_t *hash_table, int i, int *m, int k)
{
  int j, l = 0;
  h_string_t *h_strings = malloc(sizeof(h_string_t) * *m / 2);

  for (int j = 0; j < (*m) / 2; j++)
  {
    init_h_string(&h_strings[j]);
  }

  // Fill h_strings temporarly with the h_strings
  for (j = 0; j < *m / 2; j++)
  {
    // Copy the data over if its not null
    if (hash_table[j].string_arr != NULL)
    {
      copy_h_string(&h_strings[l], &hash_table[j]);
      l++;
    }
  }

  // Clean up hash table before realloc
  for (j = 0; j < *m / 2; j++)
  {
    free(hash_table[j].string_arr);
  }

  // resize hash table
  hash_table = realloc(hash_table, sizeof(h_string_t) * *m);

  for (j = 0; j < *m; j++)
  {
    init_h_string(&hash_table[j]);
  }

  // Insert all the old data in the correct order
  for (j = 0; j < l; j++)
  {
    h_insert(hash_table, &h_strings[j], j, m, k);
  }

  // Memory clean up
  for (j = 0; j < *m / 2; j++)
  {

    if (h_strings[j].string_arr != NULL)
    {
      free(h_strings[j].string_arr);
    }
  }

  free(h_strings);

  return hash_table;
}

// Copies contents of old string to new string, this is a deep copy,
// after the operaton the two strings are not intangles
void copy_h_string(h_string_t *h_string, h_string_t *h_string_old)
{

  // Assign memory if needed
  if (h_string->string_arr == NULL)
  {
    h_string->string_arr = malloc(sizeof(char) * h_string_old->size);
  }
  else
  {
    free(h_string->string_arr);
    h_string->string_arr = malloc(sizeof(char) * h_string_old->size);
  }
  // Copy data
  h_string->size = h_string_old->size;

  for (int j = 0; j < h_string_old->size; j++)
  {
    h_string->string_arr[j] = h_string_old->string_arr[j];
  }
  h_string->key = h_string_old->key;
}
