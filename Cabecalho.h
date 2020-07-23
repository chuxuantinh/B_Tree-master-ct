#ifndef CABECALHO_H_INCLUDED
#define CABECALHO_H_INCLUDED
#include <string>
#include "Seriazable.h"
using namespace std;

class Cabecalho: public Serializable{
public:
    Cabecalho(); //ok
    Cabecalho(const  string t, const int v); //ok
    Cabecalho(const Cabecalho &c); //ok
    bool operator == (const Cabecalho &c); //ok
    Cabecalho operator = (const Cabecalho &c); //ok
    unsigned long int primeiroExcluido() const; //ok
    unsigned long int primeiroValido() const; //ok
    void primeiroValido(unsigned long int i); //ok
    void primeiroExcluido(unsigned long int i); //ok
    string tipoArquivo() const; //ok
    void tipoArquivo(string t); //ok
    int versao() const; //ok
    void versao(int v); //ok
    string toString();//ok
    void fromString(string repr);//ok
    unsigned long int raiz;
    /* string toCSV(){}
      string toXML(){}
      string toJSON(){}
      virtual void fromString(string repr);
      virtual void fromCSV(string repr){}
      virtual void fromXML(string repr){}
      virtual void fromJSON(string repr){}
      virtual unsigned int size();*/
protected:
    string tipo;
    int ver;

    unsigned long int primExcluido;
    unsigned long int primValido;
};



#endif // CABECALHO_H_INCLUDED
