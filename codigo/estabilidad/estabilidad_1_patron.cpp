/*
	La finalidad de este programa es determinar la convergencia de la red a distintas temperaturas 
*/


#include <iostream>
#include "Hopfield.hpp"
#include <math.h>
#include <fstream>
#include "aleatorios.h"
#include <string>


//CARACTERISTICAS
#define N 900 //Definimos la dimensión de la red
#define paso 50
#define pasos paso*N*N //Indicamos el número de pasos de montecarlo que realizaremos
#define T_max 1.0 //Temperatura maxima del sistema
#define fact 500//Factor que nos indica cada cuanto guardamos los datos
#define T_0 1e-4//Temperatura inicial del sistema
#define T_min 1e-2 //Temperatura a partir de la cual cambiamos el incremento
#define hT 0.1 //Incremento de la temperatura

//Caracterísitcas necesarias a la hora de mostrar el vector por pantalla con un determinado formato
#define f 30
#define c 30

inline double desviacion(string,unsigned int,unsigned int);

using namespace std;

int main(){
	
	//Creamos los vectores para almacenar el patron distorsionado, y el original
	vect::vector v(f,c,N),u(f,c,N),r(f,c,N),z(f,c,N);
	//Variables para almacenar el valor de la función de metropolis y los aleatorios
	//Ademas variables para ir almacenando la energia, promedio
	double fb=0.0,rand=0.0,E=0.0,T=T_0;
	
	string nombre="sistema/final_T_",aux;//Cadena de texto para guardar los ficheros
	//Reservamos espacio en la memoria para no truncar al convertir las temperatuas
	aux.reserve(1000);
	
	//Variable para almacenar la posicion elegida de forma aleatoria, y contar las iteraciones
	unsigned long long int pos=0;//Definimos un contador para ir variando el incremento
	
	int semilla=4313212;
	
	//Iniciamos el generador de aleatorios
	dranini_(&semilla);
	
	//Cremaos la red
	Hopfield H(N);
    
    
	
	//Creamos los ficheros donde almacenaremos los datos
	ofstream Caracteristicas,E_T,M_T,F,Dat;
	
	//Entreamos la red
	if(H.Entrenar("inicio/modelo.dat",1) && z.Leer("inicio/modelo.dat")){
		
		//Guardamos la energia del vector inicial
		Caracteristicas.open("inicio/energia.dat");
		if(Caracteristicas.is_open()){
			E=H.Energia(z);
			Caracteristicas<<0<<"  "<<E<<endl;
			Caracteristicas.close();
		}else cout<<"No se pudo guardar la energia del vector original, revise la ruta"<<endl<<endl;
        
        //Copiamos el patrón
        v=z;
		
		//Generamos el patron de forma aleatoria
		for(unsigned long long int i=0;i<N;i++){
			rand=(double)dranu_();
			
            if(rand<0.5){
                v.v[i]=0;
            }else{
                v.v[i]=1;
            }
		}
		
		//Guardamos el patron deformado
		r=v;
		
		//Abrimos los ficheros donde vamos a guardar la magnetizacion y la energía en función de la temperatura
		E_T.open("caracteristicas/T_Energia.dat");
		M_T.open("caracteristicas/T_solapamiento.dat");
		
		//Comprobamos que estena biertos los archivos
		if(E_T.is_open() && M_T.is_open()){
			
			//Guardamos el estado incial del sistema
// 			if(v.Guardar("sistema/condicion_incial.dat")){
// 			}else cout<<"No se pudo guardar el sistema"<<endl<<endl;
			
			
			do{
				
				//Generamos el nombre del fichero con el que vamos a guardar el estado final
				aux=to_string(T);
				
				//Buscamos eliminar ahora el punto decimal para evitar problema con la extension de los archivos
				for(unsigned int k=0;k<aux.length();k++){
					if(aux[k]=='.')
						aux[k]='_';
				}
			
			
				//Creamos un archivo para obtener almacenar como evoluciona el solapamiento
				Dat.open("caracteristicas/evolucion/"+aux+".dat");
				
                u=v;
                
				//Comprobamos que este abierto el archivo
				if(Dat.is_open()){
				
					//Hacemos evolucionar el sistema empleando el metodo de ising
					for(unsigned long long int i=0;i<pasos;i++){
						
						//Cambiamos solo el spin de la posicion indicada que habiamos modificado antes
						u.v[pos]=v.v[pos];
						
						//ELegimos primero un numero aleatorio distinto de la unidad
						do{
							rand=(double)dranu_();
						}while(rand>=1.0);
						
						//Elegimos una posicion al azar y cambiamos el valor de ese spin
						pos=(unsigned long long int)N*rand;
						
						//Cambiamos el spin en esa posicion
						u.v[pos]=1-u.v[pos];
						
						//Calculamos el valor de la funcion de metropolis
						fb=exp(-H.dE(u,v,pos)/T);
						if(fb>1.0){
							fb=1.0;
						}
						
						//Genereamos un numero aleatorio
						rand=(double)dranu_();
						
						//Comprobamos si el numero aleatorio generado se considera como representante de la distribucion
						if(rand<fb){
							v.v[pos]=u.v[pos];//En caso de serlo, cambiamos el spin
						}
						
						//Guardamos los datos cada 30 iteraciones
						if(i%fact==0){
							Dat<<i<<" "<<H.Solapamiento(v,z,0)<<" "<<H.Energia(v)<<endl;
							Dat.flush();
							//Vertimos los datos del fichero
						}
					}
					
					Dat.close();
				
				}else cout<<"No se pudo almacenar la evolucion del solapamiento"<<endl;
				//Guardamos la energia
// 				E_T<<T<<" "<<H.Energia(v)<<" "<<desviacion("caracteristicas/evolucion/"+aux+".dat",3,3)<<endl;
				
                
                //Guardamos el solapamiento
//                 s=H.Solapamiento(v,z,0);
// 				M_T<<T<<" "<<s<<" "<<abs(s)<<" "<<desviacion("caracteristicas/evolucion/"+aux+".dat",2,3)<<endl;
				
				//Vertimos el buffer en el fichero
				E_T.flush();
				M_T.flush();
				
				
				//Guardamos el estado final al que ha convergido el sistema
				if(v.Guardar(nombre+aux+".dat")){
				}else cout<<"No se pudo guardar el estado final del sistema a "<<T<<" K"<<endl<<endl;
				
				//Volvemos a establecer el sistema desordenado
				v=r;
				
				//Incrementamos la temperatura
				if(T<T_min){
					T*=10.0;
				}else{
					T+=hT;
				}
			
			}while(T<T_max);
			
            //Cerramos los archivos
            E_T.close();
            M_T.close();
            
		}else cout<<"No se pudo abrir los ficheros para guardar la temperatura y el solapamiento"<<endl<<endl;
		
	}else{
		cout<<"Hubo un problema a la hora de entrenar la red, revise si ha introducido bien la dimension de la red, o la ruta del modelo"<<endl<<endl;
		cout<<"Alternativamente, puede haberse producido un problema a la hora de leer vector. Revise la ruta del archivo"<<endl<<endl;
	}
	
	return 0;
}


