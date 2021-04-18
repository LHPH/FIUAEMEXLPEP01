#ifndef LISTASIMPLEF_H_INCLUDED
#define LISTASIMPLEF_H_INCLUDED

#include "ListaSimpleE.h"
#include <string.h>


#define uno 1


void inicializacion (Lista *lista)
//Esta función inicializa el puntero inicio y el puntero fin con NULL, y el tamaÃ±o con el valor 0.
{
	lista->inicio 	= NULL;
	lista->fin 	= NULL;
	lista->tam 	= 0;
}


int ins_en_lista_vacia (Lista * lista, char *dato)
//Se realiza una inserción en una lista vacía
{
	Elemento *nuevo_elemento;

        if ((nuevo_elemento = (Elemento *) malloc (sizeof (Elemento))) == NULL)
        {
            return -1;
        }

        //La función strcpy fue utilizada para copiar el contenido de una cadena de caracteres fuente en una variable destino
        strcpy (nuevo_elemento->dato, dato);  //se copia el dato al nodo

        nuevo_elemento->siguiente = NULL;   //puesto que esta vacia el nodo apunta null
        lista->inicio = nuevo_elemento;     //elemento inicial
        lista->fin = nuevo_elemento;        //elemento final e inicial igual
        lista->tam++;                       //se aumenta el tamaño de la lista

        return 0;
}


int ins_inicio_lista (Lista * lista, char *dato)
//Con esta función se realiza la inserción al inicio de la lista
{
        Elemento *nuevo_elemento;

        if ((nuevo_elemento = (Elemento *) malloc (sizeof (Elemento))) == NULL)
        {
            return -1;
        }
        strcpy (nuevo_elemento->dato, dato);
        nuevo_elemento->siguiente = lista->inicio;   //se referencia el apuntador siguiente del nodo al nodo inicio de lista
        lista ->inicio = nuevo_elemento;     //se referencia el apuntador inicio al nodo nuevo insertado al principio
        lista ->tam++;

        return 0;
}

   
int ins_fin_lista (Lista * lista, Elemento * actual, char *dato)
//Se hace una inserción al final de la lista
{
        Elemento *nuevo_elemento;

        if ((nuevo_elemento = (Elemento *) malloc (sizeof (Elemento))) == NULL)
        {
            return -1;
        }

        strcpy (nuevo_elemento->dato, dato);
        actual->siguiente = nuevo_elemento;  //se referencia el apuntador siguiente del ultimo nodo de la lista al nuevo nodo
        nuevo_elemento->siguiente = NULL;   //se referncia el nodo nuevo a null ya que es el ultimo
        lista ->fin = nuevo_elemento;   //se referencia el apuntador fin de la lista al nuevo nodo
        lista ->tam++;

        return 0;
}

    
int ins_lista (Lista * lista, char *dato, int pos)
//Insercion en la posicion solicitada
{
	if (lista ->tam < 2)
        {
            return -1;
        }

        if (pos < 1 || pos >= lista ->tam)
        {
            return -1;
        }

        Elemento *actual;    		//nodo auxiliar elemento auxiliar
        Elemento *nuevo_elemento;    	//nuevo nodo a insertar

        int i;

        if ((nuevo_elemento = (Elemento *) malloc (sizeof (Elemento))) == NULL)
        {
            return -1;
        }

        actual = lista ->inicio;   	//se referencia el nodo inicial de la lista para encontrar la posicion a insertar
        for (i = 1; i < pos; ++i)
        {
            actual = actual->siguiente;
        }

        if (actual->siguiente == NULL)	// es el ultimo elemento lo que causaria un error
        {
            return -1;       		//retorna un -1 y finaliza la ejecucion del metodo
        }

        strcpy (nuevo_elemento->dato, dato);

        nuevo_elemento->siguiente = actual->siguiente;	//se referencia el nuevo nodo al nodo siguiente
        actual->siguiente = nuevo_elemento;   		//se referencia el nodo auxiliar (actual) al nuevo nodo y se une la lista
        lista ->tam++;

        return 0;
}


int elim_inicio (Lista * lista)
// Eliminación de un elemento al inicio de la lista
{
        if (lista ->tam == 0)
        {
        return -1;
        }
        //Elemento *sup_elemento;
        //sup_elemento = lista ->inicio;
        lista ->inicio = lista ->inicio->siguiente;
        if (lista ->tam == 1)
        {
            lista ->fin = NULL;
        }
        //free (sup_elemento->dato);
        //free (sup_elemento);
        lista ->tam--;

        return 0;
}


