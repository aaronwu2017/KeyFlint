// Trie.c
#include "Trie.h"

TrieNode *createNode(int level) {
    TrieNode *newNode = malloc(sizeof(TrieNode));
    if (newNode) {
        int i;
        newNode->isEndOfWord = 0;
        newNode->level = level; 
        for (i = 0; i < 26; i++) {
            newNode->children[i] = NULL;
        }
    }
    return newNode;
}

void insert(TrieNode *root, const char *key) {
    int level;
    int length = strlen(key);
    int index;

    TrieNode *pCrawl = root;

    for (level = 0; level < length; level++) {
        index = key[level] - 'a';
        if (!pCrawl->children[index]) {
            pCrawl->children[index] = createNode(pCrawl->level + 1);
            pCrawl->children[index]->parent = pCrawl;
        }
        pCrawl = pCrawl->children[index];
    }

    pCrawl->isEndOfWord = 1;
}

void deleteTrie(TrieNode *root) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        deleteTrie(root->children[i]);
    }
    free(root);
}

