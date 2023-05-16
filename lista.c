#include "lista.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//static lo que hace es que solo puedas usar la funcion en el documento que esta declarada
static Nodo* crearNodo (Lista *list, void *data) {
    Nodo *temp =  malloc(sizeof (Nodo));//se reserva memoria para el nodo  punetero temp
    if (!temp) return false;//si no existe retorna falso
    temp->data = malloc(list->tamDelDatoEnBytes);//reserca memoria del tamaño en bytes de la lista
    if (!temp->data) {//si existe el espacio de memoria
        free(temp);//libera la memoria
        return temp;//retorn el nodo
    }
    memcpy(temp->data, data, list->tamDelDatoEnBytes);// copia el tamaña de memoria de de la lista  desde data hacia temp->data
    return temp;//retorno temp que serie el nodo
}

bool listaInit(Lista *list, int tamDelDatoEnBytes) {//funcion del tipo booleano que inicializa la lista
    if (!list)//si no existe la lista retorna false
        return false;
    list->primero = list->ultimo = NULL;// sino al primer nodo y al ultimo los pongo nulos
    list->size = 0;//le doy tamaño al atributo size 0
    list->tamDelDatoEnBytes = tamDelDatoEnBytes;//le paso el parametro
    return true;//retorno verdadero pq la lista esta iniciada
}

bool listaIsEmpty (Lista *list) {//funcion si la lista esta vacia parametros la lista
    if (!list)//validad que la lista exista
        return true;//retorna verdadero si existe
    return (list->size == 0);//pone en 0 el tamaño y lo retorna
}

int listaGetSize ( Lista *list) {//funcion que retorna el tamaño de la lista
    if (!list)//si la listano  existe
        return -1;//retorna -1
    return list->size;//sino retorena el tamaño de la lista
}

/*void* listaGet ( Lista *list, int pos) {
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
}*/

bool listaGetCopyOf (Lista *list, int pos, void *backup) {
    if (!list || pos < 0 || list->size <= 0 || pos >= list->size) // Lista vazia ou posição nula
        return false;

    if (pos == 0) {
        memcpy(backup, list->primero->data, list->tamDelDatoEnBytes);
        return true;
    }

    if (pos == list->size - 1) {
        memcpy(backup, list->primero->data, list->tamDelDatoEnBytes);
        return true;
    }

    Nodo *f;
    for ( int i = 0; i < pos; i++) {
        if (i == 0)
            f = list->primero;
        else
            f = f->proximo;
    }

    memcpy(backup, f->proximo->data, list->tamDelDatoEnBytes);
    return true;
}

bool listaPushFront (Lista *list, void *data) {
    Nodo *temp;
    if (!(temp = crearNodo(list, data)))
        return false;

    if (list->size == 0) {
        list->primero = list->ultimo = temp;
        temp->proximo = NULL;
        list->size++;
        return true;
    }

    temp->proximo = list->primero;
    list->primero = temp;
    list->size++;
    return true;
}

bool listaPushBack (Lista *list, void *data) {
    Nodo *temp;
    if (!(temp = crearNodo(list, data)))
        return false;

    if (list->size == 0) {
        list->primero = list->ultimo = temp;
        temp->proximo = NULL;
        list->size++;
        return true;
    } else {
        list->ultimo->proximo = temp;
        list->ultimo = temp;
        list->ultimo->proximo = NULL;
    }

    list->size++;
    return true;
}

bool listaPopFront (Lista *list, void *backup) {
	if (list->size == 0)
		return false;
    else if (list->size == 1) {
        memcpy(backup, list->primero->data, list->tamDelDatoEnBytes);
        listaClear(list); // Portanto, apenas limpe a lista!
    } else {
        Nodo *proximoCpy = list->primero->proximo;
        memcpy(backup, list->primero->data, list->tamDelDatoEnBytes);

        free(list->primero->data);
        free(list->primero);
        list->primero = proximoCpy;
        list->size--;
    }
    return true;
}

bool listaPopBack (Lista *list, void *backup) {
    if (!list)
        return false;

    // Se a lista tiver apenas 1 elemento
    if (list->size == 1) {
        memcpy(backup, list->primero->data, list->tamDelDatoEnBytes);
        listaClear(list);
    }
    // A lista possui mais de um elemento
    else {
        Nodo *f = NULL, *ultimo = NULL;
        memcpy(backup, list->ultimo->data, list->tamDelDatoEnBytes);

        // Percorre a lista até encontrar o penúltimo elemento da lista
        for (f = list->primero; f != list->ultimo; f = f->proximo)
            ultimo = f;

        // Nesse momento 'ultimo' aponta para o penúltimo elemeto da lista

        free(list->ultimo->data); // Remove o dado do último elemento
        free(list->ultimo); // Remove o último elemento
        list->ultimo = ultimo; // Agora o último elemento se torna 'ultimo'
        list->ultimo->proximo = NULL; // Portanto ultimo->proximo deve ser NULL
        list->size--;
    }
    return true;
}

