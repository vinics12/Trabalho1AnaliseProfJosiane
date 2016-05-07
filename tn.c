#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int J;
typedef struct Registro{ // registro para utilizarmos uma fila dinamica
	int valor;	
	struct Registro *prox; 
}reg;
//==================================ORDENAÇÃO=============================
	//================MERGE================================================
	void merge(int vet[], int i, int m, int f){
		int ii=i,mm=m+1,j=0,*tmp=(int*)malloc(sizeof(int)*(f-i+1));

		while(ii<=m || mm<=f){
			if(ii==m+1){
				tmp[j]=vet[mm];
				mm++;
			}
			else if(mm==f+1){
				tmp[j]=vet[ii];
				ii++;
			}
			else if(vet[ii]<vet[mm]){
				tmp[j]=vet[ii];
				ii++;
			}
			else{
				tmp[j]=vet[mm];
				mm++;
			}
			j++;
		}
		for( ii = i; ii <= f; ii++ )
		{
			vet[ii] = tmp[ii-i];
		}
		free(tmp);
	}
	//================MERGESORT================================================
	void mergesort(int vet[], int i , int f){	
		if(i<f){
			int m=(i+f)/2;
			mergesort(vet,i,m);
			mergesort(vet,m+1,f);
			merge(vet,i,m,f);
		}
	}
