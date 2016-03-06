#include "libro.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstring>

using std::string;
using std::istream;
using std::ostream;
using std::stringstream;
using std::setw;
using std::fixed;
using std::setprecision;
using std::left;
using std::right;

Libro::Libro(char* ISBN, char* nombre, char* autor, unsigned int IDeditorial):/*ID(ID), nombre(nombre), autor(autor),*/IDeditorial(IDeditorial){
	      strcpy(nombre, nombre);
	      strcpy(ISBN, ISBN);
	      strcpy(autor, autor);
}

Libro::Libro(const Libro& libro):/*ID(libro.ID), nombre(libro.nombre), autor(libro.autor),*/ IDeditorial(libro.IDeditorial){
	      strcpy(nombre, libro.nombre);
	      strcpy(ISBN, libro.ISBN);
	      strcpy(autor, libro.autor);
}

Libro::Libro(){

}

string Libro::toString()const{
	stringstream ss;
	ss<< "[ID: "<<setw(5)<<ISBN<<", Nombre: "<<setw(10)<<nombre<<", Autor: "<<setw(10)<<autor<<" , ID Editorial: "<<setw(10)<<IDeditorial<<"]";
	return ss.str();
}

string Libro::getID()const{
	//string retVal;
	//for(int i = 0; i < 14; i++){
	//	retVal[i] = ID[i];
	//}
	stringstream ss;
	ss<<ISBN;
	return ss.str();
}

string Libro::getNombre()const{
	stringstream ss;
	ss<<nombre;
	return ss.str();
}

string Libro::getAutor()const{
	stringstream ss;
	ss<<autor;
	return ss.str();
}

unsigned int Libro::getIDeditorial()const{
	return IDeditorial;
}

void Libro::setID(string ISBN){
	for(int i = 0; i < 14; i++){
		this->ISBN[i] = ISBN[i];
	}
	//this->ID=ID;
}

void Libro::setNombre(string nombre){
	for(int i = 0; i < 43; i++){
		this->nombre[i] = nombre[i];
	}
	//this->nombre=nombre;
}

void Libro::setAutor(char* autor){
	for(int i = 0; i < 43; i++){
		this->autor[i] = autor[i];
	}
	//this->autor=autor;
}

void Libro::setIDeditorial(unsigned IDeditorial){
	this->IDeditorial=IDeditorial;
}
