#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include "utils.h"
#include "iconc.h"

long long int retangulos, global = 0; // numero de retangulos e var compartilhada
long double *vetor, g_soma = 0; // vetor de intervalos e soma concorrente
long double (*f)(long double); // funcao que sera integrada
int nthreads; // numero de threads
pthread_mutex_t lock; // variavel de lock para exclusao mutua

void * integra(void *arg) {
  int id = *(int*) arg; // identifica a thread
  long long int block = retangulos/nthreads; //tamanho do bloco
  long long int ini = id*block; //elemento inicial do bloco
  long long int fim; // elemento final (nao processado) do bloco
  long double a, b, soma = 0; // intervalos e soma local

  //trata se tiver resto
  if (id == nthreads-1) fim = retangulos;
  else fim = ini+block;

  // faz o calculo da integral e incrementa a soma
  for(long long int i = ini; i < fim; i++) {
    a = vetor[i];
    b = vetor[i+1];
    soma = soma + area(a, b, f);
  }

  // incrementa a soma da thread na soma global
  pthread_mutex_lock(&lock);
  g_soma = g_soma + soma;
  pthread_mutex_unlock(&lock);

  pthread_exit(NULL);
}

long double int_conc(int n, long double *v, long long int r, long double (*func)(long double)) {
  int i, j;
  pthread_t *tid;

  vetor = v;
  retangulos = r;
  f = func;
  nthreads = n;

  // inicializa mutex
  pthread_mutex_init(&lock, NULL);

  // aloca memoria para as threads 
  tid = (pthread_t*) malloc(sizeof(pthread_t)*nthreads);
  if( tid == NULL ) { fprintf(stderr, "ERRO--malloc\nthreads"); return 2;}

  int array[nthreads]; // array com os indices das threads
  
  // cria as threads
  for(i=0; i<nthreads; i++) {
    array[i] = i;
    if (pthread_create(tid+i, NULL, integra, (void*) &array[i])) {
      printf("--ERRO: pthread_create()\nthreads"); return 2;
    };
  };

  //espera todas as threads terminarem
  for (j=0; j<nthreads; j++) {
    if (pthread_join(*(tid+j), NULL)) {
         printf("--ERRO: pthread_join()\nthreads"); return 2; 
    } 
  } 

  pthread_mutex_destroy(&lock);

  // libera memoria
  free(tid);

  return g_soma;
}