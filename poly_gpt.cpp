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


// Function to display the available polynomials
void displayPolynomials(const vector<Polynomial>& polynomials) {
    for (size_t i = 0; i < polynomials.size(); ++i) {
        cout << "Polynomial " << i + 1 << ": " << polynomials[i] << endl;
    }
}



int main() {
    vector<Polynomial> polynomials = {
    // Example 1: Quadratic Polynomial (Degree 2)
    Polynomial ({1, 3, 4}),  // Represents 4x^2 + 3x + 1
    Polynomial ({-1, -3, -4}), // its negative
    // Example 2: Cubic Polynomial (Degree 3)
    Polynomial ({-7, 3, -5, 2}),  // Represents 2x^3 - 5x^2 + 3x - 7
    // Example 3: Quartic Polynomial (Degree 4)
    Polynomial ({4, -1, 0, 2, 1}),  // Represents x^4 + 2x^3 - x + 4
    // Example 4: Polynomial with Zero Coefficients
    Polynomial ({7, 0, -3, 0, 1, 0}),  // Represents x^5 - 3x^2 + 7
    // Example 5: Negative Coefficients
    Polynomial ({-8, 5, -1, -2}),  // Represents -2x^3 - x^2 + 5x - 8
    // Example 6: High Degree Polynomial (Degree 7)
    Polynomial ({9, -1, 7, 0, 0, -4, 2, 3}),  // Represents 3x^7 + 2x^6 - 4x^5 + 7x^2 - x + 9
    // Example 7: Zero Polynomial (All Coefficients Zero)
    Polynomial ({0}),  // Represents 0
    Polynomial ({0, 0, 0}),
    // Example 8: Polynomial with Fractions (Rational Coefficients)
    Polynomial ({5.0/6, -3.0/4, 1.0/2}),  // Represents (1/2)x^2 - (3/4)x + 5/6
    // Example 9: Quadratic Polynomial with Complex Roots (Imaginary Solutions)
    Polynomial ({1, 0, 1}),  // Represents x^2 + 1 (Roots: i, -i)
    // Example 10: Quadratic Polynomial with Complex Roots
    Polynomial ({1, -2, 5})  // Represents x^2 - 2x + 5 (Roots: 1 + 2i, 1 - 2i)
    };


    int choice;
    do {
        cout << "\n--- Polynomial Menu ---\n";
        cout << "1. Add two polynomials\n";
        cout << "2. Subtract two polynomials\n";
        cout << "3. Multiply two polynomials\n";
        cout << "4. Evaluate polynomial\n";
        cout << "5. Get polynomial derivative\n";
        cout << "6. Get polynomial integral\n";
        cout << "7. Compute definite integral\n";
        cout << "8. Get polynomial degree\n";
        cout << "9. Set polynomial coefficients\n";
        cout << "10. Get polynomial coefficients\n";
        cout << "11. Compare two polynomials for equality\n";
        cout << "12. Display polynomial\n";
        cout << "13. Compose two polynomials\n";
        cout << "14. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        int pIndex1, pIndex2;
        displayPolynomials(polynomials);

        switch (choice) {
            case 1: {
                // Addition
                cout << "Choose two polynomials to add (enter indices 1-10): ";
                cin >> pIndex1 >> pIndex2;
                Polynomial result = polynomials[pIndex1 - 1] + polynomials[pIndex2 - 1];
                cout << "Result of addition: " << result << endl;
                break;
            }
            case 2: {
                // Subtraction
                cout << "Choose two polynomials to subtract (enter indices 1-10): ";
                cin >> pIndex1 >> pIndex2;
                Polynomial result = polynomials[pIndex1 - 1] - polynomials[pIndex2 - 1];
                cout << "Result of subtraction: " << result << endl;
                break;
            }
            case 3: {
                // Multiplication
                cout << "Choose two polynomials to multiply (enter indices 1-10): ";
                cin >> pIndex1 >> pIndex2;
                Polynomial result = polynomials[pIndex1 - 1] * polynomials[pIndex2 - 1];
                cout << "Result of multiplication: " << result << endl;
                break;
            }
            case 4: {
                // Evaluation
                double x;
                cout << "Choose a polynomial to evaluate (enter index 1-10): ";
                cin >> pIndex1;
                cout << "Enter value of x: ";
                cin >> x;
                cout << "Polynomial evaluated at " << x << ": " << polynomials[pIndex1 - 1].evaluate(x) << endl;
                break;
            }
            case 5: {
                // Derivative
                cout << "Choose a polynomial to differentiate (enter index 1-10): ";
                cin >> pIndex1;
                Polynomial deriv = polynomials[pIndex1 - 1].derivative();
                cout << "Derivative: " << deriv << endl;
                break;
            }
            case 6: {
                // Indefinite integral
                cout << "Choose a polynomial to integrate (enter index 1-10): ";
                cin >> pIndex1;
                Polynomial integ = polynomials[pIndex1 - 1].integral();
                cout << "Integral: " << integ << endl;
                break;
            }
            case 7: {
                // Definite integral
                double x1, x2;
                cout << "Choose a polynomial to integrate (enter index 1-10): ";
                cin >> pIndex1;
                cout << "Enter lower limit of integration: ";
                cin >> x1;
                cout << "Enter upper limit of integration: ";
                cin >> x2;
                cout << "Definite integral from " << x1 << " to " << x2 << ": " << polynomials[pIndex1 - 1].integral(x1, x2) << endl;
                break;
            }
            case 8: {
                // Degree
                cout << "Choose a polynomial to get its degree (enter index 1-10): ";
                cin >> pIndex1;
                cout << "Degree of polynomial: " << polynomials[pIndex1 - 1].degree() << endl;
                break;
            }
            case 9: {
                // Set coefficients
                vector<double> newCoeffs;
                int degree;
                cout << "Choose a polynomial to modify (enter index 1-10): ";
                cin >> pIndex1;
                cout << "Enter degree of polynomial: ";
                cin >> degree;
                newCoeffs.resize(degree + 1);
                cout << "Enter coefficients (constant term first): ";
                for (int i = 0; i <= degree; ++i) {
                    cin >> newCoeffs[i];
                }
                polynomials[pIndex1 - 1].setCoefficients(newCoeffs);
                break;
            }
            case 10: {
                // Get coefficients
                int degree;
                cout << "Choose a polynomial to get its coefficient (enter index 1-10): ";
                cin >> pIndex1;
                cout << "Enter degree to get coefficient: ";
                cin >> degree;
                cout << "Coefficient of degree " << degree << ": " << polynomials[pIndex1 - 1].getCoefficient(degree) << endl;
                break;
            }
            case 11: {
                // Equality check
                cout << "Choose two polynomials to compare for equality (enter indices 1-10): ";
                cin >> pIndex1 >> pIndex2;
                if (polynomials[pIndex1 - 1] == polynomials[pIndex2 - 1])
                    cout << "Polynomials are equal.\n";
                else
                    cout << "Polynomials are not equal.\n";
                break;
            }
            case 12: {
                // Display polynomial
                cout << "Choose a polynomial to display (enter index 1-10): ";
                cin >> pIndex1;
                cout << "Polynomial: " << polynomials[pIndex1 - 1] << endl;
                break;
            }
            case 13: {
                // Compose
                cout << "Choose two polynomials to compose (enter indices 1-10): ";
                cin >> pIndex1 >> pIndex2;
                Polynomial composed = polynomials[pIndex1 - 1].compose(polynomials[pIndex2 - 1]);
                cout << "Composed polynomial: " << composed << endl;
                break;
            }
            case 14: {
                // Exit
                cout << "Exiting...\n";
                break;
            }
            default:
                cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 14);

    return 0;

    // Polynomial sum = p1 + p2;
    // Polynomial difference = p1- p2;
    // Polynomial product = p1 * p2;
    // cout << "p1: " << p1 << endl;
    // cout << "p2: " << p2 << endl;
    // cout << "p1 + p2: " << sum << endl;
    // cout << "p1- p2: " << difference << endl;
    // cout << "p1 * p2: " << product << endl;
    // double x = 2.5;
    // cout << "p1 evaluated at x = " << x << ": " << p1.evaluate(x) << endl;
    // cout << "p2 evaluated at x = " << x << ": " << p2.evaluate(x) << endl;
}