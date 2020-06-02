/* * * * * * *
 * Text Analysis module for Assignment 2.
 *
 * created for COMP20007 Design of Algorithms 2020
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by <Insert Name Here>
 */

#include "text_analysis.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_STRING_SIZE 100
#define ROOT_NODE_CHAR '^'
#define LEAF_NODE_CHAR '$'
#define FIRST_LETTER 0
#define EOS_INDEX 0
#define LETTER_OFFSET 'a'
#define CHAR_TO_INDEX(c) ((int)c - (int)'a' + 1)
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
  // TODO: remove magic numbers
  // FILL in header

  int n;
  int numScanned = scanf("%d\n", &n);
  // checks that the number of strings is read correctly
  if (numScanned != 1)
  {
    printf("Invalid input\n");
    exit(EXIT_FAILURE);
  }

  trie_node_t *root = create_trie_node(ROOT_NODE_CHAR);

  // Not dynamically associating memory as only one temp variable so its not
  // necassary to save memory in this case.
  char string[100];

  for (int i = 0; i < n; i++)
  {
    fgets(string, MAX_STRING_SIZE, stdin);
    string[strlen(string) - 1] = LEAF_NODE_CHAR;
    insert_string(root, string);
  }


  pre_order_trieversal(root);


  free_trie(root);
}

void pre_order_trieversal(trie_node_t *root)
{

  if (root == NULL)
  {
    return;
  }

  /* first print data of node */
  printf("%c\n", root->c);

  /* then recur on left sutree */
  for (int i = 0; i < NUM_CHARS; i++)
  {
    if (root->character[i] != NULL)
    {
      pre_order_trieversal(root->character[i]);
    }
  }
}

void free_trie(trie_node_t *root)
{
  int i = 0;

  if (!root)
  {

    return;
  }
  for (i = 0; i < NUM_CHARS; i++)
  {
    free_trie(root->character[i]);
  }

  free(root);
}

// Inserts a string into the char trie
void insert_string(trie_node_t *root, char *string)
{

  trie_node_t *node_crawler = root;
  int index;
  for (int i = 0; i < strlen(string); i++)
  {
    node_crawler->freq++;
    if (string[i] == LEAF_NODE_CHAR)
    {
      index = EOS_INDEX;
    }
    else
    {
      index = CHAR_TO_INDEX(string[i]);
    }

    if (!node_crawler->character[index])
    {
      node_crawler->character[index] = create_trie_node(string[i]);
    }

    node_crawler = node_crawler->character[index];
  }
  node_crawler->freq++;
}

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

  int n;
  int numScanned = scanf("%d %d\n", &n);
  // checks that the number of strings is read correctly
  if (numScanned != 2)
  {
    printf("Invalid input\n");
    exit(EXIT_FAILURE);
  }

  trie_node_t *root = create_trie_node(ROOT_NODE_CHAR);

  // Not dynamically associating memory as only one temp variable so its not
  // necassary to save memory in this case.
  char string[100];

  for (int i = 0; i < n; i++)
  {
    fgets(string, MAX_STRING_SIZE, stdin);
    string[strlen(string) - 1] = LEAF_NODE_CHAR;
    insert_string(root, string);
  }


  pre_order_trieversal(root);


  free_trie(root);
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
  // TODO: Implement Me!
}
