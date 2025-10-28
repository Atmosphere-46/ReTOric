ReTOric
Interface de communication avec Oric Atmos / Oric 1, sauvegarde / lecture des fichiers sur carte SD.
Une version mini de ReTOric est aussi disponible, plus compacte, elle dispose des mêmes fonctions mais sans le joystick.

Cette interface permet de lire des programmes au format TAP contenus dans une carte micro SD en utilisant le port cassette
et les fonctions CLOAD"".
L'interface offre également la possibilité de sauvegarder les programmes de l'Oric sur la carte SD, au format TAP en utilisant
simplement la fonction CSAVE"".

Les données transitent par le port cassette comme si on utilisait un magnétophone à cassette.
Les vitesses de transfert sont paramétrables dans le menu "SET". 
Deux vitesses de transfert sont actuellement disponibles :

1 - vitesse rapide classique du port cassette (environ 2400 bits par secondes)
(la vitesse lente de l'Oric n'est pas gérée)

2 - vitesse "F16", procédé inventé par Symoon membre du club CEO (mode lecture uniquement)
qui accélère le débit jusqu'à 1.6 fois la vitesse rapide classique de l'Oric
en réduisant les périodes des bits 0 et 1.
Une option permet d'ajuster au besoin le nombre de bits de stop (de 2 à 9 bits de stop)
nécessaires au chargement correct de certains programmes.

Pour lire un programme présent sur la carte SD, quatre méthodes sont disponibles :

1 ère méthode :
On utilise le directory, c'est la méthode la plus simple.

2 ème méthode :
On envoye une commande vers l'interface pour sélectionner le programme que l'on souhaite charger.

3 ème méthode :
On entre simplement le nom du fichier à charger dans la commande CLOAD en ajoutant le caractère ":"
pour indiquer que le fichier se trouve sur la carte SD, l'Oric cherche le fichier et le charge en mémoire.

4 ème méthode :
On sélectionne sur l'écran Oled le programme à charger à l'aide du joystick, et on tape CLOAD"" sur l'Oric.

Comment ça marche ?

Méthode 1 :

