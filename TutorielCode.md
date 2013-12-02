README Arduino Control Program 
==============================

Liste des commandes disponibles 
-------

Les commandes actuellement disponibles, ainsi que leur syntaxe, sont les suivantes : 

* __add__ &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&lt;sensorName> &lt;pinNumber> &lt;refreshDataFrequency>
* __del__ &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&lt;sensorName> | &lt;pinNumber>
* __changeFreq__ &lt;sensorName> &lt;newFrequency>
* __getSensors__

Pour exécuter une commande sur la plate-forme Arduino, il faut pour le moment se rendre dans le code, par le cheminement suivant : 

1. Ouvrir le dossier sensorRepository et double cliquer sur le fichier sensorRepository.ino, 
2. cliquer sur la tab &lt;main>, 
3. dans la fonction &lt;void setup()>, taper execCommand("&lt;votreCommande>") pour exécuter une des commandes de la liste fournie ci-dessus.
4. uploader le programme sur une plate-forme Arduino, 
5. ouvrir le moniteur série de votre Arduino en pressant &lt;ctrl+shift+m>.

Il sera très prochainement possible de passer par le moniteur série de la plate-forme Arduino pour exécuter vos commandes. 
Pour cela, il faut suivre le cheminement suivant : 

1. Ouvrir le dossier sensorRepository et double cliquer sur le fichier sensorRepository.ino, 
2. uploader le programme sur une plate-forme Arduino, 
3. ouvrir le moniteur série de votre Arduino en pressant &lt;ctrl+shit+m>,
4. taper une commande (au format de la liste ci-dessus) dans la zone de saisie du moniteur série et cliquer sur "Send".


Ajouter de nouvelles commandes
-------

Pour ajouter de nouvelles commandes utilisables par la plate-forme, il faut se rendre directement dans le code par le cheminement suivant : 

1. Ouvrir le dossier sensorRepository et double cliquer sur le fichier sensorRepository.ino, 
2. cliquer sur la tab &lt;command>, 
3. se rendre dans la fonction &lt;String execCommand(String cmd)>, 
4. se rendre au commentaire "// Check command to execute" et se rendre à la dernière condition "else if ....", 
5. ajouter une nouvelle condition "else if" en dessous de l'actuelle dernière, au format suivant : &lt;else if (command.equald("NOUVELLE_COMMANDE"))>,
6. utiliser les fonctions &lt;nextToken()> pour récupérer la prochaine chaine de caractère ou la fonction &lt;nextTokenInt() pour récupèrer la prochaine valeur entière.

Les fonctions &lt;nextToken()> et &lt;nextTokenInt()> se trouvent également dans la tab &lt;command>.

