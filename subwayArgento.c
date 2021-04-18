#include <stdio.h>      // libreria estandar
#include <stdlib.h>     // para usar exit y funciones de la libreria standard
#include <string.h>
#include <pthread.h>    // para usar threads
#include <semaphore.h>  // para usar semaforos
#include <unistd.h>


#define LIMITE 50
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//creo estructura de semaforos
struct semaforos {
    sem_t sem_mezclar;
    sem_t sem_salar;
    sem_t sem_usoSarten;
    sem_t sem_hornearPan;
    sem_t sem_armarSandwich;
	//poner demas semaforos aqui
};

//creo los pasos con los ingredientes
struct paso {
   char accion [LIMITE];
   char ingredientes[4][LIMITE];

};

//creo los parametros de los hilos 
struct parametro {
 int equipo_param;
 struct semaforos semaforos_param;
 struct paso pasos_param[8];
};

//funcion para imprimir las acciones y los ingredientes de la accion
void* imprimirAccion(void *data, char *accionIn) {
	struct parametro *mydata = data;
	//calculo la longitud del array de pasos 
	int sizeArray = (int)( sizeof(mydata->pasos_param) / sizeof(mydata->pasos_param[0]));
	//indice para recorrer array de pasos 
	int i;
	for(i = 0; i < sizeArray; i ++){
		//pregunto si la accion del array es igual a la pasada por parametro (si es igual la funcion strcmp devuelve cero)
		if(strcmp(mydata->pasos_param[i].accion, accionIn) == 0){
		printf("\tEquipo %d - accion %s \n " , mydata->equipo_param, mydata->pasos_param[i].accion);
		//calculo la longitud del array de ingredientes
		int sizeArrayIngredientes = (int)( sizeof(mydata->pasos_param[i].ingredientes) / sizeof(mydata->pasos_param[i].ingredientes[0]) );
		//indice para recorrer array de ingredientes
		int h;
		printf("\tEquipo %d -----------ingredientes : ----------\n",mydata->equipo_param); 
			for(h = 0; h < sizeArrayIngredientes; h++) {
				//consulto si la posicion tiene valor porque no se cuantos ingredientes tengo por accion 
				if(strlen(mydata->pasos_param[i].ingredientes[h]) != 0) {
							printf("\tEquipo %d ingrediente  %d : %s \n",mydata->equipo_param,h,mydata->pasos_param[i].ingredientes[h]);
				}
			}
		}
	}
}

//funcion para tomar de ejemplo
void* cortar(void *data) {
	//creo el nombre de la accion de la funcion 
	char *accion = "cortar";
	//creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero). 
	struct parametro *mydata = data;
	//llamo a la funcion imprimir le paso el struct y la accion de la funcion
	imprimirAccion(mydata,accion);
	//uso sleep para simular que que pasa tiempo
	usleep(5000000 );
	//doy la señal a la siguiente accion (cortar me habilita mezclar)
    sem_post(&mydata->semaforos_param.sem_mezclar);
	
    pthread_exit(NULL);
}

void* mezclar(void *data) {
	
	char *accion = "mezclar";
	struct parametro *mydata = data;
	sem_wait(&mydata->semaforos_param.sem_mezclar);
	imprimirAccion(mydata,accion);
	usleep(3000000);
   sem_post(&mydata->semaforos_param.sem_salar);
   pthread_exit(NULL);
}

void* salar(void *data) {
	char *accion = "salar";
	struct parametro *mydata = data;
	sem_wait(&mydata->semaforos_param.sem_salar);
	pthread_mutex_lock(&mutex);
	imprimirAccion(mydata,accion);
	usleep(3000000);
	pthread_mutex_unlock(&mutex);
	sem_post(&mydata->semaforos_param.sem_usoSarten);
   pthread_exit(NULL);
}

void* usoSarten(void *data) {
	char *accion = "usoSarten";
	struct parametro *mydata = data;
	sem_wait(&mydata->semaforos_param.sem_usoSarten);
	pthread_mutex_lock(&mutex);
	imprimirAccion(mydata,accion);
	usleep(3000000);
	pthread_mutex_unlock(&mutex);
	sem_post(&mydata->semaforos_param.sem_hornearPan);
   pthread_exit(NULL);
}

