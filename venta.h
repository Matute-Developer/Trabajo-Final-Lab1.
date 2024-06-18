#ifndef VENTA_H_INCLUDED
#define VENTA_H_INCLUDED
#include "pila.h"

///ESTRUCTURAS
typedef struct
{
    char nombre[30];
    char artista[30]; //EL NOMBRE DEL ARTISTA AL QUE PERTENCE EL ALBUM
    int anio;
    int precio;
    int ventas; //LA CANTIDAD DE VENTAS QUE TIENE UN ALBUM
    int estado; //1-ESTA DISPONIBLE 0-NO ESTA DISPONIBLE
} Album;

typedef struct
{
    char nombre[30];
    char genero[30];
    int cantAlbumes; //LA CANTIDAD DE ALBUMES QUE TIENE EL ARTISTA
    Album albumes[10];
    int estado;
} Artista;

typedef struct
{
    int gananciaTotal; //LA SUMA DE LAS VENTAS
    int cantVentas; //(la cantidad de albumes que se vendieron)
} Caja;

void apilarAlbumVendido (Pila *VENTAS, char nombreArchivo[], int posicion);
/*void devengarVentas (Caja *caja, Pila *VENTAS, Pila *DEVENGADO);*/
void devengarVentas (char archivoCaja[], Pila *VENTAS, Pila *DEVENGADO);
void devengarVentasAux(char archivoCaja[], Pila *VENTAS, Pila *DEVENGADO);
#endif // VENTA_H_INCLUDED
