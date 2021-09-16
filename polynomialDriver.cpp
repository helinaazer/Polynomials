#include <iostream>
using namespace std;

#include "polynomial.h"

int main() {
	Polynomial p1;
	p1.changeCoefficient(-1, 1);
	p1.changeCoefficient(4, 4);
	p1.changeCoefficient(2.2, 2);
	p1.changeCoefficient(-3.8, 3);
  p1.changeCoefficient(2, -1); //this will not print out anything because we are assuming there are no negative powers.
	cout << "p1 = " << p1 << endl;
	cout << "The coefficient of p1 at degree 3 is: " << p1.coefficient(3) << endl;
  cout << "The coefficient of p1 at degree 1 is: " <<p1.coefficient(1) <<endl;
  cout << "The coefficient of p1 at degree 5 is: " <<p1.coefficient(5) <<endl;
  cout << "The degree of p1 is: " << p1.degree() << endl;
	p1.changeCoefficient(0, 4);
  p1.changeCoefficient(1,0);
	cout << "p1 = " << p1 << endl;
	Polynomial p2 = p1;
	p2.changeCoefficient(-3, 6);
	cout << "p2 = " << p2 << endl;
	string str = "";
	bool x = (p1 == p1);
	if (x)
		str = "True";
	else
		str = "False";
	cout << "p1 == p1 is " << str << endl;
	x = (p1 == p2);
	if (x)
		str = "True";
	else
		str = "False";
	cout << "p1 == p2 is " << str << endl;
  x = (p1 != p2);
	if (x)
		str = "True";
	else
		str = "False";
	cout << "p1 != p2 is " << str << endl;
  x = (p2 != p2);
	if (x)
		str = "True";
	else
		str = "False";
	cout << "p2 != p2 is " << str << endl;
  p1 = p2;
  cout << "p1 = " << p1 <<endl;
  cout << "p2 = " << p2 << endl;
  x = (p1 == p2);
	if (x)
		str = "True";
	else
		str = "False";
	cout << "p1 == p2 is " << str << endl;
	Polynomial p3 = p1;
  p3.changeCoefficient(5, 6);
  p3.changeCoefficient(7,8);
  p3.changeCoefficient(-2,4);
	cout << "p3 = " << p3 << endl;
	cout << "p1 + p2 is " << p1 + p2 << endl;
	cout << "p1 - p2 is " << p1 - p2 << endl;
  cout << "p3 - p2 is " << p3 - p2 << endl;
  cout << "The degree of p3 is " << p3.degree() << endl;
	cout << "p1 + p2 = " << (p1 += p2) << endl;
	cout << "p1 is now: " << p1 << endl;;
	cout << "p2 - p1 = " << (p2 -= p1) << endl;
	cout << "p2 is now: " << p2 << endl;
  cout << "The coefficient of p2 at degree 6 is: " <<p2.coefficient(6) <<endl;
}