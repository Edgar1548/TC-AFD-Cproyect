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
    pair<vector<int>, string> hallar_0(pair<vector<int>, string> STR);
    pair<vector<int>, string> hallar_1(pair<vector<int>, string> STR);
    void MIN();
    bool MINSINC(pair<vector<int>, string> STA, string &cadena);
};




#endif //AFD_PROYECT_AFD_H
