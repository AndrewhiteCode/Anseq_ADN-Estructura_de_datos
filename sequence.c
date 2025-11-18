#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"


/**
 * @brief Reconoce los genes en una secuencia de ADN y los inserta en el trie.
 * @param sequence Secuencia de ADN a analizar.
 * @param seqLenght Longitud de la secuencia.
 * @param geneLenght Longitud del gen a reconocer.
 * @param root Nodo raíz del trie donde se insertan los genes.
 */
void genesRecognition(char *sequence, int seqLenght, int geneLenght, trieTree root)
 {

    for (int i = 0; i <= (seqLenght - geneLenght); i++) 
    {
        char gene[geneLenght + 1];
        strncpy(gene, &sequence[i], geneLenght);
        gene[geneLenght] = '\0';
/**
 * @brief Inserta un índice para un gen en el trie.
 * @param root Nodo raíz del trie.
 * @param gene Gen a insertar.
 * @param genePos Posición del gen en la secuencia.
 */
        insertGene(root, gene, i);
    }
}