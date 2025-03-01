#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
class Polynomial {
private:
vector<double> coeffs; // Store coefficients of the polynomial
public:
// Constructors
Polynomial();
Polynomial(const vector<double>& coefficients);
Polynomial(const Polynomial& other);
// Destructor
~Polynomial();
// Assignment operator
Polynomial& operator=(const Polynomial& other);
// Arithmetic operators
Polynomial operator+(const Polynomial& other) const;
Polynomial operator-(const Polynomial& other) const;
Polynomial operator*(const Polynomial& other) const;
// Equality operator
bool operator==(const Polynomial& other) const;
// Output operator
friend ostream& operator<<(ostream& out, const Polynomial& poly);
// Utility functions
int degree() const; // Return the degree of the polynomial
double evaluate(double x) const; // Evaluate the polynomial at x
Polynomial compose(const Polynomial& q) const; // Composition
Polynomial derivative() const; // Derivative of the polynomial
Polynomial integral() const; // Return a polynomial of integration
double integral(double x1, double x2) const; // Intergate from x1 to x2
// get roots of the polynomial
double getRoot(double guess = 1.0, double tolerance = 1e-6, int maxIter = 100);
// Get coefficient of a specific degree
double getCoefficient(int degree) const;
 void setCoefficients(const std::vector<double>& coefficients);
};
 #endif // POLYNOMIAL_H