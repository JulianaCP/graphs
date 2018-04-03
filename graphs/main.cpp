#include <iostream>
#include <fstream> 
#include <string.h>
# include<conio.h>
#include<stack>
#include <iomanip>
#include<queue>


using namespace std;

queue<string>colaElementosGrafo;


fstream archivosArco("ArchivosArcos.txt",ios::in | ios::out | ios::binary);


struct vertice{
	string nombreCiudad;
	string color;
	bool visitado;
	struct vertice *sigVertice;
	struct arco *primerElementoListaArcos;
	
	vertice (string nombreCiuda){
		nombreCiudad = nombreCiuda;
		visitado = false;
		sigVertice = NULL;
		color = "";
		primerElementoListaArcos = NULL;
		
	}
}*primerElementoDeGrafo;

struct arco{
	struct vertice *destino;
	string origen;
	int distancia;
	int velocidadMaximaArco;
	bool dirigido;
	bool habilitado;
	bool visitado;
	string destinoArco;
	struct arco *sigArco;
	arco(struct vertice * enlaceDestinoDelVertice, int distance, bool dirigi, int velocidadMax, string desti, string orige){
		destino = enlaceDestinoDelVertice;
		distancia = distance;
		sigArco= NULL;
		dirigido = dirigi;
		destinoArco = desti;
		velocidadMaximaArco = velocidadMax;
		origen = orige;
		visitado = false;
		habilitado = true;
	}
};


struct archivosArco{
	char ciudadOrigen[20];
	char ciudadDestino[20];
	int distancia;
	int velocidad;
	char dirigido[20];
	char habilitado[1];
}registroArcos;


struct archivoConductores{
	int registro;
	int izquierda;
	int identificacion;
	char nombreDelChofer[20];
	char tipoDeVehiculo[20];
	int enlaceArchivoDeRutas;
	int derecha;
	
};

struct nombre{
	char nomb[20];
	
};

struct archivoRutas{
	
	struct nombre nombresDeLasCiudadesAsociadasAChofer[11];
	int siguiente;
};

struct arbolSubListaRutas{
	struct arbolSubListaRutas *sig;
	struct arbol *elementosArbol;

	
	arbolSubListaRutas(){
		sig = NULL;
		elementosArbol = NULL;
	}
};


struct arbol{
	string ciudad;
	int contador;
	struct arbol *sig;
	struct arbolSubListaRutas *arbolPrimerElementoRuta;
	
	arbol(string nombreCiudad,int cont){
		sig = NULL;
		contador= cont;
		arbolPrimerElementoRuta = NULL;
		ciudad = nombreCiudad;
	}
}*raiz;




//////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////

//menus
void menu();
void menuRutas(); 
void menuConductores();
void menuVertice();
void menuArcos();
void menuReportes();
void menuConsultas();
void menuModificarArcos();



//////////////////////
//vertice

struct vertice *buscarVertice(string);
void pedrrInformacionVertice();
void verificarExisteVertice(string);
void insertarVertice(string);


/////////////////////
//arco

void pedirInformacionArco();
void verificarExisteArco(string,int,string,int,bool);
void insertarArco(string,int,string,int,bool);

///////////////////
//modificarDatos

void modificarDistanciaArco();
void modificarVelocidadMaxCamino();
void modificarVerticeNombreCiudad();


///////////////////
//borrar Datos

void borrarArco();
void eliminarArcosQueLleganAlVerticeEliminar(struct vertice, string);
void eliminarArcosQueSalenDelVertice(struct vertice,string);
void eliminarVerticeNoTieneArcos(struct vertice,string);
void eliminarVertice();


//////////////////
// archivos arcos y vertices

void guardarDatosArchivoArcoYVertices();
void cargarDatosDelArchivoVertices();
 

/////////////////
//consultas

//conexo
void hayArco(struct vertice,string);
void desmarcarVisitasCiudades();
void grafoTransporteEsConexo();

//colores
void imprimirVerticesArcosColores();
void actualizarColoresGrafo();


//impresion una vez por vertice
void limpiarCola();
bool comprobarUltimoElemento(string);
void almacenarEnCola(struct vertice);
bool verificarTodosTienenUnArcoGrafo();
bool verificarSoloInicioYFinalTienen1();
bool verificacionCantidadVertices();
void imprimirPasandoUnaVezPorVerticesPasoRestricciones(struct vertice);
void imprimirPasandoUnaVezPorVertices();

// registro conductores y rutas
int insertarRutaAConductor(long identificacion);
void cambiarFinalRutaAConductor(int identificacion, int ruta);
int contarCantidadDeRegistrosConductor();
void pedirDatosRutaAConductor();
long registrosDelArchivoIndexado();
void imprimirArchivoIndexadoConductores();
void insertarEnArchivoConductoresIndexado();


//rutas
void modificarSiguienteRuta(long posModificar,long siguienteRegistro);
void pedirDatosModificarSiguienteRuta();
int contarCantidadDeRegistros();
void imprimirArchivoRutas();
void escribirDatosEnArchivoRutas();



//consulta de personas que viajan a x
void todasLasRutasUsuarioX(int );


// rutaCorta
void imprimirRutaCorta();
void buscarRutaAB(struct vertice, string ,int );
void rutaMasCortaEntrePuntoABDatos();


//pila
void pop();
void insertar(string, int);
void igualar();


//tiempoMasCorto

void TiempoMasCorto(struct vertice , string,float);
void tiempoMinimoDeCiudadABDatos();

//cantidad de visitas a x

void cantidadDeUsuariosViajanCiudadX(string);
void pedirInformacionCantidadDeUsuariosViajaX();
void pedirInformacionTodasLasRutasUsuarioX();


//ruta de lo del arbol
void rutas(struct vertice, string,struct arco, struct vertice ,string); 
void imprimirArbol(struct arbol);
void inserte( struct arbolSubListaRutas,string,int);
void crearArbol(string);



//cerrar arco e imprimir ruta
struct arco *retornarArco(struct vertice,string);
void indicarCualArcoDeseaDejar();


//una vez por arco

void metodoUnaVezPorArco(struct vertice);
void comprobarRestriccionesUnaVezPorArco();
bool verificarCantidadDeArcosMetodoUnaVezPorArco();
void desmarcarVisitasArcos();




///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void amplitud(){
	
	//entradas: NO
	//salida: NO
	//descripcion: se encarga de imprimir el grafo segun los estandares de amplitud meadiante un recorrido del mismo

	
	
	struct vertice *tempVertice = primerElementoDeGrafo;
	struct arco *tempArco;
	cout<<"\n\n.............Recorrido en Amplitud...........\n";
	while(tempVertice != NULL){
		cout<<"\n\nNombre de la ciudad: "<<tempVertice->nombreCiudad;
		cout<<"\nSus arcos son: ";
		tempArco = tempVertice->primerElementoListaArcos;
		while(tempArco != NULL){
			cout<<tempVertice->nombreCiudad;
			cout<<tempArco->destino->nombreCiudad;
			cout<<tempArco->distancia<<",  ";
			
			tempArco = tempArco->sigArco;
		}
		tempVertice = tempVertice->sigVertice;
	}
}






//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct vertice * buscarVertice(string nombreCiudad){


	//entradas: recibe el nombre de una ciudad
	//salida: se retorna la estrucura del vertice, con todos los atributos de la misma
	//descripcion: se encarga de recorrer el grafo buscado la existencia de la ciudad ingresada por parametro, retorna resultados
	
	
	struct vertice * temp = primerElementoDeGrafo;
	
	while ( temp != NULL){
		if(temp->nombreCiudad == nombreCiudad)
			return temp;
		
		temp = temp->sigVertice;
	}
	return NULL;
}

void pedirInformacionVertice(){
	
		//entradas:  obtiene el nombre de la ciudad a crear por medio del usuario
	//salida: 
	//descripcion: solicita el nombre de la ciudad en consola, obteniendola por medio el usuario
	
	
	
	string nombre;
	cout<<"nombre de la ciudad: ";
	cin>>nombre;
	
	verificarExisteVertice(nombre);
}

void verificarExisteVertice(string nombreCiudad){
	
	//entradas:  
	//salida: 
	//descripcion: se encarga de verificar si el vertice existe o no , mediante el llamado a la funcion
	
	
	
	
	struct vertice * existeVertice = buscarVertice(nombreCiudad);
	
	if(existeVertice!= NULL){
		cout<<"\n";
		cout<<"El lugar ya se encuentra en la ciudad.\n";
		cout<<"\n";
		menu();
	}
	else{
		cout<<"\n";
		insertarVertice(nombreCiudad);
		cout<<"Dato creado con exito.\n";		
	}
	
}


void insertarVertice(string nombreCiudad){

	
	//entradas:  recibe el nombre de la ciudad
	//salida: 
	//descripcion: se encarga de enlazar el nuevo elemento perteneciente al grafo
	
	
    struct vertice * nn = new vertice(nombreCiudad);
	nn->sigVertice = primerElementoDeGrafo;
	primerElementoDeGrafo = nn;
	
}

void pedirInformacionArco(){




	//entradas:  obtiene el nombre del arco a crear por medio del usuario
	//salida: 
	//descripcion: solicita el nombre del arco en consola, obteniendola por medio el usuario


	bool estaIgual = false;
	
	int distancia;
	string destino;
	int velocidadVia;
	string StringtipoDeArco;
	string origen;
	cout<<"\n\n";
	cout<<"Informacion Nombre Ciudad Origen:  ";
	cin>>origen;
	cout<<"Informacion Nombre Ciudad Destino:  ";
	cin>>destino; 
	cout<<"distancia de via:  ";
	cin>>distancia;
	cout<<"Velocidad maxima via:  ";
	cin>>velocidadVia;
	cout<<"tipo (dirigido) o (no_dirigido):  ";
	cin>>StringtipoDeArco;
	
	if(StringtipoDeArco == "dirigido" or StringtipoDeArco == "no_dirigido"){
		
		estaIgual = true;
		bool esDirigido = false;
		if(StringtipoDeArco == "dirigido"){
			esDirigido = true;
		}
		verificarExisteArco(origen, distancia,destino,velocidadVia,esDirigido);
	}
	else if(estaIgual == false){
		cout<<"\n\n";
		cout<<"Debe escribir el tipo de arco segun se indica en pantalla";
		cout<<"\n\n";
		menu();		
	}
	
}


void verificarExisteArco(string origen, int distancia, string destino, int velocidadVia, bool tipoDeArco){


	//entradas: recibe la informacion del arco obtenida por el usuario  
	//salida: 
	//descripcion: se encarga de verificar si el arco existe o no , mediante el llamado a la funcion
	
	struct vertice * tempVerticeOrigen = buscarVertice(origen);
	struct vertice * tempVerticeDestinoArco = buscarVertice(destino);
	
	if((tempVerticeOrigen == NULL) or (tempVerticeDestinoArco == NULL)){
		cout<<"\n\n";
		cout<<"Alguno de los datos ingresados no existe\n";
		menu();
	}
	else{
		
		
		if(tipoDeArco == false){
//			cout<<"false";
			insertarArco( origen,  distancia,  destino,  velocidadVia,  tipoDeArco);
			cout<<"\n\n";
			cout<<"Arco Creado con exito";
			cout<<"\n\n";
		}
		else{
			
			cout<<"true";
			insertarArco( origen,  distancia,  destino,  velocidadVia,  tipoDeArco);
			insertarArco( destino,  distancia,  origen,  velocidadVia,  tipoDeArco);
			cout<<"\n++++++++++++++++++++++\n";
			cout<<"Arco Creado con exito";
			cout<<"\n\n";
		}
		
	}
	
}

void insertarArco(string origen, int distancia, string destino, int velocidadVia, bool tipoDeArco){


	//entradas:  recibe la informacion correspondiente al arco
	//salida: 
	//descripcion: se encarga de enlazar el nuevo elemento perteneciente al grafo



	struct vertice * tempVerticeOrigen = buscarVertice(origen);
	struct vertice * tempVerticeDestinoArco = buscarVertice(destino);
	struct arco * nn = new arco (tempVerticeDestinoArco, distancia, tipoDeArco, velocidadVia, destino,origen);
	nn->sigArco = tempVerticeOrigen->primerElementoListaArcos;
	tempVerticeOrigen->primerElementoListaArcos = nn;
}





