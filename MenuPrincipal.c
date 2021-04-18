/************************************************************/
/* Proyecto de Lenguaje de Programación Estructurado        */
/*                                                          */
/* Descripción: En este programa se hace uso de la          */
/*         estructura de una Cola Circular y una Lista      */
/*         Simple para poder realizar inserciones y         */
/*         posteriormente guardar los elementos insertados  */
/*         a cada estructura en archivos de texto.          */
/*                                                          */
/* Integrantes del equipo:                                  */
/*                                                          */
/*                Luis Humberto Ponce Hermosillo            */
/*                José Antonio Sánchez Ovando               */
/*                Juan Carlos Becerril Ruiz                 */
/*                Adrián Terrón Díaz                        */
/*                                                          */
/* Fecha: 24/Mayo/2012                                      */
/************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "ArchivosDeCabecera/ListaSimpleF.h"
#include "ArchivosDeCabecera/ColaCircularF.h"

#define LIMITE 3

//Menu Principal
int main(int args, char *argv[])
{
	int opc = 0;
    	do
	{
		system("clear");
      		printf("\n************Menu De Opciones**********\n");
      		printf("[1] Lista Simple\n");
      		printf("[2] Cola Circular\n");
      		printf("[3] Salir\n\n");
      		printf("Dame Opcion: ");
      		scanf("%d",&opc);
      		switch(opc)
		{
         		case 1:
             			//Ir Al Menu Lista
             			MenuLista();
             			break;
         		case 2:
             			//Ir Al Menu Cola
             			menuCola();
             			break;
         		case 3:
             			//Salir Del Menu y del Programa
             			opc = 3;
             			break;
         		default:
            			printf("Opcion Incorrecta\n");
            			break;
        	}
    	} while(opc != LIMITE);
    return 0;
}

