#include "Hopfield.hpp"

/*************************************************************************
	Constructor de la red neuronal, asignamos el tamaño de la red y estblecemos 
	la dimension de la matriz inicializandola a 0
	
	Entrada:
		-Dimension de la red
*************************************************************************/
Hopfield::Hopfield(unsigned int n){
	this->n=n;
	
	//Asignamos las posiciones en la memoria de los punteros
	this->w=new double*[this->n];
	
	//Creamos las columans
	for(unsigned int i=0;i<this->n;i++)
		this->w[i]=new double[this->n];
	
	//Inicializamos la matriz de pesos con el valor 0 la matriz de pesos
	for(unsigned int i=0;i<this->n;i++)
		for(unsigned int j=0;j<this->n;j++)
			this->w[i][j]=0.0;
	
}

/*************************************************************************
	Funcion para mostrar por la salida estandar la matriz de pesos y los 
	umbrales
	
	Entrada:
		-Nada
	
	Salida:
		-Nada
*************************************************************************/
void Hopfield::Mostrar(){
	for(unsigned int i=0;i<this->n;i++){
		for(unsigned int j=0;j<this->n;j++){
			cout<<this->w[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl<<endl;
	
	//Mostramos los umbrales
	for(unsigned int i=0;i<this->n;i++){
		cout<<this->umbrales[i]<<"  ";
	}
	
	cout<<endl<<endl;
}

/*************************************************************************
	Funcion para entrenar a la red neuronal, los vectores del entrenamiento 
	estaran en un fichero, cada fila sera un vector, y se leeran las n primeras
	filas indicadas por el argumento para el entrenamiento
	
	Entrada:
		-nombre del fichero con los datos del entrenamiento
		-numero de filas a leer para entrenar la red neuronal
		
	Salida:
		-Confirmacion del entrenamiento de la red neuronal
*************************************************************************/
bool Hopfield::Entrenar(string nombre,unsigned int num){
	
	bool flag=true;//Variable para confirmar si se ha realizado el entrenamiento o no
	ifstream F;//Objeto para leer los datos que se emplearan en el entrenamiento
	short int** datos=nullptr;//Matriz para almacenar el conjunto de datos que se emplearan en el entrenamiento
	this->datos_entrenamiento=nombre;//Guardamos el nombre del fichero con los datos empleados para el entrenamiento
	this->mu=num;//Almacenamos el numero de datos empleados en el entrenamiento de la red
	
	
	//Abrimos y fichero y comprobamos que se haya abierto
	F.open(nombre);
	
	if(F.is_open()){
		
		//Inicializa la matriz que almacenara los datos leidos del archivo
		datos=new short int*[num];
 		this->a=new double[num];//El tamaño es igual al numero de patrones que se van a almacenar
 		this->umbrales=new double[this->n];//Asignamos el vector para guardar los umbrales de disparo
		
		//Creamos las columnas
		for(unsigned int i=0;i<num;i++)
			datos[i]=new short int[this->n];
		
		
		//Leemos los datos de todos los patrones a almacenar
		for(unsigned int i=0;i<num;i++)
			for(unsigned int j=0;j<this->n;j++)
				F>>datos[i][j];

		//Sacamos los valores promedios corresponiente a cada vector del entrenamiento
		for(unsigned int i=0;i<num;i++){
			this->a[i]=0.0;//Inicializamos a 0 en esa posicion
			
			//Recorremos todo el vector para calcular el promedio
			for(unsigned int j=0;j<this->n;j++){
				this->a[i]+=(double)datos[i][j];
			}

			//Calculamos la media
			this->a[i]=(double)this->a[i]/this->n;
			
		}
		
		/*//Calculamos los pesos
		for(unsigned int i=0;i<this->n;i++){
			//Usmaos las propiedades de simetria de al matriz
			for(unsigned int j=i+1;j<this->n;j++){
					//Para elegir el elemento i/j de k-esimo vector
					for(unsigned int k=0;k<num;k++){
						this->w[i][j]+=(2.0*datos[k][i]-1)*(2.0*datos[k][j]-1);
					this->w[j][i]=this->w[i][j];
				}
			}
		}*/
		
		
		//Calculamos los pesos
		for(unsigned int i=0;i<this->n;i++){
			for(unsigned int j=i+1;j<this->n;j++){
				
				//Calculamos sobre todos los archivos
				for(unsigned int k=0;k<num;k++){
					//Dividimos entre la el promedio en cada paso para tener en cuenta los patrones que se generan de forma
					//aletoria como los prefijados
					this->w[i][j]+=(datos[k][i]-this->a[k])*(datos[k][j]-this->a[k])/(this->a[k]*(1-this->a[k]));
				}
				
				//Utilizamos las propiedades de simetria de la matriz
				this->w[i][j]=this->w[i][j]/(this->n);
				this->w[j][i]=this->w[i][j];
			}
		}
		
		//Calculamos los umbrales de disparo
		for(unsigned int i=0;i<this->n;i++){
			this->umbrales[i]=0.0;
			
			//Guardamos el vector con los umbrales
			for(unsigned int j=0;j<this->n;j++){
				this->umbrales[i]+=this->w[i][j];
			}
			this->umbrales[i]/=2.0;
		}
		
		
		//Cerramos el archivo y liberamos la memoria
		F.close();
		
		delete[] datos;
		
	}else flag=false;
	
	return flag;
}

/*************************************************************************
	Funcion para obtener la energia de un vector en esta red neuronal
	
	Entrada:
		-Vector
		
	Salida:
		-Real con la energia del vector
*************************************************************************/
double Hopfield::Energia(vect::vector v){
	
	double E=0.0;//Energia del vector
	
	//Calculamos la enegia del vector
	for(unsigned int i=0;i<this->n;i++){
		for(unsigned int j=0;j<this->n;j++){
			E-=this->w[i][j]*v.v[i]*v.v[j];
		}
		
		E+=2.0*this->umbrales[i]*v.v[i];
	}
	
	return E/2.0;
}

/*************************************************************************
	Evaluamos un vector en la red aplicandole una matriz de pesos
	
	Entrada:
		-Vector
		
	Salida:
		-Vector
*************************************************************************/
vect::vector Hopfield::Evaluar(vect::vector v){
	vect::vector u(this->n);
	
	//Aplicamos al vector la matriz de pesos
	for(unsigned int i=0;i<this->n;i++){
		u.v[i]=0.0;
		for(unsigned int j=0;j<this->n;j++){
			u.v[i]-=this->w[i][j]*v.v[j];
		}
		
		u.v[i]/=2.0;
	}
	
	//Aplicamos la funcion umbral
	for(unsigned int i=0;i<this->n;i++){
		if(u.v[i]<0.5){
			u.v[i]=0;
		}else if(u.v[i]>0.5){
			u.v[i]=1;
		}
	}
	
	
	return u;
}

/*************************************************************************
	Funcion para optimizar la obtencion de la diferencia de energia entre dos
	vectores
	
	Entrada:
		-Vector1: Hace referencia al vector que teniamos antes de aplicar el cambio
		-vector2: Hace referencia al vector obtenemos despues del cambio
		-posicion donde varian
		
	Salida:
		-diferencia de energia
*************************************************************************/
double Hopfield::dE(vect::vector v2,vect::vector v1, unsigned int k){
	//Definimos la variable de la enegia
	double E=0.0;
	
	for(unsigned int i=0;i<this->n;i++){
		E+=this->w[k][i]*v1.v[i]*(v1.v[k]-v2.v[k]);
	}
	
	E+=this->umbrales[k]*(v2.v[k]-v1.v[k]);
	
	return E;
}

/*************************************************************************
	Funcion determinar el coeficiente de solapamiento de un patron
	
	Entrada:
		-Vector
		-Patron alamacenado
		-Vector original
		
	Salida:
		-Coeficiente de solapamiento
*************************************************************************/
double Hopfield::Solapamiento(vect::vector v,vect::vector z,unsigned int k){
	
	double m=0.0;
	
	for(unsigned int i=0;i<this->n;i++){
		m+=(z.v[i]-this->a[k])*(v.v[i]-1/2.0);
	}
	
	//Devolvemos el coeficiente de solapamiento
	return m/(this->a[k]*(1-this->a[k])*this->n);
}
