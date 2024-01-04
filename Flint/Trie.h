// Trie.h
#ifndef TRIE_H
#define TRIE_H

#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26  // Number of characters in the English alphabet

typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    struct TrieNode *parent;
    int isEndOfWord;
} TrieNode;

TrieNode *createNode(void);
void insert(TrieNode *root, const char *key);
void deleteTrie(TrieNode *root);

#endif // TRIE_H
