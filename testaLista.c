#include <stdio.h>
#include <stdlib.h>

typedef struct _TNo {
	char ch;
	int freq;
	struct _TNo *prox;

}TNo;

TNo * adicionaInicio( TNo *inicio, char ch, int freq);
void mostraLista( TNo *inicio );
void  main( ){
	
	TNo *ini;
	ini = 0; // lista vazia
	
	ini = adicionaInicio( ini, 'a', 10);
	ini = adicionaInicio( ini, 'b', 10);
	ini = adicionaInicio( ini, 'c', 10);
	ini = adicionaInicio( ini, 'd', 10);
	ini = adicionaInicio( ini, 'e', 10);
	ini = adicionaInicio( ini, 'f', 10);
	
	mostraLista( ini );
	
}
// insere no inicio da lista
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

void mostraLista(TNo * inicio ){
	while( inicio ){
		printf("%c ", inicio->ch);
		inicio = inicio->prox;
	}
}

