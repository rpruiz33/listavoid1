#ifndef ALUMNO_H_INCLUDED
#define ALUMNO_H_INCLUDED

#define ALUMNO_H_INCLUDED
#include "lista.h"
struct AlumnoE;
struct InmuebleE;
typedef struct AlumnoE *AlumnoP;
typedef struct InmuebleE*InmuebleP;
AlumnoP contructorAlumno(char nombre[20],int dni ,float promedio);
InmuebleP contructorInmueble(char direcion[20],char duenio [20] ,int anioConstruccion ,float valor );
void DesrtructorAlumno(AlumnoP a);
void DesrtructorInmueble(InmuebleP a);
void Mostrar(AlumnoP a);
char * getNombre(AlumnoP a);
float getPromedio(AlumnoP a);
int getDni(AlumnoP a);

void setNombre(AlumnoP a, char nombre[20]);
void setDni(AlumnoP a, int dni);
void setPromedio(AlumnoP a, float promedio);
void ordeanarXnombre();
void* listaGet ( Lista *list, int pos);
bool listaSwap (Lista *list, int pos1, int pos2);
Lista* listaBubbleSort(Lista *list, int (*canSwap)(void *data1, void *data2));
int DecSort (void *x, void *y);
void mostrarLista (Lista *list);
Lista* listaDuplicate ( Lista *list);
#endif // ALUMNO_H_INCLUDED
