#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _TNo {
	char ch;
	int freq;
	struct _TNo *dir;
	struct _TNo *esq;
}TNo;

TNo * adicionaInicio( TNo *inicio, char ch, int freq)
{
	// Alocando um novo No
	TNo *novo = (TNo *) calloc(1,sizeof(TNo));
	novo->ch = ch;
	novo->freq = freq;

	novo->dir = inicio;
	inicio = novo;

	return inicio;
}


TNo * adicionaOrdenado( TNo *inicio, char ch, int freq , int * ap)
{
	// Alocando um novo No
	TNo *novo = (TNo *) calloc(1,sizeof(TNo));
	novo->ch = ch;
	novo->freq = freq;
	
	TNo *aux,*anterior;
	
	aux = inicio;
	anterior = NULL;
	
	while(aux && freq > aux->freq){
		anterior = aux;
		aux = aux->dir;
	}
	novo->dir = aux;
	if(anterior){
		anterior->dir = novo;
	}
		
	else {
		inicio = novo;
	}
	
	*ap = *ap + 1;
			
	return inicio;
}


//TNo * geraRaiz(TNo * lista , int stop){
//	int i;
//	
//	for( i = 0; i < stop; i++) {
//		TNo *novo = (TNo *) calloc(1,sizeof(TNo));
//		novo->esq = extraiMinimo(lista);
//		novo->dir = extraiMinimo(lista);
//		novo->freq = novo->esq->freq + novo->dir->freq;
//		
//		printf("Novo no com raiz %d , direita %d , esquerda %d \n " , novo->freq , novo->dir->freq , novo->esq->freq);
//	}
//} 


void mostraLista(TNo * inicio ){
	while( inicio ){
		printf("%c=%d ", inicio->ch, inicio->freq);
		inicio = inicio->dir;
	}
}

TNo * extraiMinimo(TNo * inicio) {
	
	if(inicio->dir){
		inicio = inicio->dir;
	}
	printf("Minimo  = %d \n" , inicio->freq);
	return inicio;
}


int main(){
	
	FILE *file;
	char c; // caractere do arquivo
	int i;
	int *diffLetters = 0;
	int fc[256];
	TNo *ini;
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
			ini = adicionaOrdenado(ini , (char)i , fc[i] , &diffLetters);
		}
	}
	TNo *x = extraiMinimo(ini);
	TNo *y = extraiMinimo(x);
	TNo *o = extraiMinimo(y);
	TNo *p = extraiMinimo(o);
//	geraRaiz(ini , *diffLetters);
//	mostraLista(ini);
	
}
