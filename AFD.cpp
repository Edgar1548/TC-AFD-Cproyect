//
// Created by EDGAR on 10/06/2021.
//
#include "AFD.h"
AFD::AFD(int n, int ind_inicial, int n_final, int *f_array) { // Guarda los atributos del AFD
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

void AFD::crear_conecction(int base, int conection, int final) { // Crea conexiones
    if (conection == 0) array[base]->zero = array[final]; //
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
    return false;
}*/
pair<vector<int>, string> AFD::hallar_0(pair<vector<int>, string> STR){
    priority_queue<int> pq; // Para guardarlo de forma ordenada (en este caso sera de mayor a menor)
    string cadena; // Donde se guarda el nombre del estado al que el estado actual va con 0
    vector<int> vec; // Para verificar que los estados no se repitan
    unordered_map<int, bool> map; // Donde se guardara el vector del estado al que el estado actual va con 0
    for (int i : STR.first){  // Recorremos el vector con el estado actual
        int it = array[i]->zero->position;
        if (map.find(it)==map.end()){ // Verificamos que no se repita
            map[it] = true; // Actualizamos
            //vec.push_back(it);
            //cadena+= to_string(it);
            pq.push(it); // Guardamos en el heap
        }
    }
    while (!pq.empty()){  // Pasamos del heap al vector (heapsort)
        vec.push_back(pq.top());
        cadena += to_string(pq.top()) + " "; //Se agrego " " para manejar el error
        pq.pop();
    }
    pair<vector<int>,string>pair_; // Guardamos en un pair
    pair_ = {vec, cadena};
    return pair_;
}

pair<vector<int>, string> AFD::hallar_1(pair<vector<int>, string> STR){
    priority_queue<int> pq; // Para guardarlo de forma ordenada (en este caso sera de mayor a menor)
    string name; // Donde se guarda el nombre del estado al que el estado actual va con 1
    unordered_map<int, bool> map; // Para verificar que los estados no se repitan
    vector<int> vec; // Donde se guardara el vector del estado al que el estado actual va con 1
    for (int i : STR.first){ // Recorremos el vector con el estado actual
        int it = array[i]->one->position; //
        if (map.find(it)==map.end()){ // Verificamos que no se repita
            map[it] = true; // Actualizamos
            //vec.push_back(it);
            //cadena+= to_string(it);
            pq.push(it); // Guardamos en el heap
        }
    }
    while (!pq.empty()){ // pasamos del heap al vector (heapsort)
        vec.push_back(pq.top());
        name += to_string(pq.top()) + " "; //Se agrego " " para manejar el error
        pq.pop();
    }
    pair<vector<int>,string>pair_; // Guardamos en un pair
    pair_ = {vec, name};
    return pair_;
}
void AFD::MIN() {
    string cadena; // Cadena que se mostrara si es que se haya
    string sup; // cadena que se guardara en el pair para pasarlo a la funcion MINSINC, representa al estado
    // con todos los estados unitario
    vector<int> vec; // vector que se guardara en el pair para pasarlo a la funcion MINSINC, , representa al estado
    // con todos los estados unitario
    vec.reserve(n_states); // Reservamos el tamaño del vec a n (todos los estados unitarios)
    pair<vector<int>,string> pair_; // Representa al estado con todos los estados unitario
    for(int i=n_states-1; i>=0; i--){ //Recorremos el array con estados unitarios
        int tmp = array[i]->position;
        vec.push_back(tmp);
        sup += to_string(tmp) + " "; // Se agrego " " para arreglar el error
    }
    pair_ = {vec, sup}; // Guardamos
    if (MINSINC(pair_, cadena)){ // Si MINSINC retorna verdad es sincronizable, caso contrario no
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
    } //Si el tamaño de la cadena es 1,
    pair<vector<int>, string> state_0; // Pair que guarda el estado al que se dirigue con 0
    pair<vector<int>, string> state_1; // Pair que guarda el estado al que se dirigue con 1
    queue<pair<vector<int>, string>> que; // Queue que guarda un vector y string, ambos representan un estado
    unordered_map<string, bool> map2; // Verifica si el estado ya ha sido recorrido
    unordered_map<string, pair<string, char>> map; // Guarda el padre del estado con la conexion
    que.push(STA); // Pusheamos un valor al queue
    map2[STA.second] = true; //Actualizamos STA como recorrido
    while (!que.empty()){
        STA = que.front(); // Actualiza el estado
        if (STA.first.size()==1) break; // Si el estado es de tamaño 1, es unitario, y se rompe el while
        state_0 = hallar_0(STA); // Funcion para hallar el camino por 0
        state_1 = hallar_1(STA); // Funcion para hallar el camino por 1
        map2[STA.second] = true;
        if(map2.find(state_0.second) == map2.end()) { //Verifica que el camino por 0 no haya sido recorrido
            map[state_0.second] = {STA.second,'0'}; //Guardamos el Padre de state_0  y el camino '0'
            map2[state_0.second] = true; //state_0 sera recorrido
            que.push(state_0); // Pusheamos al queue el state_0
        }
        if(map2.find(state_1.second)==map2.end()) {
            map[state_1.second] = {STA.second,'1'}; //Guardamos el Padre de state_1  y el camino '1'
            map2[state_1.second] = true; //state_1 sera recorrido
            que.push(state_1); // Pusheamos al queue el state_0
        }
        que.pop(); // Hacemos pop del front del queue
    }
    if (que.empty()) return false; // Si es vacio el queue, habra recorrido el automata potencia
    // y no encontro ningun camino a un automata unitario

    while (map.find(STA.second)!=map.end()){ //Recorremos desde el automata unitario hasta el automata con todos los estados unitario
        cadena += map[STA.second].second; // Le sumamos a cadena la coneccion (simbolo del alfabeto)
        STA.second = map[STA.second].first; //  Actualizamos el STA
    }
    auto it = cadena.end(); // Usamos iteradores para recorrer el string
    for(int i=0;i<cadena.size()/2;i++){
        char first = cadena[i];
        cadena[i] = *--it;
        *it = first;
    }// Recorremos el string a la inversa
    return true;
}