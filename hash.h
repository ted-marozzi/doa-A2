/* * * * * * *
 * Hashing module for Assignment 2.
 *
 * created for COMP20007 Design of Algorithms 2020
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by <Insert Name Here>
 */

#ifndef HASH_H
#define HASH_H

// hash string structure
typedef struct
{
    char* string_arr;
    int size;
    int key;

} h_string_t;


// Implements a solution to Problem 1 (a), which reads in from stdin:
//   N M
//   str_1
//   str_2
//   ...
//   str_N
// And outputs (to stdout) the hash values of the N strings 1 per line.

// Hash string functions
void problem_1_a();
int is_lower(char c);
int is_upper(char c);
int character_mapping(char c);
void calculate_hash(h_string_t* h_string, int m);
void init_h_string();
void free_h_string(h_string_t* h_string);


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

// More hash string functions
void problem_1_b();
void print_string(h_string_t h_string);
void copy_h_string(h_string_t *h_string, h_string_t *h_string_old);
void get_h_string(h_string_t* h_string);
h_string_t* rehash(h_string_t* hash_table, int i, int* m, int k);
h_string_t* h_insert(h_string_t* hash_table, h_string_t* h_string, int i, int *m, int k);
void print_hash_table(h_string_t* hash_table, int m);
void init_h_table(h_string_t* h_table, int size);
void free_h_table(h_string_t* h_table, int size);
void free_h_string(h_string_t* h_string);
void assertPtr(void* ptr);

#endif
