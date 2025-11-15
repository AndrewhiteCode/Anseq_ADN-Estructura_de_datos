#include <stdio.h>
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
            head->index = 7;
            head->next  = NULL;
            node->head  = head;
        }
    }

    return node;
}


void insertArrayNode(arrayNode currNode, arrayNode newArrayNode){
    if (currNode->next == NULL){
        currNode->next = newArrayNode;
    } else{
        insertArrayNode(currNode->next, newArrayNode);
    }
}

//pero creo que entiend a que te refieres, es para despues recibir el puntero a la hoja, ok

trieTree findGeneLeaf(char* gene, int genePos, int index, trieTree node){
    if (node->head != NULL){
 
        //Array node memory assignment
        arrayNode newArrayNode = malloc(sizeof(struct arrayNode));
        newArrayNode->index = genePos;

        if (node->head->index == NULL){
            node->head = newArrayNode;
            printf("%c] was chosen. Array found empty, index [%d] inserted", node->l, genePos);
        } else{
            insertArrayNode(node->head, newArrayNode);
            printf("%c] was chosen, index [%d] inserted", node->l, genePos);
        }
        return node;
    }
    
    if (gene[index] == 'A'){
        findGeneLeaf(gene, genePos, index+1, node->A);
        printf("A ");
    } else if (gene[index] == 'C'){
        findGeneLeaf(gene, genePos, index+1, node->C);
        printf("C ");
    } else if (gene[index] == 'G'){
        findGeneLeaf(gene, genePos, index+1, node->G);
        printf("G ");
    } else if (gene[index] == 'T'){
        findGeneLeaf(gene, genePos, index+1, node->T);
        printf("T ");
    }
}