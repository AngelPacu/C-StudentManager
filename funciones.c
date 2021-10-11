#include "headers.h"


void Mayus(char *nomAl){
    int i=0;
    while (nomAl[i]!= '\n'){
        nomAl[i]=toupper(nomAl[i]);
        i++;
    }
}

char letraDNI(int numDni){
    char letras[23] = "TRWAGMYFPDXBNJZSQVHLCKE"; //Diccionario para asignar la letra automaticamente
    int pos;
    char letra;
    pos = numDni % 23; //Aplicamos la formula del DNI
    letra=letras[pos];
    return letra; //Devolvemos la letra para asignar
}

void nuevoAlumno(lista *head){
    puntero p,actual;
    int dni;
    int i = 0; //A lo mejor sobra
    int totalNotas;
    float nota;
    bool repetido = true;
    actual = *head; /*Colocamos el actual en la primera pos*/
    printf("Cantidad de notas a introducir al alumno: ");
    scanf("%d",&totalNotas);
    p = (nodo*)malloc(sizeof(nodo) + totalNotas * sizeof(nodo)); /*Reservamos la memoria en funcion de la cantidad de notas*/
    p->next = *head;
    fflush(stdin);
    if (p==NULL)printf("Error de memoria, cerrar programa!");
    else{
        /*Nombre*/
        printf("Escribe el nombre: ");
        fgets(p->alumno.n_alumno.nombre,MAX_N,stdin);
        Mayus(p->alumno.n_alumno.nombre);
        /*Apellidos*/
        printf("Escribe los apellidos: ");
        fgets(p->alumno.n_alumno.apellidos,MAX_N,stdin);
        Mayus(p->alumno.n_alumno.apellidos);
        /*DNI*/
        while (repetido){
            repetido = false; /*No hay numero repetido*/
            printf("Escribe el numero del DNI: ");
            scanf(" %d" ,&dni);
            while (dni<10000000 || dni > 99999999){
                printf("Error con el numero del DNI!\n\nEscribelo de nuevo: ");
                scanf(" %d" ,&dni);
            }
            for(puntero r=p; r!=NULL && repetido==false; r=r->next){
                if (dni == r->alumno.dni_a.num){
                    printf("Este DNI ya esta en uso. \n\n");
                    repetido=true;
                }
            }
        }
        p->alumno.dni_a.num=dni; /*Le damos el valor del DNI correcto*/
        p->alumno.dni_a.letra=letraDNI(p->alumno.dni_a.num); /*Calculamos la letra del DNI*/
        /*Correo*/
        printf("Escribe un correo: ");
        scanf(" %s", p->alumno.correo);
        /*Fecha*/
        printf("Introduce la fecha de nacimiento (dd/mm/aaaa): ");
        scanf("%d/%d/%d", &p->alumno.fecha.dia, &p->alumno.fecha.mes, &p->alumno.fecha.any);
        /*Genero*/
        printf("Introduce el genero (H/M): ");
        scanf(" %c", &p->alumno.genero_a);
        /*Nota*/
        while (i<totalNotas){
            printf("Escribe la nota: ");
            scanf(" %f", &nota);
            if (nota>=0 && nota<=10){
                p->nota[i]=nota;
                i++;
            }
            else{
                printf("Error!! La nota ha de entrar entre 0 y 10\n");
            }
        }
        p->cantidad = totalNotas; /*Guardamos la cantidad de notas*/
        actual = *head;
        if (actual){
            while(actual->prev){
                actual = actual->prev; /*Final de la lista*/
            }
        }
        if (!actual || actual->alumno.dni_a.num > dni){ /*Para el primer elemento*/
            p->next = actual;
            p->prev = NULL;
            if (actual) actual->prev = p; /*RevisaRR*/
            *head = p;
        }
        else {
            while (actual->next && actual->next->alumno.dni_a.num <= dni){ /*Para llegar a la ultima posicion o que el siguiente elemento sea el mas grande*/
                actual = actual->next;
            }
            p->next = actual->next; /*Recolocamos para insertar el nuevo nodo despues del anterior*/
            actual->next = p;
            p->prev = actual;
            if (actual->next && p->next){
                p->next->prev = p; /*Si la posicion no es ultima*/
            }
        }
    }
}

