#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED

#include "Seriazable.h"

#include <vector>
#include "OPERADORA_FRAC.h"

#define tno 3

class No : public Serializable {
public:
    No();

	void numKeys(int n);
	void numLeaf();
	int Num_Chaves();
	int Num_Filhos();
	void eFolha(bool f);
	bool eFolha();
	string toString();
	void fromString(string repr);


	unsigned long int regFolhas[2*tno];//vetor que contem o numero de registro dos filhos/folhas  das chaves
	vector<OperaTADFRAC> keys;//vetor que contem todas as chaves da pagina, o tamanho dele é definido na classe arvore
    int num_keys;
    int num_leaf;

private:
	//int num_leaf;
	bool folha;
};


#endif // NO_H_INCLUDED
