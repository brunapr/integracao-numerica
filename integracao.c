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
void escolha(int funcao) {
  switch (funcao) {
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
void trata_vetor(long double **vetor, long long int retangulos, long double a, long double b) {

  (*vetor) = (long double *) malloc(sizeof(long double) * (retangulos+1));
  if ((*vetor) == NULL) { printf("ERRO -- malloc\n"); exit(-1); }

  long double intervalo = (b - a) / retangulos;
  long long int i;

  // vetor inicializado com todos os intervalos 
  for(i = 0; i <= retangulos; i++) {
    if(i == 0) { (*vetor)[i] = a; }
    else if(i == retangulos) { (*vetor)[i] = b; }
    else { (*vetor)[i] = (*vetor)[i-1]+intervalo; };
  }
}

// funcao main
int main(int argc, char *argv[]) {
  long long int retangulos; // quantidade de retangulos
  int nthreads, funcao; // numero de threads e escolha da funcao
  long double a, b, res_seq, res_conc, *vetor; // intervalos, resultados e vetor
  double ini, fim, t_seq, t_conc; // controle de tempo

  // printa as funcoes disponiveis e espera pela escolha do usuario
  welcome();

  printf("Funcao escolhida: ");
  scanf("%d", &funcao);
  
  printf("Intervalo: [a, b]\n");
  printf("a: ");
  scanf("%Lf", &a);
  printf("b: ");
  scanf("%Lf", &b);

  printf("Numero de retangulos: ");
  scanf("%lld", &retangulos);

  printf("Numero de threads: ");
  scanf("%d", &nthreads);

  printf("\n");

  // trata e define a funcao escolhida
  escolha(funcao);

  // aloca memoria para o array e o inicializa
  trata_vetor(&vetor, retangulos, a, b);

  // calculo sequencial com get_time
  GET_TIME(ini);
  res_seq = int_seq(vetor, retangulos, f);
  GET_TIME(fim);
  t_seq = fim - ini;

  // calculo concorrente com get_time
  GET_TIME(ini);
  res_conc = int_conc(nthreads, vetor, retangulos, f);
  GET_TIME(fim);
  t_conc = fim - ini;

  // print dos resultados
  printf("Resultado sequencial: %.4Lf \n", res_seq);
  printf("Resultado concorrente: %.4Lf \n", res_conc);
  printf("Tempo sequencial: %.4f \n", t_seq);
  printf("Tempo concorrente: %.4f \n", t_conc);
  
  // libera memoria
  free(vetor);
}