void functionMenu(){
    int num;
    lista head = NULL;
    lista ultAlu;
    char orden;
    char letra;
    bool menu=false;
    bool buscat=false;
    while(!menu){
        printf("\n\n----Gestor de Alumnos----\n\n");
        printf("1-Crear un alumno\n");
        printf("2-Buscar por DNI\n");
        printf("3-Buscar por nombre\n");
        printf("4-Mirar el ultimo alumno buscado\n");
        printf("5-Eliminar el ultimo alumno buscado\n");
        printf("6-Mostrar lista de alumnos\n");
        printf("7-Mostrar el alumno con mejor nota\n");
        printf("8-Borrar todos los alumnos\n");
        printf("9-Cargar alumnos (fichero)\n");
        printf("0-Sortir\n\n");
        printf("Escoge una opcion: ");
        scanf("%d", &num);
        fflush(stdin);
        switch (num) {
        case 1:
            nuevoAlumno(&head);
            printf("\nAlumno creado con exito!\n\n");
            break;
        case 2:
            system("cls");
            ultAlu=buscarDNI(head);
            buscat=true;
            break;

        case 3:
            system("cls");
            ultAlu=buscarAlumno(head);
            buscat=true;
            break;

        case 4:
            system("cls");
            if (buscat) ultimoAlumno(ultAlu);
            else printf("\nFalta buscar un alumno (Menu 2/3)\n");
            break;

        case 5:
            system("cls");
            borrar_alumno(ultAlu,&head);
            break;

        case 6:
            system("cls");
            printf("Mostrar lista Ascendiente o Descendinte  (A/D):\n");
            scanf(" %c" ,&orden);
            orden=toupper(orden);
            MostrarLista(head,orden);
            break;

        case 7:
            system("cls");
            maxNota(head);
            break;

        case 8:
            system("cls");
            printf("Quieres borrar todo el listado (S/N): \n");
            scanf(" %c" ,&letra);
            letra=tolower(letra);
            /*gets(letra);
            letra[0]=tolower(letra[0]);
            letra[1]=tolower(letra[1]);
            if ((strcmp(letra, "si")==0) || letra[0] == 's') borrarTodo (&head);*/
            if (letra == 's') borrarTodo (&head);
            break;

        case 9:
            cargarFit(&head);
            break;

        case 0:
            guardarFit(head);
            printf("Hasta luego!!!! ");
            menu=true;
            break;
        }
    }
}

void MostrarLista(lista head, char orden){
    system("cls");
    puntero nodo = head; /*Apuntamos al primer nodo*/
    if(head==NULL) printf("Lista Vacia\n\n");
    else{
        if(orden == 'A'){
            printf("Lista Ascendiente\n");
            printf("-----------------\n");
            for(nodo = head; nodo != NULL; nodo = nodo->next){ /*Recorreremos nodo por nodo y mostraremos la informacion contenida*/
                printf("\nNombre: %s", nodo->alumno.n_alumno.nombre);
                printf("\nApellidos: %s", nodo->alumno.n_alumno.apellidos);
                printf("\nDNI: %d-%c \n\n", nodo->alumno.dni_a.num, nodo->alumno.dni_a.letra);
            }
        }
        if(orden == 'D'){
            printf("Lista Descendiente\n");
            printf("-----------------\n");
            while(nodo->next!=NULL) nodo = nodo->next; /*Colocamos el puntero en el ultimo nodo*/
            for(;nodo != NULL; nodo = nodo->prev){ /*Recorreremos nodo por nodo y mostraremos la informacion contenida*/
                printf("\nNombre: %s", nodo->alumno.n_alumno.nombre);
                printf("\nApellidos: %s", nodo->alumno.n_alumno.apellidos);
                printf("\nDNI: %d-%c \n\n", nodo->alumno.dni_a.num, nodo->alumno.dni_a.letra);
            }
        }
    }
}

void mostrarAlumno(lista nodo){
        printf("\nNombre: %s", nodo->alumno.n_alumno.nombre);
        printf("\nApellidos %s", nodo->alumno.n_alumno.apellidos);
        printf("\nDNI: %d-%c", nodo->alumno.dni_a.num, nodo->alumno.dni_a.letra);
        printf("\nCorreo: %s", nodo->alumno.correo);
        printf("\nFecha de nacimiento: %d/%d/%d" ,nodo->alumno.fecha.dia,nodo->alumno.fecha.mes,nodo->alumno.fecha.any);
        printf("\nGenero: %c", nodo->alumno.genero_a);
        for (int i=0; i<nodo->cantidad; i++){
            printf("\nNota %d: %.2f",i+1,nodo->nota[i]);
        }



}

