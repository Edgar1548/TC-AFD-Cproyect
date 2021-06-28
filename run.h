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

    do{
        cin >> n >> ind_inicial >> n_final;
    }while(n < ind_inicial || n < n_final || n<=0)
    
    f_states = new int[n_final];
    for (int i=0;i<n_final;i++){
        cin >> f_states[i];
    }
    AFD afd(n, ind_inicial, n_final, f_states);
    int qini;
    int caracter;
    int qfin;
    for (int i=0; i<2*n; i++){
        do{
            cin >> qini >> caracter >> qfin;
            }while(caracter!=1 and caracter!=0)
        
        afd.crear_conecction(qini, caracter, qfin);
    }
    afd.MIN();
}

#endif //AFD_PROYECT_RUN_H
