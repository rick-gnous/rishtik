# tp-shell

## Compilation

Il suffit de faire `make` pour compiler le fichier `shellOpt.c` ainsi que les bibliothèques se trouvant dans le dossier `boitoutil`.

## Bibliothèques

* parser : contient les méthodes permettant de récupérer et de manipuler les commandes de l’utilisateur
* essential_shell : contient les méthodes essentielles au shell (gestion des erreurs, commande cd…)

## Utilisation

Lancez le shell avec `./rishtic`. Il ne comprend que les commandes avec des arguments et des pipes simples (comme `ls | wc -l`). À partir de 2 pipes, le programme plante et tourne en boucle. Il faut alors l’arrêter avec `Ctrl+C`. Vous pouvez aussi le quitter de manière normale avec la commande `exit`.
