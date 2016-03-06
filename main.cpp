#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include "libro.h"
#include "editorial.h"

using namespace std;

struct Indice {
   	int IDeditorial;
	long indice;
};

struct Header{
	int AvailList;
	int sizeRegistro;
};


void Capturar(Libro &libro);
void EliminarRetornoLinea(char *cad);
void Leer(FILE *fa, Libro &libro, int IDeditorial);
void Insertar(FILE *fa, Libro &libro);
void Mostrar(Libro &libro);
void ListarPorEditorial(FILE *fa);
void ListarNatural(FILE *fa);
void ReconstruirIndices(FILE *fa);
void Intercambia(FILE *fa, long iz, long de);
int LeeCampo(FILE *fa, long n, int buf);
void QuickSort(FILE *fa, long inicio, long final);


int main(int argc, char** argv){
	//Libro* libro;
	Libro libro;	
	//Libro* libro2 = new Libro();
	Editorial editorial;
	int IDeditorial;
	//Editorial* editorial;
	FILE *fa;
	FILE *fed;
	int opcion, menu;
	//string NombreLibro, ISBN, autor, NombreEditorial, direccion;
	//unsigned int IDEditorialLibro, IDEditorial; 
	//ofstream SalidaLibros("libros.bin",ios::out | ios::binary);
	fa = fopen("libros.dat", "r+b");          // Este modo permite leer y escribir
        if(!fa) fa = fopen("libros.dat", "w+b");  // si el fichero no existe, lo crea.
	fed = fopen("editoriales.dat", "r+b");          // Este modo permite leer y escribir
        if(!fed) fed = fopen("editoriales.dat", "w+b");  // si el fichero no existe, lo crea.
	do{
		cout<<"Ingrese su opcion: "<<endl
		<<"1) Create Book"<<endl<<"2) Read Book"<<endl
		<<"3) Update Book"<<endl<<"4) Delete Book"<<endl
		<<"5) List Books"<<endl<<"6) Create Editorial"<<endl<<"7) Exit"<<endl;
		cin>>menu;
		cin.ignore(256,'\n' );
		if(menu>7||menu<1){
			cout<<"Opcion no valida"<<endl;
			cin.ignore(256,'\n' );
		}
		if(menu==1){
			Capturar(libro);
			Insertar(fa, libro);
            	

		}
		if(menu==2){
			do {
	       			cin>>IDeditorial;
            		} while(IDeditorial < 1);
            		Leer(fa, libro, IDeditorial);
           		Mostrar(libro);
		}
		if(menu==3){
			
		}
		if(menu==4){
			
		}
		if(menu==5){
			ListarNatural(fa);
		}

		if(menu==6){

		}
	}while(menu!=7);
//	cin.ignore(256,'\n' );

	return 0;
}


// Permite que el usuario introduzca un registro por pantalla
void Capturar(Libro &libro){
	int i;
	//   char numero[6];

   	//system("cls");
   	//printf("Leer registro:\n\n");
   	//libro.valido = 'S';
   	printf("Nombre: ");
   	fgets(libro.nombre, 41, stdin);
   	EliminarRetornoLinea(libro.nombre);
   	printf("Autor: ");
   	fgets(libro.autor, 41, stdin);
   	EliminarRetornoLinea(libro.autor);
   	printf("ISBN: ");
   	fgets(libro.ISBN, 14, stdin);
   	EliminarRetornoLinea(libro.ISBN);
   	printf("ID editorial: ");
   	//fgets(libro.IDeditorial, 5, stdin);
   	cin>>libro.IDeditorial;
   	//EliminarRetornoLinea(libro.IDeditorial);
}

// Elimina los caracteres de retorno de línea al final de cadena
void EliminarRetornoLinea(char *cad){
   	int i;
   	// la función fgets captura el retorno de línea, hay que eliminarlo:
   	for(i = strlen(cad)-1; i >= 0 && cad[i] < ' '; i--) cad[i] = 0;
}

// Muestra un registro en pantalla, si no está marcado como borrado
void Mostrar(Libro &libro){

	int i;

	if(libro.IDeditorial > 0) {
      		printf("Nombre: %s %s %s\n", libro.nombre, libro.autor, libro.ISBN);
      		printf("Número de teléfono: %u\n", libro.IDeditorial);
   	}
   	system("PAUSE");
}