void modificarDistanciaArco(){
	

	//entradas:  obtiene los datos necesarios por medio del usuario
	//salida: 
	//descripcion: solicita los vertices en consola, obteniendola por medio el usuario y se encarga de verificar si existe
	// ademas de realizar el cambio si encuentra una coinsidencia en el arco segun los datos introducidos



	string nombreCiudadOrigen;
	string nombreCiudadDestino;
	cout<<"Digite el nombre de la ciudad origen del camino: ";
	cin>> nombreCiudadOrigen;
	cout<<"Digite el nombre de la ciudad destino: ";
	cin>>nombreCiudadDestino;
	
	
	int nuevaDistancia;
	
	cout<<"Digite la nueva distancia del camino: ";
	cin>>nuevaDistancia;
	
	
	
	struct vertice * tempExisteVerticeOrigen = buscarVertice(nombreCiudadOrigen);
	struct vertice * tempExisteVerticeDestino = buscarVertice(nombreCiudadDestino);
	
	if(tempExisteVerticeDestino == NULL or tempExisteVerticeOrigen == NULL){
		cout<<"\n\n";
		cout<<"Alguno de los datos ingresados no son correctos... intente de nuevo";
		cout<<"\n\n";
		menu();
	}
	else{
	
		struct arco * temp = tempExisteVerticeOrigen->primerElementoListaArcos;
		
		
		bool hayArco = false;
		while(temp!=NULL){
			
			if(temp->destino->nombreCiudad == nombreCiudadDestino){
				
				cout<<endl;
				cout<<"   Distancia: " << temp->distancia<<endl;
					cout<<" Origen: " << nombreCiudadOrigen<<endl;
					
				
				temp->distancia = nuevaDistancia;
				
	
					cout<<"  destino " << temp->destino->nombreCiudad<<endl;
					cout<<"  Nueva Distancia: " << temp->distancia<<endl;
					
				
				
				if(hayArco == false){
					hayArco = true;
				}
					
					
					//cout<<"\n";
				
				
			}
			temp= temp->sigArco;
				
		}
		
		if(hayArco == true){
			cout<<"\n\n";
			cout<<"Cambio realizado con exito";
			cout<<"\n\n";
			//menu
		}
		else{
			cout<<"\n\n";
			cout<<"no se pudo encontrar el camino";
		    cout<<"\n\n";
		}
	}
}




void modificarVelocidadMaxCamino(){



	//entradas:  obtiene los datos necesarios por medio del usuario
	//salida: 
	//descripcion: solicita los vertices en consola, obteniendola por medio el usuario y se encarga de verificar si existe
	// ademas de realizar el cambio si encuentra una coinsidencia en el arco segun los datos introducidos



	string nombreCiudadOrigen;
	string nombreCiudadDestino;
	cout<<"Digite el nombre de la ciudad origen del camino: ";
	cin>> nombreCiudadOrigen;
	cout<<"Digite el nombre de la ciudad destino: ";
	cin>>nombreCiudadDestino;
	
	
	int nuevaValocidadMaxima;
	
	cout<<"Digite la nueva velocidad maxima del camino: ";
	cin>>nuevaValocidadMaxima;	
	
	
	struct vertice * tempVerticeOrigen = buscarVertice(nombreCiudadOrigen);
	struct vertice * tempVerticeDestino = buscarVertice(nombreCiudadDestino);

	if(tempVerticeOrigen == NULL or tempVerticeDestino == NULL){
	cout<<"\n\n";
		cout<<"Alguno de los datos ingresados no son correctos... intente de nuevo";
		cout<<"\n\n";
		menu();
	}
	else{
		
		struct arco * temp = tempVerticeOrigen->primerElementoListaArcos;
		
		bool hayArco = false;
		while(temp!=NULL){
			if(temp->destino->nombreCiudad == nombreCiudadDestino){
				
				cout<<endl;
				cout<<"Velocidad Actual: " << temp->velocidadMaximaArco <<endl;
								
					cout<<"Origen: " << nombreCiudadOrigen<<endl;
					
				
				temp->velocidadMaximaArco = nuevaValocidadMaxima;
				if(hayArco == false){
					hayArco = true;
				}

					cout<<"destino: " << temp->destino->nombreCiudad<<endl ;
					cout<<"nueva velocidad: " << temp->velocidadMaximaArco<<endl ;
					
				
			

				
			}
			temp = temp->sigArco;
		}
		
		if(hayArco == true){
			cout<<"\n\n";
			cout<<"Cambio realizado con exito";
			//menu
		}
		else{
			cout<<"\n\n";
			cout<<"no se pudo encontrar el camino";
		    cout<<"\n\n";
		}
	}
}




void modificarVerticeNombreCiudad(){

	
	//entradas:  obtiene los datos necesarios por medio del usuario
	//salida: 
	//descripcion: solicita el nombre del vertice, obteniendola por medio el usuario y se encarga de verificar si existe
	// ademas de realizar el cambio si encuentra una coinsidencia  segun los datos introducidos



	
	string antiguoNombreCiudad;
	string nuevoNombreCiudad;
	cout<<"Digite el nombre anterior de la ciudad: ";
	cin>> antiguoNombreCiudad;
	cout<<"Digite el nuevo de la ciudad: ";
	cin>>nuevoNombreCiudad;
	
	struct vertice * tempVerticeCiudad = buscarVertice(antiguoNombreCiudad);
	struct vertice * tempVerticeNuevo = buscarVertice(nuevoNombreCiudad);
	
	if(tempVerticeCiudad == NULL){
		cout<<"\n";
		cout<<"La ciudad no existe.... intente de nuevo"<<endl;
		cout<<"\n";
		menu();
	}
	if(tempVerticeNuevo!=NULL){
		cout<<"\n";
		cout<<"El nuevo nombre ya existe.. intente de nuevo"<<endl;
		cout<<"\n";
		menu();
	}
	else{
	
		struct vertice * temp = primerElementoDeGrafo;
		
		
		while(temp!=NULL){
			if(temp->nombreCiudad == antiguoNombreCiudad){
				temp->nombreCiudad = nuevoNombreCiudad;
			} 
			temp = temp->sigVertice;
		}
		cout<<"\n";
		cout<<"Dato cambiado con exito";
		cout<<"\n";
		//menu
	}
		
}



void borrarArco(){

	
	//entradas:  obtiene los datos necesarios por medio del usuario
	//salida: 
	//descripcion: solicita el los vertices del arco, obteniendola por medio el usuario y se encarga de verificar si existe
	// ademas de realizar el arco si encuentra una coinsidencia  segun los datos introducidos
	


	
	string nombreCiudadOrigen;
	string nombreCiudadDestino;
	
	cout<<"Digite el nombre de la ciudad origen: ";
	cin>>nombreCiudadOrigen;
	cout<<"Digite el nombre de la ciudad destino; ";
	cin>>nombreCiudadDestino;

	struct vertice * tempVerticeOrigen = buscarVertice(nombreCiudadOrigen);
	struct vertice * tempVerticeDestino = buscarVertice(nombreCiudadDestino);
	
	if(tempVerticeDestino == NULL or tempVerticeOrigen == NULL){
		cout<<"\n\n";
		cout<<"Alguno de los datos ingresados no existe...intente de nuevo";
		cout<<"\n\n";
		menu();
	}
	else{
		
		struct arco * temp = tempVerticeOrigen->primerElementoListaArcos;
		
		
		bool existeArco = false;
		
		while(temp!=NULL){
			if(temp->destino->nombreCiudad == nombreCiudadDestino){
				existeArco = true;				
			}
			temp = temp->sigArco;
		}
		
		if(existeArco == false){
			cout<<"\n\n";
			cout<<"El camino asignado no existe"<<endl;
			cout<<"\n\n";
			menu();
		}
		else{
		
		
			struct arco * tempAnterior;
			temp = tempVerticeOrigen->primerElementoListaArcos;
			
			if(temp->destino->nombreCiudad == nombreCiudadDestino && temp->sigArco == NULL){
				tempVerticeOrigen->primerElementoListaArcos = NULL;
			}
			else if(temp->destino->nombreCiudad == nombreCiudadDestino ){
				tempVerticeOrigen->primerElementoListaArcos = temp->sigArco;
				delete temp;
			}
			else{
				while(temp!=NULL){
					if(temp->destino->nombreCiudad == nombreCiudadDestino){
						tempAnterior->sigArco = temp->sigArco;
						delete temp;
					}
					else{
						tempAnterior = temp;
						temp = temp->sigArco;
					}
				}

				//menu		
			}	
			
				cout<<"\n\n";
				cout<<"Dato eliminado con exito"<<endl;	
				cout<<"\n\n";	
		}
	}
}



void eliminarArcosQueLleganAlVerticeEliminar(struct vertice * tempVerticeNombreCiudad, string nombreCiudadEliminar){



	
	//entradas:  obtiene los datos necesarios por medio del usuario
	//salida: 
	//descripcion: recorre el grafo buscando relacion con el vertice obtenido 
	// ademas de realizar la eliminacion de los arcos que llegan al vertice que se va a eliminar
	
	
	
	struct vertice * tempEliminarArcosEntranEnVertice = primerElementoDeGrafo;
	
	while(tempEliminarArcosEntranEnVertice!=NULL){
		
		if(tempEliminarArcosEntranEnVertice == tempVerticeNombreCiudad){
		
			tempEliminarArcosEntranEnVertice = tempEliminarArcosEntranEnVertice->sigVertice;
			continue;
		}
		else{
			
			struct arco * tempArcosEliminarArcosEntranEnVertice = tempEliminarArcosEntranEnVertice->primerElementoListaArcos;
			while(tempArcosEliminarArcosEntranEnVertice!=NULL){
				
				if(tempArcosEliminarArcosEntranEnVertice->destino->nombreCiudad == nombreCiudadEliminar){
						
						struct arco * tempAnterior;
						struct arco * temp = tempEliminarArcosEntranEnVertice->primerElementoListaArcos;
						
						if(temp->destino->nombreCiudad == nombreCiudadEliminar && temp->sigArco == NULL){
							
							tempEliminarArcosEntranEnVertice->primerElementoListaArcos = NULL;
							delete temp;
						}
						else if(temp->destino->nombreCiudad == nombreCiudadEliminar ){
							tempEliminarArcosEntranEnVertice->primerElementoListaArcos = temp->sigArco;
							delete temp;
							
						}
						else{
							
							while(temp!=NULL){
							
								if(temp->destino->nombreCiudad == nombreCiudadEliminar){
								
									tempAnterior->sigArco = temp->sigArco;
									delete temp;
									break;
								}
								else{
							
									tempAnterior = temp;
									temp = temp->sigArco;
								}
							}			
						}
				}
		
				tempArcosEliminarArcosEntranEnVertice = tempArcosEliminarArcosEntranEnVertice->sigArco;
			}
		
			tempEliminarArcosEntranEnVertice = tempEliminarArcosEntranEnVertice->sigVertice;
		}
	}
}



void eliminarArcosQueSalenDelVertice(struct vertice * tempVerticeNombreCiudad, string nombreCiudadEliminar){


	//entradas:  obtiene los datos necesarios por medio del usuario
	//salida: 
	//descripcion: recorre el grafo buscando relacion con el vertice obtenido
	// ademas de realizar la eliminacion de los arcos que salen del vertice que se va a eliminar
		
	
	
	int cont = 0;
	struct arco * tempArcoCantidadElementos = tempVerticeNombreCiudad->primerElementoListaArcos;
	while(tempArcoCantidadElementos!=NULL){
		
		cont= cont + 1;
		tempArcoCantidadElementos = tempArcoCantidadElementos ->sigArco;
	}
	
	
	int cont2 =0;
	for(int i=0; i<cont ; i++){
		cont2++;
		
		struct arco * tempArcoCicloEliminar =  tempVerticeNombreCiudad->primerElementoListaArcos;
		if(tempArcoCicloEliminar == NULL){
			break;
		}
		tempVerticeNombreCiudad->primerElementoListaArcos = tempArcoCicloEliminar->sigArco;
		delete tempArcoCicloEliminar;
		
	}
	

	
	if(tempVerticeNombreCiudad->primerElementoListaArcos  == NULL){
	//	cout<<"si elimino arcos     ";
			cout<<cont2;
		
	}	
}



void eliminarVerticeNoTieneArcos(struct vertice * tempVerticeNombreCiudad, string nombreCiudadEliminar){
	
	//entradas:  obtiene los datos necesarios por medio del usuario
	//salida: 
	//descripcion: recorre el grafo buscando relacion con el vertice obtenido
	// ademas de realizar la eliminacion del vertice que no tiene arcos	
		
	
	
	struct vertice * tempVerticeGrafo = primerElementoDeGrafo;
	
	
	if(tempVerticeGrafo->nombreCiudad == nombreCiudadEliminar &&  tempVerticeGrafo->sigVertice == NULL){
	
		primerElementoDeGrafo = NULL;
		delete tempVerticeGrafo;
		return;
	}
	if(tempVerticeGrafo->nombreCiudad == nombreCiudadEliminar &&  tempVerticeGrafo->sigVertice != NULL){
	
		primerElementoDeGrafo = tempVerticeGrafo->sigVertice;
		delete tempVerticeGrafo;
		return;
	}	
	
	struct vertice * tempVerticeAnterior;
	while(tempVerticeGrafo != NULL){
		if(tempVerticeGrafo->nombreCiudad == nombreCiudadEliminar){
			tempVerticeAnterior->sigVertice = tempVerticeGrafo->sigVertice;
			delete tempVerticeGrafo;
			break;
		}
		tempVerticeAnterior = tempVerticeGrafo;
		tempVerticeGrafo = tempVerticeGrafo ->sigVertice;
	}
	
	// SOLO VERIFICACION DE QUE LO ELIMINO
	struct vertice * prueba = buscarVertice(nombreCiudadEliminar);
	if(prueba == NULL){
	//	cout<<"         si vertice";
	}	
}





