//gcc -o main.tst -x c main.c
//Una nota importante, este programa requiere que todos los archivos de entrada posean una línea vacía al final del archivo

#include <stdio.h>//librería de entrada/salida
#include <stdlib.h>//librería de estándar de C
#include <string.h>//necesito poder manejar strings arbitrariamente
#include <regex.h>//necesito expresiones regulares
#include <omp.h>//librerías de openmp

int main(int argc, char *argv[])
{
    //primero debo cargar todos los archivos especificados por lo ingresado en la línea de comandos
    #pragma omp parallel for
    for(int documento = 1; documento < argc;documento++){//debo empezar en 1 para saltarme la información de en dónde se está ejecutando esto
        printf("Intentado abrir el archivo: %s\n", argv[documento]);
        FILE * handleArchivo = fopen(argv[documento],"r");//necesito abrir el archivo en la posición documento en modo de sólo lectura, sólo necesito leerlo
        if(handleArchivo == NULL){
            printf("Ocurrió un error al abrir el archivo\n");
            //return -1;
        }
        //archivo abierto correctamente
        printf("Archivo abierto correctamente, leyendo información\n");
        char * informacionArchivo = malloc(sizeof(char));//el sitio donde estará toda la información, empieza con un sólo caracter
        informacionArchivo[0] = '\0';
        char lineaLeida[200];

        while(feof(handleArchivo) == 0){//mientras no haya alcanzado el fin del archivo
            fgets(lineaLeida, 200, handleArchivo);//leeré la siguiente línea de 50 caracteres.
            char * punteroRevision = realloc(informacionArchivo, (strlen(informacionArchivo)+strlen(lineaLeida))*(sizeof(char)));
            if(punteroRevision == NULL){
                printf("Error de asignación de memoria, saliendo...\n");
                //return -2;
            }
            informacionArchivo = punteroRevision;
            strcat(informacionArchivo, lineaLeida);
            //printf("%s\n",informacionArchivo);//veamos qué conseguí
        }
        printf("%s",informacionArchivo);//veamos qué conseguí
        fclose(handleArchivo);//tengo que cerrarlo, ya terminé de leerlo
        //ahora el análisis

        //todo finalizado, liberando
        free(informacionArchivo);
    }

    return 0;
}
