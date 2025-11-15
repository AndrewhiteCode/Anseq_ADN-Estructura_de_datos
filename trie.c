#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include "struct.h"

/* Crea un trie completo de altura treeSize.
 * letter es la letra que se guarda en este nodo.
 */
trieTree createTrieTree(int treeSize, char letter) {

    // Node creation with memory assignment
    trieTree node = malloc(sizeof(struct tTreeNode));
    if (node == NULL) {
        printf(
            "ERROR: Memory allocation for node '%c' with height '%d' was not possible\n",
            letter, treeSize
        );
        return NULL;
    }

    node->l = letter;
    node->A = node->C = node->G = node->T = NULL;
    node->head = NULL;

    if (treeSize > 0) {
        int nextHeight = treeSize - 1;

        node->A = createTrieTree(nextHeight, 'A');
        node->C = createTrieTree(nextHeight, 'C');
        node->G = createTrieTree(nextHeight, 'G');
        node->T = createTrieTree(nextHeight, 'T');
    } else {

        arrayNode head = malloc(sizeof(struct arrayNode));
        if (head == NULL) {
            printf("ERROR: Memory allocation for array head in leaf %c was not possible.\n", letter);
        } 
        else {
            head->index = -1;
            head->next  = NULL;
            node->head  = head;
        }
    }

    return node;
}

//pero creo que entiend a que te refieres, es para despues recibir el puntero a la hoja, ok
//Modifique el struct para que reciba root y *gene , por lo tanto
//trieTree findGeneLeaf(trieTree root, const char *gene) 
//Pero necesita los auxiliares
//van por aparte

//okei entiendo
static trieTree getChildForChar(trieTree node , char c){
    if (node == NULL) return NULL;
    switch (c){
        case 'A': return node->A;
        case 'C': return node->C;
        case 'G': return node->G;
        case 'T': return node->T;
    default:
        return NULL; //Caracter invalido
    }
}
//asi encuentra la hoja del gen
trieTree findGeneLeaf(trieTree root , const char *gene){
    if (root == NULL || gene == NULL){
        return NULL;
    }
    trieTree current = root;

    for (int i = 0; gene[i] !='\0' ; i++){
        char c = gene[i];
        current = getChildForChar(current, c);
        if (current == NULL){
            //el camino no existe o caracter invalido
            return NULL;
        }
        //aqui deberiamos estar en la hoja correpondiente al gene
        
    }
    return current;
}

//inserta newarray al final de la lista que comienza
void insertGene (trieTree root, const char *gene, int genePos, arrayNode uniqueGeneArray){
    trieTree leaf = findGeneLeaf(root,gene);
    if(leaf == NULL){
        printf("-> no leaf found for %s\n", gene);
        return;
    }
    arrayNode newArrayNode = malloc(sizeof(struct arrayNode));
    if (newArrayNode == NULL){
        printf("ERROR: no se pudo asignar memoria para indicar el indice %d del gen %s\n", genePos, gene);
        return;
    }
    newArrayNode->index = genePos;
    newArrayNode->next = NULL;

    if(leaf->head == NULL){
        leaf->head = newArrayNode;

        arrayNode newUniqueGene = malloc(sizeof(struct arrayNode));
        if (newUniqueGene == NULL){
            printf("ERROR: no se pudo asignar memoria para añadir un nuevo gen único\n");
            return;
        }
        newUniqueGene->geneName = gene;
        newUniqueGene->next = NULL;
        if (uniqueGeneArray == NULL){
            uniqueGeneArray = newUniqueGene;
        }
        else{
            insertArrayNode(uniqueGeneArray, newUniqueGene);
        }
        printf("Nuevo gen detectado: [%s]\n", gene);

    }else {
        insertArrayNode(leaf->head, newArrayNode);
    }
}

void insertArrayNode(arrayNode currNode, arrayNode newNode){
    if (currNode->next == NULL){
        currNode->next = newNode;
    } else {
        insertArrayNode(currNode->next, newNode);
    }
}

int arrayLenght(arrayNode head, int cont){
    cont++;
    if (head->next == NULL) return cont;
    else {return arrayLenght(head->next, cont);}
}

void showMostRepetitions(trieTree root, arrayNode uniqueGeneArray){
    const char currGene = uniqueGeneArray->geneName;
    trieTree leaf;
    while (currGene != NULL){
        leaf = findGeneLeaf(root, currGene);
        
    }
}
