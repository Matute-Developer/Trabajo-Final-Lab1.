#ifndef MUESTRA_H_INCLUDED
#define MUESTRA_H_INCLUDED

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
void mostrarAlbum (Album A);
void mostrarArrayAlbumes (Album B[], int validosB);
void mostrarArtista (Artista A);
void mostrarArrayArtista (Artista artista[], int validosA);
void mostrarArchivoArtista (char archivoNombre[]);
void mostrarSoloArtistaArchivo (char archivoArtista[], int datoArt);
void mostrarArchivoAlbum (char archivoNombre[]);
void mostrarCaja (Caja caja);
void mostrarArchivoCaja (char archivoCaja[]);
void mostrarAlbumInvertido (Album B[], int validosB);
void mostrarSoloArtista (Artista A[], int validosA);
void mostrarArtistaSinAlbum (Artista A);
void mostrarArregloPalabra (int dimF, int dimC, char matriz[dimF][dimC]);
void mostrarSoloDisponibles (char archivoAlbum[]);
void mostrarSoloAgotados (char archivoAlbum[]);
void mostrarArtistaActivos (char archivoArtista[]);
void mostrarArtistaInactivos (char archivoArtista[]);

#endif // MUESTRA_H_INCLUDED
