#include "Polynomial.h"
#include <iostream> 

using namespace std;

Polynomial::Polynomial() : coeffs(1, 0.0) {}

// Constructor with coefficients
Polynomial::Polynomial(const vector<double>& coefficients) : coeffs(coefficients) {}

// Copy constructor
Polynomial::Polynomial(const Polynomial& other) : coeffs(other.coeffs) {}

// Destructor
Polynomial::~Polynomial() {}

// Assignment operator
Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        coeffs = other.coeffs;
    }
    return *this;
}

// Addition operator
Polynomial Polynomial::operator+(const Polynomial& other) const {
    vector<double> result(max(coeffs.size(), other.coeffs.size()), 0.0);
    for (size_t i = 0; i < result.size(); ++i) {
        if (i < coeffs.size()) result[i] += coeffs[i];
        if (i < other.coeffs.size()) result[i] += other.coeffs[i];
    }
    return Polynomial(result);
}

// Subtraction operator
Polynomial Polynomial::operator-(const Polynomial& other) const {
    vector<double> result(max(coeffs.size(), other.coeffs.size()), 0.0);
    for (size_t i = 0; i < result.size(); ++i) {
        if (i < coeffs.size()) result[i] += coeffs[i];
        if (i < other.coeffs.size()) result[i] -= other.coeffs[i];
    }
    return Polynomial(result);
}

// Multiplication operator
Polynomial Polynomial::operator*(const Polynomial& other) const {
    vector<double> result(coeffs.size() + other.coeffs.size() - 1, 0.0);
    for (size_t i = 0; i < coeffs.size(); ++i) {
        for (size_t j = 0; j < other.coeffs.size(); ++j) {
            result[i + j] += coeffs[i] * other.coeffs[j];
        }
    }
    return Polynomial(result);
}

// Equality operator
bool Polynomial::operator==(const Polynomial& other) const {
    return coeffs == other.coeffs;
}

// Output operator (friend function)
ostream& operator<<(ostream& out, const Polynomial& poly) {
    for (int i = poly.coeffs.size() - 1; i >= 0; --i) {
        if (poly.coeffs[i] != 0) {
            if (i != poly.coeffs.size() - 1 && poly.coeffs[i] > 0) out << "+";
            out << poly.coeffs[i];
            if (i > 0) out << "x";
            if (i > 1) out << "^" << i;
            out << " ";
        }
    }
    return out;
}

// Utility functions
int Polynomial::degree() const {
    return coeffs.size() - 1;
}

// Evaluate the polynomial at x
double Polynomial::evaluate(double x) const {
    double result = 0;
    for (int i = coeffs.size() - 1; i >= 0; --i) {
        result = result * x + coeffs[i];
    }
    return result;
}

// Derivative of the polynomial
Polynomial Polynomial::derivative() const {
    if (coeffs.size() <= 1) return Polynomial();
    vector<double> deriv(coeffs.size() - 1);
    for (size_t i = 1; i < coeffs.size(); ++i) {
        deriv[i - 1] = coeffs[i] * i;
    }
    return Polynomial(deriv);
}

// Integral of the polynomial (indefinite integral, constant term is 0)
Polynomial Polynomial::integral() const {
    vector<double> integ(coeffs.size() + 1, 0.0);
    for (size_t i = 0; i < coeffs.size(); ++i) {
        integ[i + 1] = coeffs[i] / (i + 1);
    }
    return Polynomial(integ);
}

// Definite integral from x1 to x2
double Polynomial::integral(double x1, double x2) const {
    Polynomial integ = integral();
    return integ.evaluate(x2) - integ.evaluate(x1);
}

// Get root using Newton's method
double Polynomial::getRoot(double guess, double tolerance, int maxIter) {
    Polynomial deriv = derivative();
    for (int i = 0; i < maxIter; ++i) {
        double f_val = evaluate(guess);
        double f_deriv = deriv.evaluate(guess);
        if (abs(f_val) < tolerance) return guess;
        guess -= f_val / f_deriv;
    }
    return guess;
}

// Set coefficients
void Polynomial::setCoefficients(const vector<double>& coefficients) {
    coeffs = coefficients;
}

// Get coefficient of a specific degree
double Polynomial::getCoefficient(int degree) const {
    if (degree < 0 || degree >= coeffs.size()) return 0.0;
    return coeffs[degree];
}

// Composition of polynomials
Polynomial Polynomial::compose(const Polynomial& q) const {
    Polynomial result({0});
    Polynomial temp({1});
    for (size_t i = 0; i < coeffs.size(); ++i) {
        result = result + temp * Polynomial({coeffs[i]});
        temp = temp * q;
    }
    return result;
}


int main() {
    // Example 1: Quadratic Polynomial (Degree 2)
    Polynomial p1({1, 3, 4});  // Represents 4x^2 + 3x + 1
    Polynomial p1_neg({1, 3, 4}); // its negative
    // Example 2: Cubic Polynomial (Degree 3)
    Polynomial p2({-7, 3, -5, 2});  // Represents 2x^3 - 5x^2 + 3x - 7
    // Example 3: Quartic Polynomial (Degree 4)
    Polynomial p3({4, -1, 0, 2, 1});  // Represents x^4 + 2x^3 - x + 4
    // Example 4: Polynomial with Zero Coefficients
    Polynomial p4({7, 0, -3, 0, 1, 0});  // Represents x^5 - 3x^2 + 7
    // Example 5: Negative Coefficients
    Polynomial p5({-8, 5, -1, -2});  // Represents -2x^3 - x^2 + 5x - 8
    // Example 6: High Degree Polynomial (Degree 7)
    Polynomial p6({9, -1, 7, 0, 0, -4, 2, 3});  // Represents 3x^7 + 2x^6 - 4x^5 + 7x^2 - x + 9
    // Example 7: Zero Polynomial (All Coefficients Zero)
    Polynomial p7({0});  // Represents 0
    // Example 8: Polynomial with Fractions (Rational Coefficients)
    Polynomial p8({5.0/6, -3.0/4, 1.0/2});  // Represents (1/2)x^2 - (3/4)x + 5/6
    // Example 9: Quadratic Polynomial with Complex Roots (Imaginary Solutions)
    Polynomial p9({1, 0, 1});  // Represents x^2 + 1 (Roots: i, -i)
    // Example 10: Quadratic Polynomial with Complex Roots
    Polynomial p10({1, -2, 5});  // Represents x^2 - 2x + 5 (Roots: 1 + 2i, 1 - 2i)

    Polynomial sum = p1 + p2;
    Polynomial difference = p1- p2;
    Polynomial product = p1 * p2;
    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
    cout << "p1 + p2: " << sum << endl;
    cout << "p1- p2: " << difference << endl;
    cout << "p1 * p2: " << product << endl;
    double x = 2.5;
    cout << "p1 evaluated at x = " << x << ": " << p1.evaluate(x) << endl;
    cout << "p2 evaluated at x = " << x << ": " << p2.evaluate(x) << endl;
}