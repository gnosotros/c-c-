
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#define CREATE_TABLE_PERSONA \
    "CREATE TABLE IF NOT EXISTS persona" \
    "(id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL" \
      ", nombre TEXT NOT NULL" \
      ", edad INTEGER NOT NULL);"

typedef struct Persona Persona;

struct Persona {
            char nombre [70];
            int edad;
            int id;
            Persona *siguiente; //lista enlazada
};

//se pone como constante pero el conpilador no deja
//void muestraLista(const Persona *lista)
void muestraLista(Persona *lista){
    if (lista == NULL){
       printf("[Lista vacia]\n");
       return;
    }
    Persona *ix = lista;
    while (ix!=NULL){
      printf("ID: %d; Nombre %s; Edad %d\n", ix->id, ix->nombre, ix->edad);
      ix=ix->siguiente;
   }
}
Persona *personaNueva(const Persona *persona) {
    Persona *p =(Persona *) malloc(sizeof(Persona));
    strcpy(p->nombre, persona->nombre);
    p->edad=persona->edad;
    p->id =persona->id;
    p->id=-1;
    p->siguiente=NULL;
    return p;

}

void agregaPersona(Persona **lista, const Persona *persona){
    if (lista==NULL){
        return;
    }
    if (*lista==NULL){
        *lista=personaNueva(persona);
        return;
    }
    Persona *ix= *lista;
    while (ix->siguiente !=NULL){
        ix->siguiente;
    }
    ix->siguiente=personaNueva(persona);
}

int gestionaError(sqlite3 *db){
    fprintf(stderr, "Error sqlite %s\n", sqlite3_errmsg(db));
    return sqlite3_errcode(db);
}

//using namespace std;

void introduceDatos(Persona *lista,sqlite3 *db){
    if(lista==NULL){
        return;
    }
    Persona *ix =lista;
    char sql[100];
    while (ix!=NULL){
            sprintf(sql,"INSERT INTO persona (nombre, edad ) VALUES ('%s', %d)", ix->nombre, ix->edad);
            if(sqlite3_exec(db,sql,NULL,NULL, NULL )!=SQLITE_OK){
                gestionaError(db);
                return;
            }
        ix=ix->siguiente;

    }

}

int callback(void *ptr, int numeroColumnas,char**valorCelda,char**nombresColumnas){
    (void)ptr;
    //printf("%d", numeroColumnas);
    //printf("%s\n", *valorCelda);
    //printf("%s\n", *nombresColumnas);

    int ix;
    for (ix=0; ix<numeroColumnas; ++ix){
        printf("%s: %s\n", nombresColumnas[ix], valorCelda[ix]);
    }
    printf("\n");
    return 0;
}

void leeBaseDatos(sqlite3 *db){
    sqlite3_exec(db, "SELECT * FROM persona", callback, NULL, NULL);
}

int main(){
    FILE *file=NULL;
    Persona persona;
    Persona *lista = NULL;
    sqlite3 *db = NULL;
    const char *filenameDatabase = "tarjet2.db";
    const char *filenameLista = "datos.txt";

    //abrir base de datos
    if(sqlite3_open(filenameDatabase, &db)!= SQLITE_OK){
        return gestionaError(db);
    }

    //configura base de datos
    if (sqlite3_exec(db, CREATE_TABLE_PERSONA, NULL, NULL, NULL)!=SQLITE_OK)//pasamos bd,sentencia sql, funcion(), argumento extra, msg error
    {
        return gestionaError(db);
    }

    //lee lista
    file=fopen(filenameLista, "r");
    if (file!=NULL){
             while (!feof(file)){                        // not file end of file (!feof) mientras no este en el final del archivo
                fscanf(file, "%s%d", persona.nombre, &persona.edad);
                agregaPersona(&lista, &persona);          //pasamos la direccion de memoria para no copiar todo el contenido
                }
                fclose(file);
    } else {
        fprintf(stderr, "error de archivo");
    }

    // comprobar que se lleno la lista
    muestraLista(lista);


    //introduce datos
    introduceDatos(lista,db);

    //lectra de base de datos
    leeBaseDatos(db);

    //cerramos el sqlite
    sqlite3_close(db);



    return 0;
}