/******************************************************************
 * Funcion para calcular la desviacion estandar del solapamiento
 * 
 * Entrada:
 *  -Nombre del fichero
 *  -Columna con los datos a los que hay que aplicar la desviacion
 * 
 * Salida:
 * 	-DEsviacion estandar de los datos
******************************************************************/
inline double desviacion(string nombre, unsigned int col,unsigned int col_max){
	
	double datos[(unsigned int)pasos/fact],media=0.0,var=0.0,aux=0.0;
	ifstream F;
	
	//Abrimos el fichero con los datos
	F.open(nombre);
	
	//Comprobamos que este abrierto, y en caso de estarlo hacemos la media de los datos
	if(F.is_open()){
		for(unsigned int j=0;j<pasos/fact;j++){
			for(unsigned int i=1;i<=col_max;i++){
				if(i!=col){
					F>>aux;
				}else{
					F>>datos[j];
				}
			}
			
			//Añadimos los terminos a la media
			media+=datos[j];
		}
		
		//Calculamos la media de los datos
		media=media*(double)fact/(pasos);
		
		F.close();
		
		//Calculamos la varianza de los datos
		for(unsigned int i=0;i<pasos/fact;i++)
			var+=(datos[i]-media)*(datos[i]-media);
		
	}
	
	return sqrt(var/abs((pasos)/fact-1));
}
