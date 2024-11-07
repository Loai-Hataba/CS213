#include "pch.h"
#include "Polynomial.h"
#include <cmath>
#include <stdexcept>
#include <sstream>
using namespace std;

class PolynomialTest : public ::testing::Test {
protected:
    Polynomial p1;
    Polynomial p2;

    void SetUp() override {
        p1 = Polynomial({ 1, -2, 3 }); // Represents 1 - 2x + 3x^2
        p2 = Polynomial({ -1, 4 });    // Represents -1 + 4x
    }
};

// Test Case 1
TEST_F(PolynomialTest, TestCase1) {
    Polynomial p1({ -1, 0, 1 });       // x^2 - 1
    Polynomial p2({ -1, 0, 0, 1 });   // x^3 - 1
    Polynomial result = p2.compose(p1);
    EXPECT_EQ(result, Polynomial({ -2, 0, 3, 0, -3, 0, 1 })); // x^6 - 3x^4 + 3x^2 - 2
}

// Test Case 2
TEST_F(PolynomialTest, TestCase2) {
    Polynomial p1({ 0, 1 });       // x
    Polynomial p2({ -1, 0, 0, 1 }); // x^3 - 1
    Polynomial sum = p1 + p2;
    EXPECT_EQ(sum, Polynomial({ -1, 1, 0, 1 })); // x^3 + x - 1
}

// Test Case 3
TEST_F(PolynomialTest, TestCase3) {
    Polynomial p1({ 0, 1, 1 });       // x^2 + x
    Polynomial p2({ -2, 0, 0, 1 }); // x^3 - 2
    Polynomial difference = p1 - p2;
    EXPECT_EQ(difference, Polynomial({ 2, 1, 1, -1 })); // -x^3 + x^2 + x + 2
}

// Test Case 4
TEST_F(PolynomialTest, TestCase4) {
    Polynomial p1({ 1, 0, 0, 1 });       // x^3 + 1  
    Polynomial p2({ -1, 0, 0, 0, 0, 1 }); // x^5 - 1
    Polynomial product = p1 * p2;
    EXPECT_EQ(product, Polynomial({ -1, 0, 0, -1, 0, 1, 0, 0, 1 })); // x^8 - x^3 - 1 
}

// Test Case 5
TEST_F(PolynomialTest, TestCase5) {
    Polynomial p({ -1, 2, 1 });    // x^2 + 2x - 1
    double result = p.evaluate(3);
    EXPECT_DOUBLE_EQ(result, 14.0); // P(3) = 3^2 + 2*3 - 1 = 14
}

// Test Case 6
TEST_F(PolynomialTest, TestCase6) {
    Polynomial p({ -1, 2, 1 });    // x^2 + 2x - 1
    Polynomial integral = p.integral();
    EXPECT_EQ(integral, Polynomial({ 0, -1, 1, 1.0 / 3.0 })); // (1/3)x^3 + x^2 - x + C
}

// Test Case 7
TEST_F(PolynomialTest, TestCase7) {
    Polynomial p({ -1, 2, 1 });    // x^2 + 2x - 1
    double integral = p.integral(0, 9); // Assuming integral method calculates the definite integral
    EXPECT_DOUBLE_EQ(integral, 315); // Integral from 0 to 9
}

// Test Case 8
TEST_F(PolynomialTest, TestCase8) {
    Polynomial p({ 1 }); // x
    Polynomial derivative = p.derivative();
    EXPECT_EQ(derivative, Polynomial({ 0 })); // 0
}

// Test Case 9
TEST_F(PolynomialTest, TestCase9) {
    Polynomial p({ 1 }); // x
    Polynomial integral = p.integral();
    EXPECT_EQ(integral, Polynomial({ 0, 1 })); // x
}

// Test Case 10
TEST_F(PolynomialTest, TestCase10) {
    Polynomial p({ 0, -1, 0, 1, 0, 1 }); // x^5 + x^3 - x
    double result = p.evaluate(2);
    EXPECT_DOUBLE_EQ(result, 38.0); // P(2) = 32 + 8 - 2 = 38
}

// Test Case 11
TEST_F(PolynomialTest, TestCase11) {
    Polynomial p({ 0, -1, 0, 1, 0, 1 }); // x^5 + x^3 - x
    Polynomial derivative = p.derivative();
    EXPECT_EQ(derivative, Polynomial({ -1, 0, 3, 0, 5 })); // 5x^4 + 3x^2 - 1
}

// Test Case 12
TEST_F(PolynomialTest, TestCase12) {
    Polynomial p({ 0, -1, 0, 1, 0, 1 }); // x^5 + x^3 - x
    Polynomial integral = p.integral();
    EXPECT_EQ(integral, Polynomial({ 0, 0, -0.5, 0, 0.25, 0, (1.0 / 6) })); // (1/6)x^6 + (1/4)x^4 - (1/2)x^2 + C
}

// Test Case 13
TEST_F(PolynomialTest, TestCase13) {
    Polynomial p({ 0, 0, -1, 0, 1, 0, -1, 0, 1 }); // x^8 - x^6 + x^4 - x^2
    double result = p.evaluate(3);
    EXPECT_DOUBLE_EQ(result, 5904); // P(3) = 5904
}

// Test Case 14
TEST_F(PolynomialTest, TestCase14) {
    Polynomial p({ 0, 0, -1, 0, 1, 0, -1, 0, 1 }); // x^8 - x^6 + x^4 - x^2
    Polynomial derivative = p.derivative();
    EXPECT_EQ(derivative, Polynomial({ 0, -2, 0, 4, 0, -6, 0, 8 })); // 8x^7 - 6x^5 + 4x^3 - 2
}

// Test Case 15
TEST_F(PolynomialTest, TestCase15) {
    Polynomial p({ 0, 0, -1, 0, 1, 0, -1, 0, 1 }); // x^8 - x^6 + x^4 - x^2
    Polynomial second_derivative = p.derivative().derivative();
    EXPECT_EQ(second_derivative, Polynomial({ -2, 0, 12, 0, -30, 0, 56 })); // 56x^6 - 30x^4 + 12x^2 - 2
}

// Test Case 16
TEST_F(PolynomialTest, TestCase16) {
    Polynomial p({ 0, 0, -1, 0, 1, 0, -1, 0, 1 }); // x^8 - x^6 + x^4 - x^2
    double result = p.evaluate(10);
    EXPECT_DOUBLE_EQ(result, 99009900); // P(10) = 99009900
}

// Test Case 17
TEST_F(PolynomialTest, TestCase17) {
    Polynomial p({ -1, 1, -3, 5 }); // 5x^4 - 3x^2 + x - 1
    double result = p.evaluate(0);
    EXPECT_DOUBLE_EQ(result, -1); // P(0) = -1
}

// Test Case 18
TEST_F(PolynomialTest, TestCase18) {
    Polynomial p({ -1, 1, -3, 0, 5 }); // 5x^4 - 3x^2 + x - 1
    Polynomial derivative = p.derivative();
    EXPECT_EQ(derivative, Polynomial({ 1, -6, 0, 20 })); // 20x^3 - 6x + 1
}

// Test Case 19
TEST_F(PolynomialTest, TestCase19) {
    Polynomial p({ -1, 1, -3, 0, 5 }); // 5x^4 - 3x^2 + x - 1
    Polynomial integral = p.integral();
    EXPECT_EQ(integral, Polynomial({ 0, -1, 0.5, -1.0, 0, 1.0 })); // x^5 - x^3 + (1/2)x^2 - x + C
}

// Test Case 20
TEST_F(PolynomialTest, TestCase20) {
    Polynomial p({ -1, 1, -3, 0, 5 }); // 5x^4 - 3x^2 + x - 1
    double integral = p.integral(0, 2); // Definite integral from 0 to 2
    EXPECT_DOUBLE_EQ(integral, 24); // Calculate this value based on the polynomial
}

// Test Case 21
TEST_F(PolynomialTest, TestCase21) {
    // 1. Evaluate P at x = -1
    Polynomial P({ 5, 4, 3 }); // 3x^2 + 4x + 5
    EXPECT_EQ(P.evaluate(-1), 4);

    // 2. Find the derivative of P
    Polynomial derivative = P.derivative();
    EXPECT_EQ(derivative, Polynomial({ 4, 6 })); // 6x + 4

    // 3. Compute the definite integral from 0 to 2
    double integralValue = P.integral(0, 2);
    EXPECT_DOUBLE_EQ(integralValue, 26); // Adjusted expected value
}

// Test Case 22 
TEST_F(PolynomialTest, TestCase22) {
    Polynomial P({ 1, 0, -2, 0, 3, 0, 1 }); // Represents x^6 + 3x^4 - 2x^2 + 1
    // 1. Evaluate P at x = 30 
    EXPECT_EQ(P.evaluate(30), 731428201);

    // 2. Find the derivative of P
    Polynomial derivative = P.derivative();
    EXPECT_EQ(derivative, Polynomial({ 0, -4, 0, 12, 0, 6 })); // 6x^5 + 12x^3 - 4x
}

// Test Case 23 
TEST_F(PolynomialTest, TestCase23) {
    Polynomial P({ (sqrt(10) / 3), 0, 0, (sqrt(6) / 3), (sqrt(3) / 2) });
    // 1. Evaluate P at x = sqrt(3) 
    EXPECT_DOUBLE_EQ(P.evaluate(sqrt(2)),( (sqrt(10) + 10 * sqrt(3) ) /3 )); // Use EXPECT_DOUBLE_EQ for floating-point comparison

    // 2. Find the derivative of P
    Polynomial derivative = P.derivative();
    EXPECT_EQ(derivative, Polynomial({ 0, 0, sqrt(6), 2 * sqrt(3) })); // Ensure this is correct
    derivative = derivative.derivative(); // 2nd Derivative
    EXPECT_EQ(derivative, Polynomial({ 0, 2 * sqrt(6), 6 * sqrt(3) })); // Ensure this is correct
}

// Test Case 24
TEST_F(PolynomialTest, TestCase24) {
    Polynomial P({ (sqrt(10) / 3), 0, 0, (sqrt(6) / 3), (sqrt(3) / 2) });

    // Compute the indefinite integral
    Polynomial Integral = P.integral();
    EXPECT_EQ(Integral, Polynomial({ 0, (sqrt(10) / 3), 0, 0, (sqrt(6) / 12), (sqrt(3) / 10) })); // Adjust expected values if needed

    // Compute the definite integral from sqrt(3) to sqrt(10)
    double definiteIntegral = P.integral(sqrt(3), sqrt(10));

    // Use EXPECT_DOUBLE_EQ for floating-point comparison
    EXPECT_NEAR(definiteIntegral, 72.15514444, 1e-5); // Allow for some floating-point tolerance
}

// Test Case 25
TEST_F(PolynomialTest, TestCase25) {
    Polynomial P({ 1, 0, (0.5), (5.0 / 4.0), (2.0 / 3.0) }); // Represents (2/3)x^4 + (5/4)x^3 + (1/2)x^2 + 1
    // Compute the indefinite integral
    Polynomial Integral = P.integral();
    EXPECT_EQ(Integral, Polynomial({ 0, 1, 0, (0.5 / 3.0), (5.0 / 16.0), (2.0 / 15.0) })); // Expected values adjusted for integration

    // Compute the definite integral from sqrt(3)/2 to sqrt(13)
    double definiteIntegral = Integral.integral(0.5, 2.5);

    // Use EXPECT_DOUBLE_EQ for exact floating-point comparison
    EXPECT_DOUBLE_EQ(definiteIntegral, 10337.0/640); // Expected value for the definite integral
}

// Test Case 26 
TEST_F(PolynomialTest, TestCase26) {
    Polynomial p1({ 0, 3, 0, 0, (sqrt(10) / 5), 0, 0, 0, (sqrt(3) / 3) }); // Represents (sqrt(3)/3)x^8 + (sqrt(10)/5)x^6 + 3x
    Polynomial p2({ 0, -(sqrt(3) / 2), 0, 0, (sqrt(6) / 4) }); // Represents (sqrt(6)/4)x^4 - (sqrt(3)/2)x
    // Compute p3 as the product of p1 and p2.
    Polynomial p3 = p1 * p2;
    // Compute the indefinite integral of p3 (the antiderivative).
    Polynomial integral = p3.integral();
    double expected_value = 117614.75952999208;
    double definiteIntegral = integral.integral((sqrt(3) / 2), sqrt(13));

    // Replace with the actual expected definite integral value.
    EXPECT_DOUBLE_EQ(definiteIntegral, expected_value);
}

