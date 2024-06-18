#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pila.h"
#include "windows.h"
#include <mmsystem.h>


///ESTRUCTURAS
typedef struct
{
    char nombre[50];
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
    int estado;
} Artista;

typedef struct
{
    int gananciaTotal; //LA SUMA DE LAS VENTAS
    int cantVentas; //(la cantidad de albumes que se vendieron)
} Caja;

///FUNCIONES DE MUSICA
void playlist ();
void playAudio(const char* filename);
void stopAudio();

/* DETALLES DEL CODIGO
-TODO LO RELACIONADO A LA STRUCT ARTISTA LLEVARA UNA 'A' (arrayA[], validosA)
-TODO LO RELACIONADO A LA STRUCT ALBUM LLEVARA UNA 'B' (arrayB[], validosB)
-POR ULTIMO, LO RELACIONADO A LA STRUCT CAJA SERA 'C' O DIRECTAMENTE CAJA
*/

///FUNCION DE MUSICA
void playAudio(const char* filename);

int main()
{
    ///VARIABLES
    int control = 0;
    int opciones = 0;
    int dato = 0;
    int validosArt = 0;
    int validosAlbumes = 0;
    Album albumes[70];
    Artista artistas[50];
    char archivoArtistas[30] = "archivoArtistas";
    char archivoAlbumes[30] = "archivoAlbumes";
    char archivoCaja[30] = "archivoCaja";
    Pila VENTAS; inicpila(&VENTAS);
    Pila DEVENGADO; inicpila(&DEVENGADO);
    int password= 12345;
    int id=0;
    char opcion = 's'; ///DOS VARIABLES PORQUE EN ALGUNOS CASE PRECISO MAS DE UNA OPCION
    char opcion2 = 's';
    char datoBusqueda[30];
    char nombresArtistas[50][50];
    char nombresAlbumes[50][70];
    Album ordenamientoAlbum[20];
    Album *dinamicoAlbum;
    Artista ordenamientoArtista[20];
    Artista *dinamicoArtista;

    do
    {
        printf("Ingrese La Contrasenia: ");
        scanf("%d",&id);
        system("cls");
        while (id == password)
        {
            control = menuMain();
            switch(control)
            {

            case 1:
                printf("\nRECUERDA:\n-SI CARGA UN ARTISTA DEBERA CARGARLE AL MENOS UN ALBUM\n\n");
                cargarArtistaConAlbum(archivoArtistas, archivoAlbumes); ///EL USUARIO CARGA UN ARTISTA Y SUS RESPECTIVOS ALBUMES
                system("cls");
                mostrarArchivoAlbum(archivoAlbumes);
                system("pause");
                system("cls");
                mostrarArchivoArtista(archivoArtistas);
                break;

            case 2:
                do {
                    printf("\n-BUSCAR ARTISTA POR NOMBRE (1) \n-BUSCAR ARTISTA POR LISTA (2) \n");
                    scanf("%d", &opciones);
                    if (opciones == 1) {
                        dato = buscarArtistaNombreArchivo(archivoArtistas);
                        if (dato >= 0) {
                            agregarAlbumToArtistaSeleccionado(archivoArtistas, archivoAlbumes, dato);
                            mostrarArchivoArtista(archivoArtistas);
                            printf("\n\n");
                            system("pause");
                            system("cls");
                            mostrarArchivoAlbum(archivoAlbumes);
                        }
                        else {
                            printf("\nVUELVE A BUSCAR EL ARTISTA");
                        }

                    }
                    else if (opciones == 2) {
                        dato = seleccionarArtistaArchivo(archivoArtistas);
                        if (dato >= 0) {
                            system("cls");
                            agregarAlbumToArtistaSeleccionado(archivoArtistas, archivoAlbumes, dato);
                            mostrarArchivoArtista(archivoArtistas);
                            system("pause");
                            system("cls");
                            mostrarArchivoAlbum(archivoAlbumes);
                        }
                        else {
                            printf("\n\nVUELVE A BUSCAR EL ARTISTA");
                        }
                    }
                    printf("\n");
                    system("pause");
                    system("cls");
                    printf("\nQUIERE AGREGAR OTRO ALBUM?");
                    fflush(stdin);
                    scanf(" %c", &opcion);
                } while (opcion == 's' || opcion == 's');
                opcion = 's';
                break;

            case 3:
                do {
                    dato = menuConsultas();

                    if (dato == 1) {
                        printf("\nARTISTAS DEL SISTEMA\n\n");
                        mostrarArchivoArtista(archivoArtistas);
                        printf("\n\n");
                    }
                    if (dato == 2) {
                        printf("\nALBUMES DEL SISTEMA\n\n");
                        mostrarArchivoAlbum(archivoAlbumes);
                        printf("\n\n");
                    }
                    if (dato == 3) {
                        mostrarArchivoCaja(archivoCaja);
                    }
                    if (dato == 4) {
                        printf("\nARTISTAS ACTIVOS\n\n");
                        mostrarArtistaActivos(archivoArtistas);
                        printf("\n\n");
                    }
                    if (dato == 5) {
                        printf("\nALBUMES DISPONIBLES\n\n");
                        mostrarSoloDisponibles(archivoAlbumes);
                        printf("\n\n");
                    }
                    if (dato == 6) {
                        printf("\nARTISTAS INACTIVOS\n\n");
                        mostrarArtistaInactivos(archivoArtistas);
                        printf("\n\n");
                    }
                    if (dato == 7) {
                        printf("\nALBUMES AGOTADOS\n\n");
                        mostrarSoloAgotados(archivoAlbumes);
                        printf("\n\n");
                    }
                    if (dato == 8) {
                        printf("\n-INTRODUCE EL NOMBRE DEL ARTISTA: ");
                        fflush(stdin);
                        gets(datoBusqueda);
                        mostrarDiscografiaArtistaSeleccionado(archivoAlbumes, datoBusqueda);
                        printf("\n\n");
                    }
                    if (dato == 9) {
                        printf("\n-INTRODUCE EL NOMBRE DEL GENERO BUSCADO: ");
                        fflush(stdin);
                        gets(datoBusqueda);
                        mostrarArtistaPorGenero(archivoArtistas, datoBusqueda);
                        printf("\n\n");
                    }
                    printf("\n");
                    system("pause");
                    system("cls");
                    printf("\nDESEA CONSULTAR ALGO MAS? ");
                    fflush(stdin);
                    scanf(" %c", &opcion);
                } while ((opcion == 's' || opcion == 's') && (dato != 0));
                opcion = 's'; //RESTAURO EL VALOR DE OPCION
                break;

            case 4:
                while (opcion == 's' || opcion == 's') {
                    printf("\nDESEA BUSCAR...\n-POR LISTA (1)\n-POR NOMBRE(2)\n");
                    scanf("%d", &opciones);
                    if (opciones == 1) {
                        dato = seleccionarAlbumArchivo(archivoAlbumes);
                        apilarAlbumVendido(&VENTAS, archivoAlbumes, dato);
                    }
                    if (opciones == 2) {
                        dato = buscarAlbumNombreArchivo(archivoAlbumes);
                        apilarAlbumVendido(&VENTAS, archivoAlbumes, dato);
                    }
                    printf("\nDESEA AGREGAR OTRA VENTA?");
                    fflush(stdin);
                    scanf(" %c", &opcion);
                    system("cls");
                }
                printf("\n(SUS GANANCIAS SE SUMARAN EN LA CAJA)\n ");
                system("pause");
                system("cls");
                devengarVentas(archivoCaja, &VENTAS, &DEVENGADO);
                mostrarArchivoCaja(archivoCaja);
                opcion = 's'; //REESTABLEZCO EL VALOR DE OPCION PARA QUE SEA POSIBLE VOLVER A INGREGAR
                break;

            case 5:
                while (opcion == 's' || opcion == 's') {
                    printf("\nDAR DE BAJA UN ALBUM (1) \nDAR DE ALTA UN ALBUM (2) \n");
                    scanf("%d", &opciones);
                    system("cls");
                    if (opciones == 1) { ///DAR DE BAJA UN ALBUM
                        printf("\nDesea...\n-BUSCAR ALBUM POR NOMBRE (1)\n-BUSCAR ALBUM POR LISTA (2) \n");
                        scanf("%d", &opciones);
                        if (opciones == 1)
                        {///BUSCO POR NOMBRE
                            dato = buscarAlbumNombreArchivo(archivoAlbumes);
                            darDeBajaAlbum(archivoAlbumes, dato);
                        }///BUSCO POR LISTA
                        else if (opciones == 2)
                        {
                            dato = seleccionarAlbumArchivo(archivoAlbumes);
                            darDeBajaAlbum(archivoAlbumes, dato);
                        }

                    }
                    else if (opciones == 2) { ///DAR DE ALTA UN ALBUM
                        printf("\nDesea...\n-BUSCAR ALBUM POR NOMBRE (1)\n-BUSCAR ALBUM POR LISTA (2) \n");
                        scanf("%d", &opciones);
                        if (opciones == 1)
                        {
                            dato = buscarAlbumNombreArchivo(archivoAlbumes);
                            darDeAltaAlbum(archivoAlbumes, dato);
                        }
                        else if (opciones == 2)
                        {
                            dato = seleccionarAlbumArchivo(archivoAlbumes);
                            darDeAltaAlbum(archivoAlbumes, dato);
                        }
                    }
                    printf("\nDESEA DAR DE BAJA/ALTA OTRO ALBUM? ");
                    fflush(stdin);
                    scanf(" %c", &opcion);
                    system("cls");
                }
                opcion = 's'; ///RESTAURO EL VALOR POR SI EL USUARIO QUIERE VOLVER A INGRESAR
                break;

            case 6:
                while (opcion == 's' || opcion == 's') {
                    printf("\nDAR DE BAJA UN ARTISTA (1) \nDAR DE ALTA UN ARTISTA (2) \n");
                    scanf("%d", &opciones);
                    system("cls");
                    if (opciones == 1) { ///DAR DE BAJA UN ARTISTA
                        printf("\nDesea...\n-BUSCAR ARTISTA POR NOMBRE (1)\n-BUSCAR ARTISTA POR LISTA (2) \n");
                        scanf("%d", &opciones);
                        if (opciones == 1)
                        {///BUSCO POR NOMBRE
                            dato = buscarArtistaNombreArchivo(archivoArtistas);
                            darDeBajaArtista(archivoArtistas, archivoAlbumes, dato);
                        }///BUSCO POR LISTA
                        else if (opciones == 2)
                        {
                            dato = seleccionarArtistaArchivo(archivoArtistas);
                            system("cls");
                            darDeBajaArtista(archivoArtistas, archivoAlbumes, dato);
                        }

                    }
                    else if (opciones == 2) { ///DAR DE ALTA UN ARTISTA
                        printf("\nDesea...\n-BUSCAR ARTISTA POR NOMBRE (1)\n-BUSCAR ARTISTA POR LISTA (2) \n");
                        scanf("%d", &opciones);
                        if (opciones == 1)
                        {
                            dato = buscarArtistaNombreArchivo(archivoArtistas);
                            system("cls");
                            darDeAltaArtista(archivoArtistas, archivoAlbumes, dato);
                        }
                        else if (opciones == 2)
                        {
                            dato = seleccionarArtistaArchivo(archivoArtistas);
                            system("cls");
                            darDeAltaArtista(archivoArtistas, archivoAlbumes, dato);
                        }
                    }
                    printf("\nDESEA DAR DE BAJA/ALTA OTRO ARTISTA? ");
                    fflush(stdin);
                    scanf(" %c", &opcion);
                    system("cls");
                }
                opcion = 's'; ///RESTAURO EL VALOR POR SI EL USUARIO QUIERE VOLVER A INGRESAR
                break;

            case 7:
                while (opcion == 's' || opcion == 's') {
                    dato = buscarArtistaNombreArchivo(archivoArtistas);
                    if (dato >= 0) {
                        mostrarSoloArtistaArchivo(archivoArtistas, dato);
                    }
                    else {
                    printf("\nEl artista no se encuentra en el sistema... \nDesea cargarlo? ");
                    fflush(stdin);
                    scanf(" %c", &opcion2);

                        if (opcion2 == 's') {
                        cargarArtistaConAlbum(archivoArtistas, archivoAlbumes);
                        printf("\nARTISTA CARGADO");
                        mostrarArchivoArtista(archivoArtistas);
                        }
                    }
                    printf("\n-Quiere buscar otro artista? ");
                    fflush(stdin);
                    scanf(" %c", &opcion);
                }
                opcion = 's'; ///RESTAURO EL VALOR POR SI EL USUARIO QUIERE VOLVER A INGRESAR
                break;

            case 8:
                do {
                    dato = menuOrdenamientos();

                    if (dato == 1) {
                        validosAlbumes = pasarArchivoToArrayAlbumDinamico(archivoAlbumes, &dinamicoAlbum);
                        insercionVentas(dinamicoAlbum, validosAlbumes);
                        mostrarAlbumInvertido(dinamicoAlbum, validosAlbumes);
                    }

                    if (dato == 2) {
                        validosAlbumes = pasarArchivoToArrayAlbum(archivoAlbumes, ordenamientoAlbum);
                        insercionAnio(ordenamientoAlbum, validosAlbumes);
                        mostrarArrayAlbumes(ordenamientoAlbum, validosAlbumes);
                    }

                    if (dato == 3) {
                        validosArt = pasarArchivoToArrayArtistaDinamico(archivoArtistas, &dinamicoArtista);
                        insercionCantidad(dinamicoArtista, validosArt);
                        mostrarArtistaArray(dinamicoArtista, validosArt);
                    }

                    if (dato == 4) {
                        validosArt = pasarArchivoToArrayArtistaDinamico(archivoArtistas, &dinamicoArtista);
                        cargarArregloPalabrasArtista(50, nombresArtistas, dinamicoArtista, validosArt);
                        seleccionNombre(50, nombresArtistas, validosArt);
                        mostrarArregloPalabra(validosArt, 50, nombresArtistas);
                    }

                    if (dato == 5) {
                        validosAlbumes = pasarArchivoToArrayAlbumDinamico(archivoAlbumes, &dinamicoAlbum);
                        cargarArregloPalabrasAlbum(70, nombresAlbumes, dinamicoAlbum, validosAlbumes);
                        seleccionNombre(70, nombresAlbumes, validosAlbumes);
                        mostrarArregloPalabra(validosAlbumes, 70, nombresAlbumes);
                    }
                    printf("\n");
                    system("pause");
                } while (dato != 0);
                break;

            case 9:
                do {
                    printf("\nDESEA MODIFICAR...\n\n(1)-UN ARTISTA \n(2)-UN ALBUM\n");
                    scanf("%d", &opciones);
                    if (opciones == 1) {
                        dato = seleccionarArtistaArchivo(archivoArtistas);
                        modificarArtistaAeleccion(archivoArtistas, archivoAlbumes, dato);
                        printf("\n");
                        system("pause");
                        system("cls");
                        mostrarArchivoArtista(archivoArtistas);
                    }
                    if (opciones == 2) {
                        dato = seleccionarAlbumArchivo(archivoAlbumes);
                        modificarAlbumAeleccion(archivoAlbumes, dato);
                        printf("\n");
                        system("pause");
                        system("cls");
                        mostrarArchivoAlbum(archivoAlbumes);
                    }
                    printf("\n");
                    system("pause");
                    system("cls");
                    printf("\nDESEA MODIFICAR OTRO ARTISTA O ALBUM? ");
                    fflush(stdin);
                    scanf(" %c", &opcion);
                } while (opcion == 's' || opcion == 's');
                opcion = 's';
                break;

            case 10:
                while (opcion == 's') {
                    playlist();
                    printf("\nQuiere reproducir otra cancion? ");
                    fflush(stdin);
                    scanf(" %c", &opcion);
                    system("cls");
                }
                opcion = 's';
                break;

            default:
                printf("\nOPCION NO VALIDA");
                break;
            }
        }
    }while (control != 0);


    return 0;
}

