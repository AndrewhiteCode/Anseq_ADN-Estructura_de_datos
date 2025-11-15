#include <stdio.h>
#include <string.h>
#include "struct.h"

/* Esta función recorre la secuencia, identifica cada gen
 * y (por ahora) solo los imprime.
 * Más adelante aquí llamarás a una función del trie para
 * insertar la posición en la hoja correspondiente.
 */
void genesRecognition(char *sequence, int seqLenght, int geneLenght, trieTree root) {
    (void)root; // para que no dé warning mientras no lo uses

    for (int i = 0; i <= (seqLenght - geneLenght); i++) {
        char gene[geneLenght + 1];

        strncpy(gene, &sequence[i], geneLenght);
        gene[geneLenght] = '\0';

        printf("Se va a buscar el gen %s en la posición %d\n", gene, i);
    }
}
