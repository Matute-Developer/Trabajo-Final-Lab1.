#include "modificaciones.h"
#include "pila.h"
#include <stdio.h>
#include <string.h>

///FUNCIONES PARA MODIFICAR REGISTROS DE UN ARCHIVO
//MODIFICAR ARTISTA
void modificarArtistaAeleccion (char nombreArchivo[], char archivoAlbumes[], int posicion) {
    FILE *archivo = fopen(nombreArchivo, "r+b");
    int registros = registrosArtistas(nombreArchivo);


    if ((archivo != NULL) && (posicion > 0 && posicion <= registros)) {
        Artista A;

        fseek(archivo, sizeof(Artista) * (posicion - 1), SEEK_SET);
        fread(&A, sizeof(Artista), 1, archivo);

        system("cls");

        A = modificarDatosArtista(A, archivoAlbumes); ///LLAMO A LA AUXILIAR

        fseek(archivo, sizeof(Artista) * (-1), SEEK_CUR);
        fwrite(&A, sizeof(Artista), 1, archivo);

        fclose(archivo);
    }
}

Artista modificarDatosArtista (Artista A, char archivoAlbumes[]) {
    printf("\nDatos actuales del Artista: ");
    mostrarArtista(A);

    int control = 0;
    char continuar = 's';
    char datoNombre[50];


    do {
        printf("\n\nQUE CAMPO DESEA MODIFICAR?\n\n1-MODIFICAR NOMBRE\n2-MODIFICAR GENERO\n3-MODIFICAR CANTIDAD DE ALBUMES\n0-SALIR DEL MENU\n");
        scanf("%d", &control);
        switch (control) {
            case 1:
                strcpy(datoNombre, A.nombre);
                printf("\nIngrese NUEVO nombre: ");
                fflush(stdin);
                gets(A.nombre);
                guardarNombreEnAlbumes(archivoAlbumes, datoNombre, A.nombre); //TAMBIEN MODIFICO SU NOMBRE EN LOS ALBUMES
                break;

            case 2:
                printf("\nIngrese NUEVO genero: ");
                fflush(stdin);
                gets(A.genero);
                break;

            case 3:
                printf("\nIngrese NUEVA cantidad de albumes: ");
                scanf("%d", &A.cantAlbumes);
                break;

            default:
                printf("\nINTRODUCE UNA OPCION VALIDA");
                break;

            if (control != 0) {
                printf("\nDESEA MODIFICAR OTRO CAMPO? (s/n): ");
                fflush(stdin);
                scanf(" %c", &continuar);
                system("cls");
            }
        }
    } while ((continuar == 's' || continuar == 's') && (control != 0 && control <= 5));

    printf("\n\nDATOS MODIFICADOS DEL ARTISTA: ");
    mostrarArtista(A);

    return A;
}

///MODIFICAR EL ARTISTA DEL ALBUM
//(SI MODIFICO EL NOMBRE DE UN ARTISTA, EL CAMPO 'ARTISTA' DE SUS ALBUMES TAMBIEN SE MODIFICA)
void guardarNombreEnAlbumes(char archivoAlbumes[], char nombreAntiguo[], char nombreModificado[]) {
    FILE *archivo = fopen(archivoAlbumes, "r+b");
    Album B;

    if (archivo != NULL) {
        while (fread(&B, sizeof(Album), 1, archivo)>0) {
            if (strcmpi(nombreAntiguo, B.artista)==0) {
                strcpy(B.artista, nombreModificado);
                fseek(archivo, (-1)*sizeof(Album), SEEK_CUR);
                fwrite(&B, sizeof(Album), 1, archivo);
                fseek(archivo, 0, SEEK_CUR);
            }
        }
        fclose(archivo);
    }
}

//MODIFICAR ALBUM
void modificarAlbumAeleccion (char nombreArchivo[], int posicion) {
    FILE *archivo = fopen(nombreArchivo, "r+b");
    int registros = registrosAlbumes(nombreArchivo);

    if ((archivo != NULL) && (posicion > 0 && posicion <= registros)) {
        Album B;

        fseek(archivo, sizeof(Album) * (posicion - 1), SEEK_SET);
        fread(&B, sizeof(Album), 1, archivo);

        system("cls");

        B = modificarDatosAlbum(B); ///LLAMO A LA FUNCION AUXILIAR

        fseek(archivo, sizeof(Album) * (-1), SEEK_CUR);

        fwrite(&B, sizeof(Album), 1, archivo);

        rewind(archivo);
        fclose(archivo);
    }
}

