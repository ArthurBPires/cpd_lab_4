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

typedef struct {
    char key[71]; //Hash table armazena os nomes de uma lista de contatos.
    struct HT *next;
} HT;

unsigned long long hash(char* name) {
    unsigned long long hash = 0;
    int p = 53; //31 se só lower/upper case, 53 se os dois
    
    for (int i = 0; i < strlen(name); i++) {
        hash = (hash * p + (name[i] - 'A' + 1)) % M;
    }
    return hash;
}

int main() {
    HT hashTable[M];
    char name[] = "Arthur Brackmann Pires";

    printf("%llu", hash(name));
}