lista buscarDNI(puntero head){
    nodo* p = head;
    nodo* ult_alumno = NULL;
    int dni;
    bool encontrado = false;
    printf("---Buscador DNI---\n\n");
    printf("Introduce el DNI XXXXXXXXX: \n");
    scanf("%d", &dni);
    if (p==NULL){ /*Si no tenemos ningun alumno*/
        printf("ERROR! No hay ningun alumno en la lista!");
    }
    else{
        while(!encontrado){ /*Hacemos un bucle de busqueda hasta encontrar el dni*/
            if (dni<10000000 || dni > 99999999){
                printf("DNI INVALIDO! Introduce un DNI valido: ");
                scanf("%d", &dni);
            }
            else{
                if (p->alumno.dni_a.num==dni){
                    mostrarAlumno(p);
                    encontrado=true;  /*Ponemos a "true" la booleana para salir del while*/
                    ult_alumno=p; /*Le damos los datos del alumno y lo guardamos en la variable ult_alumno*/
                }
                else{
                    p=p->next; /*Avanzamos una posicion al nodo*/
                    if (p==NULL)encontrado = true; /*Ponemos a "true" la booleana para salir del bucle*/
                }
            }
        }
        if (ult_alumno==NULL) printf("No se ha encontrado el DNI en la lista"); /*Si se queda sin valor, no conseguimos ningun DNI*/
    }
    return ult_alumno;
}

bool sonIguales(char name1[], char name2[]){
    int i=0;
    while ((name1[i]==name2[i]) && (name1[i] != '\n')){
        i++;
    }
    return (name1[i] =='\n');
}

lista buscarAlumno(puntero head){
    nodo* p = head;
    nodo* ult_alumnoTemp = NULL;
    int total = 0; /*Variable para saber cuantos nombres repetidos tenemos en la lista*/
    bool primer = true;
    char nomAlumno[MAX_N];
    printf("---Buscador de nombres de alumnos---\n\n");
    printf("Introduce el nombre: \n");
    fgets(nomAlumno,MAX_N,stdin);
    Mayus(nomAlumno);
    if (p==NULL){ /*Si no tenemos ningun alumno*/
        printf("ERROR! No hay ningun alumno en la lista!");
    }
    else{
        while (p!=NULL){
            if (sonIguales(nomAlumno,p->alumno.n_alumno.nombre)){ /*Aplicamos la funcion "SONIGUALES" que sirve para abreviaciones tambien*/
                total++; /*Sumamos 1 si el nombre coincide*/
                if (primer){
                    printf("\nEl primer alumno encontrado es:");
                    mostrarAlumno(p);
                    ult_alumnoTemp=p;
                    primer = false; /*Imprimimos el primer alumno y pasamos la booleana a falsa para no volver a imprimir los datos*/
                }
            }
            p=p->next; /*Avanzamos la posicion del nodo*/
        }
        if (total>1) printf("\nHay un total de %d alumnos con el mismo nombre" ,total);
        if (total==0) printf("\nNo se ha encontrado alumnos");
    }
        return ult_alumnoTemp;

}

void ultimoAlumno(puntero ultAlu){
    printf("---Ultimo alumno---\n\n");
    if (ultAlu==NULL) printf("No se ha encontrado el ultimo alumno");
    else{
        mostrarAlumno(ultAlu);
    }
}

void borrar_alumno(puntero last, nodo** head){
    nodo* p = *head;
    char letra[1];
    printf("---Eliminar ultimo alumno---\n\n");
    if (*head==NULL) printf("No se ha podido encontrar a ningun alumno.\n");
    else {
        mostrarAlumno(last);
        printf("\n\nQuieres borrar el alumno seleccionado? (si/no):\n");
        scanf(" %s" ,letra);
        letra[0]=tolower(letra[0]);
        letra[1]=tolower(letra[1]);
        if ((strcmp(letra, "si")==0) || letra[0] == 's'){
            if (last==NULL) printf ("La lista esta vacia\n");
            else{
            /*ELIMINAR PRIMER NODO*/
                if (last == p){
                    if(last->prev) p = last->prev;
                    else p = last->next;
                    free(last);
                }
                /*ELIMINAR ULTIMO NODO*/
                if (last->prev){
                    last->prev->next = last->next;
                    free(last);
                }
                /*ELIMINAR NODO INTERMEDIO*/
                if (last->next){
                    last->next->prev = last->prev;
                    last->prev->next = last->next;
                    free(last);
                }
            printf("Se ha borrado el alumno con exito!");
            }
        }
    }
}

void guardarFit(lista head){
    FILE *fit;
    int i;
    fit=fopen("alumnos.txt","w+");
    puntero p = head;
    if (head==NULL){
        printf("\nNo hay ningun alumno!\n");
        fclose(fit);
    }
    else {
        for (p=head; p!=NULL; p=p->next){ /*Printamos uno a uno los datos del nodo*/
            fprintf(fit, "%s",p->alumno.n_alumno.nombre);
            fprintf(fit, "%s",p->alumno.n_alumno.apellidos);
            fprintf(fit, "%d-%c\n",p->alumno.dni_a.num, p->alumno.dni_a.letra);
            fprintf(fit, "%s",p->alumno.correo);
            fprintf(fit, "%d/%d/%d\n", p->alumno.fecha.dia, p->alumno.fecha.mes, p->alumno.fecha.any);
            fprintf(fit, "%c\n",p->alumno.genero_a);
            for (i=0; i<p->cantidad; i++){
                fprintf(fit, "%.2f\n",p->nota[i]);
            }
            fputc('*',fit);
            fputc('\n',fit);
        }
        fclose(fit);
    }
}

