#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

/* Crea un trie completo de altura treeSize.
 * letter es la letra que se guarda en este nodo.
 */
trieTree createTrieTree(int treeSize, int currLevel, char letter, char* nameBuffer, char* childKeys) 
{
    // Node creation with memory assignment
    trieTree node = malloc(sizeof(struct tTreeNode));
    if (node == NULL) 
    {
        printf(
            "ERROR: Memory allocation for node '%c' with height '%d' was not possible\n",
            letter, treeSize
        );
        return NULL;
    }

    node->l = letter;
    node->childNodes[0] = node->childNodes[1] = 
    node->childNodes[2] = node->childNodes[3] = NULL;
    node->head = NULL;
    node->arrayLenght = -1;

    if (currLevel < treeSize) {
        //Inner node creation
        for (int i = 0; i < 4; i++){
            
            if (currLevel != 0) nameBuffer[currLevel-1] = letter; 

            node->childNodes[i] = 
            createTrieTree(treeSize, currLevel+1, childKeys[i], nameBuffer, childKeys);
        }
    } else {
        //Leaf creation
        nameBuffer[currLevel-1] = letter;

        arrayNode head = malloc(sizeof(struct arrayNode));
        if (head == NULL) {
            printf("ERROR: Memory allocation for array head in leaf %c was not possible.\n", letter);
        } else {

            node->geneName = malloc(strlen(nameBuffer)+1);
            if (node->geneName == NULL){
                printf("ERROR: Memory allocation for gene name in leaf %c was not possible\n", letter);
            } else {
                
                strcpy(node->geneName, nameBuffer);
                head->index = -1;
                head->next  = NULL;
                node->head  = head;
                node->arrayLenght = 0;

                printf("Leaf {%s} created\n", node->geneName);
            }            
        }
    }


    return node;

    /* Funcion creadora antigua
    if (currLevel < treeSize) {
        

        int nextHeight = treeSize - 1;
        char nameChildA[treeSize], nameChildC[treeSize], nameChildG[treeSize], nameChildC[treeSize];
        strncpy(nameChildA, geneName);
        node->A = createTrieTree(nextHeight, 'A');
        node->C = createTrieTree(nextHeight, 'C');
        node->G = createTrieTree(nextHeight, 'G');
        node->T = createTrieTree(nextHeight, 'T');
    }*/ 
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
        case 'A': return node->childNodes[0];
        case 'C': return node->childNodes[1];
        case 'G': return node->childNodes[2];
        case 'T': return node->childNodes[3];
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
void insertGene (trieTree root, const char *gene, int genePos){
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
        leaf->arrayLenght = 1;

        /*ArrayNode newUniqueGene = malloc(sizeof(struct arrayNode));
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
        }*/


    }else {
        insertArrayNode(leaf->head, newArrayNode);
        (leaf->arrayLenght)++;
    }
    printf("Gene[%s] Index[%d] inserted in Leaf[%s]Lenght[%d].\n", gene, genePos, leaf->geneName, leaf->arrayLenght);
}

void insertArrayNode(arrayNode currNode, arrayNode newNode){
    if (currNode->next == NULL){
        currNode->next = newNode;
    } else {
        insertArrayNode(currNode->next, newNode);
    }
}

//Cont should be 0
int arrayLenght(arrayNode head, int cont){
    cont++;
    if (head->next == NULL) return cont;
    else {return arrayLenght(head->next, cont);}
}

//Recursive function to find longest array lenght (of indexes)
void findLongest(trieTree node, int* longest){
    
    if (node->head != NULL){
        //Leaf found
        if (node->arrayLenght > (*longest)){
            //Longest updated
            (*longest) = node->arrayLenght;
        }
        return;

    } else {
        for (int i = 0; i < 4; i++){
            findLongest(node->childNodes[i], longest);
        }
    }
    return;
}

void showArrayByLenght();
//Toi sacando la basura
//Echale un ojo al código pa que caches cómo vamos
//Calquier pregunta me dice
//nao yo linux, por?
//por ahora solo puedo ejecutar yo
//pero puedes descargar los archivos y correrlos en tu pc
// voy tratar de arreglar los errores .....🦈