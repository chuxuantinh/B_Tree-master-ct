#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED

#include "No.h"
#include "registro.h"
#include "arquivoRegistro.h"

class Arvore : public ArqRegistro<No>{
public:
	Arvore(const string nome,const string tip, int ver, ios::openmode mode = ios::in | ios:: out | ios::binary);
	bool inserir(OperaTADFRAC &o);
	bool procura(OperaTADFRAC &o);
	void insere_n_cheio(OperaTADFRAC &o, unsigned long int vNo);
	void inserir(OperaTADFRAC &o, unsigned long int vNo);
	void inserirTad(OperaTADFRAC &o);
	void Retira(OperaTADFRAC o, No &no);
	//~Arvore();
private:
	bool procura(OperaTADFRAC &o, No &no);
	unsigned long int raiz;
	void splitChild(unsigned long int r,int i);
	bool abrirArvore(const string nome, int ver, ios::openmode mode);
	void remocao_caso_1(OperaTADFRAC o, No &no);
	//void Retira(OperaTADFRAC o, No &no);

};


#endif // ARVORE_H_INCLUDED


