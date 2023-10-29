
#ifndef CRIPTOGRAFIA_FEISTEL_H
#define CRIPTOGRAFIA_FEISTEL_H
#include <stdio.h>
#include <string.h>

#define cmpr 256

//Cifra o bloco
void cifragem(int blocoClaro[32], int tamK, int K0[tamK], int nrodadas) ;

//Decifra o bloco
void decifragem(int blocoCriptografado[], int tamK, int K0[], int nrodadas);

//Funcoes auxiliares

//Produz as permutações utilizadas dentro da funcao F
void produzPermutacao (int tamK, int K[tamK], int i, int permut[cmpr]);

//Funcao para a troca de valores dentro da permutacao
void troca(int *a, int *b);

//Funcao F
void FuncaoF(int blocoCrip[16], int i, int permut[cmpr],  int tamK, int K[]);

//Troca os blocos de lugar
void trocaLados(int esquerda[], int direito[]);


#endif //CRIPTOGRAFIA_FEISTEL_H
