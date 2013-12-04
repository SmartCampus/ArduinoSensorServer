README Arduino Control Program 
==============================

Description des différents blocs du programme
-------

Le programme de gestion des capteurs est divisé en 4 parties distinctes, traitant chacune une problématique donnée. 
Les 4 parties sont les suivantes : 
* __sensorRepository.ino :__ Contient les données concernant les capteurs, comme leur nom, le numéro de pin où ils sont branchés, leur fréquence d'envoi des données ... Cette partie contient également le tableau de tous les capteurs branchés à l'Arduino ainsi que les méthodes permettant d'ajouter ou de supprimer des capteurs. 
* __command.ino :__ Contient le code de toutes les commandes permettant à un utilisateur d'ajouter, de supprimer, de lister ou de changer la fréquence des capteurs branchés sur la plate-forme Arduino. Cette partie contient également des fonctions de traitement des chaînes de caractéres, nécessaires pour la lecture des commandes sur l'entrée série.
* __sensorUpdateManager.ino :__ : Contient les méthodes de gestion du temps et d'envoie des données des capteurs. 
* __main.ino :__ Contient la boucle de traitement principale, qui envoie les informations des capteurs sur la sortie série en fonction de leurs fréquences de rafraichissement. 


Liste des commandes disponibles 
-------

Les commandes actuellement disponibles, ainsi que leur syntaxe, sont les suivantes : 

* __add__ &lt;sensorName> &lt;pinNumber> &lt;refreshDataFrequency>
* __del__ &nbsp;&lt;sensorName> 
* __freq__ &lt;sensorName> &lt;newFrequency>
* __list__
* __timestamp__
* __resetsensors__

Description des paramètres 
--------
* __sensorName :__ &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Le nom du capteur. 
* __pinNumber :__ &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Le numéro du pin où est branché le capteur.
* __refreshDataFrequency :__ La fréquence d'envoi des données du capteur vers l'Arduino.
* __newFrequency :__ &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;La nouvelle fréquence d'envoi des données du capteur.


Description des commandes 
--------

* __add :__ Ajoute un nouveau capteur à une plate-forme Arduino connecter à un ordinateur et ainsi de récupérer ses données. 
* __del :__ Supprime un capteur déjà branché sur une plate-forme Arduino. 
* __freq :__ Change la fréquence d'envoi des données d'un capteurs existant et branché sur une plate-forme Arduino.
* __list :__ Récupère la liste de tous les capteurs branchés à la plate-forme Arduino et la transmet à l'utilisateur au format : &lt;nomCapteur> &lt;pinNumber> &lt;refreshDataFrequency>.
* __timestamp :__ Affiche depuis combien de temps (en secondes) tourne le programme sur l'Arduino. 
* __resetsensors :__ Efface toute la table contenant les capteurs de la plate-forme Arduin.o

Attention, il n'est possible que de récupérer les données envoyées par des capteurs analogiques. Les capteurs digitaux ne sont pas pris en compte pour le moment.

Pour exécuter une commande sur la plate-forme Arduino, il faut pour le moment se rendre dans le code, par le cheminement suivant : 

1. Ouvrir le dossier sensorRepository et double clicker sur le fichier sensorRepository.ino, 
2. cliquer sur la tab &lt;main>, 
3. dans la fonction &lt;void setup()>, taper &lt;execCommand("NOUVELLECOMMANDE")> pour exécuter une des commandes de la liste fournie ci-dessus.
4. uploader le programme sur une plate-forme Arduino, 
5. ouvrir le moniteur série de l'Arduino afin de visualiser les données et modifications reçues en pressant &lt;ctrl+shift+m>.

Il est également possible de passer par le moniteur série de la plate-forme Arduino pour exécuter vos commandes. 
Pour cela, il faut suivre le cheminement suivant : 

1. Ouvrir le dossier sensorRepository et double cliquer sur le fichier sensorRepository.ino, 
2. uploader le programme sur une plate-forme Arduino, 
3. ouvrir le moniteur série de l'Arduino en pressant &lt;ctrl+shit+m>,
4. taper une commande (au format de la liste ci-dessus) dans la zone de saisie du moniteur série et cliker sur Send".

Attention à ne pas taper les commandes trop vite sur le moniteur de série ni à les envoyer trop rapidement, il semblerait qu'il ne soit pas capable de les lire correctement. 

Ajouter de nouvelles commandes
-------

Pour ajouter de nouvelles commandes utilisables par la plate-forme, il faut se rendre directement dans le code par le cheminement suivant : 

1. Ouvrir le dossier sensorRepository et double clicker sur le fichier sensorRepository.ino, 
2. cliquer sur la tab &lt;command>, 
3. se rendre dans la fonction &lt;String execCommand(String cmd)>, 
4. se rendre au commentaire "// Check command to execute" et se rendre à la dernière condition "else if ....", 
5. ajouter une nouvelle condition "else if" en dessous de l'actuelle dernière, au format suivant : &lt;else if (command.equals("NOUVELLECOMMANDE"))>,
6. scroller en bas du programme et écrire une nouvelle fonction, qui contiendra la commande, au format suivant : &lt;boolean macommandeCommand>() et ajouter le code nécessaire au fonctionnement de la commande. La fonction doit retourner un booleen, pour savoir si la commande a bien été exécutée ou non. 
7. Pour récupérer les String dans l'entrée série, utiliser la fonction &lt;nextToken>. Pour récupérer une valeur entière, utiliser la fonction &lt;nextTokenInt()>. 
8. Enfin, à l'endroit où se situe le code &lt;else if (command.equals("NOUVELLECOMMANDE"))>, ajouter les tests nécessaires à l'éxécution de la commande. 
9. Si cela est nécessaire, se rendre dans la tab de code correspondante pour créer une nouvelle fonction, à appeler pour l'exécution de la commande (voir exemple dans la fonction &lt;addCommand> où la fonction &lt;addSensor est appellée).