void eliminarVertice(){


	//entradas:  obtiene los datos necesarios por medio del usuario
	//salida: 
	//descripcion: se encarga de verificar que el vertice exita, ademas de llamar a las funciones que se encargan de eliminar el vertice
	
	
	
	string nombreCiudadEliminar;
	
	cout<<"Digite el nombre de la ciudad a eliminar: ";
	cin>>nombreCiudadEliminar;
	
	
	struct vertice * tempVerticeNombreCiudad = buscarVertice(nombreCiudadEliminar);
	
	if(tempVerticeNombreCiudad == NULL){
		cout<<"\n\n";
		cout<<"Datos inconsistentes ciudad no encontrada.... intente de nuevo"<<endl;
		menu();
		
	}
	else{

			eliminarArcosQueLleganAlVerticeEliminar(tempVerticeNombreCiudad,nombreCiudadEliminar);
			
			eliminarArcosQueSalenDelVertice(tempVerticeNombreCiudad,nombreCiudadEliminar);
			
			
			eliminarVerticeNoTieneArcos(tempVerticeNombreCiudad, nombreCiudadEliminar);		
			cout<<"\n\n";

			cout<<"dato eliminado con exito";
	}
} 



void guardarDatosArchivoArcoYVertices(){

	

	//entradas:  
	//salida: 
	//descripcion: se encarga de recorrer el grafo almacenando cada uno de los elementos en el archivo
	



	fstream archivosArco("ArchivosArcos.txt",ios::in | ios::out | ios::binary | ios::trunc );
	struct vertice * tempVertices = primerElementoDeGrafo;
	while(tempVertices !=NULL){
		struct arco * arcosDeVertice =  tempVertices-> primerElementoListaArcos;
		while(arcosDeVertice != NULL){
			struct archivosArco nuevoDatoArchivo;			
			//strcpy(nuevoDatoArchivo.ciudadDestino,"");
			std::string stringNombreCiudadDestino = arcosDeVertice->destino->nombreCiudad;;
			const char * nombreCiudadDestino = stringNombreCiudadDestino.c_str();
//				cout<<nombreCiudadDestino;
			strcpy(nuevoDatoArchivo.ciudadDestino, nombreCiudadDestino);
//				cout<<"\n\nDestino: "<<nombreCiudadDestino;
//				cout<<"\n\ndestino de archivo: "<<nuevoDatoArchivo.ciudadDestino;
			//	strcpy(nuevoDatoArchivo.ciudadOrigen,"");
			std::string stringNombreCiudadOrigen =  tempVertices->nombreCiudad;
			const char * nombreCiudadOrigen = stringNombreCiudadOrigen.c_str();
			strcpy(nuevoDatoArchivo.ciudadOrigen, nombreCiudadOrigen);		
			//strcpy(nuevoDatoArchivo.dirigido,"");
			string stringDirigido = "no_dirigido";
			bool dirigido = arcosDeVertice->dirigido;
			bool habilitado = arcosDeVertice->habilitado;
			string stringHabilitado = "S";
			if(dirigido == true){
				stringDirigido = "dirigido";
			}
			if(habilitado != true)
			{
				stringHabilitado = "N";
			}
			std::string stringDirigidoToArchivo =  stringDirigido;
			std::string stringHabilitadoToArchivo =  stringHabilitado;
			const char * charDirigido = stringDirigidoToArchivo.c_str();
			const char * charHabilitado = stringHabilitadoToArchivo.c_str();
			strcpy(nuevoDatoArchivo.dirigido, charDirigido);
			strcpy(nuevoDatoArchivo.habilitado, charHabilitado);
			nuevoDatoArchivo.distancia = arcosDeVertice->distancia;
			nuevoDatoArchivo.velocidad = arcosDeVertice->velocidadMaximaArco;
			archivosArco.write(reinterpret_cast<char * > (&nuevoDatoArchivo) , sizeof(nuevoDatoArchivo));
			arcosDeVertice = arcosDeVertice->sigArco;
		}
		tempVertices = tempVertices->sigVertice;
	}
}





void cargarDatosDelArchivoVertices(){
	
	

	//entradas:  
	//salida: 
	//descripcion: se encarga de crear elementos del grafo por cada uno de los elementos del archivo, sin repetir datos
		
	
	
	fstream arhivoArcos("ArchivosArcos.txt",ios::in | ios::out | ios::binary );	
	struct archivosArco tempArchivoArco;
	arhivoArcos.seekg(0,ios::beg);
	arhivoArcos.read(reinterpret_cast<char *>(&tempArchivoArco),sizeof(tempArchivoArco));	
	while(!arhivoArcos.eof()){
		
		string nombreCiudadOrigen = tempArchivoArco.ciudadOrigen;
		string nombreCiudadDestino = tempArchivoArco.ciudadDestino;
//		cout<<tempArchivoArco.ciudadOrigen<<endl;
//		cout<<nombreCiudadDestino<<endl;
		
		string stringDirigido = tempArchivoArco.dirigido;
		string stringHabilitado = tempArchivoArco.habilitado;
		bool dirigido = false;
		bool habilitado = true;
		if(stringDirigido == "dirigido"){
			dirigido = true;
		}
		if(stringHabilitado == "N"){
			habilitado = false;
		}
		int distancia = tempArchivoArco.distancia;
		int veelocidadMaxArco = tempArchivoArco.velocidad;
		struct vertice * tempVerticeOrigen = buscarVertice(nombreCiudadOrigen);
		struct vertice * tempVerticeDestino = buscarVertice(nombreCiudadDestino);
		

		
		if(tempVerticeOrigen == NULL){
		
			insertarVertice(nombreCiudadOrigen);
		}
		if(tempVerticeDestino == NULL){
			
			insertarVertice(nombreCiudadDestino);
		}
		
		if(dirigido == true){
			insertarArco(nombreCiudadOrigen,distancia,nombreCiudadDestino,veelocidadMaxArco,dirigido);	
			insertarArco(nombreCiudadDestino,distancia,nombreCiudadOrigen,veelocidadMaxArco,dirigido);	
		}
		else{
			insertarArco(nombreCiudadOrigen,distancia,nombreCiudadDestino,veelocidadMaxArco,dirigido);	

					
		}
		
		
		arhivoArcos.read(reinterpret_cast<char *>(&tempArchivoArco),sizeof(tempArchivoArco));			
		
	}
		
}




bool existeRutaConexo = false;

void hayArco(struct vertice * nombreCiudadOrigen, string nombreCiudadDestino){



	//entradas:  recibe un elemento de la estructura, y el nombre de la ciudad destino del tipo string
	//salida:  establece si el grafo es conexo modificando variable global
	//descripcion: determina si no existe una ruta desde un punto A a un punto B


	if((nombreCiudadOrigen == NULL) or (nombreCiudadOrigen->visitado == true)){
			
		return;
		
	}
	
	
	if(nombreCiudadDestino == nombreCiudadOrigen->nombreCiudad){
		existeRutaConexo= true;
		
		return;
	}
	
	
	nombreCiudadOrigen->visitado = true;
		
	struct arco * tempA = nombreCiudadOrigen->primerElementoListaArcos;
	while ( tempA!= NULL){
		
		hayArco(tempA->destino, nombreCiudadDestino);
			
	//    nombreCiudadOrigen->visitado = false;
		tempA = tempA->sigArco;
	}	
	return;

}




void desmarcarVisitasCiudades(){

	//entradas:  
	//salida:  
	//descripcion: se encarga de poner en false cada uno de las atributos de tipo visitado en el vertice



	struct vertice * temp = primerElementoDeGrafo;
	
	while(temp!=NULL){
		temp->visitado = false;
		temp = temp->sigVertice;
		
	}	
}






bool grafoEsConexoImpresion = true;
void grafoTransporteEsConexo(){

	//entradas:  
	//salida:  
	//descripcion: se encarga de verificar si el grafo es conexo o no, imprimiendo el resultado en pantalla


	if(primerElementoDeGrafo == NULL){
		cout<<"\n\n";
		cout<<"no hay datos en grafo";
		cout<<"\n\n";
		grafoEsConexoImpresion = false;
		return;
	}
	
	bool grafoConexo=true;
	struct vertice * tempVertice = primerElementoDeGrafo;
	
	while(tempVertice != NULL){  // origen
		struct vertice * tempVertice2 = primerElementoDeGrafo;
		
		while(tempVertice2!=NULL){  // destinos
			if(tempVertice->nombreCiudad == tempVertice2->nombreCiudad){
					
				tempVertice2 = tempVertice2->sigVertice;
				continue;
			}
			else{
					
				hayArco(tempVertice, tempVertice2->nombreCiudad);
				
				
				bool hayArcoVar = existeRutaConexo;
				desmarcarVisitasCiudades();
				
				
				if(hayArcoVar == false){
					grafoConexo = false;
						
					cout<<"No es conexo";
					grafoEsConexoImpresion =  false;
					break;
				}
				existeRutaConexo = false;
				tempVertice2 = tempVertice2->sigVertice;
			}
		}
		if(grafoConexo == false){
				
			break;
			
		}
			
		tempVertice = tempVertice->sigVertice;
	}
	
	if(grafoConexo == true){
		cout<<"Es conexo";
			
		grafoEsConexoImpresion = true;
	}
	
	
}




void imprimirVerticesArcosColores(){


	//entradas:  
	//salida:  
	//descripcion: se encarga de establecer un color para cada uno de los vertices imprimiendo los resultados en pantalla
	


	
	struct vertice * tempVertice = primerElementoDeGrafo;
	
	while(tempVertice!=NULL){
		cout<<"\n\n\n  Vertice: "<<tempVertice->nombreCiudad  <<  "    color: "<< tempVertice->color<<endl;
		struct arco * tempArco = tempVertice->primerElementoListaArcos;
		cout<<"\n Arcos: "<<endl;
		while(tempArco!=NULL){
			cout<<tempVertice->nombreCiudad;
			cout<<tempArco->destino->nombreCiudad;
			cout<<tempArco->distancia<<"  color destino arco: "<<tempArco->destino->color<<"  ,";    
			tempArco = tempArco->sigArco;
		}
		tempVertice = tempVertice->sigVertice;
	}
}




void limpiarCola(){
	
	
	//entradas:  
	//salida:  
	//descripcion: remueva todos los elementos de la cola
	
	
	while(!colaElementosGrafo.empty()){
		colaElementosGrafo.pop();
	}
}

bool comprobarUltimoElemento(string nombreCiudadQueTieneUnArco){

	
	//entradas: recibe el nombre de la ciudad 
	//salida:  
	//descripcion: se encarga de comprobar si el ultimo elemento en el grafo posee un solo vertices ya que de ser asi se puede imprimir
	// sino no se permite la impresion

	bool si = false;
	string nombreEnCola = colaElementosGrafo.back();
//	cout<<"\n\n Ciudad un arco: "<<nombreCiudadQueTieneUnArco<<endl;
//		cout<<"\n\n Ciudad segun recorrido cola: "<<nombreEnCola<<endl;
	if(nombreEnCola == nombreCiudadQueTieneUnArco){
		si = true;
	}
	return si;
}




void almacenarEnCola(struct vertice * verticeNombreCiudad){
	
	
	
	//entradas: recibe el nombre de la ciudad 
	//salida:  
	//descripcion: se encarga de almacenar cada uno de los elementos del grafo en la cola
	
//	cout<<"   en almaenar: "<<verticeNombreCiudad->nombreCiudad<<endl;
	string nombre = verticeNombreCiudad->nombreCiudad;
	colaElementosGrafo.push(nombre);

	verticeNombreCiudad->visitado = true;
	
	struct arco * tempArco = verticeNombreCiudad->primerElementoListaArcos;
	while(tempArco!=NULL){

		if(tempArco!=NULL  and tempArco->destino->visitado == false){
			//	cout<<"   en ciclo  : "<<verticeNombreCiudad->nombreCiudad<<endl;
			almacenarEnCola(tempArco->destino);
		}
		tempArco= tempArco->sigArco;
		
	}
}




