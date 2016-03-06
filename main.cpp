#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include "libro.h"
#include "editorial.h"

using namespace std;

template <class T>
class Stack{
public:
  	Stack() {}
  	void push(T x);
  	void pop();
  	T & top();
  	size_t size();
  	bool empty();
	std::vector<T> elems;
};

template <class T>
void Stack<T>::push(T x){
	elems.push_back(x);
}

template <class T>
void Stack<T>::pop(){
	if (elems.size() > 0){
      		elems.erase(elems.end() - 1);
    	};
}

template <class T>
T & Stack<T>::top(){
	assert(elems.size() > 0);
	return elems.at(elems.size()-1);
}

template <class T>
size_t Stack<T>::size(){
	return elems.size();
}

template <class T>
bool Stack<T>::empty(){
	return elems.size() == 0 ? true : false;
}

struct Indice {
   	int IDeditorial;
	long indice;
};

struct Header{
	Stack<int> AvailList;
	int sizeRegistro;
};


void Capturar(Libro &libro);
void EliminarRetornoLinea(char *cad);
void Leer(FILE *fa, Libro &libro, int IDeditorial);
void Update(FILE *fa, Libro &libro, int IDeditorial);
void Delete(FILE *fa, Libro &libro, int IDeditorial);
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
	Header header;
	if(header.AvailList.empty()==1){
		header.AvailList.push(-1);
	}
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
		<<"5) List Books"<<endl<<"6) Create Editorial"<<endl
		<<"7) Read Editorial"<<endl<<"8) Update Editorial"<<endl
		<<"9) Delete Editorial"<<endl<<"10) List Editorials"<<endl
		<<"11) List Books By Editorial"<<endl<<"12) Reindexar Libros"<<endl
		<<"13) Exit"<<endl;
		cin>>menu;
		cin.ignore(256,'\n' );
		if(menu>13||menu<1){
			cout<<"Opcion no valida"<<endl;
			cin.ignore(256,'\n' );
		}
		if(menu==1){
			Capturar(libro);
			Insertar(fa, libro);
			header.sizeRegistro++;
		}
		if(menu==2){
			do {
				cout<<"Ingrese el ID del editorial del libro que desea buscar"<<endl;
	       			cin>>IDeditorial;
            		} while(IDeditorial < 1);
            		Leer(fa, libro, IDeditorial);
           		Mostrar(libro);
		}
		if(menu==3){
			do{
				cout<<"Ingrese el ID del editorial del libro que desea modificar"<<endl;
				cin>>IDeditorial;
			}while(IDeditorial<1);	
			Update(fa, libro, IDeditorial);
			cin.ignore(256,'\n' );
		}
		if(menu==4){
			do{
				cout<<"Ingrese el ID del editorial del libro que desea eliminar"<<endl;
				cin>>IDeditorial;
			}while(IDeditorial<1);	
			Delete(fa, libro, IDeditorial);
			cin.ignore(256,'\n' );
			
		}
		if(menu==5){
			ListarNatural(fa);
		}

		if(menu==6){

		}
		if(menu==8){

		}
		if(menu==9){

		}
		if(menu==10){

		}
		if(menu==11){
			ListarPorEditorial(fa);
		}
		if(menu==12){
			printf("Indices Reordenados");
			cout<<endl;
			ReconstruirIndices(fa);
		}
	}while(menu!=13);
//	cin.ignore(256,'\n' );

	return 0;
}


