#include <stdio.h>
#include <math.h>
#include "utils.h"
#include "iseq.h"

double int_seq(double *v, int r, double (*f)(double)) {
  double a, b, soma = 0;
  int i;

  // soma das areas
  for(i = 0; i < r; i++) {
    a = v[i];
    b = v[i+1]; 
    soma = soma + area(a, b, f);
  }

  return soma;
}
