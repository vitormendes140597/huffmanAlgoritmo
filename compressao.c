#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _TNo {
	char ch;
	int freq;
	struct _TNo *prox;
	struct _TNo *dir;
	struct _TNo *esq;
}TNo;

TNo *ini;
TNo *teste;

TNo * adicionaInicio( TNo *inicio, char ch, int freq)
{
	// Alocando um novo No
	TNo *novo = (TNo *) calloc(1,sizeof(TNo));
	novo->ch = ch;
	novo->freq = freq;

	novo->prox = inicio;
	inicio = novo;

	return inicio;
}


TNo * adicionaOrdenado(char ch, int freq , int * ap)
{
	// Alocando um novo No
	TNo *novo = (TNo *) calloc(1,sizeof(TNo));
	novo->ch = ch;
	novo->freq = freq;
	
	TNo *aux,*anterior;
	
	aux = ini;
	anterior = NULL;
	
	while(aux && freq > aux->freq){
		anterior = aux;
		aux = aux->prox;
	}
	novo->prox = aux;
	if(anterior){
		anterior->prox = novo;
	}
		
	else {
		ini = novo;
	}
	
	*ap = *ap + 1;
			
	return ini;
}


void insereCrescente(TNo * novo)
{	
	TNo *aux,*anterior;
	
	aux = ini;
	anterior = NULL;
	
	while(aux && novo->freq > aux->freq){
		anterior = aux;
		aux = aux->prox;
	}
	novo->prox = aux;
	if(anterior){
		anterior->prox = novo;
	}
		
	else {
		ini = novo;
	}
}

TNo * extraiMinimo() {
	TNo * aux = ini;
	
	if(ini->prox){
		ini = ini->prox;
	}
	return aux;
}

TNo * geraRaiz(int stop){
	int i;
	
	for( i = 0; i < stop; i++) {
		TNo *novo = (TNo *) calloc(1,sizeof(TNo));
		novo->ch = 'x';
		novo->esq = extraiMinimo(ini);
		novo->dir = extraiMinimo(ini);
		novo->freq = novo->esq->freq + novo->dir->freq;
		insereCrescente(novo);
//		printf("Novo freq = %d char=%c, esquerda fre = %d char = %c, direita freq = %d char = %c\n" , novo->freq, novo->ch , novo->esq->freq , novo->esq->ch,  novo->dir->freq , novo->dir->ch);
	}
} 


void percorrePosOrdem(TNo * ini , int i){
	
	if(ini){
		printf("%d " , ini->freq);
		percorrePosOrdem(ini->esq , i+1);
		percorrePosOrdem(ini->dir , i + 1);
		
	}	
}

void mostraLista(TNo * inicio ){
	while( inicio ){
		printf("%c=%d ", inicio->ch, inicio->freq);
		inicio = inicio->prox;
	}
}

int main(){
	
	FILE *file;
	char c; // caractere do arquivo
	int i;
	int *diffLetters = 0;
	int fc[256];
	
	ini = 0;
	
	file = fopen("base.txt" , "r");
	
	memset(fc, 0, 256*sizeof(int));
	// Copia caracteres do arquivo para o vetor fc
	if(file) {
		while((c = getc(file)) != EOF) {
			fc[c]++;
		}
	}
	
	// Cria a linked list
	for(i = 0; i<256; i++) {
		if(fc[i] != 0) {
			ini = adicionaOrdenado((char)i , fc[i] , &diffLetters);
		}
	}
	
	
	
	geraRaiz(diffLetters);
	percorrePosOrdem(ini , -1);
	
}
