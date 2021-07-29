//
// Created by EDGAR on 10/06/2021.
//

#ifndef AFD_PROYECT_AFD_H
#define AFD_PROYECT_AFD_H

#include "state.h"

class AFD{
private:
    int n_states; // Se guarda el numero de estados
    vector<int> states;
    vector<int> zero;
    vector<int> one;
    int state_inicial; // Posicion del estado inicial
    int* states_finals; // Array de posiciones con los estados finales
public:
    AFD(int n, int ind_inicial, int n_final, int* f_array);
    void crear_conecction(int base,int conection,int final); // Crea las conexiones del automata
    //bool crear_automaton() const;
    pair<vector<int>, string> hallar_0(pair<vector<int>, string> STR); // Retorna el camino al que el automata va con zero
    pair<vector<int>, string> hallar_1(pair<vector<int>, string> STR); // Retorna el camino al que el automata va con uno
    void run_MIN(); // Trabaja con el MINSINC y hace el cout
    void run_DEC();
    void run_CAD();
    bool MINSINC(pair<vector<int>, string> actual, string &cadena); // Halla si la cedena es sincronizable
    bool DECSINC();

    unordered_map<string, pair<string, int>> PRE_CAD();
    vector<int> find_new(string str_, vector<int> vec_);
    string CADSINC();
    bool singleton_or_visited(unordered_map<string, bool> visited);
};




#endif //AFD_PROYECT_AFD_H