int elim_en_lista (Lista * lista, int pos)
// ELiminación de un elemento después de la posición solicitada
{
        if (lista ->tam <= 1 || pos < 1 || pos >= lista ->tam)
        {
            return -1;
        }
        int i;
        Elemento *actual;
        //Elemento *sup_elemento;
        actual = lista ->inicio;

        for (i = 1; i < pos; ++i)
        {
            actual = actual->siguiente;
        }

        //sup_elemento = actual->siguiente;
        actual->siguiente = actual->siguiente->siguiente;
        if(actual->siguiente == NULL)
        {
            lista ->fin = actual;
        }
        //free (sup_elemento->dato);
        //free (sup_elemento);
        lista ->tam--;
        
	return 0;
}

    
void muestra (Lista * lista)
//Con esta función se puede visualizar la lista en pantalla
{
        Elemento *actual;
        actual = lista->inicio;
        printf("\n");
        printf("Elementos de la lista: ");
        while (actual != NULL)
        {
            printf ("%s;", actual->dato);   //imprime el dato del nodo
            actual = actual->siguiente;   //recorre la lista elemento por elemento
        }
        printf("\n");
        printf("\n");
}

void VerDatos(Lista *list)
{

        FILE * Fichero = fopen("listaPersistencia.txt", "r");

        if(Fichero == NULL)
        {
                       return;
        }
        char  aux[50];
        fread(&aux, sizeof(aux), uno, Fichero);

        while(!feof(Fichero))
        {
               	if (list->tam == 0)
		{
                        //Si la lista resulta vacia se inserta el elemento usando la siguiente función
                        ins_en_lista_vacia (list, aux);
               	}
		else
		{
                        //Si la lisa no esta vacía se hace la inserción con la siguiente función
                        ins_fin_lista (list, list->fin, aux);
		}
		fread(&aux, sizeof(aux), uno, Fichero);
        }

        fclose(Fichero);
        muestra(list);
}


void meter (Lista * list)
{
        Elemento *actual;
        actual = list->inicio;
        printf("\n");
        printf("Respaldando informacion espere ...\n");
        FILE *  arch = fopen("listaPersistencia.txt", "w");
        fclose(arch);
        while (actual != NULL)
        {

               arch = fopen("listaPersistencia.txt", "a+");  //se abre el archivo para escritura y añadir registro
               if(arch != NULL)
               {
                       fwrite(actual->dato, sizeof(char[50]), uno, arch);
                       fclose(arch);
                       actual = actual->siguiente;   //recorre la lista elemento por elemento
                }
        }
}