// Test Case 27
TEST_F(PolynomialTest, TestCase27) {
    // Define the polynomial P(x) = x^2 - 1 
    Polynomial P({ - 1 ,0 ,1 }); 
    // Use getRoot to find the root
    double root =P.getRoot(2, 1e-6, 100);
    // Verify that the root is close to the expected value
   EXPECT_NEAR(P.evaluate(root), 0.0, 1e-6);
}

// Test Case 28 
// Test case for the polynomial x^2 + 1, which has complex roots (i and -i)
TEST_F(PolynomialTest, TestCase28) {
    // Polynomial represents x^2 + 1, which has no real roots.
    Polynomial p({ 1, 0, 1 });
    double initialGuess = 1.0;  // Starting guess
    double tolerance = 1e-6;     // Small tolerance
    int maxIter = 100;           // Maximum iterations

    // Get the root (or indication that no root exists)
    double root = p.getRoot(initialGuess, tolerance, maxIter);

    // Check if the root is NaN (or any special value you choose to indicate no real root)
    EXPECT_TRUE(std::isnan(root)); // If using NaN to indicate no real root
    // Or if you use a specific value to indicate no real root, you can check against that value
    // EXPECT_EQ(root, -1.0); // Assuming -1.0 indicates no real root (use the value you decide)
}


// Test Case 29 
TEST_F(PolynomialTest, TestCase29) {
    Polynomial poly({ 1, -2, 5 }); // Represents the polynomial x^2 - 2x + 5, which has no real roots.

    double initialGuess = 0.0; // Starting point for Newton's method
    double tolerance = 1e-5;    // Tolerance for convergence
    int maxIter = 10;           // Maximum iterations

    // Get the root (or indication that no root exists)
    double root = poly.getRoot(initialGuess, tolerance, maxIter);

    // Check if the root is NaN (or any special value you choose to indicate no real root)
    EXPECT_TRUE(isnan(root)); // Assuming you return NaN to indicate no real root
    // Or check against a specific value indicating no real root
    // EXPECT_EQ(root, -1.0); // Use this if you choose a specific value to indicate no real root
}

// Test 30 
TEST_F(PolynomialTest, Test30) {
    //Test -->27
    Polynomial p1({ -9 });
    Polynomial p2({ 12 });
    EXPECT_EQ(p1.integral(), Polynomial({ 0,-9 }));
    EXPECT_EQ(p1 - p2, Polynomial({-21 }));
    EXPECT_EQ(p1 * p2, Polynomial({ -108 }));
    EXPECT_EQ(p1.derivative(), Polynomial({ 0 }));
    EXPECT_EQ(p1.evaluate(2), -9);
    EXPECT_DOUBLE_EQ(p1.integral(0, 1), -9);
 
}


// Test 31
TEST_F(PolynomialTest, Test31) {
    Polynomial p1({ 5 }); // Polynomial 1: 5
    Polynomial p2({ 1 }); // Polynomial 2: 1

    // Sum
    EXPECT_EQ((p1 + p2), Polynomial({ 6 })); // Sum: 6

    // Subtraction
    EXPECT_EQ((p1 - p2), Polynomial({ 4 })); // Subtraction: 4

    // Product
    EXPECT_EQ((p1 * p2), Polynomial({ 5 })); // Product: 5

    // Degree
    EXPECT_EQ(p1.degree(), 0); // Degree of Polynomial: 0

    // Evaluation
    EXPECT_DOUBLE_EQ(p1.evaluate(2), 5); // Evaluation at x=2: 5

    // Derivative
    EXPECT_EQ(p1.derivative(), Polynomial({ 0 })); // Derivative: 0

    // Integral
    EXPECT_EQ(p1.integral(), Polynomial({ 0 , 5 })); // Integral: 5*x

    // Definite integral
    EXPECT_EQ(p1.integral(0, 1), 5); // Integral: 5*x


    double initialGuess = 0.0; // Starting point for Newton's method
    double tolerance = 1e-5;    // Tolerance for convergence
    int maxIter = 10;           // Maximum iterations

    // Expect the result to be NaN or another indication of no real roots
    double root = p1.getRoot(initialGuess, tolerance, maxIter);

    // Check if the root is NaN
    EXPECT_TRUE(std::isnan(root)); // If you want to check for NaN
    // Alternatively, if your implementation defines a specific behavior for no real root
}
// Test 32
TEST_F(PolynomialTest, Test32) {
    //Test -->28
    Polynomial p1({ -1,-10,10,-1,2,-3,13,5,-4,13,13});
    Polynomial p2({ 4,12,7,12,3,3,-8,-1,7,9,12 });
    EXPECT_EQ(p1 .derivative(), Polynomial({-10,20,-3,8,-15,78,35,-32,117,130}));
    EXPECT_EQ(p1.evaluate(2), 20363);
}

// Test 33
TEST_F(PolynomialTest, Test33) {
    //Test -->28
    Polynomial p1({ -1,-10,10,-1,2,-3,13,5,-4,13,13 });
    Polynomial p2({ 4,12,7,12,3,3,-8,-1,7,9,12 });
    EXPECT_EQ(p1.integral(), Polynomial({ 0,-1,-5,10.0/3 , -1.0/4 ,2.0/5 , -0.5 , 13.0/7 , 5.0 /8 ,-4.0/9 ,13.0 /10 , 13.0/11 }));
    EXPECT_NEAR(p1.integral(0, 1), 41659.0 / 27720, 1e-5);
}
// Test 34
TEST_F(PolynomialTest, Test34) {
   // Polynomial 1: 12 * x ^ 8 - 10 * x ^ 7 + x ^ 6 + x ^ 5 + 10 * x ^ 4 - 12 * x ^ 3 - 6 * x ^ 2 - 9 * x - 6

    Polynomial p1({ -6, -9, -6, -12, 10, 1, 1, -10, 12 });
    //Polynomial 2: -2*x^8 + 3*x^7 + 2*x^6 - x^5 - 6*x^4 + 8*x^3 + 12*x^2 - x - 6 14*x + 11
    
    Polynomial p2({ -6, -1, 12, 8, -6, -1, 2, 3, -2 });
    EXPECT_EQ((p1 - p2), Polynomial({ 0, -8, -18, -20, 16, 2, -1, -13, 14 })); // Product: 5
    EXPECT_EQ(p1.integral(0, 1), -367.0 / 28);
}

// Test 35
TEST_F(PolynomialTest, Test35) {
    // Polynomial 1: -4*x^10 - 4*x^9 + 9*x^8 - 6*x^7 + 7*x^6 - 9*x^5 + 6*x^4 - 11*x^3 + 8*x^2 - x - 11
    Polynomial p1({ -11, -1, 8, -11, 6, -9, 7, -6, 9, -4, -4 });

    // Real roots of Polynomial 1: [-2.41489316821433, -0.663011179796566]
    double initialGuess1 = -2.0; // Starting guess close to -2.41489
    double initialGuess2 = -0.5;  // Starting guess close to -0.66301
    double tolerance = 1e-5;       // Smaller tolerance
    int maxIter = 200;             // Increased maximum iterations

    // Test for the first root
    double root1 = p1.getRoot(initialGuess1, tolerance, maxIter);
    EXPECT_NEAR(root1, -2.41489316821433, tolerance); // Check close to the expected root

    // Test for the second root
    double root2 = p1.getRoot(initialGuess2, tolerance, maxIter);
    EXPECT_NEAR(root2, -0.663011179796566, tolerance); // Check close to the expected root
}




TEST_F(PolynomialTest, Test36) {
    //Test -->26
    Polynomial p1({ -1,-4,6,-8,-2,10,6,9 });
    Polynomial p2({-14,-7,4,7,-10,8,0,15});
    EXPECT_EQ(p1*p2, Polynomial({ 14,63,-60,47,90,-84,-310,-29,-73,52,-37,-72,222,90,135 }));
    EXPECT_EQ(p1.evaluate(2), 1775);
}


TEST_F(PolynomialTest, Test37) {
    //Test -->26
    Polynomial p1({ -1,-4,6,-8,-2,10,6,9 });
    Polynomial p2({ -14,-7,4,7,-10,8,0,15 });
    EXPECT_EQ(p1 - p2, Polynomial({ 13,3,2,-15,8,2,6,-6 }));
    EXPECT_DOUBLE_EQ(p1.integral(0, 1), 209.0/ 840);
}

TEST_F(PolynomialTest, Test38) {
    //Test -->26
    Polynomial p1({ -1,-4,6,-8,-2,10,6,9 });
    Polynomial p2({ -14,-7,4,7,-10,8,0,15 });
    EXPECT_EQ(p1.derivative(), Polynomial({-4,12,-24,-8,50,36 ,63}));
    EXPECT_DOUBLE_EQ(p1.degree(), 7);
}

TEST_F(PolynomialTest, Test39) {
    //Test -->46
    Polynomial p1({-13,12,15,5,12,-2,13,-10,2,12,15 });
    Polynomial p2({ -12,-14,-10,-2,1,-3,14,1,-8,-10,-11 });
    EXPECT_EQ(p1+p2, Polynomial({ -25,-2,5,3,13,-5,27,-9,-6,2,4 }));
    EXPECT_DOUBLE_EQ(p1.degree(), 10);
}
TEST_F(PolynomialTest, Test40) {
    //Test -->46
    Polynomial p1({ -13,12,15,5,12,-2,13,-10,2,12,15 });
    Polynomial p2({ -12,-14,-10,-2,1,-3,14,1,-8,-10,-11 });
    EXPECT_EQ(p1 * p2, Polynomial({156,38,-218,-364,-401,-173,-461,49,313,-17,-253,-721,-273,-310,-219,97,163,9,-262,-282,-165 }));
    EXPECT_DOUBLE_EQ(p1.integral(0,1), 16319.0 / 3465);
    EXPECT_DOUBLE_EQ(p1.evaluate(2), 21807);
}
TEST_F(PolynomialTest, Test41) {
    Polynomial p1({ -13,12,15,5,12,-2,13,-10,2,12,15 });
    Polynomial p2({ -12,-14,-10,-2,1,-3,14,1,-8,-10,-11 });
    EXPECT_EQ(p1.integral(), Polynomial({0,-13,6,5,5.0 / 4,12.0 / 5,-1.0 / 3,13.0 / 7,-5.0 / 4,2.0 / 9,6.0 / 5,15.0 / 11}));
    EXPECT_EQ(p1.derivative(), Polynomial({12,30,15,48,-10,78,-70,16,108,150}));

}


TEST_F(PolynomialTest, Test42) {
    // Create two polynomials
    Polynomial poly1({ 10, 4, 0, 10, 4, -8 });  // Represents -8*x^5 + 4*x^4 + 10*x^3 + 4*x + 10
    Polynomial poly2({ 12, 15, 8, 1, 11, -14 }); // Represents -14*x^5 + 11*x^4 + x^3 + 8*x^2 + 15*x + 12

    // Test addition
    Polynomial sum = poly1 + poly2;
    EXPECT_EQ(sum, Polynomial({ 22, 19, 8, 11, 15, -22 })); // -22*x^5 + 15*x^4 + 11*x^3 + 8*x^2 + 19*x + 22

    // Test subtraction
    Polynomial difference = poly1 - poly2;
    EXPECT_EQ(difference, Polynomial({ -2, -11, -8, 9, -7, 6 })); // 6*x^5 - 7*x^4 + 9*x^3 - 8*x^2 - 11*x - 2

    // Test multiplication
    Polynomial product = poly1 * poly2;
    EXPECT_EQ(product, Polynomial({ 120, 198, 140, 162, 312, -52, -134, 50, -104, -144, 112 })); // 112*x^10 - 144*x^9 - 104*x^8 + 50*x^7 - 134*x^6 - 52*x^5 + 312*x^4 + 162*x^3 + 140*x^2 + 198*x + 120

    // Test degree
    EXPECT_EQ(poly1.degree(), 5);
    EXPECT_EQ(poly2.degree(), 5);

    // Test evaluation at x=2
    EXPECT_DOUBLE_EQ(poly1.evaluate(2), -94); // Evaluation of poly1 at x=2

    // Test derivative
    Polynomial derivative = poly1.derivative();
    EXPECT_EQ(derivative, Polynomial({ 4, 0, 30, 16, -40 })); // 4 + 0*x + 30*x^2 + 16*x^3 - 40*x^4

    // Test integral
    Polynomial integral = poly1.integral();
    EXPECT_EQ(integral, Polynomial({ 0, 10, 2, 0, 5.0 / 2, 4.0 / 5, -4.0 / 3 })); // 0 + 10*x + 2*x^2 + 0*x^3 + 5/2*x^4 + 4/5*x^5 - 4/3*x^6
    // Test definite integral from 0 to 1
    EXPECT_DOUBLE_EQ(poly1.integral(0, 1), 419.0 / 30); // Definite integral from x=0 to x=1

  
}

