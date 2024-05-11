#include "exposant.h"

/**
 * Élève un nombre à virgule flottante à une puissance entière
 * @param mant Un nombre positif ou nul à virgule flottante:: la mantisse
 * @param n Un nombre entier positif ou nul: l'exposant
 * @return mant^n
*/
double exposant_v1(double mant, size_t n) {

    double acc = 1.0 ; 
    for (size_t i = 0; i < n; ++i) acc = acc * mant ; 
    return acc ;  
}

double exposant_v2(double mant, size_t n) {

    if (n == 0) return 1.0 ; 
    return mant * exposant_v2(mant, n-1) ; 
}

double exposant_v3(double mant, size_t n) {
    if (n == 0) return 1.0 ; 
    double temp = exposant_v3(mant, n/2) ; 
    if (n % 2) return mant * temp * temp ; 
    return temp * temp ; 
}

