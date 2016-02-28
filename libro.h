#ifndef LIBRO_H
#define LIBRO_H

#include<string>

using std::string;

class Libro{
	string ID;
	string nombre;
	string autor;
	unsigned int IDeditorial;
public:
	Libro(string, string, string, unsigned int);
	Libro(const Libro&);
	Libro();
	string toString()const;
	string getNombre()const;
	string getID()const;
	string getAutor()const;
	unsigned int getIDeditorial()const;
	void setNombre(string);
	void setID(string);
	void setAutor(string);
	void setIDeditorial(unsigned int);
};

#endif /*LIBRO_H*/
