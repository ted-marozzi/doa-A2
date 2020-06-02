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
void problem_2_a() {
  // TODO: remove magic numbers
  
  int n;
  int numScanned = scanf("%d\n", &n);
  // checks that the number of strings is read correctly
  if(numScanned != 1)
  {
    printf("Invalid input\n");
    exit(EXIT_FAILURE);
  }

  trie_node_t* root = create_trie_node('a');
  char string[100];


  for(int i = 0; i < n ; i++)
  {
    fgets(string, 100, stdin);
    printf("%s\n", string);
    insert_string(root, string);
  }

  free(root);


}

char* get_string()
{
  char c;
  char string[] = "";
  int len = 0;

  while ((c = getchar()))
  {
    // String ended
    if (c == '\n' || c == ' ' || c == EOF)
    {
      //insert_char('\0', &string, &len);
      break;
    }

    strncat(string, &c, 1);
    //insert_char(c, &string, &len);

    // len++;

    // if(string == NULL)
    // {
    //   string = malloc(sizeof(char)*len);
    // }
    // else
    // {
    //   string = realloc(string, sizeof(char)*len);
    // }
    
    // assertPtr(string);

    // string[len-1] = c;
  }


  return string;
}

// void insert_char(char c, char *string, int* len)
// {
//   (*len)++;

//   if(string == NULL)
//   {
//     string = malloc(sizeof(char)*(*len));
//     string[(*len)-1] = NULL;
//   }
//   else
//   {
//     string = realloc(string, sizeof(char)*(*len));
//     string[(*len)-1] = NULL;
//   }
  
//   assertPtr(string);

//   string[(*len)-1] = c;

// }

// void assertPtr(void* ptr)
// {
//   if(ptr == NULL)
//   {
//     printf("Pointer assertion failed\n");
//     exit(EXIT_FAILURE);
//   }
// }

void insert_string(trie_node_t* root, char* string)
{


}



trie_node_t* create_trie_node(char c)
{
  trie_node_t* trie_node = (trie_node_t*)malloc(sizeof(trie_node_t));
  trie_node->c = c;
  for(int i =0; i<NUM_CHARS; i++)
  {
    trie_node->character[i] = NULL; 
  }

  trie_node->freq = 1;

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
void problem_2_b() {
  // TODO: Implement Me!
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
void problem_2_c() {
  // TODO: Implement Me!
}
