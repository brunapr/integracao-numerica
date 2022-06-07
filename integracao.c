#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "includes/timer.h"
#include "includes/funcs.h"
#include "includes/iseq.h"
#include "includes/iconc.h"

int main(int argc, char *argv[]) {
  int r, i, nthreads;
  double a, b, res_seq, res_conc, *v, intervalo;
  double ini, fim, t_seq, t_conc;
  double (*f)(double);

  // usuario escolhe func (a - e)
  // seta f como a func que usuario escolheu

  if (argc < 5) {
    fprintf(stderr, "Digite: %s <a> <b> <n° retangulos> <n° threads> \n", argv[0]);
    return 1;
  }

  a = atof(argv[1]);
  b = atof(argv[2]);
  r = atoi(argv[3]);
  nthreads = atoi(argv[4]);

  // aloca memoria para vetor de intervalos
  v = (double *) malloc(sizeof(double) * r);
  if (v == NULL) { printf("ERRO -- malloc\n"); return 2; }

  //inicializa vetor de intervalos
  intervalo = (b - a) / r;

  for(i = 0; i <= r; i++) {
    if(i == 0) { v[i] = a; }
    else if(i == r) { v[i] = b; }
    else { v[i] = v[i-1]+intervalo; };
  }

  // calculo sequencial com get_time

  // calculo concorrente com get_time

  // print dos resultados e comparacoes
}