#include "polynomial.h"
//I am assuming that there are no negative powers. Any time the coefficient is 0, nothing returns. Also, any time there is a 0 power, I return the coefficient with no variable or power(Ex: 1x^0 returns 1). Any time there is a 1 power, I just return x without the power 1. These are all done to make the output look clean!

//-------------------Constructor----------------
Polynomial::Polynomial() {
  head = new Term;
  head->prev = head;
  head->next = head;
  size = 0;
  head->coeff = 0;
  head->power = -1;
}

//----------------Copy constructor---------------
Polynomial::Polynomial(const Polynomial& p) {
  head = new Term;
  head->prev = head;
  head->next = head;
  size = 0;
  head->coeff = 0;
  head->power = -1;
  Term* increment = p.head->next;
  while (increment != p.head) {
    this->changeCoefficient(increment->coeff, increment->power);
    increment = increment->next;
  }
  *this = p;
}

//-------------------Destructor-------------------
Polynomial::~Polynomial() {
  Term* increment = head->next;
  while (increment != head) {
    increment = increment->next;
    remove(increment->prev);
  }
  delete head;
}

//Returns the degree of a polynomial
//precondition: none (non existant degree returns 0)
//postcondition: largest degree in the polynomial is returned as an integer
int Polynomial::degree() const {
  if (head->next == head) {
    return 0;
  } else {
    return head->next->power;
  }
}

//Returns the coefficient of the x^power term
//precondition: none
//postcondition: coefficient, if x^power term doesn't exist, then it returns 0. If it exists, then return the coefficient.
double Polynomial::coefficient(const int power) const {
  Term* increment = head->next;
  while (increment->power != power) {
    if (increment == head) {
      return 0;
    }
    increment = increment->next;
  }
  return increment->coeff;
}

//Replaces the coefficient of the x^power term with newCoeffcient
//precondition: none
//postcondition: if the x^power term with the given coefficient doesn't exist, then insert that new term. If the x^power term with the given coefficient exists, then change the coefficient to the newCoefficient.
bool Polynomial::changeCoefficient(const double newCoefficient, const int power) {
  Term* increment = head->next;
  while (increment->power > power) {
    increment = increment->next;
  }
  if (increment->power == power) {
    if (newCoefficient == 0)
      remove(increment);
    else
      increment->coeff = newCoefficient;
  } else {
    if (!insert(increment, newCoefficient, power)) {
      return false;
    }
  }
  return true;
}

//-------------------------Arithmetic Operators--------------------

//Overloaded + operator that adds two polynomials.
//Returns the simplified polynomial after adding two polynomials.
Polynomial Polynomial::operator+(const Polynomial& p) const {
  int largest = 0;
  Polynomial returnValue = *this;
  if (this->head->next->power >= p.head->next->power)
    largest = this->head->next->power;
  else
    largest = p.head->next->power;
  for (int i = largest; i >= 0; i--) {
    returnValue.changeCoefficient(this->coefficient(i) + p.coefficient(i), i);
  }
  return returnValue;
}

//Overloaded - operator that subtracts two polynomials.
//Returns the simplified polynomial after suubtracting two polynomials.
Polynomial Polynomial::operator-(const Polynomial& p) const {
  int largest = 0;
  Polynomial returnValue = *this;
  if (this->head->next->power >= p.head->next->power)
    largest = this->head->next->power;
  else
    largest = p.head->next->power;
  for (int i = largest; i >= 0; i--) {
    returnValue.changeCoefficient(this->coefficient(i) - p.coefficient(i), i);
  }
  return returnValue;
}

//---------------Boolean Comparison Operators----------------

//overloaded == operator that checks whether two polynomials are the same or not
//return true if the polynomials are the same. Returns false if the polynomials are different.
bool Polynomial::operator==(const Polynomial& p) const {
  if (this == &p) return true;
  if (this->size != p.size) return false;
  Term* increment1 = this->head->next;
  Term* increment2 = p.head->next;
  while (increment1 != head && increment2 != p.head) {
    if (increment1->coeff != increment2->coeff || increment1->power != increment2->power) {
      return false;
    }
    increment1 = increment1->next;
    increment2 = increment2->next;
  }
  return true;
}

//overloaded != operator that checks whether two polynomials are the differemt or not
//return true if the polynomials are different. Returns false if the polynomials are the same.
bool Polynomial::operator!=(const Polynomial& p) const {
  return !(*this == p);
}

//---------------------Assignment Operators-----------

//Sets this polynomal the same as the parameter(another polynomial) 
//Return value is reference to this polynomial.
Polynomial& Polynomial::operator=(const Polynomial& p) {
  if (*this == p) return *this;
  this->clear();
  Term* increment = p.head->next;
  while (increment != p.head) {
    this->changeCoefficient(increment->coeff, increment->power);
    increment = increment->next;
  }
  return *this;
}

//terms of p are added to the terms of this polynomial. The result is stored back in this polynomial.
//Return value is reference to this polynomial.
Polynomial& Polynomial::operator+=(const Polynomial& p) {
  *this = *this + p;
  return *this;
}

//terms of p are subtracted from the terms of this polynomial. The result is stored back in this polynomial.
//Return value is reference to this polynomial.
Polynomial& Polynomial::operator-=(const Polynomial& p) {
  *this = *this - p;
  return *this;
}

//inserts a new Term node with newCoefficient and power before the existing Term pointed by the pos pointer
//precondition: a non zero newCoeffcient is passes through the function as well as a pos term that exists in the polynomial. 
//postcondition: returns true if new Term was inserted. Returns false if the preconditions are not met.
bool Polynomial::insert(Term* pos, const double newCoefficient, const int power) {
  if (pos == NULL) {
    return false;
  }
  if (newCoefficient == 0) {
    return true;
  }
  Term* increment = head;
  Term* implement = new Term;
  implement->coeff = newCoefficient;
  implement->power = power;
  while (increment->next != pos) {
    increment = increment->next;
  }
  implement->next = pos;
  implement->prev = increment;
  increment->next = implement;
  pos->prev = implement;
  size++;
  return true;
}

//deletes the existing Term node pointed by the pos pointer
//precondition: position(pos) term exists in the polynomial
//postcondition: returns true if pos term was removed
bool Polynomial::remove(Term* pos) {
  pos->prev->next = pos->next;
  pos->next->prev = pos->prev;
  delete pos;
  size--;
  return true;
}

//overloaded output operator that prints out the polynomial in the form c_nx^n + c_n-1x^n-1 + c_n-2x^n-2 + ...+ c_0
ostream& operator<<(ostream& output, const Polynomial& p) {
  Term* increment = p.head->next;
  if (increment == p.head) {
    output << 0;
  }
  while (increment != p.head) {
    if (increment->coeff > 0) {
      if (increment->prev == p.head)
        output << increment->coeff;
      else
        output << " + " << increment->coeff;
    } else if (increment->coeff < 0) {
      if (increment->prev == p.head)
        output << increment->coeff;
      else
        output << " - " << -1 * increment->coeff;
    }
    if (increment->power != 0)
      output << "x";
    if (increment->power > 1)
      output << "^" << increment->power;
    increment = increment->next;
  }
  return output;
}
 
//Removes/clears all terms of the polynomial from the memory
void Polynomial::clear() {
  while (head->next != head) {
    remove(head->next);
  }
}
