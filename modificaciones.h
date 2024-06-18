#ifndef MODIFICACIONES_H_INCLUDED
#define MODIFICACIONES_H_INCLUDED

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

void modificarArtistaAeleccion (char nombreArchivo[], char archivoAlbumes[], int posicion);
Artista modificarDatosArtista(Artista A, char archivoAlbumes[]);
void guardarNombreEnAlbumes(char archivoAlbumes[], char nombreAntiguo[], char nombreModificado[]);
void modificarAlbumAeleccion (char nombreArchivo[], int posicion);
Album modificarDatosAlbum (Album B);
void darDeBajaArtista (char nombreArchivo[], char archivoAlbumes[], int posicion);
void darDeAltaArtista (char nombreArchivo[], char archivoAlbumes[], int posicion);
void darDeBajaDiscografia (char archivoAlbumes[], char nombreArtista[]);
void darDeAltaDiscografia (char archivoAlbumes[], char nombreArtista[]);
void darDeBajaAlbum (char nombreArchivo[], int posicion);
void darDeAltaAlbum (char nombreArchivo[], int posicion);
int registrosAlbumes (char nombreArchivo[]);
int registrosArtistas (char nombreArchivo[]);

#endif // MODIFICACIONES_H_INCLUDED
