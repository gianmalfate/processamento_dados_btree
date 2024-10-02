// T3 - SCC503

#include "btree.h"
#include <string.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Funcao para criar no - utilizada tambem para iniciar a arvore
struct BTreeNode *create_node(bool is_leaf) {
    struct BTreeNode *new_node = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    new_node->keys = (Info_node *)malloc((MAX_KEYS - 1) * sizeof(Info_node));
    new_node->child = (struct BTreeNode **)malloc(MAX_KEYS * sizeof(struct BTreeNode *));
    new_node->is_leaf = is_leaf;
    new_node->num_keys = 0;
    return new_node;
}

//funcao para redistribuicao dos nos
void redistribute_nodes(struct BTreeNode *parent, int index) {
    struct BTreeNode *left_child = parent->child[index];
    struct BTreeNode *right_child = parent->child[index + 1];

    // move chaves de um irmao para o outro
    left_child->keys[left_child->num_keys] = parent->keys[index];
    left_child->child[left_child->num_keys + 1] = right_child->child[0];
    parent->keys[index] = right_child->keys[0];
    left_child->num_keys++;

    // move as chaves e ponteiros de filho do filho a direita
    for (int i = 0; i < right_child->num_keys - 1; i++) {
        right_child->keys[i] = right_child->keys[i + 1];
        right_child->child[i] = right_child->child[i + 1];
    }
    right_child->child[right_child->num_keys - 1] = right_child->child[right_child->num_keys];
    right_child->num_keys--;
}

//funcao para fazer o split de um no
int split_child(struct BTreeNode *parent, int index) {
    struct BTreeNode *child = parent->child[index];
    //redistribui chaves entre os irmaos, se possivel
    if (child->num_keys < MAX_KEYS / 2 - 1 && index < parent->num_keys) {
        redistribute_nodes(parent, index);
        return 0;
    } 
    //se nao for possivel
    struct BTreeNode *new_node = create_node(child->is_leaf);
    new_node->num_keys = MAX_KEYS / 2 - 1;

    // move as chaves para o novo no
    for (int i = 0; i < new_node->num_keys; i++) {
        new_node->keys[i] = child->keys[i + MAX_KEYS / 2];
    }
    //se child nao for folha
    if (!child->is_leaf) {
        // move os ponteiros de filho para o novo no
        for (int i = 0; i < MAX_KEYS / 2; i++) {
            new_node->child[i] = child->child[i + MAX_KEYS / 2];
        }
    }

    child->num_keys = MAX_KEYS / 2 - 1;
    //move os ponteiros de filho no no pai para abrir espaco ao novo no
    for (int i = parent->num_keys; i > index; i--) {
        parent->child[i + 1] = parent->child[i];
    }

    parent->child[index + 1] = new_node;

    //move as chaves no no pai para abrir espaco para a chave mediana
    for (int i = parent->num_keys - 1; i >= index; i--) {
        parent->keys[i + 1] = parent->keys[i];
    }

    parent->keys[index] = child->keys[MAX_KEYS / 2 - 1];
    parent->num_keys++;
    return 1;
}

//funcao para inserir em um no que nao esta cheio (num_keys < MAX_KEYS)
void insert_non_full(struct BTreeNode *node, int key, long BOS) {
    int i = node->num_keys - 1;
    //se for folha
    if (node->is_leaf) {
        while (i >= 0 && key < node->keys[i].key) {
            node->keys[i + 1].key = node->keys[i].key;
            node->keys[i + 1].BOS = node->keys[i].BOS;
            i--;
        }

        node->keys[i + 1].key = key;
        node->keys[i + 1].BOS = BOS;
        node->num_keys++;
    } else { //se nao for folha
        while (i >= 0 && key < node->keys[i].key) {
            i--;
        }

        i++;

        if (node->child[i]->num_keys == MAX_KEYS - 1) {
            split_child(node, i);

            if (key > node->keys[i].key) {
                i++;
            }
        }
        //chamada recursiva para o filho apropriado
        insert_non_full(node->child[i], key, BOS);
    }
}

//Funcao para inserir um conjunto chave - BOS na arvore
void insert(struct BTreeNode **root, int key, long BOS) {
    struct BTreeNode *old_root = *root;
    if (old_root->num_keys == MAX_KEYS - 1) {
        struct BTreeNode *new_root = create_node(false);
        *root = new_root;
        new_root->child[0] = old_root;
        split_child(new_root, 0);
        insert_non_full(new_root, key, BOS);
    } else {
        insert_non_full(old_root, key, BOS);
    }
}


