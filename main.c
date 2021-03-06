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
#include <limits.h>

#define BUFFER_SIZE 256
#define P 1728 
/** Em geral, usamos o primo 31 se só lower/upper case, 53 se os dois.
 *  fineTuning() determinou 1728 como o melhor número para esses dados.
 */

typedef struct HASHTABLE HT;

struct HASHTABLE {
    char key[71]; //Hash table armazena os nomes de uma lista de contatos.
    HT *next;
};

int getName(char buffer[], FILE* file) {
    if (file == NULL) return 0;
    if(!(fgets(buffer, BUFFER_SIZE, file))) return -1;

    // fgets retorna <name>\n\0 ->entao isso substitui o \n por \0
    if (buffer[strlen(buffer) - 1] == '\n') buffer[strlen(buffer) - 1] = '\0';
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
unsigned long long hash(char* name, int m, int p) {
  unsigned long long hash = 0;
  
  for (int i = 0; i < strlen(name); i++)
      hash = (hash * p + (name[i] - 'A' + 1));
  return hash % m;//Diversos testes com valores e constantes diferentes mostraram que tirar o resto no final é muito mais eficiente.
}
//Insere um valor na tabela hash.
void insertHT(HT *hashTable, int m, int p, char *key) {
  HT *x = &hashTable[ hash(key,m,p) ];
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
int searchHT(HT *hashTable, int m, int p, char *key) {
  HT *x = &hashTable[ hash(key,m,p) ];
  int n;
  for (n = 0; x->next != NULL && (strcmp(key,x->key) != 0); x = x->next, n++);
  return n+1;
}
void freeHTCell(HT *hashCell) {
  if(hashCell->next != NULL) freeHTCell(hashCell->next);
  free(hashCell);
}
void freeHT(HT *hashTable, int m) {
  for(int j=0; j<m; j++)
    if(hashTable[j].next != NULL) freeHTCell(hashTable[j].next);
  free(hashTable);
}
//Procura pelo valor de p que minimiza a média de conflitos usando de bruteforce.
int fineTune(FILE* insertFile, FILE* searchFile) {
  char buffer[BUFFER_SIZE];
  int i,j,z,median,pBest = 0;
  float medianMin = INT_MAX;
  int m[4] = {503,2503,5003,7507};
  HT hashTable[7507];
  
  for(int p=0;p<8000;p++) {//Testei até 20000, possívelmente há estouro de representação no llu na hash.
    for (j=0; j<4; j++) {
      initHT(hashTable,m[j]);
      i = median = 0;
      while(getName(buffer,insertFile) != -1)
        insertHT(hashTable,m[j],p,buffer);
      
      while(getName(buffer,searchFile) != -1) {
        median += searchHT(hashTable,m[j],p,buffer);
        i++;
      }
      fseek(insertFile, 0, SEEK_SET);
      fseek(searchFile, 0, SEEK_SET);

      for(int k=0; k<m[j]; k++)
        if(hashTable[k].next != NULL) freeHTCell(hashTable[k].next);
    }
    if(medianMin > (float)median/i) {
      medianMin = (float)median/i;
      pBest = p;
    }
  }
  return pBest;
}
int main() {
  char buffer[BUFFER_SIZE];
  int i,p,median,max,maxAux,m = 7507; //503, 2503, 5003 e 7507
  i = median = max = maxAux = 0;
  HT *hashTable;
  hashTable = malloc(m * sizeof(HT));
  initHT(hashTable, m);

  // strings to create the output file name
  char outputFileName[20] = "experimento";
  char number[5];
  char* txt = ".txt";

  // 2 input files and the output file
  FILE* insertFile = fopen("nomes_10000.txt", "r");
  FILE* searchFile = fopen("consultas.txt", "r");
  FILE* outputFile;
  p = P; //fineTune(insertFile, searchFile);

  // strings and auxiliar strings to write to output File
  char nameAndSearches[128] = "";   
  char searches[10] = "";
  char medianAndMaximum[128] = "";
  char auxString[128] = "";
  
  // Creates Output File Name based on m and opens the file
  snprintf(number, sizeof(number), "%d", m);
  strcat(outputFileName, number);
  strcat(outputFileName,txt);

  outputFile = fopen(outputFileName,"w+");

  // insert the names into HASHTABLE
  while(getName(buffer,insertFile) != -1)
    insertHT(hashTable,m,p,buffer);
  
  // searches for name in HASHTBLE
  while(getName(buffer,searchFile) != -1){
    maxAux = searchHT(hashTable,m,p,buffer);
    median += maxAux;
    if(max < maxAux) max = maxAux;
    i++;

    // Creates the string "<name> <searches>\n" and writes to file
    strcpy(nameAndSearches, buffer);
    snprintf(searches, sizeof(searches), " %d\n", maxAux);
    strcat(nameAndSearches,searches);

    fwrite(nameAndSearches,1,strlen(nameAndSearches), outputFile);
  }
  // creates the string "MEDIA <value>\n MAXIMO <value>\n" and writes to file
  strcat(medianAndMaximum,"MEDIA");
  snprintf(auxString, sizeof(auxString), " %.2f\n",(float)median/i );
  strcat(medianAndMaximum,auxString);
  strcat(medianAndMaximum,"MAXIMO");
  snprintf(auxString, sizeof(auxString), " %d\n", max);
  strcat(medianAndMaximum,auxString);
  
  fwrite(medianAndMaximum,1,strlen(medianAndMaximum), outputFile);

  // frees memory and closes files
  freeHT(hashTable,m);
  fclose(insertFile);
  fclose(searchFile);
  fclose(outputFile);

  return 0;
}