TEST_F(PolynomialTest, Test43) {
    // Create two polynomials
    Polynomial poly1({ -11, 15, -11, -12, -9, 14, -1, 14 });   // 14*x^7 - x^6 + 14*x^5 - 9*x^4 - 12*x^3 - 11*x^2 + 15*x - 11
    Polynomial poly2({ -13, 9, -11, 6, 13, 2, 13, -11 }); // -11*x^7 + 13*x^6 + 2*x^5 + 13*x^4 + 6*x^3 - 11*x^2 + 9*x - 13

    // Test addition
    Polynomial sum = poly1 + poly2;
    EXPECT_EQ(sum, Polynomial({ -24, 24, -22, -6, 4, 16, 12, 3 })); // 14*x^11 + 9*x^10 + 4*x^9 - 2*x^8 + 7*x^7 - 7*x^6 - 14*x^5 + x^4 - 13*x^3 - 13*x^2 + 14*x - 4

    // Test subtraction
    Polynomial difference = poly1 - poly2;
    EXPECT_EQ(difference, Polynomial({ 2, 6, 0,-18, -22, 12, -14, 25 })); // 8*x^11 - 17*x^10 - 16*x^9 - 14*x^8 + x^7 + 9*x^6 + 12*x^5 - 3*x^4 - 15*x^3 - 15*x^2 + 4*x + 16

    // Test multiplication
    Polynomial product = poly1 * poly2;
    EXPECT_EQ(product, Polynomial({ 143, -294, 399, -174, 77, -24, -90, -261, -228, -31, 114, 461, -139, 193, -154 })); // Product coefficients

    // Test degree
    EXPECT_EQ(poly1.degree(), 7);
    EXPECT_EQ(poly2.degree(), 7);

    // Test evaluation at x=2
    EXPECT_DOUBLE_EQ(poly1.evaluate(2), 1911); // Evaluation of poly1 at x=2

    // Test derivative
    Polynomial derivative = poly1.derivative();
    EXPECT_EQ(derivative, Polynomial({ 15, -22, -36, -36, 70, -6, 98 })); // Derivative coefficients   
   // Test definite integral from 0 to 1
    EXPECT_DOUBLE_EQ(poly1.integral(0, 1), -3371.0 / 420); // Definite integral
}
TEST_F(PolynomialTest, Test44) {
    // Create two polynomials
    Polynomial poly1({ -11, 15, -11, -12, -9, 14, -1, 14 });   // 14*x^7 - x^6 + 14*x^5 - 9*x^4 - 12*x^3 - 11*x^2 + 15*x - 11
    Polynomial poly2({ -13, 9, -11, 6, 13, 2, 13, -11 }); // -11*x^7 + 13*x^6 + 2*x^5 + 13*x^4 + 6*x^3 - 11*x^2 + 9*x - 13

    // Test addition
    Polynomial sum = poly1 + poly2;
    EXPECT_EQ(sum, Polynomial({ -24, 24, -22, -6, 4, 16, 12, 3 })); // 14*x^11 + 9*x^10 + 4*x^9 - 2*x^8 + 7*x^7 - 7*x^6 - 14*x^5 + x^4 - 13*x^3 - 13*x^2 + 14*x - 4

    // Test subtraction
    Polynomial difference = poly1 - poly2;
    EXPECT_EQ(difference, Polynomial({ 2, 6, 0,-18, -22, 12, -14, 25 })); // 8*x^11 - 17*x^10 - 16*x^9 - 14*x^8 + x^7 + 9*x^6 + 12*x^5 - 3*x^4 - 15*x^3 - 15*x^2 + 4*x + 16

    // Test multiplication
    Polynomial product = poly1 * poly2;
    EXPECT_EQ(product, Polynomial({ 143, -294, 399, -174, 77, -24, -90, -261, -228, -31, 114, 461, -139, 193, -154 })); // Product coefficients

    // Test degree
    EXPECT_EQ(poly1.degree(), 7);
    EXPECT_EQ(poly2.degree(), 7);

    // Test evaluation at x=2
    EXPECT_DOUBLE_EQ(poly1.evaluate(2), 1911); // Evaluation of poly1 at x=2

    // Test derivative
    Polynomial derivative = poly1.derivative();
    EXPECT_EQ(derivative, Polynomial({ 15, -22, -36, -36, 70, -6, 98 })); // Derivative coefficients   
    // Test definite integral from 0 to 1
    EXPECT_DOUBLE_EQ(poly1.integral(0, 1), -3371.0 / 420); // Definite integral
}
TEST_F(PolynomialTest, Test45) {
   //Test -->85
    Polynomial p1({ 10,-1,15,-11,14,-3,8,4,-6 });
    Polynomial p2({-10,-8,5,-14,-10,9,4,-10,-10}); 
    EXPECT_EQ(p1.evaluate(2), -404); 
    EXPECT_EQ(p1*p2, Polynomial({ -100,-70,-92,-155,-63,-247,49,-174,-159,-72,-177,74,18,-88,-144,20,60 })); 
}
TEST_F(PolynomialTest, Test46) {
    //Test -->85
    // Remmeber to do Real roots of Polynomial 1: [-1.58327556220727, 1.71953761729611]

    Polynomial p1({ 10,-1,15,-11,14,-3,8,4,-6 });
    Polynomial p2({ -10,-8,5,-14,-10,9,4,-10,-10 });
    EXPECT_EQ(p1.integral(), Polynomial({0,10,-0.5,5 ,(-11.0/4) ,(14.0/5) , -0.5,8.0/7 ,0.5 , -2.0/3}));
}
TEST_F(PolynomialTest, Test47) {
    //Test -->86
    Polynomial p1({ -14,9,-6,3,-12,7,10});
    Polynomial p2({-3,-13,14,-2,-14,-1,12 });
    EXPECT_EQ(p1-p2, Polynomial({-11,22,-20,5,2,8,-2  }));
    EXPECT_DOUBLE_EQ(p1.integral(0,1), -4433.0 / 420);
}
TEST_F(PolynomialTest, Test48) {
    //Test -->86
     // Remmeber to do Real roots of Polynomial 1: [-1.76254517978563, 1.04918639904969]

    Polynomial p1({ -14,9,-6,3,-12,7,10 });
    Polynomial p2({ -3,-13,14,-2,-14,-1,12 });
    EXPECT_EQ(p1.derivative(), Polynomial({9,-12,9,-48,35,60}));
    EXPECT_EQ(p1.evaluate(2), 676);
}
TEST_F(PolynomialTest, Test49) {
    //Test -->89

    Polynomial p1({ 13,8,0,-10,3,-7,-1,-13,2,12});
    Polynomial p2({ -2 ,-7 ,2 ,-11 ,-9 ,-5 ,14 ,-6 ,12  });
    EXPECT_EQ(p1 + p2 , Polynomial({11,1,2,-21,-6,-12,13,-19,14,12  }));
    EXPECT_EQ(p1.integral(0,1), 34241.0 / 2520);
}
TEST_F(PolynomialTest, Test50) {
    //Test -->89
    // Remmeber to do Real roots of Polynomial 1: [-1.37922798199990]
    Polynomial p1({ 13,8,0,-10,3,-7,-1,-13,2,12 });
    Polynomial p2({ -2 ,-7 ,2 ,-11 ,-9 ,-5 ,14 ,-6 ,12 });
    EXPECT_EQ(p1 .integral (), Polynomial({0,13,4,0,-5.0/2 ,3.0/5 ,-7.0/6 ,-1.0/7 , -13.0/8 ,2.0/9,6.0/5}));
    EXPECT_EQ(p1.integral(0, 1), 34241.0 / 2520);
}
TEST_F(PolynomialTest, Test51) {
    //Test -->90
    Polynomial p1({ -13,0,-11,-7,-10,11 });
    Polynomial p2({ 4,-6,-6,-2,-2,-14 });
    EXPECT_EQ(p1*p2, Polynomial({ -52,78,34,64,94,350,30,122,96,118,-154 }));
    EXPECT_EQ(p1.evaluate(2),79);
}
TEST_F(PolynomialTest, Test52) {
    //Test -->90
    // Remmeber to do Real roots of Polynomial 1: [1.73684576071411]

    Polynomial p1({ -13,0,-11,-7,-10,11 });
    Polynomial p2({ 4,-6,-6,-2,-2,-14 });
    EXPECT_EQ(p1.integral(), Polynomial({ 0,-13,0,-11.0 / 3,-7.0 / 4,-2,11.0 / 6 }));
    EXPECT_EQ(p1.integral(0,1), -223.0/12);
}
TEST_F(PolynomialTest, Test53) {
    //Test -->93
    Polynomial p1({ -5,-1,0,-6,-8,15,-9,7,-7,9,-14,-10 });
    Polynomial p2({10,-8,-12,-1,15,2,-4,-7,-8,6,10,12});
    EXPECT_EQ(p1.derivative(), Polynomial({-1,0,-18,-32,75 ,-54 ,49 ,-56 ,81,-140,-110}));
    EXPECT_EQ(p1.evaluate(2), -31383);
}
TEST_F(PolynomialTest, Test54) {
    //Test -->93
    // Remmeber to Real roots of Polynomial 1: [-2.13178791593010]

    Polynomial p1({ -5,-1,0,-6,-8,15,-9,7,-7,9,-14,-10 });
    Polynomial p2({ 10,-8,-12,-1,15,2,-4,-7,-8,6,10,12 });
    EXPECT_EQ(p1.integral(), Polynomial({0,-5,-0.5,0,-3.0/2,-8.0/5,5.0 /2 ,-9.0/7, 7.0/8,-7.0/9,9.0/10,-14.0/11,-5.0/6 }));

    EXPECT_EQ(p1.evaluate(2), -31383);
    EXPECT_EQ(p1.integral(0, 1), -235469.0 / 27720);
}
TEST_F(PolynomialTest, Test55) {
    //Test -->97
    Polynomial p1({ -4,8,11 });
    Polynomial p2({ -4,4,15 });
    EXPECT_EQ(p1.integral(), Polynomial({ 0,-4,4,11.0/3 }));
    EXPECT_EQ(p1-p2, Polynomial({ 0,4,-4 }));
    EXPECT_EQ(p1 * p2, Polynomial({ 16,-48,-72,164,165}));
    EXPECT_EQ(p1.derivative(), Polynomial({ 8,22 }));
    EXPECT_EQ(p1.evaluate(2), 56);
    EXPECT_DOUBLE_EQ(p1.integral(0, 1), 11.0/3);
    //Real roots of Polynomial 1: [-1.06781515385589, 0.340542426583167]
}
TEST_F(PolynomialTest, Test56) {
    // Polynomial: P(x) = -1x^9 - 10x^8 + 10x^7 - 1x^6 + 2x^5 - 3x^4 + 13x^3 + 5x^2 - 4x + 13
    Polynomial p1({ -1, -10, 10, -1, 2, -3, 13, 5, -4, 13, 13 });

    // Define initial guesses for the roots
    double guess1 = -0.1; // Close to the first root
    double guess2 = 0.7;  // Close to the second root
    double tolerance = 1e-5; // Tolerance for convergence
    int maxIter = 100; // Maximum iterations

    // Get the roots using the getRoot method
    double root1 = p1.getRoot(guess1, tolerance, maxIter);
    double root2 = p1.getRoot(guess2, tolerance, maxIter);

    // Check if the roots are close to the expected values
    EXPECT_NEAR(root1, -0.0915290543036897, tolerance);
    EXPECT_NEAR(root2, 0.727055676529518, tolerance);
}

TEST_F(PolynomialTest, Test57) {
    // Polynomial coefficients for: -1 * x^6 - 4 * x^5 + 6 * x^4 - 8 * x^3 - 2 * x^2 + 10 * x + 6
    Polynomial p1({ -1, -4, 6, -8, -2, 10, 6, 9 });

    double tolerance = 1e-6; // Set the tolerance level for root finding
    int maxIter = 100; // Set maximum iterations for Newton's method

    // Initial guesses based on expected roots
    double guess1 = -1.0; // Near the first expected root
    double guess2 = -0.2; // Near the second expected root
    double guess3 = 0.7;  // Near the third expected root

    // Get roots using the getRoot function
    double root1 = p1.getRoot(guess1, tolerance, maxIter);
    double root2 = p1.getRoot(guess2, tolerance, maxIter);
    double root3 = p1.getRoot(guess3, tolerance, maxIter);

    // Check that the found roots are close to the expected values
    EXPECT_NEAR(root1, -1.03819717707786, tolerance);
    EXPECT_NEAR(root2, -0.186199186330593, tolerance);
    EXPECT_NEAR(root3, 0.749600188448983, tolerance);
}

