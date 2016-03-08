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

struct IndiceEditorial{
	int IDeditorial;
	long indice;
};

struct Header{
	Stack<int> AvailList;
	int sizeRegistro;
};

struct HeaderEditorial{
	Stack<int> AvailList;
	int sizeRegistro;
};

void Capturar(Libro &libro);
void EliminarRetornoLinea(char *cad);
void Leer(FILE *fa, Libro &libro, int IDeditorial);
void Update(FILE *fa, Libro &libro, int IDeditorial);
void Delete(FILE *fa, Libro &libro, int IDeditorial, Header & header);
void Insertar(FILE *fa, Libro &libro);
void Mostrar(Libro &libro);
void ListarPorEditorial(FILE *fa);
void ListarNatural(FILE *fa);
void ReconstruirIndices(FILE *fa);
void Intercambia(FILE *fa, long iz, long de);
int LeeCampo(FILE *fa, long n, int buf);
void QuickSort(FILE *fa, long inicio, long final);
void CapturarEditorial(Editorial &editorial);
void LeerEditorial(FILE *fa, Editorial &editorial, int IDeditorial);
void UpdateEditorial(FILE *fa, Editorial &editorial, int IDeditorial);
void DeleteEditorial(FILE *fa, Editorial &editorial, int IDeditorial);
void InsertarEditorial(FILE *fa, Editorial &editorial);
void MostrarEditorial(Editorial &editorial);
void ListarEditorialPorEditorial(FILE *fa);
void ListarEditorialNatural(FILE *fa);
void ReconstruirIndiceEditorials(FILE *fa);
void IntercambiaEditorial(FILE *fa, long iz, long de);
int LeeCampoEditorial(FILE *fa, long n, int buf);
void QuickSortEditorial(FILE *fa, long inicio, long final);
void MostrarCruzado(Libro &libro, Editorial &editorial);
void InsertarHeader(FILE *fa, Header &header);
void LeerHeader(FILE *fa, Header &header);
void ActualizarAvailList(FILE* fa, Header &header);