void* hornearPan(void *data) {
	char *accion = "hornearPan";
	struct parametro *mydata = data;
	sem_wait(&mydata->semaforos_param.sem_hornearPan);
	pthread_mutex_lock(&mutex);
	imprimirAccion(mydata,accion);
	usleep(3000000);
	pthread_mutex_unlock(&mutex);
	sem_post(&mydata->semaforos_param.sem_armarSandwich);
   pthread_exit(NULL);
}

void* cortarExtra(void *data) {
	char *accion = "cortarExta";
	struct parametro *mydata = data;
	imprimirAccion(mydata,accion);
	usleep(3000000);
   pthread_exit(NULL);
}

void* armarSandwich(void *data) {
	char *accion = "armarSandwich";
	struct parametro *mydata = data;
	sem_wait(&mydata->semaforos_param.sem_armarSandwich);
	imprimirAccion(mydata,accion);
	usleep(3000000);
   pthread_exit(NULL);
}

void* ejecutarReceta(void *i) {
	
	//variables semaforos
	sem_t sem_mezclar;
	//crear variables semaforos aqui
	sem_t sem_salar;
	sem_t sem_usoSarten;
	sem_t sem_hornearPan;
	sem_t sem_armarSandwich;
	//variables hilos
	pthread_t p1;
	pthread_t p2;
	pthread_t p3;
	pthread_t p4;
	//crear variables hilos aqui
	
	//numero del equipo (casteo el puntero a un int)
	int p = *((int *) i);
	
	printf("Ejecutando equipo %d \n", p);

	//reservo memoria para el struct
	struct parametro *pthread_data = malloc(sizeof(struct parametro));

	//seteo los valores al struct
	
	//seteo numero de grupo
	pthread_data->equipo_param = p;

	//seteo semaforos
	pthread_data->semaforos_param.sem_mezclar = sem_mezclar;
	//setear demas semaforos al struct aqui
	pthread_data->semaforos_param.sem_salar = sem_salar;
	pthread_data->semaforos_param.sem_usoSarten = sem_usoSarten;
	pthread_data->semaforos_param.sem_hornearPan = sem_hornearPan;
	pthread_data->semaforos_param.sem_armarSandwich = sem_armarSandwich;
	//seteo las acciones y los ingredientes (Faltan acciones e ingredientes) ¿Se ve hardcodeado no? ¿Les parece bien?
     	strcpy(pthread_data->pasos_param[0].accion, "cortar");
	    strcpy(pthread_data->pasos_param[0].ingredientes[0], "ajo");
      strcpy(pthread_data->pasos_param[0].ingredientes[1], "perejil");


	    strcpy(pthread_data->pasos_param[1].accion, "mezclar");
	    strcpy(pthread_data->pasos_param[1].ingredientes[0], "ajo");
      strcpy(pthread_data->pasos_param[1].ingredientes[1], "perejil");
 	    strcpy(pthread_data->pasos_param[1].ingredientes[2], "huevo");
	    strcpy(pthread_data->pasos_param[1].ingredientes[3], "carne");
		
		strcpy(pthread_data->pasos_param[2].accion, "salar");
		
		strcpy(pthread_data->pasos_param[3].accion, "usoSarten");
		 
		 strcpy(pthread_data->pasos_param[4].accion, "hornear");
		 strcpy(pthread_data->pasos_param[4].ingredientes[0], "pan");
		 
		 strcpy(pthread_data->pasos_param[5].accion, "cortarExtra");
		 strcpy(pthread_data->pasos_param[5].ingredientes[0], "lechuga");
		 strcpy(pthread_data->pasos_param[5].ingredientes[1], "tomate");
		 strcpy(pthread_data->pasos_param[5].ingredientes[2], "cebolla");
		 strcpy(pthread_data->pasos_param[5].ingredientes[3], "pepino");
		 
		  strcpy(pthread_data->pasos_param[5].accion, "armarSandwich");
		 
		 
		

		


	//inicializo los semaforos

	sem_init(&(pthread_data->semaforos_param.sem_mezclar),0,0);
	//inicializar demas semaforos aqui
	sem_init(&(pthread_data->semaforos_param.sem_salar),0,0);
	sem_init(&(pthread_data->semaforos_param.sem_usoSarten),0,0);
	sem_init(&(pthread_data->semaforos_param.sem_hornearPan),0,0);
	sem_init(&(pthread_data->semaforos_param.sem_armarSandwich),0,0);

	//creo los hilos a todos les paso el struct creado (el mismo a todos los hilos) ya que todos comparten los semaforos 
    int rc;
    rc = pthread_create(&p1,                           //identificador unico
                            NULL,                          //atributos del thread
                                cortar,             //funcion a ejecutar
                                pthread_data);                     //parametros de la funcion a ejecutar, pasado por referencia
	//crear demas hilos aqui
    rc = pthread_create(&p1, 
							NULL,
								mezclar,
								pthread_data);
	
	rc = pthread_create(&p1, 
							NULL,
								salar,
								pthread_data);
								
	rc = pthread_create(&p1, 
							NULL,
								usoSarten,
								pthread_data);
								
	rc = pthread_create(&p1, 
							NULL,
								hornearPan,
								pthread_data);
								
	rc = pthread_create(&p1, 
							NULL,
								cortarExtra,
								pthread_data);
							
	rc = pthread_create(&p1, 
							NULL,
								armarSandwich,
								pthread_data);


	//join de todos los hilos
	pthread_join (p1,NULL);
	pthread_join (p2,NULL);
	pthread_join (p3,NULL);
	pthread_join (p4,NULL);
	//crear join de demas hilos


	//valido que el hilo se alla creado bien 
    if (rc){
       printf("Error:unable to create thread, %d \n", rc);
       exit(-1);
     }

	 
	//destruccion de los semaforos 
	sem_destroy(&sem_mezclar);
	//destruir demas semaforos 
	sem_destroy(&sem_salar);
	sem_destroy(&sem_usoSarten);
	sem_destroy(&sem_hornearPan);
	sem_destroy(&sem_armarSandwich);
	//salida del hilo
	 pthread_exit(NULL);
}


