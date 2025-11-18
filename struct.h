
#ifndef STRUCT_H
#define STRUCT_H
#define ANSI_CYAN    "\x1b[36m"
#define ANSI_YELLOW  "\x1b[33m"
#define ANSI_GREEN   "\x1b[32m"
#define ANSI_RESET   "\x1b[0m"
#define LINE_BUFSIZE 1024
#define PROMPT       "bio> "

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
/**
 * @brief Crea un trie completo de altura treeSize.
 * @param treeSize Altura máxima del trie.
 * @param currLevel Nivel actual del trie (inicia en 0).
 * @param letter Letra del nodo actual.
 * @param nameBuffer Buffer para almacenar el nombre del gen.
 * @param childKeys Claves de los hijos (A, C, G, T).
 * @return Nodo raíz del trie creado.
 */
trieTree createTrieTree(int treeSize, int currLevel, char letter, char* nameBuffer, char* childKeys);
/**
 * @brief Busca la hoja correspondiente a un gen en el trie.
 * @param root Nodo raíz del trie.
 * @param gene Gen a buscar.
 * @return Nodo hoja donde se encuentra el gen, o NULL si no se encuentra.
 */
trieTree findGeneLeaf(trieTree root, const char *gene);

/**
 * @brief Reconoce los genes en una secuencia de ADN y los inserta en el trie.
 * @param sequence Secuencia de ADN a analizar.
 * @param seqLenght Longitud de la secuencia.
 * @param geneLenght Longitud del gen a reconocer.
 * @param root Nodo raíz del trie donde se insertan los genes.
 */
void genesRecognition(char *sequence, int seqLenght, int geneLenght, trieTree root);
void insertArrayNode(arrayNode currNode, arrayNode newArrayNode);
/**
 * @brief Inserta un índice para un gen en el trie.
 * @param root Nodo raíz del trie.
 * @param gene Gen a insertar.
 * @param genePos Posición del gen en la secuencia.
 */
void insertGene(trieTree root, const char *gene, int genePos);
void findLongest(trieTree node, int* longest);
void findShortest(trieTree node, int* shortest);
void showArray (arrayNode arrNode);
void showAll(trieTree node);
void showByLenght(trieTree node, int longest);
void freeArray(arrayNode arrNode);
void freeMemory(trieTree node);
void show_help(void);
void show_cadena(char *filename);


#endif
