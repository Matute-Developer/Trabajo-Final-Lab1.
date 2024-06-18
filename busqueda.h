#ifndef BUSQUEDA_H_INCLUDED
#define BUSQUEDA_H_INCLUDED

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

///PROTOTIPADOS
//SELECCIONAR UN ALBUM (LISTA)
int seleccionarAlbumArchivo (char nombreArchivo[]);
//SELECCIONAR UN ARTISTA (LISTA)
int seleccionarArtistaArchivo (char nombreArchivo[]);
//SELECCIONAR UN ARTISTA (POR NOMBRE)
int buscarArtistaNombreArchivo (char nombreArchivo[]);
//SELECCIONAR UN ALBUM (POR NOMBRE)
int buscarAlbumNombreArchivo (char nombreArchivo[]);
//MUESTRA LOS ALBUMES DE UN ARTISTA BUSCADO
void mostrarDiscografiaArtistaSeleccionado (char archivoAlbumes[], char nombreArtista[]);
//MUESTRA LOS ARTISTAS DE UN GENERO BUSCADO
void mostrarArtistaPorGenero (char archivoArtista[], char datoGenero[]);
#endif // BUSQUEDA_H_INCLUDED
