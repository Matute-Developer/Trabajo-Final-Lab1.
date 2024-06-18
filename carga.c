#include "carga.h"
#include <stdio.h>

///FUNCIONES PARA CARGAR UN ARREGLO DE ALBUMES Y UN ALBUM SOLO
Album crearAlbum (Artista A) ///(TOMA COMO PARAMETRO EL ARTISTA AL QUE SE LE CARGA EL ALBUM, ASI AUTOCOMPLETA EL NOMBRE)
{
    Album B;

    printf("\n-Introduce el nombre del album: ");
    fflush(stdin);
    gets(B.nombre);

    strcpy(B.artista, A.nombre); ///EL NOMBRE DEL ARTISTA SE COMPLETA AUTOMATICAMENTE

    printf("\n-Introduce el anio: ");
    scanf("%d", &B.anio);

    do {
        printf("\n-Introduce el precio (Max.$45000): ");
        scanf("%d", &B.precio);
    } while (B.precio < 0 || B.precio > 45000); ///EL PRECIO NO PUEDE SER MENOR A 0 O MAYOR A 45000

    B.ventas = 0; ///SE INICIALIZA EN 0, LUEGO INCREMENTARA DE ACUERDO A LAS VENTAS

    B.estado = 1; ///EL ESTADO POR DEFECTO SERA UNO, LUEGO SE PODRA DAR DE BAJA

    return B;
}

///FUNCIONES PARA CARGAR UN ARRAY DE ARTISTAS Y UN SOLO ARTISTA
Artista crearArtista()
{
    Artista A;

    printf("\n-Introducir nombre del artista: ");
    fflush(stdin);
    gets(A.nombre);

    printf("\n-Introducir genero musical del artista: ");
    fflush(stdin);
    gets(A.genero);

    A.cantAlbumes = 0; ///LA CANT DE ALBUMES SE INICIALIZA EN CERO

    A.estado = 1; ///SE INICIALIZA EN 0

    return A;
}

///CARGO EL ARCHIVO DE ARTISTAS
void cargarArtistaConAlbum (char archivoArtista[], char archivoAlbum[]) {
    char continuar = 's';
    Artista A;

    FILE *archivo = fopen(archivoArtista, "ab");

    if (archivo != NULL) {
        while (continuar == 's' || continuar == 'S') {
            A = crearArtista();
            agregarAlbumAlArtista(archivoAlbum, &A); ///LLAMO A LA FUNCION PARA CARGAR ALBUMES EN EL ARCHIVO

            mostrarArtista(A);

            fwrite(&A, sizeof(Artista), 1, archivo);

            printf("\nDesea agregar otro artista? ");
            fflush(stdin);
            scanf(" %c", &continuar);
            system("cls");
        }
        fclose(archivo);
    }
}


///CARGAR ALBUMES EN EL ARCHIVO
void agregarAlbumAlArtista (char archivoAlbumes[], Artista *A) {
    FILE *archivo = fopen(archivoAlbumes, "ab");
    char continuar = 's';
    Album B;

    if (archivo != NULL) {
        while (continuar == 's' || continuar == 'S') {
            B = crearAlbum(*A);
            A->cantAlbumes++;
            mostrarAlbum(B);

            fwrite(&B, sizeof(Album), 1, archivo);
            printf("\nDesea agregar otro album? ");
            fflush(stdin);
            scanf(" %c", &continuar);
            system("cls");
        }
        fclose(archivo);
    }
}

///FUNCION PARA AÑADIR UN ALBUM A UN ARTISTA SELECCIONADO
void agregarAlbumToArtistaSeleccionado (char archivoArtistas[], char archivoAlbum[], int datoPosicion) {
    char continuar = 's';
    Album B;
    Artista A;

    FILE *archivo = fopen(archivoArtistas, "r+b");

    if (archivo != NULL) {
        while (continuar == 's' || continuar == 'S') {

            fseek(archivo, sizeof(Artista) * (datoPosicion-1), SEEK_SET); ///ME SITUO EN EL ARTISTA SELECCIONADO
            fread(&A, sizeof(Artista), 1, archivo);
            mostrarArtista(A);///MUESTRO LOS DATOS DEL ARTISTA
            printf("\n");

            B = crearAlbum(A); ///CARGO EL ALBUM
            A.cantAlbumes++;  ///AUMENTO LA CANTIDAD DE ALBUMES DEL ARTISTA

            fseek(archivo, sizeof(Artista) * (-1), SEEK_CUR); ///RESITUO EL CURSOR Y ESCRIBO
            fwrite(&A, sizeof(Artista), 1, archivo);

            agregarAlbumToArchivo(archivoAlbum, B);///TAMBIEN GUARDO EL ALBUM EN EL ARCHIVO DE ALBUMES

            printf("\nALBUM AGREGADO AL ARTISTA");

            printf("\n-Desea agregar otro album? ");
            fflush(stdin);
            scanf(" %c", &continuar);
        }
        fclose(archivo);
    }
    else {
        printf("\nNO PUDO ABRIRSE EL ARCHIVO");
    }
}

void agregarAlbumToArchivo (char archivoAlbum[], Album B) {
    FILE *archivo = fopen(archivoAlbum, "ab");

    if (archivo != NULL) {
        fwrite(&B, sizeof(Album), 1, archivo);
        fclose(archivo);
    }
}

