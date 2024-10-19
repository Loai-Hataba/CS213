#include "Polynomial.h"
#include <numeric>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <limits>

Polynomial::Polynomial() {}

Polynomial::Polynomial(const vector<double>& coefficients) : coeffs(coefficients) {
    // Remove leading zeros
    while (!coeffs.empty() && coeffs.back() == 0) {
        coeffs.pop_back();
    }
}

Polynomial::Polynomial(const Polynomial& other) : coeffs(other.coeffs) {}

Polynomial::~Polynomial() {}

Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        coeffs = other.coeffs;
    }
    return *this;
}

Polynomial Polynomial::operator+(const Polynomial& other) const {
    vector<double> result_coeffs(max(coeffs.size(), other.coeffs.size()), 0);
    for (size_t i = 0; i < coeffs.size(); ++i) {
        result_coeffs[i] += coeffs[i];
    }
    for (size_t i = 0; i < other.coeffs.size(); ++i) {
        result_coeffs[i] += other.coeffs[i];
    }
    return Polynomial(result_coeffs);
}

Polynomial Polynomial::operator-(const Polynomial& other) const {
    vector<double> result_coeffs(max(coeffs.size(), other.coeffs.size()), 0);
    for (size_t i = 0; i < coeffs.size(); ++i) {
        result_coeffs[i] += coeffs[i];
    }
    for (size_t i = 0; i < other.coeffs.size(); ++i) {
        result_coeffs[i] -= other.coeffs[i];
    }
    return Polynomial(result_coeffs);
}

Polynomial Polynomial::operator*(const Polynomial& other) const {
    vector<double> result_coeffs(coeffs.size() + other.coeffs.size() - 1, 0);
    for (size_t i = 0; i < coeffs.size(); ++i) {
        for (size_t j = 0; j < other.coeffs.size(); ++j) {
            result_coeffs[i + j] += coeffs[i] * other.coeffs[j];
        }
    }
    return Polynomial(result_coeffs);
}

bool Polynomial::operator==(const Polynomial& other) const {
    return coeffs == other.coeffs;
}

ostream& operator<<(ostream& out, const Polynomial& poly) {
    bool first = true;
    for (int i = poly.coeffs.size() - 1; i >= 0; --i) {
        if (poly.coeffs[i] != 0) {
            if (!first && poly.coeffs[i] > 0) {
                out << " + ";
            } else if (!first && poly.coeffs[i] < 0) {
                out << " - ";
            }
            if (abs(poly.coeffs[i]) != 1 || i == 0) {
                out << abs(poly.coeffs[i]);
            }
            if (i > 0) {
                out << "x";
                if (i > 1) {
                    out << "^" << i;
                }
            }
            first = false;
        }
    }
    if (first) {
        out << "0";
    }
    return out;
}

int Polynomial::degree() const {
    return coeffs.size() - 1;
}

double Polynomial::evaluate(double x) const {
    return accumulate(coeffs.rbegin(), coeffs.rend(), 0.0,
                      [x](double sum, double coeff) { return sum * x + coeff; });
}

Polynomial Polynomial::compose(const Polynomial& q) const {
    Polynomial result;
    for (int i = coeffs.size() - 1; i >= 0; --i) {
        result = result * q + Polynomial({coeffs[i]});
    }
    return result;
}

Polynomial Polynomial::derivative() const {
    if (coeffs.size() <= 1) {
        return Polynomial({0});
    }
    vector<double> deriv_coeffs(coeffs.size() - 1);
    for (size_t i = 1; i < coeffs.size(); ++i) {
        deriv_coeffs[i - 1] = i * coeffs[i];
    }
    return Polynomial(deriv_coeffs);
}

Polynomial Polynomial::integral() const {
    vector<double> int_coeffs(coeffs.size() + 1);
    int_coeffs[0] = 0;  // Constant of integration
    for (size_t i = 0; i < coeffs.size(); ++i) {
        int_coeffs[i + 1] = coeffs[i] / (i + 1);
    }
    return Polynomial(int_coeffs);
}

double Polynomial::integral(double x1, double x2) const {
    Polynomial antiderivative = integral();
    return antiderivative.evaluate(x2) - antiderivative.evaluate(x1);
}

double Polynomial::getRoot(double guess, double tolerance, int maxIter) {
    vector<double> roots;
    Polynomial derivative = this->derivative();

    // Helper function to check if a root is unique (not already in the roots vector)
    auto isUniqueRoot = [&](double root) {
        for (double r : roots) {
            if (abs(r - root) < tolerance) {
                return false;
            }
        }
        return true;
    };

    // Helper function for Newton's method
    auto newtonMethod = [&](double x) {
        for (int i = 0; i < maxIter; ++i) {
            double fx = this->evaluate(x);
            if (abs(fx) < tolerance) {
                return make_pair(true, x);
            }
            double dfx = derivative.evaluate(x);
            if (dfx == 0) {
                return make_pair(false, x);
            }
            x = x - fx / dfx;
        }
        return make_pair(false, x);
    };

    // Try to find roots starting from different initial guesses
    vector<double> initialGuesses = {guess, -10, -1, 0, 1, 10};
    for (double initialGuess : initialGuesses) {
        auto [found, root] = newtonMethod(initialGuess);
        if (found && isUniqueRoot(root)) {
            roots.push_back(root);
        }
    }

    // If no roots found, try random guesses
    if (roots.empty()) {
        srand(time(nullptr));
        for (int i = 0; i < 10; ++i) {
            double randomGuess = (rand() / double(RAND_MAX)) * 20 - 10;  // Random number between -10 and 10
            auto [found, root] = newtonMethod(randomGuess);
            if (found && isUniqueRoot(root)) {
                roots.push_back(root);
            }
        }
    }

    // Output all found roots
    if (roots.empty()) {
        cout << "No roots found." << endl;
    } else {
        cout << "Roots found:" << endl;
        for (double root : roots) {
            cout << root << endl;
        }
    }

    // Return the first root found (or NaN if no roots were found)
    return roots.empty() ? numeric_limits<double>::quiet_NaN() : roots[0];
}

