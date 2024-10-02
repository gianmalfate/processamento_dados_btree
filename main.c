// T3 - SCC503
//Como pedido pela professora, aqui esta um lembrete de que o grupo fez o trabalho em memoria principal, pois depois
//que descobrimos que deveria ser em arquivo, nao conseguimos mudar o codigo a tempo do prazo de entrega.

#include "register.h"
#include "btree.h"
#include <string.h>
#include <locale.h>


int main(void){
    setlocale(LC_ALL, "pt_BR");
    char op[8];
    book_t livro;

    //criando a Btree
    struct BTreeNode *root = create_node(true);
    do{
        scanf("%s", op);
        op[strlen(op)] = '\0';

        if(strcmp(op, "ADD") == 0){ //INSERCAO
            scanf("%*[^0-9]%d%*[^A-Z]%[^']%*[^A-Z]%[^']", &livro.id, livro.title, livro.author);
            /*Para escrever em arquivo
            FILE *fileBTreePointer;
            fileBTreePointer = fopen("btree_file.bin", "ab");
            */
            //if(searchBTree(root, livro.id, fileBTreePointer) == -1){
            if(searchBTree(root, livro.id) == -1){ 
                FILE *filePointer;
                filePointer = fopen("books_file.bin", "ab");
                long BOS = writeFile(livro, filePointer);
                insert(&root, livro.id, BOS);
                fclose(filePointer);
                printf("----------------------------------------------------------\n");
                printf("Registro inserido\n");
            } else{
                printf("----------------------------------------------------------\n");
                printf("Erro ao inserir registro, chave primária duplicada\n");
            }
            //fclose(fileBTreePointer);

        } else if(strcmp(op, "SEARCH") == 0){
            int id_busca;
            scanf("%*[^0-9]%d",&id_busca);
            //FILE *fileBTreePointer;
            //fileBTreePointer = fopen("btree_file.bin", "ab");
            long res_busca = searchBTree(root, id_busca);
            //long res_busca = searchBTree(root, id_busca, fileBTreePointer);
            if(res_busca == -1){
                printf("----------------------------------------------------------\n");
                printf("Não encontrado\n");
            } else{
                FILE *filePointer;
                filePointer = fopen("books_file.bin", "rb");
                fseek(filePointer, res_busca, SEEK_SET);
                book_t livro_busca = readBook(filePointer);
                printf("----------------------------------------------------------\n");
                printf("%d - %s - %s\n", livro_busca.id, livro_busca.title, livro_busca.author);
                //printf("----------------------------------------------------------\n");
                fclose(filePointer);
                //printf("livro encontrado\n");
            }     
            //fclose(fileBTreePointer);
        }

    } while(strcmp(op, "EXIT") != 0);
    //apos uma secao completa, escreveriamos os dados da BTree em um arquivo, para que ela possa ser recuperada e usada para indexacao de registros
    //write_BTree();
    remove("books_file.bin");
    free(root);
    return 0;
}
