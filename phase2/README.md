# Laboratoire 5 : Serveur - Phase 2

Auteurs : Oussama Lagha et Adam Zouari  
Date : 8 Juin 2018
##But du laboratoire
Ajout d'un threadpool avec un taille maxiéale afin d'éviter les phénomènes néfastes liés au lancement d'un thread par requête,l'idée est d'allouer dynamiquement des threads au fur et à mesure que cela devient nécessaire jusqu'a atteindre la taille maximale ,si on atteint la taille maximale on doit réutilisé les threads au'ils ont dejà fini leurs traivaille.
## Choix du mécanisme

Durant cette phase du laboratoire, nous avons fait le choix d'utiliser Moniteur Mesa afin d'implémenter le mecanisme de threadpool et on a amélioré le mécanise implémenter durant la phase 1 pour le producerconsumerbuffer pour traiter le cas du taille maximale .

## Implémentation

Nous avons commencer par amélioré la classe producerconsumerbuffer pour traitter le cas si on veut ajouter dans le tampon et qu'il est plein les threads ne doivent pas attendre.

On a poursuit d'implémenté le mécanisme de threadpool qui va géré un nombre de thread fixe pour protéger le serveur des effet néfaste si il est saturé. Le thread pool gére aussi le recyclage des thread une fois il est en etat de waiting.On a pu géré correctement la destruction des thread en utilisant la méthode requestInterruption.

On a ajouter aussi au niveau de la classe producerconsumerbuffer la fonction tryPut(T item),cette fonction teste si le tampon est plein ou non,si il ya encore de la place elle va ajouter dans le tampon sans soucis et fini par retourner true sinon elle retourne false et rejete le request.

enfin, on a adaptez le fonctionnement du code de traitement du requêtes entrantes au niveau du thread principale dans le fichier fileserver.cpp en utilisant tryPut au lieu de put. 