Album modificarDatosAlbum (Album B) {
    printf("\nDatos actuales del album: ");
    mostrarAlbum(B);

    int control = 0;
    char continuar = 's';

    do {
        printf("\n\nQUE CAMPO DESEA MODIFICAR?\n\n1-MODIFICAR NOMBRE\n2-MODIFICAR ARTISTA\n3-MODIFICAR ANIO\n4-MODIFICAR PRECIO\n5-MODIFICAR ESTADO\n0-SALIR DEL MENU\n");
        scanf("%d", &control);
        switch (control) {
            case 1:
                printf("\nIngrese NUEVO nombre: ");
                fflush(stdin);
                gets(B.nombre);
                break;

            case 2:
                printf("\nIngrese NUEVO artista: ");
                fflush(stdin);
                gets(B.artista);
                break;

            case 3:
                printf("\nIngrese NUEVO anio: ");
                scanf("%d", &B.anio);
                break;

            case 4:
                printf("\nIngrese NUEVO precio: ");
                scanf("%d", &B.precio);
                break;

            case 5:
                do {
                    printf("\n-Introduce el precio (Max.$45000): ");
                    scanf("%d", &B.precio);
                } while (B.precio < 0 || B.precio > 45000); //Al modificarlo tambien hay un limite en el precio
                break;

            default:
                printf("\nINTRODUCE UNA OPCION VALIDA");
                break;

            if (control != 0) {
                printf("\nDESEA MODIFICAR OTRO CAMPO? (s/n): ");
                fflush(stdin);
                scanf(" %c", &continuar);
                system("cls");
            }
        }
    } while ((continuar == 's') && (control != 0 && control <= 5));

    printf("\n\nDATOS MODIFICADOS DEL ALBUM: ");
    mostrarAlbum(B);

    return B;
}

///FUNCIONES PARA LA BAJA/ALTA DE ARTISTAS Y ALBUMES
void darDeBajaAlbum (char nombreArchivo[], int posicion)
{
    FILE *archivo = fopen(nombreArchivo, "r+b");
    posicion = posicion;
    if ((archivo != NULL) && (posicion >= 0)) {
        Album B;
        fseek(archivo, sizeof(Album) * (posicion-1), SEEK_SET); ///ME POSICIONO EN EL ALBUM SELECCIONADO
        fread(&B, sizeof(Album), 1, archivo); ///LO LEO

        B.estado = 0; ///SU ESTADO PASA A 0
        fseek(archivo, sizeof(Album) * (-1), SEEK_CUR); ///ME REPOSICIONO
        fwrite(&B, sizeof(Album), 1, archivo); ///Y LO ESCRIBO

        printf("\nEl album se dio de baja"); ///POR ULTIMO PRINTEO UN MENSAJE Y MUESTRO EL ARCHIVO
        mostrarAlbum(B);

        fclose(archivo);
    }
    else {
        printf("\nEl album no se encuentra en el sistema");
        fclose(archivo);
    }

}

void darDeAltaAlbum (char nombreArchivo[], int posicion)
{
    FILE *archivo = fopen(nombreArchivo, "r+b");
    posicion = posicion;
    if ((archivo != NULL) && (posicion >= 0)) {
        Album B;
        fseek(archivo, sizeof(Album) * (posicion-1), SEEK_SET); ///ME POSICIONO EN EL ALBUM SELECCIONADO
        fread(&B, sizeof(Album), 1, archivo); ///LO LEO

        B.estado = 1; ///SU ESTADO PASA A 0
        fseek(archivo, sizeof(Album) * (-1), SEEK_CUR); ///ME REPOSICIONO
        fwrite(&B, sizeof(Album), 1, archivo); ///Y LO ESCRIBO

        printf("\nEl album se dio de alta"); ///POR ULTIMO PRINTEO UN MENSAJE Y MUESTRO EL ARCHIVO
        mostrarAlbum(B);

        fclose(archivo);
    }
    else {
        printf("\nEl album no se encuentra en el sistema");
        fclose(archivo);
    }

}

