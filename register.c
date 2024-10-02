

#include "register.h"
#include <string.h>
#include <locale.h>

// funcao para escrever registro no arquivo binario
long writeFile(book_t book, FILE *pointer) {
    fseek(pointer, 0, SEEK_END); 
    long byteoffset = ftell(pointer);
    // caracteres delimitadores
    char titleDelimiter = '|';
    char registerDelimiter = -1;

    int authorLength = strlen(book.author);

    // escrita binaria das informacoes no arquivo
    fwrite(&book.id, sizeof(int), 1, pointer);
    fwrite(&book.title, sizeof(char), strlen(book.title), pointer);
    fwrite(&titleDelimiter, sizeof(char), 1, pointer);
    fwrite(&authorLength, sizeof(int), 1, pointer);
    fwrite(&book.author, sizeof(char), strlen(book.author), pointer);
    fwrite(&registerDelimiter, sizeof(char), 1, pointer);

    return byteoffset;
    //calculateBytesOffSet(book); // byte off set

}

book_t readBook(FILE *pointer){
    book_t book;
    int authorLength;

    // caracteres delimitadores
    char titleDelimiter = '|';
    char registerDelimiter = -1;

    // leitura do id
    fread(&book.id, sizeof(int), 1, pointer);

    // leitura do titulo
    char title[100];
    int i = 0;
    char c = fgetc(pointer);
    while(c != '|') {
        title[i++] = c;
        c = fgetc(pointer);
    }
    title[i] = '\0';
    strcpy(book.title, title);

    //leitura do indicador do tamanho da string do autor
    fread(&authorLength, sizeof(int), 1, pointer);

    // leitura do autor
    fread(&book.author, sizeof(char), authorLength, pointer);
    book.author[authorLength]='\0';
    c = fgetc(pointer);

    return book;
}
