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
    bool found = false;
    unsigned int index = hashIndex(clave);
    // Lockeamos el bucket correspondiente, unique_lock porque es el lock de los writers. (Solo puede haber un writer a la vez)
    std::unique_lock<std::shared_mutex> lock(locks[index]);

    for (auto& p : *tabla[index]) {
        if (p.first == clave) {
            p.second++;
            found = true;
            break;
        }
    }
    // Si llegamos al final, es porque la clave no estaba. Insertamos la clave con su valor de 1 aparicion
    if (!found) {
        hashMapPair nuevoPar = std::make_pair(clave, 1);
        tabla[index]->insertar(nuevoPar);
    }
}

std::vector<std::string> HashMapConcurrente::claves() {
    // Completar (Ejercicio 2)
    std::vector<std::string> claves;
    for (unsigned int index = 0; index < HashMapConcurrente::cantLetras; index++) {
        // Lockeamos el shared lock del bucket porque es el lock de los readers. (Muchos pueden leer al mismo tiempo)
        std::shared_lock<std::shared_mutex> lock(locks[index]);
        for (const auto& p : *tabla[index]) {
            claves.push_back(p.first);
        }
    }
    return claves;
}

unsigned int HashMapConcurrente::valor(std::string clave) {
    // Completar (Ejercicio 2)
    unsigned int index = hashIndex(clave);
    // Lockeamos el shared lock del bucket porque es el lock de los readers. (Muchos pueden leer al mismo tiempo)
    std::shared_lock<std::shared_mutex> lock(locks[index]);

    for (const auto& p : *tabla[index]) {
        if (p.first == clave) {
            return p.second;
        }
    }
    return 0;
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