void darDeBajaArtista (char nombreArchivo[], char archivoAlbumes[], int posicion)
{
    FILE *archivo = fopen(nombreArchivo, "r+b");

    if ((archivo != NULL) && (posicion >= 0)) {
        Artista A;
        fseek(archivo, sizeof(Artista) * (posicion-1), SEEK_SET); ///ME POSICIONO EN EL ALBUM SELECCIONADO
        fread(&A, sizeof(Artista), 1, archivo); ///LO LEO

        A.estado = 0; ///SU ESTADO PASA A 0
        darDeBajaDiscografia(archivoAlbumes, A.nombre); ///EL ESTADO DE SUS ALBUMES TAMBIEN PASA A 0


        fseek(archivo, sizeof(Artista) * (-1), SEEK_CUR); ///ME REPOSICIONO
        fwrite(&A, sizeof(Artista), 1, archivo); ///Y LO ESCRIBO

        printf("\n\nEL ARTISTA SE DIO DE BAJA\n"); ///POR ULTIMO PRINTEO UN MENSAJE Y MUESTRO EL ARCHIVO
        mostrarArtista(A);

        rewind(archivo);
        fclose(archivo);
    }
    else {
        printf("\nEl artista no se encuentra en el sistema");
        fclose(archivo);
    }
}

void darDeAltaArtista (char nombreArchivo[], char archivoAlbumes[], int posicion)
{
    FILE *archivo = fopen(nombreArchivo, "r+b");

    if ((archivo != NULL) && (posicion >= 0)) {
        Artista A;
        fseek(archivo, sizeof(Artista) * (posicion-1), SEEK_SET); ///ME POSICIONO EN EL ALBUM SELECCIONADO
        fread(&A, sizeof(Artista), 1, archivo); ///LO LEO

        A.estado = 1; ///SU ESTADO PASA A 0
        darDeAltaDiscografia(archivoAlbumes, A.nombre); ///SUS ALBUMES TAMBIEN SE DAN DE ALTA

        fseek(archivo, sizeof(Artista) * (-1), SEEK_CUR); ///ME REPOSICIONO
        fwrite(&A, sizeof(Artista), 1, archivo); ///Y LO ESCRIBO

        printf("\nEL ARTISTA SE DIO DE ALTA\n"); ///POR ULTIMO PRINTEO UN MENSAJE Y MUESTRO EL ARCHIVO
        mostrarArtista(A);

        rewind(archivo);
        fclose(archivo);
    }
    else {
        printf("\nEl artista no se encuentra en el sistema");
        fclose(archivo);
    }
}

void darDeBajaDiscografia (char archivoAlbumes[], char nombreArtista[]) {
    FILE *archivo = fopen(archivoAlbumes, "r+b");

    if (archivo != NULL) {
        Album B;
        while (fread(&B, sizeof(Album), 1, archivo)>0) {
            if (strcmpi(nombreArtista, B.artista)==0) {
                B.estado = 0; ///SI EL ARTISTA COINCIDE DOY DE BAJA EL ALBUM
                printf("\nSe dio de baja el album: %s", B.nombre);
                fseek(archivo, sizeof(Album) * (-1), SEEK_CUR);
                fwrite(&B, sizeof(Album), 1, archivo);
                fseek(archivo, 0, SEEK_CUR);
            }
        }
        rewind(archivo);
        fclose(archivo);
    }
}

void darDeAltaDiscografia (char archivoAlbumes[], char nombreArtista[]) {
    FILE *archivo = fopen(archivoAlbumes, "r+b");

    if (archivo != NULL) {
        Album B;
        while (fread(&B, sizeof(Album), 1, archivo)>0) {
            if (strcmpi(nombreArtista, B.artista)==0) {
                B.estado = 1; ///SI EL ARTISTA COINCIDE DOY DE ALTA EL ALBUM
                printf("\nSe dio de alta el album: %s", B.nombre);
                fseek(archivo, sizeof(Album) * (-1), SEEK_CUR);
                fwrite(&B, sizeof(Album), 1, archivo);
                fseek(archivo, 0, SEEK_CUR);
            }
        }
        rewind(archivo);
        fclose(archivo);
    }
}

///RETORNAR CANTIDAD DE REGISTROS
int registrosAlbumes (char nombreArchivo[]) {
    FILE *archivo = fopen(nombreArchivo, "rb");
    Album B;
    int cantidad;

    if (archivo != NULL) {
        fseek(archivo, 0, SEEK_END);
        cantidad = ftell(archivo) / sizeof(Album);
        rewind(archivo);
        fclose(archivo);
    }
    return cantidad;
}

int registrosArtistas (char nombreArchivo[]) {
    FILE *archivo = fopen(nombreArchivo, "rb");
    Artista A;
    int cantidad;

    if (archivo != NULL) {
        fseek(archivo, 0, SEEK_END);
        cantidad = ftell(archivo) / sizeof(Artista);
        rewind(archivo);
        fclose(archivo);
    }
    return cantidad;
}
