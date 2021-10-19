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

#define BUFFER_SIZE 256

typedef struct HASHTABLE HT;

struct HASHTABLE {
    char key[71]; //Hash table armazena os nomes de uma lista de contatos.
    HT *next;
};

int getName(char buffer[], FILE* file) {
    if (file == NULL) return 0;
    if(!(fgets(buffer, BUFFER_SIZE, file))) return -1;

    // fgets returna <name>\n\0 ->entao isso substitui o \n por \0
    buffer[strlen(buffer) - 2] = '\0';
    return 1;
}

//Inicializa os valores da tabela hash
void initHT(HT* hashTable, int m) {
  for (int i = 0; i<m; i++) {
    strcpy(hashTable[i].key,"");
    hashTable[i].next= NULL;
  }
}

//Função hash que corresponde uma string à um inteiro de 0 a m-1.
unsigned long long hash(char* name, int m) {
  unsigned long long hash = 0;
  int p = 53; //31 se só lower/upper case, 53 se os dois
  
  for (int i = 0; i < strlen(name); i++) {
      hash = (hash * p + (name[i] - 'A' + 1)) % m;
  }
  return hash;
}
//Insere um valor na tabela hash.
void insertHT(HT *hashTable, int m, char *key) {
  HT *x = &hashTable[ hash(key,m) ];
  while (x->next != NULL && (strcmp(key,x->key) != 0)) x = x->next;
  if (x->next != NULL) return;
  else if (!strcmp("",x->key)) strcpy(x->key,key);
  else {
    x->next = (HT*)malloc(sizeof(HT));
    strcpy(x->next->key,key);
    x->next->next = NULL;
  }
}
//Procura por um nome na tabela hash.
int searchHT(HT *hashTable, int m, char *key) {
  HT *x = &hashTable[ hash(key,m) ];
  int n;
  for (n = 0; x != NULL && (strcmp(key,x->key) != 0); x = x->next, n++);
  //printf("%s", x->key);
  return n+1;
}

int main() {
  char buffer[BUFFER_SIZE];
  int i,median,max,maxAux,m = 503; //503, 2503, 5003 e 7507
  i = median = 0;
  HT hashTable[m];
  initHT(hashTable, m);

  FILE* insertFile = fopen("nomes_10000.txt", "r");
  while(getName(buffer,insertFile) != -1){
    insertHT(hashTable,m,buffer);
  }
  fclose(insertFile);

  FILE* searchFile = fopen("consultas.txt", "r");
  while(getName(buffer,searchFile) != -1){
    maxAux = searchHT(hashTable, m,buffer);
    median += maxAux;
    if(max < maxAux) max = maxAux;
    printf("%s %d\n", buffer, searchHT(hashTable, m,buffer));
    i++;
  }
  fclose(searchFile);

  printf("MEDIA %.2f\nMAXIMO %d\n",(float)median/i,max);

  return 0;
}
