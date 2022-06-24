#include <stdio.h>
#include "utils.h"

long double area(long double a, long double b, long double (*f)(long double)) {
  long double base = b - a;
  long double ponto_medio = (b + a) / 2;
  return base * f(ponto_medio);
}

void corretude(long double seq, long double conc) {
  long double dif = seq - conc; 
  printf("Resultado sequencial: %.4Lf \n", seq);
  printf("Resultado concorrente: %.4Lf \n", conc);
  printf("Diferença (seq-conc): %.4Lf \n", dif);
}

void tempo(double seq, double conc) {
  double ace = seq / conc;
  printf("Tempo sequencial: %.4f \n", seq);
  printf("Tempo concorrente: %.4f \n", conc);
  printf("Aceleração: %.4f \n", ace);
}

void welcome() {
  printf("Funcoes disponiveis: \n");
  printf("1 -> x^2 + x -1\n");
  printf("2 -> |3x^4|\n");
  printf("3 -> sqrt(x^4 + 2)\n");
  printf("4 -> sin(3x - ((6pi + 11)/0.5))/2\n");
  printf("5 -> cos(e^{-1}(0.005x^3 + 1))\n");
  printf("\n");
}