Accès au directory : taper CLOAD"" ou CLOAD"DIR"  (attention cela écrase le prg présent en mémoire !)
Pour charger un programme il suffit de taper le nom du programme (avec ou sans l'extension .TAP) et valider.

Seuls les fichiers de 8 lettres maxi sont affichés.

On peut utiliser les fonctions siovantes :

">" pour changer de page

"#", "#|" et "#[" (voir descroption plus bas) #J ou #JA (sélection mode joystick)

"/" et "/nom du répertoire" (pour changer de répertoire)

"nom du prg.TAPxx"   (xx est le numéro de la séquence à lire) pour lire la séquence choisie

Méthode 2 :

On envooie en premier le nom du programme à charger avec la commande "?" : exemple CSAVE"?nom du prg"

Pour cela il est préférable de s'assurer que la mémoire de l'Oric soit vide, sinon le transfert de la commande sera plus long...

Astuce : on peut utiliser la syntaxe CSAVE "commande",A500,E501 ce qui a pour effet d'envoyer la commande et seulement 2 octets

On tape CSAVE"?nom du programme" et on valide. 

(la fonction "?" indique à l'interface qu'on demande à charger un programme)

On tape ensuite CLOAD"" et l'interface va envoyer le programme sur le port cassette.

* Une astuce, vous pouvez utiliser par exemple CSAVE"?nom du prg",A"adr",E"adr+1" si vous voulez
racourcir le temps d'envoi de la commande. (adr peut être une adresse mémoire quelconque)
                  
Pour Sauvegarder un programme présent dans la mémoire de l'Oric :

taper CSAVE"nom du prg" ou CSAVE"nom du prg.ext" (ext étant l'extension de votre choix)

si on ne précise pas d'extension, ".TAP" sera automatiquement ajouté au nom du programme.

Le nom du programme doit comporter 8 lettres au maximum et ne doit pas commencer par les caractères suivants 
(ces caractères sont utilisés pour les commandes) : "?", "#", ">", "+", "%" et "/"

Si le nom du programme dépasse les 8 caractères, seuls les 8 premiers seront conservés pour le nom du fichier,
les suivants seront conservés dans le nom du programme comme si on utilisait une cassette (16 caractères maxi).

Si le fichier extiste déjà sur la carte SD vous devrez confirmer le remplacement
en appuyant plus de 3 secondes sur le bouton en haut à droite de l'interafece,
au bout de 30 secondes sans confirmation la sauvergarde est annulée.

Les commandes disponibles sont les suivantes :

"+" : Ajouter le programme sauvegardé à un fichier existant : CSAVE"+nom du prg"

"?" Sélection d'un fichier à lire : CSAVE"?nom du prg" puis CLOAD""

"#|" Effacer un fichier : CSAVE"#|nom du prg" (l'extension est obligatoire)

"#[" Créer un répertoire : CSAVE"#[nom du répertoire" (le répertoire sera créé dans le répertoire actuel)

"#" Demande d'info sur un fichier TAP : CSAVE"#nom du prg.TAP" (affiche les séquences ainsi que leur taille en octets)
(l'extension est obligatoire)

"/nom du répertoire" Changement de répertoire : CSAVE"/nom du repertoire"   (utiliser "/" pour revenir au répertoire racine)

Il est possible de lire un fichier contenant plusieurs séquences :

Pour cela ouvrez le fichier suivant la méthode 1 ou 2, si il contient plusieurs séquences l'interface va lire la première
séquence et se mettra en PAUSE à la fin de la séquence.

Si vous n'avez pas quitté la pause vous pouvez lire les séquences suivantes en tapant simplement CLOAD""

la séquence suivante sera chargée dans la mémoire de l'Oric.

Il est possible de choisir la séquence à lire en tapant CLOAD"nom du prg.TAPxx"
"xx" étant le numéro de la séquence entre 1 et 20.

Méthode 3 :

On tape simplement CLOAD":nom.ext" puis touche Return.
Exemple, CLOAD":PRG.TAP" va chaercher si le programme PRG.TAP existe sur la carte SD et va le charger en mémoire.
L'extension est obligatoire. 
Inconvénient : si le répertoire en cours contient beaucoup de fichiers, cela peut prendre du temps pour trouver le bon
fichier à charger. Le système passe en revue les noms de fichiers du répertoire, il les présente à l'Oric et si le nom
correspond à celui entré dans CLOAD alors le fichier complet sera envoyé à l'Oric.
Attention : sur Oric 1 cette fonction efface le programme actuelement en mémoire même si il s'agit d'un bloc mémoire.

Méthode 4 (pour version avec joystick) :

Dirigez le joystick vers le haut ou vers le bas pour accéder au directory. Sélectionnez le fichier à charger en appuyant sur le
haut du joystick. Il suffit alors de taper CLOAD"" sur l'Oric pour lire le programme.
Dans la liste, si on dirige le joystick vers la droite on obtiens un mini éditeur de code hexadécimal, ce qui permet de voir rapidement 
le contenu du fichier présélectionné (>).

Eemarque : dans les modes 3 et 4 il n'est pas possible de spécifier le numéro de séquence à lire (pour les fichiers contenants plusieurs
séquences). La lecture se fera en séquentiel à partir de la première séquence avec une pause entre chaque séquence (attente CLOAD"" suivant).

Utilisation du joystick :

Pour lire la position du joystick il faut au préalable charger la routine joystick en tapant CLOAD"JOYSTICK"
Ensuite il faut activer le mode joystick. Soit en appuyant sur le bouton (en haut à droite) pendant 1 à 2 secondes
(joystick numérique uniquement), soit en envoyant la commande #J pour le joystick numérique ou #JA pour le joystick analogique

exemple : CSAVE"#JA",A#500,E#501 (cette fonction active le joystick analogique).

Pour lire la position du joystick :

CALL#97AE appelle la routine joystick. L'interface envoie alors un octet contenant la position du joystick. 
On peut lire le résultat avec un PEEK(0)

Pour le joystick numérique les valeurs sont : (Nord, Sud, Est, Ouest)

N : 247  S : 251  O : 253 E : 254
N/O : 252 N/E : 250 S/O : 249 S/E : 245

Pour le joystick analogique :

on a toujours 1 octet mais les axes X et Y sont envoyés une fois sur 2.
Si l'octet reçu est inférieur à 127 alors la donnée correspond à l'axe X.

Si l'octet reçu est supérieur à 127 alors la donnée correspond à l'axe Y

Dans les deux cas (joystick analogique ou numérique), la valeur 127 correspond au bouton tir (bouton en bas à gauche de l'interface)

La valeur 255 correspond au bouton de sélection du joystick (appui sur le champignon).

Pour quitter le mode joystick on peut faire un POKE 768,63 ou appuyer sur le bouton en haut à droite.

Tant que le mode joystick est actif il n'est pas possible de charger ou sauvegarder des programmes.

Menu Configuration (SET) :

Pour modifier la configuration de l'interface vous pouvez accéder au menu de configuration
en tapant simplement CLOAD"SET"

L'interface va charger le programme de configuration dans la mémoire de l'Oric (attention cela écrase le prg présent !)
Il est possible de choisir la compatibilité Oric 1 (si vous utilisez un Oric 1 seul ce mode est compatible) ou Atmos,
la vitesse de transfert, les bits de stop en vitesse F16 (certains jeux ne se chargent qu'avec 9 bits de stop),
la langue (Français / Anglais) et le niveau de volume du haut parleur de l'Oric.
Il est possible de changer l'adresse à laquelle est stocké la lecture du joystick (en page zéro de 0 à 9).

Les options de Wifi et Bluetooth ne sont pas encore disponibles.

Il est également possible de sélectionner ces paramètres à l'aide du bouton en haut à droite de l'interface.

(appuy court : Niveau du son, appuy plus long : Compatibilité, appuy plus de 5 secondes : Langue)
Le bouton du bas permet de redémarrer l'interface (ne pas utiliser si l'interface est en train d'écrire sur la carte SD !)

Il est fortement recommandé de ne pas sortir ou insérer la carte SD quand l'interface est sous tension.

Ne pas débrancher l'alimentation USB-C si l'intrface est en cours d'écriture ou de réception d'un programme.

De même certaines actions sur les fichiers de la carte avec un ordinateur peuvent rendre illisible la carte par l'interface.


Lors du démarrage de l'interface attendez la fin de l'initialisation avant d'utiliser CLOAD ou CSAVE sur l'Oric.
En cours de lecture si vous souhaitez arrêter le transfert il suffit de faire un appuy court sur le bouton en haut à droite.
Il peut arriver que l'ordre de chargement du directory soit perturbé par certaines actions précédentes, dans ce cas si vous 
tapez CLOAD"DIR" l'Oric chargera bien le directory et non les fichiers annexes qui pourraient se présenter en premier.

Je remercie les membres du club CEO qui m'ont aidée à mieux comprendre certaines spécifictés de L'Oric et fournis
de précieuses informations pour l'élaboration des routines assembleur.
