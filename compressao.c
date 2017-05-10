#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _TNo {
	int freq;
	char ch;
	char pref[50];
	struct _TNo *prox;
	struct _TNo *dir;
	struct _TNo *esq;
}TNo;

struct tabelaPrefixo{
	char prefixo[50];
};

TNo *ini;
char array[50];
struct tabelaPrefixo listaTabelaPrefixo[256];

TNo * adicionaInicio( TNo *inicio, char ch, int freq){
	// Alocando um novo No
	TNo *novo = (TNo *) calloc(1,sizeof(TNo));
	novo->ch = ch;
	novo->freq = freq;

	novo->prox = inicio;
	inicio = novo;

	return inicio;
}

TNo * adicionaOrdenado(char ch, int freq , int * ap){
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

void insereCrescente(TNo * novo){	
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

TNo * geraRaiz(TNo * no,int stop){
	int i;
	TNo*novo;
	for( i = 0; i < stop; i++) {
		novo = (TNo *) calloc(1,sizeof(TNo));
		novo->ch = 'x';
		novo->esq = extraiMinimo(no);
		novo->dir = extraiMinimo(no);
		novo->freq = novo->esq->freq + novo->dir->freq;
		insereCrescente(novo);
	}
	return novo;
} 

void percorrePosOrdem(TNo * inicio , int i, char prefixoDeCadaChar[]){
	
	// verifica se o no existe
	if(!inicio)
	{
		return;
	}
	
	prefixoDeCadaChar[i] = '0';
	
	percorrePosOrdem(inicio->esq , i+1 , prefixoDeCadaChar);
	
	prefixoDeCadaChar[i] = '1';
	
	percorrePosOrdem(inicio->dir , i+1 , prefixoDeCadaChar);
	
	prefixoDeCadaChar[i] = 0;
	
	if(inicio -> ch != 'x')
	{
		strcpy(listaTabelaPrefixo[inicio->ch].prefixo, prefixoDeCadaChar);
	}
}

void mostraLista(TNo * inicio ){
	while( inicio ){
		printf("%c=%d ", inicio->ch, inicio->freq);
		inicio = inicio->prox;
	}
}

void escrever_arquivo(int freq[]){
	int i;
	char x;
	int count=0;
	
	FILE *f = fopen("saida.txt", "w");
	if (f == NULL){
	    printf("Error opening file!\n");
	    exit(1);
	}
    for(i=0;i <256;i++){
    	if(freq[i]>0){
    		count++;
    	}
	}
	
	//quantidade de caracteres diferentes
	fprintf(f,"%d \n",count);
	
	for(i=0;i <256;i++){
    	if(freq[i]>0){
    		fprintf(f,"%d %c ", freq[i], (char)i);
    	}
	}	
	
	fprintf(f,"\n");
	
	FILE *file;
	char c; // caractere do arquivo
	file = fopen("base.txt" , "r");
	
	if(file) {
		while((c = getc(file)) != EOF) {
			fprintf(f,"%s", listaTabelaPrefixo[c].prefixo);
		}
	}
	fclose(file);

	fclose(f);
}


TNo *remontaArvore(){
	
	TNo *novo;
	
	FILE *file;
	char c;
	char ch;
	int parada;
	int freq;
	int diffLetters = 0;
	int i;
	file = fopen("saida.txt" , "r");
	
	
	if(!file ){
    	printf("\nfalha na abertura do arquivo\n");
   	}

	fscanf(file,"%d",&parada);
	for(i = 0; i<parada;i++){
		fscanf(file , "%d %c" , &freq , &ch);
		printf("%d , %c \n" , freq , ch);
		novo = adicionaOrdenado(ch,freq,&diffLetters);
	}
	
	fclose(file);
	
	return novo;
}

char * recuperaPrefixo(TNo * no) {
	FILE *file;
	char c;
	char line[256];
	char *prefix = (char *) malloc(256 * sizeof(char));
	int count = 0;
	int i =0;
	int j , length ;
	
	file = fopen("saida.txt" , "r");
	if (file == NULL){
	    printf("Error opening file!\n");
	    exit(1);
	}
	
	while( (c = fgetc(file)) != EOF ) {
		if(c == '\n'){
			count++;
		}
		if(count == 2) {
			line[i]=c;
			i++;
		}
	}
	fclose(file);
	
	length = (int)strlen(line);
	for(i = 0; i < length; i++){
		if(line[i] == '0' || line[i]== '1'){
			prefix[j] = line[i];
			j++;
		}
	}
	
	
	return prefix;
}

void descompacta(TNo *no , char arrPrefixo[], int arrLength , int i) {
	while(no){
		no->esq;
		printf("s");
	}
} 


int tamanhoPrefixo (char prefixo[]) {
	int i , posicoesValidas;
	posicoesValidas  = 0;
	
	for(i =0; i < 256; i++) {
		if(prefixo[i] == '0' || prefixo[i] == '1'){
			posicoesValidas = posicoesValidas + 1;
		}
	}
	return posicoesValidas; 
}

int main(){
	
	FILE *file;
	char c; // caractere do arquivo
	int i;
	int *diffLetters = 0;
	int fc[256];
	char *prefixoRemontado;
	ini = 0;
	
	file = fopen("base.txt" , "r");
	
	if (file == NULL){
	    printf("Error opening file!\n");
	    exit(1);
	}
	
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
	
 	geraRaiz(ini,diffLetters);
	percorrePosOrdem(ini , 0 , array);
	
	escrever_arquivo(fc);
	
	//Descompactar
	TNo * novaRaiz;	
	novaRaiz = remontaArvore();
	novaRaiz = geraRaiz(novaRaiz, diffLetters);
	prefixoRemontado = recuperaPrefixo(novaRaiz);
	int x = tamanhoPrefixo(prefixoRemontado);
	
	
	
}
