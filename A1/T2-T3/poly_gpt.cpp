#include "Polynomial.h"
#include <vector>
#include <iostream> 
#include <chrono>

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

// Get coefficient of a specific degree
double Polynomial::getCoefficient(int degree) const {
    if (degree < 0 || degree >= coeffs.size()) return 0.0;
    return coeffs[degree];
}

// Set coefficients
void Polynomial::setCoefficients(const std::vector<double>& coefficients) {
    coeffs = coefficients;
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


void displayPolynomialMenu() {
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
    cout << "14. Get root using Newton's method\n"; // Added menu option
    cout << "15. Exit\n"; // Updated exit option
}

vector<double> inputCoefficients() {
    int degree;
    cout << "Enter the degree of the polynomial: ";
    cin >> degree;

    vector<double> coefficients(degree + 1);
    cout << "Enter coefficients (constant term first): ";
    for (int i = 0; i <= degree; ++i) {
        cin >> coefficients[i];
    }
    return coefficients;
}

int main() {
    int choice;
    do {
        displayPolynomialMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                // Addition
                cout << "Input coefficients for the first polynomial:\n";
                Polynomial p1(inputCoefficients());

                cout << "Input coefficients for the second polynomial:\n";
                Polynomial p2(inputCoefficients());

                // Start timing
                auto start = chrono::high_resolution_clock::now();

                // Perform the addition
                Polynomial result = p1 + p2;

                // End timing
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                cout << "Result of addition: " << result << endl;
                cout << "Time taken for addition: " << duration.count() << " microseconds" << endl;
                break;
            }
            case 2: {
                // Subtraction
                cout << "Input coefficients for the first polynomial:\n";
                Polynomial p1(inputCoefficients());

                cout << "Input coefficients for the second polynomial:\n";
                Polynomial p2(inputCoefficients());

                // Start timing
                auto start = chrono::high_resolution_clock::now();

                // Perform the subtraction
                Polynomial result = p1 - p2;

                // End timing
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                cout << "Result of subtraction: " << result << endl;
                cout << "Time taken for subtraction: " << duration.count() << " microseconds" << endl;
                break;
            }
            case 3: {
                // Multiplication
                cout << "Input coefficients for the first polynomial:\n";
                Polynomial p1(inputCoefficients());

                cout << "Input coefficients for the second polynomial:\n";
                Polynomial p2(inputCoefficients());

                // Start timing
                auto start = chrono::high_resolution_clock::now();

                // Perform the multiplication
                Polynomial result = p1 * p2;

                // End timing
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                cout << "Result of multiplication: " << result << endl;
                cout << "Time taken for multiplication: " << duration.count() << " microseconds" << endl;
                break;
            }
            case 4: {
                // Evaluation
                cout << "Input coefficients for the polynomial:\n";
                Polynomial p(inputCoefficients());
                
                double x;
                cout << "Enter value of x: ";
                cin >> x;

                // Start timing
                auto start = chrono::high_resolution_clock::now();

                // Perform the evaluation
                double result = p.evaluate(x);

                // End timing
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                cout << "Polynomial evaluated at " << x << ": " << result << endl;
                cout << "Time taken for evaluation: " << duration.count() << " microseconds" << endl;
                break;
            }
            case 5: {
                // Derivative
                cout << "Input coefficients for the polynomial:\n";
                Polynomial p(inputCoefficients());

                // Start timing
                auto start = chrono::high_resolution_clock::now();

                // Compute the derivative
                Polynomial deriv = p.derivative();

                // End timing
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                cout << "Derivative: " << deriv << endl;
                cout << "Time taken for derivative: " << duration.count() << " microseconds" << endl;
                break;
            }
            case 6: {
                // Indefinite integral
                cout << "Input coefficients for the polynomial:\n";
                Polynomial p(inputCoefficients());

                // Start timing
                auto start = chrono::high_resolution_clock::now();

                // Compute the integral
                Polynomial integ = p.integral();

                // End timing
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                cout << "Integral: " << integ << endl;
                cout << "Time taken for integral: " << duration.count() << " microseconds" << endl;
                break;
            }
            case 7: {
                // Definite integral
                cout << "Input coefficients for the polynomial:\n";
                Polynomial p(inputCoefficients());
                
                double x1, x2;
                cout << "Enter lower limit of integration: ";
                cin >> x1;
                cout << "Enter upper limit of integration: ";
                cin >> x2;

                // Start timing
                auto start = chrono::high_resolution_clock::now();

                // Compute the definite integral
                double result = p.integral(x1, x2);

                // End timing
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                cout << "Definite integral from " << x1 << " to " << x2 << ": " << result << endl;
                cout << "Time taken for definite integral: " << duration.count() << " microseconds" << endl;
                break;
            }
            case 8: {
                // Degree
                cout << "Input coefficients for the polynomial:\n";
                Polynomial p(inputCoefficients());

                // Start timing
                auto start = chrono::high_resolution_clock::now();

                // Get the degree
                int degree = p.degree();

                // End timing
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                cout << "Degree of polynomial: " << degree << endl;
                cout << "Time taken to get degree: " << duration.count() << " microseconds" << endl;
                break;
            }
            case 9: {
                // Set coefficients
                cout << "Input coefficients for the polynomial:\n";
                Polynomial p(inputCoefficients());
                cout << "Setting new coefficients for this polynomial.\n";
                p.setCoefficients(inputCoefficients());
                cout << "Coefficients set successfully.\n";
                break;
            }
            case 10: {
                // Get coefficient
                cout << "Input coefficients for the polynomial:\n";
                Polynomial p(inputCoefficients());
                int degree;
                cout << "Enter degree to get coefficient: ";
                cin >> degree;

                // Start timing
                auto start = chrono::high_resolution_clock::now();

                // Get coefficient
                double coeff = p.getCoefficient(degree);

                // End timing
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                cout << "Coefficient of degree " << degree << ": " << coeff << endl;
                cout << "Time taken to get coefficient: " << duration.count() << " microseconds" << endl;
                break;
            }
            case 11: {
                // Compare equality
                cout << "Input coefficients for the first polynomial:\n";
                Polynomial p1(inputCoefficients());

                cout << "Input coefficients for the second polynomial:\n";
                Polynomial p2(inputCoefficients());

                // Start timing
                auto start = chrono::high_resolution_clock::now();

                // Compare equality
                bool equal = (p1 == p2);

                // End timing
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                cout << "Polynomials are " << (equal ? "equal" : "not equal") << endl;
                cout << "Time taken for comparison: " << duration.count() << " microseconds" << endl;
                break;
            }
            case 12: {
                // Display polynomial
                cout << "Input coefficients for the polynomial:\n";
                Polynomial p(inputCoefficients());

                // Start timing
                auto start = chrono::high_resolution_clock::now();

                // Display the polynomial
                cout << p << endl;

                // End timing
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                cout << "Time taken to display polynomial: " << duration.count() << " microseconds" << endl;
                break;
            }
            case 13: {
                // Compose two polynomials
                cout << "Input coefficients for the first polynomial:\n";
                Polynomial p1(inputCoefficients());

                cout << "Input coefficients for the second polynomial:\n";
                Polynomial p2(inputCoefficients());

                // Start timing
                auto start = chrono::high_resolution_clock::now();

                // Compose the polynomials
                Polynomial result = p1.compose(p2);

                // End timing
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                cout << "Composition result: " << result << endl;
                cout << "Time taken for composition: " << duration.count() << " microseconds" << endl;
                break;
            }
            case 14: { // Case for getting the root using Newton's method
                cout << "Input coefficients for the polynomial:\n";
                Polynomial p(inputCoefficients());

                // Start timing
                auto start = chrono::high_resolution_clock::now();

                // Find the root using Newton's method
                double root = p.getRoot();

                // End timing
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                cout << "Root found: " << root << endl;
                cout << "Time taken to find root: " << duration.count() << " microseconds" << endl;
                break;
            }
            case 15: { // Update exit case number
                // Exit
                cout << "Exiting...\n";
                break;
            }
            default:
                cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 15); // Update loop condition to match exit case number

    return 0;
}