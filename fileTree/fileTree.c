#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "fileTree.h"
#include "../sha1/sha1.h"

typedef struct node node;
typedef struct nodeList nodeList;

struct node {
    node* left;
    node* right;
    char *data;
};

struct nodeList {
    nodeList* next;
    node* data;
};
//TODO: make nodeList
nodeList *nl;

void addToNodeList(nodeList* nla, node* n);
int nodeListLength(nodeList* nla);
void nListInit();
nodeList* treeLevelGenerator(nodeList* a);

/**
 * meh
 */

void nListInit() {
    nl = (nodeList *) malloc(sizeof(nodeList));

    nl->next = NULL;
    nl->data = (node*) malloc(sizeof(node));
    nl->data->data = malloc(SHA_LEN);
    strcpy(nl->data->data, "");
}

/**
 * 
 */
void initialNodeListadd(char * sha){
    nodeList* newNl = (nodeList *) malloc(sizeof(nodeList));
    node* newN = (node*) malloc(sizeof(node));

    newN->data = malloc(SHA_LEN);
    strcpy(newN->data, sha);
    newN->left = NULL;
    newN->right = NULL;

    newNl->next = nl->next;
    newNl->data = nl->data;

    nl->next = newNl;
    nl->data = newN;
}

void addToNodeList(nodeList* nla, node* n) {
    nodeList* newNl = (nodeList *) malloc(sizeof(nodeList));
    newNl->next = nla->next;
    newNl->data = nla->data;

    nla->next = newNl;
    nla->data = n;
}

/**
 * 
 */

int nodeListLength(nodeList* nla) {
    if(nla->next == NULL) return 0;
    else return 1 + nodeListLength(nla->next);
}

/**
 * 
 */

void parseTree() {
    nodeList* nla = (nodeList*) malloc(sizeof(nodeList));
    nla = nl;
    node* root = (node*) malloc(sizeof(node));
    char* sha = malloc(FILE_LEN);
    int offset;

    while(nodeListLength(nla) > 1) {
        nla = treeLevelGenerator(nla);       
    }  

    SHA1(sha, nla->data->data, strlen(sha));

    printf("\nFinal sha: ");

    printSha(sha);

    printf("\n");
}

/**
 * 
 */

nodeList* treeLevelGenerator(nodeList* a) {
    int x = nodeListLength(a);
    int i, j;
    nodeList* b = (nodeList*) malloc(sizeof(nodeList));
    nodeList* d = (nodeList*) malloc(sizeof(nodeList));

    b = a;

    for(i = 0; i < x; i = i+2) {
        node* c = (node*) malloc(sizeof(node));

        c->data = malloc(SHA_LEN);
        if(b->next->data == NULL) {
            strcpy(c->data, b->data->data);
        } else {
            char* sha = malloc(FILE_LEN);

            strcpy(sha, b->data->data);
            strcat(sha, b->next->data->data);
            SHA1(c->data, sha, strlen(sha));
        }

        c->left = b->data;
        if(b->next->data != NULL) c->right = b->next->data;

        addToNodeList(d, c);

        b = b->next->next;
    }

    return d;
}

void printSha(char* sha) {
    int i;

    /* format the hash for comparison */
    for( i = 0; i < 20; i++) {
        printf("%02x", sha[i]&0xff);
    }

    printf("\n");
}