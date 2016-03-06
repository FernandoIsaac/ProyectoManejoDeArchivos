#ifndef EDITORIAL_H
#define EDITORIAL_H
#include <string>

using std::string;

class Editorial{
	unsigned int ID;
	string nombre;
	string direccion;
public:
	Editorial(unsigned int, string, string);
	Editorial(const Editorial&);
	Editorial();
	string toString()const;
	string toString2()const;
	unsigned int getID()const;
	string getNombre()const;
	string getDireccion()const;
	void setID(unsigned int);
	void setNombre(string);
	void setDireccion(string);
};

#endif/*EDITORIAL_H*/
