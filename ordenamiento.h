#ifndef ORDENAMIENTO_H_INCLUDED
#define ORDENAMIENTO_H_INCLUDED

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

///FUNCIONES DE ORDENAMIENTO
void insercionVentas (Album B[], int validosB);
void insertarVenta (Album B[], int pos, Album dato);
void insercionAnio (Album B[], int validosB);
void insertarAnio (Album B[], int pos, Album dato);
void insercionCantidad (Artista A[], int validosA);
void insertarCantidad (Artista A[], int pos, Artista dato);
void seleccionNombre(int dimC, char matriz[][dimC], int cantidadPalabras);
int hallarPosMenor (int dimC, char matriz[][dimC], int pos, int cantidadPalabras);
#endif // ORDENAMIENTO_H_INCLUDED
