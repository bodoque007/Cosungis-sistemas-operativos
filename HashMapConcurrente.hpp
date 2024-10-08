#ifndef HMC_HPP
#define HMC_HPP

#include <shared_mutex>
#include <array>
#include <atomic>
#include <string>
#include <vector>
#include <mutex>

#include "ListaAtomica.hpp"

typedef std::pair<std::string, unsigned int> hashMapPair;

class HashMapConcurrente {
 public:
    static constexpr int cantLetras = 26;

    HashMapConcurrente();

    void incrementar(std::string clave);
    std::vector<std::string> claves();
    unsigned int valor(std::string clave);

    float promedio();


 private:
    ListaAtomica<hashMapPair> *tabla[HashMapConcurrente::cantLetras];

    static unsigned int hashIndex(std::string clave);
    std::shared_mutex locks[cantLetras];
};

#endif  /* HMC_HPP */
