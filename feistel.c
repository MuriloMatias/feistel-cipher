#include "feistel.h"

int main(){
    //Descobrir o tipo de I e colocar aqui
    int inicializado = 0, nrodadas, tamK, blocoClaro[32], chaveK[32], blocoCifrado[32], chaveauxiliar[32];
    char opcao;
    do{
        printf("Escolhas: \nI - Inicializar\nC - Cifrar\nD - Decifrar\nE - Encerrar o programa\n");
        scanf(" %c", &opcao);
        strupr(&opcao);

        //Comando de inicialização da rede.
        if(opcao == 'I'){
            inicializado = 1;

            //Leitura da quantidade de rodadas e o tamanho da chave.
            //Assim como a leitura do bytes da chave.
            scanf(" %d %d", &nrodadas, &tamK);
            chaveK[tamK];
            for(int i = 0; i < tamK; i++){
                scanf(" %d", &chaveK[i]);
            }
        }

        //Comando de cifragem, ele só ocorre caso a inicialização da rede tenha ocorrido.
        //A leitura do bloco  de texto claro ocorre logo após o C. O bloco deve conter 32 inteiros.
        //Pode ocorrer várias vezes com a mesma rede.
        //No final das rodas é necessário imprimir o bloco cifrado
        else if(opcao == 'C'){
            if(inicializado != 1){
                printf("Erro encontrado!\nInicializacao nao realizada");
                break;
            }
            for(int i = 0; i < 32; i++){
                scanf(" %d", &blocoClaro[i]);
            }
            cifragem(blocoClaro, tamK, chaveK, nrodadas);

        }
        //Comando de decifragem, só pode ocorrer com a rede já inicializada
        //A leitura do bloco cifrado ocorre logo após o D. O bloco deve conter 32 inteiros cifrados.
        else if(opcao == 'D'){
            if(inicializado != 1){
                printf("Erro encontrado!\nInicializacao nao realizada");
                break;
            }
            for(int i = 0; i < 32; i++){
                chaveauxiliar[i] = chaveK[i];
            }
            for(int i = 0; i < 32; i++) {
                scanf(" %d", &blocoCifrado[i]);
            }

            decifragem(blocoCifrado, tamK, chaveauxiliar, nrodadas);
        }
    }while(opcao != 'E');
}

//Cifra o bloco
void cifragem(int blocoClaro[], int tamK, int K0[tamK], int nrodadas) {
    int n = 16, aux;
    int esq[n], dir[n], blocoCript[n], Final[32];
    int permut[cmpr];
    for (int j = 0; j < n; j++) {
        esq[j] = blocoClaro[j];
        dir[j] = blocoClaro[j + n];
        blocoCript[j] = blocoClaro[j + n];
    }

    //for da rodada aqui
    for(int rodada = 0; rodada < nrodadas; rodada++) {
        //Gira um byte da chave

        if(rodada != 0 && rodada % 2 == 0){
            aux = K0[tamK-1];
            for(int i = tamK-1; i >= 0; i--){
                K0[i+1] = K0[i];
            }
            K0[0] = aux;
        }

        //Função F da rede de feistel
        FuncaoF(blocoCript, rodada, permut, tamK, K0);

        //Realiza o xor
        for (int i = 0; i < n; i++) {
            esq[i] = esq[i] ^ blocoCript[i];
        }

        //Troca o lados dos blocos
        trocaLados(esq, dir);


        for (int i = 0; i < n; i++) {
            blocoCript[i] = dir[i];
        }
    }

    trocaLados(esq, dir);
    for(int i = 0; i < n; i++){
        Final[i] = esq[i];
        Final[i+n] = dir[i];
    }
    printf("C ");
    for(int i = 0; i < 32; i++){
        printf(" %d ", Final[i]);
    }
    printf("\n");

}

//Decifra o bloco
//Eu refaço o vetor da função F na ordem inversa
void decifragem(int blocoCriptografado[], int tamK, int K0[], int nrodadas){
    int n = 16, aux;
    int esq[n], dir[n], blocoCript[n], Final[32];
    int permut[cmpr];

    for(int i = 0; i < n;i ++){
        esq[i] = blocoCriptografado[i];
        dir[i] = blocoCriptografado[i+16];
        blocoCript[i] = blocoCriptografado[i+16];
    }

    for(int rodada = nrodadas-1; rodada >= 0; rodada--){
        FuncaoF(blocoCript, rodada, permut, tamK,  K0);

        for(int i = 0; i < n; i++){
            esq[i] = esq[i] ^ blocoCript[i];
        }

        trocaLados(esq, dir);

        for (int i = 0; i < n; i++) {
            blocoCript[i] = dir[i];
        }
        if(rodada != 0 && rodada % 2 == 0) {
            aux = K0[0];
            for (int i = 0; i < tamK - 1; i++) {
                K0[i] = K0[i + 1];
            }
            K0[tamK - 1] = aux;
        }
    }

    trocaLados(esq, dir);
    for(int i = 0; i < n; i++){
        Final[i] = esq[i];
        Final[i+n] = dir[i];
    }
    printf("C ");
    for(int i = 0; i < 32; i++){
        printf(" %d ", Final[i]);
    }
    printf("\n");

}

//Produz as permutações utilizadas dentro da funcao F
void produzPermutacao (int tamK, int K[tamK], int rodada, int permut[cmpr]){
    int T[cmpr];
    int aux, cont = 0;
    if(rodada % 2 == 0){
        aux = 0;
    }else{
        aux = 1;
    }
    for(int i = 0; i < 2; i++){
        if(i == 1) cont = 128;
        for(int x = aux; x < 256;x += 2, cont++){
            permut[cont] = x;
        }
    }

    for(int x = 0; x < 256; x++){
        T[x] = K[x % tamK];
    }

    int j = 0;
    for(int x = 0; x < 256; x++){
        j = (j + permut[x] + T[x]) % 256;
        troca(&permut[x], &permut[j]);
    }
    /*
    printf("Chave: ");
    for(int i = 0; i< tamK; i++){
        printf("%d", K[i]);
    }
    printf("\n");

    printf("Aux = %d e rodada: %d. Permutacao:\n", aux, rodada);
    for(int cont = 0; cont < 256; cont++){
        printf(" %d", permut[cont]);
    }
    printf("\n");
*/
}

//Funcao F
void FuncaoF(int blocoCrip[], int i, int permut[], int tamK, int K[]){
    produzPermutacao(tamK, K, i, permut);
    int aux;
    for(int j = 0; j < 16; j++){
        aux = blocoCrip[j];
        blocoCrip[j] = permut[aux];
    }

}

//Funcao para a troca de valores dentro da permutacao
void troca(int *a, int *b){
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

//Troca os blocos de lugar
void trocaLados(int esquerda[], int direito[]){
    int n = 16;
    int aux[n];
    for(int i = 0; i < n; i++){
        aux[i] = esquerda[i];
        esquerda[i] = direito[i];
        direito[i] = aux[i];
    }
}