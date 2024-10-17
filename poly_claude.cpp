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
    double x = guess;
    for (int i = 0; i < maxIter; ++i) {
        double fx = evaluate(x);
        if (abs(fx) < tolerance) {
            return x;
        }
        double dfx = derivative().evaluate(x);
        if (dfx == 0) {
            throw runtime_error("Derivative is zero. Cannot continue.");
        }
        x = x - fx / dfx;
    }
    throw runtime_error("Root finding did not converge.");
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

        if (choice == 14) break;

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

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    cout << "Thank you for using the Polynomial Calculator!\n";
    return 0;
}