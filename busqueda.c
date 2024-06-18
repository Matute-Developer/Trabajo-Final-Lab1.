#include "busqueda.h"
#include <stdio.h>

///FUNCIONES PARA SELECCIONAR UN ALBUM O UN ARTISTA, BUSCANDO POR NOMBRE O POR LISTA
//SELECCIONAR UN ALBUM (LISTA)
int seleccionarAlbumArchivo (char nombreArchivo[])
{
    int registros = registrosAlbumes(nombreArchivo);

    int seleccion = 0;
    mostrarArchivoAlbum(nombreArchivo);

    printf("\n-SELECCIONE UN ALBUM: ");
    scanf("%d", &seleccion);

    if ((seleccion <= registros) && (seleccion >= 0)) {
        return (seleccion);
    }
    else {
        printf("\nNO HAY UN ALBUM EN ESA POSICION");
        return -2;
    }
}

//SELECCIONAR UN ARTISTA (LISTA)
int seleccionarArtistaArchivo (char nombreArchivo[])
{
    int registros = registrosArtistas(nombreArchivo);
    int seleccion = 0;

    mostrarArchivoArtista(nombreArchivo);

    printf("\n-SELECCIONE UN ARTISTA: ");
    scanf("%d", &seleccion);

    if ((seleccion <= registros) && (seleccion >= 0)) {
        return (seleccion);
    }
    else {
        printf("\nNO HAY UN ARTISTA EN ESA POSICION");
        return -2;
    }
}

//SELECCIONAR UN ARTISTA (POR NOMBRE)
int buscarArtistaNombreArchivo (char nombreArchivo[]) {
    char datoBusqueda[50];
    printf("\n-Introduce el nombre del artista a buscar: ");
    fflush(stdin);
    gets(datoBusqueda);
    int flag = 0;
    int i = 0;

    FILE *archivo = fopen(nombreArchivo, "rb");

    if (archivo != NULL) {
        Artista A;
        while ((fread(&A, sizeof(Artista), 1, archivo)>0) && (flag==0)) {
        if (strcmpi(A.nombre, datoBusqueda)==0) {
            flag++;
        }
        else {
            i++;
        }
        }
        fclose(archivo);
    }

    if (flag == 1) {
        return (i+1); ///SI ENCONTRO EL ALBUMs RETORNO SU SUBINDICE
    }
    else {
        return -2; ///SI NO RETORNO -1
    }
}
//SELECCIONAR UN ALBUM (POR NOMBRE)
int buscarAlbumNombreArchivo (char nombreArchivo[]) {
    char datoBusqueda[50];
    printf("\n-Introduce el nombre del album a buscar: ");
    fflush(stdin);
    gets(datoBusqueda);
    int flag = 0;
    int i = 0;

    FILE *archivo = fopen(nombreArchivo, "rb");

    if (archivo != NULL) {
        Album B;
        while ((fread(&B, sizeof(Album), 1, archivo)>0) && (flag==0)) {
        if (strcmpi(B.nombre, datoBusqueda)==0) {
            flag++;
        }
        else {
            i++;
        }
        }
        fclose(archivo);
    }

    if (flag == 1) {
        return (i+1); ///SI ENCONTRO EL ALBUM RETORNO SU SUBINDICE
    }
    else {
        return -2; ///SI NO RETORNO -1
    }
}

///MUESTRA TODOS LOS ALBUMES DEL ARTISTA BUSCADO
void mostrarDiscografiaArtistaSeleccionado (char archivoAlbumes[], char nombreArtista[]) {
    FILE *archivo = fopen(archivoAlbumes, "rb");

    if (archivo != NULL) {
        Album B;
        while (fread(&B, sizeof(Album), 1, archivo)>0) {
            if (strcmpi(nombreArtista, B.artista) == 0) {
                mostrarAlbum(B);
            }
        }
        fclose(archivo);
    }
}

///MUESTRA TODOS LOS ARTISTAS DEL GENERO BUSCADO
void mostrarArtistaPorGenero (char archivoArtista[], char datoGenero[]) {
    FILE *archivo = fopen(archivoArtista, "rb");

    if (archivo != NULL) {
        Artista A;
        while (fread(&A, sizeof(Artista), 1, archivo)) {
            if (strcmpi(A.genero, datoGenero)==0) { ///SI EL GENERO COINCIDE MUESTRO EL ARTISTA
                mostrarArtista(A);
                printf("\n");
            }
        }
        fclose(archivo);
    }
}
