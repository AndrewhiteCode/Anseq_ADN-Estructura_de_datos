# Anseq_ADN – Estructura de Datos

Proyecto en C para la asignatura **Estructura de Datos **, cuyo objetivo es
**reconocer genes en una secuencia de ADN** utilizando un **árbol Trie 4-ario**
y almacenar las posiciones donde aparece cada gen.


---

##  Descripción general

El programa:

1. Construye un **árbol Trie 4-ario** con letras `{A, C, G, T}` hasta una
   altura dada (en el `main` actual, altura 3).
2. Recorre una **secuencia de ADN** fija:
   ```c
   "ATCGATCGATCGATTCGA"
   ```
3. Para un largo de gen `m` (en el código actual, `m = 3`):
   - Genera todas las ventanas de tamaño `m` de la secuencia.
   - Para cada gen (p. ej. `"ATC"`, `"TCG"`, …):
     - Busca la hoja correspondiente en el trie.
     - Inserta la posición inicial del gen en una **lista enlazada** asociada a
       esa hoja.
     - Imprime mensajes de depuración indicando el camino y la inserción.

La estructura final permite saber, para cada gen posible de longitud `m`,
**en qué índices de la secuencia aparece** (almacenado en una lista de `arrayNode`).

---

##  Estructura del proyecto

Archivos principales:

- `main.c`  
  Crea el trie, define la secuencia de prueba y llama a
  `genesRecognition()` para cargar los genes en el árbol.

- `struct.h`  
  Contiene:
  - Definición de tipos opacos:
    - `arrayNode`, `trieTree`, `treeNodePos`
  - Estructuras:
    ```c
    struct arrayNode {
        int index;
        arrayNode next;
    };

    struct tTreeNode {
        char l;          // letra del nodo (A, C, G, T o 'R' en la raíz)
        trieTree A;
        trieTree C;
        trieTree G;
        trieTree T;
        arrayNode head;  // lista de índices en la hoja (si aplica)
    };
    ```
  - Prototipos de funciones:
    - `trieTree createTrieTree(int treeSize, char letter);`
    - `trieTree findGeneLeaf(trieTree root, const char *gene);`
    - `void genesRecognition(char *sequence, int seqLenght, int geneLenght, trieTree root);`
    - `void insertArrayNode(arrayNode currNode, arrayNode newArrayNode);`
    - `void insertGene(trieTree root, const char *gene, int genePos);`

- `trie.c`  
  Implementa las funciones de manejo del trie:
  - `createTrieTree(...)`  
    Crea recursivamente un trie de altura `treeSize` y reserva memoria para
    cada nodo.
  - `findGeneLeaf(...)`  
    Recorre el trie siguiendo las letras del gen (`A/C/G/T`) hasta llegar a
    la hoja correspondiente.
  - `insertArrayNode(...)`  
    Inserta un nuevo nodo al final de la lista de índices de un gen.
  - `insertGene(...)`  
    Combina lo anterior:
    - Busca la hoja del gen.
    - Reserva un `arrayNode` nuevo.
    - Lo inserta en la lista `head` de esa hoja.

- `sequence.c`  
  Implementa:
  - `genesRecognition(char *sequence, int seqLenght, int geneLenght, trieTree root)`  
    Recorre la secuencia y, para cada posición `i`, construye el gen de largo
    `geneLenght` empezando en `sequence[i]`, luego llama a `insertGene(root, gene, i)`.

- `Makefile`  
  Archivo de automatización para compilar el proyecto.

- `Doxyfile` (no se incluye en repo por defecto, pero se menciona su uso):  
  Archivo de configuración para generar documentación con **Doxygen**.

---

##  Compilación con `make`

El proyecto incluye un `Makefile` sencillo que:

- Compila los archivos:
  - `main.c`
  - `trie.c`
  - `sequence.c`
- Genera archivos objeto `.o`
- Enlaza todo en un ejecutable (por ejemplo `bio`)

### Objetivo principal

```bash
make
```

Esto ejecuta internamente algo equivalente a:

```bash
gcc -Wall -Wextra -pedantic -std=c11 -c main.c -o main.o
gcc -Wall -Wextra -pedantic -std=c11 -c trie.c -o trie.o
gcc -Wall -Wextra -pedantic -std=c11 -c sequence.c -o sequence.o
gcc -Wall -Wextra -pedantic -std=c11 -o bio main.o trie.o sequence.o
```

### Limpiar archivos generados

Para borrar los `.o` y el ejecutable:

```bash
make clean
```

*(Depende del contenido exacto del `Makefile`, pero la convención habitual es
que exista un objetivo `clean` que haga algo como `rm -f *.o bio`.)*

---

##  Ejecución

Una vez compilado:

```bash
./bio
```

El programa:

1. Construye un trie de altura `3` con raíz `'R'`.
2. Usa la secuencia:
   ```c
   "ATCGATCGATCGATTCGA"
   ```
3. Usa `geneLenght = 3` para generar todos los genes posibles de 3 letras.
4. Inserta cada gen en el trie y muestra mensajes de depuración para:
   - El gen que se está procesando.
   - El camino por el trie.
   - La inserción de la posición en la lista de índices.

---

##  Documentación con Doxygen

Para generar documentación HTML del código:

1. Crear un archivo de configuración:

   ```bash
   doxygen -g Doxyfile
   ```

2. Editar el `Doxyfile` con los ajustes recomendados, por ejemplo:

   ```txt
   PROJECT_NAME      = "Anseq_ADN"
   OUTPUT_DIRECTORY  = docs
   GENERATE_HTML     = YES
   HTML_OUTPUT       = html
   EXTRACT_ALL       = YES
   RECURSIVE         = YES
   FILE_PATTERNS     = *.c *.h
   ```

3. Generar la documentación:

   ```bash
   doxygen Doxyfile
   ```

4. Abrir en el navegador:

   ```text
   docs/html/index.html
   ```

Ahí se podrá navegar por:
- Lista de archivos (`main.c`, `trie.c`, `sequence.c`, `struct.h`).
- Estructuras (`arrayNode`, `tTreeNode`).
- Funciones (`createTrieTree`, `insertGene`, `genesRecognition`, etc.).
- Comentarios Doxygen añadidos en el código.

---

##  Resumen

Este proyecto implementa:

- Un **Trie 4-ario** para representar genes de ADN.
- Una **lista enlazada de índices** por cada gen.
- Un flujo simple:
  - Construcción del trie.
  - Recorrido de una secuencia fija.
  - Inserción de todas las apariciones de cada gen en el árbol.
- Soporte para:
  - Compilación fácil con `make`.
  - Documentación automática con **Doxygen** (vía `Doxyfile`).