// Lee el registro desde el fichero de datos con el teléfono dado
void Leer(FILE *fa, Libro &libro, int IDeditorial){

	FILE *fi;
   	Indice ind;
   	long inf, sup, n, nRegs;

   	fi = fopen("libros.ind", "rb");
   	fseek(fi, 0, SEEK_END);
   	nRegs = ftell(fi)/sizeof(Indice);
   	// Búsqueda binaria:
   	inf = 0;
   	sup = nRegs-1;
   	do {
      		n = inf+(sup-inf)/2;
      		fseek(fi, n*sizeof(Indice), SEEK_SET);
      		fread(&ind, sizeof(Indice), 1, fi);
      		if((ind.IDeditorial<0)&&(IDeditorial < 0)) inf = n+1;
      		else sup = n-1;
   	} while(inf <= sup && (ind.IDeditorial==IDeditorial));
   	// Si se encontró el teléfono, lee el registro, si no muestra mensaje.
   	if((ind.IDeditorial!=IDeditorial)) {
      		fseek(fa, ind.indice*sizeof(Libro), SEEK_SET);
      		fread(&libro, sizeof(Libro), 1, fa);
   	}
   	else {
      		libro.IDeditorial = -2;
      		printf("Registro no encontrado\n");
   	}
   	fclose(fi);
}

void Insertar(FILE *fa, Libro &libro){
   	// Insertar al final:
	fseek(fa, 0, SEEK_END);
   	fwrite(&libro, sizeof(Libro), 1, fa);
   	ReconstruirIndices(fa);
}

void ListarPorEditorial(FILE *fa){

	FILE *fi;
	Indice ind;
	Libro libro;
   
   	//system("cls");
   	fi = fopen("libros.ind", "rb");
   	while(fread(&ind, sizeof(Indice), 1, fi)) {
      		fseek(fa, ind.indice*sizeof(Libro), SEEK_SET);
      		fread(&libro, sizeof(Libro), 1, fa);
      		printf("%s %s %s %u\n", libro.nombre, libro.autor,
        	libro.ISBN, libro.IDeditorial);
   	}
   	fclose(fi);
   	//system("PAUSE");
}

// Lista todos los registros del archivo de datos por el orden en que se
// insertaron.
void ListarNatural(FILE *fa){

	Libro libro;
   
   	rewind(fa);
   	//system("cls");
   	while(fread(&libro, sizeof(Libro), 1, fa)) 
      	printf("%s %s %s %u\n", libro.nombre, libro.autor,
        libro.ISBN, libro.IDeditorial);
   	//system("PAUSE");
}

// Reconstruye el archivo de índices
void ReconstruirIndices(FILE *fa){
	long n=0;
   	FILE *fi;
   	Libro libro;
   	Indice ind;
   
   	// Crea el fichero de índices 
   	fi = fopen("libros.ind", "w+b");
   	rewind(fa);
   	while(fread(&libro, sizeof(Libro), 1, fa)) {
      		//strcpy(ind.IDeditorial, libro.IDeditorial);
      		ind.IDeditorial=libro.IDeditorial;
      		ind.indice = n++;
      		fwrite(&ind, sizeof(Indice), 1, fi);
   	}
   	// Ordena usando el algoritmo Quicksort:
   	QuickSort(fi, 0, n-1);
   	fclose(fi);
}

void QuickSort(FILE *fi, long inicio, long final){

   	long iz, de;
   	//char mitad[10];
   	//static char cad[10];
   	int mitad;
   	static int cad;

   	iz = inicio;
   	de = final;
   	//strcpy(mitad, LeeCampo(fi, (iz+de)/2, cad));
   	mitad = LeeCampo(fi, (iz+de)/2, cad);
   	do {
      		while((LeeCampo(fi, iz, cad)<0) && (mitad<0) && iz < final) iz++;
      		while((mitad<0) && (LeeCampo(fi, de, cad)<0) && (de > inicio)) de--;
      		if(iz < de) Intercambia(fi, iz, de);
      		if(iz <= de) {
         		iz++;
         		de--;
     		 }
   	} while(iz <= de);
   	if(inicio < de) QuickSort(fi, inicio, de);
   	if(iz < final) QuickSort(fi, iz, final);
}

int LeeCampo(FILE *fi, long n, int buf){

   	Indice ind;

   	fseek(fi, n*sizeof(Indice), SEEK_SET);
   	fread(&ind, sizeof(Indice), 1, fi);
   	//strcpy(buf, ind.IDeditorial);
   	buf = ind.IDeditorial;
   	return buf;
}

void Intercambia(FILE *fi, long iz, long de){
   
	Indice libro1, libro2;

   	fseek(fi, iz*sizeof(Indice), SEEK_SET);
   	fread(&libro1, sizeof(Indice), 1, fi);
   	fseek(fi, de*sizeof(Indice), SEEK_SET);
   	fread(&libro2, sizeof(Indice), 1, fi);
   	fseek(fi, iz*sizeof(Indice), SEEK_SET);
   	fwrite(&libro2, sizeof(Indice), 1, fi);
	fseek(fi, de*sizeof(Indice), SEEK_SET);
	fwrite(&libro1, sizeof(Indice), 1, fi);
}
