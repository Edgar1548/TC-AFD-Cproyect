//
// Created by EDGAR on 10/06/2021.
//
#include "AFD.h"
AFD::AFD(int n, int ind_inicial, int n_final, int *f_array) {
    array = new state*[n];
    a_final = new int[n_final];
    for (int i=0; i<n; i++){
        array[i] = new state;
        array[i]->position = i;
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

/*bool AFD::crear_automaton() const {

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

}*/
/*
string AFD::hallar_0(vector<int> STR){
    priority_queue<int> pq;
    string cadena;
    unordered_map<int, bool> map;
    for (int i : STR){
        int it = array[i]->zero->position;
        if (map.find(it)==map.end())
            pq.push(it);
    }
    while (!pq.empty()){
        cadena += to_string(pq.top());
        pq.pop();
    }
    return cadena;
}
string AFD::hallar_1(vector<int> STR){
    priority_queue<int> pq;
    string cadena;
    unordered_map<int, bool> map;
    for (int i : STR){
        int it = array[i]->zero->position;
        if (map.find(it)==map.end())
            pq.push(it);
    }
    while (!pq.empty()){
        cadena += to_string(pq.top());
        pq.pop();
    }
    return cadena;
}
 */
pair<vector<int>, string> AFD::hallar_0(pair<vector<int>, string> STR){
    priority_queue<int> pq;
    string cadena;
    vector<int> vec;
    unordered_map<int, bool> map;
    for (int i : STR.first){
        int it = array[i]->zero->position;
        if (map.find(it)==map.end()){
            map[it] = true;
            //vec.push_back(it);
            //cadena+= to_string(it);
            pq.push(it);
        }
    }

    while (!pq.empty()){
        vec.push_back(pq.top());
        cadena += to_string(pq.top());
        pq.pop();
    }

    pair<vector<int>,string>pair_;
    pair_ = {vec, cadena};
    return pair_;
}

pair<vector<int>, string> AFD::hallar_1(pair<vector<int>, string> STR){
    priority_queue<int> pq;
    string cadena;
    unordered_map<int, bool> map;
    vector<int> vec;
    for (int i : STR.first){
        int it = array[i]->one->position;
        if (map.find(it)==map.end()){
            map[it] = true;
            //vec.push_back(it);
            //cadena+= to_string(it);
            pq.push(it);
        }
    }
    while (!pq.empty()){
        vec.push_back(pq.top());
        cadena += to_string(pq.top());
        pq.pop();
    }
    pair<vector<int>,string>pair_;
    pair_ = {vec, cadena};
    return pair_;
}
void AFD::MIN() {
    string cadena;
    string sup;
    vector<int> vec;
    pair<vector<int>,string> pair_;
    vec.reserve(n_states);
    for(int i=0; i<n_states; i++){
        int tmp = array[i]->position;
        vec.push_back(tmp);
        sup += to_string(tmp);
    }
    pair_ = {vec, sup};
    if (MINSINC(pair_, cadena)){
        cout << "si es sincronizable"<<endl;
        cout << "tamanio_cadena: " << cadena.size()<<endl;
        cout << "cadena: " << cadena<<endl;
    }
    else cout << "NO";
}


bool AFD::MINSINC(pair<vector<int>, string> STA, string &cadena){
    if (STA.first.size()==1){
        cadena = to_string(0);
        return true;
    }
    pair<vector<int>, string> state_0;
    pair<vector<int>, string> state_1;
    queue<pair<vector<int>, string>> que;
    unordered_map<string, bool> map2;
    unordered_map<string, pair<string, char>> map;
    que.push(STA);
    while (!que.empty()){
        STA = que.front();
        if (STA.first.size()==1) break;
        state_0 = hallar_0(STA);
        state_1 = hallar_1(STA);
        map2[STA.second] = true;
        if(map2.find(state_0.second) == map2.end()) {
            map[state_0.second] = {STA.second,'0'};
            map2[state_0.second] = true;
            que.push(state_0);
        }
        if(map2.find(state_1.second)==map2.end()) {
            map[state_1.second] = {STA.second,'1'};
            map2[state_1.second] = true;
            que.push(state_1);
        }
        que.pop();
    }
    if (que.empty()) return false;
    while (map.find(STA.second)!=map.end()){
        cadena += map[STA.second].second;
        STA.second = map[STA.second].first;
         }
    auto it = cadena.end();
    for(int i=0;i<cadena.size()/2;i++){
        char first = cadena[i];
        cadena[i] = *--it;
        *it = first;
    }

    return true;
}