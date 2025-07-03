#include "Hopfield.hpp"

/*************************************************************************
	Constructor por defecto para inicializar las componentes del vector a 0
	y establecer su dimension
	
	Entrada:
		-Dimension del vector
	
	Salida:
		-nada
*************************************************************************/
vect::vector::vector(unsigned int n){
	
	this->n=n;
	
	v=new double[this->n];
	
	for(unsigned int i=0;i<this->n;i++)
		this->v[i]=0.0;
}

/*************************************************************************
	Constructor por defecto para inicializar las componentes del vector a 0
	establecemos tambien su dimension junto con las filas y columnas para guardar
	posteriormente el vector en un archivo
	
	Entrada:
		-Dimension del vector
		-Numero de filas
		-Numero de columnas
	
	Salida:
		-nada
*************************************************************************/
vect::vector::vector(unsigned int filas,unsigned int columnas,unsigned int n){
	
	this->f=filas;
	this->c=columnas;
	
	this->n=n;
	
	v=new double[this->n];
	
	for(unsigned int i=0;i<this->n;i++)
		this->v[i]=0.0;
}

/*************************************************************************
	Metodo para leer los datos de un archivo y guardarlos en un vector
	
	Entrada:
		-nombre del archivo
	
	Salida:
		-boolenado indicando si se ha leido o no el archivo
*************************************************************************/

bool vect::vector::Leer(string nombre){
	
	ifstream F;
	bool flag=true;
	
	F.open(nombre);
	
	if(F.is_open()){
		
		//Leemos datos dl fichero hasta rellenar la dimension del vector
		for(unsigned int i=0;i<this->n;i++)
			F>>this->v[i];
		
		F.close();
		
	}else{ 
		flag=false;
	}
	
	return flag;
}

/*************************************************************************
	Metodo para guardar los datos de un vector en un archivo
	
	Entrada:
		-nombre del archivo
	
	Salida:
		-boolenado indicando si se ha guardado o no el archivo
*************************************************************************/

bool vect::vector::Guardar(string nombre){
	
	ofstream F;
	bool flag=true;
	unsigned int fil=0,col=0;//Contador para contar el numero de filas
	
	//Abrimos el archivo de manera que empiece a escribir por el final
	F.open(nombre,ofstream::app);
	
	if(F.is_open()){
		
		//Guardamos el vector en el fichero
		for(unsigned int i=0;i<this->n;i++){
			//Solo guardamos el spin 1
			if(this->v[i]==1)
				F<<fil<<"  "<<col<<"  "<<v[i]<<endl;
			
			col++;
			//ariamos las coordenadas
			if(col==this->c){
				col=0;
				fil++;
			}
		}
		
		F<<endl<<endl;
		
		F.close();
		
	}else{
		//Indicamos que no se ha podido leer el archivo
		flag=false;
	}
	
	return flag;
}


/*************************************************************************
	Definimos el operador copiar
	
	Entrada:
		-vector
	
	Salida:
		-vector
*************************************************************************/
void vect::vector::operator =(vector v){
	
	//Copiamos el numero de filas
	this->f=v.f;
	this->f=v.c;
	
	//Copiamos el contenido del vector
	if(this->n<=v.n){
		for(unsigned int i=0;i<this->n;i++)
			this->v[i]=v.v[i];
	}else{
		for(unsigned int i=0;i<v.n;i++)
			this->v[i]=v.v[i];
	}
}



/*************************************************************************
	Metodo para mostrar los datos del vector por pantalla
	
	Entrada:
		-Nada
	
	Salida:
		-Nada
*************************************************************************/
void vect::vector::Mostrar(){
	
	unsigned int cont=0;
	
	for(unsigned int j=0;j<this->f;j++){
		for(unsigned int i=0;i<this->c;i++){
			if(cont<this->n)
				cout<<this->v[cont]<<" ";
			cont++;
		}
		cout<<endl;
	}
	cout<<endl;
}

/*************************************************************************
	Asignamos el numero de filas y columnas al vector z
	
	Entrada:
		-Filas
		-Columnas
		-numero de componenentes
	
	Salida:
		-Nada
*************************************************************************/
void vect::vector::Asignar(unsigned int f,unsigned int c,unsigned int n){
	
	this->f=f;
	this->c=c;
	this->n=n;
	
	//Inicializamos el vector
	v=new double[this->n];
	
	for(unsigned int i=0;i<this->n;i++)
		this->v[i]=0.0;
}
