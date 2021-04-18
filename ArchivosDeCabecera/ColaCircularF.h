#ifndef COLACIRCULARF_H_INCLUDED
#define COLACIRCULARF_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "ColaCircularE.h"


/*UTILIDAD: Declaracion de las constantes a utlizar */
#define NOMBREARCHIVO	"colaPersistencia.txt"
#define MAXIMO 		10
#define MINIMO 		1
#define ELEGIR 		4
#define CERO		0


int cola_Vacia(tCola *cola)
/* UTILIDAD: VERIFICA SI LA COLA ESTA VACIA.
   ENTRADAS: NINGUNA.
   SALIDAS : RETORNA 1 SI LA COLA ESTA VACIA Y 0 EN CASO CONTRARIO. */
{
	int vacia = 0;

	if( (*cola).frente == NULL )
		vacia = 1;

	return vacia;
}


void insertarEnCola(tCola *cola, int tElemento)
/* UTILIDAD: INSERTAR UN ELEMENTO DENTRO DE LA COLA CIRCULAR.
   ENTRADAS: NINGUNA.
   SALIDAS : NINGUNA. */
{
	nodoCola *auxiliar = (nodoCola *)malloc(sizeof(nodoCola));

	(*auxiliar).elemento 	= tElemento;
	(*auxiliar).siguiente	= NULL;

	if(cola_Vacia(cola))
		(*cola).frente 	= auxiliar;
	else
		(*cola).final -> siguiente = auxiliar;

	(*cola).final	= auxiliar;
}


void persistenciaCola(tCola *icola)
/* UTILIDAD: Verifica que haya elementos en el archivo y la reconstruye.
   ENTRADAS: Ninguna.
   SALIDAS : Cola dinamica reconstruida. */
{
	FILE *archivo	= fopen(NOMBREARCHIVO, "a+");
	int tElemento	= 0;
	system("clear");
	printf("\nCOLA INICIAL\n");
	if(archivo != NULL)
	{
		fscanf(archivo, "%d", &tElemento);
		while(!feof(archivo))
		{
			printf("--> %d ", tElemento);
			(*icola).insertaCola(icola, tElemento);
			fscanf(archivo, "%d", &tElemento);
		}
		setbuf(stdin, NULL);
		getchar();
	}
	fclose(archivo);
}


void inicializar_Cola(tCola *cola)
/* UTILIDAD: INICIALIZA LA COLA EN ESTADO NULO TANTO EL FRENTE COMO EL FINAL.
   ENTRADAS: COLA CON MEMORIA ASIGNADA.
   SALIDAS : COLA INICIALIZADA. */
{
	(*cola).frente 	= NULL;
	(*cola).final	= NULL;
	persistenciaCola(cola);
}


int consultaFrente(tCola *cola)
/* UTILIDAD: IMPRIME EL VALOR DEL ELEMENTO QUE SE ENCUENTRA EN EL FRENTE.
   ENTRADAS: NINGUNA.
   SALIDAS : RETORNA EL VALOR QUE CONTIENE EL FRENTE. */
{
	return (*cola).frente -> elemento;
}


int pintaMenu()
/* UTILIDAD: Imprime en pantalla el menu de la aplicacion y pide al usuario la opcion a realizar.
   ENTRADAS: Ninguna.
   SALIDAS : Opcion del menu a realizar. */
{
	int eleccion = 0;
	do
	{
		system("clear");
		puts("\n****************** MENU ******************");
		puts("\t[1] INSERTAR EN COLA.");
		puts("\t[2] ELIMINAR EN COLA.");
		puts("\t[3] CONSULTAR FRENTE.");
		puts("\t[4] SALIR.");
		printf("\n\nOpcion: ");
		scanf("%d", &eleccion);
	} while( (eleccion < MINIMO) || (eleccion > ELEGIR) );
	return eleccion;
}


int pideElemento()
/* UTILIDAD: Valida que le de un elemento mayor a 0 para ser insertado en la cola.
   ENTRADAS: Ninguna.
   SALIDAS : Ninguna. */
{
	int elemento = 0;
	do
	{
		printf("\n\nDame Elemento: ");
		scanf("%d", &elemento);
	} while(elemento < MINIMO);
	return elemento;
}


void desenColar(tCola *icola)
/* UTILIDAD: Desencola el frente de cola.
   ENTRADAS: Ninguna.
   SALIDAS : Ninguna. */
{
	nodoCola *auxiliar = (nodoCola *)malloc(sizeof(nodoCola));

	if(!cola_Vacia(icola))
	{
		auxiliar = (*icola).frente;
		(*icola).frente = (*icola).frente -> siguiente;
		if( (*icola).frente == NULL )
			(*icola).final = NULL;
		free(auxiliar);
	}
}


void guardaCola(tCola *cola)
/* UTILIDAD: Guarda en el archivo la cola.
   ENTRADAS: Ninguna.
   SALIDAS : archivo con la cola guardada. */
{
	FILE *archivo 	= fopen(NOMBREARCHIVO, "w");
	int numero 	= 0;

	system("clear");
	printf("\nCOLA FINAL\n");
	if(archivo != NULL)
	{
		while((*cola).frente != NULL)
		{
			numero = consultaFrente(cola);
			fprintf(archivo, "%d\n", numero);
			printf("--> %d ", numero);
			(*cola).desenCola(cola);
		}
		setbuf(stdin, NULL);
		getchar();
	}
	fclose(archivo);
}


void accionCola(int accionMenu, tCola *icola)
/* UTILIDAD: Dependiendo de la opcion que eligio realizara la tarea correspondiente.
   ENTRADAS: Opcion del menu a realizar.
   SALIDAS : Ninguna. */
{
	system("clear");
	switch(accionMenu)
	{
		case 1: (*icola).insertaCola(icola, pideElemento());
			 printf("\nELEMENTO INSERTADO\n");
			 setbuf(stdin, NULL);
			 getchar();
			 break;
		case 2: (*icola).desenCola(icola);
			 printf("\nELEMENTO ELIMINADO\n");
			 setbuf(stdin, NULL);
			 getchar();
			 break;
		case 3: printf("\nFRENTE: %d.\n", (*icola).consultaFrenteC(icola));
			 setbuf(stdin, NULL);
			 getchar();
			 break;
	}
}

void referenciar_fuciones(tCola *cola)
/* UTILIDAD: Apunta a las funciones propias de la cola.
   ENTRADAS: Ninguna.
   SALIDAS : Ninguna. */
{
	(*cola).colaVacia 	= cola_Vacia;		
	(*cola).insertaCola  	= insertarEnCola;		
	(*cola).inicializaCola	= inicializar_Cola;	
	(*cola).consultaFrenteC	= consultaFrente;	
	(*cola).desenCola	= desenColar;
}


void menuCola(void)
/* UTILIDAD: Imprime en pantalla el menu y efectua las acciones para la cola.
   ENTRADAS: Si el archivo contiene elementos recrea la cola circular.
   SALIDAS : Ninguna. */
{
	tCola *colaNormal = (tCola *)malloc(sizeof(tCola));
	int opcion = 0;

	referenciar_fuciones(colaNormal);
	(*colaNormal).inicializaCola(colaNormal);
	do
	{
		opcion = pintaMenu();
		if(opcion != ELEGIR)
			accionCola(opcion, colaNormal);
	} while(opcion != ELEGIR);
	guardaCola(colaNormal);
}

#endif // COLACIRCULARF_H_INCLUDED

