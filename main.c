

#include "struct.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE_BUFSIZE 1024

char *skip_spaces(char *s) 
{
    while (*s == ' ') s++;
    return s;
}

int main(void) 
{
    trieTree root = NULL;          
    char *nameBuffer = NULL;     
    char *sequenceBuffer = NULL; 
    int geneLenght = 0;
    char line[LINE_BUFSIZE];
    char childKeys[] = {'A', 'C', 'G', 'T'};

    printf("Escribe 'bio help' para ver los comandos.\n\n");
    
    while(1)
    {
        printf(ANSI_GREEN "bio> "); //ayuda visual
        if (!fgets(line, sizeof(line), stdin)) {
            putchar('\n');
            break;
        }
        line[strcspn(line, "\n")] = 0; //eliminar salto de linea
        char *cmd = skip_spaces(line);
        if (strlen(cmd) == 0)
            continue;

        if (strcmp(cmd, "bio help") == 0 || strcmp(cmd, "help") == 0)
        {    
            show_help();
            printf("\n");
        } 
        
        if (strncmp(cmd, "bio start", 9) == 0 || strncmp(cmd, "start", 5) == 0) 
        {

            if (strncmp(cmd, "bio start", 9) == 0) {
                geneLenght = atoi(cmd + 9); 
            } else {
                geneLenght = atoi(cmd + 5);
            }

            if (geneLenght <= 0) {
                fprintf(stderr, "Error: Debes indicar el tamano\n");
                continue;
            }

            //limpieza por si ya existe un arbol anterior
            if (root != NULL) {
                freeMemory(root); 
                free(nameBuffer);
                if (sequenceBuffer) 
                { 
                    free(sequenceBuffer); 
                    sequenceBuffer = NULL;
                }
            }

            nameBuffer = malloc(sizeof(char) * (geneLenght + 1));
            
            //se crea el  arbol
/**
 * @brief Crea un trie completo de altura treeSize.
 * @param treeSize Altura máxima del trie.
 * @param currLevel Nivel actual del trie (inicia en 0).
 * @param letter Letra del nodo actual.
 * @param nameBuffer Buffer para almacenar el nombre del gen.
 * @param childKeys Claves de los hijos (A, C, G, T).
 * @return Nodo raíz del trie creado.
 */
            root = createTrieTree(geneLenght, 0, 'R', nameBuffer, childKeys);
            
            if (root == NULL) return 1;
            printf("Arbol iniciado (gen: %d)\n", geneLenght);
            printf("\n");
        }
        //read
        if (strncmp(cmd, "bio read", 8) == 0 || strncmp(cmd, "read", 4) == 0)
        {    
            if (root == NULL) {
                fprintf(stderr, "Error!,primero crea el arbol .\n");
                continue;
            }

            char *filename;
            //longitud exacta del comando para llegar al nombre del archivo
            if (strncmp(cmd, "bio read", 8) == 0) {
                filename = skip_spaces(cmd + 8);
            } else {
                filename = skip_spaces(cmd + 4);
            }

            if (strlen(filename) == 0) {
                fprintf(stderr, "Uso: bio read archivo.txt\n");
                continue;
            }

            //manejo de archivo
            FILE *fp = fopen(filename, "r");
            if (!fp) {
                fprintf(stderr, "Error! al abrir  '%s'\n", filename);
                continue;
            }

            //calcular tamano
            fseek(fp, 0, SEEK_END);
            long fsize = ftell(fp);
            rewind(fp);

            //preparar memoria
            if (sequenceBuffer) free(sequenceBuffer);
            sequenceBuffer = malloc(fsize + 1);
            
            if (!sequenceBuffer) 
            { 
                fclose(fp); 
                fprintf(stderr, "Error fatal de memoria\n");
                break; 
            }

            // lectura 
            fread(sequenceBuffer, 1, fsize, fp);
            sequenceBuffer[fsize] = 0; // Terminador nulo
            fclose(fp);

            // saltos de linea sobrantes 
            sequenceBuffer[strcspn(sequenceBuffer, "\r\n")] = 0;
            
            int seqLenght = (int)strlen(sequenceBuffer);

            if (seqLenght < geneLenght) 
            {
                printf("Error! archivo mas corto que el tamano del gen.\n");
            } else {
/**
 * @brief Reconoce los genes en una secuencia de ADN y los inserta en el trie.
 * @param sequence Secuencia de ADN a analizar.
 * @param seqLenght Longitud de la secuencia.
 * @param geneLenght Longitud del gen a reconocer.
 * @param root Nodo raíz del trie donde se insertan los genes.
 */
                genesRecognition(sequenceBuffer, seqLenght, geneLenght, root);
                printf("Archivo '%s'correctamente.\n", filename);
            }

            show_cadena(filename);
            printf("\n");

        }
        if (strncmp(cmd, "bio search", 10) == 0 || strncmp(cmd, "search", 6) == 0) 
        {
            if (root == NULL) {
                fprintf(stderr, "Error!! ejecuta start <n>\n");
                continue;
            }

            char *geneToFind;
            // Calcular inicio del texto saltando el comando
            if (strncmp(cmd, "bio search", 10) == 0) geneToFind = skip_spaces(cmd + 10);
            else geneToFind = skip_spaces(cmd + 6);

            if (strlen(geneToFind) != geneLenght) {
                printf("Error: El gen buscado debe tener %d letras (escribiste %ld).\n", geneLenght, strlen(geneToFind));
                continue;
            }

            // Usar la función de búsqueda del Trie
            trieTree leaf = findGeneLeaf(root, geneToFind); 

            if (leaf != NULL && leaf->arrayLenght > 0) {
                printf("\nResultado\n");
                printf("Gen: [%s]\n", leaf->geneName);
                printf("Apariciones: %d\n", leaf->arrayLenght);
                printf("posiciones: ");
                showArray(leaf->head); 
                printf("\n\n");
            } else {
                printf("El gen '%s' no aparece en la secuencia cargada.\n", geneToFind);
            }
            continue;
        }
        if (strcmp(cmd, "bio max") == 0 || strcmp(cmd, "max") == 0)
        {
            if (root == NULL) { printf("Arbol vacio.\n"); continue; }
            int longest = 0;
            findLongest(root, &longest); 
            printf("List of longest lists\n");  
            showByLenght(root, longest); //mostrando genes mayores
            printf("\n");

        } 

        if (strcmp(cmd, "bio min") == 0 || strcmp(cmd, "min") == 0)
        {
            if (root == NULL) { printf("Arbol vacio.\n"); continue; }
            int shortest = -1;
            findShortest(root, &shortest); 
            printf("\nList of shortest lists\n");
            showByLenght(root, shortest); //muestra los genes menores
            printf("\n");

        } 

        if (strcmp(cmd, "bio all") == 0 || strcmp(cmd, "all") == 0)
        {   
            if (root == NULL) { printf("Arbol vacio.\n"); continue; }
            printf("\nAll found genes\n");
            showAll(root); //muestra todos los genes de la cadena 
            printf("\n");

        } 

        if (strcmp(cmd, "bio exit") == 0 || strcmp(cmd, "exit") == 0) 
        {    
            printf(ANSI_YELLOW "Liberando cache y saliendo...\n" ANSI_RESET);

            if (root != NULL) {
                freeMemory(root); //liberacion de memeria 
                free(nameBuffer);
                if (sequenceBuffer) free(sequenceBuffer);
            }
            break;
        }
    }
    return 0;
}
