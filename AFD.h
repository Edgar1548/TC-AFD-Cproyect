//
// Created by EDGAR on 10/06/2021.
//

#ifndef AFD_PROYECT_AFD_H
#define AFD_PROYECT_AFD_H

#include "state.h"

class AFD{
private:
    int n_states;
    state** array;
    int s_inicial;
    int* a_final;
public:
    AFD(int n, int ind_inicial, int n_final, int* f_array);
    void crear_conecction(int base,int conection,int final);
    bool crear_automaton() const;
    vector<int> hallar_0(vector<int> STR);
    vector<int> hallar_1(vector<int> STR);
    void MIN();
    bool MINSINC(vector<int> STA, string &cadena);
};




#endif //AFD_PROYECT_AFD_H
