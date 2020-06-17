/* Contador de primos com multi-threads
 * Data de  submissao: 17/06/20
 * Nome: Augusto Lourenço de Faria
 * RA: 194447
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define n_threads 4

pthread_mutex_t trava;
int resultado=0;

// função retorna 0 se não for primo e 1 se for primo
int primo (int numero){
	int i;
	if (numero == 1 || numero == 0)
		return 0;
	for (i=2; i < numero; i++){
		if (numero % i == 0)
			return 0;
	}
	return 1;
}

//cria a função thread para travar e as demais threads não aumentarem o resultado sem a anterior terminar
void *thread(void *args){

	int num = *((int *)args);
	int num_avaliado = primo(num);
	pthread_mutex_lock(&trava);
	resultado += num_avaliado;
	pthread_mutex_unlock(&trava);
	return NULL;
}

int main() {

	pthread_t t[n_threads] = {0, 0, 0, 0};
	int numero, filhos, vazia=0, i=0;
	int valores[n_threads];
	

	do{
		scanf("%d", &numero);

		//verifica se já tem 4 threads filhos, se sim espera um acabar para continuar
		if (filhos == 4){

			while (i < 4){		
				//espera acabar
				pthread_join(t[i], NULL);
				//seta novamente pra 0, ou seja está disponível
				t[i]=0;
				filhos--;
				i++;
			}	
		}
		
		for(i=0; i < 4; i++){
			//verifica qual dos threads está vazio, ou seja setado com 0
			if(t[i] == 0){
				vazia=i;
				i=4;
			}
		}

		//após a verificação de qual está vazio, cria o thread no endereço t[vazio]
		valores[vazia] = numero;
		pthread_create(&(t[vazia]), NULL, thread, ((void *) (&valores[vazia])));
		filhos++;
		
	}while(getchar() != '\n');
	
	//espera todos os threads acabarem	
	for(int i = 0; i < 4; i++)
		pthread_join(t[i], NULL);
		
	printf("%d\n", resultado);
  return 0;
}
