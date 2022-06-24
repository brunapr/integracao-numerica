#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include "iseq.h"

long double int_seq(long double *vetor, long long int retangulos, long double (*f)(long double)) {
  long double a, b, soma = 0;
  int i;

  // soma das areas
  for(i = 0; i < retangulos; i++) {
    a = vetor[i];
    b = vetor[i+1]; 
    soma = soma + area(a, b, f);
  }

  return soma;
}
