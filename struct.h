#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>

/* Tipos opacos */
typedef struct arrayNode *arrayNode;
typedef struct tTreeNode *trieTree;
typedef struct tTreeNode *treeNodePos;

/* Lista enlazada de índices para un gen */
struct arrayNode 
{
    int index;
    arrayNode next;
    // char* geneName; //Used for temporary gene list
};

/* Nodo del trie 4-ario */
struct tTreeNode 
{
    char l;          // letra del nodo (A, C, G, T o R en la raíz)
    trieTree childNodes[4];

    //Only for leaf nodes
    arrayNode head;  
    int arrayLenght;
    char* geneName;
};

/* Prototipos de las funciones */
trieTree createTrieTree(int treeSize, int currLevel, char letter, char* nameBuffer, char* childKeys);
trieTree findGeneLeaf(trieTree root, const char *gene);

void genesRecognition(char *sequence, int seqLenght, int geneLenght, trieTree root);
void insertArrayNode(arrayNode currNode, arrayNode newArrayNode);
void insertGene(trieTree root, const char *gene, int genePos);
void showMostRepetitions(trieTree root, arrayNode uniqueGeneArray);


#endif
