#include "venta.h"
#include <stdio.h>


///FUNCIONES PARA LAS VENTAS
//FUNCION QUE APILA LAS VENTAS EN UNA PILA
void apilarAlbumVendido (Pila *VENTAS, char nombreArchivo[], int posicion) {
    FILE *archivo = fopen(nombreArchivo, "r+b");
    Album B;

    if ((archivo != NULL) && (posicion >= 0)) {
        fseek(archivo, sizeof(Album) * (posicion-1), SEEK_SET); ///ME SITUO EN EL ALBUM ELEGIDO Y LO LEO
        fread(&B, sizeof(Album), 1, archivo);

        if (B.estado == 1) { ///SI ESTA DISPONIBLE APILO SU PRECIO EN VENTAS Y AUMENTO SUS VENTAS
            apilar(VENTAS, B.precio);
            B.ventas += 1;
            printf("\nSE VENDIO EL ALBUM: '%s'", B.nombre);

            fseek(archivo, sizeof(Album) * (-1), SEEK_CUR);
            fwrite(&B, sizeof(Album), 1, archivo); ///LO ESCRIBO
        }
        else {
            printf("\nEL ALBUM ESTA AGOTADO");
        }
        rewind(archivo); ///SITUO EL CURSOR AL COMIENZO DE NUEVO
        fclose(archivo);
    }
}

///FUNCION QUE LLAMA A LA AUX DE VENTAS
void devengarVentas (char archivoCaja[], Pila *VENTAS, Pila *DEVENGADO) {
    FILE *archivo = fopen(archivoCaja, "r+b"); ///LO ABRO EN WB POR QUE EL ARCHIVO NO EXISTE

    if (archivo != NULL) {
        devengarVentasAux(archivoCaja, VENTAS, DEVENGADO);
        fclose(archivo);
    }
    else {
        archivo = fopen(archivoCaja, "wb");
        if (archivo != NULL) {
            Caja C = {0};
            fwrite(&C, sizeof(Caja), 1, archivo);
            fclose(archivo);
            devengarVentasAux(archivoCaja, VENTAS, DEVENGADO);
        }
    }
}

void devengarVentasAux(char archivoCaja[], Pila *VENTAS, Pila *DEVENGADO) {
    FILE *archivo = fopen(archivoCaja, "r+b"); ///EN LA AUX LO ABRO EN R+B, PARA LEER Y ESCRIBIR SOBRE LA CAJA

    if (archivo != NULL) {
        Caja C; ///LA INICIALIZO EN 0

        fseek(archivo, 0, SEEK_SET); ///ME UBICO AL COMIENZO Y LA LEO
        fread(&C, sizeof(Caja), 1, archivo);

        while (!pilavacia(VENTAS)) { ///CARGO TODOS LOS VALORES DE LAS VENTAS
            C.gananciaTotal += tope(VENTAS);
            apilar(DEVENGADO, desapilar(VENTAS));
            C.cantVentas++;

            fseek(archivo, 0, SEEK_SET); ///Y ESCRIBO
            fwrite(&C, sizeof(Caja), 1, archivo);
        }
        fclose(archivo);
    }
}

