#ifndef OPERADORA_FRAC_H_INCLUDED
#define OPERADORA_FRAC_H_INCLUDED

#include <iostream>
#include "Seriazable.h"

using namespace std;

class OperaTADFRAC : public Serializable{

public:
    double resultado()const;
    void resultado(double r);
    int numerador()const;
    void numerador(int n);
    int denominador()const;
    void denominador(int d);
    OperaTADFRAC();
    OperaTADFRAC(int n,int d);
    OperaTADFRAC(const OperaTADFRAC &o);
    OperaTADFRAC operator +(const OperaTADFRAC &f);
    OperaTADFRAC operator -(const OperaTADFRAC &f);
    OperaTADFRAC operator *(const OperaTADFRAC &f);
    OperaTADFRAC operator /(const OperaTADFRAC &f);
    bool operator == (const OperaTADFRAC &c);
    bool operator < (const OperaTADFRAC &c);
    bool operator > (const OperaTADFRAC &c);
    bool operator >= (const OperaTADFRAC &c);
    bool operator <= (const OperaTADFRAC &c);
    OperaTADFRAC operator = (const OperaTADFRAC &c);
    friend ostream& operator << (ostream& o,OperaTADFRAC &c);
    int mdc(int n,int d);
    int mmc(int d1,int d2);
    void simplifies(int n,int d);
    string toString();
    void fromString(string repr);


private:
    double result;
    int numerator;
    int denominator;

};

#endif // OPERADORA_FRAC_H_INCLUDED
