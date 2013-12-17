README : Client Java synchrone
=========

Structure du programme
-------

Le programme est divisé en 10 classes principales (11 en comptant la classe de gestion des exceptions) : 
* __ArduinoInterface.java :__ Cette classe se charge d'ouvrir le port de communication entre l'Arduino et le client Java, d'envoyer des lignes de commandes ou des fichiers de commandes à l'Arduino, et d'afficher les informations et les données qu'envoie l'Arduino. 
* __MicroController.java :__ Cette reprèsente un micro-contrôleur dans son ensemble. Elle permet de créer une configuration, une interface, un repository et un historique de ses données et de ses capteurs. C'est la classe principale à créer dans le main. 
* __MicroControllerConfig.java :__ La classe _MicroControllerConfig.java_ permet d'enregistrer la configuration précédente du micro-contrôleur et de recharger cette configuration après un redémarrage de ce dernier. Cette classe permet d'ajouter ou de supprimer des capteurs.
* __SensorData.java :__ Cette classe stock les informations envoyées par un capteur depuis le micro-contrôleur. Ces informations sont au format : &lt;NOM_CAPTEUR> &lt;VALEUR> &lt;TEMPS>. Le temps est en millisecondes.
* __SensorDataRepository :__ Il s'agit de la "base de données" de nos capteurs. Ils sont stockés dans un dictionnaire au format &lt;clé : NOM_CAPTEUR> &lt;valeur : SENSOR_DATA>. 
* __SensorDescriptor.java :__ Cette classe continet la description d'un capteur, à savoir son nom, le pin où il est branché et sa fréquence d'envoie des données. Cette classe permet l'exécution de commandes comme add ou delete.
* __SensorHistory.java :__ Cette classe créée l'historique des données de chaque capteurs dans le temps. Chaque capteur possède son propre fichier d'historique de données dédié. Une méthode est également disponiblep our consulter à chaque instant l'historique général d'un capteur.
* __Main.java :__ Il s'agit de la classe exécutant le client Java. Il y a, en argument du programme, le nom du port utilisé par l'Arduino (ici le port COM3). 

Arborescence du dossier
--------
Le dossier contient : 

1. les sources du programmes, situées dans le package _"serial"_,
2. un dossier _"ControllerData"_, contenant un dossier portant le nom du port où le capteur est branché,
3. ce dossier contient deux autres dossiers : un dossier _"History"_, contenant un fichier d'historique des valeurs des capteurs (un fichier par capteur branché), et un dossier _"MicroControllerConfig"_, contenant le fichier de configuration du micro-contrôleur.
4. Un dernier dossier _"lib"_, contenant les .jar des librairies utilisées pour le développement du client Java.

