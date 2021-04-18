#ifndef LISTASIMPLEE_H_INCLUDED
#define LISTASIMPLEE_H_INCLUDED


typedef struct ElementoLista
//Aqui se define el elemento de la lista
{
	char			dato [50];
	struct ElementoLista 	*siguiente;   //Apuntador al siguiente nodo (Elementolista)
}Elemento;  //alias para la estructura


typedef struct Lista
/*Aquí­ se tendra el control de la lista donde:
  El puntero inicio contendrá la dirección del primer elemento de la lista.
  El puntero fin contendrá la dirección del último elemento de la lista.
  La variable tam contiene el número de elementos.*/
{
	Elemento *inicio;   	//nodo inicial
	Elemento *fin;      	//nodo final
	int 	 tam;           //tamaño de la lista actual total de nodos
	void 	 (*Inicia)	(struct Lista *);
	void 	 (*Most)  	(struct Lista *);
	int 	 (*elimInicio)	(struct Lista *);
	int 	 (*elimPos)	(struct Lista *,int);
	int 	 (*InsVac)	(struct Lista *, char *);
	int 	 (*InsIni)	(struct Lista *, char *);
	int 	 (*InsPos)	(struct Lista *, char*, int);
	int 	 (*InsFin)	(struct Lista *, Elemento *, char*);
} Lista;    //alias para la estructura


#endif // LISTASIMPLEE_H_INCLUDED
