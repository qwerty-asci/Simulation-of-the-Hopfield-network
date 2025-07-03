/*

	La finalidad de este programa es determinar la convergencia del coeficeinte de solapamiento y la energia a disitintas temperaturas variando el numero de patrones
	que hemos almacenado en la red, introduciendo una condicion inicial aleatoria
 
*/


#include <iostream>
#include "Hopfield.hpp"
#include <math.h>
#include <fstream>
#include "aleatorios.h"
#include <string>

//CARACTERISTICAS
#define N 100 //Definimos la dimensión de la red
#define paso 30
#define pasos paso*N*N //Indicamos el número de pasos de montecarlo que realizaremos
#define T_max 1.1 //Temperatura maxima del sistema
#define fact 100//Factor que nos indica cada cuanto guardamos los datos
#define T_0 1e-7//Temperatura inicial del sistema
#define T_min 1e-2 //Temperatura a partir de la cual cambiamos el incremento
#define hT 0.01 //Incremento de la temperatura
#define N_max_patrones 7 //Guardamos el numero maximo de patrones a almacenar
#define crite_estb 1000//Numero de elementos a eliminar de los guardados solo hacer la media a los elementos una vez alcanzado el estado estacionario

//Caracterísitcas necesarias a la hora de mostrar el vector por pantalla con un determinado formato
#define f 10
#define c 10

inline void desviacion(string,unsigned int,unsigned int,double[]);

using namespace std;

