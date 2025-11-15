#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>

/* Tipos opacos */
typedef struct arrayNode *arrayNode;
typedef struct tTreeNode *trieTree;
typedef struct tTreeNode *treeNodePos;

/* Lista enlazada de índices para un gen */
struct arrayNode {
    int index;
    arrayNode next;
};

/* Nodo del trie 4-ario */
struct tTreeNode {
    char l;          // letra del nodo (A, C, G, T o R en la raíz)
    trieTree A;
    trieTree C;
    trieTree G;
    trieTree T;
    arrayNode head;  // solo tiene datos en hojas
};

/* Prototipos de las funciones que ya tienes */
trieTree createTrieTree(int treeSize, char letter);
trieTree findGeneLeaf(trieTree root, const char *gene);

void genesRecognition(char *sequence, int seqLenght, int geneLenght, trieTree root);
void insertArrayNode(arrayNode currNode, arrayNode newArrayNode);
void insertGene(trieTree root, const char *gene, int genePos);

#endif
