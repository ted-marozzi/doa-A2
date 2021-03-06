/* * * * * * *
 * Text Analysis module for Assignment 2.
 *
 * created for COMP20007 Design of Algorithms 2020
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by <Insert Name Here>
 */

#ifndef TEXT_ANALYSIS_H
#define TEXT_ANALYSIS_H
#define NUM_CHARS 27
#define MAX_SIZE 100
#include <stdbool.h>
#include <stddef.h>

struct Trie_node
{
    struct Trie_node* character[NUM_CHARS];
    char c;
    int freq;

};

struct Str_prob
{
    double prob;
    char string[MAX_SIZE];

};



typedef struct Trie_node trie_node_t;
typedef struct Str_prob str_prob_t;


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
void problem_2_a();

trie_node_t* create_trie_node(char c);
void assertPtr(void* ptr);
void insert_string(trie_node_t* root, char* string);
void insert_char(char c, char *string, int* len);
void free_trie(trie_node_t *root);
void pre_order_trieversal(trie_node_t* root);

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
void problem_2_b();

void get_prefix_util(trie_node_t *root, int strLen, int* level, char* string);
void get_prefix(trie_node_t *root, int strLen);

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
void problem_2_c();
bool append_char(char** string, char c, int *j);
char* get_string();
trie_node_t* traverse_to(trie_node_t* root, char* stub);
void get_freq(trie_node_t *root, char* string, int* level, int* num_strings, int* sum_freq, char* stub, str_prob_t* str_prob_arr);
void merge(void *out, const void *pa, size_t na, const void *pb, size_t nb, size_t elem_size, 
                    int (*cmp)(const void *, const void *));
void merge_sort(void *base, size_t n_memb, size_t elem_size, int (*cmp)(const void *, const void *));
int prob_comp(const void* a, const void* b);
#endif
