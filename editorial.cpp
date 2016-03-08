#include"editorial.h"
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

Editorial::Editorial(int IDeditorial, char* nombre, char* direccion):IDeditorial(IDeditorial)/*, nombre(nombre), direccion(direccion)*/{
              strcpy(nombre, nombre);
              strcpy(direccion, direccion);
             
}

Editorial::Editorial(const Editorial& editorial):IDeditorial(editorial.IDeditorial){//, nombre(editorial.nombre), direccion(editorial.direccion){

}

Editorial::Editorial(){
	
}

string Editorial::toString()const{
        stringstream ss;
        ss<< "[ID: "<<setw(5)<<IDeditorial<<", Nombre: "<<setw(10)<<nombre<<", Direccion: "<<setw(10)<<direccion<<"]";
        return ss.str();
}

string Editorial::toString2()const{
	stringstream ss;
	ss<<IDeditorial;
	return ss.str();

}

int Editorial::getIDeditorial()const{
        return IDeditorial;
}

string Editorial::getNombre()const{
        return nombre;
}

string Editorial::getDireccion()const{
        return direccion ;
}

void Editorial::setIDeditorial(int IDeditorial){

	 this->IDeditorial=IDeditorial;
}

void Editorial::setNombre(string nombre){
        for(int i = 0; i < 41; i++){
                this->nombre[i] = nombre[i];
        }
        //this->nombre=nombre;
}

void Editorial::setDireccion(string direccion){
        for(int i = 0; i < 41; i++){
                this->direccion[i] = direccion[i];
        }
}
