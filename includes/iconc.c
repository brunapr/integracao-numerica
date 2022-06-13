#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include "utils.h"
#include "iconc.h"

long long int t, global = 0; // n° trapezios e var compartilhada
long double *v, c_soma = 0; // vetor de intervalos e soma concorrente
long double (*f)(long double);
pthread_mutex_t lock; // variavel de lock para exclusao mutua

void * integra() {
  long double a, b, soma = 0;
  long long int i; 

  pthread_mutex_lock(&lock);
  i = global; global++;
  pthread_mutex_unlock(&lock);

  while(i < t) {
    a = v[i];
    b = v[i+1];
    soma = area(a, b, f);

    pthread_mutex_lock(&lock);
    c_soma = c_soma + soma;
    i = global; global++;
    pthread_mutex_unlock(&lock);
  }

  pthread_exit(NULL);
}

long double int_conc(int nthreads, long double *vet, long long int tra, long double (*func)(long double)) {
  int i, j;
  pthread_t *tid;

  v = vet;
  t = tra;
  f = func;

  pthread_mutex_init(&lock, NULL);

  // cria as threads
  tid = (pthread_t*) malloc(sizeof(pthread_t)*nthreads);
  if( tid == NULL ) { fprintf(stderr, "ERRO--malloc\n"); return 2;}

  for(i=0; i<nthreads; i++) {
    if (pthread_create(tid+i, NULL, integra, NULL)) {
      printf("--ERRO: pthread_create()\n"); return 2;
    };
  };

  //espera todas as threads terminarem
  for (j=0; j<nthreads; j++) {
    if (pthread_join(*(tid+j), NULL)) {
         printf("--ERRO: pthread_join()\n"); return 2; 
    } 
  } 

  pthread_mutex_destroy(&lock);

  free(tid);

  return c_soma;
}