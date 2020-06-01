#include "PolynomialRing.hpp"

#include <cmath>
#include <cassert>

namespace lab {

namespace details {

    bool prime(const uint64_t& n){
        for(uint64_t i = 2; i <= sqrt(n); i++) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }

} // namespace details

PolynomialRing::PolynomialRing(uint64_t p) : _p{p} {
    assert(details::prime(p));
}

uint64_t PolynomialRing::getP() const {
    return _p;
}

Polynomial PolynomialRing::add(const Polynomial &left, const Polynomial &right) const {
    return (left + right).modify(_p);
}

Polynomial PolynomialRing::subtract(const Polynomial &left, const Polynomial &right) const {
    return (left - right).modify(_p);
}

Polynomial PolynomialRing::multiply(const Polynomial &left, const Polynomial &right) const {
    return (left * right).modify(_p);
}

Polynomial PolynomialRing::multiply(const Polynomial &polynomial, const uint64_t &num) const {
    return (polynomial * num).modify(_p);
}

Polynomial PolynomialRing::multiply(const uint64_t &num, const Polynomial &polynomial) const {
    return multiply(polynomial, num);
}

Polynomial PolynomialRing::normalize(Polynomial &polynomial) const {
    Polynomial result(polynomial.modify(_p));
    uint64_t normalizator = 1;
    if (_p > 2) {
        normalizator = std::pow(polynomial.coefficient(polynomial.degree()), _p - 2);
    }
    return (result*normalizator).modify(_p);
}

uint64_t PolynomialRing::evaluate(Polynomial &polynomial, uint64_t point) const {
    polynomial = polynomial.modify(_p);
    uint64_t result = 0;
    int64_t point_power = 1;
    for (size_t power = 0; power <= polynomial.degree(); ++power) {
        result += (polynomial.coefficient(power) * point_power) % _p;
        point_power *= point;
    }
    result %= _p;
    return result;
}

Polynomial PolynomialRing::derivate(Polynomial &polynomial) const {
    return polynomial.derivate().modify(_p);
}

} // namespace lab
