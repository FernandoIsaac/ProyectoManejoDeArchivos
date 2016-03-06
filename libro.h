#ifndef LIBRO_H
#define LIBRO_H

#include<string>

using std::string;

class Libro{
public:
	char ISBN[14];
	char nombre[43];
	char autor[41];
	int IDeditorial;
	Libro(char*, char*, char*, int);
	Libro(const Libro&);
	Libro();
	string toString()const;
	string getNombre()const;
	string getID()const;
	string getAutor()const;
	int getIDeditorial()const;
	void setNombre(string);
	void setID(string);
	void setAutor(char*);
	void setIDeditorial(int);
};

#endif /*LIBRO_H*/
