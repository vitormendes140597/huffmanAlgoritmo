#include <stdio.h>
#include <stdlib.h>

typedef struct _TNo {
	char ch;
	int freq;
	struct _TNo *prox;

}TNo;

int capturaFrequencia(char *vetor , int qtdeLetras) {
	
	int *freq;
	freq = (int*) calloc(256,sizeof(int)); 
	int converted;
	int i = 0;
	
	for(i = 0; i < qtdeLetras; i++){
		converted = (int) vetor[i];
		freq[converted]++;
	} 
	return freq;	
}

TNo * adicionaInicio( TNo *inicio, char ch, int freq)
{
	// Alocando um novo No
	TNo *novo = (TNo *) calloc(1,sizeof(TNo));
	novo->ch = ch;
	novo->freq = freq;
	
	TNo *cp = (TNo *) calloc(1,sizeof(TNo));
	cp->ch = inicio->ch;
	cp->freq = inicio->freq;
	cp->prox = inicio->prox;
		
	if(inicio == 0) {
		novo->prox = inicio;
		inicio = novo;
	}

	return inicio;
}

void mostraLista(TNo * inicio ){
	while( inicio ){
		printf("%d ", inicio->freq);
		inicio = inicio->prox;
	}
}


int main(){
	
	FILE *file;
	char c; // caractere do arquivo
	int i = 0;
	char fc[256];
	int *freq;
	TNo *ini;
	ini = 0;
	
	file = fopen("base.txt" , "r");
	
	// Copia caracteres do arquivo para o vetor fc
	if(file) {
		while((c = getc(file)) != EOF) {
			fc[i] = c;
			i++;		
		}
	}
	
	freq = capturaFrequencia(fc , 8);
	// Cria a linked list
	for(i = 0; i<256; i++) {
		if(freq[i] != 0) {
			ini = adicionaInicio(ini , (char)i , freq[i]);
		}
	}
	
	mostraLista(ini);

}

