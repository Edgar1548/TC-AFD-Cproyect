//
// Created by EDGAR on 10/06/2021.
//

#ifndef AFD_PROYECT_AFD_H
#define AFD_PROYECT_AFD_H

#include "state.h"



class AFD{
private:
    state** array;
    int s_inicial;
    int* a_final;
public:
    AFD(int n, int ind_inicial, int n_final, int* f_array){
        // n = numero de estados
        // ind_inicial = indice del estado inicial
        // n_final = numero estados finales
        // f_state debe recibir varios valores, leer variadic template
        array = new state*[n];
        a_final = new int[n_final];
        for (int i=0; i<n; i++){
            array[i] = new state;
        }
        a_final = f_array;
        s_inicial = ind_inicial;
    }
    void crear_conecction(int base,int conection,int final){
        if (conection == 0) array[base]->zero = array[final];
        else if (conection==1) array[base]->one = array[final];
        else cout << "Alphabet is only 0 or 1";
    }

};


#endif //AFD_PROYECT_AFD_H
