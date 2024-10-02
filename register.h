/*T1 - SCC503
*/

#ifndef REGISTER_H
#define REGISTER_H

// bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>

// tratamento do funcionamento
#define ERROR_CREATE 0
#define SUCCESS 1
#define NOT_FOUND -1

// estrutura de livros registrados
typedef struct book_t {
    int id;
    char title[100];
    char author[100];
    int byte;
} book_t;

// funcoes
//Manipulam o arquivo de dados
long writeFile(book_t book, FILE *pointer);
book_t readBook(FILE *pointer);

#endif