#include "muestra.h"
#include <stdio.h>

///FUNCIONES PARA MOSTRAR UN ARRAY DE ALBUMES Y UN ALBUM SOLO
void mostrarAlbum (Album A)
{
    printf("\n===================================");
    printf("\n-NOMBRE: %s", A.nombre);
    printf("\n-ARTISTA: %s", A.artista);
    printf("\n-ANIO: %d", A.anio);
    printf("\n-PRECIO: $%d", A.precio);
    printf("\n-VENTAS: %d", A.ventas);
    if (A.estado == 1)
    {
        printf("\n-ESTADO: DISPONIBLE");
    }
    else
    {
        printf("\n-ESTADO: AGOTADO");
    }
    printf("\n===================================");
}

void mostrarArrayAlbumes (Album B[], int validosB)
{
    int i = 0;

    while (i < validosB)
    {
        printf("\n");
        mostrarAlbum(B[i]);
        i++;
    }
}

///FUNCIONES PARA MOSTRAR UN SOLO Artista
void mostrarArtista (Artista A)
{
    printf("\n=======INFORMACION=======");
    printf("\n-NOMBRE: %s", A.nombre);
    printf("\n-GENERO: %s", A.genero);
    printf("\n-CANTIDAD DE ALBUMES: %d", A.cantAlbumes);
    if (A.estado == 1)
    {
        printf("\n-ESTADO: ACTIVO");
    }
    else
    {
        printf("\n-ESTADO: INACTIVO");
    }
}

void mostrarArrayArtista (Artista artista[], int validosA)
{
    int i = 0;

    while (i < validosA)
    {
        printf("\n");
        mostrarArtista(artista[i]);
        i++;
    }
}

//MOSTRAR ARTISTAS DE UN ARCHIVO
void mostrarArchivoArtista (char archivoNombre[])
{
    FILE *archivo = fopen(archivoNombre, "rb");
    Artista A;
    int i = 1;

    if (archivo != NULL)
    {
        while (fread(&A, sizeof(Artista), 1, archivo)>0)
        {
            printf("\n\nNumero de registro: %d", i++);
            mostrarArtista(A);
        }
        fclose(archivo);
    }
}
//MOSTRAR UN SOLO ARTISTA DE UN ARCHIVO
void mostrarSoloArtistaArchivo (char archivoArtista[], int datoArt) {
    FILE *archivo = fopen(archivoArtista, "rb");
    Artista A;

    if (archivo != NULL) {
        fseek(archivo, sizeof(Artista)*(datoArt-1), SEEK_SET);
        fread(&A, sizeof(Artista), 1, archivo);
        mostrarArtista(A);
        rewind(archivo);
        fclose(archivo);
    }
    else {
        printf("\nEL ARCHIVO NO PUDO ABRIRSE");
    }
}

//MOSTRAR ALBUMES DE UN ARCHIVO
void mostrarArchivoAlbum (char archivoNombre[])
{
    FILE *archivo = fopen(archivoNombre, "rb");
    Album B;
    int i = 1;

    if (archivo != NULL)
    {
        while (fread(&B, sizeof(Album), 1, archivo)>0)
        {
            printf("\n\nNumero de registro: %d", i++);
            mostrarAlbum(B);
        }
        fclose(archivo);
    }
}

//FUNCION PARA MOSTRAR LA CAJA
void mostrarCaja (Caja caja)
{
    printf("\n    INFORMACION DE LA CAJA:");
    printf("\n=================================");
    printf("\n-GANANCIAS TOTALES: $%d", caja.gananciaTotal);
    printf("\n-CANTIDAD DE VENTAS: %d", caja.cantVentas);
    printf("\n=================================\n");
}

void mostrarArchivoCaja (char archivoCaja[]) {
    FILE *archivo = fopen(archivoCaja, "rb");

    if (archivo != NULL) {
        Caja C;
        fread(&C, sizeof(Caja), 1, archivo);
        printf("\n");
        mostrarCaja(C);
        fclose(archivo);
    }
}

//FUNCION PARA MOSTRAR EL ARREGLO DE PALABRAS
void mostrarArregloPalabra (int dimF, int dimC, char matriz[dimF][dimC]) {
    int f = 0;

    for (f = 0; f < dimF; f++) {
        printf("\n( %s )", matriz[f]);
    }
    printf("\n");
}

///OTRAS FUNCIONES DE MUESTRA (PARA MOSTRAR CON MAYOR COMODIDAD LOS ORDENAMIENTO)
void mostrarAlbumInvertido(Album B[], int validosB) ///funcion recursiva
{
    if(validosB!=0){
        mostrarAlbumInvertido(B, validosB-1);
        mostrarAlbum(B[validosB-1]);
    }
}

void mostrarArtistaArray(Artista A[], int validosA) {
    int i = 0;

    while (i < validosA) {
        printf("\n");
        mostrarArtista(A[i]);
        i++;
    }
}

///MOSTRAR SOLO A LOS ALBUMES DISPONIBLES
void mostrarSoloDisponibles (char archivoAlbum[]) {
    FILE *archivo = fopen(archivoAlbum, "rb");

    if (archivo != NULL) {
        Album B;
        while (fread(&B, sizeof(Album), 1, archivo)>0) {
            if (B.estado == 1) {
                mostrarAlbum(B);
            }
        }
        rewind(archivo);
        fclose(archivo);
    }
}
///MOSTRAR SOLO A LOS ALBUMES AGOTADOS
void mostrarSoloAgotados (char archivoAlbum[]) {
    FILE *archivo = fopen(archivoAlbum, "rb");

    if (archivo != NULL) {
        Album B;
        while (fread(&B, sizeof(Album), 1, archivo)>0) {
            if (B.estado == 0) {
                mostrarAlbum(B);
            }
        }
        rewind(archivo);
        fclose(archivo);
    }
}
///FUNCIONES PARA MOSTRAR A LOS ARTISTAS ACTIVOS
void mostrarArtistaActivos (char archivoArtista[]) {
    FILE *archivo = fopen(archivoArtista, "rb");

    if (archivo != NULL) {
        Artista A;
        while (fread(&A, sizeof(Artista), 1, archivo)>0) {
            if (A.estado == 1) {
                printf("\n");
                mostrarArtista(A);
            }
        }
        fclose(archivo);
    }
}
///FUNCIONES PARA MOSTRAR A LOS ARTISTAS INACTIVOS
void mostrarArtistaInactivos (char archivoArtista[]) {
    FILE *archivo = fopen(archivoArtista, "rb");

    if (archivo != NULL) {
        Artista A;
        while (fread(&A, sizeof(Artista), 1, archivo)>0) {
            if (A.estado == 0) {
                printf("\n");
                mostrarArtista(A);
            }
        }
        fclose(archivo);
    }
}
