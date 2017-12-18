# Rapport 3A IBD
## Projet   : yamlDB
*QUERET Olivier, LINCK Hugo, SIMON Pierre*
## Outils utilisé
### Partage & Communication
<p align="center">
    <a href="https://github.com/rypall/yamlDataBase/tree/part4/gtk">
        <img src="https://image.flaticon.com/icons/png/512/25/25231.png" width="200" height="auto"/>
    </a>
    <img src="https://pbs.twimg.com/media/DCEe9aPXYAA4joh.png" width="200" height="auto"/>
</p>

### IDE
<p align="center">
    <img src="https://confluence.jetbrains.com/download/attachments/54342479/CLION?version=3&modificationDate=1449748289000&api=v2" width="173" height="auto"/>
    <img src="https://i.imgur.com/FrSvn5s.png" width="400" height="auto"/>
</p>

## Découpage & choix d'implémentations gloable du projet
* __Fonction système__

   Toutes les fonctions qui interagissent avec le système. Comme la création ou la suppression d'un fichier.
   Le stockage sur le disque des fichier yaml est découpé par dossier ou une dossier représente une database. Dans une database il peut y avoir une liste de table représentée par un dossier chacune, et dans une table deux fichier générique data.yaml et structure.yaml
* __Parser yaml__

   BLABLA
* __Parser SQL__

   Permet de rediriger la requête en fonction de son type (create, use, drop,...).
* __Core programme__

   Toutes les fonctions qui sont appelées par le parserSQL afin de traiter les requêtes. Ces fonctions utilisent les fonctions système et YAML, soit directement soit par des fonctions intermédiaires.
* __Fonctions Générique__

   Toutes les fonctions annexes utilisées par les Parsers YAML & SQL ainsi que par le système.
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
#define YAMLDATABASE_CORE_H
void queryUse(char *);
void queryCreateDatabase(char *);
void queryDropDatabase(char *);
void queryDropTable(char *);
void queryCreateTable(char *);
void queryInsert(char *);
void queryUpdate(char *);
void queryDelete(char *);
void querySelectAll(char *);
void insertSqlValues(char*, char*);
void splitCreateQuery(char *, const char *, char *);
void goSplitCreateQuery(char *, const char *, char *);
char *strtok1(char *, const char *);
void valuesUpdateQuery(char *, char *);
void condDeleteQuery(char *);
void condSelectQuery(char *);
```
### Fonctions Générique
```C
#define YAML_SOME_FUNCT_H
void menu();
extern int FILE_LINE_COUNTER;
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
arrayOfStrings createArrayOfStrings(int);
int updateArrayOfStrings(arrayOfStrings*, int);
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
<p align="center">
    <img src="https://i.imgur.com/tB0hYxE.png" width="800" height="auto"/>
</p>

__L'interface est découpé en trois parties :__
* Les actions possibles : *nouveau fichier, ouvrir, enregistrer, enregistrer sous, fermer le fichier, quitter*
* L'arborescence disque
* Le contenu du fichier
## Bilan THE END
Nous avions plutôt bien demarré en établissant un découpage plutôt efficace du projet. Mais le temps passe vite.
Nous avons pu délivrer un résultat mais qui ne répond pas aux attentes fixées.
Nous espérions réussir à répondre à plus de critère des différentes parties. Nous avons mis trop de temps à réunir les différentes morceaux de chacun pour faire un bilan et avancé plus efficacement. Nous avons donc du faire des choix et modification de dernière minute.
Malgrès tous ça, il y a quand même des points positifs. Nous avons réussi à garder un rythme de travail, communiquer et échanger entre nous pour faire valoir nos idées et points de vue.
