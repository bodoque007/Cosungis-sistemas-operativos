#ifndef CHM_CPP
#define CHM_CPP

#include <thread>
#include <iostream>
#include <fstream>

#include "HashMapConcurrente.hpp"

HashMapConcurrente::HashMapConcurrente() {
    for (unsigned int i = 0; i < HashMapConcurrente::cantLetras; i++) {
        tabla[i] = new ListaAtomica<hashMapPair>();
    }
}

unsigned int HashMapConcurrente::hashIndex(std::string clave) {
    return (unsigned int)(clave[0] - 'a');
}

void HashMapConcurrente::incrementar(std::string clave) {
    // Completar (Ejercicio 2)
    unsigned int hashIndex = HashMapConcurrente::hashIndex(clave);
    std::unique_lock<std::mutex> lock(locks[index]);
    auto it = tabla[index]->begin();
    // Iteramos hasta encontrar la clave o llegar al final
    while (it != tabla[index]->end() && it->first != clave) {
        it++;
    }
    // Si llegamos al final, es porque la clave no estaba. Insertamos la clave con su valor de 1 aparicion
    if (it == tabla[index]->end()) {
        tabla[index]->push_back({clave, 1});
    } else {
        // Si la clave ya estaba, incrementamos su valor y ya esta
        it->second++;
    }
    // No es necesario soltar el lock, pues el destructor de unique_lock lo hace por nosotros al salir del scope
}

std::vector<std::string> HashMapConcurrente::claves() {
    // Completar (Ejercicio 2)
}

unsigned int HashMapConcurrente::valor(std::string clave) {
    // Completar (Ejercicio 2)
}

float HashMapConcurrente::promedio() {

    float sum = 0.0;
    unsigned int count = 0;
    for (unsigned int index = 0; index < HashMapConcurrente::cantLetras; index++) {
        for (const auto& p : *tabla[index]) {
            sum += p.second;
            count++;
        }
    }
    if (count > 0) {
        return sum / count;
    }
    return 0;        
}
#endif