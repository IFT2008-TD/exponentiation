#ifndef EXPBENCH_H
#define EXPBENCH_H

#include <iostream>
#include <vector>
#include <chrono>
#include <random>

template <typename T>
class ExpBench {

private:
    struct Triplet {
        double res ; 
        double mnt ; 
        double ex ; 

        Triplet(double r, double m, size_t e) : res(r), mnt(m), ex(e) {}
    } ; 

    using triplet = struct Triplet ; 

public:
    ExpBench(T funcObj) : callback(funcObj) {}

    std::string getFuncName() const {return callback.getName() ; } 
    void test_validity() ; 
    long unsigned int benchmark(size_t = 10000) ; 
    void init_benchmark(size_t) ; 

private:
    T callback ; 
    const std::vector<triplet> tests {triplet(1.0, 1.0, 0), 
                                      triplet(4.0, 2.0, 2), 
                                      triplet(100000.0, 10.0, 5), 
                                      triplet(1024.0, 2.0, 10)} ; 
    std::vector<double> mant ; 
    std::vector<size_t> ex ;  

} ; 

template <typename T>
void ExpBench<T>::test_validity() {
    std::cout << "Test de validité\n" ; 
    for (size_t i = 0 ; i < tests.size(); ++i) {
        double r = tests.at(i).res ; 
        double m = tests.at(i).mnt ; 
        size_t e = tests.at(i).ex ; 
        double obt = callback(m, e) ; 
        if (r == obt) std::cout << "TEST "  << i << " RÉUSSI!\n" ;
        else std::cout << "TEST " << i << " ÉCHOUÉ: Attendu = " << r << " Obtenu = " << obt << "\n" ; 
    }
    std::cout << "Fin du test de validité\n" ; 
    return ; 
}

template <typename T>
void ExpBench<T>::init_benchmark(size_t nSample) {
    std::random_device dev ; 
    std::mt19937 rng(dev()) ; 
    std::uniform_int_distribution<std::mt19937::result_type> uni(0, 50) ; 
    std::normal_distribution<double> norm(50.0, 10.0) ; 

    mant.resize(nSample) ; 
    ex.resize(nSample) ; 
    
    for (size_t i = 0; i < nSample; ++i) {
        mant[i] = norm(rng) ; 
        if (mant[i] < 0.0) mant[i] = - mant[i] ; 
        ex[i] = static_cast<size_t> (uni(rng)) ; 
    }
}

template <typename T>
long unsigned int ExpBench<T>::benchmark(size_t nSample) { 
    
    init_benchmark(nSample) ; 

    auto debut = std::chrono::high_resolution_clock::now() ; 
    for (size_t i = 0; i < nSample; ++i) {
        callback(mant[i], ex[i]) ;      
    }
    auto fin = std::chrono::high_resolution_clock::now() ; 

    auto duree = std::chrono::duration_cast<std::chrono::microseconds> (fin - debut) ; 
    long unsigned int resultat = duree.count() ; 

    return resultat ; 
    
} 

#endif