#include "funcs.h"
#include <math.h>

long double f_a(long double x) {
  return pow(x, 2) + x - 1;
}

long double f_b(long double x) {
    return fabs(3*pow(x, 4));
}

long double f_c(long double x) {
  return sqrt(pow(x, 4) + 2);
}

long double f_d(long double x) {
  return (sin(3*x - ((6*M_PI + 11)/0.5))) / 2;
}

long double f_e(long double x) {
  return (cos(pow(M_E, -x))) * (0.005 * pow(x, 3) + 1);
}


