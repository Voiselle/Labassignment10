#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

struct Trie {
    int count;
    struct Trie* children[ALPHABET_SIZE];
};

void insert(struct Trie **ppTrie, char *word) {
    if (word[0] == '\0') {
        // end of word
        if (*ppTrie == NULL) {
            *ppTrie = malloc(sizeof(struct Trie));
            (*ppTrie)->count = 0;
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                (*ppTrie)->children[i] = NULL;
            }
        }
        (*ppTrie)->count++;
    } else {
        int index = word[0] - 'a';
        if ((*ppTrie)->children[index] == NULL) {
            (*ppTrie)->children[index] = malloc(sizeof(struct Trie));
            (*ppTrie)->children[index]->count = 0;
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                (*ppTrie)->children[index]->children[i] = NULL;
            }
        }
        insert(&((*ppTrie)->children[index]), word + 1);
    }
}

int numberOfOccurances(struct Trie *pTrie, char *word) {
    if (pTrie == NULL) {
        return 0;
    } else if (word[0] == '\0') {
        return pTrie->count;
    } else {
        int index = word[0] - 'a';
        return numberOfOccurances(pTrie->children[index], word + 1);
    }
}

struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (pTrie != NULL) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            deallocateTrie(pTrie->children[i]);
        }
        free(pTrie);
    }
    return NULL;
}

int main(void) {
    struct Trie *trie = NULL;

    // read the number of words in the dictionary
    int n;
    scanf("%d", &n);

    // parse line by line and insert each word to the trie data structure
    for (int i = 0; i < n; i++) {
        char word[100];
        scanf("%s", word);
        insert(&trie, word);
    }

    // test the trie by checking the number of occurrences of each word
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));
    }

    // deallocate the trie
    trie = deallocateTrie(trie);
    if (trie != NULL) {
        printf("There is an error in this program\n");
    }
    return 0;
}
