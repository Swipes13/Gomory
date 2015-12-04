#include "Digit.h"

using namespace math;
#define MAX_INT_COUNT 25

Digit::Digit(int numerator, int denominator) :_numerator(numerator), _denominator(denominator) {
  _reduce();
}

Digit::Digit(int numerator) : _numerator(numerator), _denominator(1) {}

Digit::Digit() : _numerator(0), _denominator(1) {}

Digit::Digit(const Digit& d) {
  _numerator = d._numerator;
  _denominator = d._denominator;
  _reduce();
}

Digit::~Digit() {}

double Digit::toDouble() {
  return static_cast<double>(_numerator) / static_cast<double>(_denominator);
}

string Digit::toString() {
  return _intToString(_numerator) + "/" + _intToString(_denominator);
}

string Digit::_intToString(int value) {
  char* buf = new char[MAX_INT_COUNT];
  _itoa_s(value, buf, MAX_INT_COUNT, 10);
  string ret = string(buf);
  delete buf;
  return ret;
}

DigitType Digit::digitType(){
  return _digitType;
}

void Digit::_reduce() {
  if(this->_denominator < 0) {
    _numerator = -_numerator;
    _denominator = -_denominator;
  }

  if (_denominator == 0){
    if (_numerator == 0)
      _digitType = DT_Undefenite;
    else
      _digitType = DT_Infinity;
  }
  else
    _digitType = DT_Definite;

  if (_digitType != DT_Definite)
    return;

  static int simple [] = {2,3,5,7,11,13,17,19,23,29,
    31,37,41,43,47,53,59,61,67,71,
    73,79,83,89,97,101,103,107,109,113,
    127,131,137,139,149,151,157};

  for(int i = 36; i >=0; i--) {
    int ost = _numerator % simple[i];
    while(ost == 0) {
      int ost2 = _denominator % simple[i];
      if(ost2 == 0) {
        _numerator /= simple[i];
        _denominator /= simple[i];
        ost = _numerator % simple[i];
      }
      else break;
    }
  }
}

Digit& Digit::operator*(const Digit &digit) {
  Digit* ret = new Digit(_numerator, _denominator);
  ret->_numerator *= digit._numerator;
  ret->_denominator *= digit._denominator;
  ret->_reduce();
  return *ret;
}

Digit& Digit::operator*(const int &value) {
  Digit* ret = new Digit(_numerator, _denominator);
  ret->_numerator *= value;
  ret->_reduce();
  return *ret;
}

Digit& Digit::operator*=(const Digit &digit) {
  _numerator *= digit._numerator;
  _denominator *= digit._denominator;
  _reduce();
  return *this;
}

Digit& Digit::operator*=(const int &value) {
  _numerator *= value;
  _reduce();
  return *this;
}

Digit& Digit::operator/(const Digit &digit) {
  Digit* ret = new Digit(_numerator, _denominator);
  ret->_numerator *= digit._denominator;
  ret->_denominator *= digit._numerator;
  ret->_reduce();
  return *ret;
}

Digit& Digit::operator/(const int &value) {
  Digit* ret = new Digit(_numerator, _denominator);
  ret->_denominator *= value;
  ret->_reduce();
  return *ret;
}

Digit& Digit::operator/=(const Digit &digit) {
  _numerator *= digit._denominator;
  _denominator *= digit._numerator;
  _reduce();
  return *this;
}

Digit& Digit::operator/=(const int &value) {
  _denominator *= value;
  _reduce();
  return *this;
}

bool Digit::operator==(const Digit &digit) {
  if(digit._numerator == this->_numerator && digit._denominator == this->_denominator)
    return true;
  return false;
}

bool Digit::operator==(const int &value) {
  if(value == this->_numerator && this->_denominator == 1)
    return true;
  return false;
}

bool Digit::operator!=(const Digit &digit) {
  return !(*this == digit);
}

bool Digit::operator!=(const int &value) {
  return !(*this == value);
}

Digit& Digit::operator=(const Digit &digit) {
  _numerator = digit._numerator;
  _denominator = digit._denominator;
  Digit* ret = new Digit(_numerator, _denominator);
  return *ret;
}

Digit& Digit::operator=(const int &value) {
  Digit* ret = new Digit(value);
  return *ret;
}

Digit& Digit::operator+(const Digit &digit) {
  Digit* ret = new Digit(_numerator*digit._denominator + digit._numerator*_denominator, _denominator*digit._denominator);
  ret->_reduce();
  return *ret;
}

Digit& Digit::operator+(const int &value) {
  Digit* ret = new Digit(_numerator + value*_denominator, _denominator);
  ret->_reduce();
  return *ret;
}

Digit& Digit::operator+=(const Digit &digit) {
  _numerator = _numerator*digit._denominator + digit._numerator*_denominator;
  _denominator = _denominator*digit._denominator;
  _reduce();
  return *this;
}

Digit& Digit::operator+=(const int &value) {
  _numerator = _numerator + value*_denominator;
  _denominator = _denominator;
  _reduce();
  return *this;
}

Digit& Digit::operator-(const Digit &digit) {
  Digit* ret = new Digit(_numerator*digit._denominator - digit._numerator*_denominator, _denominator*digit._denominator);
  ret->_reduce();
  return *ret;
}

Digit& Digit::operator-() {
  Digit* ret = new Digit(-_numerator, _denominator);
  ret->_reduce();
  return *ret;
}

Digit& Digit::operator-(const int &value) {
  Digit* ret = new Digit(_numerator - value*_denominator, _denominator);
  ret->_reduce();
  return *ret;
}

Digit& Digit::operator-=(const Digit& digit) {
  _numerator = _numerator*digit._denominator - digit._numerator*_denominator;
  _denominator = _denominator*digit._denominator;
  _reduce();
  return *this;
}

Digit& Digit::operator-=(const int &value) {
  _numerator = _numerator - value*_denominator;
  _denominator = _denominator;
  _reduce();
  return *this;
}

bool Digit::operator<(const Digit& b){
  Digit a = Digit(*this);
  Digit b_ = Digit(b);
  a._numerator = _numerator*b._denominator;
  a._denominator = _denominator*b._denominator;
  b_._numerator = b._numerator*_denominator;
  b_._denominator = b._denominator *_denominator;

  if (a._numerator < b_._numerator)
    return true;
  return false;
}

bool Digit::operator<=(const Digit& b){
  Digit a = Digit(*this);
  Digit b_ = Digit(b);
  a._numerator = _numerator*b._denominator;
  a._denominator = _denominator*b._denominator;
  b_._numerator = b._numerator*_denominator;
  b_._denominator = b._denominator *_denominator;

  if (a._numerator <= b_._numerator)
    return true;
  return false;
}

bool Digit::operator<=(const int& value){
  if (_numerator <= value*_denominator)
    return true;
  return false;
}

bool Digit::operator<(const int& value){
  if (_numerator < value*_denominator)
    return true;
  return false;
}

bool Digit::operator>(const Digit& b){
  if (*this <= b)
    return false;
  return true;
}

bool Digit::operator>(const int& value){
  if (*this <= value)
    return false;
  return true;
}

bool Digit::integer(){
  _reduce();
  if (_denominator != 1)
    return false;
  return true;
}

Digit& Digit::left(){
  if (_digitType != DT_Definite)
    return *(new Digit(0, 0));

  return *(new Digit(_numerator % _denominator, _denominator));
}

Digit& Digit::absD(){
  _reduce();
  return *(new Digit(abs(_numerator), _denominator));
}