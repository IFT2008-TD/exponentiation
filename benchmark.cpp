#include "exposant.h"
#include "expbench.h"
#include <cassert>
#include <cmath>


class Foncteur1 {
public:
    std::string getName() const {return  "Version itérative" ; }
    double operator () (double m, size_t e) {
        return exposant_v1(m, e) ; 
    }
} ;

class Foncteur2 {
    public:
    std::string getName() const {return "Version récursive naïve" ; }
    double operator () (double m, size_t e) {
        return exposant_v2(m, e) ; 
    }
} ; 

class Foncteur3 {
    public:
    std::string getName() const {return "Version récursive avancée" ; }
    double operator () (double m, size_t e) {
        return exposant_v3(m, e) ; 
    }
} ; 

template <typename F>
void experience(ExpBench<F> bench, size_t nRun, size_t nSample) {
    std::vector<size_t> resultats(nRun) ; 
    for (size_t i = 0; i < nRun; ++i) {
        resultats[i] += bench.benchmark(nSample) ; 
    }
    size_t sum = 0.0 ; 
    for (size_t i = 0; i < nRun; ++i) sum += resultats[i] ; 
    double moyenne = static_cast<double> (sum) / static_cast<double> (100) ; 

    double accDiff = 0.0 ; 
    for (size_t i = 0; i < nRun; ++i) {
        double diff = resultats[i] - moyenne ; 
        accDiff += diff * diff ; 
    }
    double stdDev = std::sqrt(accDiff) / (nRun - 1) ;
    std::cout << "Résultats de l'expérience avec la fonction: " << bench.getFuncName() << std::endl ; 
    std::cout << "Échantillon: " << nRun << std::endl ; 
    std::cout << "Moyenne: " << moyenne << std::endl ; 
    std::cout << "Écart-type: " << stdDev << std::endl ;   
}


int main() {

    Foncteur1 foncteur1 ; 
    Foncteur2 foncteur2 ; 
    Foncteur3 foncteur3 ; 

    experience<Foncteur1>(foncteur1, 100, 100000) ; 
    experience<Foncteur2>(foncteur2, 100, 100000) ; 
    experience<Foncteur3>(foncteur3, 100, 100000) ; 
}