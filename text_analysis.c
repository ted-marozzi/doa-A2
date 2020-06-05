/* * * * * * *
 * Text Analysis module for Assignment 2.
 *
 * created for COMP20007 Design of Algorithms 2020
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by Edward Marozzi
 */

#include "text_analysis.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

#define MAX_STRING_SIZE 100
#define ROOT_NODE_CHAR '^'
#define LEAF_NODE_CHAR '$'
#define FIRST_LETTER 0
#define EOS_INDEX 0
#define LETTER_OFFSET 'a'
#define CHAR_TO_INDEX(c) ((int)c - (int)'a' + 1)
#define NUM_PARAMS_A 1
#define NUM_PARAMS_B 2
#define EOS '\0'
#define MAX_STRINGS 5

// Build a character level trie for a given set of words.
//
// The input to your program is an integer N followed by N lines containing
// words of length < 100 characters, containing only lowercase letters.
//
// Your program should built a character level trie where each node indicates
// a single character. Branches should be ordered in alphabetic order.
//
// Your program must output the pre-order traversal of the characters in
// the trie, on a single line.
void problem_2_a()
{
  int n;
  int numScanned = scanf("%d\n", &n);
  // checks that the number of strings is read correctly
  if (numScanned != NUM_PARAMS_A)
  {
    printf("Invalid input\n");
    exit(EXIT_FAILURE);
  }

  // Creates a trie_node
  trie_node_t *root = create_trie_node(ROOT_NODE_CHAR);

  // Not dynamically associating memory as only one temp variable so its not
  // necassary to save memory in this case.
  char string[MAX_STRING_SIZE];

  // For each string add it to the trie
  for (int i = 0; i < n; i++)
  {
    fgets(string, MAX_STRING_SIZE, stdin);
    string[strlen(string) - 1] = LEAF_NODE_CHAR;
    insert_string(root, string);
  }

  // trieverse the trie
  pre_order_trieversal(root);

  // Clean up recursivly
  free_trie(root);
}

// Prints the preorder traversal of trie
void pre_order_trieversal(trie_node_t *root)
{
  // Exit condition
  if (root == NULL)
  {
    return;
  }
  // Print the roots char as it is visited
  printf("%c\n", root->c);


  // For each char traverse to child char in alphabetical order
  for (int i = 0; i < NUM_CHARS; i++)
  {
    // If a char is not null traverse to it
    if (root->character[i] != NULL)
    {
      pre_order_trieversal(root->character[i]);
    }
  }
  // Returns back a node
}

// Frees the trie recurisevly
void free_trie(trie_node_t *root)
{
  int i = 0;

  // Exit condition
  if (!root)
  {
    return;
  }
  // Recursive call
  for (i = 0; i < NUM_CHARS; i++)
  {
    free_trie(root->character[i]);
  }
  // Base case
  free(root);
}

// Inserts a string into the char trie
void insert_string(trie_node_t *root, char *string)
{

  trie_node_t *node_crawler = root;
  int index;

  // For each char in string
  for (int i = 0; i < strlen(string); i++)
  {
    // Increase the frequency
    node_crawler->freq++;
    // Assign appropriate index
    if (string[i] == LEAF_NODE_CHAR)
    {
      // End of string
      index = EOS_INDEX;
    }
    else
    {
      // Converts to an index
      index = CHAR_TO_INDEX(string[i]);
    }

    // Create a node if the spot is null
    if (!node_crawler->character[index])
    {
      node_crawler->character[index] = create_trie_node(string[i]);
    }
    // Next node
    node_crawler = node_crawler->character[index];
  }

  node_crawler->freq++;
}

// Constructs a memory safe trie_node
trie_node_t *create_trie_node(char c)
{
  trie_node_t *trie_node = (trie_node_t *)malloc(sizeof(trie_node_t));
  trie_node->c = c;
  for (int i = 0; i < NUM_CHARS; i++)
  {
    trie_node->character[i] = NULL;
  }

  trie_node->freq = 0;

  return trie_node;
}

// Using the trie constructed in Part (a) this program should output all
// prefixes of length K, in alphabetic order along with their frequencies
// with their frequencies. The input will be:
//   n k
//   str_0
//   ...
//   str_(n-1)
// The output format should be as follows:
//   an 3
//   az 1
//   ba 12
//   ...
//   ye 1
void problem_2_b()
{

  int n, str_len;
  int num_scanned = scanf("%d %d\n", &n, &str_len);
  // Checks that the number of strings is read correctly
  if (num_scanned != NUM_PARAMS_B)
  {
    printf("Invalid input\n");
    exit(EXIT_FAILURE);
  }

  trie_node_t *root = create_trie_node(ROOT_NODE_CHAR);

  // Not dynamically associating memory as only one temp variable so its not
  // necassary to save memory in this case. We were told a maximum of 100 chars
  char string[100];

  // Construts the trie
  for (int i = 0; i < n; i++)
  {
    // Gets a string from stdin
    fgets(string, MAX_STRING_SIZE, stdin);
    // Replaces new line char with '$' char to mark end of word
    string[strlen(string) - 1] = LEAF_NODE_CHAR;
    // Inserts it
    insert_string(root, string);
  }

  // Gets prefix of length
  get_prefix(root, str_len);

  // Recursively frees the trie
  free_trie(root);
}

