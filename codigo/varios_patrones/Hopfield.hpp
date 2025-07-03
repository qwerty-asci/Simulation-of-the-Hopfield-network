#ifndef HOPFIELD_HPP_INCLUDED
#define HOPFIELD_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <fstream>

using namespace std;


/*************************************************************************
	Estructura para trabajar con vectores de una dimension arbitraria
	
	Herencia:
		-Ninguna
	
	Atributos:
		-v: Puntero para almacenar el vector de dimension arbitaria
		
		-n: Dimension del vector
	
	Metodos:
		-Constructor: Le indicamos el tamaño del vector
		
		-Constructor: Le indicamos el tamaño del vector, ademas el numero de
		filas y columnas con el que tendra que guardarlo luego
		
		-Constructor: Constructor estandar que no pide parametros
		
		-Leer: Leemos el vector de un archivo
		
		-Guardar: Guardamos el vector en un archivo
		
		-Mostrar: Mostramos el vector por pantalla
		
		-Asignar: Asignamos el numero de filas y el numero de columnas al vector
	
	Operadores:
		= sobreescribimos el operador de asignacion
	
*************************************************************************/
namespace vect{
	struct vector{
		private:
			
		public:
			
			//Creamos el vector junto con su dimension
			double* v;
			unsigned int n;
			
			//Variables para saber el numero de filas y columnas del archivo
			unsigned int f=0,c=0;
			
			//Definimos el constructor
			vector(unsigned int);
			vector(unsigned int,unsigned int,unsigned int);
			vector(void){};
		
			//Metodos para manupular y guardar el contenido del vector
			bool Leer(string);
			bool Guardar(string);
			
			//Mostrar el vector por pantalla
			void Mostrar();
			void Asignar(unsigned int,unsigned int,unsigned int);
			
			//Definimos el operador copiar
			void operator = (vector);
	};
}



/*************************************************************************
 
 Clase para crear una red neuronal de Hopfield, trabajara con en binario donde
 el estado 0 representará apagado y el estado 1 sera activado.
 
 Herencia:
	-Ninguna
 
 -Atributos:
	-n: Numero de neuronas que tendrá la red
	
	-w: Matriz de pesos de la red neuronal
	
	-datos_entrenamiento: string para guardar el nombre del fichero empleado
	
	para entrenar la red neuronal
	
	-mu: numero de modelos empleados para el entrenamiento de la red
	
	-a: vector para guardar los promedios almacenados de cada modelo del entrenamiento
	
	-umbrales: Vector para almacenar los umbrales de disparo
 
 -Metodos:
	-Constructor: Le indicamos el numero de neuronas que tendra la red
	
	-Mostrar: Mostramos la matriz de pesos por la salida estandar
	
	-Entrenar: Funcion para leer los vectores para el entrenamiento	
	
	-Energia: Obtener la energia de un vector en la red
	
	-Evaluar: Evaluamos un vector en la red por la matriz de pesos
	
	-DE: Funcion para optimizar la obtencion de la diferencia de energía entre
	dos vectores que se diferencia en una unica componente
	
	-Solapamiento: Función para determinar en cuanto coinciden el patrón original
	con el obtenido por la red neuronal
 
*************************************************************************/

class Hopfield{

	private:
		
		double** w=nullptr;
		double* a=nullptr;
		double* umbrales=nullptr;
		unsigned int n,mu;
		string datos_entrenamiento;
		
	public:
		
		//Constructores
		Hopfield(unsigned int);
		
		//Entrada y salida estandar
		void Mostrar();
		
		//Funcionamiento de la red
		bool Entrenar(string,unsigned int);
		double Energia(vect::vector);
		vect::vector Evaluar(vect::vector);
		double dE(vect::vector,vect::vector,unsigned int);
		double Solapamiento(vect::vector,vect::vector,unsigned int);
	
};


#endif //HOPFIELD_HPP_INCLUDED
