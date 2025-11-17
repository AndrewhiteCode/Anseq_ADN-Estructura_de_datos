#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include <ctype.h>

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
    node->geneName = NULL;

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

        node->geneName = malloc(sizeof(char)*(treeSize+1));
        if (node->geneName == NULL){
            printf("ERROR: Memory allocation for gene name in leaf %c was not possible\n", letter);
        
        } else {
            nameBuffer[treeSize] = '\0';
            strcpy(node->geneName, nameBuffer);
            node->head = NULL;
            node->arrayLenght = 0;
        }            
    }
    return node;
}

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

//inserta nuevo index a la hoja correspondiente
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

    }else {
        insertArrayNode(leaf->head, newArrayNode);
        (leaf->arrayLenght)++;
    }
}

void insertArrayNode(arrayNode currNode, arrayNode newNode){
    if (currNode->next == NULL){
        currNode->next = newNode;
    } else {
        insertArrayNode(currNode->next, newNode);
    }
}

//Recursive function to find longest array lenght (of indexes)
void findLongest(trieTree node, int* longest){
    
    if (node->arrayLenght == -1){
        for (int i = 0; i < 4; i++){
            findLongest(node->childNodes[i], longest);
        }
        return;
    } else {
        //Leaf found
        if (node->arrayLenght > (*longest)){
            //Longest updated
            (*longest) = node->arrayLenght;
        }
    }
    return;
}

void findShortest(trieTree node, int* shortest){
    
    if (node->arrayLenght == -1){
        for (int i = 0; i < 4; i++){
            findShortest(node->childNodes[i], shortest);
        }
        return;
    } else {
        //Leaf found
        if (node->arrayLenght != 0){
            if ((node->arrayLenght < (*shortest) || (*shortest) == -1)){
                //Shortest updated
                (*shortest) = node->arrayLenght;
            }
        }     
    }
    return;
}

void showArray (arrayNode arrNode){
    printf(" %d", arrNode->index);

    if (arrNode->next == NULL) return;
    else {showArray(arrNode->next);}
}

void showByLenght(trieTree node, int lenght){
    if (node->arrayLenght == -1){
        for(int i = 0; i < 4; i++){
            showByLenght(node->childNodes[i], lenght);
        }
    //Its a leaf
    } else {
        if (node->arrayLenght == lenght){
            printf("[%s]:", node->geneName);
            showArray(node->head);
            printf("\n");
        }
    }    
}

void showAll(trieTree node){
    if (node->arrayLenght == -1){
        for (int i = 0; i < 4; i++){
            showAll(node->childNodes[i]);
        }
    } else {
        if (node->arrayLenght != 0){
            printf("[%s]:", node->geneName);
            showArray(node->head);
            printf("\n");
        }
    }
}

void freeArray(arrayNode arrNode){
    arrayNode curr = arrNode;
    arrayNode next;

    while (curr != NULL){
        next = curr->next;
        free(curr);
        curr = next;
    }
    return;
}

void freeMemory(trieTree node){
    if (node->arrayLenght != -1) {
        free(node->geneName);
        if (node->arrayLenght != 0){
            freeArray(node->head);
        }
        
    } else {
        for (int i = 0; i < 4; i++){
            freeMemory(node->childNodes[i]);
        }
    }
    free(node);
}
void show_help() 
{
    printf(ANSI_CYAN "\n===== MENU DE COMANDOS =====\n\n" ANSI_RESET);
    printf(ANSI_YELLOW "Comando" ANSI_RESET "               " ANSI_YELLOW "Descripcion\n" ANSI_RESET);
    printf(ANSI_GREEN "bio start <n>" ANSI_RESET "          - Creación del árbol, siendo n el tamano de los genes que serán igual a la altura del árbol \n");
    printf(ANSI_GREEN "bio read <ADN.TXT>" ANSI_RESET "     - Leer archivo de texto (Una sola linea). \n");
    printf(ANSI_GREEN "bio search <G>" ANSI_RESET "         - Búsqueda manual de un Gen especifico junto con su posición \n");
    printf(ANSI_GREEN "bio max " ANSI_RESET "               - Búsqueda de Gen con más repetición dentro de lista junto con sus posiciones \n");
    printf(ANSI_GREEN "bio min " ANSI_RESET "               - Para el gen que aparece menos veces, se lista todos con sus respectivas posiciones\n");
    printf(ANSI_GREEN "bio min " ANSI_RESET "               - Muestra el estado actual del cache\n");
    printf(ANSI_GREEN "bio all " ANSI_RESET "               - Ver todos los genes que aparecen en la secuencia junto a sus posiciones)\n");
    printf(ANSI_GREEN "bio exit " ANSI_RESET "              - Libera el cache y termina el programa\n");

}
void show_cadena(char *filename) 
{
    FILE *fp = fopen(filename, "r");
    char c;

    if (fp == NULL) {
        printf("Error! en abrir el archivo'%s'\n", filename);
        return;
    }

    printf(ANSI_YELLOW"Cadena genetica de  '%s' \n\n", filename);
    while ((c = fgetc(fp)) != EOF) 
    {
        printf("%c", c);
    }
    
    printf("\n");
    fclose(fp);
}