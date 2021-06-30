//
// Created by EDGAR on 10/06/2021.
//

#ifndef AFD_PROYECT_STATE_H
#define AFD_PROYECT_STATE_H
#include "library.h"

struct state{
    int position; // Posicion del automata en el array
    state* zero; // Automata al que va con cero
    state* one;  // Automata al que va con uno
};





#endif //AFD_PROYECT_STATE_H