TEST_F(PolynomialTest, Test58) {
    // Polynomial coefficients for: -1 * x^6 - 4 * x^5 + 6 * x^4 - 8 * x^3 - 2 * x^2 + 10 * x + 6
    Polynomial p1({ -1, -4, 6, -8, -2, 10, 6, 9 });

    double tolerance = 1e-6; // Set the tolerance level for root finding
    int maxIter = 100; // Set maximum iterations for Newton's method

    // Initial guesses based on expected roots
    double guess1 = -1.0; // Near the first expected root
    double guess2 = -0.2; // Near the second expected root
    double guess3 = 0.7;  // Near the third expected root

    // Get roots using the getRoot function
    double root1 = p1.getRoot(guess1, tolerance, maxIter);
    double root2 = p1.getRoot(guess2, tolerance, maxIter);
    double root3 = p1.getRoot(guess3, tolerance, maxIter);

    // Check that the found roots are close to the expected values
    EXPECT_NEAR(root1, -1.03819717707786, tolerance);
    EXPECT_NEAR(root2, -0.186199186330593, tolerance);
    EXPECT_NEAR(root3, 0.749600188448983, tolerance);
}
TEST_F(PolynomialTest, Test59) {
    // Polynomial coefficients for: 10 * x^8 - 1 * x^7 + 15 * x^6 - 11 * x^5 + 14 * x^4 - 3 * x^3 + 8 * x^2 + 4 * x - 6
    Polynomial p1({ 10, -1, 15, -11, 14, -3, 8, 4, -6 });

    double tolerance = 1e-6; // Set the tolerance level for root finding
    int maxIter = 100; // Set maximum iterations for Newton's method

    // Initial guesses based on expected roots
    double guess1 = -1.5; // Near the first expected root
    double guess2 = 1.7;  // Near the second expected root

    // Get roots using the getRoot function
    double root1 = p1.getRoot(guess1, tolerance, maxIter);
    double root2 = p1.getRoot(guess2, tolerance, maxIter);

    // Check that the found roots are close to the expected values
    EXPECT_NEAR(root1, -1.58327556220727, tolerance);
    EXPECT_NEAR(root2, 1.71953761729611, tolerance);
}

TEST_F(PolynomialTest, Test60) {
    // Polynomial coefficients for: -4 * x^2 + 8 * x + 11
    Polynomial p1({ -4, 8, 11 });

    double tolerance = 1e-6; // Set the tolerance level for root finding
    int maxIter = 100; // Set maximum iterations for Newton's method

    // Initial guesses based on expected roots
    double guess1 = -1.0; // Near the first expected root
    double guess2 = 0.5;  // Near the second expected root

    // Get roots using the getRoot function
    double root1 = p1.getRoot(guess1, tolerance, maxIter);
    double root2 = p1.getRoot(guess2, tolerance, maxIter);

    // Check that the found roots are close to the expected values
    EXPECT_NEAR(root1, -1.06781515385589, tolerance);
    EXPECT_NEAR(root2, 0.340542426583167, tolerance);
}
TEST_F(PolynomialTest, Test61) {
    // Polynomial coefficients for: x^4 + 2x^3 + 5x^2 + 6x + 10
    Polynomial p1({ 10, 6, 5, 2, 1 });

    double initialGuess = 0.0; // Starting point for Newton's method
    double tolerance = 1e-6;    // Tolerance for convergence
    int maxIter = 100;          // Maximum iterations

    // Expect that getRoot does not return a real root (you can also check if it returns NaN)
    double root = p1.getRoot(initialGuess, tolerance, maxIter);
    EXPECT_TRUE(std::isnan(root)); // or check the return value against a known condition for no real roots
}
TEST_F(PolynomialTest, Test62) {
    // Polynomial coefficients for: 2x^6 + 3x^5 + 4x^4 + 5x^3 + 6x^2 + 7x + 8
    Polynomial p1({ 8, 7, 6, 5, 4, 3, 2 });

    double initialGuess = 0.0; // Starting point for Newton's method
    double tolerance = 1e-6;    // Tolerance for convergence
    int maxIter = 100;          // Maximum iterations

    // Expect that getRoot does not return a real root (you can also check if it returns NaN)
    double root = p1.getRoot(initialGuess, tolerance, maxIter);
    EXPECT_TRUE(std::isnan(root)); // or check the return value against a known condition for no real roots
}
TEST_F(PolynomialTest, Test63) {
    Polynomial p1({ 5, 4, 6, 4, 1 });

    double initialGuess = 0.0; // Starting point for Newton's method
    double tolerance = 1e-6;    // Tolerance for convergence
    int maxIter = 100;          // Maximum iterations

    double root = p1.getRoot(initialGuess, tolerance, maxIter);
    EXPECT_TRUE(std::isnan(root)); // Expect no real roots
}
TEST_F(PolynomialTest, Test64) {
    Polynomial p1({ 8, 0, 1, 2, 0, 3 });

    double initialGuess = 0.0; // Starting point for Newton's method
    double tolerance = 1e-6;    // Tolerance for convergence
    int maxIter = 100;          // Maximum iterations

    double root = p1.getRoot(initialGuess, tolerance, maxIter);
    EXPECT_TRUE(root , -0.86382264 ); // Expect no real roots
}
TEST_F(PolynomialTest, Test65) {
    Polynomial p1({ 10, 5, 2, 1 });

    double initialGuess = 0.0; // Starting point for Newton's method
    double tolerance = 1e-6;    // Tolerance for convergence
    int maxIter = 100;          // Maximum iterations

    double root = p1.getRoot(initialGuess, tolerance, maxIter);
    EXPECT_TRUE(root ,-0.5); // Expect no real roots
}
/*converging properly to the expected roots. Here are a few considerations to determine whether the issue lies within the function or the parameters being used:
*/
TEST_F(PolynomialTest, Test66) {
    // Polynomial: x^4 + sqrt(2)x^3 + sqrt(3)x^2 + sqrt(5)x + sqrt(6)
    // This polynomial does not have any real roots.
    Polynomial poly1({ sqrt(6), sqrt(5), sqrt(3), sqrt(2), 1 }); // Represents x^4 + sqrt(2)x^3 + sqrt(3)x^2 + sqrt(5)x + sqrt(6)

    // Check that there are no real roots
    double initialGuess = 0.0; // Starting guess
    double tolerance = 1e-6;    // Tolerance for convergence
    int maxIter = 100;          // Maximum iterations

    // Since the polynomial is expected to have no real roots,
    // we can test that calling getRoot returns a value that is not a real root
    double root = poly1.getRoot(initialGuess, tolerance, maxIter);
    EXPECT_TRUE(isnan(root)); 

    // Additional checks for properties of the polynomial
    EXPECT_EQ(poly1.degree(), 4); // Check degree
    EXPECT_DOUBLE_EQ(poly1.evaluate(1), sqrt(6) + sqrt(5) + sqrt(3) + sqrt(2) + 1); // Evaluate at x=1

    // Test derivative
    Polynomial derivative = poly1.derivative();
    EXPECT_EQ(derivative.degree(), 3); // Check that derivative is degree 3
}
TEST_F(PolynomialTest, Test67) {
    // Polynomial: x^12 + sqrt(2)x^11 + sqrt(3)x^10 + sqrt(4)x^9 + sqrt(5)x^8 + 
    // sqrt(6)x^7 + sqrt(7)x^6 + sqrt(8)x^5 + sqrt(9)x^4 + sqrt(10)x^3 + 
    // sqrt(11)x^2 + sqrt(12)x + 1
    // This polynomial does not have any real roots.
    Polynomial poly1({ 1, sqrt(12), sqrt(11), sqrt(10), sqrt(9),
                        sqrt(8), sqrt(7), sqrt(6), sqrt(5),
                        sqrt(4), sqrt(3), sqrt(2), 1 }); // Represents x^12 + sqrt(2)x^11 + ... + 1
    double initialGuess = 1.0; // Starting guess
    double tolerance = 1e-6;    // Tolerance for convergence
    int maxIter = 100;          // Maximum iterations

    // Check that there are no real roots
    // Since the polynomial is expected to have no real roots,
    double root = poly1.getRoot(initialGuess, tolerance, maxIter);
    // we can test that calling getRoot returns a value that is not equal to the known real roots
     EXPECT_NEAR(root, -2.50562387, tolerance); // Check if it is not approximately equal to -2.50562387
    EXPECT_NEAR(root, -0.94087713, tolerance); // Check if it is not approximately equal to -0.94087713

    // Additional checks for properties of the polynomial
    EXPECT_EQ(poly1.degree(), 12); // Check degree
    EXPECT_DOUBLE_EQ(poly1.evaluate(1), 1 + sqrt(12) + sqrt(11) + sqrt(10) +
        sqrt(9) + sqrt(8) + sqrt(7) +
        sqrt(6) + sqrt(5) + sqrt(4) +
        sqrt(3) + sqrt(2) + 1); // Evaluate at x=1

    // Test derivative
    Polynomial derivative = poly1.derivative();
    EXPECT_EQ(derivative.degree(), 11); // Check that derivative is degree 11
}

TEST_F(PolynomialTest, Test68) {
    // Polynomial: P(x) = -71x^20 + 67x^19 + 61x^18 + 59x^17 - 53x^16 + 47x^15 - 43x^14 + 41x^13 - 37x^12 + 31x^11 - 29x^10 + 23x^9 - 19x^8 + 17x^7 - 13x^6 + 11x^5 - 7x^4 + 5x^3 - 3x^2 + 2x + 1
    Polynomial p1({ -71, 67, 61, 59, -53, 47, -43, 41, -37, 31, -29, 23, -19, 17, -13, 11, -7, 5, -3, 2, 1 });

    // Define initial guesses for the roots
    double guess1 = 1.5;   // Adjusted to be closer to the expected real root
    double guess2 = -0.2;  // Adjusted to be closer to the second expected real root
    double tolerance = 1e-7; // Tighter tolerance for convergence
    int maxIter = 100; // Maximum iterations

    // Get the roots using the getRoot method
    double root1 = p1.getRoot(guess1, tolerance, maxIter);
    double root2 = p1.getRoot(guess2, tolerance, maxIter);

    // Check if the roots are close to the expected values
    EXPECT_NEAR(root1, 1.65737085, tolerance);
    EXPECT_NEAR(root2, -0.28384746, tolerance);
}
TEST_F(PolynomialTest, Test69) {
    // Polynomial: P(x) = x^25 - 2x^24 + 3x^23 - 4x^22 + 5x^21 - 6x^20 + 7x^19 - 8x^18 + 9x^17 - 10x^16 + 11x^15 - 12x^14 + 13x^13 - 14x^12 + 15x^11 - 16x^10 + 17x^9 - 18x^8 + 19x^7 - 20x^6 + 21x^5 - 22x^4 + 23x^3 - 24x^2 + 25x - 26
    Polynomial p1({ -26, 25, -24, 23, -22, 21, -20, 19, -18, 17, -16, 15, -14, 13, -12, 11, -10, 9, -8, 7, -6, 5, -4, 3, -2, 1 });

    // Define initial guess for the real root
    double guess1 = 0.9;   // Adjusted to be closer to the expected real root
    double tolerance = 1e-7; // Tighter tolerance for convergence
    int maxIter = 100; // Maximum iterations

    // Get the root using the getRoot method
    double root1 = p1.getRoot(guess1, tolerance, maxIter);

    // Check if the root is close to the expected value
    EXPECT_NEAR(root1, 0.86072381, tolerance);
}
TEST_F(PolynomialTest, Test70) {
    // Polynomial: P(x) = -31x^30 + 30x^29 - 29x^28 + 28x^27 - 27x^26 + 26x^25 - 25x^24 + 24x^23 - 23x^22 + 22x^21 - 21x^20 + 20x^19 - 19x^18 + 18x^17 - 17x^16 + 16x^15 - 15x^14 + 14x^13 - 13x^12 + 12x^11 - 11x^10 + 10x^9 - 9x^8 + 8x^7 - 7x^6 + 6x^5 - 5x^4 + 4x^3 - 3x^2 + 2x - 1
    Polynomial p1({ -31, 30, -29, 28, -27, 26, -25, 24, -23, 22, -21, 20, -19, 18, -17, 16, -15, 14, -13, 12, -11, 10, -9, 8, -7, 6, -5, 4, -3, 2, -1, 0 });

    // Define initial guess for the root
    double guess1 = 0.0;   // Close to the expected real root
    double tolerance = 1e-7; // Tighter tolerance for convergence
    int maxIter = 100; // Maximum iterations

    // Get the root using the getRoot method
    double root1 = p1.getRoot(guess1, tolerance, maxIter);

    // Check if the root is close to the expected value
    EXPECT_NEAR(root1, 0.0, tolerance);
}

