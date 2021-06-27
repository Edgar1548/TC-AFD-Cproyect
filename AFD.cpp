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
vector<int> AFD::hallar_0(vector<int> STR){
    priority_queue<int,vector<int>, std::greater<int>> pq;
    string cadena;
    unordered_map<int, bool> map;
    for (int i : STR){
        int it = array[i]->zero->position;
        if (map.find(it)==map.end()){
            map[it] = true;
            pq.push(it);
        }
    }
    vector<int> vec;
    while (!pq.empty()){
        vec.push_back(pq.top());
        pq.pop();
    }
    return vec;
}

vector<int> AFD::hallar_1(vector<int> STR){
    priority_queue<int,vector<int>, std::greater<int>> pq;
    unordered_map<int, bool> map;
    for (int i : STR){
        int it = array[i]->one->position;
        if (map.find(it)==map.end()){
            map[it] = true;
            pq.push(it);
        }
    }
    vector<int> vec;
    while (!pq.empty()){
        vec.push_back(pq.top());
        pq.pop();
    }
    return vec;
}
string convert_string(vector<int> vec){
    string cadena_aux;
    for (int i:vec) cadena_aux += to_string(i);
    return cadena_aux;
}
void AFD::MIN() {
    string cadena;
    vector<int> vec;
    vec.reserve(n_states);
    for(int i=0; i<n_states; i++)
        vec.push_back(array[i]->position);
    if (MINSINC(vec, cadena)){
        cout << "si es sincronizable"<<endl;
        cout << "tamanio_cadena: " << cadena.size()<<endl;
        cout << "cadena: " << cadena<<endl;
    }
    else cout << "NO";
}


bool AFD::MINSINC(vector<int> STA, string &cadena){
    if (STA.size()==1){
        cadena = to_string(0);
        return true;
    }
    string cadena_aux;
    vector<int> state_a;
    vector<int> state_b;
    queue<vector<int>> que;
    unordered_map<string, bool> map2;
    unordered_map<string, pair<string, int>> map;
    que.push(STA);
    while (!que.empty()){
        STA = que.front();
        cadena_aux = "";
        if (STA.size()==1) break;
        state_a = hallar_0(STA);
        state_b = hallar_1(STA);
        cadena_aux = convert_string(STA);
        map2[cadena_aux] = true;
        cadena_aux = convert_string(state_a);
        if(map2.find(cadena_aux) == map2.end()) {
            map[cadena_aux] = {convert_string(STA),0};
            map2[cadena_aux] = true;
            que.push(state_a);
        }
        cadena_aux = convert_string(state_b);
        if(map2.find(cadena_aux)==map2.end()) {
            map[cadena_aux] = {convert_string(STA),1};
            map2[cadena_aux] = true;
            que.push(state_b);
        }
        que.pop();
    }
    if (que.empty()) return false;
    cadena_aux = convert_string(STA);
    while (map.find(cadena_aux)!=map.end()){
        cadena += to_string(map[cadena_aux].second);
        cadena_aux = map[cadena_aux].first;
    }
    auto it = cadena.end();
    for(int i=0;i<cadena.size()/2;i++){
        char first = cadena[i];
        cadena[i] = *--it;
        *it = first;
    }
    return true;
}