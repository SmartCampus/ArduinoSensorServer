README Arduino Control Program 
==============================

Liste des commandes disponibles 
-------

Les commandes actuellement disponibles, ainsi que leur syntaxe, sont les suivantes : 

* __add__ &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&lt;sensorName> &lt;pinNumber> &lt;refreshDataFrequency>
* __del__ &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&lt;sensorName> | &lt;pinNumber>
* __changeFreq__ &lt;sensorName> &lt;newFrequency>
* __getSensors__

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
* __changeFreq :__ Change la fréquence d'envoi des données d'un capteurs existant et branché sur une plate-forme Arduino.
* __getSensors :__ Récupère la liste de tous les capteurs branchés à la plate-forme Arduino et la transmet à l'utilisateur.

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
6. utiliser les fonctions &lt;nextToken()> pour récupérer la prochaine chaine de caractère ou la fonction &lt;nextTokenInt() pour récupèrer la prochaine valeur entière.

Les fonctions &lt;nextToken()> et &lt;nextTokenInt()> se trouvent également dans la tab &lt;command>.

Tests réalisés 
-------

###Test #1 : Ajout d'un capteur à l'Arduino

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