TEST_F(PolynomialTest, Test71) {
    Polynomial p1({ 0, -1, 2, -3, 4, -5, 6, -7, 8, -9, 10, -11, 12, -13, 14, -15, 16, -17, 18, -19, 20, -21, 22, -23, 24, -25, 26, -27, 28, -29, 30, -31, 32, -33, 34, -35, 36, -37, 38, -39, 40, -41, 42, -43, 44, -45, 46, -47, 48, -49, 50, -51 }
    );

    double initialGuess = 1.0; // Starting point for Newton's method
    double tolerance = 1e-6;    // Tolerance for convergence
    int maxIter = 100;          // Maximum iterations

    double root = p1.getRoot(initialGuess, tolerance, maxIter);
    EXPECT_TRUE(root,0); // Expect no real roots
}
TEST_F(PolynomialTest, Test72) {
    Polynomial p1({ 3.14, -1.59, 2.65, -3.58, 9.79, -2.65, 3.58, -9.79,
    2.71, -8.28, 4.67, -1.41, 5.12, -7.22, 0.58, -2.71,
    4.14, -1.61, 9.26, -5.35, 3.18, -2.73, 1.62, -4.56,
    7.98, -0.37, 1.05, -2.19, 6.28, -7.15, 9.62, -1.44,
    3.32, -8.23, 0.58, -9.21, 4.75, -5.81, 6.22, -3.83,
    7.45, -8.06, 1.91, -2.71, 2.45, -3.67, 4.85, -9.02,
    0.42, -6.39, 8.14, -5.67, 1.23, -4.35, 9.99, -2.56,
    7.84, -3.43, 0.76, -5.45, 6.72, -1.92, 3.74, -8.12,
    4.56, -9.11, 2.64, -7.23, 3.59, -1.85, 5.37, -4.29,
    8.11, -6.19, 1.78, -2.54, 9.83, -0.77, 4.12, -8.41,
    6.73, -3.65, 0.67, -5.83, 1.54, -2.33, 7.98, -4.12,
    5.49, -3.66, 0.88, -6.74, 9.25, -4.82, 1.19, -2.76,
    8.56, -7.35, 3.21, -5.90, 6.82, -0.49, 4.57, -2.99,
    1.32, -8.31, 7.20, -3.87, 0.53, -5.91, 2.69, -4.74,
    6.15, -1.23, 3.87, -9.77, 5.83, -2.44, 8.10, -6.22,
    4.56, -3.68, 0.77, -8.45, 9.01, -5.14, 2.72, -1.91,
    7.18, -0.43, 5.88, -3.29, 6.47, -2.91, 1.07, -4.90,
    0.44, -8.11, 9.29, -7.21, 2.78, -5.89, 3.58, -0.95,
    1.48, -4.13, 6.30, -3.64, 2.10, -7.53, 8.22, -1.60,
    5.49, -0.98, 3.92, -2.71, 9.80, -6.04, 1.74, -7.12,
    0.96, -4.86, 8.67, -3.50, 5.81, -1.19, 2.83, -9.28,
    4.99, -5.34, 3.73, -8.05, 7.14, -0.62, 6.77, -2.45,
    1.24, -5.86, 0.34, -4.27, 8.51, -6.85, 2.22, -3.48,
    9.99, -0.36, 5.77, -1.12, 3.10, -2.57, 6.22, -4.91,
    1.90, -7.99, 0.83, -8.40, 5.03, -9.49, 3.50, -6.78 ,22,3.14, -1.59, 2.65, -3.58, 9.79, -2.65, 3.58, -9.79,
    2.71, -8.28, 4.67, -1.41, 5.12, -7.22, 0.58, -2.71,
    4.14, -1.61, 9.26, -5.35, 3.18, -2.73, 1.62, -4.56,
    7.98, -0.37, 1.05, -2.19, 6.28, -7.15, 9.62, -1.44,
    3.32, -8.23, 0.58, -9.21, 4.75, -5.81, 6.22, -3.83,
    7.45, -8.06, 1.91, -2.71, 2.45, -3.67, 4.85, -9.02,
    0.42, -6.39, 8.14, -5.67, 1.23, -4.35, 9.99, -2.56,
    7.84, -3.43, 0.76, -5.45, 6.72, -1.92, 3.74, -8.12,
    4.56, -9.11, 2.64, -7.23, 3.59, -1.85, 5.37, -4.29,
    8.11, -6.19, 1.78, -2.54, 9.83, -0.77, 4.12, -8.41,
    6.73, -3.65, 0.67, -5.83, 1.54, -2.33, 7.98, -4.12,
    5.49, -3.66, 0.88, -6.74, 9.25, -4.82, 1.19, -2.76,
    8.56, -7.35, 3.21, -5.90, 6.82, -0.49, 4.57, -2.99,
    1.32, -8.31, 7.20, -3.87, 0.53, -5.91, 2.69, -4.74,
    6.15, -1.23, 3.87, -9.77, 5.83, -2.44, 8.10, -6.22,
    4.56, -3.68, 0.77, -8.45, 9.01, -5.14, 2.72, -1.91,
    7.18, -0.43, 5.88, -3.29, 6.47, -2.91, 1.07, -4.90,
    0.44, -8.11, 9.29, -7.21, 2.78, -5.89, 3.58, -0.95,
    1.48, -4.13, 6.30, -3.64, 2.10, -7.53, 8.22, -1.60,
    5.49, -0.98, 3.92, -2.71, 9.80, -6.04, 1.74, -7.12,
    0.96, -4.86, 8.67, -3.50, 5.81, -1.19, 2.83, -9.28,
    4.99, -5.34, 3.73, -8.05, 7.14, -0.62, 6.77, -2.45,
    1.24, -5.86, 0.34, -4.27, 8.51, -6.85, 2.22, -3.48,
    9.99, -0.36, 5.77, -1.12, 3.10, -2.57, 6.22, -4.91,
    1.90, -7.99, 0.83, -8.40, 5.03, -9.49, 3.50, -6.78 ,22,3.14, -1.59, 2.65, -3.58, 9.79, -2.65, 3.58, -9.79,
    2.71, -8.28, 4.67, -1.41, 5.12, -7.22, 0.58, -2.71,
    4.14, -1.61, 9.26, -5.35, 3.18, -2.73, 1.62, -4.56,
    7.98, -0.37, 1.05, -2.19, 6.28, -7.15, 9.62, -1.44,
    3.32, -8.23, 0.58, -9.21, 4.75, -5.81, 6.22, -3.83,
    7.45, -8.06, 1.91, -2.71, 2.45, -3.67, 4.85, -9.02,
    0.42, -6.39, 8.14, -5.67, 1.23, -4.35, 9.99, -2.56,
    7.84, -3.43, 0.76, -5.45, 6.72, -1.92, 3.74, -8.12,
    4.56, -9.11, 2.64, -7.23, 3.59, -1.85, 5.37, -4.29,
    8.11, -6.19, 1.78, -2.54, 9.83, -0.77, 4.12, -8.41,
    6.73, -3.65, 0.67, -5.83, 1.54, -2.33, 7.98, -4.12,
    5.49, -3.66, 0.88, -6.74, 9.25, -4.82, 1.19, -2.76,
    8.56, -7.35, 3.21, -5.90, 6.82, -0.49, 4.57, -2.99,
    1.32, -8.31, 7.20, -3.87, 0.53, -5.91, 2.69, -4.74,
    6.15, -1.23, 3.87, -9.77, 5.83, -2.44, 8.10, -6.22,
    4.56, -3.68, 0.77, -8.45, 9.01, -5.14, 2.72, -1.91,
    7.18, -0.43, 5.88, -3.29, 6.47, -2.91, 1.07, -4.90,
    0.44, -8.11, 9.29, -7.21, 2.78, -5.89, 3.58, -0.95,
    1.48, -4.13, 6.30, -3.64, 2.10, -7.53, 8.22, -1.60,
    5.49, -0.98, 3.92, -2.71, 9.80, -6.04, 1.74, -7.12,
    0.96, -4.86, 8.67, -3.50, 5.81, -1.19, 2.83, -9.28,
    4.99, -5.34, 3.73, -8.05, 7.14, -0.62, 6.77, -2.45,
    1.24, -5.86, 0.34, -4.27, 8.51, -6.85, 2.22, -3.48,
    9.99, -0.36, 5.77, -1.12, 3.10, -2.57, 6.22, -4.91,
    1.90, -7.99, 0.83, -8.40, 5.03, -9.49, 3.50, -6.78 ,22,3.14, -1.59, 2.65, -3.58, 9.79, -2.65, 3.58, -9.79,
    2.71, -8.28, 4.67, -1.41, 5.12, -7.22, 0.58, -2.71,
    4.14, -1.61, 9.26, -5.35, 3.18, -2.73, 1.62, -4.56,
    7.98, -0.37, 1.05, -2.19, 6.28, -7.15, 9.62, -1.44,
    3.32, -8.23, 0.58, -9.21, 4.75, -5.81, 6.22, -3.83,
    7.45, -8.06, 1.91, -2.71, 2.45, -3.67, 4.85, -9.02,
    0.42, -6.39, 8.14, -5.67, 1.23, -4.35, 9.99, -2.56,
    7.84, -3.43, 0.76, -5.45, 6.72, -1.92, 3.74, -8.12,
    4.56, -9.11, 2.64, -7.23, 3.59, -1.85, 5.37, -4.29,
    8.11, -6.19, 1.78, -2.54, 9.83, -0.77, 4.12, -8.41,
    6.73, -3.65, 0.67, -5.83, 1.54, -2.33, 7.98, -4.12,
    5.49, -3.66, 0.88, -6.74, 9.25, -4.82, 1.19, -2.76,
    8.56, -7.35, 3.21, -5.90, 6.82, -0.49, 4.57, -2.99,
    1.32, -8.31, 7.20, -3.87, 0.53, -5.91, 2.69, -4.74,
    6.15, -1.23, 3.87, -9.77, 5.83, -2.44, 8.10, -6.22,
    4.56, -3.68, 0.77, -8.45, 9.01, -5.14, 2.72, -1.91,
    7.18, -0.43, 5.88, -3.29, 6.47, -2.91, 1.07, -4.90,
    0.44, -8.11, 9.29, -7.21, 2.78, -5.89, 3.58, -0.95,
    1.48, -4.13, 6.30, -3.64, 2.10, -7.53, 8.22, -1.60,
    5.49, -0.98, 3.92, -2.71, 9.80, -6.04, 1.74, -7.12,
    0.96, -4.86, 8.67, -3.50, 5.81, -1.19, 2.83, -9.28,
    4.99, -5.34, 3.73, -8.05, 7.14, -0.62, 6.77, -2.45,
    1.24, -5.86, 0.34, -4.27, 8.51, -6.85, 2.22, -3.48,
    9.99, -0.36, 5.77, -1.12, 3.10, -2.57, 6.22, -4.91,
    1.90, -7.99, 0.83, -8.40, 5.03, -9.49, 3.50, -6.78 ,22,3.14, -1.59, 2.65, -3.58, 9.79, -2.65, 3.58, -9.79,
    2.71, -8.28, 4.67, -1.41, 5.12, -7.22, 0.58, -2.71,
    4.14, -1.61, 9.26, -5.35, 3.18, -2.73, 1.62, -4.56,
    7.98, -0.37, 1.05, -2.19, 6.28, -7.15, 9.62, -1.44,
    3.32, -8.23, 0.58, -9.21, 4.75, -5.81, 6.22, -3.83,
    7.45, -8.06, 1.91, -2.71, 2.45, -3.67, 4.85, -9.02,
    0.42, -6.39, 8.14, -5.67, 1.23, -4.35, 9.99, -2.56,
    7.84, -3.43, 0.76, -5.45, 6.72, -1.92, 3.74, -8.12,
    4.56, -9.11, 2.64, -7.23, 3.59, -1.85, 5.37, -4.29,
    8.11, -6.19, 1.78, -2.54, 9.83, -0.77, 4.12, -8.41,
    6.73, -3.65, 0.67, -5.83, 1.54, -2.33, 7.98, -4.12,
    5.49, -3.66, 0.88, -6.74, 9.25, -4.82, 1.19, -2.76,
    8.56, -7.35, 3.21, -5.90, 6.82, -0.49, 4.57, -2.99,
    1.32, -8.31, 7.20, -3.87, 0.53, -5.91, 2.69, -4.74,
    6.15, -1.23, 3.87, -9.77, 5.83, -2.44, 8.10, -6.22,
    4.56, -3.68, 0.77, -8.45, 9.01, -5.14, 2.72, -1.91,
    7.18, -0.43, 5.88, -3.29, 6.47, -2.91, 1.07, -4.90,
    0.44, -8.11, 9.29, -7.21, 2.78, -5.89, 3.58, -0.95,
    1.48, -4.13, 6.30, -3.64, 2.10, -7.53, 8.22, -1.60,
    5.49, -0.98, 3.92, -2.71, 9.80, -6.04, 1.74, -7.12,
    0.96, -4.86, 8.67, -3.50, 5.81, -1.19, 2.83, -9.28,
    4.99, -5.34, 3.73, -8.05, 7.14, -0.62, 6.77, -2.45,
    1.24, -5.86, 0.34, -4.27, 8.51, -6.85, 2.22, -3.48,
    9.99, -0.36, 5.77, -1.12, 3.10, -2.57, 6.22, -4.91,
    1.90, -7.99, 0.83, -8.40, 5.03 }
    );

    EXPECT_EQ(p1.degree(), 1000);
}
TEST_F(PolynomialTest, Test73) {
    Polynomial p1({0,1,sqrt(2) , sqrt(3) /2 , sqrt(5)/4 , 4 });

    double initialGuess = 1.0; // Starting point for Newton's method
    double tolerance = 1e-6;    // Tolerance for convergence
    int maxIter = 100;          // Maximum iterations

    double root = p1.getRoot(initialGuess, tolerance, maxIter);
    EXPECT_TRUE(isnan(root)); // Expect no real roots
}
TEST_F(PolynomialTest, Test74) {
    Polynomial p1({ 0,1,3 , sqrt(3) / 2 , sqrt(5) / 4 , 4 });

    double initialGuess = 1.0; // Starting point for Newton's method
    double tolerance = 1e-6;    // Tolerance for convergence
    int maxIter = 100;          // Maximum iterations

    double root = p1.getRoot(initialGuess, tolerance, maxIter);
    EXPECT_NEAR(root, -2.47909554 , tolerance);
    EXPECT_NEAR(root, -1.51010908 , tolerance);
}
TEST_F(PolynomialTest, Test75) {
    Polynomial p1({ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 });
    EXPECT_EQ(p1.integral(), Polynomial({ 0 , 1.0 / 1,1.0 / 2,1.0 / 3,1.0 / 4,1.0 / 5,1.0 / 6,1.0 / 7,1.0 / 8,1.0 / 9,1.0 / 10,1.0 / 11,1.0 / 12,1.0 / 13,1.0 / 14,1.0 / 15,1.0 / 16,1.0 / 17,1.0 / 18,1.0 / 19,1.0 / 20,1.0 / 21,1.0 / 22,1.0 / 23,1.0 / 24,1.0 / 25,1.0 / 26,1.0 / 27,1.0 / 28,1.0 / 29,1.0 / 30,1.0 / 31,1.0 / 32,1.0 / 33,1.0 / 34,1.0 / 35,1.0 / 36,1.0 / 37,1.0 / 38,1.0 / 39,1.0 / 40,1.0 / 41,1.0 / 42,1.0 / 43,1.0 / 44,1.0 / 45,1.0 / 46,1.0 / 47,1.0 / 48,1.0 / 49,1.0 / 50,1.0 / 51,1.0 / 52,1.0 / 53,1.0 / 54,1.0 / 55,1.0 / 56,1.0 / 57,1.0 / 58,1.0 / 59,1.0 / 60,1.0 / 61,1.0 / 62,1.0 / 63,1.0 / 64,1.0 / 65,1.0 / 66,1.0 / 67,1.0 / 68,1.0 / 69,1.0 / 70,1.0 / 71,1.0 / 72,1.0 / 73,1.0 / 74,1.0 / 75,1.0 / 76,1.0 / 77,1.0 / 78,1.0 / 79,1.0 / 80,1.0 / 81,1.0 / 82,1.0 / 83,1.0 / 84,1.0 / 85,1.0 / 86,1.0 / 87,1.0 / 88,1.0 / 89,1.0 / 90,1.0 / 91,1.0 / 92,1.0 / 93,1.0 / 94,1.0 / 95,1.0 / 96,1.0 / 97,1.0 / 98,1.0 / 99,1.0 / 100,1.0 / 101,1.0 / 102,1.0 / 103,1.0 / 104,1.0 / 105,1.0 / 106,1.0 / 107,1.0 / 108,1.0 / 109,1.0 / 110,1.0 / 111,1.0 / 112,1.0 / 113,1.0 / 114,1.0 / 115,1.0 / 116,1.0 / 117,1.0 / 118,1.0 / 119,1.0 / 120,1.0 / 121,1.0 / 122,1.0 / 123,1.0 / 124,1.0 / 125,1.0 / 126,1.0 / 127,1.0 / 128,1.0 / 129,1.0 / 130,1.0 / 131,1.0 / 132,1.0 / 133,1.0 / 134,1.0 / 135,1.0 / 136,1.0 / 137,1.0 / 138,1.0 / 139,1.0 / 140,1.0 / 141,1.0 / 142,1.0 / 143,1.0 / 144,1.0 / 145,1.0 / 146,1.0 / 147,1.0 / 148,1.0 / 149,1.0 / 150,1.0 / 151,1.0 / 152,1.0 / 153,1.0 / 154,1.0 / 155,1.0 / 156,1.0 / 157,1.0 / 158,1.0 / 159,1.0 / 160,1.0 / 161,1.0 / 162,1.0 / 163,1.0 / 164,1.0 / 165,1.0 / 166,1.0 / 167,1.0 / 168,1.0 / 169,1.0 / 170,1.0 / 171,1.0 / 172,1.0 / 173,1.0 / 174,1.0 / 175,1.0 / 176,1.0 / 177,1.0 / 178,1.0 / 179,1.0 / 180,1.0 / 181,1.0 / 182,1.0 / 183,1.0 / 184,1.0 / 185,1.0 / 186,1.0 / 187,1.0 / 188,1.0 / 189,1.0 / 190,1.0 / 191,1.0 / 192,1.0 / 193,1.0 / 194,1.0 / 195,1.0 / 196,1.0 / 197,1.0 / 198,1.0 / 199,1.0 / 200,1.0 / 201,1.0 / 202,1.0 / 203,1.0 / 204,1.0 / 205,1.0 / 206,1.0 / 207,1.0 / 208,1.0 / 209,1.0 / 210,1.0 / 211,1.0 / 212,1.0 / 213,1.0 / 214,1.0 / 215,1.0 / 216,1.0 / 217,1.0 / 218,1.0 / 219,1.0 / 220,1.0 / 221,1.0 / 222,1.0 / 223,1.0 / 224,1.0 / 225,1.0 / 226,1.0 / 227,1.0 / 228,1.0 / 229,1.0 / 230,1.0 / 231,1.0 / 232,1.0 / 233,1.0 / 234,1.0 / 235,1.0 / 236,1.0 / 237,1.0 / 238,1.0 / 239,1.0 / 240,1.0 / 241,1.0 / 242,1.0 / 243,1.0 / 244,1.0 / 245,1.0 / 246,1.0 / 247,1.0 / 248,1.0 / 249,1.0 / 250,1.0 / 251,1.0 / 252,1.0 / 253,1.0 / 254,1.0 / 255,1.0 / 256,1.0 / 257,1.0 / 258,1.0 / 259,1.0 / 260,1.0 / 261,1.0 / 262,1.0 / 263,1.0 / 264,1.0 / 265,1.0 / 266,1.0 / 267,1.0 / 268,1.0 / 269,1.0 / 270,1.0 / 271,1.0 / 272,1.0 / 273,1.0 / 274,1.0 / 275,1.0 / 276,1.0 / 277,1.0 / 278,1.0 / 279,1.0 / 280,1.0 / 281,1.0 / 282,1.0 / 283,1.0 / 284,1.0 / 285,1.0 / 286,1.0 / 287,1.0 / 288,1.0 / 289,1.0 / 290,1.0 / 291,1.0 / 292,1.0 / 293,1.0 / 294,1.0 / 295,1.0 / 296,1.0 / 297,1.0 / 298,1.0 / 299,1.0 / 300,1.0 / 301,1.0 / 302,1.0 / 303,1.0 / 304,1.0 / 305,1.0 / 306,1.0 / 307,1.0 / 308,1.0 / 309,1.0 / 310,1.0 / 311,1.0 / 312,1.0 / 313,1.0 / 314,1.0 / 315,1.0 / 316,1.0 / 317,1.0 / 318,1.0 / 319,1.0 / 320,1.0 / 321,1.0 / 322,1.0 / 323,1.0 / 324,1.0 / 325,1.0 / 326,1.0 / 327,1.0 / 328,1.0 / 329,1.0 / 330,1.0 / 331,1.0 / 332,1.0 / 333,1.0 / 334,1.0 / 335,1.0 / 336,1.0 / 337,1.0 / 338,1.0 / 339,1.0 / 340,1.0 / 341,1.0 / 342,1.0 / 343,1.0 / 344,1.0 / 345,1.0 / 346,1.0 / 347,1.0 / 348,1.0 / 349,1.0 / 350,1.0 / 351,1.0 / 352,1.0 / 353,1.0 / 354,1.0 / 355,1.0 / 356,1.0 / 357,1.0 / 358,1.0 / 359,1.0 / 360,1.0 / 361,1.0 / 362,1.0 / 363,1.0 / 364,1.0 / 365,1.0 / 366,1.0 / 367,1.0 / 368,1.0 / 369,1.0 / 370,1.0 / 371,1.0 / 372,1.0 / 373,1.0 / 374,1.0 / 375,1.0 / 376,1.0 / 377,1.0 / 378,1.0 / 379,1.0 / 380,1.0 / 381,1.0 / 382,1.0 / 383,1.0 / 384,1.0 / 385,1.0 / 386,1.0 / 387,1.0 / 388,1.0 / 389,1.0 / 390,1.0 / 391,1.0 / 392,1.0 / 393,1.0 / 394,1.0 / 395,1.0 / 396,1.0 / 397,1.0 / 398,1.0 / 399,1.0 / 400,1.0 / 401,1.0 / 402,1.0 / 403,1.0 / 404,1.0 / 405,1.0 / 406,1.0 / 407,1.0 / 408,1.0 / 409,1.0 / 410,1.0 / 411,1.0 / 412,1.0 / 413,1.0 / 414,1.0 / 415,1.0 / 416,1.0 / 417,1.0 / 418,1.0 / 419,1.0 / 420,1.0 / 421,1.0 / 422,1.0 / 423,1.0 / 424,1.0 / 425,1.0 / 426,1.0 / 427,1.0 / 428,1.0 / 429,1.0 / 430,1.0 / 431,1.0 / 432,1.0 / 433,1.0 / 434,1.0 / 435,1.0 / 436,1.0 / 437,1.0 / 438,1.0 / 439,1.0 / 440,1.0 / 441,1.0 / 442,1.0 / 443,1.0 / 444,1.0 / 445,1.0 / 446,1.0 / 447,1.0 / 448,1.0 / 449,1.0 / 450,1.0 / 451,1.0 / 452,1.0 / 453,1.0 / 454,1.0 / 455,1.0 / 456,1.0 / 457,1.0 / 458,1.0 / 459,1.0 / 460,1.0 / 461,1.0 / 462,1.0 / 463,1.0 / 464,1.0 / 465,1.0 / 466,1.0 / 467,1.0 / 468,1.0 / 469,1.0 / 470,1.0 / 471,1.0 / 472,1.0 / 473,1.0 / 474,1.0 / 475,1.0 / 476,1.0 / 477,1.0 / 478,1.0 / 479,1.0 / 480,1.0 / 481,1.0 / 482,1.0 / 483,1.0 / 484,1.0 / 485,1.0 / 486,1.0 / 487,1.0 / 488,1.0 / 489,1.0 / 490,1.0 / 491,1.0 / 492,1.0 / 493,1.0 / 494,1.0 / 495,1.0 / 496,1.0 / 497,1.0 / 498,1.0 / 499,1.0 / 500,1.0 / 501,1.0 / 502,1.0 / 503,1.0 / 504,1.0 / 505,1.0 / 506,1.0 / 507,1.0 / 508,1.0 / 509,1.0 / 510,1.0 / 511,1.0 / 512,1.0 / 513,1.0 / 514,1.0 / 515,1.0 / 516,1.0 / 517,1.0 / 518,1.0 / 519,1.0 / 520,1.0 / 521,1.0 / 522,1.0 / 523,1.0 / 524,1.0 / 525,1.0 / 526,1.0 / 527,1.0 / 528,1.0 / 529,1.0 / 530,1.0 / 531,1.0 / 532,1.0 / 533,1.0 / 534,1.0 / 535,1.0 / 536,1.0 / 537,1.0 / 538,1.0 / 539,1.0 / 540,1.0 / 541,1.0 / 542,1.0 / 543,1.0 / 544,1.0 / 545,1.0 / 546,1.0 / 547,1.0 / 548,1.0 / 549,1.0 / 550,1.0 / 551,1.0 / 552,1.0 / 553,1.0 / 554,1.0 / 555,1.0 / 556,1.0 / 557,1.0 / 558,1.0 / 559,1.0 / 560,1.0 / 561,1.0 / 562,1.0 / 563,1.0 / 564,1.0 / 565,1.0 / 566,1.0 / 567,1.0 / 568,1.0 / 569,1.0 / 570,1.0 / 571,1.0 / 572,1.0 / 573,1.0 / 574,1.0 / 575,1.0 / 576,1.0 / 577,1.0 / 578,1.0 / 579,1.0 / 580,1.0 / 581,1.0 / 582,1.0 / 583,1.0 / 584,1.0 / 585,1.0 / 586,1.0 / 587,1.0 / 588,1.0 / 589,1.0 / 590,1.0 / 591,1.0 / 592,1.0 / 593,1.0 / 594,1.0 / 595,1.0 / 596,1.0 / 597,1.0 / 598,1.0 / 599,1.0 / 600,1.0 / 601,1.0 / 602,1.0 / 603,1.0 / 604,1.0 / 605,1.0 / 606,1.0 / 607,1.0 / 608,1.0 / 609,1.0 / 610,1.0 / 611,1.0 / 612,1.0 / 613,1.0 / 614,1.0 / 615,1.0 / 616,1.0 / 617,1.0 / 618,1.0 / 619,1.0 / 620,1.0 / 621,1.0 / 622,1.0 / 623,1.0 / 624,1.0 / 625,1.0 / 626,1.0 / 627,1.0 / 628,1.0 / 629,1.0 / 630,1.0 / 631,1.0 / 632,1.0 / 633,1.0 / 634,1.0 / 635,1.0 / 636,1.0 / 637,1.0 / 638,1.0 / 639,1.0 / 640,1.0 / 641,1.0 / 642,1.0 / 643,1.0 / 644,1.0 / 645,1.0 / 646,1.0 / 647,1.0 / 648,1.0 / 649,1.0 / 650,1.0 / 651,1.0 / 652,1.0 / 653,1.0 / 654,1.0 / 655,1.0 / 656,1.0 / 657,1.0 / 658,1.0 / 659,1.0 / 660,1.0 / 661,1.0 / 662,1.0 / 663,1.0 / 664,1.0 / 665,1.0 / 666,1.0 / 667,1.0 / 668,1.0 / 669,1.0 / 670,1.0 / 671,1.0 / 672,1.0 / 673,1.0 / 674,1.0 / 675,1.0 / 676,1.0 / 677,1.0 / 678,1.0 / 679,1.0 / 680,1.0 / 681,1.0 / 682,1.0 / 683,1.0 / 684,1.0 / 685,1.0 / 686,1.0 / 687,1.0 / 688,1.0 / 689,1.0 / 690,1.0 / 691,1.0 / 692,1.0 / 693,1.0 / 694,1.0 / 695,1.0 / 696,1.0 / 697,1.0 / 698,1.0 / 699,1.0 / 700,1.0 / 701,1.0 / 702,1.0 / 703,1.0 / 704,1.0 / 705,1.0 / 706,1.0 / 707,1.0 / 708,1.0 / 709,1.0 / 710,1.0 / 711,1.0 / 712,1.0 / 713,1.0 / 714,1.0 / 715,1.0 / 716,1.0 / 717,1.0 / 718,1.0 / 719,1.0 / 720,1.0 / 721,1.0 / 722,1.0 / 723,1.0 / 724,1.0 / 725,1.0 / 726,1.0 / 727,1.0 / 728,1.0 / 729,1.0 / 730,1.0 / 731,1.0 / 732,1.0 / 733,1.0 / 734,1.0 / 735,1.0 / 736,1.0 / 737,1.0 / 738,1.0 / 739,1.0 / 740,1.0 / 741,1.0 / 742,1.0 / 743,1.0 / 744,1.0 / 745,1.0 / 746,1.0 / 747,1.0 / 748,1.0 / 749,1.0 / 750,1.0 / 751,1.0 / 752,1.0 / 753,1.0 / 754,1.0 / 755,1.0 / 756,1.0 / 757,1.0 / 758,1.0 / 759,1.0 / 760,1.0 / 761,1.0 / 762,1.0 / 763,1.0 / 764,1.0 / 765,1.0 / 766,1.0 / 767,1.0 / 768,1.0 / 769,1.0 / 770,1.0 / 771,1.0 / 772,1.0 / 773,1.0 / 774,1.0 / 775,1.0 / 776,1.0 / 777,1.0 / 778,1.0 / 779,1.0 / 780,1.0 / 781,1.0 / 782,1.0 / 783,1.0 / 784,1.0 / 785,1.0 / 786,1.0 / 787,1.0 / 788,1.0 / 789,1.0 / 790,1.0 / 791,1.0 / 792,1.0 / 793,1.0 / 794,1.0 / 795,1.0 / 796,1.0 / 797,1.0 / 798,1.0 / 799,1.0 / 800,1.0 / 801,1.0 / 802,1.0 / 803,1.0 / 804,1.0 / 805,1.0 / 806,1.0 / 807,1.0 / 808,1.0 / 809,1.0 / 810,1.0 / 811,1.0 / 812,1.0 / 813,1.0 / 814,1.0 / 815,1.0 / 816,1.0 / 817,1.0 / 818,1.0 / 819,1.0 / 820,1.0 / 821,1.0 / 822,1.0 / 823,1.0 / 824,1.0 / 825,1.0 / 826,1.0 / 827,1.0 / 828,1.0 / 829,1.0 / 830,1.0 / 831,1.0 / 832,1.0 / 833,1.0 / 834,1.0 / 835,1.0 / 836,1.0 / 837,1.0 / 838,1.0 / 839,1.0 / 840,1.0 / 841,1.0 / 842,1.0 / 843,1.0 / 844,1.0 / 845,1.0 / 846,1.0 / 847,1.0 / 848,1.0 / 849,1.0 / 850,1.0 / 851,1.0 / 852,1.0 / 853,1.0 / 854,1.0 / 855,1.0 / 856,1.0 / 857,1.0 / 858,1.0 / 859,1.0 / 860,1.0 / 861,1.0 / 862,1.0 / 863,1.0 / 864,1.0 / 865,1.0 / 866,1.0 / 867,1.0 / 868,1.0 / 869,1.0 / 870,1.0 / 871,1.0 / 872,1.0 / 873,1.0 / 874,1.0 / 875,1.0 / 876,1.0 / 877,1.0 / 878,1.0 / 879,1.0 / 880,1.0 / 881,1.0 / 882,1.0 / 883,1.0 / 884,1.0 / 885,1.0 / 886,1.0 / 887,1.0 / 888,1.0 / 889,1.0 / 890,1.0 / 891,1.0 / 892,1.0 / 893,1.0 / 894,1.0 / 895,1.0 / 896,1.0 / 897,1.0 / 898,1.0 / 899,1.0 / 900,1.0 / 901,1.0 / 902,1.0 / 903,1.0 / 904,1.0 / 905,1.0 / 906,1.0 / 907,1.0 / 908,1.0 / 909,1.0 / 910,1.0 / 911,1.0 / 912,1.0 / 913,1.0 / 914,1.0 / 915,1.0 / 916,1.0 / 917,1.0 / 918,1.0 / 919,1.0 / 920,1.0 / 921,1.0 / 922,1.0 / 923,1.0 / 924,1.0 / 925,1.0 / 926,1.0 / 927,1.0 / 928,1.0 / 929,1.0 / 930,1.0 / 931,1.0 / 932,1.0 / 933,1.0 / 934,1.0 / 935,1.0 / 936,1.0 / 937,1.0 / 938,1.0 / 939,1.0 / 940,1.0 / 941,1.0 / 942,1.0 / 943,1.0 / 944,1.0 / 945,1.0 / 946,1.0 / 947,1.0 / 948,1.0 / 949,1.0 / 950,1.0 / 951,1.0 / 952,1.0 / 953,1.0 / 954,1.0 / 955,1.0 / 956,1.0 / 957,1.0 / 958,1.0 / 959,1.0 / 960,1.0 / 961,1.0 / 962,1.0 / 963,1.0 / 964,1.0 / 965,1.0 / 966,1.0 / 967,1.0 / 968,1.0 / 969,1.0 / 970,1.0 / 971,1.0 / 972,1.0 / 973,1.0 / 974,1.0 / 975,1.0 / 976,1.0 / 977,1.0 / 978,1.0 / 979,1.0 / 980,1.0 / 981,1.0 / 982,1.0 / 983,1.0 / 984,1.0 / 985,1.0 / 986,1.0 / 987,1.0 / 988,1.0 / 989,1.0 / 990,1.0 / 991,1.0 / 992,1.0 / 993,1.0 / 994,1.0 / 995,1.0 / 996,1.0 / 997,1.0 / 998,1.0 / 999,1.0 / 1000,1.0 / 1001 }));

}
TEST_F(PolynomialTest, Test76) {
    Polynomial p1({ 0, 1 , 4, sqrt(2) });

    double tolerance = 1e-6;    // Tolerance for convergence
    int maxIter = 100;          // Maximum iterations

    // First root: starting point close to -0.39
    double initialGuess1 = 1.0;
    double root1 = p1.getRoot(initialGuess1, tolerance, maxIter);
    EXPECT_NEAR(root1, -0.39196193, tolerance);  // Check for root near -0.39

    // Second root: starting point close to -3.60
    double initialGuess2 = -4.0;
    double root2 = p1.getRoot(initialGuess2, tolerance, maxIter);
    EXPECT_NEAR(root2, -3.60803807, tolerance);  // Check for root near -3.60
}