bool verificarTodosTienenUnArcoGrafo(){
	

	//entradas: 
	//salida:  
	//descripcion: se encarga de comprobar si cada uno de los elementos en el grafo tiene dos vertices si es asi se puede imprimir 
	// sino no se permite la impresion
		
	
	bool todosTienen1Arco = true;
	int cont = 0;

	struct vertice * tempVertices = primerElementoDeGrafo;
	while(tempVertices!=NULL){
		
		
		struct arco * tempArcos = tempVertices->primerElementoListaArcos;
		while(tempArcos!=NULL){
			cont=cont+1;
			
			tempArcos=tempArcos->sigArco;
		}
		
		if(todosTienen1Arco == true){
			if(cont != 1){
				todosTienen1Arco = false;
			}
			
		}
	
		cont=0;
		
		
		
		tempVertices = tempVertices->sigVertice;
	}

	return todosTienen1Arco;
}



bool verificarSoloInicioYFinalTienen1(){


	//entradas: recibe el nombre de la ciudad 
	//salida:  
	//descripcion: se encarga de comprobar si solo el primer elemento del grafo y el ultimo poseen un solo vertice, si es asi se puede imprimir 
	// sino no se permite la impresion


	bool inicioEs1 = false;
	bool finalEs1 = false;
	bool sePuede = true;
	
	
	int cont = 0;
	
	struct vertice * enviar = primerElementoDeGrafo;
	limpiarCola();
	almacenarEnCola(enviar);
	
	struct vertice * tempVertice  = primerElementoDeGrafo;
	
	while(tempVertice!=NULL){
		struct arco * tempArco = tempVertice->primerElementoListaArcos;
		while(tempArco!=NULL){
			cont = cont + 1;
			tempArco = tempArco->sigArco;
		}
		
		if(cont == 1){
			
			if(inicioEs1 == false){
			
				if(tempVertice == primerElementoDeGrafo){
					inicioEs1 = true;
					cont = 0;
				}

			}
			if(finalEs1 == false){
				bool esDelFinal = comprobarUltimoElemento(tempVertice->nombreCiudad);
				if(esDelFinal == true){
					finalEs1 = true;
				}
				else{
					sePuede = false;
					break;
				}
				
				cont = 0;
				
			}
						
		}
		tempVertice = tempVertice->sigVertice;
	}
	
	return sePuede;
}



bool verificacionCantidadVertices(){

		
	//entradas: recibe el nombre de la ciudad 
	//salida:  
	//descripcion: se encarga de comprobar si cada uno de los elementos en el grafo verificando si se puede hacer la impresion o no
	// sino no se permite la impresion


		
		bool sePuede = true;
		
		
		int cont = 0;
		struct vertice * tempVertices = primerElementoDeGrafo;
		while(tempVertices!=NULL){
			
			
			struct arco * tempArcos = tempVertices->primerElementoListaArcos;
			while(tempArcos!=NULL){
				cont=cont+1;
				
				tempArcos=tempArcos->sigArco;
			}
			
			if(sePuede == true){
				if(cont< 2){
					sePuede = false;
				}
				
			}
		
			cont=0;
			
			
			
			tempVertices = tempVertices->sigVertice;
		}
		
		return sePuede;	
	
}



void imprimirPasandoUnaVezPorVerticesPasoRestrincciones(struct vertice * verticeNombreCiudad){	


	//entradas: recibe el nombre de la ciudad 
	//salida:  
	//descripcion: se encarga de imprimir el grafo segun estandares hamiltoneados (una vez por vertice)


	cout<<endl;
	cout<<"	"<<verticeNombreCiudad->nombreCiudad<<"		";

	
	verticeNombreCiudad->visitado = true;
	


	struct arco * tempArco = verticeNombreCiudad->primerElementoListaArcos;
	while(tempArco!=NULL){
	//cout<<endl;
	  //cout<<"arcos: "<<verticeNombreCiudad->nombreCiudad<<"		";
	
		if(tempArco!=NULL  and tempArco->destino->visitado == false){
				
			imprimirPasandoUnaVezPorVerticesPasoRestrincciones(tempArco->destino);
		}
		tempArco= tempArco->sigArco;	
	}
}




void imprimirPasandoUnaVezPorVertices(){

	//entradas: recibe el nombre de la ciudad 
	//salida:  
	//descripcion: se encarga de llamar a cada una de las funciones que se encargan de comprobar si cada uno 
	//de los elementos para la impresion del mismo

	if(primerElementoDeGrafo == NULL){
		cout<<"No hay Datos";
		return;
	}
	bool sePuede = false;
	grafoTransporteEsConexo();
	desmarcarVisitasCiudades();
	bool pasaGrafoConexo = grafoEsConexoImpresion;
	if(pasaGrafoConexo == false){
		cout<<"\n\n";
		cout<<"no se puede imprimir el grafo...CONEXO";
		return;
	}
	bool verificarTodosTienenUnArcoGrafoVar = verificarTodosTienenUnArcoGrafo();
	desmarcarVisitasCiudades();
	if(verificarTodosTienenUnArcoGrafoVar == true){
	//	cout<<"  si verificarTodosTienenUnArcoGrafoVar  ";
		sePuede = true;
	}
	bool verificarSoloInicioYFinalTienen1Var = verificarSoloInicioYFinalTienen1();
	desmarcarVisitasCiudades();
	if(verificarSoloInicioYFinalTienen1Var == true){
	//	cout<<"  si verificarSoloInicioYFinalTienen1Var  ";
		sePuede = true;
	}
	bool verificacionCantidadVerticesVar = verificacionCantidadVertices();
	desmarcarVisitasCiudades();
	if(verificacionCantidadVerticesVar== true){
	//	cout<<"  si verificacionCantidadVerticesVar  ";
		sePuede = true;
	}
	if(sePuede == true){
		struct vertice * temp = primerElementoDeGrafo;
		imprimirPasandoUnaVezPorVerticesPasoRestrincciones(temp);
		desmarcarVisitasCiudades();		
	}
	else{
		cout<<"\n\n";
		cout<<"no se puede imprimir el grafo";
		cout<<"\n\n";
	}
}





bool VerticeRojo =false;
bool VerticeVerde=false;
bool VerticeAzul = false;
bool VerticeNegro = false;


