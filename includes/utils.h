#ifndef UTILS_H_
#define UTILS_H_

/*
  Função que calcula a área de um retângulo usando os intervalos
  dados e o ponto médio deles
*/

long double area(long double, long double, long double (*)(long double));

/*
  Função que testará a corretude dos resultados
*/

void corretude(long double, long double);

/*
  Função que retornará o tempo e aceleração dos resultados
*/

void tempo(double, double);

#endif
