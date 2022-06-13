#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "includes/timer.h"
#include "includes/funcs.h"
#include "includes/iseq.h"
#include "includes/iconc.h"

#define OPTION_LENGTH 1

long double (*f)(long double);

void choice() {
  int choice = 0;

  printf("Funcoes (1-5): \n");
  printf("1: x^2 + x -1\n");
  printf("2: 3x^4\n");
  printf("3: sqrt(x^4 + 2)\n");
  printf("4: sin(3x - 2)\n");
  printf("5: cos(e^{-1}(0.005x^3 + 1))\n");
  printf("Sua escolha: ");

  scanf("%d", &choice);

  switch (choice) {
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

void allocateMemory(long double *v, long long int t) {
  v = (long double *) malloc(sizeof(long double) * (t+1));
  if (v == NULL) { printf("ERRO -- malloc\n"); return 2; }
}

void initialize(long double *v, long double a, long double b, long long int t) {
  long double intervalo = (b - a) / t;
  long long int i;

  for(i = 0; i <= t; i++) {
    if(i == 0) { v[i] = a; }
    else if(i == t) { v[i] = b; }
    else { v[i] = v[i-1]+intervalo; };
  }
}

int main(int argc, char *argv[]) {
  long long int t;
  int i, nthreads;
  long double a, b, res_seq, res_conc, *v;
  double ini, fim, t_seq, t_conc;

  // usuario escolhe func (a - e)
  choice();

  if (argc < 5) {
    fprintf(stderr, "Digite: %s <a> <b> <n° retangulos> <n° threads> \n", argv[0]);
    return 1;
  }

  a = atof(argv[1]);
  b = atof(argv[2]);
  t = atoi(argv[3]);
  nthreads = atoi(argv[4]);

  // aloca memoria para o array
  allocateMemory(&v, t);

  // inicializa o array
  initialize(&v, a, b, t);

  // calculo sequencial com get_time
  GET_TIME(ini);
  res_seq = int_seq(&v, t, f);
  GET_TIME(fim);
  t_seq = fim = ini;

  // calculo concorrente com get_time
  GET_TIME(ini);
  res_conc = int_conc(nthreads, &v, t, f);
  GET_TIME(fim);
  t_conc = fim - ini;

  // print dos resultados e comparacoes
  printf("Soma S: %.2Lf \n", res_seq);
  printf("Soma C: %.2Lf \n", res_conc);
  printf("Tempo S: %f \n", t_conc);
  printf("Tempo C: %f \n", t_conc);
  
  free(v);
}