Ci-joint : [l'arborescence complète](http://img11.hostingpics.net/pics/327079arboCode.jpg "Arborescence")

Format d'enregistrement des fichiers 
--------
Les fichiers enregistrent différement les données qu'ils reçoivent. Vous trouverez ci-après le format de sauvegarde de chacun d'eux. 

#####Dossier _"History"_ 
Chaque capteur qui renvoie des données crée un fichier portant son nom. Les données sont stockées au format texte (pour le moment), sous la forme : &lt;SENSOR_NAME> &lt;SENSOR_VALUE> &lt;RECEIVED_DATA_DATE>

#####Dossier _"MicroControllerConfig"_ 
La configuration est enregistré dans un fichier _"config.txt"_, où les données sont stockées sous la forme suivante : &lt;SENSOR_NAME> &lt;PIN_NUMBER> &lt;SENSOR_FREQUENCY>

Exécution du programme 
--------
_Attention : Avant toute chose il faut penser à brancher votre micro-contrôleur à votre PC._

L'ensemble du code source est disponible au chemin ArduinoSensorServer/JavaSyncClient/_JavaSyncClientSRC  
Il faut copier l'ensemble du répertoire dans votre IDE préféré (les exemples seront réalisés avec Eclipse Juno et Indigo) : 

1. Ouvrir la classe _Main.java_, qui contient le lancement du programme.  
2. Le port série par défaut est le port _"COM4"_. Pour le changer, sous Eclipse, se rendre dans l'onglet _"Run Configurations ..."_ et cliquer sur la table "arguments". Dans la zone _"Program Arguments"_, remplacer _"COM4"_ par le port choisi : [configuration du main](http://img11.hostingpics.net/pics/693801mainConfig.jpg "Configuration du main"). 
3. Cliquer sur "Run" (flèche verte sous Eclipse, ou presser F5) et observer le résultat. 


__Attention !__ Le répertoire _lib_ contient les librairies (.jar) nécessaires au fonctionnement du projet, à savoir la librairie RXTX, qui permet la communication avec le port série. 
Lors de l'exécution du client Java et particulièrement lors de l'envoi des lignes de commandes vers l'Arduino, il est normal que la commande ne s'exécute pas instantanément. 
En effet, le client Java attend la réponse de l'Arduino à la commande avant de continuer à affichier ou à envoyer quoi que ce soit. La communication série n'étant pas instantanée, il est possible qu'il y ai une attente. 

__Remarque :__ Il est important de noter que l'Arduino se reset automatiquement à chaque connexion ou déconnexion du port série. Pour palier à ce problème, un système de sauvegarde de l'ancienne configuration de l'Arduino a été mis en place. 

###Test #1 : Lancer le programme en mode configuration
_Attention : La configuration n'est pas créée par défaut. Pour ce faire, lancez le programme une première fois sans rien modifier pour lui permettre d'exécuter des commandes et de créer le fichier de configuration. Voici à quoi devrait ressembler le fichier de configuration une fois crée :_ [fichier de configuration](http://img11.hostingpics.net/pics/118264config.jpg "Configuration").

Par défaut, le programme ne se lance pas en mode "configuration", qui permet de récupérer tous les capteurs présents lors de la précédente exécution du programme. Pour activer ce mode, il faut suivre la procédure suivante : 

1. Se rendre dans la classe _Main.java_. 
2. Aller à la ligne n°29 (déclaration du micro-contrôleur) et mettre le 3eme paramètre du constructeur à "true" (mode configuration activé) : [Ligne à modifier](http://img11.hostingpics.net/pics/290039lineToModify.jpg "Ligne à modifier"). 
3. Mettre en commentaire les lignes suivantes : [Lignes à commenter](http://img11.hostingpics.net/pics/899463exampleToComment.jpg "Lignes à commenter"). 
4. Lancer le programme.

Dans la console, vous pouvez voir la bonne exécution du programme. Une fois le programme fermé (ou pendant son exécution), l'historique des données reçues peut-être consulté au chemin suivant : 
SerialFinal/ControllerDatas/PORT_COMX/History/NOM_CAPTEUR . 

COMX est remplacé par COM3, COM4, COM5 ... Tout dépendant du numéro de port entré comme paramètre de la classe _Main.java_.

###Test #2 : Lancer le programme sans le mode configuration 

Le programme se lance sans le mode configuration, par défaut. Toutefois, si vous avez suivi l'exemple précédent, il faut de nouveau modifier le 3eme argument du constructeur du micro-contrôleur à la ligne 29 et le mettre à "false".
Il faut également enlever les commentaires des lignes suivants la déclaration du micro-contrôleur. 

Pour ajouter un capteur, il suffit de taper &lt;mc1.getConfig().addSensor("NOM_CAPTEUR", PIN_CAPTEUR, FREQ_CAPTEUR);> . Pour en supprimer un, il faut taper :  &lt;mc1.getConfig().delSensor("NOM_CAPTEUR);>. Cela supprimera le capteur indiqué. 

__Remarque :__ Le fichier de configuration du micro-contrôleur ne retient que les capteurs qui n'ont pas été supprimés pendant l'exécution du programme. Si vous créez une capteur "t3" et que vous le supprimez après, il est normal qu'il n'apparaisse pas dans le fichier de configuration. 



