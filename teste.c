#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "includes/funcs.h"
#include "includes/iconc.h"
#include "includes/iseq.h"
#include "includes/timer.h"
#include "includes/utils.h"

long double (*f)(long double);

void choice(int c) {
  switch (c) {
    case 1:
      f = f_a; break;
    case 2:
      f = f_b; break;
    case 3:
      f = f_c; break;
    case 4:
      f = f_d; break;
    case 5:
      f = f_e; break;
  }
}

void allocate_initialize(long double **v, long long int t, long double a, long double b) {
  (*v) = (long double *) malloc(sizeof(long double) * (t+1));
  if ((*v) == NULL) { printf("ERRO -- malloc\n"); exit(-1); }

  long double intervalo = (b - a) / t;
  long long int i;

  for(i = 0; i <= t; i++) {
    if(i == 0) { (*v)[i] = a; }
    else if(i == t) { (*v)[i] = b; }
    else { (*v)[i] = (*v)[i-1]+intervalo; };
  }
}

int main(int argc, char *argv[]) {
  long long int t;
  int nthreads, c;
  long double a, b, res_seq, res_conc, *v;
  double ini, fim, t_seq, t_conc;

  if (argc < 6) {
    fprintf(stderr, "Digite: %s <(1-5)> <a> <b> <n° trapezios> <n° threads> \n", argv[0]);
    return 1;
  }

  c = atoi(argv[1]);
  a = atof(argv[2]);
  b = atof(argv[3]);
  t = atoi(argv[4]);
  nthreads = atoi(argv[5]);

  // trata a funcao escolhida e define ela com as disponiveis
  choice(c);

  // aloca memoria para o array e o inicializa
  allocate_initialize(&v, t, a, b);

  // calculo sequencial com get_time
  GET_TIME(ini);
  res_seq = int_seq(v, t, f);
  GET_TIME(fim);
  t_seq = fim - ini;

  // calculo concorrente com get_time
  GET_TIME(ini);
  res_conc = int_conc(nthreads, v, t, f);
  GET_TIME(fim);
  t_conc = fim - ini;

  // print dos resultados
  corretude(res_seq, res_conc);
  tempo(t_seq, t_conc);
  
  free(v);
}