#include "OPERADORA_FRAC.h"
#include <iostream>

int OperaTADFRAC::numerador()const {

return numerator;

}
void OperaTADFRAC::numerador(int n){

numerator = n;

}

double OperaTADFRAC::resultado()const{

return result;

}

void OperaTADFRAC::resultado(double r){

result = r;

}

int OperaTADFRAC::denominador() const{

return denominator;

}
void OperaTADFRAC::denominador(int d){

denominator = d;

}
OperaTADFRAC::OperaTADFRAC(){

numerador(0);
denominador(1);
resultado((0/(double)1));

}

OperaTADFRAC::OperaTADFRAC(int n, int d){

simplifies(n,d);
resultado((n/(double)d));

}
OperaTADFRAC::OperaTADFRAC(const OperaTADFRAC &o){

numerador(o.numerador());
denominador(o.denominador());
resultado((o.numerador()/(double)o.denominador()));

}

int OperaTADFRAC::mdc(int n,int d){
int mdc;
int j;
j = d;
        if(n > d){
            j = n;
}

    for(int i = 1; i < j;i++){
        if(n%i == 0 && d%i == 0){
            mdc = i;
}
}
return mdc;
}


int OperaTADFRAC::mmc(int d1,int d2){
int mdc;
int j;

if(d1 == d2)
    return d1;
if(d1 > d2){

j = d1;

}else{

j = d2;
}

for(int i = 1; i < j;i++){
if(d1%i == 0 && d2%i == 0){
    mdc = i;
}

}
//DEF:sejam a e b dois naturais validos, temos que MMC(a,b) = (a.b)/MDC
return (d1*d2)/mdc;

}
void OperaTADFRAC::simplifies(int n,int d){

    if ((n%d) == 0){
        numerador(n/d);
        denominador(1);
    }else{
        if ((d%n) == 0){
            denominador(d/n);
            numerador(1);
        }else{

        numerador(n/mdc(n,d));
        denominador(d/mdc(n,d));
}
}
}


OperaTADFRAC OperaTADFRAC::operator +(const OperaTADFRAC &f){

OperaTADFRAC fra;

if(f.denominador() == denominador()){

    fra.denominador(f.denominador());
    fra.numerador((f.numerador() + numerador()));

}else{
    fra.denominador(mmc(f.denominador(),denominador()));
    fra.numerador(f.numerador() + numerador());

}

return fra;
}

OperaTADFRAC OperaTADFRAC::operator -(const OperaTADFRAC &f){

OperaTADFRAC fra;

if(f.denominador() == denominador()){

    fra.denominador(f.denominador());
    fra.numerador((numerador() - f.numerador()));

}else{
    fra.denominador(mmc(f.denominador(),denominador()));
    fra.numerador(numerador() - f.numerador());

}

return fra;
}

OperaTADFRAC OperaTADFRAC::operator *(const OperaTADFRAC &f){

OperaTADFRAC fra;

fra.numerador(numerador()*f.numerador());
fra.denominador(denominador()*f.denominador());

return fra;

}


OperaTADFRAC OperaTADFRAC::operator /(const OperaTADFRAC &f){

OperaTADFRAC fra;

fra.numerador(numerador()*f.denominador());
fra.denominador(denominador()*f.numerador());

return fra;

}

OperaTADFRAC OperaTADFRAC::operator =(const OperaTADFRAC &o){

OperaTADFRAC aux(o);
numerador(o.numerador());
denominador(o.denominador());
return aux;

}

bool OperaTADFRAC::operator ==(const OperaTADFRAC &o){

return (numerador() == o.numerador() && denominador() == o.denominador());

}

bool OperaTADFRAC::operator <(const OperaTADFRAC &o){

return (resultado() < o.resultado());

}

bool OperaTADFRAC::operator >(const OperaTADFRAC &o){

return (resultado() > o.resultado());

}

ostream& operator <<(ostream& saida,OperaTADFRAC &o){

cout << "Fracao: " << o.numerador() << "/" << o.denominador() << "   Resultado: " << o.resultado() ;
    return saida;

}


bool OperaTADFRAC::operator<=(const OperaTADFRAC &o){
    return (resultado()< o.resultado() || numerador()== o.numerador() && denominador() == o.denominador());
}

bool OperaTADFRAC ::operator>=(const OperaTADFRAC &o){
    return (resultado() > o.resultado() || o.numerador() && denominador() == o.denominador());
}


string OperaTADFRAC::toString(){

int numAux = numerador();
int denAux = denominador();
double resulAux = resultado();

string nume = string(reinterpret_cast<char*>(&numAux), sizeof(int));
string deno = string(reinterpret_cast<char*>(&denAux), sizeof(int));
string resu = string(reinterpret_cast<char*>(&resulAux), sizeof(double));

string palavra = (nume + deno + resu);

return palavra;

}

void OperaTADFRAC::fromString(string repr){

char numAux[sizeof(int)];
repr.copy(numAux,sizeof(int),0);

char denAux[sizeof(int)];
repr.copy(denAux,sizeof(int),4);

char resulAux[sizeof(double)];
repr.copy(resulAux,sizeof(double),8);

numerator = *reinterpret_cast<int*>(&numAux);

denominator = *reinterpret_cast<int*>(&denAux);
result = *reinterpret_cast<double*>(&resulAux);
}

