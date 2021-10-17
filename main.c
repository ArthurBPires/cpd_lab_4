/**
 * - Função de hash tem que mapear de 0 a M-1
 * - Resolução de conflitos por endereçamento fechado
 * - Implementar função de inserção
 * - (ignorar este)Implementar função de busca que retorna -1 se não encontrar ou um número positivo indicando o número de busca necessárias para encontra-lo.
 * - Fazer cada teste, função de busca do teste deve retornar n+1, sendo n o número de colisões. Caso não encontre, retorna o número máximo de colisões.
 * - Escrever output em arquivos...
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 503 //503, 2503, 5003 e 7507
#define BUFFER_SIZE 256

typedef struct {
    char key[71]; //Hash table armazena os nomes de uma lista de contatos.
    struct HT *next;
} HT;

unsigned long long hash(char* name) {
    unsigned long long hash = 0;
    int p = 53; //31 se só lower/upper case, 53 se os dois
    
    for (int i = 0; i < strlen(name); i++) {
        hash = (hash * p + (name[i] - 'A' + 1));
    }
    hash %= M;
    return hash;
}

int getName(char buffer[], FILE* file) {
    if (file == NULL) return 0;
    if(!(fgets(buffer, BUFFER_SIZE, file))) return -1;

    // fgets returna <name>\n\0 ->entao isso substitui o \n por \0
    buffer[strlen(buffer) - 2] = '\0';
    return 1;
}

int main(){
    FILE* names;
    char buffer[BUFFER_SIZE];

    if(!(names = fopen("nomes_10000.txt", "r"))){
        printf("Arquivo nao encontrado");
        return 0;
    }

    if ( getName(buffer, names)==1){
        printf("%s\n",buffer);  
    } 

    if ( getName(buffer, names)==1){
        printf("%s\n",buffer);  
    } 

    if ( getName(buffer, names)==1){
        printf("%s\n",buffer);  
    } 

    fclose(names);
    return 0;
}

