#ifndef ICONC_H_
#define ICONC_H_

/*
 Função concorrente
 Recebe o numero de threads, o vetor com os intervalos, o número de retângulos
 e a função que deve ser usada
*/

long double int_conc(int nthreads, long double*, long long int, long double (*)(double));

#endif
