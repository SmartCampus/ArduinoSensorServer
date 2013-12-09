README : Client Java
=====

Description du client 
------

Le client est en communication avec la plate-forme Arduino Uno connectée à l'ordinateur. Il peut envoyer des fichiers de commandes qui seront exécutés par l'Arduino, puis récupérer les données résultantes. 
Le client se charge également de convertir les données envoyées par l'Arduino au format JSON, compréhensible par le collecteur de données. 
Le client est composé d'une seule classe, qui peut-être découpée en 3, mais cela ne change rien pour cette version : 

* __SerialInterface.java :__ Lis la sortie du port série pour recevoir les données de l'Arduino. Possède une méthode de lecture sur le port série, et deux méthode d'écriture. La première permet d'écrire un simple String sur le port série, et la seconde permet de lire le contenu d'un fichier, découpé ligne par ligne. 


Utilisation du client
------
_Note : Le client est en version java 1.7 ._

Pour utiliser le client, il faut ouvrir SerialInterface.java dans Eclipse ou tout autre IDE Java (NetBeans...). La méthode pour utiliser le client avec javac via l'invite de commandes ne sera pas détaillée ici, et seule une méthode avec l'IDE Eclipse sera détaillée. 
Prochainement, un jar exécutable sera disponible, lorsque le client sera dans une version plus avancée. 

1. Ouvrir le dossier ArduinoSensorServer/JavaClient/_ClientSRC, 
2. se rendre dans le dossier src/ et double clicker sur le fichier SerialInterface.class (ou choisir votre IDE préféré pour l'ouvrir, 
3. se rendre dans la méthode &lt;public static void main(String[] args)> pour éditer le port série (COM3 par défaut, mais si vous avez branché plusieurs Arduino, il se peut que le port soit COM4, COM5, ..., COMX selon l'Arduino utilisé,
4. Une fois le port édité, vous pouvez lancer le programme (F5 sur Eclipse, ou le bouton "Run"), qui se lancera par défaut avec le fichier "command1.txt" en paramètre. 
5. Pour remplacer le fichier de commande, se rendre, toujours dans le main, à la ligne contenant le code &lt;si.sendFile("NOM_FICHIER")> et remplacer le chemin du fichier par celui voulu. 

__Attention :__ Penser à respecter le format de commandes décrit dans ArduinoSensorServer/README.md ou dans ArduinoSensorServer/CodeArduino/README.md . 
