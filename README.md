# Implementação de B-Tree em Memória Principal

## Descrição do Projeto
Este projeto implementa uma árvore B (B-Tree) para armazenar e gerenciar registros de livros em memória principal. A B-Tree é usada para indexar os livros por meio de suas chaves (IDs) e acessar rapidamente os registros armazenados.

## Funcionalidades
- **Inserção de Livros (ADD):** Insere registros de livros na B-Tree e salva as informações em um arquivo binário `books_file.bin`.
- **Busca de Livros (SEARCH):** Busca um livro na B-Tree pelo seu ID e exibe suas informações se encontrado.
- **Remoção de Arquivos:** Ao final da execução, o arquivo binário contendo os livros (`books_file.bin`) é removido.

## Como Executar
1. Compile o programa utilizando um compilador compatível com C:
    ```bash
    gcc -o main main.c btree.c -lm
    ```
2. Execute o programa:
    ```bash
    ./main
    ```
3. Insira os comandos para adicionar ou buscar livros na árvore B:
    - `ADD [ID] [Título] [Autor]` para adicionar um livro.
    - `SEARCH [ID]` para buscar um livro pelo seu ID.
    - `EXIT` para sair do programa.

## Estrutura do Projeto
- **main.c:** Contém o fluxo principal de execução do programa e as operações de inserção e busca.
- **btree.c:** Implementa a estrutura e as operações da árvore B (B-Tree), como inserção e busca.
- **register.c:** Escrita e leitura dos registros de livros em um arquivo binário, manipulando delimitadores e strings.

## Considerações
Devido à natureza do trabalho ter sido realizado em memória principal, não há persistência dos dados da B-Tree em arquivos. Ao encerrar a execução do programa, as informações da árvore são perdidas.

## Autores
- Giancarlo Malfate Caprino
- Henrique Gualberto Marques
- Rafael Scalon Peres Conti