/* Funcao auxiliar utilizada para printar a arvore -- usada para testes
void print_tree(struct BTreeNode *node) {
    if (node != NULL) {
        for (int i = 0; i < node->num_keys; i++) {
            printf("%d ", node->keys[i].key);
        }

        printf("\n");

        if (!node->is_leaf) {
            for (int i = 0; i <= node->num_keys; i++) {
                print_tree(node->child[i]);
            }
        }
    }
}
*/

//Funcao para procurar uma chave na arvore
//-se encontrar: retorna o BOS atrelado a chave encontrada
//-senao: retorna -1
long searchBTree(struct BTreeNode* root, int key) {
    if (root == NULL){ // no nulo
        return -1;
    } 
    int i = 0;
    while (i < root->num_keys && key > root->keys[i].key){ // busca na lista de chaves do no
        i++;
    }
    if (i < root->num_keys && key == root->keys[i].key){ // chave desejada encontrada
        return root->keys[i].BOS;
    }
    if (root->is_leaf){ // verifica se no folha
        return -1;
    }
    // se no atual nao folha, busca recursiva no filho apropriado
    return searchBTree(root->child[i], key);
}

// ALGORITMO DE ESCRITA DA ARVORE B EM ARQUIVO
/*Prototipos que seriam utilizados em uma solucao real

void insert(struct BTreeNode **root, int key, long BOS, FILE *file) {
    
    struct BTreeNode *old_root = *root;
    if(searchBTree(*root, key, file) == -1){
        if (old_root->num_keys == MAX_KEYS - 1) {
            struct BTreeNode *new_root = create_node(false);
            *root = new_root;
            new_root->child[0] = old_root;
            split_child(new_root, 0);
            insert_non_full(new_root, key, BOS);
        } else {
            insert_non_full(old_root, key, BOS);
        }
    } else{
        printf("chave repetida!\n");
    }


    insert_non_full(old_root, key, BOS);

    // Salve a árvore B no arquivo após a inserção
    fseek(file, 0, SEEK_SET);
    write_node(file, *root);

}

long searchBTree(struct BTreeNode* root, int key, FILE *file) {
    if (root == NULL){ // no nulo
        return -1;
    } 

    int i = 0;
    while (i < root->num_keys && key > root->keys[i].key){ // busca na lista de chaves do no
        i++;
    }
    if (i < root->num_keys && key == root->keys[i].key){ // chave desejada encontrada
        //printf("----------------------------------------------------------\n");
        //printf("BOS DA BUSCA: %ld\n", root->keys[i].BOS);
        return root->keys[i].BOS;
    }
    if (root->is_leaf){ // verifica se no folha
        return -1;
    }
    // se no atual nao folha, busca recursiva no filho apropriado
    //return searchBTree(root->child[i], key);


    // Carregue a árvore B do arquivo antes da busca
    fseek(file, 0, SEEK_SET);
    struct BTreeNode *loaded_root = read_node(file);

    // Faça a busca na árvore carregada
    long result = searchBTree(loaded_root, key, file);

    // Libere a memória alocada para a árvore carregada
    free(loaded_root->keys);
    free(loaded_root->child);
    free(loaded_root);

    return result;
}

void write_node(FILE *file, struct BTreeNode *node) {
    NodeRecord record;
    record.is_leaf = node->is_leaf;
    record.num_keys = node->num_keys;

    // Copie as chaves do nó para o registro
    record.keys = (Info_node *)malloc((MAX_KEYS - 1) * sizeof(Info_node));
    memcpy(record.keys, node->keys, node->num_keys * sizeof(Info_node));

    // Escreva o registro no arquivo
    fwrite(&record, sizeof(NodeRecord), 1, file);

    // Libere a memória alocada
    free(record.keys);
}

struct BTreeNode *read_node(FILE *file) {
    NodeRecord record;

    // Leia o registro do arquivo
    fread(&record, sizeof(NodeRecord), 1, file);

    // Crie um novo nó da árvore B
    struct BTreeNode *node = create_node(record.is_leaf);
    node->num_keys = record.num_keys;

    // Copie as chaves do registro para o nó
    node->keys = (Info_node *)malloc((MAX_KEYS - 1) * sizeof(Info_node));
    memcpy(node->keys, record.keys, record.num_keys * sizeof(Info_node));

    return node;
}

struct BTreeNode *load_tree(FILE *file) {
    // Verifique se o arquivo existe
    if (file == NULL) {
        // Crie uma nova árvore B vazia
        struct BTreeNode *root = create_node(true);
        return root;
    }

    // Carregue a árvore B do arquivo
    struct BTreeNode *root = read_node(file);
    return root;
}
*/