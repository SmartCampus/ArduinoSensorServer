README : Client Java synchrone
=========

Structure du programme
------

Le programme est divisé en 4 classes : 
* __ArduinoInterface.java :__ Cette classe se charge d'ouvrir le port de communication entre l'Arduino et le client Java, d'envoyer des lignes de commandes ou des fichiers de commandes à l'Arduino, et d'afficher les informations et les données qu'envoie l'Arduino. 
* __DataReceiver.java :__ La classe DataReceiver.java permet d'écrire toutes les données des capteurs renvoyées par l'Arduino dans un fichier json. Chaque données est accompagnée de sa date d'écriture dans le fichier. 
* __InformationReceiver.java :__ De la même manière que la classe précédente, la classe InformationReceiver.java permet d'enregistrer les informations reçues de la plate-forme Arduino (_rappel : au format "I: &lt;message>"_) dans un journal de log.
* __Main.java :__ Il s'agit de la classe exécutant le client Java. Il y a, en argument du programme, le nom du port utilisé par l'Arduino (ici le port COM3). 

Attention toutefois, certains problèmes subsistent encore. En effet, il existe un certain délai de communication entre un ordinateur et une plate-forme Arduino. De même, le temps de traitement de certaines données dépend grandement de la vitesse de traitement du processur. 
La méthode "execCommand" de la classe ArduinoInterface.java contient un &lt;Thread.sleep(1500)>, qui est, pour le moment, obligatoire. 
Il est possible que la valeur 1500 ne soit pas suffisante pour votre ordinateur. Dans ce cas, n'hésitez pas à l'augmenter. 

Exécution du programme 
-------

L'ensemble du code source est disponible au chemin ArduinoSensorServer/JavaAsyncClient/_AsyncClientSrc. 
Il faut copier l'ensemble du répertoire dans votre IDE préféré (les exemples seront réalisés avec Eclipse Juno et Indigo). 