TEST_F(PolynomialTest, Test77) {
    Polynomial p1({ 0, 1 , sqrt(2) });

    double initialGuess = 1.0; // Starting point for Newton's method
    double tolerance = 1e-6;    // Tolerance for convergence
    int maxIter = 100;          // Maximum iterations

    double root = p1.getRoot(initialGuess, tolerance, maxIter);
    EXPECT_NEAR(root, -1.41421356, tolerance);
 
}
TEST_F(PolynomialTest, Test78) {
    Polynomial p1({ 0,  0 ,0, 1,sqrt(2) });

    double initialGuess = 1.0; // Starting point for Newton's method
    double tolerance = 1e-6;    // Tolerance for convergence
    int maxIter = 100;          // Maximum iterations

    double root = p1.getRoot(initialGuess, tolerance, maxIter);
    EXPECT_NEAR(root, -1.41421356, tolerance);

}
TEST_F(PolynomialTest, Test79) {
    Polynomial p1({ sqrt(2) , sqrt(2) , sqrt(2) , sqrt(2) });

    double initialGuess = 1.0; // Starting point for Newton's method
    double tolerance = 1e-6;    // Tolerance for convergence
    int maxIter = 100;          // Maximum iterations

    double root = p1.getRoot(initialGuess, tolerance, maxIter);
    EXPECT_NEAR(root, -1.00000000e+00, tolerance);

}
TEST_F(PolynomialTest, Test80) {
    Polynomial p1({ 1,sqrt(2) , 3 , sqrt(4) , (5) });

    double initialGuess = 1.0; // Starting point for Newton's method
    double tolerance = 1e-6;    // Tolerance for convergence
    int maxIter = 100;          // Maximum iterations

    double root = p1.getRoot(initialGuess, tolerance, maxIter);
    EXPECT_TRUE(isnan(root));

}
TEST_F(PolynomialTest, Test81) {
    Polynomial p1({ 5, -7, 13, 10, 2, 15, -8, -3, -14, -4, 10 });

    double tolerance = 1e-6;    // Tolerance for convergence
    int maxIter = 100;          // Maximum iterations

    // First root: Use an initial guess near -0.79
    double initialGuess1 = 1.0;
    double root1 = p1.getRoot(initialGuess1, tolerance, maxIter);
    EXPECT_NEAR(root1, -0.79058165, tolerance);

    // Second root: Use a different initial guess near -1.04
    double initialGuess2 = -2.0;
    double root2 = p1.getRoot(initialGuess2, tolerance, maxIter);
    EXPECT_NEAR(root2, -1.04797069, tolerance);
}

