#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
/*Constantes*/
#define MAX_C 50
#define MAX_N 20    /*Nombre*/
#define MAX_A 50    /*Apellidos*/

/*Variable para alumnos*/
typedef char genero;
typedef char mail[MAX_C];

/*----Registro para alumnos-----*/
/*Nombre Completo*/
typedef struct{
     char nombre[MAX_N];
     char apellidos[MAX_A];
}nombreAl;

/*Fecha*/
typedef struct{
	int dia, mes, any;
	}fechaAl;

/*DNI*/
typedef struct {
	int num;
	char letra;

}dni;

/*Alumno*/
typedef struct{
	dni dni_a;
	genero genero_a;
	nombreAl n_alumno;
	fechaAl fecha;
	mail correo;
}db_alumno;


/*Nodo Alumno doble enlazado*/
typedef struct nodo{
	db_alumno alumno;
	struct nodo* next; /*Apuntando hacia delante*/
	struct nodo* prev; /*Apuntando hacia detras*/
    int cantidad;
	float nota [];
}nodo;

typedef nodo *puntero;
typedef nodo *lista;

/*FUNCIONES*/
void Mayus(char *nomAl);
char letraDNI(int numDni);
void nuevoAlumno(lista *head);
void functionMenu();
void MostrarLista(lista head, char orden);
lista buscarDNI(puntero head);
bool sonIguales(char name1[], char name2[]);
lista buscarAlumno(puntero head);
void ultimoAlumno(puntero ulAlu);
void borrar_alumno(puntero last, nodo** head);
void guardarFit(lista head);
int contarNotas();
void cargarFit(lista *head);
void maxNota(puntero head);
void borrarTodo (lista *head);


#endif // HEADERS_H_INCLUDED
