//
// Created by EDGAR on 10/06/2021.
//
#include "AFD.h"


void funct(){
    int n;
    int ind_inicial;
    int n_final;
    int* f_state;
    cin >> n >> ind_inicial >> n_final;
    f_state = new int[n_final];
    for (int i=0;i<n_final;i++){
        cin >> f_state[i];
    }
    AFD afd(n, ind_inicial, n_final, f_state);
    int qini;
    int cont;
    int qfin;
    for (int i=0; i<2*n; i++){
        cin >> qini >> cont >> qfin;
        afd.crear_conecction(qini, cont, qfin);
    }
}

int main(){
    funct();
    return 0;
}