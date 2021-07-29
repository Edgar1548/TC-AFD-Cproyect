//
// Created by EDGAR on 10/06/2021.
//
#include "AFD.h"
    AFD::AFD(int number_states, int ind_inicial, int number_final, int *f_states) { // Guarda los atributos del AFD
        states_finals = new int[number_final];
        states.reserve(number_states);
        for (int i=0; i<number_states; i++){
            states.push_back(i);
        }
        zero.reserve(number_states);
        one.reserve(number_states);
        states_finals = f_states;
        state_inicial = ind_inicial;
        n_states = number_states;
    }

    void AFD::crear_conecction(int base, int conection, int final) { // Crea conexiones
        if (conection == 0) zero[base] = states[final]; //
        else if (conection==1) one[base] = states[final];
        else cout << "Alphabet is only 0 or 1";
    }
    pair<vector<int>, string> AFD::hallar_0(pair<vector<int>, string> STR){
        priority_queue<int> pq; // Para guardarlo de forma ordenada (en este caso sera de mayor a menor)
        string cadena; // Donde se guarda el nombre del estado al que el estado actual va con 0
        vector<int> vec; // Para verificar que los estados no se repitan
        unordered_map<int, bool> map; // Donde se guardara el vector del estado al que el estado actual va con 0

        set<int> myset;
        for (int i : STR.first){  // Recorremos el vector con el estado actual
            int it = zero[i];
            myset.insert(it);
        }
        vec.reserve(myset.size());
        for (int it : myset){
            vec.push_back(it);
            cadena += to_string(it) + " "; //Se agrego " " para manejar el error
        }
        pair<vector<int>,string>pair_; // Guardamos en un pair
        pair_ = {vec, cadena};
        return pair_;
    }

    pair<vector<int>, string> AFD::hallar_1(pair<vector<int>, string> STR){
        priority_queue<int> pq; // Para guardarlo de forma ordenada (en este caso sera de mayor a menor)
        string cadena; // Donde se guarda el nombre del estado al que el estado actual va con 1
        unordered_map<int, bool> map; // Para verificar que los estados no se repitan
        vector<int> vec; // Donde se guardara el vector del estado al que el estado actual va con 1
        set<int> myset;
        for (int i : STR.first){  // Recorremos el vector con el estado actual
            int it = one[i];
            myset.insert(it);
        }
        vec.reserve(myset.size());
        for (int it : myset){
            vec.push_back(it);
            cadena += to_string(it) + " "; //Se agrego " " para manejar el error
        }
        pair<vector<int>,string>pair_; // Guardamos en un pair
        pair_ = {vec, cadena};
        return pair_;
    }
    void AFD::run_MIN() {
        string cadena; // Cadena que se mostrara si es que se haya
        string sup; // cadena que se guardara en el pair para pasarlo a la funcion MINSINC, representa al estado
        // con todos los estados unitario
        // con todos los estados unitario
        pair<vector<int>,string> pair_; // Representa al estado con todos los estados unitario
        for(int i=0; i<n_states; i++){ //Recorremos el array con estados unitarios
            sup += to_string(states[i]) + " "; // Se agrego " " para arreglar el error
        }
        pair_ = {states, sup}; // Guardamos
        if (MINSINC(pair_, cadena)){ // Si MINSINC retorna verdad es sincronizable, caso contrario no
            cout << "si es sincronizable"<<endl;
            cout << "tamanio_cadena: " << cadena.size()<<endl;
            cout << "cadena: " << cadena<<endl;
        }
        else cout << "NO" << endl;
    }

    bool AFD::MINSINC(pair<vector<int>, string> actual, string &cadena){

        if (actual.first.size() == 1){
            cadena = to_string(0);
            return true;
        } //Si el tamaño de la cadena es 1,
        pair<vector<int>, string> state_0; // Pair state_que guarda el estado al state_que se dirigue con 0
        pair<vector<int>, string> state_1; // Pair state_que guarda el estado al state_que se dirigue con 1
        queue<pair<vector<int>, string>> state_que; // Queue state_que guarda un vector y string, ambos representan un estado
        unordered_map<string, bool> visiteds_map; // Verifica si el estado ya ha sido recorrido
        unordered_map<string, string> fathers_map; // Guarda el padre del estado con la conexion
        state_que.push(actual); // Pusheamos un valor al queue
        visiteds_map[actual.second] = true; //Actualizamos top como recorrido
        fathers_map[actual.second] = "";
        string father_;
        do{
            actual = state_que.front();
            state_0 = hallar_0(actual); // Funcion para hallar el camino por 0
            father_ = fathers_map[actual.second];
            if (state_0.first.size() == 1){
                fathers_map[state_0.second] = father_+"0";
                actual.second = state_0.second;
                break;
            }
            if(visiteds_map.find(state_0.second) == visiteds_map.end()) { //Verifica state_que el camino por 0 no haya sido recorrido
                fathers_map[state_0.second] = father_+"0";//Guardamos el Padre de state_0  y el camino '0'
                visiteds_map[state_0.second] = true; //state_0 sera recorrido
                state_que.push(state_0); // Pusheamos al queue el state_0
            }
            state_1 = hallar_1(actual); // Funcion para hallar el camino por 1
            if (state_1.first.size() == 1){
                fathers_map[state_1.second] = father_+"1";
                actual.second = state_1.second;
                break;
            }
            if(visiteds_map.find(state_1.second) == visiteds_map.end()) {
                fathers_map[state_1.second] = father_+"1"; //Guardamos el Padre de state_1  y el camino '1'
                visiteds_map[state_1.second] = true; //state_1 sera recorrido
                state_que.push(state_1); // Pusheamos al queue el state_0
            }
            state_que.pop(); // Hacemos pop del front del queue

        }while (!state_que.empty());

        if (state_que.empty()) return false; // Si es vacio el queue, habra recorrido el automata potencia

        cadena = fathers_map[actual.second];
        return true;
    }
    bool AFD::DECSINC() {
        if (n_states == 1 || n_states == 0) return true;
        int limit = (n_states*(n_states-1))/2;
        unordered_map<string, bool> trues_;
        pair<vector<int>, string> pair_;
        pair<vector<int>, string> zero_;
        pair<vector<int>, string> one_;
        stack<pair<vector<int>, string>> stack_states;
        int count = 0;
        for (int i=0; i<n_states; i++){
            for (int j=i+1; j<n_states; j++){
                unordered_map<string, bool> visited;
                if (j>i) pair_.second = to_string(i) + " " +to_string(j) + " ";
                else pair_.second = to_string(j) + " " +to_string(i) + " ";
                if (trues_[pair_.second]) continue;
                pair_.first = {i, j};
                stack_states.push(pair_);
                while(!stack_states.empty()){
                    pair_ = stack_states.top();
                    zero_ = hallar_0(pair_);
                    visited[pair_.second] = true;
                    if (trues_[zero_.second] || zero_.first.size() == 1 ){
                        while (!stack_states.empty()){
                            count ++;
                            trues_[stack_states.top().second] = true;
                            stack_states.pop();
                        }
                        if (count == limit) return true;
                        break;
                    }
                    one_ = hallar_1(pair_);
                    if (one_.first.size() == 1 || trues_[one_.second]){
                        while (!stack_states.empty()){
                            count ++;
                            trues_[stack_states.top().second] = true;
                            stack_states.pop();
                        }
                        if (count == limit) return true;
                        break;
                    }
                    else if (!visited[zero_.second]) stack_states.push(zero_);
                    else if (!visited[one_.second]) stack_states.push(one_);
                    else stack_states.pop();
                    if (stack_states.empty()) return false;
                }
                if (count == limit) return true;
            }
        }
        return true;
    }

    void AFD::run_DEC() {
        if (DECSINC()) cout << "SI" << endl;
        else cout << "NO" << endl;
    }

    unordered_map<string, pair<string, int>> AFD::PRE_CAD() {
        unordered_map<string, bool> trues_;
        pair<vector<int>, string> pair_;
        pair<vector<int>, string> zero_;
        pair<vector<int>, string> one_;
        unordered_map<string, pair<string, int>> strings_;
        string chain;
        stack<pair<pair<vector<int>, string>, string>> stack_states;
        int count = 0;
        for (int i=0; i<n_states; i++){
            for (int j=i+1; j<n_states; j++){
                unordered_map<string, bool> visited;
                if (j>i) pair_.second = to_string(i) + " " +to_string(j) + " ";
                else pair_.second = to_string(j) + " " +to_string(i) + " ";
                chain = "";
                if (trues_[pair_.second]) continue;
                pair_.first = {i, j};
                stack_states.push({pair_, chain});
                while(!stack_states.empty()){
                    zero_ = hallar_0(pair_);
                    visited[pair_.second] = true;
                    if (trues_[zero_.second]){
                        chain = "0" + strings_[zero_.second].first;
                        while (!stack_states.empty()){
                            count++;
                            strings_[stack_states.top().first.second] = {chain, strings_[zero_.second].second};
                            chain = stack_states.top().second + chain;
                            trues_[stack_states.top().first.second] = true;
                            stack_states.pop();
                        }
                        break;
                    }
                    else if (zero_.first.size() == 1){
                        chain = "0";
                        while (!stack_states.empty()){
                            count ++;
                            strings_[stack_states.top().first.second] = {chain, stoi(zero_.second)};
                            chain += stack_states.top().second;
                            trues_[stack_states.top().first.second] = true;
                            stack_states.pop();
                        }
                        break;
                    }
                    one_ = hallar_1(pair_);
                    if (trues_[one_.second]){
                        chain = "1"  + strings_[one_.second].first;
                        while (!stack_states.empty()){
                            count ++;
                            strings_[stack_states.top().first.second] = {chain, strings_[one_.second].second};
                            chain = stack_states.top().second + chain;
                            trues_[stack_states.top().first.second] = true;
                            stack_states.pop();
                        }
                        break;
                    }
                    if (one_.first.size() == 1){
                        chain = "1" ;
                        while (!stack_states.empty()){
                            count ++;
                            strings_[stack_states.top().first.second] = {chain, stoi(one_.second)};
                            chain += stack_states.top().second;
                            trues_[stack_states.top().first.second] = true;
                            stack_states.pop();
                        }
                        break;
                    }
                    else if (!visited[zero_.second]) {
                        stack_states.push({zero_, "0"});
                    }
                    else if (!visited[one_.second]) {
                        stack_states.push({one_, "1"});
                    }
                    else stack_states.pop();
                    pair_ = stack_states.top().first;
                }
                if (count == (n_states*(n_states-1))/2) break;
            }
            if (count == (n_states*(n_states-1))/2) break;
        }
        return strings_;
    }

    vector<int> AFD::find_new(string str_, vector<int> vec_){
        int element ;
        set<int> myset;
        vector<int> vector_;
        for (int i=2; i<vec_.size(); i++){
            element = vec_[i];
            for (char & it : str_){
                if (it - '0' == 0) element = zero[element];
                else element = one[element];
            }
            myset.insert(element);
        }
        vector_.reserve(myset.size());
        for (int it : myset) vector_.push_back(it);
        return vector_;
    }

    string AFD::CADSINC() {
        if (n_states == 1) return "0";
        if (n_states == 0) return "";
        unordered_map<string, pair<string, int>> T_ = PRE_CAD();
        vector<int> X = states;
        vector<int> tmp;
        string T;
        while(X.size() > 1){
            if (X.size() == 2) {
                if (X[0] > X[1]) swap(X[0], X[1]);
                string try_ = to_string(X[0]) + " " + to_string(X[1]) + " ";
                T += T_[try_].first;
                break;
            }
            else {
                string try_ = to_string(X[0]) + " " + to_string(X[1]) + " ";
                tmp = find_new(T_[try_].first, X);
                tmp.push_back(T_[try_].second);
                X = tmp;
                T += T_[try_].first;
            }
        }
        return T;
    }
    void AFD::run_CAD() {
        cout << CADSINC() << endl;
    }



