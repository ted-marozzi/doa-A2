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
#include <stdbool.h>

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
  if (numScanned != NUM_PARAMS_A)
  {
    printf("Invalid input\n");
    exit(EXIT_FAILURE);
  }

  trie_node_t *root = create_trie_node(ROOT_NODE_CHAR);

  // Not dynamically associating memory as only one temp variable so its not
  // necassary to save memory in this case.
  char string[100];

  // For each string add it to the trie
  for (int i = 0; i < n; i++)
  {
    fgets(string, MAX_STRING_SIZE, stdin);
    string[strlen(string) - 1] = LEAF_NODE_CHAR;
    insert_string(root, string);
  }

  // trieverse the trie
  pre_order_trieversal(root);


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
    if (root->character[i] != NULL)
    {
      pre_order_trieversal(root->character[i]);
    }
  }
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
  // Recurisve call
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
      index = EOS_INDEX;
    }
    else
    {
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
  char* string = malloc(sizeof(char)*str_len);
  // Recursive call
  get_prefix_util(root, str_len, &level, string);

  free(string);

}

void get_prefix_util(trie_node_t *root, int str_len, int* level, char* string)
{
  // Exit condition
  if (root == NULL)
  {
    return;
  }
  // If the current levelis not on the root char but less than the str_len
  // and the current char isn't a leaf char then insert it into the array 
  if((*level) <= str_len && (*level) > 0  && root->c != LEAF_NODE_CHAR)
  {
    string[(*level)-1] = root->c;
  }
  
  // If we are at the level of str_len and the current node isnt a leaf node
  // Print out resulting string and freq
  if((*level) == str_len && (root->c) != LEAF_NODE_CHAR)
  {
    for(int i = 0; i < str_len ; i++)
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
  int numScanned = scanf("%d\n", &n);
  char* string = NULL;
  char * stub = NULL;
  trie_node_t* stub_node = NULL;
  str_freq_t* str_freq_arr = malloc(sizeof(str_freq_t));

  // checks that the number of strings is read correctly
  if (numScanned != NUM_PARAMS_A)
  {
    printf("Invalid input\n");
    exit(EXIT_FAILURE);
  }

  trie_node_t *root = create_trie_node(ROOT_NODE_CHAR);
  stub = get_string();
  for( int i = 0 ; i < n; i++)
  {
    string = get_string();
    insert_string(root, string);
       
  }

  stub_node = traverse_to(root, str_freq_arr);

  get_freq(stub_node, stub);



  free(string);
  free(stub);
  free_trie(root);

}

void get_freq(trie_node_t *root, str_freq_t* str_freq_arr)
{
  // Exit condition
  if (root == NULL)
  {
    // Contines searching on the current node to go down a level
    return;
  }
  // Print the roots char as it is visited
  printf("%c\n", root->c);

  // For each char traverse to child char in alphabetical order
  for (int i = 0; i < NUM_CHARS; i++)
  {
    // TODO: Add this effciency upgrade if it works root -> c != LEAF_NODE_CHAR
    if ( root->character[i] != NULL)
    {
      pre_order_trieversal(root->character[i], str_freq_arr);
    }
  }
  // Goes up a level bc at $
  str_freq_t* str_freq_node = create_str_freq_node(root->freq, root->c);
  
}



str_freq_t *create_str_freq_node(int freq, char* string)
{
  str_freq_t *str_freq_node = (str_freq_t *)malloc(sizeof(str_freq_t));
  str_freq_node->freq = freq;
  str_freq_node->string = string;
  return str_freq_node;
}

trie_node_t* traverse_to(trie_node_t* root, char* stub)
{
  trie_node_t *node_crawler = root;
  int index;

  for(int i = 0; i < strlen(stub)-1; i++)
  {
    if (stub[i] == LEAF_NODE_CHAR)
    {
      index = EOS_INDEX;
    }
    else
    {
      index = CHAR_TO_INDEX(stub[i]);
    }
    node_crawler = node_crawler->character[index];
  }
  return node_crawler;

}


char* get_string()
{

  char c;
  char* string = NULL;
  int j = 0;
  bool isEnd = false;

  // For each char in each word
  while (!isEnd)
  {
    c = getchar();
    isEnd = append_char(&string, c, &j);
  }

  append_char(&string, LEAF_NODE_CHAR, &j);
  append_char(&string, EOS, &j);

  return string;
}

bool append_char(char** string, char c, int* j)
{

  // String ended
  if (c == '\n' || c == ' ')
  {
    return true;
  }

  // If string is empty then give it some memory
  if (*string == NULL)
  {
    *string = malloc(sizeof(char) * (*j + 1));
  }
  else
  {
    // Dynamically add memory for each chare
    *string = realloc(*string, sizeof(char) * (*j + 1));
  }

  (*string)[*j] = c;
  (*j)++;

  return false;
}


