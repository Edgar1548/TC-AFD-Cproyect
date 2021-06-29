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
    int qini;
    int caracter;
    int qfin;
    int stat=1;
    int stat2=1;

    cin >> n >> ind_inicial >> n_final;

    if(n < ind_inicial || n < n_final || n<=0){
        stat*=0;
    }
    if(stat==1){
        f_states = new int[n_final];
        for (int i=0;i<n_final;i++){
            cin >> f_states[i];
        }
        AFD afd(n, ind_inicial, n_final, f_states);
        for (int i=0; i<2*n; i++){
            cin >> qini >> caracter >> qfin;
            if(caracter!=1 and caracter!=0){
                stat2*=0;

                cout<<endl<<"error en la linea: "<<i+1<<endl;
            }
            if(stat2==1){
                afd.crear_conecction(qini, caracter, qfin);
            }
            else{
                break;
            }
        }
        if(stat==1 and stat2==1){
            afd.MIN();
            return;
        }
    }
    else{
        cout<<endl<<"Error en la linea 0"<<endl;
    }

}

#endif //AFD_PROYECT_RUN_H
