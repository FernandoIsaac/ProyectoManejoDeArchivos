#include"editorial.h"
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

Editorial::Editorial(unsigned int ID, string nombre, string direccion):ID(ID), nombre(nombre), direccion(direccion){

}

Editorial::Editorial(const Editorial& editorial):ID(editorial.ID), nombre(editorial.nombre), direccion(editorial.direccion){

}

Editorial::Editorial(){
	
}

string Editorial::toString()const{
        stringstream ss;
        ss<< "[ID: "<<setw(5)<<ID<<", Nombre: "<<setw(10)<<nombre<<", Direccion: "<<setw(10)<<direccion<<"]";
        return ss.str();
}

string Editorial::toString2()const{
	stringstream ss;
	ss<<ID;
	return ss.str();

}

unsigned int Editorial::getID()const{
        return ID;
}

string Editorial::getNombre()const{
        return nombre;
}

string Editorial::getDireccion()const{
        return direccion ;
}

void Editorial::setID(unsigned int ID){
        this->ID=ID;
}

void Editorial::setNombre(string nombre){
        this->nombre=nombre;
}

void Editorial::setDireccion(string direccion){
        this->direccion=direccion;
}
