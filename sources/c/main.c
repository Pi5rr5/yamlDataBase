#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../h/some_funct.h"
#include "../h/globals.h"
#include "../h/system_function.h"

int main() {
    //printf("create: %d\n",createTable("aa"));
    //printf("current: %s\n",CURRENT_DATABASE);
    //printf("use: %d\n",useDB("test"));
    printf("create db: %d\n",createDB("test"));
    printf("use: %d\n",useDB("test"));
    printf("current: %s\n",CURRENT_DATABASE);
    printf("create: %d\n",createTable("aa"));
    //printf("remove table: %d\n", dropTable("bb"));
    //printf("remove DB: %d\n", dropDB("test"));
    //menu();

    return 0;

}
// a mettre dans un autre fichier et dans un while






//test

// base : dossier
// table : dossier

// yaml nom du champs, null, defaut, pk

// utilisation structure


// systeme gestion dossier/fichiers, saisie commande SQL, function print





