
#include "NO.h"
#define t 3
#include <vector>
#include <cstdio>
#include "OPERADORA_FRAC.h"
#include <iostream>
#include <fstream>
#include <string>
No::No(){

num_leaf = 0;
num_keys = 0;
eFolha(true);

for (int i = 0; i< 2*t;i++){

regFolhas[i] = 0;

}

OperaTADFRAC K;
for(int i = 0; i < (2*t) - 1;i++){

keys.push_back(K);

}

}


void No::numLeaf(){

num_leaf = Num_Chaves() + 1;


}

void No::eFolha(bool f){
	folha = f;
}

bool No::eFolha(){

return folha;

}

void No::numKeys(int n){

	num_keys = n;
	Num_Filhos();
}


int No::Num_Chaves(){
	return num_keys;
}

int No::Num_Filhos(){

return num_leaf;

}



string No::toString(){
int nchaves = Num_Chaves();
int nfilhos = Num_Filhos();
bool nfolha = eFolha();
unsigned long int nfilhos[2*t];

for(int i = 0; i < 2*t; i++){

regFolhas[i] = regFolhas[i];

}
string regFilh;
string nkeys;

string numChav = string(reinterpret_cast<char*>(&nchaves), sizeof(int));
string numFilh = string(reinterpret_cast<char*>(&nfilhos), sizeof(int));
string folh = string(reinterpret_cast<char*>(&nfolha), sizeof(bool));

for(int i = 0; i< num_leaf;i++){
regFolhas = regFolhas + string(reinterpret_cast<char*>(&nfilhos[i]), sizeof(unsigned long int));
}
unsigned long int pWriteTad = 0;
for(int i = num_leaf; i < 2*t; i++){
    regFolhas = regFolhas + string(reinterpret_cast<char*>(&pWriteTad), sizeof(unsigned long int));
}

for(int i = 0; i < nchaves; i++){
    nkeys = nkeys + keys[i].toString();
}
OperaTADFRAC pWrite;

for(int i = nchaves; i < 2*t-1; i++){
    nkeys = nkeys + pWrite.toString();
}
string palavra = (numChav + numFilh + folh + regFolhas + nkeys);
return palavra;
}


void No::fromString(string repr){
int i;
char nchave[sizeof(int)];
repr.copy(nchave,sizeof(int),0);
char nfolha[sizeof(int)];
repr.copy(nfolha,sizeof(int),4);
char nfilho[sizeof(bool)];
repr.copy(nfilho,sizeof(bool),8);
char regFilho[sizeof(unsigned long int)];

num_keys = *reinterpret_cast<int*>(&nchave);
num_leaf = *reinterpret_cast<int*>(&nfolha);
folha = *reinterpret_cast<bool*>(&nfilho);

    int j = 1;//para o vetor conter os numeros de registros de cada filho/*
    for(i = 0; i < Num_Filhos(); i++){
        j += 8;
        repr.copy(nfolha,sizeof(unsigned long int),j);
        regFolhas[i] = *reinterpret_cast<unsigned long int*>(&nfolha);
    }

    int k = 41;//vetor de chaves
    char ntad[16];
    for(i = 0; i < Num_Chaves();i++){
        k += 16;
        repr.copy(ntad,16, k);
        keys[i].fromString(string(ntad, 16));
    }


}

