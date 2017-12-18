# Rapport 3A IBD
## Projet   : yamlDB
*QUERET Olivier, LINCK Hugo, SIMON Pierre*
## Outils utilisé
### Partage & Communication
<p align="center">
    <a href="https://github.com/rypall/yamlDataBase/tree/part4/gtk">
        <img src="https://image.flaticon.com/icons/png/512/25/25231.png" width="100" height="auto"/>
    </a>
    <img src="https://pbs.twimg.com/media/DCEe9aPXYAA4joh.png" width="100" height="auto"/>
</p>

### IDE
<p align="center">
    <img src="https://confluence.jetbrains.com/download/attachments/54342479/CLION?version=3&modificationDate=1449748289000&api=v2" width="86" height="auto"/>
    <img src="https://i.imgur.com/FrSvn5s.png" width="200" height="auto"/>
</p>

## Découpage & choix d'implémentations gloable du projet :rocket:
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
## Documentation :clipboard: 
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
    <img src="https://i.imgur.com/tB0hYxE.png" width="680" height="auto"/>
</p>

__L'interface est découpé en trois parties :__
* Les actions possibles : *nouveau fichier, ouvrir, enregistrer, enregistrer sous, fermer le fichier, quitter*
* L'arborescence disque
* Le contenu du fichier
## Bilan THE END :calendar: 
Nous avions plutôt bien demarré en établissant un découpage plutôt efficace du projet. Mais le temps passe vite.
Nous avons pu délivrer un résultat mais qui ne répond pas aux attentes fixées.
Nous espérions réussir à répondre à plus de critère des différentes parties. Nous avons mis trop de temps à réunir les différentes morceaux de chacun pour faire un bilan et avancé plus efficacement. Nous avons donc du faire des choix et modification de dernière minute.
Malgrès tous ça, il y a quand même des points positifs. Nous avons réussi à garder un rythme de travail, communiquer et échanger entre nous pour faire valoir nos idées et points de vue.
