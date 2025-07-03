/*

	La finalidad de este programa es estudiar el comportamiento de una red de Hopfield a la hora de recordar patrones en función
	de la temperatura. En este caso particularizaremos para el caso de un un único patrón que será leido, almacenado y posteriormente
	distorsionado para hacer evolucionar a la red hasta que converja al mínimo

 
*/


#include <iostream>
#include "Hopfield.hpp"
#include <math.h>
#include <fstream>
#include "aleatorios.h"
#include <time.h>
#include <random>

/*
#define N 100 //Definimos la dimensión de la red
#define paso 10
#define pasos paso*N*N //Indicamos el número de pasos de montecarlo que realizaremos
#define T 1e-5//Temperatura inicial del sistema
#define N_max_patrones 60 //Guardamos el numero maximo de patrones a almacenar
#define crite_estb 3.2e4//Esperamos 10 pasos de montecarlo para que se alcance el estado estacionario
#define fact 500
#define N_rep 50 //Numero de repeticiones del programa
#define N_min 1
*/

//Caracterísitcas necesarias a la hora de mostrar el vector por pantalla con un determinado formato
#define f 20
#define c 20


using namespace std;

inline void desviacion(string,unsigned int,unsigned int,double[],double,unsigned int,double);

int main(){
    
    
    double N,paso,pasos,T,crite_estb;
    
    long long unsigned int fact,N_max_patrones,N_rep,N_min;
    
    cout<<"Dimension del sistema: "<<endl;
    cin>>N;
    cout<<"Numero de pasos a evolucionar: "<<endl;
    cin>>paso;
    
    pasos=paso*N*N;
    
    cout<<"Temperatura del sistema: "<<endl;
    cin>>T;
    
    cout<<"Intervalo de iteraciones para guardar datos: "<<endl;
    cin>>fact;
    
    
    cout<<"Criterio de estabilidad: "<<endl;
    cin>>crite_estb;
    
    cout<<"Numero de maximo de patrones a almacenar: "<<endl;
    cin>>N_max_patrones;
    
    cout<<"Numero de minimo de patrones a almacenar: "<<endl;
    cin>>N_min;
    
    
    cout<<"Numero de repeticiones del experimento: "<<endl;
    cin>>N_rep;
    
    
    
    
    
    
    
	
	//Creamos los vectores para almacenar el patron distorsionado, y el original
	vect::vector v(f,c,N),u(f,c,N),r(f,c,N),z[N_max_patrones];
	//Variables para almacenar el valor de la función de metropolis y los aleatorios
	//Ademas variables para ir almacenando la energia, promedio
	double rand=0.0,promedio_a[N_max_patrones],aux,a,vect[2],a_tabla[N_max_patrones][N_rep][4],res[4],p2;
	
	//Variable para almacenar la posicion elegida de forma aleatoria, y contar las iteraciones
	unsigned long long int pos=0,contador=0;
	
	random_device rd;
	int semilla=0;
	
	//Cremaos la red
	Hopfield* H;
		
	//Creamos los ficheros donde almacenaremos los datos
	ofstream Dat,R;
	ifstream F;
	
		
		
	//Asignamos las componenetes al vector
	for(unsigned int i=0;i<N_max_patrones;i++)
		z[i].Asignar(f,c,N);
    
	
	for(unsigned long long int q=0;q<N_rep;q++){
		
		semilla=(int)1000000.0*(double)rd()/rd.max();
		
		
		//Iniciamos el generador de aleatorios
		dranini_(&semilla);
		
		
		//Generamos un numero N de patrones de forma aleatoria para almacnear en la red
		Dat.open("inicio/modelo.dat");
		
		if(Dat.is_open()){
			for(unsigned long long int i=0;i<N_max_patrones;i++){
				for(unsigned long long int j=0;j<N;j++){
					//Aplicamos esta condicion para que los patrones generados tengan probabilidades distintas y sean ortogonales
					rand=dranu_();
					aux=dranu_();
					if(rand<aux){
						Dat<<1<<" ";
					}else{
						Dat<<0<<" ";
					}
				}
				Dat<<endl;
				
			}        
			Dat.close();
		}else cout<<"No se pudo generar los patrones"<<endl<<endl;
		
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
		}else cout<<"No se pudieron almacenar los patrones originales"<<endl<<endl;
		
		//Abrimos el archivo donde vamos a guardar los datos
		Dat.open("resultados_por_partes/resultados_"+to_string(q)+".dat");
		if(Dat.is_open()){
			
			//Almacenamos el primer patron almacenado
			v=z[0];
			
			//Generamos un patron aleatorio con probabillidad 0.5
			for(unsigned long long int i=0;i<N;i++){
				rand=(double)dranu_();
				
				//Desordenamos los patrones con probabillidad un 10%
				if(rand<0.01){
					v.v[i]=1-v.v[i];
				}
			}
			
			r=v;
			
			//Iniciamos un bucle para recorrer todos los patrones que puede tener la red
			for(unsigned long long int k=1;k<=N_max_patrones;k++){
				
				//Iniciamos la red
				H=new Hopfield(N);
				
				//Entreamos la red
				if(H->Entrenar("inicio/modelo.dat",k)){
						
					u=v;
					
					//Inicializamos los promedios
					for(unsigned long long int i=0;i<N_max_patrones;i++){
						promedio_a[i]=0.0;
					}
					contador=0;
					
					R.open("solapamiento.dat");
					
					
					if(R.is_open()){
					
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
                            p2=1.0/(1.0+exp(H->dE(u,v,pos)/T));
                            
                            rand=(double)dranu_();
                            
                            
                            //Comprobamos si el numero aleatorio generado se considera como representante de la distribucion
                            if(rand<p2){
                                v.v[pos]=u.v[pos];//En caso de serlo, cambiamos el spin
                            }
							
							if(crite_estb<i){
								//Guardamos los solapamientos
								
								a=H->Solapamiento(v,z[0],0);
								promedio_a[0]+=a;
								for(unsigned long long j=1;j<k;j++){
									promedio_a[j]+=H->Solapamiento(v,z[j],j);
								}
								
								if(i%100==0){
 									R<<a<<endl;
								}
							}
						}
						
						R.close();
					}else cout<<"No se pudo guardar la evolucion del solapamiento"<<endl<<endl;
					
					
					//Sacamos el promedio del solapamiento y calculamos el numero de patrones recordados
					for(unsigned long long int i=0;i<k;i++){
						promedio_a[i]=promedio_a[i]/((double)(pasos-crite_estb-1.0));
						
						if(abs(promedio_a[i])>=0.75){
							contador++;
						}
					}
					desviacion("solapamiento.dat",1,1,vect,pasos,fact,crite_estb);
					
					
					//Guardamos los datos
 					Dat<<k<<" "<<vect[0]<<" "<<vect[1]<<" "<<contador<<" "<<(double)k/N<<endl;
					a_tabla[k-1][q][0]=vect[0];
					a_tabla[k-1][q][1]=vect[1];
					a_tabla[k-1][q][2]=(double)contador;
					a_tabla[k-1][q][3]=(double)k/N;
					
					//Reestablecemos la condicion inicial
					v=r;
				
					Dat.flush();
				}else{
					cout<<"Hubo un problema a la hora de entrenar la red, revise si ha introducido bien la dimension de la red, o la ruta del modelo"<<endl<<endl;
					cout<<"Alternativamente, puede haberse producido un problema a la hora de leer vector. Revise la ruta del archivo"<<endl<<endl;
				}
				
				//Liberamos el puntero de la red para eliminar los datos que habia en ella
				delete H;
			}
			
			Dat.close();
		
		}else cout<<"No se pudo guardar los resultados"<<endl<<endl;
	}
	
	Dat.open("resultados.dat");
	
	//Guardamos los resultados
	if(Dat.is_open()){
		
		for(unsigned long long int i=0;i<N_max_patrones;i++){
			
			res[0]=0.0;
			res[1]=0.0;
			res[2]=0.0;
			res[3]=0.0;
            
			for(unsigned long long int j=0;j<N_rep;j++){
				res[0]+=abs(a_tabla[i][j][0]);
				res[2]+=abs(a_tabla[i][j][2]);
				res[3]+=abs(a_tabla[i][j][3]);
			}
			
			for(unsigned long int p=0;p<N_rep;p++){
                res[1]+=((double)res[0]/N_rep-a_tabla[i][p][0])*((double)res[0]/N_rep-a_tabla[i][p][0]);
            }
			
			
			Dat<<i+1<<"	"<<(double)res[0]/N_rep<<"	"<<(double)sqrt(abs(res[1]/(N-1)))<<"	"<<(double)res[2]/N_rep<<"	"<<(double)res[3]/N_rep<<endl;
		}
		
		Dat.close();
	}else cout<<"Nos se pudo guardar los resultados"<<endl;
	
	
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
inline void desviacion(string nombre, unsigned int col,unsigned int col_max,double stac[],double pasos,unsigned int fact,double crite_estb){
	
	double datos[(unsigned int)(pasos-crite_estb)/100+1],media=0.0,var=0.0,aux=0.0,desv;
	ifstream F;
    
    string str;
    
    unsigned int cont=0;
	
	//Abrimos el fichero con los datos
	F.open(nombre);

    
	//Comprobamos que este abrierto, y en caso de estarlo hacemos la media de los datos
	if(F.is_open()){
        
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