///Selecciona una de las canciones cargadas en el sistema
void playlist () {
    int control = 0;
    int terminar = 0;

    control = menuCanciones();
    switch(control) {

        case 1:
            playAudio("Dontlookback");
            printf("\nTERMINAR CANCION?(1)");
            scanf("%d", &terminar);
            if (terminar == 1) {
                stopAudio();
            }
            break;

        case 2:
            playAudio("Scar_tissue");
            printf("\nTERMINAR CANCION?(1)");
            scanf("%d", &terminar);
            if (terminar == 1) {
                stopAudio();
            }
            break;

         case 3:
            playAudio("She_said");
            printf("\nTERMINAR CANCION?(1)");
            scanf("%d", &terminar);
            if (terminar == 1) {
                stopAudio();
            }
            break;


         case 4:
            playAudio("Patricio_rey");
            printf("\nTERMINAR CANCION?(1)");
            scanf("%d", &terminar);
            if (terminar == 1) {
                stopAudio();
            }
            break;

         case 5:
            playAudio("Comeas_youare");
            printf("\nTERMINAR CANCION?(1)");
            scanf("%d", &terminar);
            if (terminar == 1) {
                stopAudio();
            }
            break;

        case 6:
            playAudio("Dancing_days");
            printf("\nTERMINAR CANCION?(1)");
            scanf("%d", &terminar);
            if (terminar == 1) {
                stopAudio();
            }
            break;

        case 7:
            playAudio("Wishyou_werehere");
            printf("\nTERMINAR CANCION?(1)");
            scanf("%d", &terminar);
            if (terminar == 1) {
                stopAudio();
            }
            break;

        case 8:
            playAudio("Adios");
            printf("\nTERMINAR CANCION?(1)");
            scanf("%d", &terminar);
            if (terminar == 1) {
                stopAudio();
            }
            break;

        case 9:
            playAudio("Bajan");
            printf("\nTERMINAR CANCION?(1)");
            scanf("%d", &terminar);
            if (terminar == 1) {
                stopAudio();
            }
            break;

        default:
            printf("\nOPCION NO VALIDA");
            break;
    }
}

/// Función para reproducir el archivo WAV
void playAudio(const char* filename)
{
    // Utiliza la función PlaySound de la biblioteca winmm
    if (PlaySound(filename, NULL, SND_FILENAME | SND_ASYNC))
    {
        printf("Reproduciendo %s\n", filename);
    }
    else
    {
        printf("Error al reproducir el archivo %s\n", filename);
    }
}

/// Función para detener el audio
void stopAudio()
{
    // Utiliza la función PlaySound con NULL para detener la reproducción
    PlaySound(NULL, 0, 0);
    printf("Audio detenido.\n");
}

