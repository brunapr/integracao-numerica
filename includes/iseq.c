#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include "iseq.h"

long double int_seq(long double *v, long long int r, long double (*f)(double)) {
  long double a, b, soma = 0;
  int i;

  // soma das areas
  for(i = 0; i < r; i++) {
    a = v[i];
    b = v[i+1]; 
    soma = soma + area(a, b, f);
  }

  return soma;
}
