/*
*						IFMG-Campus Bambuí
*
*
*			 Trabalho de Técnicas de Programação
*
*							BTree
*
*		Nome: 					    RA
*		Mariane Cipriano Costa      0022126
*
*
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <vector>

#include "OPERADORA_FRAC.h"
#include "arquivoRegistro.h"
#include "registro.h"
#include "NO.h"
#include "arvore.h"
using namespace std;

int main(int argc, char const *argv[])
{
    ArqRegistro<No> teste;
    Arvore a("texto.txt", "abc", 1);
    No n1;
    Registro<No> reg, reg2;

    int opcao;
    int posicao,i;
    bool p = true;
    int n,d;
    OperaTADFRAC k;
    //Arvore<OperaTADFRAC>a("texto.txt", "abc", 1);

    a.fechar();
    teste.abrir("texto.txt", "alf", 1);
    Registro<No> aux;
    teste.lerRegistro(teste.cab.raiz, aux);
        cout << aux;
    teste.lerRegistro(1, aux);
        cout << aux;
    teste.lerRegistro(3, aux);
    cout << aux;



    do{
        cout<<endl;
		cout<<"Arvore B de fracoes"<<endl;
		cout<<"Escolha uma opcao:  "<<endl;
		cout<<"1 - Inserir uma fracao"<<endl;
		cout<<"2 - Deletar uma fracao"<<endl;
		cout<<"3 - Procurar uma fracao"<<endl;
		cout<<"4 - Imprimir o no completo de uma fracao"<<endl;
		cout<<"5 - Imprimir todas as fracoes"<<endl;
		cout<<"0 - Sair"<<endl;
		cout<<"Opcao: ";
		cin>>opcao;
		cout<<endl;

		switch(opcao){
			case 1:
				cout<<"Digite o numerador: ";
				cin>>n;
				cout<<"Digite o denominador: ";
				cin>>d;
				k= OperaTADFRAC(n,d);
				posicao = a.procura(k);
				if(posicao <= 0){
                    cout << "Elemento inserido!!!!"<< endl;
                    a.inserirTad(k);
				}else{
				    cout<< "Nao existe esta fracao"<< endl;
				}

			break;
			case 2:
				cout<<"Digite o numerador: ";
				cin>>n;
				cout<<"Digite o denominador: ";
				cin>>d;
				k= OperaTADFRAC(n,d);
				posicao = a.procura(k);
				if(posicao > 0){
                    a.Retira(k,n1);
                    cout<< "Elemento  foi excluido"<< endl;
				}else{
				    cout << "Fracao nao foi encontrada"<< endl;
				}
				cout<<"Fracao nao encontrada!"<<endl;
				}
			break;
			case 3:
				cout<<"Digite o numerador: ";
				cin>>n;
				cout<<"Digite o denominador: ";
				cin>>d;
				k =OperaTADFRAC(n,d);
				posicao=a.procura(k);
				if(posicao>0){
					cout<<" Fracao: "<<k<<"  encontrada em :  "<<posicao<<endl;
				}else{
					cout<<"Fracao nao encontrada!"<<endl;
				}
			break;
			case 4:
                cout<<"Digite o numerador: ";
				cin>>n;
				cout<<"Digite o denominador: ";
				cin>>d;
				k=OperaTADFRAC(n,d);
				posicao=a.procura(k);
				if(posicao>0){
					cout<<" Fração: "<<k<<"  encontrada em :  "<<posicao<<endl;
					a.lerRegistro(n,d);

				}else{
					cout<<"Fracao nao encontrada!"<<endl;
				}
			break;
			case 5:
			a.lerCabecalho();
			break;
			case 0:
				cout<<"Saindo..."<<endl;
				p =false;
			break;
			default:
				cout<<"Opcao invalida!"<<endl;
		}
		while(p);


	a.fechar();

    return 0;
    }