int main(){
	
	//Creamos los vectores para almacenar el patron distorsionado, y el original
	vect::vector v(f,c,N),u(f,c,N),r(f,c,N),z[N_max_patrones];
	//Variables para almacenar el valor de la función de metropolis y los aleatorios
	//Ademas variables para ir almacenando la energia, promedio
	double fb=0.0,rand=0.0,E=0.0,T=T_0,vector[2];
	
	string aux;
	
	//Variable para almacenar la posicion elegida de forma aleatoria, y contar las iteraciones
	unsigned long long int pos=0;//Definimos un contador para ir variando el incremento
	
	int semilla=123123;
	
	//Iniciamos el generador de aleatorios
	dranini_(&semilla);
	
	//Cremaos la red
	Hopfield* H;
	
	//Creamos los ficheros donde almacenaremos los datos
	ofstream Caracteristicas,E_T,M_T,Dat;
	ifstream F;
    
    //Asignamos las componenetes al vector
	for(unsigned int i=0;i<N_max_patrones;i++)
		z[i].Asignar(f,c,N);
	
	//Generamos un patron aleatorio con probabillidad 0.5
	for(unsigned long long int i=0;i<N;i++){
		rand=(double)dranu_();
		
		if(rand<0.5){
			v.v[i]=1;
		}else{
			v.v[i]=0;
		}
	}
		
	//Guardamos el patron deformado
	r=v;
	
	//Guardamos el estado incial del sistema
	if(v.Guardar("sistema/condicion_incial.dat")){
	}else cout<<"No se pudo guardar la condicion incial del sistema"<<endl<<endl;
	
	
	//Almacenamos los patrones originales
	F.open("inicio/modelo.dat");
			
	//Comprobamos que se haya abierto el fichero de energia
	if(F.is_open()){
		//Almacenamos los patrones
		for(unsigned int i=0;i<N_max_patrones;i++){
			for(unsigned int j=0;j<N;j++){
				F>>z[i].v[j];
			}
		}
		F.close();
	}else cout<<"No se pudieron almacenar los patrones originales"<<endl;
	
	
	
	//Iniciamos un bucle para recorrer todos los patrones que puede tener la red
	for(unsigned long long int k=2;k<=N_max_patrones;k++){
		
		//Iniciamos la red
		H=new Hopfield(N);
		
		//Reestablecemos la temperatura
		T=T_0;
		
		//Entreamos la red
		if(H->Entrenar("inicio/modelo.dat",k)){
			
			
			//Guardamos la energia del vector inicial
			Caracteristicas.open("caracteristicas/"+to_string(k)+"_patron/energia.dat");
			if(Caracteristicas.is_open()){
				for(unsigned int i=0;i<k;i++){
					E=H->Energia(z[i]);
					Caracteristicas<<i<<"  "<<E<<endl;
				}
				
				Caracteristicas.close();
			}else cout<<"No se pudo guardar la energia del vector original, revise la ruta"<<endl<<endl;
			

			//Abrimos los ficheros donde vamos a guardar la magnetizacion y la energía en función de la temperatura
			E_T.open("caracteristicas/"+to_string(k)+"_patron/T_Energia.dat");
			M_T.open("caracteristicas/"+to_string(k)+"_patron/T_solapamiento.dat");
			
			//Comprobamos que estena biertos los archivos
			if(E_T.is_open() && M_T.is_open()){
			
				do{
					
					//Generamos el nombre del fichero con el que vamos a guardar el estado final
					aux=to_string(T);
					
					//Buscamos eliminar ahora el punto decimal para evitar problema con la extension de los archivos
					for(unsigned int k=0;k<aux.length();k++){
						if(aux[k]=='.')
							aux[k]='_';
					}
				
					//Creamos un archivo para obtener almacenar como evoluciona el solapamiento
					Dat.open("caracteristicas/"+to_string(k)+"_patron/evolucion/"+aux+".dat");
					
					//Comprobamos que este abierto el archivo
					if(Dat.is_open()){
						
						u=v;
					
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
							fb=exp(-H->dE(u,v,pos)/T);
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
								Dat<<i<<" ";
								
								//Almacenamos los solapamientos
								for(unsigned int j=0;j<k;j++){
									Dat<<H->Solapamiento(v,z[j],j)<<" ";
								}
								
								//Almacenamos la energia
								Dat<<H->Energia(v)<<endl;
								
								Dat.flush();
								//Vertimos los datos del fichero
							}
						}
						
						Dat.close();
					
					}else cout<<"No se pudo almacenar la evolucion del solapamiento"<<endl;
					
                    
                    desviacion("caracteristicas/"+to_string(k)+"_patron/evolucion/"+aux+".dat",k+2,k+2,vector);
                    
					//Guardamos la energia
					E_T<<T<<" "<<vector[0]<<" "<<vector[1]<<endl;
					
					//Guardamos el solapamiento respecto a cada temperatura con la estructura:
					//T solapamiento(patron 1) (sigma patron 1) solapamiento(patron 2) (sigma patron 2)....
                    M_T<<T;
					for(unsigned int j=1;j<=k;j++){
                        desviacion("caracteristicas/"+to_string(k)+"_patron/evolucion/"+aux+".dat",j+1,k+2,vector);
						M_T<<" "<<vector[0]<<" "<<vector[1]<<" ";
                    }
					M_T<<endl;
					
					//Vertimos el buffer en el fichero
					E_T.flush();
					M_T.flush();
					
					
					//Guardamos el estado final al que ha convergido el sistema
					if(v.Guardar("sistema/"+to_string(k)+"_patron/"+aux+".dat")){
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
				
				//Cerramos los ficheros
				M_T.close();
				E_T.close();
				
			}else cout<<"No se pudo abrir los ficheros para guardar la temperatura y el solapamiento"<<endl<<endl;
			
		}else{
			cout<<"Hubo un problema a la hora de entrenar la red, revise si ha introducido bien la dimension de la red, o la ruta del modelo"<<endl<<endl;
			cout<<"Alternativamente, puede haberse producido un problema a la hora de leer vector. Revise la ruta del archivo"<<endl<<endl;
		}
		
		//Liberamos el puntero de la red para eliminar los datos que habia en ella
 		delete H;
	}
	
	return 0;
}


/******************************************************************
 * Funcion para calcular la desviacion estandar y el valor medio
 * 
 * Entrada:
 *  -Nombre del fichero
 *  -Columna con los datos a los que hay que aplicar la desviacion
 * 
 * Salida:
 * 	-Nada
******************************************************************/
inline void desviacion(string nombre, unsigned int col,unsigned int col_max,double stac[]){
	
	double datos[(unsigned int)pasos/fact],media=0.0,var=0.0,aux=0.0,desv;
	ifstream F;
    
    string str;
    
    unsigned int cont=0;
	
	//Abrimos el fichero con los datos
	F.open(nombre);
	
	//Comprobamos que este abrierto, y en caso de estarlo hacemos la media de los datos
	if(F.is_open()){
        for(unsigned int i=0;i<crite_estb;i++){
            getline(F,str);
        }
        
		for(unsigned int j=0;!F.eof();j++,cont++){
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
		media=(double)media/((double)cont-1.0);
		
		F.close();
		
		//Calculamos la varianza de los datos
		for(unsigned int i=0;i<cont;i++)
			var+=(datos[i]-media)*(datos[i]-media);
		
	}
	
	desv=sqrt(var/abs((double)cont-2.0));
    
    stac[0]=media;
    stac[1]=desv;
}
