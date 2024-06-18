#ifndef CARGA_H_INCLUDED
#define CARGA_H_INCLUDED

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

///PROTOTIPADO
void agregarAlbumAlArtista (char archivoAlbumes[], Artista *A);
void cargarArtistaConAlbum (char archivoArtista[], char archivoAlbum[]);
Album crearAlbum ();
Artista crearArtista();
void agregarAlbumToArtistaSeleccionado (char archivoArtistas[], char archivoAlbum[], int datoPosicion);
void agregarAlbumToArchivo (char archivoAlbum[], Album B);
void cargarArtistaEnArchivo (Artista A, char nombreArchivo[]);
void cargarAlbumEnArchivo (Album B, char nombreArchivo[]);
void cargarArrayAlbumEnArchivo (Album B[], char nombreArchivo[], int validosB);
void cargarArrayArtistaEnArchivo (Artista A[], char nombreArchivo[], int validosA);
int pasarArchivoToArrayArtista (char archivoNombre[], Artista A[]);
int pasarArchivoToArrayArtistaDinamico (char archivoNombre[], Artista **arregloArtistaDinamico);
int pasarArchivoToArrayAlbum (char archivoNombre[], Album B[]);
int pasarArchivoToArrayAlbumDinamico (char archivoNombre[], Album **arregloAlbumDinamico);
void cargarArregloPalabrasArtista (int dimC, char matriz[][dimC], Artista A[], int validosA);
void cargarArregloPalabrasAlbum (int dimC, char matriz[][dimC], Album B[], int validosB);
Caja crearCaja (Caja C);

#endif // CARGA_H_INCLUDED
