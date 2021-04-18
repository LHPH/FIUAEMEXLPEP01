#ifndef COLACIRCULARE_H_INCLUDED
#define COLACIRCULARE_H_INCLUDED

/* UTILIDAD: Declaracion de las estructuras a usar durante la aplicacion*/
typedef struct tNodo
{
	int		elemento;
	struct tNodo	*siguiente;
} nodoCola;


typedef struct tCola
{
	nodoCola	*frente;
	nodoCola	*final;
	int 		(*colaVacia) 		(struct tCola *);
	void 		(*inicializaCola) 	(struct tCola *);
	int 		(*consultaFrenteC) 	(struct tCola *);
	void 		(*desenCola)		(struct tCola *);
	void 		(*insertaCola) 		(struct tCola *, int);
} tCola;


#endif // COLACIRCULARE_H_INCLUDED
