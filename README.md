ReTOric-mini
Interface de communication avec Oric Atmos / Oric 1, sauvegarde / lecture des fichiers sur carte SD


Cette interface permet de lire des programmes au format TAP contenus dans une carte micro SD en utilisant le port cassette
et les fonctions CLOAD"".
L'interface offre également la possibilité de sauvegarder les programmes de l'Oric sur la carte SD, au format TAP en utilisant
simplement la fonction CSAVE"".

Les données transitent par le port cassette comme si on utilisait un magnétophone à cassette.
Les vitesses de transfert sont paramétrables dans le menu "SET". 
Deux vitesses de transfert sont actuellement disponibles :

1 - vitesse rapide classique du port cassette (environ 2400 bits par secondes)
(la vitesse lente de l'Oric n'est pas gérée)

2 - vitesse "F16", procédé inventé par Symoon sur le club CEO (mode lecture uniquement)
qui accélère le débit jusqu'à 1.6 fois la vitesse rapide classique de l'Oric
en réduisant les périodes des bits 0 et 1.
Une option permet d'ajuster au besoin le nombre de bits de stop (de 2 à 9 bits de stop)
nécessaires au chargement correct de certains programmes.

Pour lire un programme présent sur la carte SD, deux méthodes sont disponibles :

1 ère méthode :
utiliser le directory, c'est la méthode la plus simple.

2 ème méthode :
envoyer une commande vers l'interface pour sélectionner le programme que l'on souhaite charger.


Ces méthodes sont les suivantes :

Méthode 1 :

Accès au directory : taper CLOAD"" ou CLOAD"DIR"  (attention cela écrase le prg présent en mémoire !)
Dans le directory il suffit de taper le nom du programme (avec ou sans l'extension .TAP) et valider pour 
le chargement du programme.

Seuls les fichiers de 8 lettres maxi sont affichés.
Il est possible d'utiliser les fonctions ">" pour changer de page

"#", "#|" et "#["

"/" et "/nom du répertoire"

"nom du prg.TAPxx"   (xx est le numéro de la séquence à lire)

Méthode 2 :

Envoyer le nom du programme à charger avec CSAVE"?nom du prg"
Pour cela assurez vous que la mémoire de l'Oric soit vide, sinon le transfert de la commande sera plus long...

Tapez CSAVE"?nom du programme" et validez. 
(la fonction "?" indique à l'interface qu'on demande à charger un programme)

Tapez ensuite CLOAD"" et l'interface va envoyer le programme sur le port cassette.

* Une astuce, vous pouvez utiliser par exemple CSAVE"?nom du prg",A"adr",E"adr+1" si vous voulez
racourcir le temps d'envoi de la commande. (adr peut être une adresse mémoire quelconque)
                  
Pour Sauvegarder un programme présent dans la mémoire de l'Oric :

taper CSAVE"nom du prg" ou CSAVE"nom du prg.ext" (ext étant l'extension de votre choix)
si on ne précise pas d'extension, ".TAP" sera automatiquement ajouté au nom du programme.
Le nom du programme ne doit pas commencer par les caractères suivants 

(ces caractères sont utilisés pour les commandes) : "?", "#", ">", "+", "%" et "/"

Si le fichier extiste déjà sur la carte SD vous devrez confirmer le remplacement
en appuyant plus de 3 secondes sur le bouton en haut à droite de l'interafece.

Les commandes disponibles sont les suivantes :

"+" : Ajouter le programme sauvegardé à un fichier existant : CSAVE"+nom du prg"

"?" Sélection d'un fichier à lire : CSAVE"?nom du prg" puis CLOAD""

"#|" Effacer un fichier : CSAVE"#|nom du prg" (l'extension est obligatoire)

"#[" Créer un répertoire : CSAVE"#[nom du répertoire" (le répertoire sera créé dans le répertoire actuel)

"#" Demande d'info sur un fichier TAP : CSAVE"#nom du prg.TAP" (affiche les séquences ainsi que leur tailles en octets)
(l'extension est obligatoire)

"/nom du répertoire" Changement de répertoire : CSAVE"/nom du repertoire"   (utiliser "/" pour revenir au répertoire racine)

Il est possible de lire un fichier contenant plusieurs séquences :

Pour cela ouvrez le fichier suivant la méthode 1 ou 2, si il contient plusieurs séquences l'interface va lire la première
séquence et se mettra en PAUSE.

Si vous n'avez pas quitté la pause vous pouvez lire les séquences suivantes en tapant simplement CLOAD""

la séquence suivante sera chargée dans la mémoire de l'Oric.

Il est possible de choisir la séquence à lire en tapant CLOAD"nom du prg.TAPxx"
"xx" étant le numéro de la séquence entre 1 et 20.

Menu Configuration (SET) :

Pour modifier la configuration de l'interface vous pouvez accéder au menu de configuration
en tapant simplement CLOAD"SET"

L'interface va charger le programme de configuration dans la mémoire de l'Oric (attention cela écrase le prg présent !)
Il est possible de choisir la compatibilité Oric 1 (si vous utilisez un Oric 1 seul ce mode est compatible) ou Atmos,
la vitesse de transfert, les bits de stop en vitesse F16 (certains jeux ne se chargent qu'avec 9 bits de stop),
la langue (Français / Anglais) et le niveau du haut parleur de l'Oric.

Les options de Wifi et Bluetooth ne sont pas encore disponibles.

Il est également possible de sélectionner ces paramètres à l'aide du bouton en haut à droite de l'interface.

(appuy court : Niveau du son, appuy plus long : Compatibilité, appuy plus de 5 secondes : Langue)
Le bouton du bas permet de redémarrer l'interface (ne pas utiliser si l'interface est en train d'écrire sur la carte SD !)

Il est fortement recommandé de ne pas sortir ou insérer la carte SD quand l'interface est sous tension.

Ne pas débrancher l'alimentation USB-C si l'intrface est en cours d'écriture ou de réception d'un programme.

De même certaines actions sur les fichiers de la carte avec un oridinateur peuvent rendre illisible la carte par l'interface.

Copiez de préférence vos fichiers importants sur un autre support, le mode SPI de l'esp32 peut être capricieux par moments...

Lors du démarrage de l'interface attendez la fin de l'initialisation avant d'utiliser CLOAD ou CSAVE sur l'Oric.
En cours de lecture si vous souhaitez arrêter le transfert il suffit de faire un appuy court sur le bouton en haut à droite.
Il peut arriver que l'ordre de chargement du directory soit perturbé par certaines actions précédentes, dans ce cas si vous 
tapez CLOAD"DIR" l'Oric chargera bien le directory et non les fichiers annexes qui pourraient se présenter en premier.

N'hésitez pas à me poser des questions si nécessaire, je vais mettre en ligne le firmware dès que j'aurai validé les tests du PCB.
