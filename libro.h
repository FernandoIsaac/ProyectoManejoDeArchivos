#ifndef LIBRO_H
#define LIBRO_H

#include<string>

using std::string;

class Libro{
public:
	char ISBN[14];
	char nombre[43];
	char autor[41];
	unsigned int IDeditorial;
	Libro(char*, char*, char*, unsigned int);
	Libro(const Libro&);
	Libro();
	string toString()const;
	string getNombre()const;
	string getID()const;
	string getAutor()const;
	unsigned int getIDeditorial()const;
	void setNombre(string);
	void setID(string);
	void setAutor(char*);
	void setIDeditorial(unsigned int);
};

#endif /*LIBRO_H*/
