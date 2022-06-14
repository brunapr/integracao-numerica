#include <stdio.h>

void welcome() {
  printf("Funcoes disponiveis: \n");
  printf("1 -> x^2 + x -1\n");
  printf("2 -> |3x^4|\n");
  printf("3 -> sqrt(x^4 + 2)\n");
  printf("4 -> sin(3x - ((6pi + 11)/0.5))/2\n");
  printf("5 -> cos(e^{-1}(0.005x^3 + 1))\n");
  printf("\n");
  printf("Entrada: ./nome_arquivo <(1-5)> <a> <b> <n° trapezios> <n° threads>\n");
}