#include "ordenamiento.h"

///FUNCIONES DE ORDENAMIENTO
///ORDENAMIENTOS POR INSERCION
//PARA LAS VENTAS DEL ALBUM
void insercionVentas (Album B[], int validosB) {
    int i = 0;

    while (i < validosB-1) {
        insertarVenta (B, i, B[i+1]);
        i++;
    }
}

void insertarVenta (Album B[], int pos, Album dato) {
    int i = pos;

    while (i >= 0 && dato.ventas < B[i].ventas) {
        B[i+1] = B[i];
        i--;
    }
    B[i+1] = dato;
}
//PARA EL AÑO DEL ALBUM
void insercionAnio (Album B[], int validosB) {
    int i = 0;

    while (i < validosB-1) {
        insertarAnio (B, i, B[i+1]);
        i++;
    }
}

void insertarAnio (Album B[], int pos, Album dato) {
    int i = pos;

    while (i >= 0 && dato.anio < B[i].anio) {
        B[i+1] = B[i];
        i--;
    }
    B[i+1] = dato;
}
//PARA LA CANTIDAD DE ALBUMES DE UN ARTISTA
void insercionCantidad (Artista A[], int validosA) {
    int i = 0;

    while (i < validosA-1) {
        insertarCantidad (A, i, A[i+1]);
        i++;
    }
}

void insertarCantidad (Artista A[], int pos, Artista dato) {
    int i = pos;

    while (i >= 0 && dato.cantAlbumes < A[i].cantAlbumes) {
        A[i+1] = A[i];
        i--;
    }
    A[i+1] = dato;
}
///ORDENAMIENTOS POR SELECCION
//PARA EL NOMBRE DEL ARTISTA O EL ALBUM
void seleccionNombre(int dimC, char matriz[][dimC], int cantidadPalabras) {
    int i = 0;
    int posMenor = 0;
    char aux[dimC];

    while (i < cantidadPalabras-1) {
        posMenor = hallarPosMenor (dimC, matriz, i, cantidadPalabras);
        strcpy(aux, matriz[posMenor]);
        strcpy(matriz[posMenor], matriz[i]);
        strcpy(matriz[i], aux);
        i++;
    }
}

int hallarPosMenor (int dimC, char matriz[][dimC], int pos, int cantidadPalabras) {
    char menor[dimC];
    strcpy(menor, matriz[pos]);
    int posMenor = pos;
    int i = pos + 1;


    while (i < cantidadPalabras) {
        if (strcmpi(menor, matriz[i]) > 0) {
            strcpy(menor, matriz[i]);
            posMenor = i;
        }
        i++;
    }
    return posMenor;
}
