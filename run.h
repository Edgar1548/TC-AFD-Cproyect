//
// Created by EDGAR on 11/06/2021.
//

#ifndef AFD_PROYECT_RUN_H
#define AFD_PROYECT_RUN_H
#include "AFD.h"

void run_new_atuomata(){
    int m;
    cin >> m;
    AFD afd1;
    afd1.create_aleatorio(m);
}

void test_cadenas(AFD* afd){
    int cadenas;
    int cadenas2;
    string recorrido;
    while(cin>>cadenas>>cadenas2>>recorrido)
        afd->validar_cadenas(cadenas, cadenas2, recorrido);
}

void test_cadena(AFD* afd){
    int indice;
    string cadena;
    while(cin>>cadena){
        cin >> indice;
        afd->validar_cadena(cadena, indice);
    }
}

void run(){
    int n;
    int ind_inicial;
    int n_final;
    int* f_states;
    int qini;
    int caracter;
    int qfin;

    cin >> n >> ind_inicial >> n_final;

    f_states = new int[n_final];

    for (int i=0;i<n_final;i++) cin >> f_states[i];

    AFD* afd = new AFD(n, ind_inicial, n_final, f_states);

    for (int i=0; i<2*n; i++){
        cin >> qini >> caracter >> qfin;
        afd->crear_conecction(qini, caracter, qfin);
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    //afd->run_MIN();
    //afd->run_DEC(); // n^2
    afd->run_CAD();  // n^3
    auto t2 = std::chrono::high_resolution_clock::now();
    cout << "took "
            << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()
            << " milliseconds\n";
    //test_cadenas(afd);
    //test_cadena(afd);
}

#endif //AFD_PROYECT_RUN_H
