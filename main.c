#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct utilizada para armazenar as transicoes
typedef struct{
  int partida, chegada;
  char simbolo;
} transicao;

typedef struct{
  int estado;
  int validade;
} controle;

//função auxiliar que cria um vetor de char
char* criaChar(int tam){
  char* simbolos = (char*) malloc ((1+tam)*sizeof(char));

  return simbolos;
}

//função auxiliar que cria um vetor de int
int* criaInt(int tam){
  int* estadosACC = (int*) malloc ((1+tam)*sizeof(int));

  return estadosACC;
}


//função que verifica se a cadeia é valida
controle verificaCadeia(char* cadeia, transicao* transicoes, int quant_transicoes, int inicial){
  controle ctl;
  ctl.validade=1;
  ctl.estado=inicial;
  int tam = strlen(cadeia);
  int validade = 0;
  int estado = inicial;
  char chestado = (char)estado;
  char caractere;
  
  for(int i=0; i<tam; i++){ //percorre a cadeia caractere por caractere
    caractere=cadeia[i];
    for (int j=0; j<quant_transicoes; j++){ //percorre as transicoes
      if (transicoes[j].partida == estado){ //verifica o estado de partida
        if (strcmp(&transicoes[j].simbolo, &caractere) == 0){ //verifa o simbolo
          validade = 1;
          estado = transicoes[j].chegada; 
          break;//proximo estado
        }
      }
      if (ctl.validade == 0){ //se deu falso em algum lugar n importa oq vier depois
        validade = 0;
      }
    }

  }

  //armazena ctl
  ctl.validade=validade;
  ctl.estado=estado;

  return ctl;
}

//função que verifa se o esstado da cadeia é valido nos estados de aceitção
int verificaEstado(int estado, int quant_estadosAceitacao,int*estadosAceitacao){
  for(int i = 0; i<quant_estadosAceitacao; i++){
    if(estadosAceitacao[i] == estado) return 1;
  }
  return 0;
}


int main(){
  //declaração de variaveis
  int quant_estados;
  int quantSimb_terminais;
  int quant_estadosIniciais;
  int quant_estadosAceitacao;
  int quant_cadeias;
  int* estados_aceitacao;
  char* conjSimb_terminais;
  int quant_terminais;
  int quant_transicoes; //maximo 5
  transicao* transicoes;
  char *cadeia;
  char lixo[2]; 
  int i;
  int x, y;
  char ch;
  controle ctl;

//leitura de dados

  scanf("%d", &quant_estados); //quantidade de estados

  //alfabeto
  scanf("%d", &quantSimb_terminais);
  conjSimb_terminais = criaChar(quantSimb_terminais);
  scanf("%s", lixo);
  for (i = 0; i<=quantSimb_terminais; i++){
    scanf("%c", conjSimb_terminais);
  }
  
  
  scanf("%d", &quant_estadosIniciais);//quantidade de estado inicial

  //estados aceitacao
  scanf("%d", &quant_estadosAceitacao);
  estados_aceitacao = criaInt(quant_estadosAceitacao); 
  for(i=0; i<quant_estadosAceitacao; i++){
    scanf("%d", &estados_aceitacao[i]);
  }
  

  //transicoes
  scanf("%d", &quant_transicoes);
  //cria vetor que guarda as transicoes
  transicoes = (transicao*) malloc(quant_transicoes*sizeof(transicao));

  fflush(stdin);
  for(i=0; i<quant_transicoes; i++){
    scanf("%d", &transicoes[i].partida);
    scanf("%s", &transicoes[i].simbolo);
    scanf("%d", &transicoes[i].chegada);
  }
  
  
  //cadeias
  scanf("%d", &quant_cadeias);

  //scanf("%s", lixo);
  for(i=0; i<quant_cadeias; i++){
    cadeia = (char*)malloc(100*sizeof(char));
		scanf("%s", cadeia);
		ctl = verificaCadeia(cadeia, transicoes, quant_transicoes, 0);
		if(ctl.validade == 1 && verificaEstado(ctl.estado, quant_estadosAceitacao, estados_aceitacao)){
			printf("aceita\n");
		} else printf("rejeita\n");
		free(cadeia);
  }
  
return 0;
}