//========================================================================
float TAM(FILE *f_entrada){						  // funcao para calcular o "tamanho" do arquivo de entrada em bytes
	float posicao = ftell(f_entrada);			  // guarda a posicao do arquivo
	float tamanho;
	fseek(f_entrada, 0 ,SEEK_END);		 		  // calcula o "tamanho" do arquivo (conta quantos caracteres o arquivo possui)
	tamanho = ftell(f_entrada);			  		  // guarda o "tamanho" do arquivo
	fseek(f_entrada, posicao, SEEK_SET);          // recupera a posicao antiga do arquivo

	return tamanho;				                  // retorna o valor calculado em bytes
}
int pegaValor(FILE *f_entrada){						// funcao para fazer a leitura do valor no arquivo de entrada	
	int valor;
	char c;	

		fscanf(f_entrada,"%i",&valor);	// lê um valor inteiro do arquivo
		fscanf(f_entrada,"%c",&c);		// lê o caractere que separa os valores inteiros	
	
	if(feof(f_entrada))				// if o arquivo estiver vazio retorna -1
		return -1;

	return valor;
}
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
int insere(reg *inicio, int valor){	//insere na estrutra de dados o valo lido do aruqivo de entrada
	reg* novo = (reg*)malloc(sizeof(reg));
	novo->valor = valor;
	if(inicio->prox != NULL){
		novo->prox = inicio->prox;
		inicio->prox = novo;
	}
	else{
		novo->prox = NULL;
		inicio->prox = novo;					
	}	
}
void escreveSaida(char nome_particao[],int *vet, int fim){	//escreve no arquivo o vetor recebido
	FILE *f_saida = fopen(nome_particao,"w");
	int i;	
	for(i=0;i<fim;i++)		
		fprintf(f_saida,"%i ",vet[i]);		// escreve um valor no arquivo			
	fclose(f_saida);
}
int next(int chave[],int k){			// função para verificar se há pendencias
	int i;
	for(i=0;i<k;i++){
		if(chave[i]==0)
			return 0;
	}
	return 1;
}
void zerar(int vetor[],int k){			// função para zerar o vetor recebido
	int i;
	for(i=0;i<k;i++)
		vetor[i]=0;		
}
float n_posicoes(int *memoria,int *total, FILE *f_entrada,float pos){ // retorna quantas posicoes o vetor vai precisar
	int valor,cont;
	char c;	
	*total = 0;
	pos = ftell(f_entrada);	
	for(cont=0;cont<(*memoria-10);cont++){															
		if(feof(f_entrada))
			break;						

		fscanf(f_entrada,"%i",&valor);	
		fscanf(f_entrada,"%c",&c);			
		
		cont = cont + n_bytes(valor);					
		*total = *total+1;
	}	
	return pos;
}
void proximoNome(char nome_particao[]){ //nomeclatura inicial parteXXX.txt
		if(nome_particao[7] < '9')			//parte X X '1~8'
			nome_particao[7]++;
		else{								// parte X X 9 
			if(nome_particao[6] < '9'){		// parte X '1~8' 9
				nome_particao[6]++;
				nome_particao[7] = '0';
			}else{							// parte X 9 9
				nome_particao[5]++;
				nome_particao[6] = '0';
				nome_particao[7] = '0';
			}
		}
}
void incrementa(char nome_particao[],int n,char lado){	//controle da nomeclatura
	int i;
	if(lado == 'D')
		for(i=0;i<n;i++){ //4,5,6
			if(nome_particao[6] < '9')			// ...- X X '1~8'
				nome_particao[6]++;
			else{								// ...- X X 9 
				if(nome_particao[5] < '9'){		// ...- X '1~8' 9
					nome_particao[5]++;
					nome_particao[6] = '0';
				}else{							// ...- X 9 9
					nome_particao[4]++;
					nome_particao[5] = '0';
					nome_particao[6] = '0';
				}
			}
		}		
	else
		for(i=0;i<n;i++){ //0,1,2
			if(nome_particao[2] < '9')			// X X '1~8'-...
				nome_particao[2]++;
			else{								// X X 9 -...
				if(nome_particao[1] < '9'){		// X '1~8' 9-...
					nome_particao[1]++;
					nome_particao[2] = '0';
				}else{							// X 9 9-....
					nome_particao[0]++;
					nome_particao[1] = '0';
					nome_particao[2] = '0';
				}
			}
		}			
}
void proximoNomeL(char nome_particao[],int k,int nivel,int chave){ //nomeclatura final XXX-XXX.txt 	
	int i;	
	if(nivel > 0){	
		char c1 = nome_particao[2], c2 = nome_particao[6];
		int x1 = c1, x2 = c2, x; 
		x = x2-x1;
		if(x<0)
			x = x+10;
		x = x+1;				
		if(chave > 0){			
			for(i=0;i<chave;i++){
				incrementa(nome_particao,x,'D');
				incrementa(nome_particao,x,'E');
			}
		}
		else if(chave==0){ // proximo bloco						
			incrementa(nome_particao,x,'D');
			incrementa(nome_particao,x,'E');			
		}else{											
			for(i=0;i<k;i++){
				incrementa(nome_particao,x,'D');
				incrementa(nome_particao,x,'E');						
			}
		}
	}
	if(nivel == 0){ // lendo parteXXX.txt
		if(chave > 0) 
			for(i=0;i < chave;i++)
				proximoNome(nome_particao);
		else if(chave < 0)
			for(i=0;i < k;i++) // proximo bloco
				proximoNome(nome_particao);			
	}
}
void proximoNomeE(char nome_particao[],int k,int nivel,int chave){ // controle da nomeclatura para escrever os arquivo
	char c1 = nome_particao[2], c2 = nome_particao[6];
	int x1 = c1, x2 = c2, x; 
	x = x2-x1;	
	if(x<0)
		x = x+10;
	x = x+1;
	incrementa(nome_particao,x,'D');
	incrementa(nome_particao,x,'E');		
}
int particionar(char entrada[], int *memoria){    // função para dividir o arquivo de entrada em varios com "tamanho" limitado por 'm'
	*memoria = *memoria*1048576; 				    // converter de megaByte para byte(*1048576) // Gb-> byte = *1073741824 (6gb->6.442.450.944)// kb-> byte = *1024		
	//*memoria = *memoria*1024;
	float tamanho_entrada,pos=0;						  	// tamanho do arquivo de entrada 
	int total,cont,valor,bkp; 							  	// contador de byte ; variavel para armazenar os valores do arquivo
	int i,n_particoes;
	char nome_particao[13] = "parte001.txt";	  	// vetor com o nome das particoes	
	FILE *f_entrada; 							  	// leitura do arquivo de entrada	
	reg* inicio;

	if(!(f_entrada = fopen(entrada,"r")))
		printf("Arquivo de entrada nao foi encontrado\n");

	tamanho_entrada = TAM(f_entrada);			  	// chamada da funcao que calcula o "tabamnho" do arquivo de entrada em bytes
	n_particoes = (tamanho_entrada/(*memoria))+1;	  	// numero de particoes que o programa ira gerar	
	printf("N_PARTICOES: %i\n",n_particoes);
	printf("LIMITE MEMORIRA: %i\n", *memoria);
	
	for(i=0;i<n_particoes;i++){					  	// laco para controle de particoes						
		inicio = (reg*)malloc(sizeof(reg));
		inicio->prox = NULL;						
		//=============== CONTA QUANTOS NUMEROS VAI TER MEU VETOR ==========================
		pos = n_posicoes(&(*memoria),&total,f_entrada,pos);									
		//===================================================================		
		int *vet=(int*)malloc(sizeof(int)*total);		
		//==================================================================			
		fseek(f_entrada, pos, SEEK_SET);		
		for(cont=0;cont<total;cont++){
			valor = pegaValor(f_entrada);										
			if(valor != -1 )
				vet[cont] = valor;						
			else{				
				bkp = total;
				total = cont;				
				break;
			}
		}						
		mergesort(vet,0,total-1);		
		escreveSaida(nome_particao,vet,total);
		if(valor == -1)
			total = bkp;		
		free(vet);
		proximoNome(nome_particao);
	}
	fclose(f_entrada);							  	// fecha arquivo de entrada
	return n_particoes;								// retorna o numero de particoes criadas
}
//FUNCAO RECARREGA -> DURANTE O PROCESSO DE JUNÇÃO DOS ARQUIVOS É NECESSARIO VOLTAR PARA BUSCAR O RESTANTE DOS VALORES, ESSA FUNCAO FAZ ISSO
int recarrega(char nome_particao[],int i, float posicao[], int **vetores,int fim[]){ 
	FILE *f;
	int j=0;	
	printf("RECARREGANDO->%s--\n",nome_particao);	
	if(!(f = fopen(nome_particao,"r"))){
		printf("PROBLEMA NA RECARREGA_____POSICAO[%.0f]____nome particao: %s\n",posicao[i],nome_particao);				
		return 0;
	}
	fseek(f, posicao[i], SEEK_SET);
	if(feof(f)){
		printf("particao vazia\n");
		fclose(f);
		return 0;
	}
	fim[i]=0;
	while( (!feof(f)) && j<J){
		for(j=0;j<J;j++){
			if(!feof(f)){
				vetores[i][j] = pegaValor(f);
			}
			else{
				vetores[i][j] = -1;											
				break;						
			}		
		}
	}
	posicao[i] = ftell(f);
	fclose(f);
	return 1;
}
int menor(int k, int **vetores,int v[],int fim[]){		// FUNCAO PARA RETORNAR O MENOR VALOR ENTRE OS 'K' ARQUIVOS DA VEZ
	int i,x,menor;
	menor = 999999;
	for(i = 0; i < k; i++){
		if( (vetores[i][v[i]] != -1) && (v[i] < J)) {
			if(vetores[i][v[i]] <= menor){
				menor = vetores[i][v[i]];
				x=i;
			}
		}else
			fim[i]=1;		
	}	
	if(!next(fim,k))
		v[x]++;
	return menor;
}
void combina(int k,int **vetores,char nova_particao[],char nome_particao[], float posicao[],int nivel,int chave){	// junção dos 'K' arquivos da vez
	int i,j,v[k],fim[k],valor;	
	zerar(fim,k);
	zerar(v,k);
	char copia_nome[11];
	FILE *f = fopen(nova_particao,"a");	
	while(!next(fim,k)){				
		valor = menor(k,vetores,v,fim);
		for(i=0;i<k;i++){ //RECARREGAR VETOR VAZIO			
			if(v[i] == J){ //IF ALGUM DOS VETORES ESTIVER VAZIO				
				strcpy(copia_nome,nome_particao); // faz uma copia do inicio da sequencia ex. A-B.txt
				if(i>0)
					proximoNomeL(nome_particao,k,nivel,i);	
				if(recarrega(nome_particao,i,posicao,vetores,fim))
					v[i]=0;				
				strcpy(nome_particao,copia_nome);//restaura nome_particao
			}
		}
		if(valor != 999999)
			fprintf(f,"%i ",valor);						
	}	
	fclose(f);
}
int mergeMultiNivel(int n_particoes, int k, char nome_particao[], char nova_particao[],int nivel, int **vetores){ // CONTROLA A JUNÇÃO DAS PARTES 
	FILE *f,*f_escreve;			
	int n_partes=0,i,j=0,cont=0;
	float posicao[k];
	char BKP[11],AUX[11];

	if(nivel<1){	//preparando nomeclatura do primeiro arquivo para escrita
		for(i=0;i<k-1;i++)
			nova_particao[6]++;
	}	

	while(n_partes < n_particoes){		

		printf("ESCREVENDO %s\n",nova_particao);		
		strcpy(BKP,nome_particao);
		for(i=0;i<k;i++){
			posicao[i] = 0;
		}
		for(i = 0; i < k ; i++){			
			printf("lendo_particao: %s\n",nome_particao);
			if(!(f = fopen(nome_particao,"r"))){				
				k=i;
				continue;				
			}
			fseek(f, posicao[i], SEEK_SET);
			if(!feof(f) || (j != J) ){					
				for(j=0;j<J;j++){
					if(!feof(f))
						vetores[i][j] = pegaValor(f);										
					else{
						vetores[i][j] = -1;																									
						break;						
					}					
				}			
				posicao[i] = ftell(f);				
			}
			fclose(f);			
			if(nivel>0)				
				proximoNomeL(nome_particao,k,nivel,0);				
			else				
				proximoNome(nome_particao);						
		}
		j=0;
		strcpy(nome_particao,BKP);				
		combina(k,vetores,nova_particao,nome_particao,posicao,nivel,(n_particoes - n_partes));						
		n_partes = n_partes + k;
		cont++;
		if(n_partes >= n_particoes)	// se ja realizei a combinação com todas as partes nesse "nivel"
			break;
		if(k==0){	//restou apenas uma parte, k recebeu i e ficou em 0, precisa incrementar para sair
			n_partes++;
			continue;
		}
		proximoNomeL(nome_particao,k,nivel,-1);
		proximoNomeE(nova_particao,k,nivel+1,0);
		printf("NOME %s\n",nome_particao);
		printf("NOVA %s\n",nova_particao);		
	}		
	return cont;
}
void nivelUP(char nome_particao[],int k, int nivel, char TIPO){	//passar para o proximo "nivel"(apenas nomeclatura)
	int i,passos;
	strcpy(nome_particao,"001-001.txt");
	if( TIPO == 'E')		
		nivel++;
	passos = k;
	for(i=0;i < nivel-1 ;i++){
		passos = passos * k;
	}
	incrementa(nome_particao,passos-1,'D');
}
int main(int argc, char* argv[]){
	char entrada[20],saida[20];
	int  memoria,k,i;
	int n_particoes,nivel=0;
	clock_t t_i,t_f,tf,tf2;							// variaveis para calcular o tempo de execucao
	char c,nome_particao[13] = "parte001.txt",nova_particao[12] = "001-001.txt";

	strcpy(entrada,argv[1]); 						// arquivo de entrada - arquivo que contém os dados a serem ordenados;
	strcpy(saida,argv[2]);	 						// arquivo de saída - arquivos que contém os dados ordenados;
	memoria = atoi(argv[3]); 						// memória - a quantidade total de memória disponível para a ordenação.
	k = atoi(argv[4]);		 						// K - número de vias usadas pelo Merge-sort.	


	//============== REALIZA O PARTICIONAMENTO DO ARQUIVO DE ENTRADA ================
	t_i = clock();

	n_particoes = particionar(entrada,&memoria);		

	t_f = clock();
	tf=(t_f-t_i)/(CLOCKS_PER_SEC/1000);
	printf("TEMPO DE EXECUCAO particionar: %lu\n",tf);	
	//==============================================================================
	

	//memoria = memoria*1048576;

	J = memoria/k;
	J = J/4; // 9,99,999,9.999,99.999, a media é 3 bytes por numero

	int **vetores = (int**)malloc(sizeof(int)*k);	
	for(i=0;i<k;i++){
		vetores[i] = (int*)malloc(sizeof(int)*J);		
	}

	//nivel = 5;
	//n_particoes = 5;
	//nivelUP(nome_particao,k,nivel,'L');//LEITURA
	//nivelUP(nova_particao,k,nivel,'E');//ESCRITA
	//printf("NOME %s\n",nome_particao);
	//printf("NOVA %s\n",nova_particao);
	//getchar();
	//==================REALIZA TODAS COMBINAÇÕES=======================================================
	t_i = clock();
	do{
		printf("foi\n");
		n_particoes = mergeMultiNivel(n_particoes,k,nome_particao,nova_particao,nivel,vetores);
		printf("N PARTICOES: %i\n", n_particoes);

		nivel++;//passa para o próximo "nivel" para ajustar a nomeclatura
		nivelUP(nome_particao,k,nivel,'L');//ajusta nomeclatura para LEITURA 
		nivelUP(nova_particao,k,nivel,'E');//ajusta nomeclatura para ESCRITA		
		if(n_particoes <= k) // se restam k ou menos particoes o proximo arquivo tem o nome do parametro(2) saida
			strcpy(nova_particao,saida);		
	}while(n_particoes > 1);	
	t_f = clock();
	tf2=(t_f-t_i)/(CLOCKS_PER_SEC/1000);
	printf("TEMPO DE EXECUCAO quicksort-sort: %lu\n",tf2);
	//===================================================================================================	

	//=====================ESCREVER SAIDA ===============================================================
	FILE *f;
	char out[100],nomeOut[12];
	sprintf( nomeOut, "m_%i-k_%i.txt",memoria/1048576 , k);
	sprintf( out, "m = %i , k = %i , gerar particioes:%lu, merge multi vias: %lu", memoria/1048576 , k, tf, tf2);
	f = fopen(nomeOut,"w");
	fprintf(f, "%s",out );
	fclose(f);
	//====================================================================================================

	printf("PROCESSO FINALIZADO.\n");
	return 0;
}