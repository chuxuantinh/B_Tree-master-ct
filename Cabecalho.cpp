#include "Cabecalho.h"
#include <string.h>
#include <iostream>

using namespace std;

Cabecalho::Cabecalho()
{
    tipo = "alf";
    ver = 1;
    primExcluido = 0;
    primValido = 0;
    raiz = 0;
}

Cabecalho::Cabecalho(const  string t, const int v)
{
char aux[3];
    for(int i = 0;i < 3;i++){
    aux[i] = t[i];
    }
    tipo = aux;
    ver = v;
    primExcluido = 0;
    primValido = 0;
}

Cabecalho::Cabecalho(const Cabecalho &c)
{
    tipoArquivo(c.tipoArquivo());
    versao(c.versao());
    primeiroExcluido(c.primeiroExcluido());
    primeiroValido(c.primeiroValido());
}

void Cabecalho::tipoArquivo(string t)
{
    tipo = t;
}

string Cabecalho::tipoArquivo() const
{
    return tipo;
}

void Cabecalho::versao(int v)
{
    ver = v;
}

int Cabecalho::versao() const
{
    return ver;
}

void Cabecalho::primeiroExcluido(unsigned long int i)
{
    primExcluido = i;
}

unsigned long int Cabecalho::primeiroExcluido() const
{
    return primExcluido;
}

void Cabecalho::primeiroValido(unsigned long int i)
{
    primValido = i;
}

unsigned long int Cabecalho::primeiroValido() const
{
    return primValido;
}

bool Cabecalho:: operator == (const Cabecalho &c)
{
    return (tipoArquivo() == c.tipoArquivo() && versao() == c.versao() && primExcluido == c.primeiroExcluido() && primValido == c.primeiroValido());
}

Cabecalho Cabecalho:: operator = (const Cabecalho &c) // agora um objeto do tipo cabecalho pode atribuir outro.
{

    Cabecalho aux(c);
    tipoArquivo(c.tipoArquivo());
    versao(c.versao());
    primeiroExcluido(c.primeiroExcluido());
    primeiroValido(c.primeiroValido());

    return aux;

}

string Cabecalho::toString()
{

int verAux = versao();
unsigned long int  peAux= primeiroExcluido();
unsigned long int  pvAux= primeiroValido();
unsigned long int raizAux = raiz;
string tipoAux = tipoArquivo();

string verr = string(reinterpret_cast<char*>(&verAux), sizeof(int));
string pee = string(reinterpret_cast<char*>(&peAux), sizeof(unsigned long int));
string pvv = string(reinterpret_cast<char*>(&pvAux), sizeof(unsigned long int));
string raizAuxString = string(reinterpret_cast<char*>(&raizAux), sizeof(unsigned long int));

string palavra = (tipoAux + verr + pee + pvv + raizAuxString);
    return palavra;
};

void Cabecalho::fromString(string repr)
{
        char tipoAux[3];
		repr.copy(tipoAux,3,0);
		string tipooo = string(tipoAux,3);

		char verAux[sizeof(int)];
		repr.copy(verAux, sizeof(int), 3);

		char peeAux[sizeof(unsigned long int)];
		repr.copy(peeAux, sizeof(unsigned long int), 7);

		char pvAux[sizeof(unsigned long int)];
		repr.copy(pvAux, sizeof(unsigned long int), 15);


		char raizAux[sizeof(unsigned long int)];
		repr.copy(raizAux, sizeof(unsigned long int), 23);

		tipo = tipooo;
		ver = *reinterpret_cast<int*>(&verAux);
		primExcluido = *reinterpret_cast<unsigned long int*>(&peeAux);
        primValido = *reinterpret_cast<unsigned long int*>(&pvAux);
        raiz = *reinterpret_cast<unsigned long int*>(&raizAux);
};
