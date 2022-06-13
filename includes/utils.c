#include <math.h>
#include "utils.h"

long double area(long double a, long double b, long double (*f)(long double)) {
  long double base = b - a;
  long double ponto_medio = (b + a) / 2;
  return base * f(ponto_medio);
}