TEST_F(PolynomialTest, Test82) {
    Polynomial p1({ -7 ,13, -8, 8 });

    double initialGuess = 1.0; // Starting point for Newton's method
    double tolerance = 1e-6;    // Tolerance for convergence
    int maxIter = 100;          // Maximum iterations

    double root = p1.getRoot(initialGuess, tolerance, maxIter);
    EXPECT_NEAR(root, 1.59038197, tolerance);
 

}
TEST_F(PolynomialTest, Test83) {
    Polynomial p1({ -13, -8, 15, 6, 7, -11, -4, -6, -14, 1 });

    double tolerance = 1e-6;    // Tolerance for convergence
    int maxIter = 100;          // Maximum iterations

    // First root: Use an initial guess near -0.86
    double initialGuess1 = 1.0;
    double root1 = p1.getRoot(initialGuess1, tolerance, maxIter);
    EXPECT_NEAR(root1, -0.85992705, tolerance); // Check first root

    // Second root: Use a different initial guess near 0.07
    double initialGuess2 = 0.5;
    double root2 = p1.getRoot(initialGuess2, tolerance, maxIter);
    EXPECT_NEAR(root2, 0.06926055, tolerance);  // Check second root
}

TEST_F(PolynomialTest, Test84) {
    Polynomial p1({ 1, 6, -6, -9, -7, -6 });

    double tolerance = 1e-6;    // Tolerance for convergence
    int maxIter = 100;          // Maximum iterations

    // First root: Use an initial guess near -6.71
    double initialGuess1 = -7.0;
    double root1 = p1.getRoot(initialGuess1, tolerance, maxIter);
    EXPECT_NEAR(root1, -6.71416292, tolerance); // Check first root

    // Second root: Use a different initial guess near 1.81
    double initialGuess2 = 2.0;
    double root2 = p1.getRoot(initialGuess2, tolerance, maxIter);
    EXPECT_NEAR(root2, 1.80907437, tolerance);  // Check second root

    // Third root: Use a different initial guess near -0.86
    double initialGuess3 = 0.0;
    double root3 = p1.getRoot(initialGuess3, tolerance, maxIter);
    EXPECT_NEAR(root3, -0.86048584, tolerance);  // Check third root
}

