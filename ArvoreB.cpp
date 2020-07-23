#include "arvore.h"
#include <iostream>
#include <stdlib.h>
#include "NO.h"
#define tn 3


void Arvore::splitChild(unsigned long int nNo, int nFilho){
	No pai, filhoEsq, filhoDir;
	Registro<No> regPai, regEsq, regDir;
	lerRegistro(nNo, regPai);
	pai = regPai.info();

	lerRegistro(pai.regFolhas[nFilho-1], regEsq);
	filhoEsq = regEsq.info();
	filhoDir.eFolha(filhoEsq.eFolha());
	filhoDir.numKeys(tn - 1);
	int j;

	for(j = 0; j < tn - 1; j++){
		filhoDir.keys[j] = filhoEsq.keys[j+tn];
	}
	if(!filhoEsq.eFolha()){
		for(j = 0; j < tn; j++)
			filhoDir.regFolhas[j] = filhoEsq.regFolhas[j+tn];
	}
	filhoEsq.numKeys(tn-1);
	for(j = pai.Num_Chaves(); j > nFilho +1; j--)
		pai.regFolhas[j+1] = pai.regFolhas[j];
	regDir.info(filhoDir);
	inserirRegistro(regDir);
	pai.regFolhas[nFilho] = primeiroValido();
	for (j = pai.Num_Chaves() -1 ; j > nFilho; j--)
		pai.keys[j] = pai.keys[j-1];
	pai.keys[nFilho-1] = filhoEsq.keys[tn-1];
	pai.numKeys(pai.Num_Chaves() + 1);
	regEsq.info(filhoEsq);
	regPai.info(pai);
	escreverRegistro(nNo, regPai);
	escreverRegistro(pai.regFolhas[nFilho-1],regEsq);
}

void Arvore::inserirTad(OperaTADFRAC &o){
	inserir(o, cab.raiz);
}

void Arvore::inserir(OperaTADFRAC &o, unsigned long int vNo){
	Registro<No> reg, regRaiz;
	No no;
	lerRegistro(vNo, reg);
	no = reg.info();

	if(no.Num_Chaves() == 2*tn-1){
		No pai;
		pai.eFolha(false);
		pai.numKeys(0);
		pai.regFolhas[0] = cab.raiz;
		regRaiz.info(pai);
		inserirRegistro(regRaiz);

		cab.raiz = primeiroValido();
		escreverCabecalho();
		splitChild(cab.raiz, 1);

		insere_n_cheio(o,cab.raiz);
	} else
	insere_n_cheio(o, vNo);
}

void Arvore::insere_n_cheio(OperaTADFRAC &o, unsigned long int vNo){
	Registro<No> reg;
	No no;
	lerRegistro(vNo, reg);
	no = reg.info();
	int i = no.Num_Chaves() -1;
	if (no.eFolha()){
		while(i >= 0 && o < no.keys[i]){
			no.keys[i+1] = no.keys[i];
			i = i - 1;
		}
		no.keys[i+1] = o;
		no.numKeys(no.num_keys + 1);

		reg.info(no);
		escreverRegistro(vNo, reg);
	} else {
		while (i >= 0 && o < no.keys[i])
			i--;
		i++;
		Registro<No> filho;
		No noFilho;
		lerRegistro(no.regFolhas[i], filho);
		noFilho = filho.info();
		if(noFilho.num_keys == (2*tn)-1){
			splitChild(vNo, i+1);
			lerRegistro(vNo, reg);
			no = reg.info();
			if (o > no.keys[i])
				i++;

		}
		insere_n_cheio(o, no.regFolhas[i]);
	}
}


bool Arvore::procura(OperaTADFRAC &o){
	Registro<No> res;
	lerRegistro(cab.raiz, res);
	No ino = res.info();
	return procura(o, ino);
}

bool Arvore::procura(OperaTADFRAC &o, No &no){
	int i = 1;
	while (i <= no.Num_Chaves() && o > no.keys[i-1]){
		i++;
	}
	if ( i <= no.Num_Filhos() && o == no.keys[i-1]){
		return true;
	}

	if (no.eFolha()){
		return false;
	}
	Registro<No> res2;
	No n_no;
	lerRegistro(no.regFolhas[i-1], res2);
	n_no = res2.info();
	return procura(o, n_no);
}

void Arvore::remocao_caso_1(OperaTADFRAC o, No &no){
	int i = 1;
	while ( i <= no.Num_Filhos() && o > no.keys[i-1]){
		i++;
	}
	if(no.keys[i-1] == o){
		int j;
		for (j = i; j <= no.Num_Filhos(); j++)
		{
			no.keys[j-1] = no.keys[j];
		}
		no.num_leaf = (no.Num_Filhos() - 1);
	}
}

void Arvore::Retira(OperaTADFRAC o, No &no){
	if (no.eFolha()){ //se for folha
		return;
	}
	int i = 1;
	while (i <= no.Num_Filhos() && o > no.keys[i-1]){
		i++;
	}
	if(no.keys[i-1] == o) {
		//remocaoCaso2(o, no);
	} else {
		Registro<No> reg;
		lerRegistro(no.regFolhas[i-1], reg);
		//remocaoCaso3(o, res);
	}
}
Arvore::Arvore(const string nome, string tipo, int ver ,ios::openmode mode){
	abrir(nome, tipo, ver, mode);
	if(cab.raiz == 0){
		No no;
		no.eFolha(true);
		no.numKeys(0);
		Registro<No> regRaiz;
		regRaiz.info(no);
		inserirRegistro(regRaiz);
		cab.raiz = primeiroValido();
		escreverCabecalho();
	}
}
