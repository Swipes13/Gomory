#ifndef DIGIT_H_
#define DIGIT_H_

#include <string>
using std::string;

namespace math {
  enum DigitType {
    DT_Definite,
    DT_Undefenite,
    DT_Infinity
  };

  class Digit {
  public:
    static string intToString(int value);
    Digit(int numerator, int denominator);
    Digit(int numerator);
    Digit(const Digit&);
    Digit();
    ~Digit();
    double toDouble();
    string toString();
    bool integer();
    Digit& getInteger();
    Digit& left();
    Digit& absD();
    DigitType digitType();

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
    bool operator<=(const Digit&);
    bool operator<=(const int&);
    bool operator>=(const Digit&);
    bool operator>=(const int&);
    bool operator<(const Digit&);
    bool operator<(const int&);
    bool operator>(const Digit&);
    bool operator>(const int&);
    bool operator==(const Digit&);
    bool operator==(const int&);
    bool operator!=(const Digit&);
    bool operator!=(const int&);
  private:

    DigitType _digitType;
    int _numerator;
    int _denominator;

    void _reduce();
  };

}
#endif
