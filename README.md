# tp-shell

## Compilation

Il suffit d’utiliser le make avec un de ces paramètres pour compiler le shell correspondant :

* shell1 (shell basique où juste une commande simple fonctionne)
* shell2 (shell permettant d’entrer une commande avec des paramètres)
* shell3 (shell permettant d’entrer deux commandes qui communiqueront tel un pipe)
* shellOpt (shell permettant d’utiliser | au lieu de taper la commande en 2 fois)

À part le shell3, tous les autres utilisent une bibliothèque développée par nos soins, se trouvant dans `src/include` (ne sachant ce qu’est la convention).

## Bugs

Lors de nos tests, les shells 1 et 2 marchent bien sauf si l’utilisateur entre plusieurs espaces avant de faire entrer, sans taper aucune commande.

Le shell 3 fonctionne bien mais a le meme bug que les shell 1 et 2 lorsque l’utilisateur entre plusieurs espaces avant de faire entrer.

Le shellOpt marche bien avec des commandes ne contenant qu’un pipe, comme `ls | wc-l`. Si l’on rajoute un pipe, le programme le fera marcher avant de planter si on retape une commande. Le exit ne marche pas non plus après plusieurs pipes.
