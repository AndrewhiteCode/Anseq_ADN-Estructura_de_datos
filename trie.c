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
        printf("%c", current->l);
        if (current == NULL){
            //el camino no existe o caracter invalido
            return NULL;
        }
        //aqui deberiamos estar en la hoja correpondiente al gene
        printf("\n");
    }
    return current;
}

//inserta newarray al final de la lista que comienza
void insertArrayNode(arrayNode currNode, arrayNode newArrayNode){
  
    if (currNode -> next == NULL ){
        currNode -> next = newArrayNode;
    }else {
        insertArrayNode(currNode -> next, newArrayNode);
    }
        
}

