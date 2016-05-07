#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int n_bytes(int valor){								// funcao para retornar o numero de bytes que o valor recebido possui
	if(valor < 10)
		return 1;
	else if(valor < 100)
		return 2;
	else if(valor < 1000)
		return 3;
	else if(valor < 10000)
		return 4;
	else if(valor < 100000)
		return 5;
	else if(valor < 1000000)
		return 6;
}
float TAM(FILE *f_entrada){						  // funcao para calcular o "tamanho" do arquivo de entrada em bytes
	float posicao = ftell(f_entrada);			  // guarda a posicao do arquivo
	float tamanho;
	fseek(f_entrada, 0 ,SEEK_END);		 		  // calcula o "tamanho" do arquivo (conta quantos caracteres o arquivo possui)
	tamanho = ftell(f_entrada);			  		  // guarda o "tamanho" do arquivo
	fseek(f_entrada, posicao, SEEK_SET);          // recupera a posicao antiga do arquivo

	return tamanho;				                  // retorna o valor calculado em bytes
}
int main(){

	FILE *f = fopen("input.txt","w");
	int i,j;
	//double cont=0;
	//double lim =  6442450944; 6gb //..... 10485760 10mb // 5mb 5242880 // 100mb 104857600
	//double lim = 10485760*100;
	float pos=0;

	int valor;
	srand(time(NULL));
	printf("gerando arquivo...\n");
	while(pos < 6442450944){	// ~6,4gb
	//while(cont < lim){		
		valor = rand()%100000;
		fprintf(f,"%i ",valor);
		//cont = cont + n_bytes(valor) + 1;	
		pos = ftell(f);
	}
	fclose(f);	
	printf("arquivo 'input.txt' gerado.\n");
}
