# Rapport 3A IBD
## Projet   : yamlDB
*QUERET Olivier, LINCK Hugo, SIMON Pierre*
## Outils utilisé
### Partage & Communication
<center>
    <a href="https://github.com/rypall/yamlDataBase/tree/part4/gtk">
        <img src="https://image.flaticon.com/icons/png/512/25/25231.png" style="width: 200px;"/>
    </a>
    <img src="https://pbs.twimg.com/media/DCEe9aPXYAA4joh.png" style="width:200px;"/>
</center>

### IDE
<center>
    <img src="https://confluence.jetbrains.com/download/attachments/54342479/CLION?version=3&modificationDate=1449748289000&api=v2" style="width: 173px;"/>
    <img src="https://i.imgur.com/q603VZ3.png" style="width:400px;"/>
</center>

## Découpage & choix d'implémentations gloable du projet
* __Fonction système__
   
   Toutes les fonctions qui interagissent avec le système. Comme la création ou la suppression d'un fichier.
* __Parser yaml__

   BLABLA
* __Parser SQL__

   BLABLA
* __Core programme__

   BLABLA
* __Fonctions Générique__

   BLABLA
## Fonctions principales
### Fonction système
```C
extern char CURRENT_DATABASE[MAX];
int createDB(char *);
int useDB(char *);
int createTable(char *);
int createEmptyFile(char *, char *);
int initYamlFile(char *);
int isExist(char *);
int dropTable(char *);
int dropDB(char *);
```
### Parser yaml
```C
extern int FILE_LINE_COUNTER;
listOfLines* addLineToList(listOfLines*, lineStruct);
void displayListOfLines(listOfLines*);
void freeListOfLines(listOfLines**);
listOfEntities* addEntityToList(listOfEntities*, listOfLines*);
listOfEntities* removeLastEntity(listOfEntities**);
listOfEntities* removeEntityAt(listOfEntities**, int);
void displayListOfEntities(listOfEntities*);
void freeListOfEntities(listOfEntities**);
int isEOY(char*);
int verifLine(char*);
char* getKey(char*);
char* getValue(char*);
lineStruct getLineStruct(char*);
listOfLines* getEntity(int, char*);
int compareIntoLine(lineStruct, char*, char*, char*);
int compareIntoEntity(listOfLines*, char*, char*, char*);
int compareIntoList(listOfEntities*, char*, char*, char*);
int updateLine(lineStruct*, char*, char*);
listOfEntities* getBlocksWhere(arrayOfStrings, arrayOfStrings, arrayOfStrings, char*);
listOfEntities* getAllFrom(char*);
int updateFile(char*, listOfEntities*);
int updateValuesWhere(AoS, AoS, AoS, AoS, AoS, char*);
int insertLine(lineStruct, char*);
int insertEntity(listOfLines*, char*);
int insertListOfEntities(listOfEntities*, char*);
```
### Parser SQL
```C
typedef struct commandSQL {
    char *name;
    void (*functionSQL)(char *);
} commandSQL;
void parserSQL(char *);
void queryExit(char *);
void queryError(char *);
```
### Core programme
```C
void queryUse(char *);
void queryCreateDatabase(char *);
void queryDropDatabase(char *);
void queryDropTable(char *);
void queryCreateTable(char *);
void queryInsert(char *);
void queryUpdate(char *);
void queryDelete(char *);
void insertSqlValues(char *);
void splitCreateQuery(char *, const char *);
void goSplitCreateQuery(char *, const char *);
char *strtok1(char *, const char *);
void valuesUpdateQuery(char *);
void condDeleteQuery(char *);
```
### Fonctions Générique
```C
void menu();
char *upWord(char *);
char *cleanQuery(char *);
int isAlphaNum(char *);
int countArgs(char *, const char *);
char *splitWord(char *, const char *);
int correctWord(char *);
char *checkExprSQL(char *, char *);
char *checkTypeSQL(char *);
int fGoToLine(int, FILE *);
void error(const char *);
char *whichType(char *);
char *updateSplitWord(char *, int, int);
int isNumber(char);
char *insertSplit(char *buffer, int number);
int fSize(FILE *);
int freadLine(char *, unsigned int, FILE *);
int countTab(char *);
int strSearchInArray(char *, arrayOfStrings);
arrayOfStrings createArrayOfStrings(unsigned int);
arrayOfStrings updateArrayOfStrings(arrayOfStrings, unsigned int);
void freeArrayOfStrings(arrayOfStrings *);
int compare(char *, char *, char *);
```
## Documentation
### Partie 1 à 3 : yamlDB en ligne de commande
__Syntaxe SQL__
```SQL
CREATE DATABASE <database_name>;
USE <database_name>;
CREATE TABLE <nom_table> ( <colonne1> <type_donnees>, <colonne2> <type_donnees>, ... );
-- Type de données : INT | FLOAT | CHAR | VARCHAR
-- Options : PRIMARY KEY | NOT NULL
INSERT INTO <nom_table> VALUES ('valeur 1', 'valeur 2', ...);
UPDATE <nom_table> SET <colonne1> = 'nouvelle valeur', ... WHERE {conditions};
DELETE FROM <nom_table> WHERE {conditions};
DROP TABLE <nom_table>;
DROP DATABASE <database_name>;
```
__Syntaxe YAML__
```YAML
---
# Les commentaires sont précédés d'un signe "#", comme cette ligne.
# Gestion simple type séquence clé : valeur
-
    clé: valeur
    valeur_numérique: 100
    autre_clé : du text
    une_autre_clé : "du text"
...
```
### Partie 4 : GTK pour une belle interface
<center>
    <img src="https://i.imgur.com/HMziues.png" style="width:800px;"/>
</center>

L'interface est découpé en trois parties :
* Les actions possibles : *nouveau fichier, ouvrir, enregistrer, enregistrer sous, fermer le fichier, quitter*
* L'arborescence disque
* Le contenu du fichier