TEST_F(PolynomialTest, Test85) {
    Polynomial p1({ -5, -4, -11, -5, 13, 6, 0, -8, 8 });

    double tolerance = 1e-6;    // Tolerance for convergence
    int maxIter = 100;          // Maximum iterations

    // First root: Use an initial guess near -1.25
    double initialGuess1 = 1.0;
    double root1 = p1.getRoot(initialGuess1, tolerance, maxIter);
    EXPECT_NEAR(root1, -1.25405831, tolerance); // Check first root

    // Second root: Use a different initial guess near 0.92
    double initialGuess2 = 0.5;
    double root2 = p1.getRoot(initialGuess2, tolerance, maxIter);
    EXPECT_NEAR(root2, 0.91737553, tolerance);  // Check second root
}

TEST_F(PolynomialTest, Test86) {
    Polynomial p1({ 6 ,-12 , 9 , 8 , -7 , 11 , 15 , -13 , 7 , -14 , 11 , 2 });

    double initialGuess = 1.0; // Starting point for Newton's method
    double tolerance = 1e-6;    // Tolerance for convergence
    int maxIter = 100;          // Maximum iterations

    double root = p1.getRoot(initialGuess, tolerance, maxIter);
    EXPECT_NEAR(root, -0.15023882, tolerance);
   
}
TEST_F(PolynomialTest, Test87) {
    Polynomial p1({ 6, -12, 9, 8, -7, 11, 15, -13, 7, -14, 11, 2 });

    double tolerance = 1e-6; // Tolerance for convergence
    int maxIter = 100;       // Maximum iterations

    // Test for the first root
    double initialGuess1 = 1.0;
    double expectedRoot1 = 0.27271081;
    double root1 = p1.getRoot(initialGuess1, tolerance, maxIter);
    EXPECT_NEAR(root1, expectedRoot1, tolerance);

    // Test for the second root
    double initialGuess2 = -1.0;
    double expectedRoot2 = -0.77265566;
    double root2 = p1.getRoot(initialGuess2, tolerance, maxIter);
    EXPECT_NEAR(root2, expectedRoot2, tolerance);
}

TEST_F(PolynomialTest, Test88) {
    Polynomial p1({ 5,  8, 2, 0, 10, 10, 12, 10, 11, 12, -11 });

    double tolerance = 1e-6; // Tolerance for convergence
    int maxIter = 100;       // Maximum iterations

    // Test for the first root
    double initialGuess1 = 1.0;
    double expectedRoot1 = -1.18719435;
    double root1 = p1.getRoot(initialGuess1, tolerance, maxIter);
    EXPECT_NEAR(root1, expectedRoot1, tolerance);

    // Test for the second root
    double initialGuess2 = 0.5; // You might need to adjust this guess based on the expected root
    double expectedRoot2 = 0.49405972;
    double root2 = p1.getRoot(initialGuess2, tolerance, maxIter);
    EXPECT_NEAR(root2, expectedRoot2, tolerance);
}

TEST_F(PolynomialTest, Test89) {
    Polynomial p1({ -12 , 4 , 5 , 8 , -14 , 13 ,  -12 , 12 , 10 , 8 });

    double initialGuess = 1.0; // Starting point for Newton's method
    double tolerance = 1e-6;    // Tolerance for convergence
    int maxIter = 100;          // Maximum iterations

    double root = p1.getRoot(initialGuess, tolerance, maxIter);
    EXPECT_NEAR(root, 1.22634169, tolerance);
}
TEST_F(PolynomialTest, Test90) {
    Polynomial p1({ 1, 15, 0, 6, 15, -13, 5, -2, 12, -2, 4 });

    double tolerance = 1e-6; // Tolerance for convergence
    int maxIter = 100;       // Maximum iterations

    // Test for the first root
    double initialGuess1 = -15.0;
    double expectedRoot1 = -15.02190185;
    double root1 = p1.getRoot(initialGuess1, tolerance, maxIter);
    EXPECT_NEAR(root1, expectedRoot1, tolerance);

    // Test for the second root
    double initialGuess2 = -1.0; // Adjust this guess based on where you expect the second root
    double expectedRoot2 = -1.26757023;
    double root2 = p1.getRoot(initialGuess2, tolerance, maxIter);
    EXPECT_NEAR(root2, expectedRoot2, tolerance);
}

TEST_F(PolynomialTest, Test91) {
    Polynomial p1({ -1, -8, -3, -9, 0, 0, 8, 0, -6, 15 });

    double tolerance = 1e-6; // Tolerance for convergence
    int maxIter = 100;       // Maximum iterations

    // Test for the first root
    double initialGuess1 = 1.0;
    double expectedRoot1 = -7.76317497;
    double root1 = p1.getRoot(initialGuess1, tolerance, maxIter);
    EXPECT_NEAR(root1, expectedRoot1, tolerance);

    // Test for the second root
    double initialGuess2 = -1.0; // Adjust this guess based on where you expect the second root
    double expectedRoot2 = -1.0;
    double root2 = p1.getRoot(initialGuess2, tolerance, maxIter);
    EXPECT_NEAR(root2, expectedRoot2, tolerance);

    // Test for the third root
    double initialGuess3 = 1.0; // Adjust this guess based on where you expect the third root
    double expectedRoot3 = 0.96550363;
    double root3 = p1.getRoot(initialGuess3, tolerance, maxIter);
    EXPECT_NEAR(root3, expectedRoot3, tolerance);
}

TEST_F(PolynomialTest, Test92) {
    Polynomial p1({ 8, 2, -6, 1, -10, 9, 3, 13, -5, -2, 6 });

    double tolerance = 1e-6; // Tolerance for convergence
    int maxIter = 100;       // Maximum iterations

    // Test for the first root
    double initialGuess1 = 1.0;
    double expectedRoot1 = -1.49960077;
    double root1 = p1.getRoot(initialGuess1, tolerance, maxIter);
    EXPECT_NEAR(root1, expectedRoot1, tolerance);

    // Test for the second root
    double initialGuess2 = 0.0; // Adjust this guess based on where you expect the second root
    double expectedRoot2 = -0.65517255;
    double root2 = p1.getRoot(initialGuess2, tolerance, maxIter);
    EXPECT_NEAR(root2, expectedRoot2, tolerance);
}

TEST_F(PolynomialTest, Test93) {
    Polynomial p1({ -6 , 11 , -2 , 7 , 12 , 2 , 3 , -12 , -11 , 9, 4, 6 });

    double initialGuess = 1.0; // Starting point for Newton's method
    double tolerance = 1e-6;    // Tolerance for convergence
    int maxIter = 100;          // Maximum iterations

    double root = p1.getRoot(initialGuess, tolerance, maxIter);
    EXPECT_NEAR(root, 2.1388204, tolerance);
}
TEST_F(PolynomialTest, Test94) {
    Polynomial p1({ -3 , -4 , -5 , -11 , -4 , -7 , -3 , 5 , -8 , -6 , 6 , -2 });

    double initialGuess =- 1.0; // Starting point for Newton's method
    double tolerance = 1e-6;    // Tolerance for convergence
    int maxIter = 100;          // Maximum iterations

    double root = p1.getRoot(initialGuess, tolerance, maxIter);
    EXPECT_NEAR(root, -1.56738018, tolerance);
}
TEST_F(PolynomialTest, Test95) {
    Polynomial p1({ 11 , 8 ,-5 ,-10 });

    double initialGuess = 1.0; // Starting point for Newton's method
    double tolerance = 1e-6;    // Tolerance for convergence
    int maxIter = 100;          // Maximum iterations

    double root = p1.getRoot(initialGuess, tolerance, maxIter);
    EXPECT_NEAR(root, 0.90002768, tolerance);
}
TEST_F(PolynomialTest, Test96) {
    Polynomial p1({ 9 ,-6 , 13 , -2 , 1 , 9 , -8 , 13 , 14 , 4 , 7 , 1 });

    double initialGuess = 1.0; // Starting point for Newton's method
    double tolerance = 1e-6;    // Tolerance for convergence
    int maxIter = 100;          // Maximum iterations

    double root = p1.getRoot(initialGuess, tolerance, maxIter);
    EXPECT_NEAR(root, -0.15000588, tolerance);
}
TEST_F(PolynomialTest, Test97) {
    Polynomial p1({ -7 ,15, -7 ,-3 ,-5, 13, 10, -14, -14, -5 });

    double initialGuess = 1.0; // Starting point for Newton's method
    double tolerance = 1e-6;    // Tolerance for convergence
    int maxIter = 100;          // Maximum iterations

    double root = p1.getRoot(initialGuess, tolerance, maxIter);
    EXPECT_NEAR(root, -0.70764823, tolerance);
}
TEST_F(PolynomialTest, Test98) {
    Polynomial p1({ 5, -14, -14, -6, -6, -14, 12, -4, -8, 12 });

    double tolerance = 1e-6; // Tolerance for convergence
    int maxIter = 100;       // Maximum iterations

    // Test for the first root
    double initialGuess1 = 1.0;
    double expectedRoot1 = 3.68442743;
    double root1 = p1.getRoot(initialGuess1, tolerance, maxIter);
    EXPECT_NEAR(root1, expectedRoot1, tolerance);

    // Test for the second root
    double initialGuess2 = -1.0; // Adjust this guess based on where you expect the second root
    double expectedRoot2 = -0.86557888;
    double root2 = p1.getRoot(initialGuess2, tolerance, maxIter);
    EXPECT_NEAR(root2, expectedRoot2, tolerance);

    // Test for the third root
    double initialGuess3 = 0.5; // Adjust this guess based on where you expect the third root
    double expectedRoot3 = 0.73331757;
    double root3 = p1.getRoot(initialGuess3, tolerance, maxIter);
    EXPECT_NEAR(root3, expectedRoot3, tolerance);
}

TEST_F(PolynomialTest, Test99) {
    Polynomial p1({ 3, 1, -8 });

    double tolerance = 1e-6; // Tolerance for convergence
    int maxIter = 100;       // Maximum iterations

    // Test for the first root
    double initialGuess1 = -1.0;
    double expectedRoot1 = -1.80814297;
    double root1 = p1.getRoot(initialGuess1, tolerance, maxIter);
    EXPECT_NEAR(root1, expectedRoot1, tolerance);

    // Test for the second root
    double initialGuess2 = 2.0; // Adjust this guess based on where you expect the second root
    double expectedRoot2 = 1.47480963;
    double root2 = p1.getRoot(initialGuess2, tolerance, maxIter);
    EXPECT_NEAR(root2, expectedRoot2, tolerance);
}

TEST_F(PolynomialTest, Test100) {
    Polynomial p1({ -3 , 2 , -11 , 5 , -13 , -14 , -11 , 5 });

    double initialGuess = 0.5; // Starting point for Newton's method
    double tolerance = 1e-6;    // Tolerance for convergence
    int maxIter = 100;          // Maximum iterations
 
    double root = p1.getRoot(initialGuess, tolerance, maxIter);
    EXPECT_NEAR(root, 0.30451905, tolerance);

}
