#ifndef BTREE_H
#define BTREE_H

// bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>

// constantes
#define MAX_KEYS 4

typedef struct Info_node{
    int key;
    long BOS;
} Info_node;

struct BTreeNode{
    Info_node *keys;
    struct BTreeNode **child;
    bool is_leaf;
    int num_keys;
};

//funcoes
struct BTreeNode *create_node(bool is_leaf);
int split_child(struct BTreeNode *parent, int index);
void insert_non_full(struct BTreeNode *node, int key, long BOS);
void insert(struct BTreeNode **root, int key, long BOS);
void print_tree(struct BTreeNode *node);
long searchBTree(struct BTreeNode* root, int key);
void redistribute_nodes(struct BTreeNode *parent, int index);

/*Prototipos que seriam utilizados em uma solucao real
void insert(struct BTreeNode **root, int key, long BOS, FILE *file);
long searchBTree(struct BTreeNode* root, int key, FILE *file);
void write_node(FILE *file, struct BTreeNode *node);
struct BTreeNode *read_node(FILE *file);
struct BTreeNode *load_tree(FILE *file);
*/

#endif