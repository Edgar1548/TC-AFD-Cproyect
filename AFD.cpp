//
// Created by EDGAR on 10/06/2021.
//
#include "AFD.h"
AFD::AFD(int n, int ind_inicial, int n_final, int *f_array) {

    a_final = new int[n_final];
    for (int i=0; i<n; i++){
        array[i] = new state;
        array[i]->name = to_string(i);
    }
    a_final = f_array;
    s_inicial = ind_inicial;
    n_states = n;
}

void AFD::crear_conecction(int base, int conection, int final) {
    if (conection == 0) array[base]->zero = array[final];
    else if (conection==1) array[base]->one = array[final];
    else cout << "Alphabet is only 0 or 1";
}