int main ()
{
	//creo los nombres de los equipos
	int rc;
	int *equipoNombre1 =malloc(sizeof(*equipoNombre1));
	int *equipoNombre2 =malloc(sizeof(*equipoNombre2));
	int *equipoNombre3 =malloc(sizeof(*equipoNombre3));
	int *equipoNombre4 =malloc(sizeof(*equipoNombre4));
//faltan equipos

	*equipoNombre1 = 1;
	*equipoNombre2 = 2;
	*equipoNombre3 = 3;
	*equipoNombre4 = 4;

	//creo las variables los hilos de los equipos
	pthread_t equipo1;
	pthread_t equipo2;
	pthread_t equipo3;
	pthread_t equipo4;
//faltan hilos

	//inicializo los hilos de los equipos
    rc = pthread_create(&equipo1,                           //identificador unico
                            NULL,                          //atributos del thread
                                ejecutarReceta,             //funcion a ejecutar
                                equipoNombre1);

    rc = pthread_create(&equipo2,                           //identificador unico
                            NULL,                          //atributos del thread
                                ejecutarReceta,             //funcion a ejecutar
                                equipoNombre2);
    rc = pthread_create(&equipo3,
			    NULL,
				ejecutarReceta,
				equipoNombre3);
    rc = pthread_create(&equipo4,
			    NULL,
				ejecutarReceta,
				equipoNombre4);
  //faltn inicializaciones


   if (rc){
       printf("Error:unable to create thread, %d \n", rc);
       exit(-1);
     }

	//join de todos los hilos
	pthread_join (equipo1,NULL);
	pthread_join (equipo2,NULL);
	pthread_join (equipo3,NULL);
	pthread_join (equipo4,NULL);
//.. faltan joins


    pthread_exit(NULL);
}


//Para compilar:   gcc subwayArgento.c -o ejecutable -lpthread
//Para ejecutar:   ./ejecutable
