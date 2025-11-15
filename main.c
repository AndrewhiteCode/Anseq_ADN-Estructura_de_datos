#include <stdio.h>
#include <string.h>
#include "struct.h"

int main(void) {

    // Crear trie de altura 3 con raíz 'R'
    trieTree root = createTrieTree(3, 'R');
    if (root == NULL) {
        return 1;
    }

    // Secuencia de prueba (antes tenías un char[19] sin inicializar + strcat)
    char sequence[] = "ATCGATCGATCGATTCGA";
    int seqLenght   = (int)strlen(sequence);
    int geneLenght  = 3;

    genesRecognition(sequence, seqLenght, geneLenght, root);

    // TODO: aquí más adelante deberías liberar el árbol (freeTrie(root))

    return 0;
}