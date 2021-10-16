/**
 * - Função de hash tem que mapear de 0 a M-1
 * - Resolução de conflitos por endereçamento fechado
 * - Implementar função de inserção
 * - Implementar função de busca que retorna -1 se não encontrar ou um número positivo indicando o número de busca necessárias para encontra-lo.
 * - Fazer cada teste, função de busca do teste deve retornar n+1, sendo n o número de colisões. Caso não encontre, retorna o número máximo de colisões.
 * - Escrever output em arquivos...
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 503 //503, 2503, 5003 e 7507

int hashFunction(char* name) {
    //return name % M;
}

int main() { //Tentativa de função alternativa para função de hash: ficou complicada d+ para ser útil.
    const char *name = "Arthur Brackmann Pires";
    static unsigned long long int n[12];
    int i,k=0;
    
    for(i=0; i<strlen(name); i++) {
        n[k] = ((unsigned long long int)name[i])<<(8*i) | n[k];
        if((i+1) % 8 == 0) k++;
    }
    printf("%s", n);
}

