#ifndef EDITORIAL_H
#define EDITORIAL_H
#include <string>

using std::string;

class Editorial{
public:
	int IDeditorial;
	char nombre[41];
	char direccion[41];
	Editorial(int, char*, char*);
	Editorial(const Editorial&);
	Editorial();
	string toString()const;
	string toString2()const;
	int getIDeditorial()const;
	string getNombre()const;
	string getDireccion()const;
	void setIDeditorial(int);
	void setNombre(string);
	void setDireccion(string);
};

#endif/*EDITORIAL_H*/
