#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include "libro.h"
#include "editorial.h"

using namespace std;

int main(int argc, char** argv){
	Libro* libro;
	Libro* libro2 = new Libro();
	Editorial* editorial;
	int opcion;
	int menu;
	string NombreLibro, ISBN, autor, NombreEditorial, direccion;
	unsigned int IDEditorialLibro, IDEditorial; 
	ofstream SalidaLibros("libros.bin",ios::out | ios::binary);
	do{
		cout<<"Ingrese su opcion: "<<endl
		<<"1) Create"<<endl<<"2) Read"<<endl
		<<"3) Update"<<endl<<"4) Delete"<<endl
		<<"5) List"<<endl<<"6) Exit"<<endl;
		cin>>menu;
		cin.ignore(256,'\n' );
		if(menu>6||menu<1){
			cout<<"Opcion no valida"<<endl;
			cin.ignore(256,'\n' );
		}
		if(menu==1){
			do{
                		cout<<"Ingrese el nombre del libro"<<endl;
                		getline (cin,NombreLibro);
                		cout<<"Ingrese el ISBN del libro"<<endl;
                		getline (cin, ISBN);
                		cout<<"Ingrese el nombre del autor del libro"<<endl;
                		getline (cin, autor);
                		cout<<"Ingrese el ID del editorial del Libro"<<endl;
                		cin>>IDEditorialLibro;

                		libro = new Libro(ISBN, NombreLibro, autor, IDEditorialLibro);

        			//libro = new Libro("12356123", "Pokoyo", "Juancho", 25);
        			//editorial = new Editorial(20, "Editorial1", "Casablanca");

                		cout<<libro->getNombre()<<endl;
                		cout<<libro->getID()<<endl;
                		cout<<libro->getAutor()<<endl;
                		cout<<libro->getIDeditorial()<<endl;

                		SalidaLibros.write(reinterpret_cast<char *>(&libro),
                		sizeof(Libro));
                		//SalidaLibros.close();
                		cout<<"Desea Continuar Agregando Libros?"<<endl;
                		cin>>opcion;
                		cin.ignore(256, '\n');
                		if(opcion == 0){
                		//      SalidaLibros.close();
                        		break;
                		}
        		}while(opcion!=0);
        		SalidaLibros.close();

		}
		if(menu==5){
		//	cout<<"Listado de Registros"<<endl<<endl;
		//	ifstream in;
		//	in.open("libros.bin", ios::in | ios::binary);
		/*	streampos start = in.tellg();
			in.seekg(0, std::ios::end);
			streampos  end = in.tellg();
			in.seekg(0, std::ios::beg);
			std::vector<char> contents;
			contents.resize(static_cast<size_t>(end - start));
			in.read(&contents[0], contents.size());
			for(const char& c : contents){
				cout<<c;
			};
		*/
		//	cout<<in.rdbuf();
        		ifstream fentrada("libros.bin",
        		ios::in | ios::binary);

       		 	fentrada.read(reinterpret_cast<char *>(&libro2),
        		sizeof(Libro));

			cout<<libro2->getNombre()<<endl;
			cout<<libro2->getID()<<endl;
			cout<<libro2->getAutor()<<endl;
			cout<<libro2->getIDeditorial()<<endl;
			fentrada.close();
		//cout<<editorial->getID()<<endl;
		}
	}while(menu!=6);
	cin.ignore(256,'\n' );
	/*do{	
		cout<<"Ingrese el nombre del libro"<<endl;
		getline (cin,NombreLibro);
		cout<<"Ingrese el ISBN del libro"<<endl;
		getline (cin, ISBN);
		cout<<"Ingrese el nombre del autor del libro"<<endl;
		getline (cin, autor);
		cout<<"Ingrese el ID del editorial del Libro"<<endl;
		cin>>IDEditorialLibro;
	
		libro = new Libro(ISBN, NombreLibro, autor, IDEditorialLibro);
	
	//libro = new Libro("12356123", "Pokoyo", "Juancho", 25);
	//editorial = new Editorial(20, "Editorial1", "Casablanca");
	
		cout<<libro->getNombre()<<endl;
		cout<<libro->getID()<<endl;
		cout<<libro->getAutor()<<endl;
		cout<<libro->getIDeditorial()<<endl;

		SalidaLibros.write(reinterpret_cast<char *>(&libro),
        	sizeof(Libro));
        	//SalidaLibros.close();
		cout<<"Desea Continuar Agregando Libros?"<<endl;
		cin>>opcion;
		cin.ignore(256, '\n');
		if(opcion == 0){
		//	SalidaLibros.close();
			break;
		}
	}while(opcion!=0);
	SalidaLibros.close();
*/
        /*ifstream fentrada("libros.bin",
        ios::in | ios::binary);

        fentrada.read(reinterpret_cast<char *>(&libro2),
        sizeof(Libro));

	cout<<libro2->getNombre()<<endl;
	cout<<libro2->getID()<<endl;
	cout<<libro2->getAutor()<<endl;
	cout<<libro2->getIDeditorial()<<endl;
	fentrada.close();*/
	//cout<<editorial->getID()<<endl;
	//cout<<editorial->getNombre()<<endl;
	//cout<<editorial->getDireccion()<<endl;		
	

	return 0;
}