int menu (Lista *lista)
{
        int eleccion;
        printf("****************** MENU ******************\n");
        //Este menu se muestra si aun no hay elementos insertados en la lista
        if (lista ->tam == 0)
        {
            printf ("[1] Insercion del primer elemento\n");
            printf ("[4] Quitar\n");
        }

        //Este menu se muestra cuando ya hay un elemeno en la lista
        else if(lista ->tam == 1 ){
            printf ("[1] Insercion al inicio de la lista\n");
            printf ("[2] Insercion al final de la lista\n");
            printf ("[4] Eliminación al inicio de la lista\n");
            printf ("[6] Quitar\n");
        }

        //El siguiente menu se muestra cuando ya hay mas de un elemeno en la lista
        else
        {
            printf ("[1] Insercion al inicio de la lista\n");
            printf ("[2] Insercion al final de la lista\n");
            printf ("[3] Insercion despues de la posicion indicada\n");
            printf ("[4] Eliminación al inicio de la lista\n");
            printf ("[5] Eliminación después de la posición  indicada\n");
            printf ("[6] Quitar\n");
        }

        printf ("\nElegir: ");
        scanf ("%d", &eleccion);
        getchar();
        if(lista->tam == 0 && eleccion == 2)
        {
            eleccion = 6;
        }

        return eleccion;
}

    
void MenuLista()
//Menu principal para el manejo de la lista simple
{
        int eleccion;
        char *elem;
        Lista *lista;  //Declaracion de la lista
        //La función malloc se uso para solicitar un bloque de memoria del tamaño suministrado como parámetro
        if ((lista = (Lista *) malloc (sizeof (Lista))) == NULL)
        {
            return ;    //termina la ejecucion el programa si no se pudo asignar memoria a la lista
        }
        if ((elem = (char *) malloc (50)) == NULL)
        {
            return ;
        }
        eleccion = 0;

        //Referencia a funciones dentro de la estructura
        lista->Inicia=inicializacion;
        lista->InsVac=ins_en_lista_vacia;
        lista->InsIni=ins_inicio_lista;
        lista->InsFin=ins_fin_lista;
        lista->InsPos=ins_lista;
        lista->elimInicio=elim_inicio;
        lista->elimPos=elim_en_lista;
        lista->Most=muestra;

        //Se inicializa el puntero inicio y el puntero fin con el puntero NULL, y el tamaño con el valor 0.
        //Para esto se uso la siguiente funcion
        //inicializacion (lista);
        lista->Inicia(lista);
        int pos;
        VerDatos(lista);

        while (eleccion!= 6)
        {
            eleccion = menu (lista);
            switch (eleccion)
            {
                //En el primer caso se inserta un elemento al inicio de la lista
                case 1:
                    system("clear");
                    printf ("Ingrese un elemento : ");
                    gets(elem);
                    //Primero se comprueba si la lista esta vacÃ­a
                    if (lista->tam == 0)
                    {
                        //Si la lista resulta vacia se inserta el elemento usando la siguiente función
                        //ins_en_lista_vacia (lista, elem);
                        lista->InsVac(lista,elem);
                    }

                    else
                    {
                        //Si la lisa no esta vacía se hace la inserción con la siguiente funciÃ³n
                        //ins_inicio_lista (lista, elem);
                        lista->InsIni(lista,elem);
                        printf("\n");
                        //Se imprime el tamaño de la lista, el dato inicial y el dato final
                        printf ("La lista tiene %d elementos: Inicial=%s,Final=%s\n", lista->tam,lista->inicio->dato, lista->fin->dato);
                        //muestra (lista);
                        lista->Most(lista);  //Se muestran los elementos de la lista
                    }
                break;

                //En el segundo caso se hace la inserción al final de la lista
                case 2:
                    system("clear");
                    printf ("Ingrese un elemento: ");
                    gets(elem);
                    //Para realizar la inserción al final de la lista se usa la siguiente función
                    //ins_fin_lista (lista, lista->fin, elem);
                    lista->InsFin(lista,lista->fin,elem);
                    printf("\n");
                    printf ("La lista tiene %d elementos: Inicial=%s,Final=%s\n", lista->tam,
                    lista->inicio->dato, lista->fin->dato);
                    //muestra (lista);
                    lista->Most(lista);
                break;

                //En el tercer caso se hace la inserción despues de una posición indicada
                case 3:
                    system("clear");
                    //Primero se pide el elemento a insertar
                    printf ("Ingrese el elemento: ");
                    gets(elem);
                    do{
                        //Despues se pide la posición para insertar el elemento despues de la misma
                        printf ("Ingrese la posicion: ");
                        scanf ("%d", &pos);
                    }
                    while (pos < 1 || pos > lista->tam);
                    getchar ();
                    //Esta condición se realiza si se quiere insertar un elemento en una posición que excede a las posiciones de la lista
                    if (lista->tam == 1 || pos == lista->tam)
                    {
                        printf("-----------------------------------------------\n");
                        printf("Posición erronea \n");
                        printf("-----------------------------------------------\n");
                        //muestra (lista);
                        lista->Most(lista);
                break;
                    }
                    //Con esta funcion se inserta el elemento en la lista en una posición solicitada
                    //ins_lista (lista, elem, pos);
                    lista->InsPos(lista,elem,pos);
                    printf("\n");
                    printf ("La lista tiene %d elementos: Inicial=%s,Final=%s\n", lista->tam,lista->inicio->dato, lista->fin->dato);
                    //muestra (lista);
                    lista->Most(lista);
                break;

                case 4:
                    //elim_inicio (lista);
                    lista->elimInicio(lista);//Función para eliminar un elemento al inicio de la lista
                    if (lista->tam != 0){
                        printf ("%d elementos:ini=%s,fin=%s\n", lista->tam,
                        lista->inicio->dato, lista->fin->dato);
                        }
                    else
                    {
                        printf ("lista vacia\n");
                    }
                    //muestra (lista);
                    lista->Most(lista);
                break;

                case 5:
                    do{
                        printf ("Ingrese la posicion : ");
                        scanf ("%d", &pos);
                      }while (pos < 1 || pos > lista->tam);
                    getchar ();
                    //elim_en_lista
                    lista->elimPos(lista,pos); // Función que eliminara un elemento ubicado después de una posición indicada
                    if (lista->tam != 0)
                    {
                        printf ("%d elementos:ini=%s,fin=%s\n", lista->tam,
                        lista->inicio->dato, lista->fin->dato);
                    }
                    else
                    {
                        printf ("lista vacia\n");
                    }
                    //muestra (lista);
                    lista->Most(lista);
                break;

                case 6:  meter(lista);
                break;

                default: printf("Opción no válida");
            }
        }
        free(elem);
        free(lista);

}

#endif // LISTASIMPLEF_H_INCLUDED

