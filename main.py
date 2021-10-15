#Função de hash tem que mapear de 0 a M-1
#Resolução de conflitos por endereçamento fechado
#Implementar função de inserção
#Implementar função de busca que retorna -1 se não encontrar ou um número positivo indicando o número de busca necessárias para encontra-lo.
#Fazer cada teste, função de busca do teste deve retornar n+1, sendo n o número de colisões. Caso não encontre, retorna o número máximo de colisões.
#Escrever output em arquivos...

hashFunction = lambda string,M : string % M