Les fonctions &lt;nextToken()> et &lt;nextTokenInt()> se trouvent également dans la tab &lt;command>.

Tests réalisés 
-------

###Test #1 : Ajout d'un capteur à l'Arduino
_La méthode °1 (passage par le code) ne sera plus détaillée dans les autres tests._

__Méthode °1 (passage direct par le code) :__ 

1. Ouvrir le dossier sensorRepository et double clicker sur le fichier sensorRepository.ino, 
2. cliquer sur le tab &lt;main>, 
3. dans la fonction &lt;void setup()>, taper &lt;execCommand(add &lt;sensorName> &lt;pinNumber> &lt;refreshDataFrequency> avec les valeurs entre chevrons à remplacer par les valeurs de votre choix. 
4. uploader le programme sur la plate-forme Arduino, 
5. ouvrir le moniteur série de l'Arduino afin de visualiser les données et modification reçues en pressant &lt;ctrl+shift+m>.

__Méthode °2 (saisie de la commande sur le moniteur série) :__ 

1. Ouvrir le dossier sensorRepository et double clicker sur le fichier sensorRepository.ino, 
2. uploader le programme sur la plate-forme Arduino, 
3. ouvrir le moniteur série de l'Arduino en pressant &lt;ctrl+shift+m>,
4. taper la commande add (au format indiqué ci-dessus) avec les paramètres de votre choix dans la zone de saisie du moniteur et clicker sur "Send".

Attention à indiquer le bon pin de branchement du capteur, sinon la plate-forme renverra des valeurs erronées.
Un capteur a été préalablement ajouté pour les besoins de la démonstration. Vous pouvez bien évidemment en ajouter d'autres.

__Codes de retour :__ 
1. Command OK si la commande est valide.
2. Invalid parameters si la commande est bien lue mais n'a pas les paramètres correspondants où si ils n'existent pas. 
3. Invalid command, si la commande est erronée.

###Test #2 : Suppression d'un capteur existant de l'Arduino 

1. En passant par le moniteur série, utiliser la méthode précédente pour ajouter un nouveau capteur à l'Arduino. 
2. Utiliser la commande del (au format indiqué plus haut) pour supprimer le capteur de votre choix (son nom en paramètre) et clicker sur "Send". 

__Codes de retour :__
* Command OK si la commande est valide.
* Invalid parameters si la commande est bien lue mais n'a pas les paramètres correspondants où si ils n'existent pas. 
* Invalid command, si la commande est erronée.

###Test #3 : Utilisant de la commande freq pour changer la fréquence de rafraichissement des capteurs

1. En passant par le moniteur série, utiliser la méthode précédente pour ajouter un nouveau capteur, ou se baser sur le capteur déjà présent. 
2. Utiliser la commande freq (avec le nom du capteur de votre choix et sa nouvelle fréquence en secondes) pour changer la fréquence du capteur.

__Codes de retour :__
* Command OK si la commande est valide.
* Invalid parameters si la commande est bien lue mais n'a pas les paramètres correspondants où si ils n'existent pas.
* Invalid command, si la commande est erronée.

###Test #4 : Utilisation de la commande list pour visualiser les capteurs

1. En passant par le moniteur série, utiliser la commande list (sans paramètre) pour imprimer sur la sortie série le nom des capteurs actuels, le pin où ils sont branchés et leur fréquence de rafraichissement. 
2. Ajouter, supprimer, changer la fréquence des capteurs, puis utiliser la commande list pour visualiser le bon déroulement des commandes. 

__Codes de retour :__
* Command OK si la commande est valide.
* Invalid command, si la commande est erronée.
* Tous les capteurs présents dans le tableau et les informations les concernants. 

###Test #5 : Utilisation de la commande resetsensors pour effacer les capteurs

1. En passant par le moniteur série, utiliser la commande add (avec les paramètres de votre choix, au format indiqué précédemment) pour ajouter des capteurs. 
2. Utiliser la commande list pour vérifier le bon ajout des capteurs. 
3. Utiliser la commande resetsensors pour supprimer tous les capteurs présents sur la plate-forme. 
4. Utiliser la commande list pour vérifier la bonne suppression des capteus. 

__Codes de retour :__
* Command OK si la commande est valide.
* Invalid command, si la commande est erronée.

###Test #6 : Utilisation de la commande timestamp pour obtenir le temps

1. En passant par le moniteur série, utiliser la commande timestamp (sans paramètre) pour affichier le temps depuis lequel le programme tourne sur la plate-forme Arduino. 

__Codes de retour :__
* Le temps (en seconde) depuis lequel le programme tourne sur la plate-forme Arduino.
* Command OK si la commande est valide.
* Invalid command, si la commande est erronée.