void Polynomial::setCoefficients(const vector<double>& coefficients) {
    coeffs = coefficients;
    while (!coeffs.empty() && coeffs.back() == 0) {
        coeffs.pop_back();
    }
}

double Polynomial::getCoefficient(int degree) const {
    if (degree >= 0 && degree < static_cast<int>(coeffs.size())) {
        return coeffs[degree];
    }
    return 0;
}

Polynomial inputPolynomial() {
    vector<double> coeffs;
    double coeff;
    cout << "Enter coefficients (starting from constant term, enter non-number to finish):\n";
    while (cin >> coeff) {
        coeffs.push_back(coeff);
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return Polynomial(coeffs);
}

int main() {
    int choice;
    Polynomial p1, p2, result;

    while (true) {
        cout << "\nPolynomial Operations Menu:\n";
        cout << "1. Add two polynomials\n";
        cout << "2. Subtract two polynomials\n";
        cout << "3. Multiply two polynomials\n";
        cout << "4. Evaluate polynomial\n";
        cout << "5. Find derivative of a polynomial\n";
        cout << "5. Find integral of a polynomial\n";
        cout << "7. Compute definite integral\n";
        cout << "8. Get polynomial degree\n";
        cout << "9. Set polynomial coefficients\n";
        cout << "10. Get polynomial coefficients\n";
        cout << "11. Compare two polynomials for equality\n";
        cout << "12. Display polynomial\n";
        cout << "13. Compose two polynomials\n";
        cout << "14. Find a root of polynomial\n";
        cout << "15. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 15) break;

        switch(choice) {
            case 1: case 2: case 3: case 13: { // Addition, Subtraction, Multiplication, Composition
                cout << "Enter first polynomial:\n";
                p1 = inputPolynomial();
                cout << "Enter second polynomial:\n";
                p2 = inputPolynomial();

                if (choice == 1) result = p1 + p2;
                else if (choice == 2) result = p1 - p2;
                else if (choice == 3) result = p1 * p2;
                else result = p1.compose(p2);

                cout << "Result: " << result << endl;
                break;
            }

            case 4: { // Evaluation
                cout << "Enter polynomial to evaluate:\n";
                p1 = inputPolynomial();
                double x;
                cout << "Enter x value: ";
                cin >> x;
                cout << "Result: " << p1.evaluate(x) << endl;
                break;
            }

            case 5: case 6: { // Derivative, Integral
                cout << "Enter polynomial:\n";
                p1 = inputPolynomial();
                result = (choice == 5) ? p1.derivative() : p1.integral();
                cout << ((choice == 5) ? "Derivative: " : "Integral: ") << result << endl;
                break;
            }

            case 7: { // Definite Integral
                cout << "Enter polynomial:\n";
                p1 = inputPolynomial();
                double a, b;
                cout << "Enter lower bound a: ";
                cin >> a;
                cout << "Enter upper bound b: ";
                cin >> b;
                cout << "Definite integral from " << a << " to " << b << ": " << p1.integral(a, b) << endl;
                break;
            }

            case 8: { // Get degree
                cout << "Enter polynomial:\n";
                p1 = inputPolynomial();
                cout << "Degree: " << p1.degree() << endl;
                break;
            }

            case 9: { // Set coefficients
                p1 = inputPolynomial();
                cout << "Polynomial set: " << p1 << endl;
                break;
            }

            case 10: { // Get coefficients
                cout << "Enter polynomial:\n";
                p1 = inputPolynomial();
                cout << "Coefficients: ";
                for (int i = 0; i <= p1.degree(); ++i) {
                    cout << p1.getCoefficient(i) << " ";
                }
                cout << endl;
                break;
            }

            case 11: { // Compare for equality
                cout << "Enter first polynomial:\n";
                p1 = inputPolynomial();
                cout << "Enter second polynomial:\n";
                p2 = inputPolynomial();
                cout << "Polynomials are " << (p1 == p2 ? "equal" : "not equal") << endl;
                break;
            }

            case 12: { // Display polynomial
                cout << "Enter polynomial:\n";
                p1 = inputPolynomial();
                cout << "Polynomial: " << p1 << endl;
                break;
            }

            case 14: { // Find roots of polynomial
                cout << "Enter polynomial:\n";
                p1 = inputPolynomial();
                double firstRoot = p1.getRoot();
                // Note: The getRoot function now prints all roots internally
                if (isnan(firstRoot)) {
                    cout << "No roots found.\n";
                } else {
                    cout << "First root: " << firstRoot << endl;
                }
                break;
            }

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    cout << "Thank you for using the Polynomial Calculator!\n";
    return 0;
}