// Used to call a recurive get prexfix of len str_len
void get_prefix(trie_node_t *root, int str_len)
{
  // Tracks which level we are on
  int level = 0;
  char *string = malloc(sizeof(char) * str_len);
  // Recursive call
  get_prefix_util(root, str_len, &level, string);

  free(string);
}

void get_prefix_util(trie_node_t *root, int str_len, int *level, char *string)
{
  // Exit condition
  if (root == NULL)
  {
    return;
  }
  // If the current levelis not on the root char but less than the str_len
  // and the current char isn't a leaf char then insert it into the array
  if ((*level) <= str_len && (*level) > 0 && root->c != LEAF_NODE_CHAR)
  {
    string[(*level) - 1] = root->c;
  }

  // If we are at the level of str_len and the current node isnt a leaf node
  // Print out resulting string and freq
  if ((*level) == str_len && (root->c) != LEAF_NODE_CHAR)
  {
    for (int i = 0; i < str_len; i++)
    {
      printf("%c", string[i]);
    }
    printf(" %d\n", root->freq);
  }
  // Recursive traversal statement
  for (int i = 0; i < NUM_CHARS; i++)
  {
    if (root->character[i] != NULL)
    {
      (*level)++;
      get_prefix_util(root->character[i], str_len, level, string);
    }
  }
  // When we get here it means that we are going back one level
  (*level)--;
}

// Again using the trie data structure you implemented for Part (a) you will
// provide a list (up to 5) of the most probable word completions for a given
// word stub.
//
// For example if the word stub is "al" your program may output:
//   0.50 algorithm
//   0.25 algebra
//   0.13 alright
//   0.06 albert
//   0.03 albania
//
// The probabilities should be formatted to exactly 2 decimal places and
// should be computed according to the following formula, for a word W with the
// prefix S:
//   Pr(word = W | stub = S) = Freq(word = W) / Freq(stub = S)
//
// The input to your program will be the following:
//   n
//   stub
//   str_0
//   ...
//   str_(n-1)
// That is, there are n + 1 strings in total, with the first being the word
// stub.
//
// If there are two strings with the same probability ties should be broken
// alphabetically (with "a" coming before "aa").
void problem_2_c()
{

  int n;
  int num_strings;
  int numScanned = scanf("%d\n", &n);
  char string[MAX_STRING_SIZE];
  char stub[MAX_STRING_SIZE];
  int level = 0;
  trie_node_t *stub_node = NULL;

  // checks that the number of strings is read correctly
  if (numScanned != NUM_PARAMS_A)
  {
    printf("Invalid input\n");
    exit(EXIT_FAILURE);
  }
  // Creates a trie
  trie_node_t *root = create_trie_node(ROOT_NODE_CHAR);

  // Gets the strings
  fgets(stub, MAX_STRING_SIZE, stdin);
  // Puts in the leaf node char $
  stub[strlen(stub) - 1] = LEAF_NODE_CHAR;

  // For each string add it to the trie
  for (int i = 0; i < n; i++)
  {
    fgets(string, MAX_STRING_SIZE, stdin);
    string[strlen(string) - 1] = LEAF_NODE_CHAR;
    insert_string(root, string);
  }
  // Gets the node of the end of the stub
  stub_node = traverse_to(root, stub);
  // Number of words possible from the stub
  int sum_freq = stub_node->freq;

  // Used to create a string for the get freq recursive call
  char tmp_string[MAX_STRING_SIZE];
  num_strings = 0;

  // Inserst the EOS char '\0' in place of the $
  stub[strlen(stub) - 2] = EOS;
  // Array of structs containg the string and the prob
  str_prob_t *str_prob_arr = malloc(sizeof(str_prob_t) * sum_freq);

  //Initialises the array
  for (int i = 0; i < sum_freq; i++)
  {
    str_prob_arr[i].prob = -1;
    strcpy(str_prob_arr[i].string, "");
  }

  // Recursivly fills out the str_prob_array in alphabetical order
  get_freq(stub_node, tmp_string, &level, &num_strings, &sum_freq, stub,
           str_prob_arr);

  str_prob_t *str_probs = malloc(sizeof(str_prob_t) * num_strings);
  // Trims the array down to the number of unique strings
  for (int i = 0; i < num_strings; i++)
  {
    str_probs[i].prob = str_prob_arr[i].prob;
    strcpy(str_probs[i].string, str_prob_arr[i].string);
  }

  // Normal merge sorting function, stable thus we are now sorted by prob
  //  and then alphabetical
  merge_sort(str_probs, num_strings, sizeof(str_prob_t), prob_comp);

  // Max of 5 elements
  for (int i = 0; i < MAX_STRINGS; i++)
  {

    if (i == num_strings)
    {
      break;
    }
    printf("%.2lf %s\n", str_probs[i].prob, str_probs[i].string);
  }

  // Clean up

  free_trie(root);
  free(str_probs);
  free(str_prob_arr);
}