int main(int argc, char** argv){
	//Libro* libro;
	Libro libro;	
	//Libro* libro2 = new Libro();
	Editorial editorial;
	int IDeditorial;
	Header header;
	cout<<"LIBRO: "<<sizeof(Libro);
	HeaderEditorial headerE;
	//if(header.AvailList.empty()==1){
	//	header.AvailList.push(0);
	//}
	cout<<"HEADER: "<<sizeof(Header);
	//Editorial* editorial;
	FILE *fa;
	FILE *fe;
	int opcion, menu;
	//string NombreLibro, ISBN, autor, NombreEditorial, direccion;
	//unsigned int IDEditorialLibro, IDEditorial; 
	//ofstream SalidaLibros("libros.bin",ios::out | ios::binary);
	fa = fopen("libros.dat", "r+b");          // Este modo permite leer y escribir
        if(!fa){
		fa = fopen("libros.dat", "w+b");  // si el fichero no existe, lo crea.
		InsertarHeader(fa, header);
	}
	LeerHeader(fa, header);
	cout<<header.AvailList.empty();
	//cout<<header.AvailList.top();
	fe = fopen("editoriales.dat", "r+b");          // Este modo permite leer y escribir
        if(!fe) fe = fopen("editoriales.dat", "w+b");  // si el fichero no existe, lo crea.
	do{
		cout<<"Ingrese su opcion: "<<endl
		<<"1) Create Book"<<endl<<"2) Read Book"<<endl
		<<"3) Update Book"<<endl<<"4) Delete Book"<<endl
		<<"5) List Books"<<endl<<"6) Create Editorial"<<endl
		<<"7) Read Editorial"<<endl<<"8) Update Editorial"<<endl
		<<"9) Delete Editorial"<<endl<<"10) List Editorials"<<endl
		<<"11) List Books By Editorial"<<endl<<"12) Reindexar Libros"<<endl
		<<"13) List Editorials by ID"<<endl<<"14) Reindexar Editoriales"<<endl
		<<"15) Listar Cruzado"<<endl<<"16) Exit"<<endl;
		cin>>menu;
		cin.ignore(256,'\n' );
		if(menu>16||menu<1){
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
			Delete(fa, libro, IDeditorial, header);
			ActualizarAvailList(fa, header);
			cin.ignore(256,'\n' );
			
		}
		if(menu==5){
			ListarNatural(fa);
		}

		if(menu==6){
			CapturarEditorial(editorial);
			InsertarEditorial(fe, editorial);
			headerE.sizeRegistro++;

		}
		if(menu==7){
			do {
				cout<<"Ingrese el ID del editorial que desea buscar"<<endl;
	       			cin>>IDeditorial;
            		} while(IDeditorial < 1);
            		LeerEditorial(fe, editorial, IDeditorial);
           		MostrarEditorial(editorial);
		}
		if(menu==8){
			do{
				cout<<"Ingrese el ID del editorial que desea modificar"<<endl;
				cin>>IDeditorial;
			}while(IDeditorial<1);	
			UpdateEditorial(fe, editorial, IDeditorial);
			cin.ignore(256,'\n' );
			
		}
		if(menu==9){
			do{
				cout<<"Ingrese el ID del editorial del libro que desea eliminar"<<endl;
				cin>>IDeditorial;
			}while(IDeditorial<1);	
			DeleteEditorial(fe, editorial, IDeditorial);
			cin.ignore(256,'\n' );

		}
		if(menu==10){
			ListarEditorialNatural(fe);
		}
		if(menu==11){
			ListarPorEditorial(fa);
		}
		if(menu==12){
			printf("Indices Reordenados");
			cout<<endl;
			ReconstruirIndices(fa);
		}
		if(menu==13){
			ListarEditorialPorEditorial(fe);
		}
		if(menu==14){
			printf("Indices Reordenados");
			
		}
		if(menu==15){
			do {
				cout<<"Ingrese el ID del editorial"<<endl;
	       			cin>>IDeditorial;
            		} while(IDeditorial < 1);
            		Leer(fa, libro, IDeditorial);
			LeerEditorial(fe, editorial, IDeditorial);
           		MostrarCruzado(libro, editorial);
		}
	}while(menu!=16);
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

	if(libro.IDeditorial > 0) {
      		printf("Nombre: %s %s %s\n", libro.nombre, libro.autor, libro.ISBN);
      		printf("Número de Editorial: %d\n", libro.IDeditorial);
   	}
   	system("PAUSE");
}
void Delete(FILE *fa, Libro &libro, int IDeditorial, Header &header){
	FILE *fi;
   	Indice ind;
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
      		fseek(fi,  (n*sizeof(Indice)), SEEK_SET);
      		fread(&ind, sizeof(Indice), 1, fi);
		if((ind.IDeditorial==IDeditorial)&&(ind.indice==0)){
			libro.IDeditorial = ind.indice*-1;
      			//fseek(fa, 0*sizeof(Header), SEEK_SET);
    			//fread(&header, sizeof(Header), 1, fa);
			//header.AvailList.push(ind.indice);
			//cout<<header.AvailList.top();
                        fseek(fa, ind.indice*sizeof(Libro)   , SEEK_SET);
                        fwrite(&libro, sizeof(Libro) , 1, fa);
                        ReconstruirIndices(fa);

		}
		if((ind.IDeditorial==IDeditorial)) {
                        //fgets(libro.IDeditorial, 5, stdin);
			libro.IDeditorial = ind.indice*-1;
      			fseek(fa, 0*sizeof(Header), SEEK_SET);
    			//fread(&header, sizeof(Header), 1, fa);
			//header.AvailList.push(ind.indice);
			//cout<<header.AvailList.top();
                        fseek(fa, ind.indice*sizeof(Libro)   , SEEK_SET);
                        fwrite(&libro,   sizeof(Libro), 1, fa);
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
      		//fseek(fa, 0*sizeof(Header), SEEK_SET);
    		//fread(&header, sizeof(Header), 1, fa);
		//header.AvailList.push(ind.indice);
		//cout<<header.AvailList.top();
		fseek(fa,  (ind.indice*sizeof(Libro)), SEEK_SET);
   		fwrite(&libro, sizeof(Libro)   , 1, fa);
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
      		fseek(fi, (n*sizeof(Indice)), SEEK_SET);
      		fread(&ind, sizeof(Indice), 1, fi);
		if((ind.IDeditorial==IDeditorial)&&(ind.indice==0)){
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
   	fseek(fi, 0 , SEEK_END);
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
		//cout<<"ESTE ES ind.indice: "<<ind.indice<<endl;
      		fread(&libro, sizeof(Libro), 1, fa);
   	}
	else{
      		libro.IDeditorial = -2;
      		printf("Registro no encontrado\n");
   	}
   	fclose(fi);
}

void Insertar(FILE *fa, Libro &libro){
   	// Insertar al final:
	int RRN = 0;
	Libro book;		
      	fseek(fa, 0+sizeof(Libro), SEEK_SET);
   	while(fread(&book, sizeof(Libro) , 1, fa)){
		if(book.IDeditorial<0){
			RRN = book.IDeditorial*-1;
			cout<<"RRN: "<<RRN<<endl;
		}
	}
	if(RRN != 0){
		fseek(fa, RRN * sizeof(Libro) , SEEK_SET);
		fwrite(&libro, sizeof(Libro), 1, fa);
		cout<<"RRN: "<<RRN<<endl;
		ReconstruirIndices(fa);
	}
	else if(RRN == 0){
		fseek(fa, 0, SEEK_END);
   		fwrite(&libro, sizeof(Libro), 1, fa);
		cout<<"RRN: "<<RRN<<endl;
   		ReconstruirIndices(fa);
	}
}

void ListarPorEditorial(FILE *fa){

	FILE *fi;
	Indice ind;
	Libro libro;
   
   	//system("cls");
   	fi = fopen("libros.ind", "rb");
   	while(fread(&ind, sizeof(Indice), 1, fi)) {
      		fseek(fa, (ind.indice*sizeof(Libro)), SEEK_SET);
      		fread(&libro, sizeof(Libro)   , 1, fa);
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
      	fseek(fa, 0+sizeof(Libro), SEEK_SET);
   	while(fread(&libro, sizeof(Libro) , 1, fa)){
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
   	while(fread(&libro, sizeof(Libro)   , 1, fa)) {
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

void CapturarEditorial(Editorial &editorial){
   	printf("Nombre: ");
   	fgets(editorial.nombre, 41, stdin);
   	EliminarRetornoLinea(editorial.nombre);
   	printf("Direccion: ");
   	fgets(editorial.direccion, 41, stdin);
   	EliminarRetornoLinea(editorial.direccion);
   	printf("ID editorial: ");
   	//fgets(editorial.IDeditorial, 5, stdin);
   	cin>>editorial.IDeditorial;
   	//EliminarRetornoLinea(editorial.IDeditorial);
}

void MostrarEditorial(Editorial &editorial){

	if(editorial.IDeditorial > 0) {
      		printf("Nombre: %s %s\n", editorial.nombre, editorial.direccion);
      		printf("Número de Editorial: %d\n", editorial.IDeditorial);
   	}
   	system("PAUSE");
}
void DeleteEditorial(FILE *fa, Editorial &editorial, int IDeditorial){
	FILE *fi;
   	IndiceEditorial ind;
	Header header;
   	long inf, sup, n, nRegs;
   	fi = fopen("editorials.ind", "rb");
   	fseek(fi, 0, SEEK_END);
   	nRegs = ftell(fi)/sizeof(IndiceEditorial);
   	// Búsqueda binaria:
   	inf = 0;
   	sup = nRegs-1;
			//getline (cin,NombreEditorial);
	do {
      		n = inf+(sup-inf)/2;
      		fseek(fi, n*sizeof(IndiceEditorial), SEEK_SET);
      		fread(&ind, sizeof(IndiceEditorial), 1, fi);
		if((ind.IDeditorial==IDeditorial)) {
                        //fgets(editorial.IDeditorial, 5, stdin);
			editorial.IDeditorial = ind.indice*-1;
			header.AvailList.push(ind.indice);
                        fseek(fa, ind.indice*sizeof(Editorial), SEEK_SET);
                        fwrite(&editorial, sizeof(Editorial), 1, fa);
                        ReconstruirIndiceEditorials(fa);
                }

  		if(ind.IDeditorial<IDeditorial) inf = n+1;
      		else sup = n-1;
   	} while(inf <= sup /*&& (ind.IDeditorial!=IDeditorial)*/);
   	if((ind.IDeditorial==IDeditorial)) {
		//cin.ignore(256,'\n' );
     		//fseek(fa, ind.indice*sizeof(Editorial), SEEK_SET);
   		//fgets(editorial.IDeditorial, 5, stdin);
		editorial.IDeditorial=ind.indice*-1;
		fseek(fa, ind.indice*sizeof(Editorial), SEEK_SET);
   		fwrite(&editorial, sizeof(Editorial), 1, fa);
   		ReconstruirIndiceEditorials(fa);
   	}
	
	else {
      		editorial.IDeditorial = -2;
      		printf("Registro no encontrado\n");
   	}
   	
	fclose(fi);

}

void UpdateEditorial(FILE *fa, Editorial &editorial, int IDeditorial){
	FILE *fi;
   	IndiceEditorial ind;
   	bool primero = false;
	long inf, sup, n, nRegs;
   	fi = fopen("editorials.ind", "rb");
   	fseek(fi, 0, SEEK_END);
   	nRegs = ftell(fi)/sizeof(IndiceEditorial);
   	// Búsqueda binaria:
   	inf = 0;
   	sup = nRegs-1;
			//getline (cin,NombreEditorial);
	do {
      		n = inf+(sup-inf)/2;
      		fseek(fi, n*sizeof(IndiceEditorial), SEEK_SET);
      		fread(&ind, sizeof(IndiceEditorial), 1, fi);
		if((ind.IDeditorial==IDeditorial)) {
                        //fseek(fa, ind.indice*sizeof(Editorial), SEEK_SET);
                        cin.ignore(256,'\n' );
                        printf("Nombre: ");
                        fgets(editorial.nombre, 43, stdin);
                        EliminarRetornoLinea(editorial.nombre);
                        printf("Autor: ");
                        fgets(editorial.direccion, 41, stdin);
                        EliminarRetornoLinea(editorial.direccion);
                        printf("ID editorial: ");
                        //fgets(editorial.IDeditorial, 5, stdin);
                        cin>>editorial.IDeditorial;
                        fseek(fa, ind.indice*sizeof(Editorial), SEEK_SET);
                        fwrite(&editorial, sizeof(Editorial), 1, fa);
                        ReconstruirIndiceEditorials(fa);
			primero = true;
                }

  		if(ind.IDeditorial<IDeditorial) inf = n+1;
      		else sup = n-1;
   	} while(inf <= sup /*&& (ind.IDeditorial!=IDeditorial)*/);
   	if(primero == false){
	if((ind.IDeditorial==IDeditorial)) {
     			//fseek(fa, ind.indice*sizeof(Editorial), SEEK_SET);
			cin.ignore(256,'\n' );
   			printf("Nombre: ");
   			fgets(editorial.nombre, 43, stdin);
   			EliminarRetornoLinea(editorial.nombre);
   			printf("Autor: ");
   			fgets(editorial.direccion, 41, stdin);
   			EliminarRetornoLinea(editorial.direccion);
   			printf("ID editorial: ");
	   		//fgets(editorial.IDeditorial, 5, stdin);
			cin>>editorial.IDeditorial;
			fseek(fa, ind.indice*sizeof(Editorial), SEEK_SET);
	   		fwrite(&editorial, sizeof(Editorial), 1, fa);
   			ReconstruirIndiceEditorials(fa);
   		}
	}
	else {
      		editorial.IDeditorial = -2;
      		printf("Registro no encontrado\n");
   	}
   	
	fclose(fi);
}

void LeerEditorial(FILE *fa, Editorial &editorial, int IDeditorial){

	FILE *fi;
   	IndiceEditorial ind;
   	long inf, sup, n, nRegs;

   	fi = fopen("editorials.ind", "rb");
   	fseek(fi, 0, SEEK_END);
   	nRegs = ftell(fi)/sizeof(IndiceEditorial);
   	// Búsqueda binaria:
   	inf = 0;
   	sup = nRegs-1;
	do {
      		n = inf+(sup-inf)/2;
      		fseek(fi, n*sizeof(IndiceEditorial), SEEK_SET);
      		fread(&ind, sizeof(IndiceEditorial), 1, fi);
   		if((ind.IDeditorial==IDeditorial)) {
      			fseek(fa, ind.indice*sizeof(Editorial), SEEK_SET);
      			fread(&editorial, sizeof(Editorial), 1, fa);
        		break;
   		}
  		 else if(ind.IDeditorial<IDeditorial) inf = n+1;
      		 else sup = n-1;
   	} while(inf <= sup /*&& (ind.IDeditorial!=IDeditorial)*/);
   	if((ind.IDeditorial==IDeditorial)) {
      		fseek(fa, ind.indice*sizeof(Editorial), SEEK_SET);
		cout<<"ESTE ES ind.indice: "<<ind.indice<<endl;
      		fread(&editorial, sizeof(Editorial), 1, fa);
   	}
	else {
      		editorial.IDeditorial = -2;
      		printf("Registro no encontrado\n");
   	}
   	fclose(fi);
}

void InsertarEditorial(FILE *fa, Editorial &editorial){
   	// Insertar al final:
	fseek(fa, 0, SEEK_END);
   	fwrite(&editorial, sizeof(Editorial), 1, fa);
   	ReconstruirIndiceEditorials(fa);
}

void ListarEditorialPorEditorial(FILE *fa){

	FILE *fi;
	IndiceEditorial ind;
	Editorial editorial;
   
   	//system("cls");
   	fi = fopen("editorials.ind", "rb");
   	while(fread(&ind, sizeof(IndiceEditorial), 1, fi)) {
      		fseek(fa, ind.indice*sizeof(Editorial), SEEK_SET);
      		fread(&editorial, sizeof(Editorial), 1, fa);
		if(editorial.IDeditorial>=0)
      			printf("%s %s %d\n", editorial.nombre, editorial.direccion,
        		editorial.IDeditorial);
   	}
   	fclose(fi);
   	//system("PAUSE");
}

// Lista todos los registros del archivo de datos por el orden en que se
// insertaron.
void ListarEditorialNatural(FILE *fa){

	Editorial editorial;
   
   	rewind(fa);
   	//system("cls");
   	while(fread(&editorial, sizeof(Editorial), 1, fa)){
		if(editorial.IDeditorial>=0)
      			printf("%s %s %d\n", editorial.nombre, editorial.direccion,
        		editorial.IDeditorial);
	}
   	//system("PAUSE");
}

// Reconstruye el archivo de índices
void ReconstruirIndiceEditorials(FILE *fa){
	long n=0;
   	FILE *fi;
   	Editorial editorial;
   	IndiceEditorial ind;
   
   	// Crea el fichero de índices 
   	fi = fopen("editorials.ind", "w+b");
   	rewind(fa);
   	while(fread(&editorial, sizeof(Editorial), 1, fa)) {
      		//strcpy(ind.IDeditorial, editorial.IDeditorial);
      		ind.IDeditorial=editorial.IDeditorial;
      		ind.indice = n++;
      		fwrite(&ind, sizeof(IndiceEditorial), 1, fi);
   	}
   	// Ordena usando el algoritmo Quicksort:
   	QuickSortEditorial(fi, 0, n-1);
   	fclose(fi);
}

void QuickSortEditorial(FILE *fi, long inicio, long final){
	long iz, de;
   	//char mitad[10];
   	//static char cad[10];
   	int mitad;
   	static int cad;

   	iz = inicio;
   	de = final;
   	//strcpy(mitad, LeeCampoEditorial(fi, (iz+de)/2, cad));
   	mitad = LeeCampoEditorial(fi, (iz+de)/2, cad);
   	do {
      		while((LeeCampoEditorial(fi, iz, cad)<mitad) /*&& iz < final*/) iz++;
      		while((LeeCampoEditorial(fi, de, cad)>mitad)/* && (de > inicio)*/) de--;
      		if(iz < de) IntercambiaEditorial(fi, iz, de);
      			if(iz <= de) {
         			iz++;
         			de--;
     		 }
   	} while(iz <= de);
   	if(inicio < de) QuickSortEditorial(fi, inicio, de);
   	if(iz < final) QuickSortEditorial(fi, iz, final);

}

int LeeCampoEditorial(FILE *fi, long n, int buf){

   	IndiceEditorial ind;

   	fseek(fi, n*sizeof(IndiceEditorial), SEEK_SET);
   	fread(&ind, sizeof(IndiceEditorial), 1, fi);
   	//strcpy(buf, ind.IDeditorial);
   	buf = ind.IDeditorial;
   	return buf;
}

void IntercambiaEditorial(FILE *fi, long iz, long de){
   
	IndiceEditorial editorial1, editorial2;

   	fseek(fi, iz*sizeof(IndiceEditorial), SEEK_SET);
   	fread(&editorial1, sizeof(IndiceEditorial), 1, fi);
   	fseek(fi, de*sizeof(IndiceEditorial), SEEK_SET);
   	fread(&editorial2, sizeof(IndiceEditorial), 1, fi);
   	fseek(fi, iz*sizeof(IndiceEditorial), SEEK_SET);
   	fwrite(&editorial2, sizeof(IndiceEditorial), 1, fi);
	fseek(fi, de*sizeof(IndiceEditorial), SEEK_SET);
	fwrite(&editorial1, sizeof(IndiceEditorial), 1, fi);
}

void MostrarCruzado(Libro &libro, Editorial &editorial){

	if(libro.IDeditorial > 0) {
      		printf("Nombre de Libro: %s Nombre de Editorial: %s\n", libro.nombre, editorial.nombre);
      		printf("Número de Editorial: %d\n", libro.IDeditorial);
   	}
   	system("PAUSE");
}

void InsertarHeader(FILE *fa, Header &header){
	fseek(fa, 0, SEEK_END);
   	fwrite(&header, sizeof(Header)+72, 1, fa);
   	//ReconstruirIndices(fa);
}
void LeerHeader(FILE *fa, Header &header){
      	//fseek(fa, 0*sizeof(Header), SEEK_SET);
    	//fread(&header, sizeof(Header), 1, fa);
	//cout<<header.AvailList.empty();
	//if(header.AvailList.empty()!=1){
	//	cout<<header.AvailList.top();
	//}
}
void ActualizarAvailList(FILE* fa, Header &header){
	fseek(fa, 0, SEEK_SET);
	fwrite(&header, sizeof(Header)+72, 1, fa);
}