bool listaInsert (Lista *list, void *data, int pos) {

    if (!list || pos < 0 || pos > list->size) // Lista nula ou posição inválida
        return false;

    if (pos == 0) // Insere na primeira posição
        return listaPushFront(list, data);

    if (pos == list->size) // Insere na última posição
        return listaPushBack(list, data);

    // Insere no meio
    Nodo *f = NULL;
    for (register int i = 0; i < pos; i++) {
        if (i == 0)
            f = list->primero;
        else
            f = f->proximo;
    }
    // Nesse momento 'f' aponta para a posição anterior à que será inserido o elemento

    Nodo *temp;
    if (!(temp = crearNodo(list, data)))
        return false;

    temp->proximo = f->proximo;
    f->proximo = temp;
    list->size++;
    return true;
}

bool listaRemove (Lista *list, int pos, void *backup) {

    if (!list || list->size <= 0 || pos < 0 || pos >= list->size) // Lista vazia ou nula ou posição inválida
        return false;

    // Remove da última posição
    if (pos == list->size - 1)
        return listaPopBack(list, backup);

    // O usiário deseja remover um elemento do início
    if (pos == 0)
        return listaPopFront(list, backup);

    // Remover algum elemento no MEIO da lista
    Nodo *f = NULL, *proximoCpy;
    for (register int i = 0; i < pos; i++) {
        if (i == 0)
            f = list->primero;
        else
            f = f->proximo;
    }
    // Nesse momento 'f' aponta para o elemento anterior ao que será removido

    proximoCpy = f->proximo->proximo; // 'proximoCpy' aponta para o elemento posterior ao que será removido
    memcpy(backup, f->proximo->data, list->tamDelDatoEnBytes);

    free(f->proximo->data); // Remove o VALOR do elemento (Célula) entre 'f' e 'proximoCpy', que pertence justamente o elemento que o usuário deseja remover
    free(f->proximo); // Remove o ELEMENTO entre 'f' e 'proximoCpy', que é justamente o elemento que o usuário deseja remover
    f->proximo = proximoCpy; // Portanto lique 'f' em 'proximoCpy'
    list->size--;
    return true;
}

void listaClear (Lista *list) {
    if (!list || list->size <= 0 || list->primero == NULL)
        return;

    // 'curr' iniciará apontando para o primeiro elemento da lista e proximo para o segundo
    // (que pode ser nulo caso a lista possua apenas um elemento)

    register Nodo *proximo;
    for (register Nodo *p = list->primero; p != NULL;) {
        proximo = p->proximo;
        free(p->data);
        free(p);
        p = proximo;
    }

    list->primero = NULL;
    list->ultimo = NULL;
    list->size = 0;
}

/*Lista* listaDuplicate ( Lista *list) {
    if (!list)
        return NULL;
    Lista *temp = (Lista*) malloc(list->tamDelDatoEnBytes);
    listaInit(temp, list->tamDelDatoEnBytes);
    for (Nodo *p = list->primero; p != NULL; p = p->proximo)
        listaPushBack(temp, p->data);
    return temp;
}
*/
inline void *listaGetFirst( Lista *list) {
    if (!list)
        return NULL;
    return list->primero->data;
}

inline void *listaGetLast(Lista *list) {
    if (!list)
        return NULL;
    return list->ultimo->data;
}

void listaCopy(Lista *dest, Lista *orig) {
    if (!dest || !orig || dest->tamDelDatoEnBytes != orig->tamDelDatoEnBytes)
        return;
    listaClear(dest);
    dest->tamDelDatoEnBytes = orig->tamDelDatoEnBytes;
    for (int i = 0; i < orig->size; ++i) {
        listaPushBack(dest, listaGet(orig, i));
    }
}

/*bool listaSwap (Lista *list, int pos1, int pos2) {
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
}*/
 int correcto (int *canSwap){

     void *data1;

    void *data2;

}
/*Lista* listaBubbleSort(Lista *list, int (*canSwap)(void *data1, void *data2)) {
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
}*/


Lista* listaQuickSort(Lista *list, int beg, int end, int (*compare)(void *data1, void *data2)) {
	void* pivot = listaGet(list, (beg + end) / 2);
	int i = beg;
	int j = end;

	while (i < j) {
        while (compare(listaGet(list, i), pivot) < 0 && i < end)
            i++;

        while (compare(listaGet(list, j), pivot) > 0 && i < end)
            j--;

        if (i <= j) {
			listaSwap(list, i, j);
            i++;
            j--;
        }
    }

    if (i < end)
        listaQuickSort(list, i, end, compare);
    if (j > beg)
        listaQuickSort(list, beg, j, compare);

    return list;
}
