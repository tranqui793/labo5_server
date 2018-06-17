# Laboratoire 5 : Serveur - Phase 2

Auteurs : Oussama Lagha et Adam Zouari  
Date : 15 Juin 2018

##But du laboratoire

Dans cette troisième et dernière partie du laboratoire Serveur, le but est d'améliorerla capacité a monter en charge du serveur. Pour cela, nous avons implementer un mecanisme de cache qui mémorise les réponses des requêtes récentes et qui permet donc de répondre plus vite.

## Choix du mécanisme

Durant cette phase du laboratoire, nous avons fait le choix d'utiliser un moniteur de Hoare afin d'implémenter le mecanisme de lecteur-redacteur et on a adapté le mecanisme implémenté durant les phases précédentes afin d'y intégrer la gestion de la cache.

## Implémentation

On a commencé par implémenter la ReadWritelock qui permet de gérer l'acces a la cache avec priorité lecture si la lecture est en cours.

Ensuite, on a compléter la fonction run de la classe interne InvalidationTimer qui permet de verifier périodiquement (selon `invalidationdelaysec`) si la données et toujours supposée correcte (selon `staledelaysec`). Après on a poursuivi avec la classe ReadWritercache qui a deux fonctions nécessaire tryGetReponse et putResponse, la première nous permet de récupérer la réponse dans le cache si elle s'y trouve, et la deuxième de l'ajouter sinon.


adapter code dispatcherthread:

Afin d'adapter la partie requestdispatcherthread, on avait instancié un thread readwritecache et on le passe au paramétre du chaque thread requestHandler.

adapter code requesthandler:


On avait choisi dés la premiére partie d'omplémenter le request handler comme un thread donc, pour cette partie on avait juste besoin d'ajouter le code donner dans la donnée et le modifier pour qu'il soit soit conforme avec notre implémentation.on a remplacer ce bout de code
```
resp = RequestHandler(req, hasDebugLog).handle();
cache->putResponse(resp);```
par 
```
resp = this->handle();
cache->putResponse(resp);  
```


# Reponses aux questions

 Le cache améliore-t-il la performance et dans quels cas ?

 Y-a-t-il des schémas d’utilisation qui pourraient être problématiques avec votre implémentation ? Si oui, commentez lesquels et quelles seraient les mesures à prendre pour y palier.



