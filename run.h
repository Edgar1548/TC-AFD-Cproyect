//
// Created by EDGAR on 11/06/2021.
//

#ifndef AFD_PROYECT_RUN_H
#define AFD_PROYECT_RUN_H
#include "AFD.h"


void run(){
    int n;
    int ind_inicial;
    int n_final;
    int* f_states;
    cin >> n >> ind_inicial >> n_final;
    f_states = new int[n_final];
    for (int i=0;i<n_final;i++){
        cin >> f_states[i];
    }
    AFD afd(n, ind_inicial, n_final, f_states);
    int qini;
    int cont;
    int qfin;
    for (int i=0; i<2*n; i++){
        cin >> qini >> cont >> qfin;
        afd.crear_conecction(qini, cont, qfin);
    }
}

#endif //AFD_PROYECT_RUN_H
