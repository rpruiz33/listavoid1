#include "lista.h"
#include "alumno.h"
#include <stdio.h>
#include <stdlib.h>



int main() {
    //Crea la lista
    printf("------- Creamos Lista de enteros--------\n");
    Lista list;

    //Inicia la lista

    listaInit(&list, sizeof(AlumnoP));

    printf("Esta vacia la lista: %d\n", listaIsEmpty(&list));

    //10 para agregar
  /* AlumnoP d=contructorAlumno("rober",1234,7.2);
    listaPushBack(&list, &d);

    AlumnoP d1=contructorAlumno("lucho",3333,6.3);
    listaPushBack(&list, &d1);

    AlumnoP d2=contructorAlumno("papa",55555,8.3);
    listaPushBack(&list, &d2);

    AlumnoP d3=contructorAlumno("mama",333,8.1);
    listaPushBack(&list, &d3);

    AlumnoP d4=contructorAlumno("tony",1111,7.3);
    listaPushBack(&list, &d4);*/

    InmuebleP d=contructorInmueble("3 DE MAYO 3432","ROBERTO",1999,1212121);
    listaPushBack(&list, &d);
    mostrarLista(&list);
    d=contructorInmueble("4 DE MAYO 122","ROBERTO",2005,333333);
    listaPushBack(&list, &d);
    mostrarLista(&list);
    d=contructorInmueble("3 DE MAYO 3432","ROBERTO",1999,444444);
    listaPushBack(&list, &d);
    mostrarLista(&list);


    printf("Ya insertamos todos los elementos...\n");
    printf("El tamanio final es: %d\n", listaGetSize(&list));


    printf("Orden  >...");
    listaBubbleSort(&list, DecSort);
    mostrarLista(&list);

    listaDuplicate(&list);

    mostrarLista(&list);
    listaClear(&list);

    printf("Esta vacia la lista: %d\n", listaIsEmpty(&list));




    return 0;
}