///PERSISTENCIA EN ARCHIVOS
//CARGAR UN SOLO ARTISTA EN UN ARCHIVO
void cargarArtistaEnArchivo (Artista A, char nombreArchivo[]) ///CARGO UN ARTISTA EN EL ARCHIVO
{
    FILE *archivo = fopen(nombreArchivo, "ab");

    if (archivo != NULL)
    {
        fwrite(&A, sizeof(Artista), 1, archivo);
        fclose(archivo);
    }
}

//CARGO UN SOLO ALBUM EN EL ARCHIVO
void cargarAlbumEnArchivo (Album B, char nombreArchivo[]) ///CARGO UN ALBUM EN EL ARCHIVO
{
    FILE *archivo = fopen(nombreArchivo, "ab");

    if (archivo != NULL)
    {
        fwrite(&B, sizeof(Album), 1, archivo);
        fclose(archivo);
    }
}

///FUNCION PARA PASAR UN ARRAY DE ARTISTAS A UN ARCHIVO
void cargarArrayAlbumEnArchivo (Album B[], char nombreArchivo[], int validosB)
{
    FILE *archivo = fopen(nombreArchivo, "ab");
    int i = 0;

    if (archivo != NULL)
    {
        while (i < validosB) {
            fwrite(&B[i], sizeof(Album), 1, archivo);
            i++;
        }
        fclose(archivo);
    }
}
///FUNCION PARA PASAR UN ARRAY DE ARTISTAS A UN ARCHIVO
void cargarArrayArtistaEnArchivo (Artista A[], char nombreArchivo[], int validosA)
{
    FILE *archivo = fopen(nombreArchivo, "ab");
    int i = 0;

    if (archivo != NULL)
    {
        while (i < validosA) {
            fwrite(&A[i], sizeof(Artista), 1, archivo);
            i++;
        }
        fclose(archivo);
    }
}

///PASAR ARCHIVO DE ARTISTAS A UN ARREGLO
int pasarArchivoToArrayArtista (char archivoNombre[], Artista A[]) {
    FILE *archivo = fopen(archivoNombre, "rb");
    Artista Aux;
    int i = 0;

    if (archivo != NULL) {
            rewind(archivo);
        while (fread(&Aux, sizeof(Artista), 1, archivo)>0) {
            A[i] = Aux;
            i++;
        }
    fclose(archivo);
    }
    return i;
}

///PASAR ARCHIVO DE ARTISTAS A UN ARREGLO DINAMICO
int pasarArchivoToArrayArtistaDinamico (char archivoNombre[], Artista **arregloArtistaDinamico) {
    int dimension = registrosArtistas(archivoNombre);
    *arregloArtistaDinamico = (Artista*)malloc(dimension * sizeof(Artista));
    Artista Aux;
    int i = 0;

    FILE *archivo = fopen(archivoNombre, "rb");

    if (archivo != NULL) {
        while (fread(&Aux, sizeof(Artista), 1, archivo)>0) {
            (*arregloArtistaDinamico)[i] = Aux;
            i++;
        }
        fclose(archivo);
    }
    return i;
}

///PASAR ARCHIVO DE ALBUMES A UN ARREGLO
int pasarArchivoToArrayAlbum (char archivoNombre[], Album B[]) {
    FILE *archivo = fopen(archivoNombre, "rb");
    Album Aux;
    int i = 0;

    if (archivo != NULL) {
        while (fread(&Aux, sizeof(Album), 1, archivo)>0) {
            B[i] = Aux;
            i++;
        }
        fclose(archivo);
    }
    return i;
}
///PASAR ARCHIVO DE ALBUMES A UN ARREGLO DINAMICO
int pasarArchivoToArrayAlbumDinamico (char archivoNombre[], Album **arregloAlbumDinamico) {
    int dimension = registrosAlbumes(archivoNombre);
    *arregloAlbumDinamico = (Album*)malloc(dimension * sizeof(Album));
    Album Aux;
    int i = 0;

    FILE *archivo = fopen(archivoNombre, "rb");

    if (archivo != NULL) {
        while (fread(&Aux, sizeof(Album), 1, archivo)>0) {
            (*arregloAlbumDinamico)[i] = Aux;
            i++;
        }
        fclose(archivo);
    }
    return i;
}

///FUNCIONES PARA CARGAR ARREGLOS DE PALABRAS (PARA LOS ORDENAMIENTOS)
//CARGO MATRIZ CON LOS NOMBRES DE LOS ARTISTAS
void cargarArregloPalabrasArtista (int dimC, char matriz[][dimC], Artista A[], int validosA) {
    int f = 0;

    while ((f < validosA)) {
        strcpy(matriz[f], A[f].nombre);
        f++;
    }
}
//CARGO MATRIZ CON LOS NOMBRES DE LOS ALBUMES
void cargarArregloPalabrasAlbum (int dimC, char matriz[][dimC], Album B[], int validosB) {
    int f = 0;

    while ((f < validosB)) {
        strcpy(matriz[f], B[f].nombre);
        f++;
    }
}

///INICIALIZAR CAJA EN 0
Caja crearCaja (Caja C) {
    C.gananciaTotal = 0;
    C.cantVentas = 0;
    return C;
}
