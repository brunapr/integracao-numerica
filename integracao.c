#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "includes/timer.h"
#include "includes/funcs.h"
#include "includes/iseq.h"
#include "includes/iconc.h"
#include "includes/utils.h"

long double (*f)(long double); // funcao global

// definicao de f dependendo dos argumentos dados
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

// aloca memoria para o vetor e inicializa ele
void trata_vetor(long double **v, long long int t, long double a, long double b) {
  (*v) = (long double *) malloc(sizeof(long double) * (t+1));
  if ((*v) == NULL) { printf("ERRO -- malloc\n"); exit(-1); }

  long double intervalo = (b - a) / t;
  long long int i;

  // vetor inicializado com todos os intervalos 
  for(i = 0; i <= t; i++) {
    if(i == 0) { (*v)[i] = a; }
    else if(i == t) { (*v)[i] = b; }
    else { (*v)[i] = (*v)[i-1]+intervalo; };
  }
}

// funcao main
int main(int argc, char *argv[]) {
  long long int t; // quantidade de trapezios
  int nthreads, c; // numero de threads e escolha da funcao
  long double a, b, res_seq, res_conc, *v; // intervalos, resultados e vetor
  double ini, fim, t_seq, t_conc; // controle de tempo

  // printa as funcoes disponiveis e espera pela escolha do usuario
  welcome();

  printf("Funcao escolhida: ");
  scanf("%d", &c);
  
  printf("Intervalo: [a, b]\n");
  printf("a: ");
  scanf("%Lf", &a);
  printf("b: ");
  scanf("%Lf", &b);

  printf("Numero de trapezios: ");
  scanf("%lld", &t);

  printf("Numero de threads: ");
  scanf("%d", &nthreads);

  printf("\n");

  // trata e define a funcao escolhida
  choice(c);

  // aloca memoria para o array e o inicializa
  trata_vetor(&v, t, a, b);

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
  printf("Resultado sequencial: %.4Lf \n", res_seq);
  printf("Resultado concorrente: %.4Lf \n", res_conc);
  printf("Tempo sequencial: %.4f \n", t_seq);
  printf("Tempo concorrente: %.4f \n", t_conc);
  
  // libera memoria
  free(v);
}