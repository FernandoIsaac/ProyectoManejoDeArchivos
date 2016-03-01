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

struct stIndice {
   string Nombre[10];
   //long indice;
};


void Crear(Libro &libro);
void Insertar(FILE *fa, Libro &libro);

int main(int argc, char** argv){
	//Libro* libro;
	Libro libro;	
	//Libro* libro2 = new Libro();
	//Editorial* editorial;
	FILE *fa;
	int opcion, menu;
	int contLibros = 0;
	//string NombreLibro, ISBN, autor, NombreEditorial, direccion;
	//unsigned int IDEditorialLibro, IDEditorial; 
	//ofstream SalidaLibros("libros.bin",ios::out | ios::binary);
	fa = fopen("libros.bin", "r+b");          // Este modo permite leer y escribir
        if(!fa) fa = fopen("libros.bin", "w+b");  // si el fichero no existe, lo crea.
	do{
		cout<<"Ingrese su opcion: "<<endl
		<<"1) Create Book"<<endl<<"2) Read Book"<<endl
		<<"3) Update Book"<<endl<<"4) Delete Book"<<endl
		<<"5) List Books"<<endl<<"6) Exit"<<endl;
		cin>>menu;
		cin.ignore(256,'\n' );
		if(menu>6||menu<1){
			cout<<"Opcion no valida"<<endl;
			cin.ignore(256,'\n' );
		}
		if(menu==1){
			
			do{
				
				Crear(libro);
				Insertar(fa, libro);
               			//cout<<"Ingrese el nombre del libro"<<endl;
              			//getline (cin,NombreLibro);
              			//cout<<"Ingrese el ISBN del libro"<<endl;
              			//getline (cin, ISBN);
              			//cout<<"Ingrese el nombre del autor del libro"<<endl;
              			//getline (cin, autor);
              			//cout<<"Ingrese el ID del editorial del Libro"<<endl;
              			//cin>>IDEditorialLibro;
              			//libro = new Libro(ISBN, NombreLibro, autor, IDEditorialLibro);
       				//libro = new Libro("12356123", "Pokoyo", "Juancho", 25);
       				//editorial = new Editorial(20, "Editorial1", "Casablanca");
               			//cout<<libro->getNombre()<<endl;
               			//cout<<libro->getID()<<endl;
               			//cout<<libro->getAutor()<<endl;
               			//cout<<libro->getIDeditorial()<<endl;
               			//SalidaLibros.write(reinterpret_cast<char *>(&libro),
               			//sizeof(Libro));
				//contLibros++;
               			cout<<"Desea Continuar Agregando Libros?"<<endl;
               			cin>>opcion;
               			cin.ignore(256, '\n');
               			//if(opcion == 0){
                       		//	break;
               			//}
       			}while(opcion!=0);
       			//SalidaLibros.close();
		}
		if(menu==5){
	/*		cout<<"Listado de Registros"<<endl<<endl;
        		ifstream fentrada("libros.bin",
        		ios::in | ios::binary);
			for(int i = 0; i < contLibros; i++){
       		 		fentrada.read(reinterpret_cast<char *>(&libro2),
        			sizeof(Libro));
				cout<<libro2->getNombre()<<endl;
				cout<<libro2->getID()<<endl;
				cout<<libro2->getAutor()<<endl;
				cout<<libro2->getIDeditorial()<<endl;
			}
			fentrada.close();
			
		//cout<<editorial->getID()<<endl;*/
		}
	}while(menu!=6);
//	cin.ignore(256,'\n' );

	return 0;
}




void Crear(Libro &libro){
   
	//int i;
   	//char numero[6];

	//int opcion, menu;
        //int contLibros = 0;
        string NombreLibro, ISBN, autor;
        unsigned int IDEditorialLibro;

	cout<<"Ingrese el nombre del libro"<<endl;
        getline (cin,NombreLibro);
        cout<<"Ingrese el ISBN del libro"<<endl;
        getline (cin, ISBN);
        cout<<"Ingrese el nombre del autor del libro"<<endl;
        getline (cin, autor);
        cout<<"Ingrese el ID del editorial del Libro"<<endl;
        cin>>IDEditorialLibro;

   /*system("cls");
   printf("Leer registro:\n\n");
   reg.valido = 'S';
   printf("Nombre: ");
   fgets(reg.nombre, 34, stdin);
   EliminarRetornoLinea(reg.nombre);
   printf("Primer apellido: ");
   fgets(reg.apellido[0], 34, stdin);
   EliminarRetornoLinea(reg.apellido[0]);
   printf("Segundo apellido: ");
   fgets(reg.apellido[1], 34, stdin);
   EliminarRetornoLinea(reg.apellido[1]);
   printf("Teléfono: ");
   fgets(reg.telefono, 10, stdin);
   EliminarRetornoLinea(reg.telefono);*/
}


void Insertar(FILE *fa, Libro &libro){
   // Insertar al final:
   fseek(fa, 0, SEEK_END);
   fwrite(&libro, sizeof(Libro), 1, fa);
   //ReconstruirIndices(fa);
}


/*void ReconstruirIndices(FILE *fa)
{
   long n=0;
   FILE *fi;
   Libro libro;
   stIndice ind;
   
   // Crea el fichero de índices a partir del archivo de datos:
   fi = fopen("libros.bin", "w+b");

   rewind(fa);
   while(fread(&reg, sizeof(stRegistro), 1, fa)) {
      strcpy(ind.telefono, reg.telefono);
      ind.indice = n++;
      fwrite(&ind, sizeof(stIndice), 1, fi);
   }
   // Ordena usando el algoritmo Quicksort:
   QuickSort(fi, 0, n-1);
   fclose(fi);
}*/

/*



*/
