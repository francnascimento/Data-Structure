#include "FilaDePrioridade.h"

PFILA criarFila(int max){
  PFILA res = (PFILA) malloc(sizeof(FILADEPRIORIDADE));
  res->maxRegistros = max;
  res->arranjo = (PONT*) malloc(sizeof(PONT)*max);
  int i;
  for (i=0;i<max;i++) res->arranjo[i] = NULL;
  res->fila = NULL; 
  return res;
}

bool exibirLog(PFILA f){
  printf("Log [elementos: %i]\n", tamanho(f));
  PONT atual = f->fila;
  while (atual){
    printf("%p[%i;%f;%p]%p ", atual->ant, atual->id, atual->prioridade, atual, atual->prox);
    atual = atual->prox;
  }
  printf("\n\n");
  return true;
}

int tamanho(PFILA f){
  int i = 0;
  PONT atual = f->fila;
  while (atual){
    i++;
    atual = atual->prox;
  }
  return i;
}

bool inserirElemento(PFILA f, int id, float prioridade){
	if(id<0 || id>=f->maxRegistros || f->arranjo[id] != NULL) return false;
	
	PONT reg = (PONT) malloc(sizeof(REGISTRO));
	reg->prioridade = prioridade;
	reg->id   = id;
	reg->ant  = NULL;
	reg->prox = NULL;
	
	if (f->fila) {
		PONT ponteiro = f->fila;
		
		f->arranjo[id] = reg;

		while(ponteiro) {
			if (ponteiro->prioridade > prioridade) {
				f->arranjo[id]->ant  = ponteiro;
				f->arranjo[id]->prox = ponteiro->prox;
			}
			ponteiro = ponteiro->prox;
		}
		if (f->arranjo[id]->ant == NULL && f->arranjo[id]->prox == NULL) {
			f->fila->ant = f->arranjo[id];
			f->arranjo[id]->prox = f->fila;
			f->fila = f->arranjo[id];
		} else {
			if (f->arranjo[id]->prox == NULL) {
				PONT ant = f->arranjo[id]->ant;
				ant->prox = f->arranjo[id];
			} else {
				PONT ant = f->arranjo[id]->ant;
				PONT prox = f->arranjo[id]->prox;
				ant->prox = f->arranjo[id];
				prox->ant = f->arranjo[id];
			}
		}
	} else {
		f->arranjo[id] = reg;
		f->fila = reg;
	}

	return true;
}

bool aumentarPrioridade(PFILA f, int id, float novaPrioridade){
	if(id<0 || id>=f->maxRegistros || f->arranjo[id] == NULL || f->arranjo[id]->prioridade >= novaPrioridade) return false;
	
	f->arranjo[id]->prioridade = novaPrioridade;
	if (f->arranjo[id]->ant == NULL) return true;

	PONT ponteiro = f->arranjo[id]->ant;
	PONT ant = NULL;
	PONT prox = NULL;

	while(ponteiro) {
		if (novaPrioridade > ponteiro->prioridade ) {
			prox = ponteiro;
			ant = ponteiro->ant;
		}
		ponteiro = ponteiro->ant;
	}

	if (prox != NULL) {
		if (f->arranjo[id]->prox == NULL) {
			f->arranjo[id]->ant->prox = NULL;
		} else {
			PONT antTemp  = f->arranjo[id]->ant;
			PONT proxTemp = f->arranjo[id]->prox;
			
			antTemp->prox = f->arranjo[id]->prox;
			proxTemp->ant = f->arranjo[id]->ant;
		}

		f->arranjo[id]->ant = ant;
		f->arranjo[id]->prox = prox;

		if(ant == NULL) {
			f->fila = f->arranjo[id];
		} else {
			ant->prox = f->arranjo[id];
		}
		prox->ant = f->arranjo[id];
	}

	return true;
}

bool reduzirPrioridade(PFILA f, int id, float novaPrioridade){
	if(id<0 || id>=f->maxRegistros || f->arranjo[id] == NULL || f->arranjo[id]->prioridade <= novaPrioridade) return false;
	
	f->arranjo[id]->prioridade = novaPrioridade;
	if (f->arranjo[id]->prox == NULL) return true;

	PONT ponteiro = f->arranjo[id]->prox;
	PONT ant = NULL;
	PONT prox = NULL;

	while(ponteiro) {
		if (ponteiro->prioridade > novaPrioridade) {
			ant = ponteiro;
			prox = ponteiro->prox;
		}
		ponteiro = ponteiro->prox;
	}
	
	if (ant != NULL) {
		if (f->arranjo[id]->ant == NULL) {
			f->arranjo[id]->prox->ant = NULL;
			f->fila = f->arranjo[id]->prox;
		} else {
			PONT antTemp = f->arranjo[id]->ant;
			PONT proxTemp = f->arranjo[id]->prox;
			
			antTemp->prox = f->arranjo[id]->prox;
			proxTemp->ant = f->arranjo[id]->ant;
		}

		f->arranjo[id]->ant = ant;
		f->arranjo[id]->prox = prox;

		if(prox != NULL) {
			prox->ant = f->arranjo[id];
		}
		ant->prox = f->arranjo[id];
		
	}

	return true;
}

PONT removerElemento(PFILA f){

	if (f->fila) {
		f->arranjo[f->fila->id] = NULL;
		if(f->fila->prox != NULL) {
			f->fila = f->fila->prox;
			f->fila->ant = NULL;
		} else {
			f->fila = NULL;
		}
	}
	return f->fila;
}

bool consultarPrioridade(PFILA f, int id, float* resposta){
	if(id<0 || id>=f->maxRegistros || f->arranjo[id] == NULL) return false;

	*resposta = f->arranjo[id]->prioridade;
	return true;
}
