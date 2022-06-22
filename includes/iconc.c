#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include "utils.h"
#include "iconc.h"

long long int t, global = 0; // n° trapezios e var compartilhada
long double *v, g_soma = 0; // vetor de intervalos e soma concorrente
long double (*f)(long double); // funcao que sera integrada
int n; // numero de threads
pthread_mutex_t lock; // variavel de lock para exclusao mutua

void * integra(void *arg) {
  int id = *(int*) arg; // identifica a thread
  long long int block = t/n; //tamanho do bloco
  long long int ini = id*block; //elemento inicial do bloco
  long long int fim; // elemento final (nao processado) do bloco
  long double a, b, soma = 0;
  long long int i;

  //trata o resto
  if (id == n-1) fim = t;
  else fim = ini+block;

  for(i = ini; i < fim; i++) {
    a = v[i];
    b = v[i+1];
    soma = soma + area(a, b, f);
  }

  pthread_mutex_lock(&lock);
  g_soma = g_soma + soma;
  pthread_mutex_unlock(&lock);

  pthread_exit(NULL);
}

long double int_conc(int nthreads, long double *vet, long long int tra, long double (*func)(long double)) {
  int i, j;
  pthread_t *tid;

  v = vet;
  t = tra;
  f = func;
  n = nthreads;

  pthread_mutex_init(&lock, NULL);

  // cria as threads
  tid = (pthread_t*) malloc(sizeof(pthread_t)*n);
  if( tid == NULL ) { fprintf(stderr, "ERRO--malloc\n"); return 2;}

  int array[n];
  
  for(i=0; i<n; i++) {
    array[i] = i;
    if (pthread_create(tid+i, NULL, integra, (void*) &array[i])) {
      printf("--ERRO: pthread_create()\n"); return 2;
    };
  };

  //espera todas as threads terminarem
  for (j=0; j<n; j++) {
    if (pthread_join(*(tid+j), NULL)) {
         printf("--ERRO: pthread_join()\n"); return 2; 
    } 
  } 

  pthread_mutex_destroy(&lock);

  free(tid);

  return g_soma;
}