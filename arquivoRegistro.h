#ifndef ARQUIVOREGISTRO_H_INCLUDED
#define ARQUIVOREGISTRO_H_INCLUDED


#include <fstream>
#include <string>
#include <cstring>
#include "registro.h"
#include "Cabecalho.h"
#include "Seriazable.h"
#include <iostream>
using namespace std;

template <class T>
class ArqRegistro : protected fstream{
    static_assert(std::is_base_of<Serializable, T>::value, "T deve ser subclasse de Serializable");
public:
    Cabecalho cab;
    ArqRegistro();
    ArqRegistro(const string nome, const string t, int ver, ios::openmode mode = ios::in | ios:: out | ios::binary);
    //no arquivo mandado faltou o int ver
    bool abrir(const string nome, const string t, int ver, ios::openmode mode = ios::in | ios:: out | ios::binary);
    bool fechar();
    bool lerRegistro(unsigned long int i, Registro<T> &r);
    bool excluirRegistro(unsigned long int i);
    bool inserirRegistro(Registro<T> r);
    bool escreverRegistro(unsigned long int i, Registro<T> r);
    unsigned long int primeiroValido() const;
    unsigned long int primeiroExcluido() const;
    bool aberto();
    virtual ~ArqRegistro();
    bool escreverCabecalho();
protected:

    bool lerCabecalho(); //char para string

    bool verificarTipo(string tip);
    bool verificarVersao(int v);
    unsigned long int calcularPos(unsigned long int i);
};

template <class T>
ArqRegistro<T>::~ArqRegistro()
{
    fechar();
}
template <class T>
ArqRegistro<T>::ArqRegistro()
{
    fstream();
}
template <class T>
ArqRegistro<T>::ArqRegistro(const string nome, const string t, int ver, ios::openmode mode)
{
    abrir(nome,t,ver, mode);

}

template <class T>
bool ArqRegistro<T>::verificarTipo(string t){
    bool tipo=false;
     if(t == cab.tipoArquivo()){
        tipo = true;
     }
     return tipo;
}

template <class T>
bool ArqRegistro<T>::verificarVersao(int v){
    bool arq=false;
     if(v == cab.versao()){
        arq = true;
     }
     return arq;
}

template <class T>
bool ArqRegistro<T>::fechar(){
    close();
    return(good());
}

template <class T>
unsigned long int ArqRegistro<T>::primeiroValido() const{
    return cab.primeiroValido();
}

template <class T>
unsigned long int ArqRegistro<T>::primeiroExcluido() const{
    return cab.primeiroExcluido();
}

template <class T>
bool ArqRegistro<T>::aberto()
{

    return is_open();
}

template <class T>
bool ArqRegistro<T>::abrir(const string nome, const string t, int ver, ios::openmode mode)
{
    if(!aberto())
    {
        open(nome, mode);
        if(aberto())
        {
            if(!(lerCabecalho() && verificarTipo(t) && verificarVersao(ver)))
            {
                cout << "Cabecalho diferente do esperado !" << endl;
                return(fechar());
            }
        }
        else
        {
            Cabecalho c(t,ver);
            cab = c;
            open(nome.c_str(), ios::in | ios:: out | ios::binary | ios::trunc);
            return escreverCabecalho();
        }
    }
    return false;
}

template <class T>
bool ArqRegistro<T>::lerCabecalho()
{
    seekg(0);
    char* cb = new char[31];//cb de cabecalho pra auxiliar
    read(cb, 31);
    cab.fromString(string(cb,31));

    return good();
}

template <class T>
bool ArqRegistro<T>::escreverCabecalho(){
	seekp(0);
	write((const char*) cab.toString().c_str(), 31);
	return good();
}



template <class T>
bool ArqRegistro<T>::escreverRegistro(unsigned long int i, Registro<T> r)
{
    seekp(calcularPos(i));
	write((const char*) r.toString().c_str(), 148);
	return good();
}


template <class T>
bool ArqRegistro<T>::inserirRegistro(Registro<T> r)
{

    r.proximo(cab.primeiroValido()); //novo registro passa a ser o primeiro valido
    int n;
    if (cab.primeiroExcluido() != 0) //se houver algum registro excluido faça...
    {
        n = primeiroExcluido();
        Registro<T> res;
        if(lerRegistro(primeiroExcluido(), res))
        {
            cab.primeiroExcluido(res.proximo());
        }
    }
    else
    {
        seekg(0, ios_base::end);
        int tam = tellg();
        n = ((tam - 31)/148) + 1;
    }

    r.proximo(primeiroValido());
    cab.primeiroValido(n);
    escreverCabecalho();
    escreverRegistro(n, r);
    return good();
}


template <class T>
unsigned long int ArqRegistro<T>::calcularPos(unsigned long int i)
{
    return 31 + ((i-1)*148);
}


template <class T>
bool ArqRegistro<T>::lerRegistro(unsigned long int i, Registro<T> &r){
    if ( i > 0 ){
     seekg(calcularPos(i));
	char* caux = new char[148];
    read(caux, 148);
    r.fromString(string(caux,148));


    } else {

    cout << "Erro!!!" << endl;
    }

    return good();
}


template <class T>
bool ArqRegistro<T>::excluirRegistro(unsigned long int i)
{
    Registro <T> ant;//anterior
    Registro<T> alvo;
    lerRegistro(i, alvo);
    if(i == primeiroValido()){

        cab.primeiroValido(alvo.proximo());
    } else {
        lerRegistro(primeiroValido(),ant);
        while(ant.proximo() != i ){

            lerRegistro(ant.proximo() ,ant);

        }
        ant.proximo(alvo.proximo());
    }
    alvo.proximo(primeiroExcluido());
    alvo.excluir();
    cab.primeiroExcluido(i);
    escreverCabecalho();
    escreverRegistro(i, alvo);
    return good();
}

#endif // ARQUIVOREGISTRO_H_INCLUDED
