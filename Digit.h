#ifndef DIGIT_H_
#define DIGIT_H_

#include <string>
using std::string;

namespace math {
  
  class Digit {
  public:
    Digit(int numerator, int denominator);
    Digit(int numerator);
    Digit(const Digit&);
    Digit();
    ~Digit();
    double toDouble();
    string toString();

    Digit& operator/(const Digit&);
    Digit& operator/(const int&);
    Digit& operator/=(const Digit&);
    Digit& operator/=(const int&);
    Digit& operator*(const Digit&);
    Digit& operator*(const int&);
    Digit& operator*=(const Digit&);
    Digit& operator*=(const int&);
    Digit& operator+(const Digit&);
    Digit& operator+(const int&);
    Digit& operator+=(const Digit&);
    Digit& operator+=(const int&);
    Digit& operator-(const Digit&);
    Digit& operator-();
    Digit& operator-(const int&);
    Digit& operator-=(const Digit&);
    Digit& operator-=(const int&);
    Digit& operator=(const Digit&);
    Digit& operator=(const int &);
    bool operator==(const Digit&);
    bool operator==(const int&);
    bool operator!=(const Digit&);
    bool operator!=(const int&);
  private:

    int _numerator;
    int _denominator;

    string _intToString(int value);
    void _reduce();
  };

}
#endif
