#include "alumno.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct AlumnoE{
int dni;
float promedio;
char nombre[20];
};
//con lista de inmuebles
struct InmuebleE{
int anioConstruccion;
float valor;
char direccion[20];
char duenio[20]
};;


AlumnoP contructorAlumno(char nombre[20],int dni ,float promedio ){
 AlumnoP a=malloc(sizeof(struct AlumnoE));
 a->dni=dni;
 strcpy(a->nombre,nombre);
 a->promedio=promedio;

 return a;

};

InmuebleP contructorInmueble(char direcion[20],char duenio [20] ,int anioConstruccion ,float valor ){
 InmuebleP a=malloc(sizeof(struct InmuebleE));
 a->anioConstruccion=anioConstruccion;
 strcpy(a->duenio,duenio);
 a->valor=valor;
 strcpy(a->direccion,direcion);

 return a;

};

void DesrtructorAlumno(AlumnoP a){
free(a);

};
void DesrtructorInmueble(InmuebleP a){
free(a);

};
void Mostrar(AlumnoP a){
printf("\n%d dni,%s nombre, %f promedio\n",a->dni,a->nombre,a->promedio);

};
void MostrarInmueble(InmuebleP a){
printf("\n%d anio de la construcion,%s la direcion,%s el dueño %f valor\n",a->anioConstruccion,a->direccion,a->duenio,a->valor);

}
char*  getNombre(AlumnoP a){
return a->nombre;

};
float getPromedio(AlumnoP a){
return a->promedio;

};
int getDni(AlumnoP a){
return a->dni;

};

void setNombre(AlumnoP a, char nombre[20]){
strcpy(a->nombre,nombre);
}
void setDni(AlumnoP a, int dni){
a->dni=dni;
}
void setPromedio(AlumnoP a, float promedio){
a->promedio=promedio;
}
Lista* listaBubbleSort(Lista *list, int (*canSwap)(void *data1, void *data2)) {
    if (!list)
        return NULL;
    for (int i = 0; i < list->size - 1; ++i) {
        bool quit = true;
        for (int j = 0; j < list->size - 1; ++j) {
            if (canSwap(listaGet(list, j), listaGet(list, j+1)) < 0) {
                listaSwap(list, j, j+1);
                quit = false;
            }
        }
        if (quit)
            break;
    }
	return list;
}


bool listaSwap (Lista *list, int pos1, int pos2) {
    if (!list || pos1 < 0 || pos2 < 0 || pos1 >= list->size || pos2 >= list->size || pos1 == pos2)
        return false;

    void *temp = malloc(list->tamDelDatoEnBytes);
    if (!temp)
        return false;

    memcpy(temp, listaGet(list, pos1), list->tamDelDatoEnBytes);

    memcpy(listaGet(list, pos1), listaGet(list, pos2), list->tamDelDatoEnBytes);
    memcpy(listaGet(list, pos2), temp, list->tamDelDatoEnBytes);

    free(temp);
    return true;
}
void* listaGet ( Lista *list, int pos) {
    if (!list || pos < 0 || list->size <= 0 || pos >= list->size)//sino exista la lista , ai la pos es negativa, si el tamaño de la lista es negativo
        return NULL;                                                    //y si la pos es mayor al tamaño retorna un null

    if (pos == 0)// si la pos es igual a 0 retorn el  primer nodo con  el dato
        return list->primero->data;

    if (pos == list->size - 1)// si  la pos es la ultima retorna el nodo  con el ultimo dato
        return list->ultimo->data;

    Nodo *f = NULL;//nodo *f es nulo
    for ( int i = 0; i < pos; i++) {//bucle de i=0 hasta pos
        if (i == 0)//si es 0  quiere decir es el primer nodo
            f = list->primero;
        else
            f = f->proximo;//que sea el proximo
    }

    return f->proximo->data;//retorna el proximo nodo con la data
}
int DecSort (void *x, void *y) {
    AlumnoP a = *((AlumnoP*) x);
    AlumnoP b = *((AlumnoP*) y);

	if (getDni(a) > getDni(b))
		return -1;
	else if (getDni(a) < getDni(b))
		return 1;
	else
		return 0;
}
void mostrarLista (Lista *list) {
    for ( int i = 0; i < listaGetSize(list); ++i) {
        AlumnoP x = *( (AlumnoP*) listaGet(list, i) );
		printf("\n%d %s %f\n ", getDni(x),getNombre(x),getPromedio(x));
    }
   printf("\n");
}
Lista* listaDuplicate(Lista* list) {
    if (!list)
        return NULL;

    Lista* duplicate = malloc(sizeof(Lista));
    listaInit(duplicate, list->tamDelDatoEnBytes);

    Nodo* current = list->primero;
    while (!current) {
        listaPushBack(duplicate, current->data);
        current = current->proximo;
    }

    return duplicate;
}