/* Compares the s data for merge sort */
int prob_comp(const void *a, const void *b)
{
  str_prob_t *ra = (str_prob_t *)a;
  str_prob_t *rb = (str_prob_t *)b;

  /* With double data we can just subtract to get the right behaviour */
  return (ra->prob < rb->prob) - (ra->prob > rb->prob);
}

/* Subroutine to merge two input arrays into an output array. */
void merge(void *out, const void *pa, size_t na, const void *pb,
           size_t nb, size_t elem_size, int (*cmp)(const void *, const void *))
{
  while (na != 0 || nb != 0)
  {
    if (na == 0 || (nb != 0 && cmp(pa, pb) > 0))
    {
      memcpy(out, pb, elem_size);
      pb = (const char *)pb + elem_size;
      nb--;
    }
    else
    {
      memcpy(out, pa, elem_size);
      pa = (const char *)pa + elem_size;
      na--;
    }
    out = (char *)out + elem_size;
  }
}

/* Merge sort an array. Function modified from*/
void merge_sort(void *base, size_t n_memb, size_t elem_size,
                int (*cmp)(const void *, const void *))
{
  size_t n_bottom;
  size_t n_top;
  void *mid_p;
  void *bottom;
  void *top;

  if (n_memb <= 1)
  {
    /* Too small to sort. */
    return;
  }
  /* Sort the bottom half and the top half. */
  n_bottom = n_memb / 2;
  n_top = n_memb - n_bottom;
  mid_p = (char *)base + (n_bottom * elem_size);
  merge_sort(base, n_bottom, elem_size, cmp);
  merge_sort(mid_p, n_top, elem_size, cmp);
  /* Make temporary copies of the sorted bottom half and top half. */
  bottom = malloc(n_bottom * elem_size);
  top = malloc(n_top * elem_size);
  memcpy(bottom, base, n_bottom * elem_size);
  memcpy(top, mid_p, n_top * elem_size);
  /* Do a sorted merge of the copies into the original. */
  merge(base, bottom, n_bottom, top, n_top, elem_size, cmp);
  /* Free temporary copies. */
  free(bottom);
  free(top);
}

// Recursive function to get the frequency probabilities of a trie
void get_freq(trie_node_t *root, char *string, int *level,
               int *num_strings, int *sum_freq, char *stub,
               str_prob_t *str_prob_arr)
{

  // Exit condition
  if (root == NULL)
  {
    return;
  }
  // Add to string
  if (root->c != LEAF_NODE_CHAR)
  {

    string[*level] = root->c;
    string[*level + 1] = EOS;
  }

  // Push results to array
  if (root->c == LEAF_NODE_CHAR)
  {
    char tmp[MAX_STRING_SIZE];
    strcpy(tmp, stub);
    strcat(tmp, string);

    str_prob_arr[(*num_strings)].prob = (float)root->freq / (*sum_freq);
    strcpy(str_prob_arr[(*num_strings)].string, tmp);

    (*num_strings)++;
  }

  // For each char traverse to child char in alphabetical order
  for (int i = 0; i < NUM_CHARS; i++)
  {
    // Go to next char if exists
    if (root->character[i] != NULL)
    {
      (*level)++;
      get_freq(root->character[i], string, level, num_strings, sum_freq, stub, str_prob_arr);
    }
  }
  // Base case goes back one level
  (*level)--;
}

// Returns the last node of the string char assuming it exists in the
//  given char trie
trie_node_t *traverse_to(trie_node_t *root, char *stub)
{
  trie_node_t *node_crawler = root;
  int index;

  // For each letter in stub
  for (int i = 0; i < strlen(stub) - 1; i++)
  {
    // convert to an index
    if (stub[i] == LEAF_NODE_CHAR)
    {
      index = EOS_INDEX;
    }
    else
    {
      index = CHAR_TO_INDEX(stub[i]);
    }
    // Crawl onwards
    node_crawler = node_crawler->character[index];
  }
  // return the node
  return node_crawler;
}