// Permite que el usuario introduzca un registro por pantalla
void Capturar(Libro &libro){
	//   char numero[6];

   	//system("cls");
   	//printf("Leer registro:\n\n");
   	//libro.valido = 'S';
   	printf("Nombre: ");
   	fgets(libro.nombre, 43, stdin);
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
      		printf("Número de Editorial: %d\n", libro.IDeditorial);
   	}
   	system("PAUSE");
}
void Delete(FILE *fa, Libro &libro, int IDeditorial){
	FILE *fi;
   	Indice ind;
	Header header;
   	long inf, sup, n, nRegs;
   	fi = fopen("libros.ind", "rb");
   	fseek(fi, 0, SEEK_END);
   	nRegs = ftell(fi)/sizeof(Indice);
   	// Búsqueda binaria:
   	inf = 0;
   	sup = nRegs-1;
			//getline (cin,NombreLibro);
	do {
      		n = inf+(sup-inf)/2;
      		fseek(fi, n*sizeof(Indice), SEEK_SET);
      		fread(&ind, sizeof(Indice), 1, fi);
		if((ind.IDeditorial==IDeditorial)) {
                        //fgets(libro.IDeditorial, 5, stdin);
			libro.IDeditorial = ind.indice*-1;
			header.AvailList.push(libro.IDeditorial);
                        fseek(fa, ind.indice*sizeof(Libro), SEEK_SET);
                        fwrite(&libro, sizeof(Libro), 1, fa);
                        ReconstruirIndices(fa);
                }

  		if(ind.IDeditorial<IDeditorial) inf = n+1;
      		else sup = n-1;
   	} while(inf <= sup /*&& (ind.IDeditorial!=IDeditorial)*/);
   	if((ind.IDeditorial==IDeditorial)) {
		//cin.ignore(256,'\n' );
     		//fseek(fa, ind.indice*sizeof(Libro), SEEK_SET);
   		//fgets(libro.IDeditorial, 5, stdin);
		libro.IDeditorial=ind.indice*-1;
		fseek(fa, ind.indice*sizeof(Libro), SEEK_SET);
   		fwrite(&libro, sizeof(Libro), 1, fa);
   		ReconstruirIndices(fa);
   	}
	
	else {
      		libro.IDeditorial = -2;
      		printf("Registro no encontrado\n");
   	}
   	
	fclose(fi);

}

void Update(FILE *fa, Libro &libro, int IDeditorial){
	FILE *fi;
   	Indice ind;
   	bool primero = false;
	long inf, sup, n, nRegs;
   	fi = fopen("libros.ind", "rb");
   	fseek(fi, 0, SEEK_END);
   	nRegs = ftell(fi)/sizeof(Indice);
   	// Búsqueda binaria:
   	inf = 0;
   	sup = nRegs-1;
			//getline (cin,NombreLibro);
	do {
      		n = inf+(sup-inf)/2;
      		fseek(fi, n*sizeof(Indice), SEEK_SET);
      		fread(&ind, sizeof(Indice), 1, fi);
		if((ind.IDeditorial==IDeditorial)) {
                        //fseek(fa, ind.indice*sizeof(Libro), SEEK_SET);
                        cin.ignore(256,'\n' );
                        printf("Nombre: ");
                        fgets(libro.nombre, 43, stdin);
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
                        fseek(fa, ind.indice*sizeof(Libro), SEEK_SET);
                        fwrite(&libro, sizeof(Libro), 1, fa);
                        ReconstruirIndices(fa);
			primero = true;
                }

  		if(ind.IDeditorial<IDeditorial) inf = n+1;
      		else sup = n-1;
   	} while(inf <= sup /*&& (ind.IDeditorial!=IDeditorial)*/);
   	if(primero == false){
	if((ind.IDeditorial==IDeditorial)) {
     			//fseek(fa, ind.indice*sizeof(Libro), SEEK_SET);
			cin.ignore(256,'\n' );
   			printf("Nombre: ");
   			fgets(libro.nombre, 43, stdin);
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
			fseek(fa, ind.indice*sizeof(Libro), SEEK_SET);
	   		fwrite(&libro, sizeof(Libro), 1, fa);
   			ReconstruirIndices(fa);
   		}
	}
	else {
      		libro.IDeditorial = -2;
      		printf("Registro no encontrado\n");
   	}
   	
	fclose(fi);
}

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
   		if((ind.IDeditorial==IDeditorial)) {
      			fseek(fa, ind.indice*sizeof(Libro), SEEK_SET);
      			fread(&libro, sizeof(Libro), 1, fa);
        		break;
   		}
  		 else if(ind.IDeditorial<IDeditorial) inf = n+1;
      		 else sup = n-1;
   	} while(inf <= sup /*&& (ind.IDeditorial!=IDeditorial)*/);
   	if((ind.IDeditorial==IDeditorial)) {
      		fseek(fa, ind.indice*sizeof(Libro), SEEK_SET);
		cout<<"ESTE ES ind.indice: "<<ind.indice<<endl;
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
		if(libro.IDeditorial>=0)
      			printf("%s %s %s %d\n", libro.nombre, libro.autor,
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
   	while(fread(&libro, sizeof(Libro), 1, fa)){
		if(libro.IDeditorial>=0)
      			printf("%s %s %s %d\n", libro.nombre, libro.autor,
        		libro.ISBN, libro.IDeditorial);
	}
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
      		while((LeeCampo(fi, iz, cad)<mitad) /*&& iz < final*/) iz++;
      		while((LeeCampo(fi, de, cad)>mitad)/* && (de > inicio)*/) de--;
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
