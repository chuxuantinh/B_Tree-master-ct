#ifndef REGISTRO_H_INCLUDED
#define REGISTRO_H_INCLUDED


#include "Seriazable.h"
#include <iostream>

template <class T>
class Registro : public Serializable
{
private:
    T dados;
    unsigned long int prox;
    bool apagado;
public:
    Registro();
    Registro(T i); //o T vai ser o objeto a passar
    Registro(const Registro<T> &r);
    Registro<T> operator = (const Registro<T> &r);
    bool operator == (const Registro<T> &r);
    T info() const;
    void info (T i);
    unsigned long int proximo() const;
    void proximo(unsigned long int p);
    bool excluido() const;
    void excluido(bool b);
    void excluir();
    string toString();
    void fromString(string repr);
    /* string toCSV(){}
      string toXML(){}
      string toJSON(){}
      void fromCSV(string repr);
      void fromXML(string repr);
      void fromJSON(string repr);*/
      //a implementacao dos itens acima comentados n deu certo
};

template <class T>
string Registro<T>::toString(){

unsigned long int pAux = proximo();
bool apag = apagado;

string pAux2 = string(reinterpret_cast<char*>(&pAux), sizeof(unsigned long int));
string apag2 = string(reinterpret_cast<char*>(&apag), sizeof(bool));
string palavra = (pAux2 + apag2 + dados.toString());

return palavra;

}

template <class T>
void Registro<T>::fromString(string repr){
char iprox[sizeof(unsigned long int)];
repr.copy(iprox,sizeof(unsigned long int),0);

char apag[sizeof(bool)];
repr.copy(apag,sizeof(bool),8);

char idados[137];
repr.copy(idados,137,9);

prox = *reinterpret_cast<unsigned long int*>(&iprox);
apagado = *reinterpret_cast<bool*>(&apag);
dados.fromString(string(idados, 137));
}

template <class T>
void Registro<T>::excluir()
{
    apagado = true;
}

template <class T>
Registro<T>::Registro()
{
    dados = T();
    prox = 0;
    apagado = false;
}

template <class T>
Registro<T>::Registro(const Registro<T> &r)
{
    info(r.info());
    proximo(r.proximo());
    excluido(r.excluido());
}//Registro<OperaTADFRAC> reg;Registro<OperaTADFRAC> reg;

template <class T>
void Registro<T>::info(T i){
    dados = i;
}

template <class T>
T Registro<T>::info()const{
    return dados;
}

template <class T>
void Registro<T>::excluido(bool b){
    apagado = b;
}

template <class T>
bool Registro<T>::excluido()const{
    return apagado;
}

template <class T>
void Registro<T>::proximo(unsigned long int p){
    prox = p;
}

template <class T>
unsigned long int Registro<T>::proximo()const{
    return prox;
}

template <class T>
Registro<T> Registro<T>::operator = (const Registro<T> &r)
{
    Registro res(r);
    info(r.info());
    proximo(r.proximo());
    excluido(r.excluido());

    return res;
}

template <class T>
bool Registro<T>::operator == (const Registro<T> &r)
{
    return (info() == r.info() && proximo() == r.proximo() && excluido() == r.excluido());
}

template <class T>
ostream& operator <<(ostream& saida,Registro<T> &a){
cout << "Registro" << "\tExcluido: " << a.excluido() << "\tProximo: " << a.proximo() << endl;
int x;
cout << "\tChaves" << endl;
cout << "\n\tNumChaves: " << a.info().num_keys << endl;
for( x = 0; x < a.info().Num_Chaves(); x++){
    cout << "\tChave = [" << x <<"]: " << a.info().keys[x] << endl;
}
cout << "\tFolha: " << a.info().eFolha() << endl;
cout << "\tFilhos" << endl;
for(x = 0; x < a.info().Num_Filhos(); x++){
    cout << a.info().regFolhas[x] << endl;
}
    return saida;

}


#endif // REGISTRO_H_INCLUDED