int contarNotas(FILE *temp){

    int i = 0; /*La linea de la nota es la numero 5 necesitamos un indice*/
    int total = 0;
    char c[100];
    while (c[0]!='*'){
        fgets(c,100, temp); /*Leemos la linea*/
        i++;
        if (i>=7 && c[0]!= '*'){ /*Sabemos que las notas estan en la posicion 7 del fichero*/
            total++; /*Incrementamos el numero de notas */
        }
    }
    return total;
}

void cargarFit(lista *head){
    puntero p,actual;
    FILE *fit, *fitTemp;
    p=NULL;
    fit = fopen("alumnos.txt", "r");
    fitTemp = fopen("alumnos.txt", "r"); /*Para calcular el total de notas de cada alumno*/
    int i;
    int totalNotas;
    char sub;
    char temp[MAX_N];
    if (fit==NULL) printf("Error con el fichero!");
    if (*head!=NULL)printf("Ya estan los alumnos cargados!");
    else{
        while (fscanf(fit, "%s",temp)!=EOF){
            i=0; /*Inicializamos cada vez que creamos un usuario*/
            actual = *head;
            totalNotas=contarNotas(fitTemp); /*Calculamos el total de notas de cada alumno*/
            p = (nodo*)malloc(sizeof(nodo) + totalNotas * sizeof(nodo)); /*Reservamos la memoria en funcion de la cantidad de notas*/
            strcpy(p->alumno.n_alumno.nombre,temp); /*Copiamos la variable del tempora*/
            fscanf(fit, " %s", p->alumno.n_alumno.apellidos);
            fscanf(fit, "%d-%c", &p->alumno.dni_a.num, &p->alumno.dni_a.letra);
            fscanf(fit, " %s", p->alumno.correo);
            fscanf(fit, "%d/%d/%d", &p->alumno.fecha.dia, &p->alumno.fecha.mes, &p->alumno.fecha.any);
            fscanf(fit, " %c", &p->alumno.genero_a);
            p->cantidad=totalNotas;
            while (i<p->cantidad){
                fscanf(fit, "%f", &p->nota[i]);
                i++;
            }
            p->nota[i]='\0'; /*Centinela que me sirve para la siguiente funcion*/
            if (actual){
                while (actual->prev) actual = actual->prev; /*Colocamos el puntero al principio de la lista*/
            }
            if (!actual){ /*Asignamos los punteros del primer nodo*/
                p->next=actual;
                p->prev=NULL;
                *head=p; /*Cargamos el valor del usuario*/
            }
            else{
                while (actual->next) actual = actual->next; /*Colocamos el puntero al final de la lista*/
                /*Insertamos un nodo despues del anterior*/
                p->next = actual->next;
                actual->next = p;
                p->prev = actual;
            }
            fscanf(fit, " %c", &sub); /*Guardamos en la variable el asterisco de los ficheros para empezar la siguiente vez con el siguiente usuario*/
        }
        printf("Todos los alumnos se han cargado con exito!");
        fclose(fit);
        fclose(fitTemp);
    }
}

void maxNota(puntero head){
    puntero p = head;
    puntero max = head;
    int i;
    printf("---Alumno con mejor nota---\n\n");
    if (p==NULL){
        printf("La lista esta vacia!");
    }
    else{
        for(p = head; p!= NULL; p = p->next){
            i=0; /*Para cada nota del alumno*/
             for(; p->nota[i]!= '\0'; i++){ /*Este centinela sirve para detectar el final del vector dinamico*/
                if (p->nota[i] > max->nota[0]){
                    max=p;
                }
            }
        }
        /*Datos del top alumno*/
        printf("\nEl alumno con mejor nota es:" );
        printf("\nNombre: %s", max->alumno.n_alumno.nombre);
        printf("\nDNI: %d-%c\n", max->alumno.dni_a.num, max->alumno.dni_a.letra);
        printf("Su mejor nota es: %f\n", max->nota[0]);
    }
}

void borrarTodo (lista *head){
    puntero p,actual;
    p = *head;
    while (p!=NULL){
        actual = p;
        free(actual);
        p = p->next;
    }
    *head=NULL;
    printf("La lista ya ha sido borrada!\n");
}
