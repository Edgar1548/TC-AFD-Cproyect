//
// Created by EDGAR on 10/06/2021.
//
#include "AFD.h"
AFD::AFD(int n, int ind_inicial, int n_final, int *f_array) {
    array = new state*[n];
    a_final = new int[n_final];
    for (int i=0; i<n; i++){
        array[i] = new state;
        array[i]->name = to_string(i+1);
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

bool AFD::crear_automaton() const {
    state** automaton;

    int power_size = int(pow(2, n_states));
    automaton = new state*[power_size];
    int aux = 0;
    for(int i=0; i<power_size;i++){
        automaton[i] = new state;
        for (int j=0; j<n_states ;j++){
            unordered_map<state*,  bool> map_zero;
            unordered_map<state*,  bool> map_one;
            if (i & (1 << j)){
                if (to_string(i)==array[aux]->name)
                    automaton[i] = array[aux++];
                else automaton[i]->name+= to_string(j);
                automaton[i]->states.push_back(array[j]);
                if (map_zero.find(array[j]->zero) == map_zero.end()){
                    map_zero[array[j]]=true;
                    automaton[i]->states_zero.push_back(array[j]->zero);
                }
                if (map_one.find(array[j]->one) == map_one.end()){
                    map_one[array[j]]=true;
                    automaton[i]->states_one.push_back(array[j]->one);
                }

            }
        }
    }
    for (int i=0; i<power_size; i++){
        cout << automaton[i]->name << endl;
    }



    return false;
}