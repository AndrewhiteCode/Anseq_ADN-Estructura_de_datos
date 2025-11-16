#include "struct.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) 
{

    int geneLenght  = 3;
    char childKeys[] = {'A', 'C', 'G', 'T'};
    char nameBuffer[geneLenght];

    // Crear trie de altura 3 con raíz 'R'
    trieTree root = createTrieTree(3, 0, 'R', nameBuffer, childKeys);
    if (root == NULL) {
        return 1;
    }

    // Secuencia de prueba (antes tenías un char[19] sin inicializar + strcat)
    char sequence[] = "ATCGATCGATCGATTCGA";
    int seqLenght   = (int)strlen(sequence);

    genesRecognition(sequence, seqLenght, geneLenght, root);
    


    // TODO: aquí más adelante deberías liberar el árbol (freeTrie(root))

    return 0;
}