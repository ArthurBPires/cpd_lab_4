/*
Desenvolvido para testar as funcoes de has para srtings:
-gera um vetor de M posicoes
-mapeia TEST strings aleatorias para essas M posicoes
-Incrementa a posicao do vetor cada vez que uma string é mapeada
-Imprime na tela qual a variacao percentual em relacao a media de cada endereco 
*/

#include <stdio.h>
#include <string.h>

#include <time.h>
#include <stdlib.h>

#define M 200
#define TEST 10000000

char *randstring(size_t length) {

    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ";        
    char *randomString = NULL;

    if (length) {
        randomString = malloc(sizeof(char) * (length +1));

        if (randomString) {            
            for (int n = 0;n < length;n++) {            
                int key = rand() % (int)(sizeof(charset) -1);
                randomString[n] = charset[key];
            }

            randomString[length] = '\0';
        }
    }

    return randomString;
}

unsigned int hash(char* name, int m){
  unsigned int hash = 0;
  int p = 4859;
  for (int i = 0; i < strlen(name); i++){
    hash = (hash * p + (name[i] - 'A' + 1));
  }
  hash = hash % m;
  return hash;
}

int main(){
      int average = TEST / M; 
      int testVet[M] = {0};
      char* randomString = randstring(20);
      for(int i = 0 ; i<TEST ; i++){
            randomString = randstring(20);
            testVet[hash(randomString, M)] += 1;
      }
      for( int i=0 ; i<M ; i++){
            // printf("%d\n", testVet[i]);
            printf("%f\n",100*(float)abs(testVet[i]-average)/(float)average);
      }

      return 0;
}