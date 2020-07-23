#ifndef SERIAZABLE_H_INCLUDED
#define SERIAZABLE_H_INCLUDED
#include <string>
using namespace std;
class Serializable{
public:
    Serializable(){};
    ~Serializable(){};
    string toString(); //eh para escrever
    void fromString(string repr);
    /*
	virtual string toXML()=0;
	virtual void fromXML(string)=0;
	virtual string toCSV()=0;
	virtual void fromCSV(string)=0;
	virtual string toJSON()=0;
	virtual void fromJSON(string)=0;

	virtual int getSize()=0;*/
	//esta comentadao pq a implementacao n deu certo

};



#endif // SERIAZABLE_H_INCLUDED
