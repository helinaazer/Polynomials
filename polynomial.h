// A Polynomial class
//I am assuming that there are no negative powers. Any time the coefficient is 0, nothing returns. Also, any time there is a 0 power, I return the coefficient with no variable or power(Ex: 1x^0 returns 1). Any time there is a 1 power, I just return x without the power 1. These are all done to make the output look clean!
#ifndef POLYNOMIAL_H                                  
#define POLYNOMIAL_H
#include <iostream>
#include <string>
using namespace std;


struct Term {     // a term on the sparse polynomial
    double coeff;   // the coefficient of each term
    int power;      // the degree of each term
    struct Term* prev;     // a pointer to the previous higher term
    struct Term* next;     // a pointer to the next lower term
};

class Polynomial {
    // Overloaded <<: prints Cn * x^n + Cn-1 * X^n-1 + ... C1 * X + C0
    friend ostream& operator<<(ostream& output, const Polynomial& p);
    // Constructor: the default is a 0-degree polynomial with 0.0 coefficient
public:
    // Member functions
    Polynomial(); //default constructor
    Polynomial(const Polynomial& p); //copy constructor
    ~Polynomial(); //destructor
    int degree() const; // returns the degree of a polynomial
    double coefficient(const int power) const; // returns the coefficient of the x^power term. If x^power term doesn't exist, then it returns 0. If it exists, then return the coefficient.
    bool changeCoefficient(const double newCoefficient, const int power); // replaces the coefficient of the x^power term. 

    // Arithmetic operators
    Polynomial operator+(const Polynomial& p) const; //Overloaded + operator that adds two polynomials. Returns the simplified polynomial after adding two polynomials.
    Polynomial operator-(const Polynomial& p) const; //Overloaded - operator that subtracts two polynomials. Returns the simplified polynomial after subtracting two polynomials.

    // Boolean comparison operators
    bool operator==(const Polynomial& p) const; //overloaded == operator that checks whether two polynomials are the same or not
    bool operator!=(const Polynomial& p) const; //overloaded != operator that checks whether two polynomials are the differemt or not

    // Assignment operators
    Polynomial& operator=(const Polynomial& p); //Sets this polynomal the same as the parameter(another polynomial)
    Polynomial& operator+=(const Polynomial& p); //terms of p are added to the terms of this polynomial. The result is stored back in this polynomial.
    Polynomial& operator-=(const Polynomial& p); //terms of p are subtracted from the terms of this polynomial. The result is stored back in this polynomial.
private:

    int size;         // # terms in the sparse polynomial
    double* coeff; //makes coeff an array
    Term* head;       // a pointer to the doubly-linked circular list of sparse polynomial

    bool insert(Term* pos, const double newCoefficient, const int power); //inserts a new Term node with newCoefficient and power before the existing Term pointed by the pos pointer
    bool remove(Term* pos); //deletes the existing Term node pointed by the pos pointer
    void clear(); //Removes/clears all terms of the polynomial from the memory

};

#endif
