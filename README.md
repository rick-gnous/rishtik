# tp-shell

## Compilation

Il suffit de faire `make` pour compiler le fichier `shellOpt.c` ainsi que les bibliothèques se trouvant dans le dossier `boitoutil`.

## Bibliothèques

* parser : contient les méthodes permettant de récupérer et de manipuler les commandes de l’utilisateur
* essential_shell : contient les méthodes essentielles au shell (gestion des erreurs, commande cd…)
* oui-dire : echo mais recoder
* vars.h : contient des defines pour des variables globales

## Commandes natives

* cd chemin
* echo coucou : existe ausi avec `oui-dire` ou `ouï-dire`. On peut utiliser des variables avec `$nom_var`.
* export VAR=test : met la variable d’environnement VAR avec test
* exit : peut avoir un code en plus, quitte le shell en renvoyant l’erreur passé en paramètre (0 par défaut)

## Utilisation

Lancez le shell avec `./rishtic`. Il ne comprend que les commandes avec des arguments et des pipes simples (comme `ls | wc -l`). À partir de 2 pipes, le programme plante et tourne en boucle. Il faut alors l’arrêter avec `Ctrl+C`. Vous pouvez aussi le quitter de manière normale avec la commande `exit`.
