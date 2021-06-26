//
// Created by EDGAR on 10/06/2021.
//

#ifndef AFD_PROYECT_STATE_H
#define AFD_PROYECT_STATE_H
#include "library.h"

struct state{
    int position;
    vector<state*> states;
    vector<state*> states_zero;
    vector<state*> states_one;
    state* zero;
    state* one;
};





#endif //AFD_PROYECT_STATE_H