void actualizarColoresGrafo(){

	
	//entradas: recibe el nombre de la ciudad 
	//salida:  
	//descripcion: se encarga de establecer un color para cada uno de los verticesm mediantes restricciones de colores para cada
	// uno de los vertices


	
	struct vertice * tempVertice = primerElementoDeGrafo;
	
	while(tempVertice!=NULL){
			
			struct arco * tempArcos = tempVertice->primerElementoListaArcos;	   
			while(tempArcos!=NULL){
			
				
				if(tempArcos->destino->color == "Rojo"){
	
					VerticeRojo = true;
				}
				
				
				else if(tempArcos->destino->color == "Verde"){
					VerticeVerde = true;
					
				}
				
				
				else if(tempArcos->destino->color == "Azul"){
					VerticeAzul = true;
				}
				
				
				else if(tempArcos->destino->color == "Negro"){
					VerticeNegro = true;
				}
	
				tempArcos= tempArcos->sigArco;
			}
			
			if(VerticeRojo == false && VerticeVerde== false && VerticeAzul == false && VerticeNegro== false){
				tempVertice->color = "Rojo";
			}
			
			else if(VerticeRojo == true && VerticeVerde== true && VerticeAzul == true && VerticeNegro== true){
				cout<<"No se puede colorear el grafo con cuatro colores..";
				return;
				
			}
			
			else if(VerticeRojo == true && VerticeVerde== false && VerticeAzul == false && VerticeNegro == false){
				tempVertice->color = "Verde";
			}
			
			else if(VerticeRojo == false && VerticeVerde== true && VerticeAzul == false && VerticeNegro == false){
				tempVertice->color = "Rojo";				
			}
			
			else if(VerticeRojo == false && VerticeVerde== false && VerticeAzul == true && VerticeNegro == false){
				tempVertice->color = "Rojo";				
			}
			
			else if(VerticeRojo == false && VerticeVerde== false && VerticeAzul == false && VerticeNegro == true){
				tempVertice->color = "Rojo";				
			}
			
			//rojo
			else if(VerticeRojo == true && VerticeVerde== true && VerticeAzul == false && VerticeNegro == false){
				tempVertice->color = "Azul";
				
			}
			else if(VerticeRojo == true && VerticeVerde== false && VerticeAzul == true && VerticeNegro == false){
				tempVertice->color = "Verde";				
			}
			
			else if(VerticeRojo == true && VerticeVerde== false && VerticeAzul == false && VerticeNegro == true){
				tempVertice->color = "Verde";				
			}
			
			//verde
			else if(VerticeRojo == true && VerticeVerde== true && VerticeAzul == false && VerticeNegro == false){
				tempVertice->color = "Azul";
			}
			
			else if(VerticeRojo == false && VerticeVerde== true && VerticeAzul == true && VerticeNegro == false){
				tempVertice->color = "Rojo";				
			}
			
			else if(VerticeRojo == false && VerticeVerde== true && VerticeAzul == false && VerticeNegro == true){
				tempVertice->color = "Rojo";				
			}
			
			//azul
			else if(VerticeRojo == true && VerticeVerde== false && VerticeAzul == true && VerticeNegro == false){
				tempVertice->color = "Verde";
			}
			
			else if(VerticeRojo == false && VerticeVerde== true && VerticeAzul == true && VerticeNegro == false){
				tempVertice->color = "Rojo";				
			}
			
			else if(VerticeRojo == false && VerticeVerde== false && VerticeAzul == true && VerticeNegro == true){
				tempVertice->color = "Rojo";				
			}
			
			// negro
			
			else if(VerticeRojo == true && VerticeVerde== false && VerticeAzul == false && VerticeNegro == true){
				tempVertice->color = "Verde";
			}
			
			else if(VerticeRojo == false && VerticeVerde== true && VerticeAzul == false && VerticeNegro == true){
				tempVertice->color = "Rojo";				
			}
			
			else if(VerticeRojo == false && VerticeVerde== false && VerticeAzul == true && VerticeNegro == true){
				tempVertice->color = "Rojo";				
			}
			
			// tres colores
			
			//rojo
			
			
			// rojo-verde-azul
			else if(VerticeRojo == true && VerticeVerde== true && VerticeAzul == true && VerticeNegro == false){
				tempVertice->color = "Negro";
			}
			
			//rojo-verde-negro
			else if(VerticeRojo == true && VerticeVerde== true && VerticeAzul == false && VerticeNegro == true){
				tempVertice->color = "Azul";				
			}
			
			//rojo-azul-negro
			
			else if(VerticeRojo == true && VerticeVerde== false && VerticeAzul == true && VerticeNegro == true){
				tempVertice->color = "Verde";				
			}
	
			//verde-azul-negro
			
			
			else if(VerticeRojo == false && VerticeVerde== true && VerticeAzul == true && VerticeNegro == true){
				tempVertice->color = "Rojo";				
			}
				
			
			VerticeRojo=false;
			VerticeVerde=false;
			VerticeAzul=false;
			VerticeNegro=false;
					

			
			tempVertice=tempVertice->sigVertice;
			

	}
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////  ARCHIVO RUTAS Y ARCHIVO CONDUCTORES /////////////////////////////////




fstream archivoRutasInsertar("ArchivoRutas.txt",ios::in | ios::out | ios::binary );//| ios::trunc );
fstream archivoConductores("ArchivoConductores.txt",ios::in | ios::out | ios::binary);//|ios::trunc);
//fstream archivoConductores("ArchivoConductores.txt",ios::in | ios::out | ios::binary )//|ios::trunc);




/////////////////////////////////// REGISTRO CONDUCTORES /////


/*parametros: identificacion del chofer
 salidas: retorna un menos uno en caso de error
 que hace: inserta en el archivo conductor la ruta que este va a realizar*/
 
int insertarRutaAConductor(long identificacion){

	int cont=-1;
	struct archivoConductores regTemp;

    fstream archivoRutasTemp("ArchivoConductores.txt",ios::in | ios::out | ios::binary );

    archivoRutasTemp.seekg(0, ios::beg);
    archivoRutasTemp.read(reinterpret_cast<char *>(&regTemp),sizeof(regTemp));


    while(!archivoRutasTemp.eof()){
    	if(regTemp.identificacion == identificacion){
    		if(cont == -1){
    			cont++;
			}
    		return cont;
		}
		
		else if(regTemp.identificacion < identificacion){
			if(regTemp.derecha != -1){
				int posicion= regTemp.derecha;
				archivoRutasTemp.seekg(posicion*sizeof(regTemp), ios::beg);
    			archivoRutasTemp.read(reinterpret_cast<char *>(&regTemp),sizeof(regTemp));	
    			cont= posicion;
			}
			
			else{
					return -1;
			}
						
		}
		else if(regTemp.identificacion > identificacion){
			if(regTemp.izquierda != -1){
				int posicion= regTemp.izquierda;
				archivoRutasTemp.seekg(posicion*sizeof(regTemp), ios::beg);
    			archivoRutasTemp.read(reinterpret_cast<char *>(&regTemp),sizeof(regTemp));
    			cont= posicion;
			}
			
			else{
					return -1;
			}
		}
		
    }
    return cont;
}



/*parametros: identificacion del chofer y de la ruta
 salidas: 
 que hace: inserta en el archivo conductor la ruta que este va a realizar*/
 
void cambiarFinalRutaAConductor(int identificacion, int ruta){
	
	struct archivoConductores regTemp;
    fstream archivoCondTemp("ArchivoConductores.txt",ios::in | ios::out | ios::binary );
    
    archivoCondTemp.seekg(identificacion*sizeof(regTemp), ios::beg);
    archivoCondTemp.read(reinterpret_cast<char *>(&regTemp),sizeof(regTemp));
    
 	regTemp.enlaceArchivoDeRutas= ruta;
 	
    archivoCondTemp.seekg(identificacion*sizeof(regTemp), ios::beg);
   	archivoCondTemp.write(reinterpret_cast<char *>(&regTemp),sizeof(regTemp)); 	
		
}


/*parametros: 
 salidas: cantidad de registros existentes
 que hace: cuenta la cantidad de registros de conductor existentes*/
 
 
int contarCantidadDeRegistrosConductor(){
	
	struct archivoConductores regTemp;
	fstream archivoConductoresTemp("ArchivoConductores.txt",ios::in | ios::out | ios::binary);

    archivoConductoresTemp.seekg(0, ios::beg);    
    
    int cont= 0;
    while(!archivoConductoresTemp.eof()){
    	cont++;
    	archivoConductoresTemp.read(reinterpret_cast<char *>(&regTemp),sizeof(regTemp));   	    
    }
    return cont;
}


/*parametros: 
 salidas: peticiones de datos para poder definir la ruta que el chofer posee
 que hace: pide los datos para poder definir la ruta que el chofer posee*/

void pedirDatosRutaAConductor(){

	int identificacion;
	int siguienteRegistro;
	cout<<"Digite el numero de identificacion del conductor: \n";
	cin>>identificacion;
	cout<<"digite el numero de registro de ruta: \n";
	cin>>siguienteRegistro;
	int numeroRegistrosConductor= insertarRutaAConductor(identificacion);
	int numeroDeRegistrosRuta= contarCantidadDeRegistros();
	if( siguienteRegistro > numeroDeRegistrosRuta or numeroRegistrosConductor == -1){
		cout<<"ERROR datos inconclusos\n";
		return;
	}
	
	cambiarFinalRutaAConductor(numeroRegistrosConductor, siguienteRegistro);
	cout<<"\n---------------------- se ha realizado con exito -------------------\n\n"	;
	menu();
	
}



/*parametros: 
 salidas: numero de registros existentes de ruutas 
 que hace: cuenta cuantos registro existen de rutas*/

struct archivoConductores registro;
long registrosDelArchivoIndexado(){
	
	long numero;
	archivoConductores.seekg(0,ios::end);
	numero= archivoConductores.tellg();
	numero= (numero/sizeof(registro))-1;
	return numero;
}





/*parametros: 
 salidas:imprime trabajadores existentes en el archivo
 que hace: imprime todos los datos que se encuentran en registro de trabajadores*/

void imprimirArchivoIndexadoConductores(){
	struct archivoConductores regTemp;

    fstream archivoRutasTemp("ArchivoConductores.txt",ios::in | ios::out | ios::binary );

    archivoRutasTemp.seekg(0, ios::beg);
    archivoRutasTemp.read(reinterpret_cast<char *>(&regTemp),sizeof(regTemp));
	cout<<"Izq    nombre	id	enlace	vehiculo	derecha\n"<<endl;

    while(!archivoRutasTemp.eof()){
    	
        cout<<regTemp.izquierda<<"        "<<regTemp.nombreDelChofer<<"      "<<regTemp.identificacion<<"      ";
        cout<<regTemp.enlaceArchivoDeRutas<<"       "<<regTemp.tipoDeVehiculo<<"      "<<regTemp.derecha;
        cout<<endl;
        archivoRutasTemp.read(reinterpret_cast<char *>(&regTemp),sizeof(regTemp));
       
    }
    cout<<"\n\n----------------------------- FIN ARCHIVO CONDUCTORES ------------------------\n\n";
    menu();
}



/*parametros: 
 salidas: anuncios en caso de error
 que hace: registra e inserta a un nuevo chofer*/

void insertarEnArchivoConductoresIndexado(){

	int id= 0;
	char nombreDelconductor[20];
	char tipoDeVehiculop[20];
	cout<<"\nDigite la identificacion del conductor: \n";
	cin>>id;
	int ide= insertarRutaAConductor(id);
	if(ide != -1){
		cout<<"\n\nNo se pueden ingresar datos repetidos\n\n";
		menu();
	}
	cout<<"\nDigite el nombre del chofer: \n";
	cin>>nombreDelconductor;
	
	cout<<"\nDigite el modelo o nombre del vehiculo: \n";
	cin>>tipoDeVehiculop;
	
	archivoConductores.seekg(0,ios::end);
	strcpy(registro.nombreDelChofer,nombreDelconductor);
	strcpy(registro.tipoDeVehiculo,tipoDeVehiculop);
	registro.derecha= -1;
	registro.izquierda= -1;
	registro.enlaceArchivoDeRutas= -1;
	registro.identificacion= id;
	archivoConductores.write(reinterpret_cast<char *>(&registro),sizeof(registro));
	
	int index=0;
	
	while(true){
		archivoConductores.seekg(index*sizeof(registro));
		archivoConductores.read(reinterpret_cast<char *>(&registro), sizeof(registro));
		
		if(registro.identificacion == id){
			cout<<"Error Datos repetidos\n";
			menu();
		}
			
		
		 if(registro.identificacion < id){
			if(registro.derecha != -1){
				index= registro.derecha;
			}
			else{
				registro.derecha= registrosDelArchivoIndexado();
				archivoConductores.seekg(index*sizeof(registro));
				archivoConductores.write(reinterpret_cast<char *>(&registro),sizeof(registro));
				break;
			}
		}
		else{
			
			if(registro.izquierda != -1){
				index= registro.izquierda;
			}
			else{
				registro.izquierda = registrosDelArchivoIndexado();
				archivoConductores.seekg(index*sizeof(registro));
				archivoConductores.write(reinterpret_cast<char *>(&registro),sizeof(registro));
				break;
			}			
		}
	}
archivoConductores.flush();
cout<<"\n----------------- SE  HA REALIZADO EXITOSAMENTE ----------------\n\n";
menu();
}



////////////////////////////////// ARCHIVO RUTAS


/*parametros: posicion a modificar, el siguiente registro
 salidas: 
 que hace: inserta la nueva ruta a seguir despues de la origen*/


void modificarSiguienteRuta(long posModificar,long siguienteRegistro){
	
	struct archivoRutas regTemp;
	
    fstream archivoRutasTemp("ArchivoRutas.txt",ios::in | ios::out | ios::binary );
    
    
    archivoRutasTemp.seekg(posModificar*sizeof(regTemp), ios::beg);
    archivoRutasTemp.read(reinterpret_cast<char *>(&regTemp),sizeof(regTemp));
    
 	regTemp.siguiente=siguienteRegistro;
 	
    archivoRutasTemp.seekg(posModificar*sizeof(regTemp), ios::beg);
   	archivoRutasTemp.write(reinterpret_cast<char *>(&regTemp),sizeof(regTemp));
 	
	
}


/*parametros: 
 salidas: 
 que hace: cuenta la cantidad de registros existentes de rutas*/

int contarCantidadDeRegistros(){
    
    struct archivoRutas regTemp;

    fstream archivoRutasTemp("ArchivoRutas.txt",ios::in | ios::out | ios::binary );

    archivoRutasTemp.seekg(0, ios::beg);
    archivoRutasTemp.read(reinterpret_cast<char *>(&regTemp),sizeof(regTemp));
 
	int cont= 0;
    while(!archivoRutasTemp.eof()){
        cont++;
        archivoRutasTemp.read(reinterpret_cast<char *>(&regTemp),sizeof(regTemp));
    }
    return cont;
}


/*parametros: 
 salidas: solicitud de ingreso de datos por parte del usuario
 que hace: pide datos al usuario para poder realizar la modificacion*/

void pedirDatosModificarSiguienteRuta(){

	int identificacion;
	int siguienteRegistro;
	cout<<"Digite el numero de registro al cual desea realizar el cambio: \n";
	cin>>identificacion;
	cout<<"digite el numero en el cual desea que el registro apunte: \n";
	cin>>siguienteRegistro;
	int numeroRegistros= contarCantidadDeRegistros();
	if(identificacion > numeroRegistros or siguienteRegistro > numeroRegistros){
		cout<<"ERROR fuera de rango del archivo\n";
		return;
	}
	modificarSiguienteRuta(identificacion, siguienteRegistro);	
	cout<<"\n..............Se ha realizado con exito..............\n\n\n";  ///CAMBIOS MENU Y COUT
	menu();
}



/*parametros: 
 salidas: imprimir los datos que posee el archivo rutas
 que hace: imprimir los datos que posee el archivo rutas*/

void imprimirArchivoRutas(){
    
    struct archivoRutas regTemp;

    fstream archivoRutasTemp("ArchivoRutas.txt",ios::in | ios::out | ios::binary );

    archivoRutasTemp.seekg(0, ios::beg);
    archivoRutasTemp.read(reinterpret_cast<char *>(&regTemp),sizeof(regTemp));
	
	if(archivoRutasTemp.eof()){
		cout<<"Archivo vacio.\n";
		menu();
	}

    while(!archivoRutasTemp.eof()){

        
        cout<<"Ruta: ";
        for(int i = 0; i< 10; i++){
        	string nombre=regTemp.nombresDeLasCiudadesAsociadasAChofer[i].nomb;
            if(strcmp(regTemp.nombresDeLasCiudadesAsociadasAChofer[i].nomb,"")==0){
            	break;
			}
            cout<<regTemp.nombresDeLasCiudadesAsociadasAChofer[i].nomb<<"  ";

        }
        cout<<"  Siguiente: "<<regTemp.siguiente<<endl;
        archivoRutasTemp.read(reinterpret_cast<char *>(&regTemp),sizeof(regTemp));
    }
    cout<<"\n----------------FIN ARCHIVO RUTAS ------------------------\n\n";
    menu();
}


/*parametros: 
 salidas: solicitud de ingreso de datos por parte del usuario
 que hace: pide datos al usuario para poder realizar la insercion e inserta a las rutas en archivo rutas*/



void escribirDatosEnArchivoRutas(){
	archivoRutasInsertar.seekg(0,ios::end);
    struct archivoRutas reg2;
	int opcion= 0;
	char lista[10];
	char nombre[20];
	int i= 0;
	for( ; i<10; i++){
		cout<<"\n\n_______________________________________________________________\n\n";
		cout<<"1.Para agregar una nueva ciudad.\n2.O CUALQUIER OTRA tecla para SALIR\nOpcion: ";
		cin>>opcion;
		if(opcion == 1){
			cout<<"\n\n______________Escriba el Nombre: ";	//NUEVO PASAR JULI
			cin>>nombre;
			struct vertice *verifica= buscarVertice(nombre);
			if(verifica != NULL){
				strcpy(reg2.nombresDeLasCiudadesAsociadasAChofer[i].nomb,nombre);
				reg2.siguiente = -1;	
			}
			else{
				cout<<"Error no se puede insertar ya que no existe tal ciudad\n\n\n";
				menu();
			}
			
		}
		else break;
	}
	
	for(; i<11; i++){
		strcpy(reg2.nombresDeLasCiudadesAsociadasAChofer[i].nomb,"");	
	}

	archivoRutasInsertar.write(reinterpret_cast<char *>(&reg2),sizeof(reg2));
	archivoRutasInsertar.flush();				
	cout<<"\n-----------------Se ha realizado exitosamente----------------.\n"	;
	menu();
		
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////				FIN ARCHIVOS 			////////////////////////////////

/*
5.	Imprimir la ruta corta (distancia) las ciudades X y Y.
*/


/*parametros: 
 salidas:
 que hace:  estructura para pila*/

struct nodo{
	string nombre;
	int num;
	struct nodo *sig;
	nodo(string n, int nu){
		nombre= n;
		num=nu;
		sig= NULL;
	}
}*primero;
struct nodo *listaAuxImprimirRuta;




/*parametros: 
 salidas: 
 que hace: insercion de elemento a pila*/
 
void insertar(string nomb, int nume){
	struct nodo *nuevo= new nodo(nomb,nume);
	if(primero == NULL){
		primero= nuevo;
	}
	else{
		nuevo->sig= primero;
		primero= nuevo;
	}
}


/*parametros: 
 salidas: datos que posee la pila
 que hace: impresion de elemento de pila*/

void imprimirRutaCorta(){
	int conta= 0;
	bool primeraVez= true;
	while(listaAuxImprimirRuta->sig != NULL){
		if(primeraVez == true){
			listaAuxImprimirRuta= listaAuxImprimirRuta->sig;
			primeraVez= false;	
		}
	
		cout<<listaAuxImprimirRuta->nombre<<", "<<listaAuxImprimirRuta->num<<"   ";
		
		listaAuxImprimirRuta= listaAuxImprimirRuta->sig;
		
	}
	cout<<listaAuxImprimirRuta->nombre<<", "<<listaAuxImprimirRuta->num<<"   ";
}


/*parametros: 
 salidas:
 que hace:  introduce los datos de la pila principal a una auxiliar*/


void igualar(){
	listaAuxImprimirRuta= NULL;
	struct nodo *rutaAux= primero;
	while(rutaAux != NULL){
		string nombre= rutaAux->nombre;
		int numero= rutaAux->num;
		
		
		struct nodo *nuevo= new nodo(nombre,numero);
		if(listaAuxImprimirRuta == NULL){
			listaAuxImprimirRuta= nuevo;
		}
		else{
			nuevo->sig= primero;
			listaAuxImprimirRuta= nuevo;
		}
		rutaAux= rutaAux->sig;
	}	
}

/*parametros: 
 salidas:
 que hace:  elimina dato de la pila */

void pop()
{
    struct nodo *temp = primero;
    if(primero == NULL)
    {
        return;
    }
    else
    {
        if(temp->sig == NULL)
        {
            primero = NULL;
        }
        else
        {
            primero = temp->sig;
        }
    }
}


int numeroTotal=99999;
bool siHayRuta = false;
int cont = 0;
bool entro= false;


/*parametros: inicio: vertice inicial, ciudad destino, variable que almacena el minimo camino de un punto a otro 
 salidas:
 que hace:  busca la ruta mas corta de un punto a otro */


void buscarRutaAB(struct vertice * inicio, string destino,int minimo){

    if((inicio == NULL) or (inicio->visitado == true)or (minimo > numeroTotal)){
    	return;
	}

    if(destino == inicio->nombreCiudad){
    	
        siHayRuta= true;
		        
        if(minimo < numeroTotal){      	
        	numeroTotal= minimo;
        	igualar();
        	return;
		}   	        
    }

    inicio->visitado = true;
    struct arco *tempA = inicio->primerElementoListaArcos;
    while ( tempA!= NULL){
    	insertar(inicio->nombreCiudad,tempA->distancia);
        buscarRutaAB(tempA->destino, destino,tempA->distancia+minimo);
        inicio->visitado = false;
        tempA = tempA->sigArco;
        pop();   

    }

    
}


/*parametros: 
 salidas: peticion de ingreso de datos al usuario
 que hace: pide datos al usuario referentes a la consulta de distancia corta entre un sitio a otro*/


void rutaMasCortaEntrePuntoABDatos(){
	
	string ciudadOrigen;
	string ciudadDestino;
	cout<<"Digite el nombre de la ciudad origen: \n";
	cin>>ciudadOrigen;
	cout<<"Digite el nombre de la ciudad destino: \n";
	cin>>ciudadDestino;
	struct vertice *verticeOrigen= buscarVertice(ciudadOrigen);
	struct vertice *verticeDestino= buscarVertice(ciudadDestino);
	if(verticeOrigen == NULL or verticeDestino== NULL){
		cout<<"no se encuentra a la ciudad";
		return;
	}
	string nombreDestino= verticeDestino->nombreCiudad;
	buscarRutaAB(verticeOrigen,nombreDestino,0);
	if(siHayRuta==true){
        cout<<"\nSi existe ruta.\n";
        cout<<"\ndistancia minima: "<<numeroTotal;
        cout<< "\nRecorrido mas corto: ";
        
        imprimirRutaCorta();
        
    //   
    }
    else{
    	cout<<"No hay ruta.\n";
	}
        
        
    numeroTotal=99999;
	siHayRuta = false;
	cont = 0;
	entro= false;
	cout<<"\n-----------------------------------------------------------.\n"	;
	menu();
}

/////////////////////////////////////////////////////////////////


/*6.	Imprimir el tiempo más corto que tardaría trasladandose de
 una ciudad X a la ciudad Y.*/



/*parametros:ciudad inicio o origen, ciudad destino destino,tiempo minimo 
 salidas:
 que hace:  determina el camino con el tiempo mas corto entre un punto a otro */
 

 
 
struct vertice *tempParaTiempo;
float totalKmHora=9999;
void TiempoMasCorto(struct vertice * inicio, string destino,float minimo){

    if((inicio == NULL) or (inicio->visitado == true)or (minimo > totalKmHora)){
    	return;
	}
    if(destino == inicio->nombreCiudad){
        siHayRuta= true;
		        
        if(minimo < totalKmHora){ 
        	totalKmHora= minimo;
        	return;
		}   	        
    }
    
    inicio->visitado = true;
    struct arco *tempA = inicio->primerElementoListaArcos;
    while ( tempA!= NULL){
		
		if(tempParaTiempo->nombreCiudad == inicio->nombreCiudad){
			minimo= 0;
		}
    	
    	minimo= (float)tempA->distancia/(float)tempA->velocidadMaximaArco+minimo;    	
    
        TiempoMasCorto(tempA->destino, destino,minimo);
        inicio->visitado = false;
        tempA = tempA->sigArco;   
    }
}


/*parametros: 
 salidas: peticion de ingreso de datos al usuario
 que hace: pide datos al usuario referentes a la consulta de tiempo minimo entre un sitio a otro*/
 


void tiempoMinimoDeCiudadABDatos(){
	
	string ciudadOrigen;
	string ciudadDestino;
	cout<<"Digite el nombre de la ciudad origen: \n";
	cin>>ciudadOrigen;
	cout<<"Digite el nombre de la ciudad destino: \n";
	cin>>ciudadDestino;
	struct vertice *verticeOrigen= buscarVertice(ciudadOrigen);
	struct vertice *verticeDestino= buscarVertice(ciudadDestino);
	if(verticeOrigen == NULL or verticeDestino== NULL){
		cout<<"no se encuentra a la ciudad";
		return;
	}
	tempParaTiempo= verticeOrigen;
	string nombreDestino= verticeDestino->nombreCiudad;
	TiempoMasCorto(verticeOrigen,nombreDestino,0);
	if(siHayRuta==true){
         
        cout << "\n\nEl tiempo minimo es de: " << totalKmHora<<" Horas" << endl;
	
    }
    else{
    	cout<<"No hay ruta.\n";
	}
    
        
	struct vertice *tempParaTiempo;
	totalKmHora=9999;
	
	cout<<"\n---------------------------------------------------.\n"	;
	menu();
	
}


//////////////////////////////////////////////////////////////////////////////////////

/*8.	Imprimir la cantidad de usuarios que viajan hacia una ciudad X (destino).*/



/*parametros: destino o ciudad de consulta
 salidas: 
 que hace: determina la cantidad de usuarios que viajan a una ciudad en detern¿minado*/





void cantidadDeUsuariosViajanCiudadX(string destino){

	struct archivoConductores regTemp;

	int cantidad= 0;
    fstream archivoRutasTemp("ArchivoConductores.txt",ios::in | ios::out | ios::binary );

    archivoRutasTemp.seekg(0, ios::beg);
    archivoRutasTemp.read(reinterpret_cast<char *>(&regTemp),sizeof(regTemp));
	   
 	int numeroRegistroRuta= regTemp.enlaceArchivoDeRutas;

    while(!archivoRutasTemp.eof()){
    	if(regTemp.enlaceArchivoDeRutas != -1){    		
    		
		numeroRegistroRuta= regTemp.enlaceArchivoDeRutas;
		struct archivoRutas regTemp2;
		
	    fstream archivoRutasTemp("ArchivoRutas.txt",ios::in | ios::out | ios::binary );
	    
	    bool fin= false;
	    while(fin != true){
	    	
	    	archivoRutasTemp.seekg(numeroRegistroRuta*sizeof(regTemp2), ios::beg);
	    	archivoRutasTemp.read(reinterpret_cast<char *>(&regTemp2),sizeof(regTemp2));
	    	if(regTemp2.siguiente == -1){
	    		fin= true;
	        	for(int i = 0; i< 10; i++){
		        	string nombre=regTemp2.nombresDeLasCiudadesAsociadasAChofer[i].nomb;
		            if(strcmp(regTemp2.nombresDeLasCiudadesAsociadasAChofer[i].nomb,"")==0){
		            	break;
					}
					if(nombre ==destino and strcmp(regTemp2.nombresDeLasCiudadesAsociadasAChofer[i+1].nomb,"")==0)	{
						cantidad++;
					}		           
		        }		        
			}
			else{
		        numeroRegistroRuta= regTemp2.siguiente;			
				}
			}    		
		}
        archivoRutasTemp.read(reinterpret_cast<char *>(&regTemp),sizeof(regTemp));
       
    }	
	cout<<"La cantidad de personas que viajan hacia ese lugar son: "<<cantidad<<endl;
	
	cout<<"\n---------------------------------------------------------------------.\n"	;
	menu();
}


/*parametros: 
 salidas: peticion de ingreso de datos al usuario
 que hace: pide datos al usuario referentes a la consulta de personas que viajan hacia un destino*/
 


void pedirInformacionCantidadDeUsuariosViajaX(){
	string nombre;
	cout<<"digite el nombre del destino: "<<endl;
	cin>>nombre;
	cantidadDeUsuariosViajanCiudadX(nombre);
	menu();
}

//////////////////////////////////////////////////////////////////////////////////////


/*9.	Imprimir todas la rutas que realiza el usuario X. 
El id lo debe buscar en el archivo ordenado, despues dirigirse al archivo de rutas
 realizando acceso directo.*/


/*parametros: identificacion de la persona a consultar
 salidas: 
 que hace: recorre el archivo de conductores y sus rutas y las imprime*/


void todasLasRutasUsuarioX(int identificacion){
	
	int numeroRegistrosConductor= insertarRutaAConductor(identificacion);
	if(numeroRegistrosConductor == -1){
		cout<<"Error datos inconclusos\n";
		menu();
	}
	int numeroRegistroRuta=0;
	struct archivoConductores regTemp;
    fstream archivoCondTemp("ArchivoConductores.txt",ios::in | ios::out | ios::binary );
    
    archivoCondTemp.seekg(numeroRegistrosConductor*sizeof(regTemp), ios::beg);
    archivoCondTemp.read(reinterpret_cast<char *>(&regTemp),sizeof(regTemp));
    
 	numeroRegistroRuta= regTemp.enlaceArchivoDeRutas;

	struct archivoRutas regTemp2;
	if(numeroRegistroRuta == -1){
		cout<<"no posee ninguna ruta asociada\n\n";
		menu();
	}
	
    fstream archivoRutasTemp("ArchivoRutas.txt",ios::in | ios::out | ios::binary );
    
    bool fin= false;
    while(fin != true){
    	
    	archivoRutasTemp.seekg(numeroRegistroRuta*sizeof(regTemp2), ios::beg);
    	archivoRutasTemp.read(reinterpret_cast<char *>(&regTemp2),sizeof(regTemp2));
    	if(regTemp2.siguiente == -1){
    		fin= true;
    		cout<<"Ruta: ";
        	for(int i = 0; i< 10; i++){
            	if(strcmp(regTemp2.nombresDeLasCiudadesAsociadasAChofer[i].nomb,"")==0){
	            	break;
				}
	    			
	            cout<<regTemp2.nombresDeLasCiudadesAsociadasAChofer[i].nomb<<"  ";
	
	        }
	        cout<<"  Siguiente: "<<regTemp2.siguiente<<endl;
		}
		else{
			cout<<"Ruta: ";
        	for(int i = 0; i< 10; i++){
            	if(strcmp(regTemp2.nombresDeLasCiudadesAsociadasAChofer[i].nomb,"")==0){
	            	break;
				}
	    			
	            cout<<regTemp2.nombresDeLasCiudadesAsociadasAChofer[i].nomb<<"  ";
	
	        }
	        cout<<"  Siguiente: "<<regTemp2.siguiente<<endl;
	        numeroRegistroRuta= regTemp2.siguiente;			
		}
	}	
}



/*parametros: 
 salidas: peticion de ingreso de datos al usuario
 que hace: pide datos al usuario referentes a la consulta de rutas de un persona*/


void pedirInformacionTodasLasRutasUsuarioX(){
	int identificacion;
	cout<<"Digite el numero de identificacion de la persona a consultar: \n";
	cin>>identificacion;
	todasLasRutasUsuarioX(identificacion);
	cout<<"\n-----------------Fin del proceso----------------.\n"	;	
	
	menu();
	
}



///////////////////////////////////////////////////////////////////////////////////////////



/*parametros: Vertice Origen,nombre de la Ciudad Destino
 salidas: 
 que hace: retorna el arco solicitado de una ciudad a otra*/


struct arco *retornarArco(struct vertice *tempVerticeOrigen,string nombreCiudadDestino){
	
	struct arco *temp = tempVerticeOrigen->primerElementoListaArcos;
		bool existeArco = false;
		while(temp!=NULL){
			
			if(temp->destino->nombreCiudad == nombreCiudadDestino){
				return 	temp;
			}
			temp = temp->sigArco;
	}
	return NULL;
}



/*7.	Mostrar todas las rutas alternas de comunicación entre la ciudad X y la ciudad
 Y en caso del cierre de un camino (arco).
*/
 



/*parametros: ciudad origen, ciudad destino,  distancia de un punto a otro
 salidas:  
 que hace: verifica los caminos abiertos o cerrados de una ruta a otra*/


void metodoCaminosAbiertosAuxiliares(struct vertice *origen, string destino, int distancia){
	
	
	if(origen == NULL or origen->visitado == true){
		
		return;
	}
	else if(origen->nombreCiudad == destino){
		cout<<endl;
		igualar();
		cout<<destino<<", ";
		imprimirRutaCorta();
		
		pop();
		
		return;
	}
	else{
		
		
		origen->visitado = true;
		
		struct arco *camino = origen->primerElementoListaArcos;
	
		
		
		
		while(camino != NULL){
			if(camino->habilitado == true){
				insertar(origen->nombreCiudad, camino->distancia);
				metodoCaminosAbiertosAuxiliares(camino->destino, destino, distancia);
			}
			pop();			
			camino = camino->sigArco;
			origen->visitado = false;
			
		}
		
				
	}
	
}


/*parametros: 
 salidas: solicitudes de informacion por parte del usuario
 que hace: pide informacion sobre la consulta de no pasar por arco cerrado*/


void indicarCualArcoDeseaDejar(){
	
	string nombreCiudadOrigen;
	string nombreCiudadDestino;
	
	cout<<"Digite el nombre de la ciudad origen: ";
	cin>>nombreCiudadOrigen;
	cout<<"Digite el nombre de la ciudad destino; ";
	cin>>nombreCiudadDestino;

	struct vertice *tempVerticeOrigen = buscarVertice(nombreCiudadOrigen);
	struct vertice *tempVerticeDestino = buscarVertice(nombreCiudadDestino);
	
	if(tempVerticeDestino == NULL or tempVerticeOrigen == NULL){
		cout<<"Alguno de los datos ingresados no existe...intente de nuevo";
		return; //o volver al menu
	}
	else{
		metodoCaminosAbiertosAuxiliares(tempVerticeOrigen, nombreCiudadDestino,0)	;
	}
	cout<<"\n-----------------Fin del proceso----------------.\n"	;
	menu();
}




/*parametros: raiz del arbol
 salidas: imprime datos del arbol 
 que hace:imprime en preorden los datos que posee el arbol*/

void imprimirArbol(struct arbol *origen){
	if(origen == NULL){
		return;
	}
	
	struct arbolSubListaRutas *temp= origen->arbolPrimerElementoRuta;	
	while(temp !=  NULL){
		
		cout<< "\nCiudad: "<<origen->ciudad<<endl;
		cout<<"\ninsidencias: "<<origen->contador<<endl;
		imprimirArbol(temp->elementosArbol);
		temp= temp->sig;
		
	}
		
	if(origen != NULL){
		cout<< "\nCiudad: "<<origen->ciudad<<endl;
		cout<<"\ninsidencias: "<<origen->contador<<endl;
	}
	raiz= NULL;
	menu();
}









void crearArbol(string ciudadX){
	
	cout<<endl<<endl;
	struct archivoRutas regTemp;
    fstream archivoRutasTemp("ArchivoRutas.txt",ios::in | ios::out | ios::binary );
    archivoRutasTemp.seekg(0, ios::beg);
    archivoRutasTemp.read(reinterpret_cast<char *>(&regTemp),sizeof(regTemp));
	int cont= 0;
	entro= false;
    while(!archivoRutasTemp.eof()){
		string nombreR = regTemp.nombresDeLasCiudadesAsociadasAChofer[0].nomb;
		
		if(nombreR == ciudadX){
			
			if(raiz== NULL)	{
				struct arbol *nuevo= new arbol(nombreR,1);
				raiz= nuevo;
				cout<<"\nRAIZ: "<<raiz->ciudad;
				entro= true;
			}					    
			struct arbol *temp=raiz;
			struct arbolSubListaRutas *sublista= temp->arbolPrimerElementoRuta;
		   			    	
		    
			for(int i = 1; i< 10; i++){
			
				if(strcmp(regTemp.nombresDeLasCiudadesAsociadasAChofer[i].nomb,"")==0){
		            	break;
				}

				string nombre = regTemp.nombresDeLasCiudadesAsociadasAChofer[i].nomb;	
				
				if(sublista == NULL){
					
					
					struct arbol *nuevo= new arbol(nombre,1);	
					struct arbolSubListaRutas *nuevaSublista= new arbolSubListaRutas();	
					temp->arbolPrimerElementoRuta= nuevaSublista;
					nuevaSublista->elementosArbol= nuevo;
					cout<<"\nciudad de sublista: \n"<<nuevo->ciudad<<endl<<endl;
					cout<<"contador: "<<nuevo->contador<<endl<<endl;
					
					temp= nuevo;
					sublista= temp->arbolPrimerElementoRuta;
					
				}
				else{
					while(sublista != NULL){
						if(sublista->elementosArbol->ciudad == nombre){

							sublista->elementosArbol->contador= sublista->elementosArbol->contador+1;
							cout<<"\nciudad de sublista: \n"<<sublista->elementosArbol->ciudad<<endl<<endl;
							cout<<"contador: "<<sublista->elementosArbol->contador<<endl<<endl;
							break;
						}
						sublista= sublista->sig;
					}
					if(sublista == NULL){
						
						struct arbol *nuevo= new arbol(nombre,1);	
						struct arbolSubListaRutas *nuevaSublista= new arbolSubListaRutas();	
						temp->arbolPrimerElementoRuta= nuevaSublista;
						nuevaSublista->elementosArbol= nuevo;
						cout<<"\nnuevo Puntero: \n";
						cout<<"\nciudad de sublista: \n"<<nuevo->ciudad<<endl<<endl;
						cout<<"contador: "<<nuevo->contador<<endl<<endl;
						
						temp= nuevo;
						sublista= temp->arbolPrimerElementoRuta;
						
					}
					
				}			
	
    		}					
		}
        archivoRutasTemp.read(reinterpret_cast<char *>(&regTemp),sizeof(regTemp));
    }
			
}


void arbolDatos(){

	string ciudadOrigen;
	cout<<"Digite el nombre de la ciudad origen: \n";
	cin>>ciudadOrigen;

	struct vertice *verticeOrigen= buscarVertice(ciudadOrigen);

	if(verticeOrigen == NULL){
		cout<<"no se encuentra a la ciudad";
		return;
	}
	else{
		cout<<"\n\n--------------- ARBOL --------------\n\n";
		crearArbol(ciudadOrigen);
		if(raiz == NULL){
			cout<<"\nNo existe ruta que inicie con esa ciudad\n";
			//imprimirArbol(raiz);
		}
		
	}
	raiz= NULL;
	menu();


	
}


//menu que posee todos los reportes del proyecto
//ultimo dia de modificacion: 9/11/2015

void menuReportes(){
	int desicion;
	cout<<"1.	Imprimir Archivo Conductores en formato de arbol binario.\n";
	cout<<"2.	Imprimir el Archivo Rutas.\n";
	cout<<"3.	Realizar recorrido a partir de una ciudad X e imprimir las rutas y uso.\n";
	cout<<"4.	Volver al menu principal.\n";
	cout<<"opcion: ";
	
	cin>>desicion;
	
	if(desicion == 1) {
		cout<<"\n\n";
		imprimirArchivoIndexadoConductores();
		cout<<"\n\n";
	
	}
	if(desicion == 2){
		cout<<"\n\n";
		imprimirArchivoRutas();
		cout<<"\n\n";
		
	}
	if(desicion == 3){
		cout<<"\n\n";
		arbolDatos();
		cout<<"\n\n";
	
	}
	
	if(desicion == 4){
		cout<<"\n\n";
		menu();
		cout<<"\n\n";
	}
	
	else{
		cout<<"\nError.. digite una tecla valida.\n";
		menuReportes();
	}
	
}



//menu que posee todas las consultas sobre ciudades del proyecto
//ultimo dia de modificacion: 2/11/2015

void menuVertice(){
	int desicion;
	cout<<"1.Insertar\n2.Modificar\n3.Borrar\n4.Volver al menu principal\n";
	cout<<"opcion: ";
	cin>>desicion;
	cout<<"\n\n";
	if(desicion == 1) {
		cout<<"\n\n";
		pedirInformacionVertice();
		cout<<"\n\n";
		menu();
	}
	if(desicion == 2){
		cout<<"\n\n";
		modificarVerticeNombreCiudad();
		cout<<"\n\n";
		menu();
	}
	if(desicion == 3){
		cout<<"\n\n";
		eliminarVertice();
		cout<<"\n\n";
		menu();
	}
	
	if(desicion == 4){
		cout<<"\n\n";
		menu();
		
	}
	
	else{
		cout<<"\n\n";
		cout<<"\nError.. digite una tecla valida.";
		menuVertice();
		cout<<"\n\n";
	}
	
}



/*parametros: 
 salidas: solicitudes de informacion por parte del usuario
 que hace: para poder cerrar o abrir un camino*/

void cerrarArcoVertice(){

	string nombreCiudadOrigen;
	string nombreCiudadDestino;
	cout<<"Digite el nombre de la ciudad origen del camino: ";
	cin>> nombreCiudadOrigen;
	cout<<"Digite el nombre de la ciudad destino: ";
	cin>>nombreCiudadDestino;
	int opcion;
	cout<<"1.Abrir camino\n2.Cerrar camino\n3.Atras ";
	cin>>opcion;	
	struct vertice * tempVerticeOrigen = buscarVertice(nombreCiudadOrigen);
	struct vertice * tempVerticeDestino = buscarVertice(nombreCiudadDestino);
	if(tempVerticeOrigen == NULL or tempVerticeDestino == NULL){
	cout<<"\n\n";
		cout<<"Alguno de los datos ingresados no son correctos... intente de nuevo";
		cout<<"\n\n";
		menu();
	}
	else{
		bool estado = true;
		string mensaje = "Abierta";
		if(opcion == 2){
			estado = false;
			mensaje = "Cerrada";
		}
		struct arco * temp = tempVerticeOrigen->primerElementoListaArcos;
		bool hayArco = false;
		while(temp!=NULL){
			if(temp->destino->nombreCiudad == nombreCiudadDestino){
					cout<<" Origen: " << nombreCiudadOrigen;
				temp->habilitado = estado;
				if(hayArco == false){
					hayArco = true;
				}
				cout<<"  estado de camino: " <<mensaje;
				cout<<"  destino: " << temp->destino->nombreCiudad;
			}
			temp = temp->sigArco;
		}
		if(hayArco == true){
			cout<<"\n\n";
			cout<<"Cambio realizado con exito";
			//menu
		}
		else{
			cout<<"\n\n";
			cout<<"no se pudo encontrar el camino";
		    cout<<"\n\n";
		}
	}
}




//menu que posee todas las consultas sobre los arcos del proyecto
//ultimo dia de modificacion: 3/11/2015

void menuModificarArcos(){
	int desicion;
	cout<<"1.Modificar Distancia \n2. Modificar Velocidad Maxima\n3.Volver al menu Arcos\n4.Cerrar un camino\n";
	cout<<"opcion: ";	
	cin>>desicion;
	cout<<"\n\n";
	
	if(desicion == 1) {
		cout<<"\n\n";
		modificarDistanciaArco();
		cout<<"\n\n";
		menu();
	}
	if(desicion == 2){
		cout<<"\n\n";
		modificarVelocidadMaxCamino();
		cout<<"\n\n";
		menu();
	}
	if(desicion == 3){
		cout<<"\n\n";
		menuArcos();
		cout<<"\n\n";
	}
	if(desicion == 4){
		cout<<"\n\n";
		cerrarArcoVertice();
		menu();
	}
	
	
	else{
		cout<<"\n\n";
		cout<<"\nError.. digite una tecla valida.";
		cout<<"\n\n";
		menuModificarArcos();
		cout<<"\n\n";
	}
		
}



//menu que posee todas las consultas sobre arcos del proyecto
//ultimo dia de modificacion: 1/11/2015

void menuArcos(){
	
	int desicion;
	cout<<"1.Insertar Arco \n2.Modificar Arcos\n3.Eliminar Arco \n4.Volver al menu principal\n";
	cout<<"opcion: ";	
	cin>>desicion;
	cout<<"\n\n";
	
	if(desicion == 1) {
		cout<<"\n\n";
		pedirInformacionArco();
		cout<<"\n\n";
		menu();
	}
	
	if(desicion == 2){
		cout<<"\n\n";
		menuModificarArcos();
		cout<<"\n\n";
		
	}
	
	if(desicion == 3){
		cout<<"\n\n";
		borrarArco();
		cout<<"\n\n";
		menu();
	}
		
	if(desicion == 4){
		cout<<"\n\n";
		menu();
		cout<<"\n\n";
	}
	
	
	else{
		cout<<"\n\n";
		cout<<"\nError.. digite una tecla valida.\n";
		menuArcos();
		cout<<"\n\n";
	}
	
}



//menu que posee todas las consultas sobre conductores del proyecto
//ultimo dia de modificacion: 2/11/2015

void menuConductores(){
	
	int desicion;
	cout<<"1.Insertar\n2. Insertar Ruta Realizada \n3.Volver al menu principal\n";
	cout<<"opcion: ";	
	cin>>desicion;
	cout<<"\n\n";
	if(desicion == 1) {
		cout<<"\n\n";
		insertarEnArchivoConductoresIndexado();
		cout<<"\n\n";
		menu();
	}
	if(desicion == 2){
		cout<<"\n\n";
		pedirDatosRutaAConductor();
		cout<<"\n\n";
		menu();
		
	}
	if(desicion == 3){
		cout<<"\n\n";
		menu();
		cout<<"\n\n";
	}
	
	
	else{
		cout<<"\n\n";
		cout<<"\nError.. digite una tecla valida.\n";
		cout<<"\n\n";
		menuConductores();
		cout<<"\n\n";
	}
	
		
}



//menu que posee todas las consultas sobre rutas del proyecto
//ultimo dia de modificacion: 5/11/2015

void menuRutas(){
		cout<<"\n\n";
	int desicion;
	cout<<"1.Insertar\n2. Indicar Siguiente Ruta\n3.Volver al menu principal\n";
	cout<<"opcion: ";
	cin>>desicion;
	cout<<"\n\n";
	if(desicion == 1) {
		cout<<"\n\n";
		escribirDatosEnArchivoRutas();
		cout<<"\n\n";
		menu();
	}
	if(desicion == 2){
		cout<<"\n\n";
		pedirDatosModificarSiguienteRuta();
		cout<<"\n\n";
		menu();
	
		
	}
	if(desicion == 3){
		cout<<"\n\n";
		menu();
		cout<<"\n\n";
	}
	
	
	else{
		cout<<"\n\n";
		cout<<"\nError.. digite una tecla valida.";
		menuRutas();
		cout<<"\n\n";
	}
	
}








//menu que posee todas las consultas sobre todas las funcionalidades que posee el proyecto
//ultimo dia de modificacion: 1/11/2015

void menu(){
	
	cout<<"\n\n";
	int desicion;
	cout<<"1.Rutas\n2.Conductores\n3.vertice o ciudades\n4.arcos o caminos\n";
	cout<<"5.Reportes\n6.Consultas\n7.Guardar Datos Grafo (Arcos y Vertices)\n8.Imprimir grafo \n";
	cout<<"opcion: ";
	cin>>desicion;
	cout<<"\n\n";
//	if(desicion == 0){
		//metodoUnaVezPorArco(struct vertice *origen, struct arco *caminoPripal, string destino, int distancia)
//	}
	if(desicion == 1) {
		cout<<"\n\n";
		menuRutas();
		cout<<"\n\n";
	}
	if(desicion == 2){
		cout<<"\n\n";
		menuConductores();
		cout<<"\n\n";
	}
	if(desicion == 3){
		cout<<"\n\n";
		menuVertice();
		cout<<"\n\n";
	}
	if(desicion == 4){
		cout<<"\n\n";
		menuArcos();
		cout<<"\n\n";
	}
	if(desicion == 5){
		cout<<"\n\n";
		menuReportes();
		cout<<"\n\n";
	}
	if(desicion == 6){
		cout<<"\n\n";
		menuConsultas();
		cout<<"\n\n";
	}
	if(desicion == 7){
		cout<<"\n\n";
		guardarDatosArchivoArcoYVertices();
		cout<<"Datos Guardados con exito";
		cout<<"\n\n";
		menu();
	}
	if(desicion == 8){
		cout<<"\n\n";
		amplitud();
		
		
		cout<<"\n\n";
		menu();
	}
	
	else{
		cout<<"\n\n";
		cout<<"\nError.. digite una tecla valida.\n";
		cout<<"\n\n";
		menu();
		cout<<"\n\n";
	}
		
}




/*parametros: ciudad origen, ciudad destino,  distancia de un punto a otro, para saber si es la primer Vez
 salidas: 
 que hace: para poder cerrar o abrir un camino*/



void desmarcarVisitasArcos(){

	struct vertice * temp = primerElementoDeGrafo;
	
	while(temp!=NULL){
		struct arco * tempArco = temp->primerElementoListaArcos;
		while(tempArco!=NULL){
			tempArco->visitado= false;
			tempArco= tempArco->sigArco;
		}
		temp = temp->sigVertice;	
	}
	
}





bool verificarCantidadDeArcosMetodoUnaVezPorArco(){
	

	//entradas: recibe el nombre de la ciudad 
	//salida:  
	//descripcion: se encarga de comprobar si cada uno de los elementos en el grafo verificando si se puede hacer la impresion o no
	// sino no se permite la impresion


		
		bool sePuede = true;
		
		
		int cont = 0;
		struct vertice * tempVertices = primerElementoDeGrafo;
		while(tempVertices!=NULL){
			
			
			struct arco * tempArcos = tempVertices->primerElementoListaArcos;
			while(tempArcos!=NULL){
				cont=cont+1;
				
				tempArcos=tempArcos->sigArco;
			}
			
			if(sePuede == true){
				if(cont%2 !=0){
					sePuede = false;
				}
				
			}
		
			cont=0;
			
			
			
			tempVertices = tempVertices->sigVertice;
		}
		
		return sePuede;
	
}


void metodoUnaVezPorArco(struct vertice *nombreCiudad){
		
	

	struct arco * tempArco = nombreCiudad->primerElementoListaArcos;
	while(tempArco!=NULL){
	
		if(tempArco!=NULL  and tempArco->visitado== false and tempArco->habilitado == true){
			cout<<endl;	
			
			cout<<"Origen: "<<nombreCiudad->nombreCiudad<<endl;
			cout<<"Destino: "<<tempArco->destino->nombreCiudad<<endl;
			cout<<"Distancia: "<<tempArco->distancia<<endl;
			cout<<endl;
			tempArco->visitado = true;
			metodoUnaVezPorArco(tempArco->destino);
		}
		tempArco= tempArco->sigArco;
		
	}
	
	
}


void comprobarRestriccionesUnaVezPorArco(){


	if(primerElementoDeGrafo == NULL){
		cout<<"No hay Datos";
		return;
	}

	bool sePuede = false;

	grafoTransporteEsConexo();
	desmarcarVisitasCiudades();
	bool pasaGrafoConexo = grafoEsConexoImpresion;

	if(pasaGrafoConexo == false){
		cout<<"\n\n";
		cout<<"no se puede imprimir el grafo...CONEXO";
		return;
	}
	

	bool verificarTodosTienenUnArcoGrafoVar = verificarCantidadDeArcosMetodoUnaVezPorArco();
	desmarcarVisitasCiudades();
	if(verificarTodosTienenUnArcoGrafoVar == true){
	//	cout<<"  si verificarTodosTienenUnArcoGrafoVar  ";
		sePuede = true;
	}
	
	
	bool verificacionCantidadVerticesVar = verificacionCantidadVertices();
	desmarcarVisitasCiudades();
	if(verificacionCantidadVerticesVar== true){
	//	cout<<"  si verificacionCantidadVerticesVar  ";
		sePuede = true;
	}
	
	if(sePuede == true){
		struct vertice * temp = primerElementoDeGrafo;
		metodoUnaVezPorArco(temp);
		desmarcarVisitasArcos();
		menu();
				
	}
	else{
		cout<<"\n\n";
		cout<<"no se puede imprimir el grafo";
		cout<<"\n\n";
	}
	
	
		
}






//menu que posee todas las consultas del proyecto
//ultimo dia de modificacion: 10/11/2015


void menuConsultas(){
	int desicion;
	cout<<"1.	Determinar si el grafo es conexo.\n";
	
	cout<<"2.	Recorrer grafo una sola vez por cada vértice\n";
	
	cout<<"3.	Recorrido grafo una sola vez por cada arco.\n";
	
	cout<<"4.	Imprima la coloración de cada vértice del grafo.\n";
	
	cout<<"5.	Imprimir la ruta corta (distancia) las ciudades X y Y.\n";
	
	cout<<"6.	Imprimir el tiempo más corto de X a Y.\n";
	
	cout<<"7.	Rutas alternas en caso de cierre de camino.\n";
	
	cout<<"8.	Imprimir la cantidad de usuarios que viajan hacia una ciudad X .\n";
	
	cout<<"9.	Imprimir todas la rutas que realiza el usuario X. .\n";
	
	cout<<"10.	Volver al menu principal.\n";
	
	cout<<"opcion: ";
	
	cin>>desicion;
	cout<<"\n\n";
	
	if(desicion == 1) {
		cout<<"\n\n";
		grafoTransporteEsConexo();
		cout<<"\n\n";
		menu();
	}
	if(desicion == 2){
	
		cout<<"\n\n";
		imprimirPasandoUnaVezPorVertices();
		cout<<"\n\n";	
		menu();
	}
	if(desicion == 3){
		cout<<"\n\n";
		comprobarRestriccionesUnaVezPorArco();
		cout<<"\n\n";
		menu();
	
	}
	
	if(desicion == 4){
		cout<<"\n\n";
		actualizarColoresGrafo();
		actualizarColoresGrafo();
		imprimirVerticesArcosColores();
		cout<<"\n\n";
		menu();
	}

	if(desicion == 5) {
		cout<<"\n\n";
		rutaMasCortaEntrePuntoABDatos();
		cout<<"\n\n";
		menu();
	
	}
	if(desicion == 6){
		cout<<"\n\n";
		tiempoMinimoDeCiudadABDatos();
		cout<<"\n\n";
		menu();
		
	}
	if(desicion == 7){
		/*cout<<"\n\n";
		indicarCualArcoDeseaDejar();
		cout<<"\n\n";
		*/
		cout<<"\n\n";
		string verticeOrigen;
		string verticeDestino;
		cout<<"Vertice origen: ";
		cin>>verticeOrigen;
		cout<<"Vertice destino: ";
		cin>>verticeDestino;
		struct vertice *origen = buscarVertice(verticeOrigen);
		struct vertice *destino = buscarVertice(verticeDestino);
		metodoCaminosAbiertosAuxiliares(origen, destino->nombreCiudad, 0);
	
		menu();
	}
	
	if(desicion == 8){
		cout<<"\n\n";
		pedirInformacionCantidadDeUsuariosViajaX();
		cout<<"\n\n";
		menu();
	
	}

	if(desicion == 9) {
		cout<<"\n\n";
		pedirInformacionTodasLasRutasUsuarioX();
		cout<<"\n\n";
		menu();
	
	}
	if(desicion == 10){
		cout<<"\n\n";
		menu();
		cout<<"\n\n";
		menu();
	}
	
	else{
		cout<<"\nError.. digite una tecla valida.\n";
		menuConsultas();
	}
		
	
}



//principio del programa se cargan datos y demas
//ultima modificacion: 11/10/2015
int main() {
	
	
	cout<<"\n\n----------------------------------------------------------------------\n";
	cout<<"\n*********************   BIENVENIDO AL SISTEMA ***********************\n";
	cout<<"----------------------------------------------------------------------\n\n";
	
	/*
	
	Datos que se encuentran en el archivo arcos y vertices
	
	insertarVertice("A");
	insertarVertice("B");
	insertarVertice("C");

	insertarArco("A",10,"B",9,false);
	insertarArco("B",12,"A",5,false);
	insertarArco("B",20,"C",8,false);
	insertarArco("C",8,"B",2,false);
	insertarArco("C",14,"A",7,false);
	insertarArco("A",15,"C",4,false);
	
	*/
	
	/*
	
	SE encuentra en el archivo rutas
	
	- A,B,C
	- B,A,C
	- A,B,A
	
	*/
	/*
	
	SE encuentra en el archivo conductores
	

	izq		nombre		id		enlace		vehiculo		derecha
-	1		Carlos		10		2			toyota			2
-	-1		Maria		5		-1			Hyundai			-1
-	-1		Rosaria		15		0			Ferrari			-1	
			
	*/
	

	
	cargarDatosDelArchivoVertices();

	
	menu();
	
	return 0;
}
