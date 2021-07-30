//
// Created by EDGAR on 30/07/2021.
//

#ifndef AFD_PROYECT_RUN_MAGICAL_H
#define AFD_PROYECT_RUN_MAGICAL_H
#include "AFD.h"

void run_magic(){
    int T_;
    int N;
    int final;
    cin >> T_;
    vector<AFD*> afds;
    afds.reserve(T_);
    for (int t=0; t<T_; t++){
        cin >> N;
        AFD* afd = new AFD(N);
        for (int i=0; i<2; i++){
            for (int j = 0; j<N; j++){
                cin >> final;
                afd->crear_conecction(j, i, final-1);
            }
        }
        afds.push_back(afd);
    }
    for (int i=0; i<T_; i++){
        afds[i]->run_magical();
        if (i != T_-1) cout << endl;
    }
}
#endif //AFD_PROYECT_RUN_MAGICAL_H
