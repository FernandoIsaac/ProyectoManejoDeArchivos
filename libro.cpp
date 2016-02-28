#include "libro.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

using std::string;
using std::istream;
using std::ostream;
using std::stringstream;
using std::setw;
using std::fixed;
using std::setprecision;
using std::left;
using std::right;

Libro::Libro(string ID, string nombre, string autor, unsigned int IDeditorial):ID(ID), nombre(nombre), autor(autor), IDeditorial(IDeditorial){

}

Libro::Libro(const Libro& libro):ID(libro.ID), nombre(libro.nombre), autor(libro.autor), IDeditorial(libro.IDeditorial){

}

Libro::Libro(){

}

string Libro::toString()const{
	stringstream ss;
	ss<< "[ID: "<<setw(5)<<ID<<", Nombre: "<<setw(10)<<nombre<<", Autor: "<<setw(10)<<autor<<" , ID Editorial: "<<setw(10)<<IDeditorial<<"]";
	return ss.str();
}

string Libro::getID()const{
	return ID;
}

string Libro::getNombre()const{
	return nombre;
}

string Libro::getAutor()const{
	return autor;
}

unsigned int Libro::getIDeditorial()const{
	return IDeditorial;
}

void Libro::setID(string ID){
	this->ID=ID;
}

void Libro::setNombre(string nombre){
	this->nombre=nombre;
}

void Libro::setAutor(string autor){
	this->autor=autor;
}

void Libro::setIDeditorial(unsigned IDeditorial){
	this->IDeditorial=IDeditorial;
}
