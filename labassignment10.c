#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26 // Assuming only lowercase English letters

// Trie node structure
struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int count; // Counts occurrences of words that terminate at this node
};

// Trie structure
struct Trie {
    struct TrieNode *root;
};

// Function to create a new trie node
struct TrieNode *createTrieNode() {
    struct TrieNode *pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (pNode) {
        pNode->count = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            pNode->children[i] = NULL;
        }
    }
    return pNode;
}

// Initializes a trie structure
struct Trie *createTrie() {
    struct Trie *pTrie = (struct Trie *)malloc(sizeof(struct Trie));
    if (pTrie) {
        pTrie->root = createTrieNode();
    }
    return pTrie;
}

// Inserts the word into the trie structure
void insert(struct Trie *pTrie, char *word) {
    struct TrieNode *pNode = pTrie->root;
    while (*word) {
        int index = *word - 'a';
        if (!pNode->children[index]) {
            pNode->children[index] = createTrieNode();
        }
        pNode = pNode->children[index];
        word++;
    }
    pNode->count++; // Mark the end of a word and increase its occurrence count
}

// Computes the number of occurrences of the word
int numberOfOccurances(struct Trie *pTrie, char *word) {
    struct TrieNode *pNode = pTrie->root;
    while (*word) {
        int index = *word - 'a';
        if (!pNode->children[index]) {
            return 0; // Word does not exist
        }
        pNode = pNode->children[index];
        word++;
    }
    return pNode->count; // Return the count of the word at the end node
}

// Deallocate the trie structure recursively
void deallocateTrieNode(struct TrieNode *pNode) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (pNode->children[i]) {
            deallocateTrieNode(pNode->children[i]);
        }
    }
    free(pNode);
}

struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (pTrie) {
        if (pTrie->root) {
            deallocateTrieNode(pTrie->root);
        }
        free(pTrie);
    }
    return NULL;
}

// This function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords) {
    // Placeholder function: Implement your file reading here
    return 0;
}

int main(void) {
    char *inWords[256];
    
    // Read the number of the words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i) {
        printf("%s\n", inWords[i]);
    }
    
    struct Trie *pTrie = createTrie();
    for (int i = 0; i < numWords; i++) {
        insert(pTrie, inWords[i]);
    }
    // Parse line by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
    }
    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL)
        printf("There is an error in this program\n");
    return 0;
}
