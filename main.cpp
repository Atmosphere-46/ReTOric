/*
ReTOric
Interface de communication avec Oric Atmos / Oric 1, sauvegarde / lecture des fichiers sur carte SD
Par Claire Bertrand.

Avertissement : je suis totalement autodidacte et ce code a été réalisé pour le plaisir, garanti non-conforme aux règles de l'art
mais 100% fonctionnel sur ma machine ;-)
Je vous prie donc d'être indulgent (très) sur la manière dont il a été écrit. A l'origine je souhaitais simplement décoder le protocole de communication
de l'Oric car je n'avais pas de documentation sur le sujet. Au fil du temps j'ai ajouté des fonctions de lecture et sauvegarde c'est pourquoi la structure
de base n'est pas idéale. Je n'ai plus le courage de le mettre au propre.
License libre.

Cette interface permet de lire des programmes au format TAP contenus dans une carte micro SD en utilisant le port cassette
et avec les mêmes fonctions CLOAD"" dont disposent les micro ordinateurs Oric 1 et Atmos.
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
        1 ère méthode : utiliser le directory, c'est la méthode la plus simple.
        2 ème méthode : envoyer une commande vers l'interface pour sélectionner le programme que l'on souhaite charger.

Ces méthodes sont les suivantes (d'autres on été ajoutées, voir readme sur GitHub):

        Méthode 1 - Accès au directory : taper CLOAD"" ou CLOAD"DIR"  (attention cela écrase le prg présent en mémoire !)
            Dans le directory il suffit de taper le nom du programme (avec ou sans l'extension .TAP) et valider pour 
            le chargement du programme.
            Seuls les fichiers de 8 lettres maxi sont affichés.
            Il est possible d'utiliser les fonctions ">" pour changer de page
                                                     "#", "#|" et "#["
                                                     "/" et "/nom du répertoire"
                                                     "nom du prg.TAPxx"   (xx est le numéro de la séquence à lire)

        Méthode 2 - Envoyer le nom du programme à charger avec CSAVE"?nom du prg"
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

Il est recommandé de ne pas sortir ou insérer la carte SD quand l'interface est sous tension.
Ne pas débrancher l'alimentation USB-C si l'intrface est en cours d'écriture ou de réception d'un programme.
De même certaines actions sur les fichiers de la carte avec un oridinateur peuvent rendre illisible la carte par l'interface.
Copiez de préférence vos fichiers importants sur un autre support, le mode SPI de l'esp32 peut être capricieux par moments...
Lors du démarrage de l'interface attendez la fin de l'initialisation avant d'utiliser CLOAD ou CSAVE sur l'Oric.
En cours de lecture si vous souhaitez arrêter le transfert il suffit de faire un appuy court sur le bouton en haut à droite.
Il peut arriver que l'ordre de chargement du directory soit perturbé par certaines actions précédentes, dans ce cas si vous 
tapez CLOAD"DIR" l'Oric chargera bien le directory et non les fichiers annexes qui pourraient se présenter en premier.


*/

#include <Arduino.h>
#include <FS.h>
#include <SPI.h>
#include <SD.h>
#include <LittleFS.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <vector>
#include <Preferences.h>
#include <algorithm> // Pour std::sort
// #include <map> // Pour stocker les séquences et leurs occurrences

#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

// #include <PS4Controller.h>
// #include <Bluepad32.h>
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"
#include "esp_err.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DATA_PIN 4        // Réception données
#define SEND_PIN 5        // Sortie données
#define START_PIN 13      // contact Oric
#define bouton 0         // bouton de validation
#define valid 14         // validation Joystick
#define fire 27          // Fire joystick
#define xVal 25            // X joystick
#define yVal 26            // Y joystick
#define PERIOD_LED_PIN 16 // Led Période
#define DATA_LED_PIN 17   // Led Rx et Tx
#define nivSonQ1 32       // Niveau son transistor Q1
#define nivSonQ2 33       // Niveau son transistor Q2
#define BAUD_RATE 115200
#define BUFFER_SIZE 50000 // 55 K octets

#define CS_PIN 15
// #define SD_MMC_CMD 15 // Please do not modify it.
// #define SD_MMC_CLK 14 // Please do not modify it.
// #define SD_MMC_D0 2   // Please do not modify it.

static const unsigned char PROGMEM pageDir[] = // entête de page écran
    {
    0x16,0x16,0x16,0x24,0xff,0xff,0x80,0x00,
    0xbf,0x17,0xbb,0xf8,0xff,0x43,0x41,0x54, // bf 3f = adr de fin (20 lignes de 40 caractères) BB F8 début
    0x41,0x4c,0x2e,0x42,0x49,0x4e,0x00,
};

static const unsigned char PROGMEM notFound[] = // Not Found, permet de terminer CLOAD si le fichier demandé n'a pas été trouvé.
    {
    0x16,0x16,0x16,0x24,0xff,0xff,0x80,0x00,0x02,0x80,0x02,0x7f,0xff,0x21,0x00,0x00,0x00, // "!" $027F = 0
};

static const unsigned char PROGMEM set_vide[] = // entête SET vide
    {
    0x16,0x16,0x16,0x24,0xFF,0xFF,0x00,0xC7,0x05,0x0A,0x05,0x01,0xFF,0x53,0x45,0x54,0x00,0x08,0x05,0x01,0x00,0xB6,0x22,0x00,0x00,0x00,0x00,
};

// static const unsigned char PROGMEM joystick_vide[] = // entête joystick vide (basic)
//     {
//     0x16,0x16,0x16,0x24,0xFF,0xFF,0x00,0xC7,0x05,0x0A,0x05,0x01,0xFF,0x4A,0x4F,0x59,0x53,0x54,0x49,0x43,0x4B,0x00,0x08,0x05,0x01,0x00,0xB6,0x22,0x00,0x00,0x00,0x00,
// };

static const unsigned char PROGMEM joystick_videASM[] = // entête joystick vide (asm) $BFF0
    {
    0x16,0x16,0x16,0x24,0xFF,0xFF,0x80,0xC7,0xBF,0xF7,0xBF,0xF0,0xFF,0x4A,0x4F,0x59,0x53,0x54,0x49,0x43,0x4B,0x00,0x08,0x4C,0x74,0xE8,0x20,0x3D,0xE9,0x3C,
    // 0x16,0x16,0x16,0x24,0xFF,0xFF,0x80,0xC7,0x97,0xF7,0x97,0xF0,0xFF,0x4A,0x41,0x53,0x4D,0x00,0x08,0x4C,0x74,0xE8,0x20,0x3D,0xE9,0x3C,
};

static const unsigned char PROGMEM joystick_videASMOric1[] = // entête joystick vide (asm) $BFF0 version Oric1
    {
    0x16,0x16,0x16,0x24,0xFF,0xFF,0x80,0xC7,0xBF,0xFC,0xBF,0xF0,0xFF,0x4A,0x4F,0x59,0x53,0x54,0x49,0x43,0x4B,0x00,0xA5,0x00,0x85,0x35,0x08,0x4C,0xB6,0xE7,0x20,0x04,0xE8,0x60,0x3C,
    // 0x16,0x16,0x16,0x24,0xFF,0xFF,0x80,0xC7,0x97,0xF7,0x97,0xF0,0xFF,0x4A,0x41,0x53,0x4D,0x00,0x08,0x4C,0x74,0xE8,0x20,0x3D,0xE9,0x3C,
};

// static const unsigned char PROGMEM fichier_cf[] = // fichier de configuration
//     {
//     0x16,0x16,0x16,0x24,0xFF,0xFF,0x80,0x00,0x20,0x32,0x20,0x00,0xFF,0x43,0x46,0x00,
//     0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,
//     0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,
//     0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x00,0x00,0x01,0x01,0x02,0x02,0x00,0x55,0x55,
//     0x55,0x55,0x55,
// };

static const unsigned char PROGMEM headerFile[] = // fichier d'entête pour sélection du fichier à transmettre (basic) CLOAD""
    {
    0x16,0x16,0x16,0x24,0xFF,0xFF,0x00,0xC7,0x05,0x0A,0x05,0x01,0xFF,0x00,0x08,0x05,0x01,0x00,0xB6,0x22,0x00,0x00,0x00,0x00,
};

// static const unsigned char PROGMEM headerFileASM[] = // fichier d'entête pour sélection du fichier à transmettre ASM $BFF0 CLOAD""
//     {
//     0x16,0x16,0x16,0x24,0xFF,0xFF,0x80,0xC7,0xBF,0xFA,0xBF,0xF0,0xFF,0x00,0xA9,0x00,0x8D,0x7F,0x02,0x08,0x4C,0x74,0xE8,0x20,0x3D,0xE9,0x3C,
// };

static const unsigned char PROGMEM headerFileASM[] = // fichier d'entête pour sélection du fichier à transmettre ASM $BFF0 CLOAD""
    {
    0x16,0x16,0x16,0x24,0xFF,0xFF,0x80,0xC7,0xBF,0xFB,0xBF,0xF0,0xFF,0x00,0xA9,0x00,0x8D,0x7F,0x02,0x08,0x4C,0x74,0xE8,0x20,0x3D,0xE9, // 0x3C
};

static const unsigned char PROGMEM headerFileASM_VMAX[] = // fichier d'entête pour sélection du fichier à transmettre ASM $BFF0 CLOAD"" VMAX
    {
    0x16,0x16,0x16,0x24,0xFF,0xFF,0x80,0xC7,0x31,0x35,0x31,0x00,0xFF,0x00,0xA9,0x00,0x8D,0x7F,0x02,0x20,0x10,0x31,0x08,0x4C,0x77,0xE8,0x20,0x3D,0xE9,0x60,
    0x20,0x1A,0xEE,0xA0,0x06,0x78,0xBE,0x28,0x31,0xB9,0x2F,0x31,0x9D,0x00,0x03,0x88,0x10,0xF4,0xA9,0x40,0x8D,0x00,0x03,0x60,0x05,0x04,0x0B,0x02,0x0C,0x08,
    0x0E,0x00,0xD0,0xC0,0xFF,0x10,0xF4,0x7F,
};

static const unsigned char PROGMEM headerFileASMOric1[] = // fichier d'entête pour sélection du fichier à transmettre ASM $BFF0 version Oric1
    {
    0x16,0x16,0x16,0x24,0xFF,0xFF,0x80,0xC7,0xBF,0xFB,0xBF,0xF0,0xFF,0x00,0xA5,0x00,0x85,0x35,0x08,0x4C,0xB6,0xE7,0x20,0x04,0xE8,0x3C,
        // 0x16,0x16,0x16,0x24,0xFF,0xFF,0x80,0xC7,0xBF,0xFB,0xBF,0xF0,0xFF,0x00,0xA9,0x00,0x85,0x35,0x08,0x4C,0xB6,0xE7,0x20,0x04,0xE8,0x3C,

    // 0x16,0x16,0x16,0x24,0xFF,0xFF,0x80,0xC7,0xBF,0xFA,0xBF,0xF0,0xFF,0x00,0xA0,0x00,0x8D,0x7F,0x02,0x08,0x4C,0xB6,0xE7,0x20,0xC4,0xE,0x3C,
};


static const unsigned char PROGMEM set_Oric1[] = // prg config Oric1 FR
    {
        0x16,0x16,0x16,0x24,0x00,0x31,0x00,0xC7,0x0B,0xEF,0x05,0x01,0x50,0x53,0x45,0x54,0x00,0x0F,0x05,0x0A,0x00,0xA1,0x3A,0x94,0x3A,0xB1,0x30,0x3A,0xB2,0x33,0x00,0x2A,0x05,0x1E,
        0x00,0x8D,0x49,0xD4,0x31,0xC3,0x37,0x3A,0x95,0x41,0x3A,0xB9,0x38,0x32,0x33,0x31,0xCC,0x49,0x2C,0x41,0x3A,0x90,0x49,0x00,0x30,0x05,0x32,0x00,0x9D,0x00,0x55,0x05,0x3C,0x00,
        0x42,0xD4,0xE6,0x28,0x23,0x32,0x30,0x32,0x38,0x29,0x3A,0x4D,0xD4,0xE6,0x28,0x23,0x32,0x30,0x32,0x39,0x29,0x3A,0x53,0xD4,0xE6,0x28,0x23,0x32,0x30,0x32,0x41,0x29,0x00,0x6F,
        0x05,0x46,0x00,0x4E,0xD4,0xE6,0x28,0x23,0x32,0x30,0x32,0x42,0x29,0x3A,0x4C,0xD4,0xE6,0x28,0x23,0x32,0x30,0x32,0x43,0x29,0x00,0x89,0x05,0x50,0x00,0x47,0xD4,0xE6,0x28,0x23,
        0x32,0x30,0x32,0x44,0x29,0x3A,0x4A,0xD4,0xE6,0x28,0x23,0x32,0x30,0x32,0x45,0x29,0x00,0xB2,0x05,0xFE,0x01,0x94,0x3A,0xBA,0x22,0x20,0x20,0x20,0x20,0x2D,0x2D,0x20,0x43,0x4F,
        0x4E,0x46,0x49,0x47,0x55,0x52,0x41,0x54,0x49,0x4F,0x4E,0x20,0x52,0x65,0x54,0x4F,0x72,0x69,0x63,0x20,0x2D,0x2D,0x22,0x00,0xD6,0x05,0x03,0x02,0xBA,0x3A,0xBA,0x22,0x31,0x20,
        0x2D,0x57,0x49,0x46,0x49,0x20,0x4E,0x4F,0x4D,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x3A,0x20,0x2D,0x2D,0x2D,0x22,0x00,0xF8,0x05,0x08,0x02,0xBA,0x22,0x32,0x20,
        0x2D,0x57,0x49,0x46,0x49,0x20,0x50,0x41,0x53,0x53,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x3A,0x20,0x2D,0x2D,0x2D,0x22,0x00,0x17,0x06,0x12,0x02,0xBA,0x22,0x33,0x20,
        0x2D,0x57,0x49,0x46,0x49,0x20,0x4F,0x4E,0x2F,0x4F,0x46,0x46,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x3A,0x22,0x3B,0x00,0x30,0x06,0x14,0x02,0x99,0x57,0xD4,0x30,0xC9,0xBA,0x22,
        0x20,0x4F,0x46,0x46,0x22,0xC8,0xBA,0x22,0x20,0x4F,0x4E,0x22,0x20,0x00,0x51,0x06,0x1C,0x02,0xBA,0x3A,0xBA,0x22,0x34,0x20,0x2D,0x42,0x4C,0x55,0x45,0x54,0x4F,0x4F,0x54,0x48,
        0x20,0x4F,0x4E,0x2F,0x4F,0x46,0x46,0x20,0x20,0x3A,0x22,0x3B,0x00,0x6A,0x06,0x1E,0x02,0x99,0x42,0xD4,0x30,0xC9,0xBA,0x22,0x20,0x4F,0x46,0x46,0x22,0xC8,0xBA,0x22,0x20,0x4F,
        0x4E,0x22,0x20,0x00,0x8B,0x06,0x26,0x02,0xBA,0x3A,0xBA,0x22,0x35,0x20,0x2D,0x4F,0x52,0x49,0x43,0x20,0x31,0x2F,0x41,0x54,0x4D,0x4F,0x53,0x20,0x20,0x20,0x20,0x20,0x20,0x3A,
        0x22,0x3B,0x00,0xA9,0x06,0x28,0x02,0x99,0x4D,0xD4,0x30,0xC9,0xBA,0x22,0x20,0x4F,0x52,0x49,0x43,0x20,0x31,0x22,0xC8,0xBA,0x22,0x20,0x41,0x54,0x4D,0x4F,0x53,0x22,0x00,0xCA,
        0x06,0x30,0x02,0xBA,0x3A,0xBA,0x22,0x36,0x20,0x2D,0x56,0x49,0x54,0x45,0x53,0x53,0x45,0x20,0x44,0x45,0x20,0x4C,0x45,0x43,0x54,0x55,0x52,0x45,0x3A,0x22,0x3B,0x00,0xE7,0x06,
        0x32,0x02,0x99,0x53,0xD4,0x30,0xC9,0xBA,0x22,0x20,0x4E,0x4F,0x52,0x4D,0x41,0x4C,0x45,0x22,0xC8,0xBA,0x22,0x20,0x46,0x31,0x36,0x22,0x00,0x11,0x07,0x3A,0x02,0x99,0x53,0xD3,
        0x30,0xC9,0xBA,0x3A,0xBA,0x22,0x37,0x20,0x2D,0x4E,0x62,0x72,0x65,0x20,0x42,0x49,0x54,0x53,0x20,0x44,0x45,0x20,0x53,0x54,0x4F,0x50,0x20,0x3A,0x20,0x22,0x3B,0x3A,0xBA,0x4E,
        0x00,0x1F,0x07,0x3F,0x02,0x99,0x20,0x53,0xD5,0x30,0xC9,0xBA,0x3A,0xBA,0x00,0x46,0x07,0x44,0x02,0xBA,0x3A,0xBA,0x22,0x38,0x20,0x2D,0x4E,0x49,0x56,0x45,0x41,0x55,0x20,0x53,
        0x4F,0x4E,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x3A,0x20,0x22,0x3B,0x3A,0xBA,0x4C,0xCC,0x31,0x00,0x70,0x07,0x49,0x02,0xBA,0x3A,0xBA,0x22,0x39,0x20,0x2D,0x4A,0x4F,0x59,
        0x53,0x54,0x49,0x43,0x4B,0x20,0x41,0x44,0x52,0x20,0x20,0x20,0x20,0x20,0x20,0x3A,0x20,0x23,0x39,0x37,0x41,0x45,0x2F,0x23,0x32,0x46,0x22,0x00,0x91,0x07,0x4E,0x02,0xBA,0x3A,
        0xBA,0x22,0x31,0x30,0x2D,0x4C,0x41,0x4E,0x47,0x55,0x45,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x3A,0x22,0x3B,0x00,0xAA,0x07,0x50,0x02,0x99,0x47,0xD4,
        0x30,0x20,0xC9,0x20,0xBA,0x22,0x20,0x46,0x52,0x22,0xC8,0xBA,0x22,0x20,0x45,0x4E,0x22,0x00,0xCA,0x07,0x53,0x02,0xBA,0x3A,0xBA,0x3A,0xBA,0x22,0x30,0x20,0x2D,0x53,0x41,0x55,
        0x56,0x45,0x52,0x20,0x45,0x54,0x20,0x51,0x55,0x49,0x54,0x54,0x45,0x52,0x22,0x00,0xD9,0x07,0x58,0x02,0x8D,0x49,0xD4,0x31,0xC3,0x33,0x3A,0xBA,0x3A,0x90,0x00,0xEB,0x07,0x62,
        0x02,0xBA,0x3A,0xBA,0x22,0x43,0x48,0x4F,0x49,0x58,0x20,0x3A,0x22,0x3B,0x00,0xF2,0x07,0x6C,0x02,0x92,0x41,0x00,0x03,0x08,0x71,0x02,0x99,0x20,0x41,0xD4,0x30,0x20,0xC9,0x20,
        0x32,0x30,0x30,0x30,0x00,0x18,0x08,0x76,0x02,0x99,0x20,0x41,0xD5,0x34,0x20,0xD2,0x20,0x41,0xD3,0x31,0x30,0xC9,0x20,0x35,0x30,0x00,0x2C,0x08,0x80,0x02,0x99,0x41,0xD4,0x37,
        0x20,0xD1,0x20,0x53,0xD4,0x30,0x20,0xC9,0x20,0x35,0x30,0x00,0x39,0x08,0x83,0x02,0x99,0x41,0xD4,0x34,0xC9,0x36,0x39,0x30,0x00,0x46,0x08,0x85,0x02,0x99,0x41,0xD4,0x35,0xC9,
        0x37,0x30,0x30,0x00,0x53,0x08,0x88,0x02,0x99,0x41,0xD4,0x36,0xC9,0x37,0x35,0x30,0x00,0x60,0x08,0x8A,0x02,0x99,0x41,0xD4,0x37,0xC9,0x38,0x30,0x30,0x00,0x6D,0x08,0x8C,0x02,
        0x99,0x41,0xD4,0x38,0xC9,0x39,0x30,0x30,0x00,0x79,0x08,0x8F,0x02,0x99,0x41,0xD4,0x39,0xC9,0x35,0x30,0x00,0x88,0x08,0x94,0x02,0x99,0x41,0xD4,0x31,0x30,0xC9,0x31,0x30,0x30,
        0x30,0x00,0xA2,0x08,0xB2,0x02,0xBA,0x22,0x20,0x20,0x20,0x2D,0x2D,0x20,0x42,0x4C,0x55,0x45,0x54,0x4F,0x4F,0x54,0x48,0x20,0x2D,0x2D,0x22,0x00,0xBD,0x08,0xB3,0x02,0xBA,0x3A,
        0xBA,0x22,0x30,0x20,0x2D,0x20,0x4F,0x46,0x46,0x22,0x3A,0xBA,0x22,0x31,0x20,0x2D,0x20,0x4F,0x4E,0x22,0x00,0xD2,0x08,0xB4,0x02,0xBA,0x3A,0xBA,0x22,0x43,0x48,0x4F,0x49,0x58,
        0x20,0x3A,0x22,0x3B,0x3A,0x92,0x41,0x00,0xE3,0x08,0xB7,0x02,0x99,0x41,0xD3,0x31,0xD2,0x41,0xD5,0x30,0xC9,0x36,0x39,0x30,0x00,0xF6,0x08,0xB8,0x02,0xB9,0x28,0x23,0x32,0x30,
        0x32,0x38,0x29,0x2C,0x41,0x3A,0x97,0x35,0x30,0x00,0x14,0x09,0xBC,0x02,0xBA,0x22,0x20,0x20,0x20,0x2D,0x2D,0x20,0x43,0x4F,0x4D,0x50,0x41,0x54,0x49,0x42,0x49,0x4C,0x49,0x54,
        0x45,0x20,0x2D,0x2D,0x22,0x00,0x35,0x09,0xC6,0x02,0xBA,0x3A,0xBA,0x22,0x30,0x20,0x2D,0x20,0x4F,0x52,0x49,0x43,0x20,0x31,0x22,0x3A,0xBA,0x22,0x31,0x20,0x2D,0x20,0x41,0x54,
        0x4D,0x4F,0x53,0x22,0x00,0x4A,0x09,0xC8,0x02,0xBA,0x3A,0xBA,0x22,0x43,0x48,0x4F,0x49,0x58,0x20,0x3A,0x22,0x3B,0x3A,0x92,0x41,0x00,0x5B,0x09,0xCB,0x02,0x99,0x41,0xD3,0x31,
        0xD2,0x41,0xD5,0x30,0xC9,0x37,0x30,0x30,0x00,0x6E,0x09,0xD0,0x02,0xB9,0x28,0x23,0x32,0x30,0x32,0x39,0x29,0x2C,0x41,0x3A,0x97,0x35,0x30,0x00,0x91,0x09,0xEE,0x02,0xBA,0x22,
        0x20,0x20,0x20,0x2D,0x2D,0x20,0x56,0x49,0x54,0x45,0x53,0x53,0x45,0x20,0x44,0x45,0x20,0x4C,0x45,0x43,0x54,0x55,0x52,0x45,0x20,0x2D,0x2D,0x22,0x00,0xB8,0x09,0xF8,0x02,0xBA,
        0x3A,0xBA,0x22,0x30,0x20,0x2D,0x20,0x4E,0x4F,0x52,0x4D,0x41,0x4C,0x45,0x22,0x3A,0xBA,0x22,0x31,0x20,0x2D,0x20,0x46,0x31,0x36,0x20,0x28,0x58,0x31,0x2E,0x36,0x29,0x22,0x00,
        0xCD,0x09,0xFD,0x02,0xBA,0x3A,0xBA,0x22,0x43,0x48,0x4F,0x49,0x58,0x20,0x3A,0x22,0x3B,0x3A,0x92,0x41,0x00,0xDE,0x09,0x02,0x03,0x99,0x41,0xD3,0x31,0xD2,0x41,0xD5,0x30,0xC9,
        0x37,0x35,0x30,0x00,0xF1,0x09,0x0C,0x03,0xB9,0x28,0x23,0x32,0x30,0x32,0x41,0x29,0x2C,0x41,0x3A,0x97,0x35,0x30,0x00,0x13,0x0A,0x20,0x03,0xBA,0x22,0x20,0x20,0x20,0x2D,0x2D,
        0x20,0x4E,0x62,0x72,0x65,0x20,0x62,0x69,0x74,0x73,0x20,0x64,0x65,0x20,0x53,0x54,0x4F,0x50,0x20,0x2D,0x2D,0x22,0x00,0x2E,0x0A,0x2A,0x03,0xBA,0x3A,0xBA,0x22,0x45,0x4E,0x54,
        0x52,0x45,0x20,0x32,0x20,0x45,0x54,0x20,0x39,0x20,0x22,0x3B,0x3A,0x92,0x41,0x00,0x3F,0x0A,0x34,0x03,0x99,0x41,0xD5,0x32,0xD2,0x41,0xD3,0x39,0xC9,0x38,0x30,0x30,0x00,0x52,
        0x0A,0x3E,0x03,0xB9,0x28,0x23,0x32,0x30,0x32,0x42,0x29,0x2C,0x41,0x3A,0x97,0x35,0x30,0x00,0x71,0x0A,0x84,0x03,0xBA,0x22,0x20,0x20,0x20,0x2D,0x2D,0x20,0x4E,0x49,0x56,0x45,
        0x41,0x55,0x20,0x44,0x55,0x20,0x53,0x4F,0x4E,0x20,0x2D,0x2D,0x22,0x20,0x00,0x8C,0x0A,0x8E,0x03,0xBA,0x3A,0xBA,0x22,0x45,0x4E,0x54,0x52,0x45,0x20,0x31,0x20,0x45,0x54,0x20,
        0x33,0x20,0x22,0x3B,0x3A,0x92,0x41,0x00,0x9D,0x0A,0x98,0x03,0x99,0x41,0xD5,0x31,0xD2,0x41,0xD3,0x33,0xC9,0x39,0x30,0x30,0x00,0xB6,0x0A,0xA2,0x03,0x41,0xD4,0x41,0xCD,0x31,
        0x3A,0xB9,0x28,0x23,0x32,0x30,0x32,0x43,0x29,0x2C,0x41,0x3A,0x97,0x35,0x30,0x00,0xE3,0x0A,0xB6,0x03,0xBA,0x3A,0xBA,0x22,0x20,0x20,0x2D,0x2D,0x20,0x41,0x44,0x52,0x45,0x53,
        0x53,0x45,0x20,0x4C,0x45,0x43,0x54,0x55,0x52,0x45,0x20,0x44,0x55,0x20,0x4A,0x4F,0x59,0x53,0x54,0x49,0x43,0x4B,0x20,0x2D,0x2D,0x22,0x00,0x08,0x0B,0xC0,0x03,0xBA,0x3A,0xBA,
        0x22,0x41,0x44,0x52,0x45,0x53,0x53,0x45,0x20,0x28,0x45,0x4E,0x54,0x52,0x45,0x20,0x30,0x20,0x45,0x54,0x20,0x39,0x29,0x3A,0x22,0x3B,0x3A,0x92,0x41,0x00,0x19,0x0B,0xC5,0x03,
        0x99,0x41,0xD5,0x30,0xD2,0x41,0xD3,0x39,0xC9,0x39,0x35,0x30,0x00,0x2C,0x0B,0xCA,0x03,0xB9,0x28,0x23,0x32,0x30,0x32,0x45,0x29,0x2C,0x41,0x3A,0x97,0x35,0x30,0x00,0x45,0x0B,
        0xE8,0x03,0xBA,0x3A,0xBA,0x22,0x20,0x20,0x20,0x2D,0x2D,0x20,0x4C,0x41,0x4E,0x47,0x55,0x45,0x20,0x2D,0x2D,0x22,0x00,0x6A,0x0B,0xF2,0x03,0xBA,0x3A,0xBA,0x22,0x30,0x20,0x2D,
        0x20,0x46,0x52,0x41,0x4E,0x43,0x41,0x49,0x53,0x22,0x3A,0xBA,0x22,0x31,0x20,0x2D,0x20,0x41,0x4E,0x47,0x4C,0x41,0x49,0x53,0x22,0x00,0x7F,0x0B,0xF7,0x03,0xBA,0x3A,0xBA,0x22,
        0x43,0x48,0x4F,0x49,0x58,0x20,0x3A,0x22,0x3B,0x3A,0x92,0x41,0x00,0x91,0x0B,0xFC,0x03,0x99,0x41,0xD5,0x30,0xD2,0x41,0xD3,0x31,0xC9,0x31,0x30,0x30,0x30,0x00,0xBF,0x0B,0x06,
        0x04,0xB9,0x28,0x23,0x32,0x30,0x32,0x44,0x29,0x2C,0x41,0x3A,0xB7,0x22,0x25,0x22,0x2C,0x41,0x23,0x32,0x30,0x30,0x30,0x2C,0x45,0x23,0x32,0x30,0x33,0x32,0x3A,0xB5,0x31,0x30,
        0x30,0x3A,0xB6,0x22,0x53,0x45,0x54,0x22,0x00,0xDA,0x0B,0xD0,0x07,0xB7,0x22,0x25,0x22,0x2C,0x41,0x23,0x32,0x30,0x30,0x30,0x2C,0x45,0x23,0x32,0x30,0x33,0x32,0x3A,0x94,0x3A,
        0xC1,0x00,0xED,0x0B,0xB8,0x0B,0x91,0x30,0x2C,0x31,0x2C,0x31,0x2C,0x32,0x2C,0x30,0x2C,0x30,0x2C,0x30,0x00,0x00,0x00,0x49,

};

static const unsigned char PROGMEM set_Oric1_EN[] = // prg config Oric1 EN
    {
        0x16,0x16,0x16,0x24,0x00,0x31,0x00,0xC7,0x0B,0xCB,0x05,0x01,0x50,0x53,0x45,0x54,0x00,0x0F,0x05,0x0A,0x00,0xA1,0x3A,0x94,0x3A,0xB1,0x30,0x3A,0xB2,0x33,0x00,0x2A,
        0x05,0x1E,0x00,0x8D,0x49,0xD4,0x31,0xC3,0x37,0x3A,0x95,0x41,0x3A,0xB9,0x38,0x32,0x33,0x31,0xCC,0x49,0x2C,0x41,0x3A,0x90,0x49,0x00,0x30,0x05,0x32,0x00,0x9D,0x00,
        0x55,0x05,0x3C,0x00,0x42,0xD4,0xE6,0x28,0x23,0x32,0x30,0x32,0x38,0x29,0x3A,0x4D,0xD4,0xE6,0x28,0x23,0x32,0x30,0x32,0x39,0x29,0x3A,0x53,0xD4,0xE6,0x28,0x23,0x32,
        0x30,0x32,0x41,0x29,0x00,0x6F,0x05,0x46,0x00,0x4E,0xD4,0xE6,0x28,0x23,0x32,0x30,0x32,0x42,0x29,0x3A,0x4C,0xD4,0xE6,0x28,0x23,0x32,0x30,0x32,0x43,0x29,0x00,0x89,
        0x05,0x50,0x00,0x47,0xD4,0xE6,0x28,0x23,0x32,0x30,0x32,0x44,0x29,0x3A,0x4A,0xD4,0xE6,0x28,0x23,0x32,0x30,0x32,0x45,0x29,0x00,0xAF,0x05,0xFE,0x01,0x94,0x3A,0xBA,
        0x22,0x20,0x20,0x20,0x20,0x2D,0x2D,0x20,0x52,0x65,0x54,0x4F,0x72,0x69,0x63,0x20,0x43,0x4F,0x4E,0x46,0x49,0x47,0x55,0x52,0x41,0x54,0x49,0x4F,0x4E,0x22,0x00,0xD3,
        0x05,0x03,0x02,0xBA,0x3A,0xBA,0x22,0x31,0x20,0x2D,0x57,0x49,0x46,0x49,0x20,0x4E,0x41,0x4D,0x45,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x3A,0x20,0x2D,0x2D,
        0x2D,0x22,0x00,0xF5,0x05,0x08,0x02,0xBA,0x22,0x32,0x20,0x2D,0x57,0x49,0x46,0x49,0x20,0x50,0x41,0x53,0x53,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x3A,0x20,
        0x2D,0x2D,0x2D,0x22,0x00,0x14,0x06,0x12,0x02,0xBA,0x22,0x33,0x20,0x2D,0x57,0x49,0x46,0x49,0x20,0x4F,0x4E,0x2F,0x4F,0x46,0x46,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
        0x3A,0x22,0x3B,0x00,0x2D,0x06,0x14,0x02,0x99,0x57,0xD4,0x30,0xC9,0xBA,0x22,0x20,0x4F,0x46,0x46,0x22,0xC8,0xBA,0x22,0x20,0x4F,0x4E,0x22,0x20,0x00,0x4E,0x06,0x1C,
        0x02,0xBA,0x3A,0xBA,0x22,0x34,0x20,0x2D,0x42,0x4C,0x55,0x45,0x54,0x4F,0x4F,0x54,0x48,0x20,0x4F,0x4E,0x2F,0x4F,0x46,0x46,0x20,0x20,0x3A,0x22,0x3B,0x00,0x67,0x06,
        0x1E,0x02,0x99,0x42,0xD4,0x30,0xC9,0xBA,0x22,0x20,0x4F,0x46,0x46,0x22,0xC8,0xBA,0x22,0x20,0x4F,0x4E,0x22,0x20,0x00,0x88,0x06,0x26,0x02,0xBA,0x3A,0xBA,0x22,0x35,
        0x20,0x2D,0x4F,0x52,0x49,0x43,0x20,0x31,0x2F,0x41,0x54,0x4D,0x4F,0x53,0x20,0x20,0x20,0x20,0x20,0x20,0x3A,0x22,0x3B,0x00,0xA6,0x06,0x28,0x02,0x99,0x4D,0xD4,0x30,
        0xC9,0xBA,0x22,0x20,0x4F,0x52,0x49,0x43,0x20,0x31,0x22,0xC8,0xBA,0x22,0x20,0x41,0x54,0x4D,0x4F,0x53,0x22,0x00,0xC7,0x06,0x30,0x02,0xBA,0x3A,0xBA,0x22,0x36,0x20,
        0x2D,0x44,0x4F,0x57,0x4E,0x4C,0x4F,0x41,0x44,0x20,0x53,0x50,0x45,0x45,0x44,0x20,0x20,0x20,0x20,0x3A,0x22,0x3B,0x00,0xE3,0x06,0x32,0x02,0x99,0x53,0xD4,0x30,0xC9,
        0xBA,0x22,0x20,0x4E,0x4F,0x52,0x4D,0x41,0x4C,0x22,0xC8,0xBA,0x22,0x20,0x46,0x31,0x36,0x22,0x00,0x0D,0x07,0x3A,0x02,0x99,0x53,0xD3,0x30,0xC9,0xBA,0x3A,0xBA,0x22,
        0x37,0x20,0x2D,0x53,0x54,0x4F,0x50,0x20,0x42,0x49,0x54,0x20,0x4E,0x55,0x4D,0x42,0x45,0x52,0x20,0x20,0x20,0x3A,0x20,0x22,0x3B,0x3A,0xBA,0x4E,0x00,0x1B,0x07,0x3F,
        0x02,0x99,0x20,0x53,0xD5,0x30,0xC9,0xBA,0x3A,0xBA,0x00,0x42,0x07,0x44,0x02,0xBA,0x3A,0xBA,0x22,0x38,0x20,0x2D,0x53,0x4F,0x55,0x4E,0x44,0x20,0x4C,0x45,0x56,0x45,
        0x4C,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x3A,0x20,0x22,0x3B,0x3A,0xBA,0x4C,0xCC,0x31,0x00,0x6C,0x07,0x49,0x02,0xBA,0x3A,0xBA,0x22,0x39,0x20,0x2D,0x4A,0x4F,0x59,
        0x53,0x54,0x49,0x43,0x4B,0x20,0x4C,0x4F,0x43,0x41,0x54,0x49,0x4F,0x4E,0x20,0x3A,0x20,0x23,0x39,0x37,0x41,0x45,0x2F,0x23,0x32,0x46,0x22,0x00,0x8D,0x07,0x4E,0x02,
        0xBA,0x3A,0xBA,0x22,0x31,0x30,0x2D,0x4C,0x41,0x4E,0x47,0x55,0x41,0x47,0x45,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x3A,0x22,0x3B,0x00,0xA6,0x07,0x50,
        0x02,0x99,0x47,0xD4,0x30,0x20,0xC9,0x20,0xBA,0x22,0x20,0x46,0x52,0x22,0xC8,0xBA,0x22,0x20,0x45,0x4E,0x22,0x00,0xC2,0x07,0x53,0x02,0xBA,0x3A,0xBA,0x3A,0xBA,0x22,
        0x30,0x20,0x2D,0x53,0x41,0x56,0x45,0x20,0x41,0x4E,0x44,0x20,0x45,0x58,0x49,0x54,0x22,0x00,0xD1,0x07,0x58,0x02,0x8D,0x49,0xD4,0x31,0xC3,0x33,0x3A,0xBA,0x3A,0x90,
        0x00,0xE3,0x07,0x62,0x02,0xBA,0x3A,0xBA,0x22,0x43,0x48,0x4F,0x49,0x43,0x45,0x3A,0x22,0x3B,0x00,0xEA,0x07,0x6C,0x02,0x92,0x41,0x00,0xFB,0x07,0x71,0x02,0x99,0x20,
        0x41,0xD4,0x30,0x20,0xC9,0x20,0x32,0x30,0x30,0x30,0x00,0x10,0x08,0x76,0x02,0x99,0x20,0x41,0xD5,0x34,0x20,0xD2,0x20,0x41,0xD3,0x31,0x30,0xC9,0x20,0x35,0x30,0x00,
        0x24,0x08,0x80,0x02,0x99,0x41,0xD4,0x37,0x20,0xD1,0x20,0x53,0xD4,0x30,0x20,0xC9,0x20,0x35,0x30,0x00,0x31,0x08,0x83,0x02,0x99,0x41,0xD4,0x34,0xC9,0x36,0x39,0x30,
        0x00,0x3E,0x08,0x85,0x02,0x99,0x41,0xD4,0x35,0xC9,0x37,0x30,0x30,0x00,0x4B,0x08,0x88,0x02,0x99,0x41,0xD4,0x36,0xC9,0x37,0x35,0x30,0x00,0x58,0x08,0x8A,0x02,0x99,
        0x41,0xD4,0x37,0xC9,0x38,0x30,0x30,0x00,0x65,0x08,0x8C,0x02,0x99,0x41,0xD4,0x38,0xC9,0x39,0x30,0x30,0x00,0x71,0x08,0x8F,0x02,0x99,0x41,0xD4,0x39,0xC9,0x35,0x30,
        0x00,0x80,0x08,0x94,0x02,0x99,0x41,0xD4,0x31,0x30,0xC9,0x31,0x30,0x30,0x30,0x00,0x9A,0x08,0xB2,0x02,0xBA,0x22,0x20,0x20,0x20,0x2D,0x2D,0x20,0x42,0x4C,0x55,0x45,
        0x54,0x4F,0x4F,0x54,0x48,0x20,0x2D,0x2D,0x22,0x00,0xB5,0x08,0xB3,0x02,0xBA,0x3A,0xBA,0x22,0x30,0x20,0x2D,0x20,0x4F,0x46,0x46,0x22,0x3A,0xBA,0x22,0x31,0x20,0x2D,
        0x20,0x4F,0x4E,0x22,0x00,0xCA,0x08,0xB4,0x02,0xBA,0x3A,0xBA,0x22,0x43,0x48,0x4F,0x49,0x58,0x20,0x3A,0x22,0x3B,0x3A,0x92,0x41,0x00,0xDB,0x08,0xB7,0x02,0x99,0x41,
        0xD3,0x31,0xD2,0x41,0xD5,0x30,0xC9,0x36,0x39,0x30,0x00,0xEE,0x08,0xB8,0x02,0xB9,0x28,0x23,0x32,0x30,0x32,0x38,0x29,0x2C,0x41,0x3A,0x97,0x35,0x30,0x00,0x0C,0x09,
        0xBC,0x02,0xBA,0x22,0x20,0x20,0x20,0x2D,0x2D,0x20,0x43,0x4F,0x4D,0x50,0x41,0x54,0x49,0x42,0x49,0x4C,0x49,0x54,0x59,0x20,0x2D,0x2D,0x22,0x00,0x2D,0x09,0xC6,0x02,
        0xBA,0x3A,0xBA,0x22,0x30,0x20,0x2D,0x20,0x4F,0x52,0x49,0x43,0x20,0x31,0x22,0x3A,0xBA,0x22,0x31,0x20,0x2D,0x20,0x41,0x54,0x4D,0x4F,0x53,0x22,0x00,0x42,0x09,0xC8,
        0x02,0xBA,0x3A,0xBA,0x22,0x43,0x48,0x4F,0x49,0x43,0x45,0x3A,0x22,0x3B,0x3A,0x92,0x41,0x00,0x53,0x09,0xCB,0x02,0x99,0x41,0xD3,0x31,0xD2,0x41,0xD5,0x30,0xC9,0x37,
        0x30,0x30,0x00,0x66,0x09,0xD0,0x02,0xB9,0x28,0x23,0x32,0x30,0x32,0x39,0x29,0x2C,0x41,0x3A,0x97,0x35,0x30,0x00,0x85,0x09,0xEE,0x02,0xBA,0x22,0x20,0x20,0x20,0x2D,
        0x2D,0x20,0x44,0x4F,0x57,0x4E,0x4C,0x4F,0x41,0x44,0x20,0x53,0x50,0x45,0x45,0x44,0x20,0x2D,0x2D,0x22,0x00,0xAB,0x09,0xF8,0x02,0xBA,0x3A,0xBA,0x22,0x30,0x20,0x2D,
        0x20,0x4E,0x4F,0x52,0x4D,0x41,0x4C,0x22,0x3A,0xBA,0x22,0x31,0x20,0x2D,0x20,0x46,0x31,0x36,0x20,0x28,0x58,0x31,0x2E,0x36,0x29,0x22,0x00,0xC0,0x09,0xFD,0x02,0xBA,
        0x3A,0xBA,0x22,0x43,0x48,0x4F,0x49,0x43,0x45,0x3A,0x22,0x3B,0x3A,0x92,0x41,0x00,0xD1,0x09,0x02,0x03,0x99,0x41,0xD3,0x31,0xD2,0x41,0xD5,0x30,0xC9,0x37,0x35,0x30,
        0x00,0xE4,0x09,0x0C,0x03,0xB9,0x28,0x23,0x32,0x30,0x32,0x41,0x29,0x2C,0x41,0x3A,0x97,0x35,0x30,0x00,0xFF,0x09,0x20,0x03,0xBA,0x22,0x20,0x20,0x20,0x2D,0x2D,0x20,
        0x23,0x20,0x53,0x54,0x4F,0x50,0x20,0x42,0x49,0x54,0x20,0x2D,0x2D,0x22,0x00,0x1B,0x0A,0x2A,0x03,0xBA,0x3A,0xBA,0x22,0x42,0x45,0x54,0x57,0x45,0x45,0x4E,0x20,0x32,
        0x20,0x26,0x20,0x39,0x22,0x3B,0x3A,0x92,0x41,0x20,0x00,0x2C,0x0A,0x34,0x03,0x99,0x41,0xD5,0x32,0xD2,0x41,0xD3,0x39,0xC9,0x38,0x30,0x30,0x00,0x3F,0x0A,0x3E,0x03,
        0xB9,0x28,0x23,0x32,0x30,0x32,0x42,0x29,0x2C,0x41,0x3A,0x97,0x35,0x30,0x00,0x5B,0x0A,0x84,0x03,0xBA,0x22,0x20,0x20,0x20,0x2D,0x2D,0x20,0x53,0x4F,0x55,0x4E,0x44,
        0x20,0x4C,0x45,0x56,0x45,0x4C,0x20,0x2D,0x2D,0x22,0x00,0x76,0x0A,0x8E,0x03,0xBA,0x3A,0xBA,0x22,0x42,0x45,0x54,0x57,0x45,0x45,0x4E,0x20,0x31,0x20,0x26,0x20,0x33,
        0x22,0x3B,0x3A,0x92,0x41,0x00,0x87,0x0A,0x98,0x03,0x99,0x41,0xD5,0x31,0xD2,0x41,0xD3,0x33,0xC9,0x39,0x30,0x30,0x00,0xA0,0x0A,0xA2,0x03,0x41,0xD4,0x41,0xCD,0x31,
        0x3A,0xB9,0x28,0x23,0x32,0x30,0x32,0x43,0x29,0x2C,0x41,0x3A,0x97,0x35,0x30,0x00,0xC7,0x0A,0xB6,0x03,0xBA,0x3A,0xBA,0x22,0x20,0x20,0x2D,0x2D,0x20,0x52,0x45,0x41,
        0x44,0x20,0x4A,0x4F,0x59,0x53,0x54,0x49,0x43,0x4B,0x20,0x41,0x44,0x44,0x52,0x45,0x53,0x53,0x20,0x2D,0x2D,0x22,0x00,0xE4,0x0A,0xC0,0x03,0xBA,0x3A,0xBA,0x22,0x42,
        0x45,0x54,0x57,0x45,0x45,0x4E,0x20,0x30,0x20,0x26,0x20,0x39,0x29,0x3A,0x22,0x3B,0x3A,0x92,0x41,0x00,0xF5,0x0A,0xC5,0x03,0x99,0x41,0xD5,0x30,0xD2,0x41,0xD3,0x39,
        0xC9,0x39,0x35,0x30,0x00,0x08,0x0B,0xCA,0x03,0xB9,0x28,0x23,0x32,0x30,0x32,0x45,0x29,0x2C,0x41,0x3A,0x97,0x35,0x30,0x00,0x23,0x0B,0xE8,0x03,0xBA,0x3A,0xBA,0x22,
        0x20,0x20,0x20,0x2D,0x2D,0x20,0x4C,0x41,0x4E,0x47,0x55,0x41,0x47,0x45,0x20,0x2D,0x2D,0x22,0x00,0x46,0x0B,0xF2,0x03,0xBA,0x3A,0xBA,0x22,0x30,0x20,0x2D,0x20,0x46,
        0x52,0x45,0x4E,0x43,0x48,0x22,0x3A,0xBA,0x22,0x31,0x20,0x2D,0x20,0x45,0x4E,0x47,0x4C,0x49,0x53,0x48,0x22,0x00,0x5B,0x0B,0xF7,0x03,0xBA,0x3A,0xBA,0x22,0x43,0x48,
        0x4F,0x49,0x43,0x45,0x3A,0x22,0x3B,0x3A,0x92,0x41,0x00,0x6D,0x0B,0xFC,0x03,0x99,0x41,0xD5,0x30,0xD2,0x41,0xD3,0x31,0xC9,0x31,0x30,0x30,0x30,0x00,0x9B,0x0B,0x06,
        0x04,0xB9,0x28,0x23,0x32,0x30,0x32,0x44,0x29,0x2C,0x41,0x3A,0xB7,0x22,0x25,0x22,0x2C,0x41,0x23,0x32,0x30,0x30,0x30,0x2C,0x45,0x23,0x32,0x30,0x33,0x32,0x3A,0xB5,
        0x31,0x30,0x30,0x3A,0xB6,0x22,0x53,0x45,0x54,0x22,0x00,0xB6,0x0B,0xD0,0x07,0xB7,0x22,0x25,0x22,0x2C,0x41,0x23,0x32,0x30,0x30,0x30,0x2C,0x45,0x23,0x32,0x30,0x33,
        0x32,0x3A,0x94,0x3A,0xC1,0x00,0xC9,0x0B,0xB8,0x0B,0x91,0x30,0x2C,0x31,0x2C,0x31,0x2C,0x32,0x2C,0x30,0x2C,0x31,0x2C,0x30,0x00,0x00,0x00,0x49,

};

static const unsigned char PROGMEM routineEnvoik7[] = // Routine pour envoyer des octets sur le port cassette (#BBAA-#BBBB) à $3000
    {
        0x16,0x16,0x16,0x24,0xFF,0xFF,0x80,0x00,0x30,0x23,0x30,0x00,0xFF,0x52,0x4F,0x55,
        0x54,0x4B,0x37,0x00,0x20,0x6A,0xE7,0xA9,0x00,0x8D,0x4D,0x02,0xA9,0xAA,0x8D,0xA9,
        0x02,0xA9,0xBB,0x8D,0xAA,0x02,0xA9,0xBB,0x8D,0xAB,0x02,0xA9,0xBB,0x8D,0xAC,0x02,
        0x20,0x2E,0xE6,0x20,0x3D,0xE9,0x60,0x55,
};
// static const unsigned char PROGMEM routineEnvoik7[] = // Routine pour envoyer des octets sur le port cassette (#BBAA-#BBBB) à $7000
//     {
//         0x16,0x16,0x16,0x24,0xFF,0xFF,0x80,0x00,0x70,0x23,0x70,0x00,0xFF,0x52,0x4F,0x55,
//         0x54,0x4B,0x37,0x00,0x20,0x6A,0xE7,0xA9,0x00,0x8D,0x4D,0x02,0xA9,0xAA,0x8D,0xA9,
//         0x02,0xA9,0xBB,0x8D,0xAA,0x02,0xA9,0xBB,0x8D,0xAB,0x02,0xA9,0xBB,0x8D,0xAC,0x02,
//         0x20,0x2E,0xE6,0x20,0x3D,0xE9,0x60,0x55,
// };

// static const unsigned char PROGMEM routineJoystick[] = // Routine pour lire le Joystick adresse $3100
//     {
//         0x16,0x16,0x16,0x24,0xFF,0xFF,0x80,0x00,0x31,0x11,0x31,0x00,0xFF,0x4A,0x4F,0x59,
//         0x53,0x54,0x49,0x43,0x4B,0x00,0x20,0x6A,0xE7,0xA9,0x00,0x8D,0x4D,0x02,0x20,0xC9,
//         0xE6,0x85,0x00,0x20,0x3D,0xE9,0x60,0x55,
// };

static const unsigned char PROGMEM routineJoystick[] = // Routine pour lire le Joystick adresse $97AE / $2F
    {
        0x16,0x16,0x16,0x24,0xFF,0xFF,0x80,0x00,0x97,0xBF,0x97,0xAE,0xFF,0x4A,0x4F,0x59,
        0x53,0x54,0x49,0x43,0x4B,0x00,0x20,0x6A,0xE7,0xA9,0x00,0x8D,0x4D,0x02,0x20,0xC9,
        0xE6,0x85,0x2F,0x20,0x3D,0xE9,0x60,0x55,
};

static const unsigned char PROGMEM routineJoystickOric1[] = // Routine pour lire le Joystick adresse $97AE version Oric1
    {
        0x16,0x16,0x16,0x24,0xFF,0xFF,0x80,0x00,0x97,0xBE,0x97,0xAE,0xFF,0x4A,0x4F,0x59,
        0x53,0x54,0x49,0x43,0x4B,0x00,0x20,0xCA,0xE6,0xA9,0x00,0x85,0x67,0x20,0x30,0xE6,
        0x85,0x2F,0x20,0x04,0xE8,0x60,0x55,
};

static const unsigned char PROGMEM dirPrg[] = // programme dir Atmos Fr
    {
        0x16,0x16,0x16,0x24,0xFF,0xFF,0x00,0xC7,0x06,0x23,0x05,0x01,0xFF,0x44,0x49,0x52,
        0x00,0x0B,0x05,0x01,0x00,0xA1,0x3A,0x52,0xD4,0x30,0x00,0x41,0x05,0x02,0x00,0x94,
        0x3A,0xB1,0x30,0x3A,0xB2,0x33,0x3A,0xBA,0xC6,0x30,0x2C,0x30,0x3B,0xED,0x28,0x31,
        0x34,0x38,0x29,0x3B,0xED,0x28,0x31,0x33,0x31,0x29,0x3B,0x22,0x52,0x45,0x50,0x45,
        0x52,0x54,0x4F,0x49,0x52,0x45,0x20,0x43,0x41,0x52,0x54,0x45,0x20,0x53,0x44,0x22,
        0x00,0x73,0x05,0x03,0x00,0xBA,0xC6,0x30,0x2C,0x32,0x33,0x3B,0xED,0x28,0x31,0x34,
        0x38,0x29,0x3B,0xED,0x28,0x31,0x33,0x31,0x29,0x3B,0x22,0x2F,0x3A,0x52,0x65,0x70,
        0x2E,0x20,0x3E,0x3A,0x50,0x61,0x67,0x65,0x20,0x73,0x75,0x69,0x76,0x2E,0x22,0x3A,
        0xB6,0x22,0x00,0x84,0x05,0x04,0x00,0x99,0x52,0xD4,0x30,0xC9,0xB6,0x22,0x22,0x3A,
        0x52,0xD4,0x31,0x00,0xAD,0x05,0x05,0x00,0xBA,0x3A,0x92,0x22,0x4E,0x4F,0x4D,0x20,
        0x3A,0x22,0x3B,0x42,0x24,0x3A,0x99,0x42,0x24,0xD4,0x22,0x3E,0x22,0xC9,0xBA,0xC6,
        0x32,0x2C,0x30,0x3B,0x22,0x5B,0x3E,0x5D,0x22,0x3A,0x97,0x37,0x00,0xE1,0x05,0x06,
        0x00,0x99,0xF4,0x28,0x42,0x24,0x2C,0x31,0x29,0xD4,0x22,0x23,0x22,0xD2,0xF4,0x28,
        0x42,0x24,0x2C,0x31,0x29,0xD4,0x22,0x2F,0x22,0xC9,0xBA,0xC6,0x32,0x2C,0x30,0x3B,
        0x22,0x5B,0x22,0xCC,0x42,0x24,0xCC,0x22,0x5D,0x22,0x3A,0x97,0x37,0x3A,0xC8,0x39,
        0x00,0xF4,0x05,0x07,0x00,0xBF,0x23,0x33,0x30,0x30,0x30,0x3A,0xB5,0x31,0x30,0x30,
        0x3A,0x97,0x32,0x00,0x21,0x06,0x09,0x00,0x42,0x24,0xD4,0x22,0x5B,0x3F,0x22,0xCC,
        0x42,0x24,0xCC,0x22,0x5D,0x22,0x3A,0xBA,0xC6,0x32,0x2C,0x30,0x3B,0x42,0x24,0x3A,
        0xBF,0x23,0x33,0x30,0x30,0x30,0x3A,0xB5,0x31,0x30,0x30,0x3A,0x94,0x3A,0xB6,0x22,
        0x00,0x00,0x00,0x00,

    };
        
static const unsigned char PROGMEM dir_atmosEn[] = // programme dir Atmos En
    {
        0x16,0x16,0x16,0x24,0xFF,0xFF,0x00,0xC7,0x06,0x22,0x05,0x01,0xFF,0x44,0x49,0x52,
        0x00,0x0B,0x05,0x01,0x00,0xA1,0x3A,0x52,0xD4,0x30,0x00,0x3F,0x05,0x02,0x00,0x94,
        0x3A,0xB1,0x30,0x3A,0xB2,0x33,0x3A,0xBA,0xC6,0x30,0x2C,0x30,0x3B,0xED,0x28,0x31,
        0x34,0x38,0x29,0x3B,0xED,0x28,0x31,0x33,0x31,0x29,0x3B,0x22,0x53,0x44,0x20,0x43,
        0x41,0x52,0x44,0x20,0x44,0x49,0x52,0x45,0x43,0x54,0x4F,0x52,0x59,0x22,0x00,0x72,
        0x05,0x03,0x00,0xBA,0xC6,0x30,0x2C,0x32,0x33,0x3B,0xED,0x28,0x31,0x34,0x38,0x29,
        0x3B,0xED,0x28,0x31,0x33,0x31,0x29,0x3B,0x22,0x2F,0x3A,0x46,0x6F,0x6C,0x64,0x65,
        0x72,0x20,0x3E,0x3A,0x4E,0x65,0x78,0x74,0x20,0x70,0x61,0x67,0x65,0x22,0x3A,0xB6,
        0x22,0x00,0x83,0x05,0x04,0x00,0x99,0x52,0xD4,0x30,0xC9,0xB6,0x22,0x22,0x3A,0x52,
        0xD4,0x31,0x00,0xAC,0x05,0x05,0x00,0xBA,0x3A,0x92,0x22,0x4E,0x4F,0x4D,0x20,0x3A,
        0x22,0x3B,0x42,0x24,0x3A,0x99,0x42,0x24,0xD4,0x22,0x3E,0x22,0xC9,0xBA,0xC6,0x32,
        0x2C,0x30,0x3B,0x22,0x5B,0x3E,0x5D,0x22,0x3A,0x97,0x37,0x00,0xE0,0x05,0x06,0x00,
        0x99,0xF4,0x28,0x42,0x24,0x2C,0x31,0x29,0xD4,0x22,0x23,0x22,0xD2,0xF4,0x28,0x42,
        0x24,0x2C,0x31,0x29,0xD4,0x22,0x2F,0x22,0xC9,0xBA,0xC6,0x32,0x2C,0x30,0x3B,0x22,
        0x5B,0x22,0xCC,0x42,0x24,0xCC,0x22,0x5D,0x22,0x3A,0x97,0x37,0x3A,0xC8,0x39,0x00,
        0xF3,0x05,0x07,0x00,0xBF,0x23,0x33,0x30,0x30,0x30,0x3A,0xB5,0x31,0x30,0x30,0x3A,
        0x97,0x32,0x00,0x20,0x06,0x09,0x00,0x42,0x24,0xD4,0x22,0x5B,0x3F,0x22,0xCC,0x42,
        0x24,0xCC,0x22,0x5D,0x22,0x3A,0xBA,0xC6,0x32,0x2C,0x30,0x3B,0x42,0x24,0x3A,0xBF,
        0x23,0x33,0x30,0x30,0x30,0x3A,0xB5,0x31,0x30,0x30,0x3A,0x94,0x3A,0xB6,0x22,0x00,
        0x00,0x00,0x00,

    };

static const unsigned char PROGMEM dirPrg_Oric1[] = // programme dir Oric1 Fr
    {
        0x16,0x16,0x16,0x24,0xFF,0xFF,0x00,0xC7,0x05,0xC9,0x05,0x01,0xFF,0x44,0x49,0x52,
        0x00,0x07,0x05,0x01,0x00,0xA1,0x00,0x13,0x05,0x02,0x00,0x94,0x3A,0xB1,0x30,0x3A,
        0xB2,0x33,0x00,0x3F,0x05,0x03,0x00,0x87,0x32,0x2C,0x32,0x33,0x2C,0x22,0x2D,0x2D,
        0x2D,0x20,0x2F,0x3A,0x52,0x65,0x70,0x2E,0x20,0x3E,0x3A,0x50,0x61,0x67,0x65,0x20,
        0x73,0x75,0x69,0x76,0x2E,0x20,0x2D,0x2D,0x2D,0x22,0x3A,0xB6,0x22,0x22,0x00,0x5F,
        0x05,0x06,0x00,0x92,0x22,0x4E,0x4F,0x4D,0x20,0x3A,0x22,0x3B,0x42,0x24,0x3A,0x99,
        0xF4,0x28,0x42,0x24,0x2C,0x31,0x29,0xD4,0x22,0x3E,0x22,0xC9,0x97,0x38,0x00,0x83,
        0x05,0x07,0x00,0x99,0xF4,0x28,0x42,0x24,0x2C,0x31,0x29,0xD4,0x22,0x23,0x22,0xD2,
        0xF4,0x28,0x42,0x24,0x2C,0x31,0x29,0xD4,0x22,0x2F,0x22,0xC9,0x97,0x38,0x3A,0xC8,
        0x97,0x39,0x00,0x9F,0x05,0x08,0x00,0xB7,0x42,0x24,0x2C,0x41,0x23,0x34,0x30,0x30,
        0x2C,0x45,0x23,0x34,0x30,0x32,0x3A,0xB5,0x31,0x30,0x30,0x3A,0x97,0x32,0x00,0xC7,
        0x05,0x09,0x00,0x42,0x24,0xD4,0x22,0x3F,0x22,0xCC,0x42,0x24,0x3A,0xB7,0x42,0x24,
        0x2C,0x41,0x23,0x34,0x30,0x30,0x2C,0x45,0x23,0x34,0x30,0x32,0x3A,0xB5,0x31,0x30,
        0x30,0x3A,0x94,0x3A,0xB6,0x22,0x00,0x00,0x00,0x3A,
    };

static const unsigned char PROGMEM dir_oricEn[] = // programme dir Oric1 En
    {
      0x16,0x16,0x16,0x24,0xFF,0xFF,0x00,0xC7,0x05,0xCA,0x05,0x01,0xFF,0x44,0x49,
      0x52,0x00,0x07,0x05,0x01,0x00,0xA1,0x00,0x13,0x05,0x02,0x00,0x94,0x3A,0xB1,0x30,
      0x3A,0xB2,0x33,0x00,0x3F,0x05,0x03,0x00,0x87,0x32,0x2C,0x32,0x33,0x2C,0x22,0x2D,
      0x2D,0x2D,0x20,0x2F,0x3A,0x44,0x69,0x72,0x2E,0x20,0x3E,0x3A,0x4E,0x65,0x78,0x74,
      0x20,0x70,0x61,0x67,0x65,0x2E,0x20,0x2D,0x2D,0x2D,0x22,0x3A,0xB6,0x22,0x22,0x00,
      0x60,0x05,0x06,0x00,0x92,0x22,0x4E,0x41,0x4D,0x45,0x20,0x3A,0x22,0x3B,0x42,0x24,
      0x3A,0x99,0xF4,0x28,0x42,0x24,0x2C,0x31,0x29,0xD4,0x22,0x3E,0x22,0xC9,0x97,0x38,
      0x00,0x84,0x05,0x07,0x00,0x99,0xF4,0x28,0x42,0x24,0x2C,0x31,0x29,0xD4,0x22,0x23,
      0x22,0xD2,0xF4,0x28,0x42,0x24,0x2C,0x31,0x29,0xD4,0x22,0x2F,0x22,0xC9,0x97,0x38,
      0x3A,0xC8,0x97,0x39,0x00,0xA0,0x05,0x08,0x00,0xB7,0x42,0x24,0x2C,0x41,0x23,0x34,
      0x30,0x30,0x2C,0x45,0x23,0x34,0x30,0x32,0x3A,0xB5,0x31,0x30,0x30,0x3A,0x97,0x32,
      0x00,0xC8,0x05,0x09,0x00,0x42,0x24,0xD4,0x22,0x3F,0x22,0xCC,0x42,0x24,0x3A,0xB7,
      0x42,0x24,0x2C,0x41,0x23,0x34,0x30,0x30,0x2C,0x45,0x23,0x34,0x30,0x32,0x3A,0xB5,
      0x31,0x30,0x30,0x3A,0x94,0x3A,0xB6,0x22,0x00,0x00,0x00,0x55,
    };



String Firmware = "1.346";    // Version du firmware
bool SDcard = true;     // vraie = carte SD     Faux = LittleFS (mémoire interne)

Preferences preferences;
const char* prefKey = "NiveauSon";
const char* prefConfigKey = "Langage";
const char* prefKeyOric1 = "oric1";
const char* prefKeySpeed = "Speed";
const char* prefKeyNstop = "Nstop";    
const char* prefKeyAdrJ = "adrJoy";
const char* prefKeyBlueT = "Bluetooth";

int TimerSpeed = 208;   //208/ 416 Timer correspondant au timer sélectionné dans SetUpVia du 6522
int NiveauSon = 0;
int pageConfig = 0;
int buttonState = 0;
int lastButtonState = 0;
// int TimeStart = 0;  // temps depuis démarage
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int buttonPressCount = 0;
unsigned long lastPressTime = 0;
unsigned long pressTimeout = 1500;
unsigned long buttonPressTime = 0;
bool mini = false;  // version mini (sans joystick)
bool StopCload = false;  // Indique qu'on a stopé la recherche de fichier suite fichier non trouvé
bool Start = true;  // démarrage O/N
bool Sequentiel = false;    // si on précise le numéro de la séquence à lire, les suivantes seront lues en séquetiel
bool longPressDetected = false;
bool configMode = false;
bool Oric1 = false;
bool CopyK7 = false;
bool BlueT = false;
bool Set = false;
bool Joystick = false;
bool AnalogicJoy = false;   // true = mode joystick anologique / false : mode numérique
int directoryCount = 0;
char langage = 0;  // langue 0 Fr, 1 EN
char adrJoy = 0;    // adresse lecteur joystick (page 0 de $00 à $0B)
bool Speed = 0;  // Vitesse de lecture 0 = normal  1 = rapide
uint8_t nStopF16 = 3;  // Nombre de bits stop en vitesse rapide
int bit1H = 190;    // délai état Haut bit 1
int bit1L = 226;    // délai état Bas bit 1
int bit0H = 370;    // délai état Haut bit 0
int bit0L = 254;    // délai état Bas bit 0

// Variables globales pour stocker les informations
int NbFichiers = 0;
int NbRep = 0;
int CapaSD = 0;
int page = 0;   // Page dir en cours
int ttPage;     // Total pages

int setSeq = 0;         // sélection de la séquence à lire
int SeqCount = 0;       // nbre de séquences contenue dans le fichier
uint8_t lectureOPT = 1; // options de lecture (défaut séquentiel)
uint8_t execMode = 0;   // mode d'exécution du fichier (0 = par défaut, 1 = Auto, 2 = Manuel)
int nbSynchro = 0;      // nombre de synchro 0x16 lus dans la séquence
bool leader = false;    // marqueur pour savoir si on a lu tous les octets 0x16 de synchro
bool ajoutSeq = false;  // ajoute une séquence au fichier TAP existant
bool confirmed = false; // confirmation appui bouton
// bool afficheur = false; // permet de savoir si on a déjà rafraichit le lcd
bool startSignalCmd = false;    // réception du signal de commande
bool erreur = false;
int errorCount = 0;
bool receiving = false;
// bool endFile = false;   // Fin de lecture fichier
bool cmdRoutineK7 = false;  // commande provenant de la routine k7 = true
bool firstBitDetected = false;
bool dataStarted = false;
bool debut = false;
bool dir = false;    // permet de savoir si le dir a été affiché avant de charger la routine k7
bool dirAlt = false; // on alterne dir(false) ou settings(true)
bool catal = false;  // catal.bin chargé
bool routK7 = false; // Routine K7 chargée
bool Cload = false; // Détecte si la commande provient de CLOAD
bool NameCload = false; // indique si on a reçu le nom de CLOAD
bool RLE = false;   // octet RLE Oui / Non
bool pauseAffich = false;    // Pause affichage
bool afficheNom = false;        // Flag afficher le nom reçu
unsigned long lastRisingEdge = 0;
unsigned long bitDuration = 0;
uint8_t receivedByte = 0;
uint8_t bitCount = 0;
uint8_t buffer[BUFFER_SIZE];
int bufferIndex = 0;
int indexBuffer = 256; // uint16_t
int tailleNom = 0;  // nombre de caractères du nom d'origine du programme Oric, sert à déterminier quand envoyer la 'pause' lors du transfert vers l'Oric = 270+tailleNom
int indexPause = 0; // détermine quand l'Oric envoi 6 ou 7 bits de stop
int countBytes;
int delaiSignal = 10; // Délai pour corriger le signal d'entrée
int delaiSignalK7 = 10; // Délai correction signal K7
int delaiSignalCmd = 0;// Délai du signal de commande
int parity;           // bit de parité
int bitMdulation = 0; // permet de détéecter si l'Oric est en mode réception
char commande = 0;    // 0 commande envoyée par l'utilisateur pour sélectionner le nom de fichier à lire sur la carte SD
int fileCount = 0;
int selectedIndex = 0; // Index du fichier sélectionné
int displayStartIndex = 0; // Index du premier élément affiché
int xFile = 0;  // position originalFiles
int tailleFichierRecu = 0;
// int adrRecFinH = 0; // adresse fin Haut réception
// int adrRecFinL = 0; // adresse fin Low réception
// int adrRecDebutH = 0; // adresse début Haut réception
// int adrRecDebutL = 0; // adresse début Haut réception
// int Rectaille = 0; // taille fichier reçu

// Variables pour l'affichage du fichier
// String selectedFile = "/test.txt"; // Exemple de nom de fichier
String selectedFile = "";
File file;
String fileContent = "";
int scrollPosition = 0;
const int LINES_PER_PAGE = 5; // Nombre de lignes affichables sur l'OLED (64px / 10px par ligne)

// variables affichage core 0
int progressionPrecedente = -1; // Drapeau pour barre de progression
bool nomRecuTermine = false;    // Flag nom Reçu
bool adrFinRecept = false;      // Flag fin de fichier reçu
String nomRecu = "";
int adrRecDebutH = 0;
int adrRecDebutL = 0;
int adrRecFinH = 0;
int adrRecFinL = 0;
int adrdebut = 0;
int adfrfin = 0;

// Variables pour le joystick
bool xy = false;   // si faux on envoie la valeur de X sinon la valeur de Y
int joyX = 0;
int joyY = 0;
const int JOY_CENTER = 2048; // Valeur centrale (à ajuster selon ton joystick)
const int JOY_DEADZONE = 500; // Seuil pour éviter les micro-mouvements

// Variables partagées entre les deux cœurs
volatile int globalProgress = -1; // -1 signifie "rien à mettre à jour"
volatile bool isDisplayBusy = false;

// Tableaux pour stocker les noms d'origine des répertoires et des fichiers
std::vector<String> originalDirectories;
std::vector<String> originalFiles;

// Listes pour stocker les répertoires et les fichiers
std::vector<String> directories;
std::vector<String> files;

String fileNameFromBuffer = ""; // Nom de fichier extrait du buffer
String OrigineCload = "";  // Nom demandé par CLOAD
String cheminSd = "/";           // Chemin accès à la carte SD
String lastChemin = "/";         // dernier chemin utilisé
String fileSelect = "";     // fichier sélectionné avec le joystick
char commandek7[17];  // nom de fichier provenant de la routine K7
#define LINES_PER_PAGE  2  // On réduit pour laisser de la place à l'en-tête

// BluetoothSerial SerialBt;

void checkButtonPress();
void resendFromSD();
void saveDataToSD();
void transfert_vide_buffer();
unsigned long getFreeSpaceKb();
void sequenceDetect();
String formatName(const String& name, bool isDirectory);
void listFilesAndDirectories();
void posJoystick();
void sendBit(bool bitValue);

// --- TÂCHE D'AFFICHAGE (S'exécute uniquement sur le CORE 0) ---
void displayTask(void * pvParameters) {
  for(;;) {
    if(globalProgress >= 0) {
      isDisplayBusy = true;
      
    //   // dessine la barre
    // //   display.clearDisplay();
    //   display.drawRect(10, 25, 108, 14, SSD1306_WHITE);
    //   display.fillRect(12, 27, (globalProgress * 104) / 100, 10, SSD1306_WHITE);
    //   display.display();

    // --- Bloc de dessin corrigé pour une épaisseur réduite ---
    // hauteur totale (14 -> 13)
    // remplissage intérieur (10 -> 9)
    if (!afficheNom) {
        display.setCursor(0, 10);
        display.println(nomRecu);
        // display.println(tailleFichierRecu / 1024);
        // display.print(" Ko");
        nomRecu = "";
        afficheNom = true;
    } 
      display.drawRect(10, 24, 108, 5, SSD1306_WHITE); // Hauteur passée de 14 à 13
      display.fillRect(12, 25, (globalProgress * 104) / 100, 3, SSD1306_WHITE); // Hauteur passée de 10 à 9
      display.display();
      globalProgress = -1; // On indique que c'est fait
      isDisplayBusy = false;
    }
    // Petite pause pour laisser le processeur respirer
    vTaskDelay(10 / portTICK_PERIOD_MS); 
  }
}

void updateProgressBar(int progress) {
    int barWidth = (progress * SCREEN_WIDTH) / 100;
    int boxSize = SCREEN_WIDTH / 10; // Taille de chaque petit carré
    int boxHeight = 5; // Hauteur réduite des petits carrés
    // sendBit(1);
    // Dessiner les petits carrés de progression
    for (int i = 0; i < 10; i++) {
      if (i < (progress / 10)) {
        display.fillRect(i * boxSize, SCREEN_HEIGHT - boxHeight, boxSize, boxHeight, SSD1306_WHITE);
        // sendBit(1);
      } else {
        display.drawRect(i * boxSize, SCREEN_HEIGHT - boxHeight, boxSize, boxHeight, SSD1306_WHITE);
        // sendBit(1);
      }
    }
    // sendBit(1);
    display.display();
    // sendBit(1);
    // sendBit(1);
  }
  

// Variables globales
// unsigned long buttonPressTime = 0;
int timeOut = 0;
const unsigned long buttonPressDuration = 3000; // 3 secondes
const unsigned long confirmationTimeout = 30000; // 30 secondes
bool waitingForConfirmation = false;
String fileToDelete = "";

void printDeviceAddress() {
  const uint8_t* point = esp_bt_dev_get_address();
  for (int i = 0; i < 6; i++) {
    char str[3];
    sprintf(str, "%02x", (int)point[i]);
    Serial.print(str);
    if (i < 5) {
      Serial.print(":");
    }
  }
}

void affiche_pretReception()
{
    display.clearDisplay();
            display.setCursor(0, 0);
            Serial.print("BT = ");
            Serial.print(BlueT);
                if (langage == 0) {
                display.println("pret reception...");
                display.setCursor(0, 10);
                display.print("Reste ");
                display.print(CapaSD / 1024);
                if (BlueT) {
                    display.print(" Mo-BT");
                } else {
                    display.print(" Mo");
                }  
                } else {
                display.println("Waiting reception...");
                display.setCursor(0, 10);
                display.print("Free ");
                display.print(CapaSD / 1024);
                if (BlueT == true) {
                    display.print(" MB-BT");
                } else {
                    display.print(" MB");
                }         
                }
                if (TimerSpeed == 208) {
                    if (Speed == 0) {
                    display.print("-SP1");
                } else {
                    display.print("-F16");
                }  
                } else {
                    display.print("-FSP");
                    Speed = 1;
                }
                
                display.setCursor(0, 22);     
                if (debut) {    
                    display.print(NbFichiers);
                    if (NbFichiers > 1) {
                        if (langage == 0) {
                            display.print(" fichiers ");
                        } else {
                            display.print(" files ");
                        }
                        
                    } else {
                        if (langage == 0) {
                            display.print(" fichier ");
                        } else {
                            display.print(" file ");
                        }
                        
                    }
                    if (fileCount > 60) {
                    display.print("Pg.");
                    display.print(page + 1);
                    display.print("/");
                    display.print(ttPage);
                    }
                }
            // }
            display.display();
}

// Fonction pour trouver le nom dans le buffer (sans les commandes)
String findNameInBuffer_simple(const uint8_t *buffer, size_t bufferSize)
{
    String nom = "";
    int index = 1; // size_t index = 1; Commencer à la position index 1
    tailleNom = 0;
    nbSynchro = 0;

    while (index < bufferSize)
    {
        if (buffer[index] == 0x16)
        {
            // Passer à l'octet suivant
            index++;
            nbSynchro++;
        }
        else
        {
            // nbSynchro = index;
            Serial.print(" Nb synchro finfNameInBuffer_simple : ");
            Serial.println(nbSynchro);
            // Augmenter la position index de 10
            index += 10;
            if (index >= bufferSize)
            {
                break; // Sortir de la boucle si on dépasse la taille du buffer
            }

            // Lire les bits à partir de cette position
            while (index < bufferSize && buffer[index] != 0)
            {
                nom += static_cast<char>(buffer[index]);
                index++;
                tailleNom++;
            }

            // Si on a trouvé un 0, c'est la fin de la chaîne
            if (index < bufferSize && buffer[index] == 0)
            {
                break;
            }
        }
    }

    // Limiter la taille de la chaîne à 16 caractères
    if (nom.length() > 8)   // 16
    {
        nom = nom.substring(0, 8);
    } 

    // nom = fileNameFromBuffer; // Mettre à jour la variable nom
    
// Serial.println(fileNameFromBuffer);                                               
    return nom;
}

// Fonction pour trouver le nom dans le buffer
String findNameInBuffer(const uint8_t *buffer, size_t bufferSize)
{
    String nom = "";
    int index = 1; // size_t index = 1; Commencer à la position index 1
    tailleNom = 0;
    setSeq = 0; // Initialiser la variable setSeq
    nbSynchro = 0;

    //
    // Vérifier le nombre de 0x16 au début du buffer
    while (nbSynchro < bufferSize && buffer[nbSynchro] == 0x16) {
        nbSynchro++;
        // Serial.print(buffer[nbSynchro]);
        // Serial.print(" ");
    }

    while (index < bufferSize)
    {
        if (buffer[index] == 0x16)  //buffer[index] == 0x16
        {
            // Passer à l'octet suivant
            index++;
            nbSynchro++;
        }
        else
        {
            if (buffer[index] == 0x24) {
            nbSynchro = index;
            Serial.print(" Nb synchro findNameInBuffer : ");
            Serial.println(nbSynchro);
            // Augmenter la position index de 10
            index += 10;    //10
            if (index >= bufferSize)
            {
                break; // Sortir de la boucle si on dépasse la taille du buffer
            }

            // Lire les bits à partir de cette position
            while (index < bufferSize && buffer[index] != 0)
            {
                nom += static_cast<char>(buffer[index]);
                index++;
                tailleNom++;
            }

            // Si on a trouvé un 0, c'est la fin de la chaîne
            if (index < bufferSize && buffer[index] == 0)
            {
                break;
            }
            } else {
                index++;
            }
        }
    }

    // Limiter la taille de la chaîne à 16 caractères
    if (nom.length() > 16)
    {
        nom = nom.substring(0, 16);
    }
    Serial.print("nom origine :");
    Serial.println(nom);
    if (nom.startsWith("+")) {
        ajoutSeq = true;
        nom = nom.substring(1);
        // return nom;
    }

    if (nom.startsWith("#J")) {     // mode joystick
        commande = 0;
        if (nom == "#JA") {
            AnalogicJoy = true;
        } else {
            AnalogicJoy = false;
        }
        nom = "";
        bufferIndex = 0;
        page = 0;
        posJoystick();
    }

    
        // Serial.print("bufferIndex = ");
        // Serial.println(bufferIndex);
    
    if (nom == "%" && bufferIndex < 323) {     //322 réception configuration bufferIndex < 323 || bufferIndex == 76
        int pos;
        pos = bufferIndex;
        // if (bufferIndex == 321) {
        //     Serial.println("-------------321----------");
        //     pos = 321;
        // } else {
        //     Serial.println("-------------76----------");
        //     pos = 76;
        // }
        if (buffer[pos - 10] == 1) { //312 bufferindex -10
            BlueT = true;
        } else {
            BlueT = false;
        }
        if (buffer[pos - 9] == 0) { //313
            Oric1 = true;
        } else {
            Oric1 = false;
        }
    preferences.putBool(prefKeyOric1, Oric1);
    preferences.putBool(prefKeyBlueT, BlueT);

    Speed = buffer[pos -8];    //314
    if (TimerSpeed != 208) {
        Speed = 1;
    }
    preferences.putBool(prefKeySpeed, Speed);
    if (Speed == 1) {
        nStopF16 = buffer[pos -7]; //315
        preferences.putChar(prefKeyNstop, nStopF16);
    }
    NiveauSon = buffer[pos -6];    //316
    langage = buffer[pos -5];   //317
    adrJoy = buffer[pos -4];   //318
    preferences.putInt(prefKey, NiveauSon);
    preferences.putChar(prefConfigKey, langage);
    preferences.putChar(prefKeyAdrJ, adrJoy);
    commande = 0;
    OrigineCload = "";
    nom = "";
    page = 0;
    if (NiveauSon == 2) {
        digitalWrite(nivSonQ1, LOW);
        digitalWrite(nivSonQ2, LOW);
    }
    if (NiveauSon == 1) {
        digitalWrite(nivSonQ1, LOW);
        digitalWrite(nivSonQ2, HIGH);
    }
    if (NiveauSon == 0) {
        digitalWrite(nivSonQ1, HIGH);
        digitalWrite(nivSonQ2, HIGH);
    }
    Serial.print("Sauvegarde configuration "); 
    // Serial.println(bufferIndex);
    if (BlueT == true) {
        SerialBT.begin("Oric");
        delay(1000);
        // PS4.begin();
        Serial.print("Adresse MAC : ");
        printDeviceAddress();
        Serial.println("");
        // PS4.begin("41:42:4E:41:B6:44");
        // delay(1000);
        // Serial.println("Adresse MAC : ");
        // printDeviceAddress();
        // Serial.println("");
        // if (PS4.isConnected()) {
        //     Serial.println("PS4 connectée ");
        // }
    } else {
        // PS4.end();
        SerialBT.end();
    }
    delay(1000);
    affiche_pretReception();
    bufferIndex = 0; 
    return nom;
    }

    if (nom.startsWith("B:") || OrigineCload.startsWith("B:")) {
        int x = 256;
        nom = nom.substring(2);
        if (BlueT)  {
            // sauter les 0x22
            while (buffer[x] == 0x22) {
                x++;
            }
            x += 9;
            // Sauter jusqu'au prochain 0x00
            while (buffer[x] > 0) {
                x++;
            }
            if (cmdRoutineK7) {     // commande venant de la routine K7
                Serial.println("cmdRoutineK7 ");
                delayMicroseconds(500);
                SerialBT.print(nom); // envoyer le nom
            } else {
                delayMicroseconds(500);
                SerialBT.print(nom + (char)10); // envoyer le nom et retour ligne
                while (x < bufferIndex) {
                    // Vérifier si le caractère est imprimable (ASCII entre 32 et 126)
                    String c = "";
                    if (buffer[x] >= 32 && buffer[x] <= 126) {
                      c = (char)buffer[x];
                      delayMicroseconds(600);
                      SerialBT.print(c);
                    }
                x++;
                }
            }
            cmdRoutineK7 = false;
        }
        
        bufferIndex = 0;
        commande = 0;
        nom = "";
        page = 0;
        return nom;
    }

    fileNameFromBuffer = nom.substring(1); // Prendre les caractères suivants
    Serial.println(nom);

    if (nom.startsWith("?") && nom.length() > 1)
    {
    commande = 1;

    // Ajouter une extension par défaut si nécessaire
    if (fileNameFromBuffer.length() < 4 || fileNameFromBuffer.indexOf('.') == -1)
    {
        fileNameFromBuffer += ".TAP";
    }

    // Vérifier si le nom contient l'extension .TAP
    int tapIndex = fileNameFromBuffer.indexOf(".TAP");
    if (tapIndex != -1)
    {
        
        // Extraire la partie après ".TAP"
        String suffixe = fileNameFromBuffer.substring(tapIndex + 4);

        if (fileNameFromBuffer.endsWith("M")) {    // mode Manuel
                execMode = 2;
                fileNameFromBuffer = fileNameFromBuffer.substring(0, tapIndex + 4); // Garder uniquement ".TAP"
            }
        if (fileNameFromBuffer.endsWith("A")) {    // mode Auto
                execMode = 1;
                fileNameFromBuffer = fileNameFromBuffer.substring(0, tapIndex + 4); // Garder uniquement ".TAP"
        }
        // if (fileNameFromBuffer.endsWith("P")) {    // Pause forcée
        //         lectureOPT = 3;
        //         Sequentiel = true;
        //         fileNameFromBuffer = fileNameFromBuffer.substring(0, tapIndex + 4); // Garder uniquement ".TAP"
        // }
        Serial.print("suffixe : ");
        Serial.print(suffixe);
        Serial.print(" fileNameromBuffer : ");
        Serial.println(fileNameFromBuffer);

        // Initialiser les variables
        Sequentiel = false;
        setSeq = 0;

        // Vérifier si le suffixe contient 1 ou 2 chiffres suivis éventuellement d'un "S" (séquentiel) ou "P" (pause forcée)
        if (suffixe.length() >= 1 && suffixe.length() <= 3)
        {
            bool aUnS = (suffixe.endsWith("S") | suffixe.endsWith("P"));
            if (suffixe.endsWith("P")) {    // Pause forcée
                lectureOPT = 3;
                Sequentiel = true;
            }
            if (suffixe.endsWith("S")) {    // Sériel
                lectureOPT = 1;
                Sequentiel = true;
            }

            String chiffres;

            if (aUnS)
            {
                chiffres = suffixe.substring(0, suffixe.length() - 1); // Enlever le "S"
                // Sequentiel = true;
                // lectureOPT = 1;
            }
            else
            {
                chiffres = suffixe;
                // lectureOPT = 2;
                // Sequentiel = false;
            }

            // Vérifier si les chiffres sont valides (1 ou 2 chiffres)
            if (chiffres.length() >= 1 && chiffres.length() <= 2 &&
                isDigit(chiffres[0]) && (chiffres.length() == 1 || isDigit(chiffres[1])))
            {
                setSeq = chiffres.toInt();
                Serial.print("Setseq : ");
                Serial.print(setSeq);
                fileNameFromBuffer = fileNameFromBuffer.substring(0, tapIndex + 4); // Garder uniquement ".TAP" + chiffres
            }
            }
        }

        nom = fileNameFromBuffer; // Mettre à jour la variable nom
    }

    if (nom.startsWith("/"))
    { // demande pour changer de répertoire
        commande = 3;
        if (nom == "/") {
            cheminSd = "/";
        } else if (nom == "/..") {
            // Enlever le dernier répertoire de cheminSd
            int lastSlashIndex = cheminSd.lastIndexOf('/');
            if (lastSlashIndex != -1) {
                cheminSd = cheminSd.substring(0, lastSlashIndex);
                // // S'assurer que cheminSd se termine par un '/'
                // if (!cheminSd.endsWith("/")) {
                //     cheminSd += "/";
                // }
            }
        } else {
            cheminSd += nom;
        }
        nom = "";
        bufferIndex = 0;
        debut = false;
        Serial.print("commande = 3 ");
        Serial.print("Chemin : ");
        Serial.println(cheminSd);
    }
    

if (nom.startsWith("#")) {
    if (nom.startsWith("#[")) {
        Serial.println(nom);
        // Demande pour créer un nouveau répertoire
        nom = nom.substring(2); // Enlever le '#['
        String newDirPath = "/" + cheminSd + "/" + nom;
        if (SD.mkdir(newDirPath)) {
            Serial.print("Répertoire créé : ");
            Serial.println(nom);
            display.clearDisplay();
            display.setCursor(0, 10);
            display.println("Cr. Rep. / ");
            display.print(nom);
            display.display();
            delay(2000);
            commande = 0;
            bufferIndex = 0;
            nom = "";
        } else {
            Serial.print("Erreur lors de la création du répertoire : ");
            Serial.println(nom);
        }
    } else {
        // Demande pour afficher les séquences d'un fichier TAP
        commande = 5;
        bufferIndex = 0;
        nom = nom.substring(1); // Enlever le '#'
        if (nom.startsWith("|")) {
            // Demande effacement fichier
            commande = 0;
            bufferIndex = 0;
            nom = nom.substring(1); // Enlever le '|'
            fileToDelete = "/" + cheminSd + "/" + nom;
            File dataFile = SD.open(fileToDelete, FILE_READ);
            if (dataFile) {
                dataFile.close();
                Serial.print("Appuyez sur le bouton pendant 3 secondes pour confirmer la suppression de ");
                Serial.println(nom);
                timeOut = millis();
                while (digitalRead(bouton) == HIGH && (millis() - timeOut) < confirmationTimeout) {
                    display.clearDisplay();
                    display.setCursor(0, 10);
                    if (langage == 0) {
                        display.print("Effacer ");
                        display.print(nom);
                        display.println(" ?");
                        display.print("Confirmez +3s ");
                    } else {
                        display.print("Delete ");
                        display.print(nom);
                        display.println(" ?");
                        display.print("Confirm +3s ");
                    }

                    display.print((confirmationTimeout / 1000) - ((millis() - timeOut) / 1000));
                    display.display();
                    // delay(2000);
                }
                waitingForConfirmation = true;
                buttonPressTime = millis();
                while (digitalRead(bouton) == LOW && millis() - buttonPressTime < 3000) {
                    // display.clearDisplay();
                    // display.setCursor(5, 10);
                    // display.print(millis() - buttonPressTime / 1000);
                    // display.print(" sec.");
                    // display.display();
                }
                checkButtonPress();
            } else {
                Serial.print("Le fichier ");
                Serial.print(nom);
                Serial.println(" n'existe pas.");
            }
            nom = "";
        } else {
            Serial.println(commande);
            Serial.print(" ");
            Serial.println(nom);
        }
    }
}


    if (nom == ">")
    { // demande pour afficher la page suivante
        if (fileCount > 60)
        {
            commande = 4;
            bufferIndex = 0;
            if (page == ttPage - 1) {
                page = 0;
            } else {
            page++;
            }
            nom = "";
            Serial.print("commande = 4 page : ");
            Serial.println(page);
            
        }
        else
        {
            commande = 0;
            nom = "";
            bufferIndex = 0;
            page = 0;
            // Serial.println("Commande annulée");
        }
    }
// Serial.println(fileNameFromBuffer);                                               
    return nom;
}

// Fonction pour vérifier l'appui sur le bouton
void checkButtonPress() {
    if (waitingForConfirmation) {
        
            if (millis() - buttonPressTime >= buttonPressDuration) {
                SD.remove(fileToDelete);
                Serial.print("Fichier ");
                Serial.print(fileToDelete);
                Serial.println(" supprimé.");
                display.clearDisplay();
                display.setCursor(0, 10);
                if (langage == 0) {
                    display.println("Fichier supprime !");
                } else {
                    display.println("File deleted !");
                }
                
                display.display();
                delay(2000);
                waitingForConfirmation = false;
            } else {
                Serial.println("Confirmation annulée. Le fichier n'a pas été supprimé.");
                display.clearDisplay();
                display.setCursor(0, 10);
                if (langage == 0) {
                    display.println("Demande annulee !");
                } else {
                    display.println("Canceled !");
                }
                
                display.display();
                delay(2000);
            }
        
            if (millis() - buttonPressTime >= confirmationTimeout) {
                Serial.println("Confirmation annulée. Le fichier n'a pas été supprimé.");
                waitingForConfirmation = false;
            }
        
    }
}

void displayNiveauSon() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    if (langage == 0) {
        display.print("     Volume Son");
    } else {
        display.print("    Sound level");
    }
    
    // display.println(NiveauSon);
  
     // Draw horizontal scale
  int scaleLength = 80;
  int scaleStartX = (SCREEN_WIDTH - scaleLength) / 2;
  int scaleY = 20;

  // Draw scale line
  display.drawLine(scaleStartX, scaleY, scaleStartX + scaleLength, scaleY, SSD1306_WHITE);

  // Draw scale ticks
  for (int i = 1; i <= 3; i++) {
    int tickX = scaleStartX + ((i - 1) * scaleLength / 2);
    display.drawLine(tickX, scaleY - 2, tickX, scaleY + 2, SSD1306_WHITE);
    display.setCursor(tickX - 3, scaleY + 5);
    display.print(i);
  }

  // Draw cursor
  int cursorX = scaleStartX + (NiveauSon * scaleLength / 2);
  display.fillTriangle(cursorX - 5, scaleY - 5, cursorX + 5, scaleY - 5, cursorX, scaleY + 5, SSD1306_WHITE);

  display.display();
  }


// Fonction pour afficher les fichiers et répertoires
void displayFilesAndDirectories() {
    // Calculer la longueur de la chaîne
    int longueur = cheminSd.length();

    // Extraire les 21 derniers caractères
    String dernierSegment = cheminSd.substring(max(0, longueur - 21));

    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(dernierSegment);
    display.setCursor(0, 8);

    int debutIndex = 1100;
    // Afficher les fichiers et répertoires à partir de l'index displayStartIndex
    // Serial.println("Fichier sélectionné displayFiles : " + selectedFile);
    if (Oric1) {
        debutIndex++;
    }
    for (int i = 0; i < 4 && (displayStartIndex + i) <= (NbRep + NbFichiers); i++) { // i<4
        String fileName = "";
        if (displayStartIndex == 0 && i == 0) {
                fileName = "..";
            } else {
        for (int j = 0; j < 12; j++) {
            fileName += (char)buffer[debutIndex + (displayStartIndex + i) * 12 + j];
            
        }
    }
        
        if ((displayStartIndex + i) == selectedIndex) {
            display.print(">");
            selectedFile = fileName;
        } else {
            display.print(" ");
        }
        display.println(fileName);
    }

    display.display();
}

void setup()    // ---------------------- SETUP -------------------------------------
{
    // display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for(;;);
    }
    Wire.setClock(800000);
    // Wire.begin(SDA, SCL ,800000);
    // display.display();
    // delay(2000);
    display.clearDisplay();
    display.display();

    // Création de la tâche d'affichage sur le CORE 0
    xTaskCreatePinnedToCore(
        displayTask,    // Fonction
        "DisplayTask",  // Nom
        4096,           // Pile
        NULL,           // Paramètres
        1,              // Priorité
        NULL,           // Handle
        0               // <--- CORE 0
    );

    Serial.begin(BAUD_RATE);
    pinMode(DATA_PIN, INPUT);
    pinMode(START_PIN, INPUT_PULLUP);
    pinMode(bouton, INPUT_PULLUP);
    pinMode(valid, INPUT_PULLUP);
    pinMode(fire, INPUT_PULLUP);
    pinMode(SEND_PIN, OUTPUT);
    pinMode(PERIOD_LED_PIN, OUTPUT);
    pinMode(DATA_LED_PIN, OUTPUT);
    pinMode(nivSonQ1, OUTPUT);
    pinMode(nivSonQ2, OUTPUT);
    digitalWrite(PERIOD_LED_PIN, LOW); // Éteindre la LED de période au démarrage
    digitalWrite(DATA_LED_PIN, LOW);   // Éteindre la LED de données au démarrage

    preferences.begin("my-app", false);
    NiveauSon = preferences.getInt(prefKey, 0);
    langage = preferences.getChar(prefConfigKey, 0);
    Oric1 = preferences.getBool(prefKeyOric1, false);
    Speed = preferences.getBool(prefKeySpeed, false);
    nStopF16 = preferences.getChar(prefKeyNstop, 3);
    adrJoy = preferences.getChar(prefKeyAdrJ, 0);
    BlueT = preferences.getBool(prefKeyBlueT, false);
    if (BlueT) {
        SerialBT.begin("Oric");
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("    >> ReTOric <<");
    // display.setCursor(0, 10);
    if (langage == 0) {
        display.println("     Bienvenue !");
    } else {
        display.println("     Welcome !");
    }
    display.println("");
    display.print("              v.");
    display.print(Firmware);
    display.display();
        
    Serial.print("Version : ");
    if (analogRead(xVal) > 1000) {
        mini = false;
        Serial.println("joystick OK");
     } else {
        mini = true;
        Serial.println("NO joystick");
     }
    // Serial.print(analogRead(yVal));
    // Serial.println(analogRead(xVal));
    delay(2000);
    

    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Config ");
        if (!Oric1) {
            display.println(" Atmos");
        } else {
            display.println(" Oric 1");
        }
        if (Speed == 1) {
            // display.print(" ");
            display.print(nStopF16);
            display.println(" stop bit F16");
        } else {
            display.println("Sp 1");
        }
    display.print("Bt ");
    if (BlueT) {
        display.println("ON");
    } else {
        display.println("OFF");
    }
    if (langage == 0) {
        display.print("Volume son : ");
    } else {
        display.print("Sound level : ");
    }
    
    display.print(NiveauSon + 1);
    display.display();
    if (NiveauSon == 2) {
        digitalWrite(nivSonQ1, LOW);
        digitalWrite(nivSonQ2, LOW);
    }
    if (NiveauSon == 1) {
        digitalWrite(nivSonQ1, LOW);
        digitalWrite(nivSonQ2, HIGH);
    }
    if (NiveauSon == 0) {
        digitalWrite(nivSonQ1, HIGH);
        digitalWrite(nivSonQ2, HIGH);
    }
    
    delay(1600);

    if (!LittleFS.begin(true)) { // Le paramètre `true` formate LittleFS si nécessaire
        Serial.println("Erreur lors du montage de LittleFS");
        return;
    }
    delay(500);

    Serial.println("LittleFS monté avec succès");
    // Récupérer les informations sur l'espace
    uint64_t totalBytes = LittleFS.totalBytes();
    uint64_t usedBytes = LittleFS.usedBytes();
    uint64_t freeBytes = totalBytes - usedBytes;

    // Afficher les résultats
    Serial.println("--- Informations sur LittleFS ---");
    Serial.print("Taille totale : ");
    Serial.print(totalBytes);
    Serial.println(" octets");

    Serial.print("Taille utilisée : ");
    Serial.print(usedBytes);
    Serial.println(" octets");

    Serial.print("Taille disponible : ");
    Serial.print(freeBytes);
    Serial.println(" octets");

    // SD.begin("/SD", true);
    // Initialiser la carte SD
    if (!SD.begin(CS_PIN))
    {
        Serial.println("Initialisation de la carte SD échouée !");
        display.clearDisplay();
        display.setCursor(0, 0);
        if (langage == 0) {
            display.println("Erreur carte SD !");
        } else {
            display.println("SD card error !");
        }
        
        display.display();
        delay(5000);
        return;
    }
    Serial.println("Carte SD initialisée avec succès.");
    listFilesAndDirectories();
    CapaSD = getFreeSpaceKb();
    display.clearDisplay();

    // attente démarrage Oric
    while (digitalRead(DATA_PIN) == LOW)
    {
        delay(400);
    } 
    while (digitalRead(START_PIN) == LOW)
    {
        delay(400);
    }

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    if (langage == 0) {
        display.println("Attente reception");
    } else {
        display.println("Waiting reception");
    }

    display.setCursor(0, 10);
    if (langage == 0) {
        display.print("Reste : ");
    } else {
        display.print("Free : ");
    }
    
    display.print(CapaSD / 1024);
    // affiche_pretReception();
    commande = 0;
    transfert_vide_buffer();
    delay(10);
    resendFromSD();
    
    // if (CapaSD < 1024000) {
    //     display.print(CapaSD / 1024);
    //     display.print(" Mo");
    // } else {
    //     display.print(CapaSD / 1024000);
    //     display.print(" Go");
    // }
    
    // display.setCursor(0, 20);
    if (langage == 0) {
        if (BlueT) {
            display.print(" Mo-BT");
        } else {
            display.print(" Mo");
        }
        
        
    } else {
        if (BlueT) {
            display.print(" MB-BT");
        } else {
            display.print(" MB");
        }
        // display.println(" MB");
        
    }
    if (TimerSpeed == 208) {
        if (Speed == 0) {
            display.println("-SP1");
        } else {
            display.println("-F16");
                }  
        } else {
            display.println("-FSP");
    }
    if (langage == 0) {
        display.println("Carte SD prete");
    } else {
        display.println("SD card ready");
    }
    if (BlueT) {
    //     // PS4.begin("41:42:4E:41:B6:44");
    //     PS4.begin();
        Serial.println("Adresse MAC : ");
        printDeviceAddress();
        Serial.println("");
    //     delay(1000);
    //     if (PS4.isConnected()) {
    //         Serial.println("PS4 connectée ");
    //     }
    }
    display.display();     
    delay(1000);
    // displayNiveauSon();
    // SerialBt.println("Oric Bluetooth initialisé.");
}

// Fonction pour obtenir la capacité restante de la carte SD en Ko
unsigned long getFreeSpaceKb()
{
    unsigned long freeBytes = SD.cardSize() - SD.usedBytes();
    return freeBytes / 1024;
}


void Sablier() {
  display.clearDisplay();
  display.setCursor(0, 10);
  if (langage == 0) {
        display.println("Un instant SVP...");
    } else {
        display.print("Please wait...");
    }
  
  display.display();
}

// Fonction pour lister les fichiers et dossiers présents sur la carte SD
void listFilesAndDirectories() {
    NbFichiers = 0;
    NbRep = 0;
    page = 0;
    Sablier();
        
    File root = SD.open("/" + cheminSd);
    if (!root) {
        display.clearDisplay();
        display.setCursor(0, 10);
        if (langage == 0) {
        display.println("Impossible d'ouvrir");
        display.setCursor(0, 20);
        display.println("le repertoire !");
    } else {
        display.println("Unable top open");
        display.setCursor(0, 20);
        display.println("directory !");
    }
        
        display.display();
        delay(3000);
        Serial.println("Erreur : Impossible d'ouvrir le répertoire racine.");
        commande = 0;
        return;
    }

    int bufferIndex = 1100; // Commencer à l'index 1100
    if (Oric1) {
        bufferIndex++;
    }
    fileCount = 0;
    debut = true;
    File file = root.openNextFile();

    // // Listes pour stocker les répertoires et les fichiers
    // std::vector<String> directories;
    // std::vector<String> files;

    // Vider les tableaux des noms d'origine
    originalDirectories.clear();
    originalFiles.clear();

    directories.clear();
    files.clear();

    while (file && bufferIndex < BUFFER_SIZE) {
        String fileName = file.name();
        bool isDirectory = file.isDirectory();

        // Filtrer les fichiers selon les critères de longueur de nom et d'extension
        if (fileName != "System Volume Information") {
            if (isDirectory) {
                directories.push_back(fileName);
                originalDirectories.push_back(fileName); // Stocker le nom d'origine
                NbRep++;
            } else if (fileName.length() <= 12 && fileName.indexOf('.') >= 0 && fileName.indexOf('.') <= 8 && fileName.length() - fileName.indexOf('.') <= 4) {
                files.push_back(fileName);
                originalFiles.push_back(fileName); // Stocker le nom d'origine
                NbFichiers++;
            }
        }
        file = root.openNextFile();
    }

    // Trier les répertoires et les fichiers par ordre alphabétique
    std::sort(directories.begin(), directories.end());
    std::sort(files.begin(), files.end());

    // Ajouter cheminSD au buffer en premier, limité aux 12 derniers caractères
    String limitedCheminSD = cheminSd.substring(cheminSd.length() > 12 ? cheminSd.length() - 12 : 0);
    for (int i = 0; i < 12; i++) {
        buffer[bufferIndex++] = limitedCheminSD.charAt(i);
    }
    fileCount++;

    // Ajouter les répertoires au buffer ensuite
    for (size_t i = 0; i < directories.size(); i++) {
        String formattedName = formatName(directories[i], true);
        for (int j = 0; j < 12; j++) {
            buffer[bufferIndex++] = formattedName.charAt(j);
        }
        fileCount++;
    }

    // Ajouter les fichiers au buffer ensuite
    for (size_t i = 0; i < files.size(); i++) {
        if (bufferIndex == selectedIndex) {
            fileSelect = originalFiles[i]; // Utiliser le nom d'origine
            Serial.println(fileSelect);
        }
        String formattedName = formatName(files[i], false);
        for (int j = 0; j < 12; j++) {
            buffer[bufferIndex++] = formattedName.charAt(j);
        }
        fileCount++;
    }

    // Ajouter un nom de 12 caractères contenant des "*" à la fin
    if (bufferIndex + 12 <= BUFFER_SIZE) {
        // String endMarker = "************             ";
        String endMarker = "************                                       ";
        for (int i = 0; i < 50; i++) {  // 24
            buffer[bufferIndex++] = endMarker.charAt(i);
        }
    }

    // Obtenir la capacité restante de la carte SD en Ko
    CapaSD = getFreeSpaceKb();
    Serial.print("Nombre fichiers : ");
    Serial.print(NbFichiers);
    Serial.print(" Nombre répertoires : ");
    Serial.print(NbRep);
    // Serial.print(" Nombre de pages : ");
    // Serial.println(ttPage);
    // Mettre à jour les compteurs de répertoires et de fichiers
    directoryCount = directories.size();
    fileCount = files.size();
}


// Fonction pour formater le nom
String formatName(const String& name, bool isDirectory)
{
    if (isDirectory)
    {
        // Garder les 10 premiers caractères et ajouter "[]" à la fin
        String dirName = name.substring(0, name.length() > 10 ? 10 : name.length());
        return dirName + "[]";
    }
    else
    {
        String namePart = name;
        String extPart = "";
        int dotIndex = name.lastIndexOf('.');
        if (dotIndex != -1)
        {
            namePart = name.substring(0, dotIndex);
            extPart = name.substring(dotIndex);
        }

        // Formater le nom pour qu'il ait 8 caractères
        while (namePart.length() < 8)
        {
            namePart += ' ';
        }
        if (namePart.length() > 8)
        {
            namePart = namePart.substring(0, 8);
        }

        // Formater l'extension pour qu'elle ait 4 caractères
        while (extPart.length() < 4)
        {
            extPart += ' ';
        }
        if (extPart.length() > 4)
        {
            extPart = extPart.substring(0, 4);
        }

        // Combiner le nom et l'extension avec des espaces entre eux
        return namePart + extPart;
    }
}

bool verifierPariteImpaire(int bits, int parity);

// Fonction pour mettre le programme dir dans le buffer
void transfert_dir_buffer()
{
    indexBuffer = 256;
    memset(buffer, 0x16, 256);
    if (langage == 0) {
        if (Oric1) {
            for (uint16_t x = 0; x < sizeof(dirPrg_Oric1); x++)
            {
                buffer[indexBuffer] = pgm_read_byte_near(dirPrg_Oric1 + x);
                indexBuffer++;
            }
            } else {
            for (uint16_t x = 0; x < sizeof(dirPrg); x++)
            {
                buffer[indexBuffer] = pgm_read_byte_near(dirPrg + x);
                indexBuffer++;
            }     
        }
    } else {
        if (Oric1) {
            for (uint16_t x = 0; x < sizeof(dir_oricEn); x++)
            {
                buffer[indexBuffer] = pgm_read_byte_near(dir_oricEn + x);
                indexBuffer++;
            }
        } else {
            for (uint16_t x = 0; x < sizeof(dir_atmosEn); x++)
            {
                buffer[indexBuffer] = pgm_read_byte_near(dir_atmosEn + x);
                indexBuffer++;
            }
        }
    }

}

// Fonction pour mettre le programme set dans le buffer
void transfert_set_buffer()
{
    indexBuffer = 256;
    memset(buffer, 0x16, 256);
    // if (Oric1) {
        if (langage == 0) {
        for (uint16_t x = 0; x < sizeof(set_Oric1); x++)
    {
        buffer[indexBuffer] = pgm_read_byte_near(set_Oric1 + x);
        indexBuffer++;                                                                                                                                                                                 
    }    
    } else {
        for (uint16_t x = 0; x < sizeof(set_Oric1_EN); x++)
    {
        buffer[indexBuffer] = pgm_read_byte_near(set_Oric1_EN + x);
        indexBuffer++;
    }
    }

    // Remplacement conditionnel de "#97AE" par "#E4F7" si TimerSpeed != 208
    if (TimerSpeed != 208) {
        for (uint16_t i = 280; i < indexBuffer - 4; i++) {
            if (buffer[i] == 0x23 &&  // '#'
                buffer[i+1] == 0x39 && // '9'
                buffer[i+2] == 0x37 && // '7'
                buffer[i+3] == 0x41 && // 'A'
                buffer[i+4] == 0x45) { // 'E'
                buffer[i] = 0x23;   // '#'
                buffer[i+1] = 0x45; // 'E'
                buffer[i+2] = 0x34; // '4'
                buffer[i+3] = 0x46; // 'F'
                buffer[i+4] = 0x37; // '7'
                break;
            }
        }
        for (uint16_t i = 280; i < indexBuffer - 2; i++) {
            if (buffer[i] == 0x46 &&  // 'F'
                buffer[i+1] == 0x31 && // '1'
                buffer[i+2] == 0x36 // '6'
                ) {
                buffer[i] = 0x46;   // 'F'
                buffer[i+1] = 0x53; // 'S'
                buffer[i+2] = 0x50; // 'P'
                break;
            }
        }
    }

    if (BlueT) {
        buffer[indexBuffer - 17] = 0x31;
    } else {
        buffer[indexBuffer - 17] = 0x30;
    }
    if (Oric1) {
        buffer[indexBuffer - 15] = 0x30;
    } else {
        buffer[indexBuffer - 15] = 0x31;
    }
    if (Speed == 0) {
        buffer[indexBuffer - 13] = 0x30;
    } else {
        buffer[indexBuffer - 13] = 0x31;
    }
    buffer[indexBuffer - 11] = nStopF16 + 0x30;
    buffer[indexBuffer - 9] = NiveauSon + 0x30;
    if (langage == 0) {
        buffer[indexBuffer - 7] = 0x30;
    } else {
        buffer[indexBuffer - 7] = 0x31;
    }
    // buffer[indexBuffer - 5] = adrJoy + 0x30;
    buffer[indexBuffer - 5] = (uint8_t)adrJoy + 0x30;
    // }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
}

void transfert_vide_buffer()  // charge routine CLOAD""
{     
    Serial.print(" nb fichiers : ");
    Serial.println(NbFichiers);
    Serial.print(" xFile : ");
    Serial.println(xFile);
    if (xFile > NbFichiers) {
        xFile = NbFichiers;
    }
    if (xFile == 0) {
        xFile = NbFichiers - 1;
    } else {
        xFile--;
    }
    // xFile--;
    String nom = originalFiles[xFile];
    nom = ":" + nom;
    // originalFiles[xFile] = ":" + originalFiles[xFile];
    indexBuffer = 256;
    memset(buffer, 0x16, 256);
    if (!Oric1) {   // version Atmos
        for (uint16_t x = 0; x < sizeof(headerFileASM); x++)
        {
        if (indexBuffer == 269) {
          for (uint16_t i = 0; i < nom.length(); i++) {
              char c = nom.charAt(i);
               if (c >= 'a' && c <= 'z') {  // Si le caractère est une minuscule
                   buffer[indexBuffer] = c - 32;  // Conversion en majuscule (ASCII)
                } else {
                 buffer[indexBuffer] = c;  // Sinon, on garde le caractère tel quel
             }
                indexBuffer++;
         }
        }
        buffer[indexBuffer] = pgm_read_byte_near(headerFileASM + x);
        indexBuffer++;
        }
    } else {    // version Oric 1
    for (uint16_t x = 0; x < sizeof(headerFile); x++)
    {
    if (indexBuffer == 269) {
        for (uint16_t i = 0; i < nom.length(); i++) {
            char c = nom.charAt(i);
            if (c >= 'a' && c <= 'z') {  // Si le caractère est une minuscule
                buffer[indexBuffer] = c - 32;  // Conversion en majuscule (ASCII)
            } else {
                buffer[indexBuffer] = c;  // Sinon, on garde le caractère tel quel
            }
            indexBuffer++;
        }
      }
      buffer[indexBuffer] = pgm_read_byte_near(headerFile + x);
      indexBuffer++;
      }
    }
}

void transfert_joyVide_buffer()  // charge routine CLOAD"JOYSTICK"
{
    indexBuffer = 256;
    memset(buffer, 0x16, 256);
    if (!Oric1) {
        for (uint16_t x = 0; x < sizeof(joystick_videASM); x++)
    {
        buffer[indexBuffer] = pgm_read_byte_near(joystick_videASM + x);
        indexBuffer++;
    }
    } else {
        for (uint16_t x = 0; x < sizeof(joystick_videASMOric1); x++)
    {
        buffer[indexBuffer] = pgm_read_byte_near(joystick_videASMOric1 + x);
        indexBuffer++;
    }
    }
    
    Set = true;

}

void transfert_joystick_buffer()
{
    indexBuffer = 256;
    memset(buffer, 0x16, 256);
    if (Oric1) {
        for (uint16_t x = 0; x < sizeof(routineJoystickOric1); x++)
    {
        if (x == 33) {  // mettre adrJoy à la place de 00 pour adressage de lecture de la valeur du Joystick
            buffer[indexBuffer] = adrJoy;
        } else {
            buffer[indexBuffer] = pgm_read_byte_near(routineJoystickOric1 + x);
        }
        indexBuffer++;
    }
    } else {
        for (uint16_t x = 0; x < sizeof(routineJoystick); x++)
    {
        if (x == 34) {  // mettre adrJoy à la place de 00 pour adressage de lecture de la valeur du Joystick
            buffer[indexBuffer] = adrJoy;
        } else {
            buffer[indexBuffer] = pgm_read_byte_near(routineJoystick + x);
        }
        indexBuffer++;
    }
    }
    
    Set = true;

}

void transfert_notFound_buffer()  // charge Not Found
{
    indexBuffer = 256;
    memset(buffer, 0x16, 256);
    for (uint16_t x = 0; x < sizeof(notFound); x++)
    {
        buffer[indexBuffer] = pgm_read_byte_near(notFound + x);
        indexBuffer++;
    }
    Set = true;
}

void transfert_Setvide_buffer()
{
    indexBuffer = 256;
    for (uint16_t i = 0; i < 256; i++)
    { // ajouter les 256 bytes à 0x16
        buffer[i] = 0x16;
    }
    for (uint16_t x = 0; x < sizeof(set_vide); x++)
    {
        buffer[indexBuffer] = pgm_read_byte_near(set_vide + x);
        indexBuffer++;
    }
    Set = true;

}

// Fonction pour mettre la routine K7 dans le buffer
void transfert_routk7_buffer()
{
    indexBuffer = 256;
    for (uint16_t i = 0; i < 256; i++)                                                             
    { // ajouter les 256 bytes à 0x16
        buffer[i] = 0x16;
    }
    for (uint16_t x = 0; x < sizeof(routineEnvoik7); x++)
    {
        buffer[indexBuffer] = pgm_read_byte_near(routineEnvoik7 + x);
        indexBuffer++;
    }
}

void sequenceDetect()   // détecte nombre de séquences présentes dans le fichier
{
    const uint8_t sequence1[] = {0x16, 0x16, 0x16, 0x24};
    const uint8_t sequence2[] = {0x16, 0x16, 0x16, 0x16, 0x24};
    const int sequenceLength1 = sizeof(sequence1);
    const int sequenceLength2 = sizeof(sequence2);
    int sequenceCount = 0;
    int currentIndex1 = 0;
    int currentIndex2 = 0;
    // String fileName = fileNameFromBuffer;   // nom du fichier
    File dataFile = SD.open("/" + cheminSd + "/" + fileNameFromBuffer, FILE_READ);
    if (!dataFile)
    {
        Serial.println("Erreur : Fichier introuvable sur la carte SD.");
        commande = 0;
        display.clearDisplay();
        display.setCursor(0, 10);
        if (langage == 0) {
            display.println("Fichier introuvable !");
        } else {
            display.println("File doesn't exist !");
        }
        
        display.display();
        delay(3000);
        display.clearDisplay();
        display.display();
        return;
    }

    // Détecter le nombre de séquences comprenant la suite 0x16 0x16 0x16 0x24 ou 0x16 0x16 0x16 0x16 0x24 dans dataFile
    while (dataFile.available())
    {
        uint8_t data = dataFile.read();
        if (data == sequence1[currentIndex1])
        {
            currentIndex1++;
            if (currentIndex1 == sequenceLength1)
            {
                sequenceCount++;
                currentIndex1 = 0;
            }
        }
        else
        {
            currentIndex1 = 0;
        }

        if (data == sequence2[currentIndex2])
        {
            currentIndex2++;
            if (currentIndex2 == sequenceLength2)
            {
                sequenceCount++;
                currentIndex2 = 0;
            }
        }
        else
        {
            currentIndex2 = 0;
        }
    }
    SeqCount = sequenceCount;
    dataFile.close();
}

void affichePause(int sequence, int totalSeq)
{
    display.clearDisplay();
    if (!mini) {
        display.setCursor(0, 9);
        display.print(" - <O> +    ^:Opt.");
    }
            
    display.setCursor(0, 15);
    if (langage == 0) {
        display.println("Pause...");
        display.println("Bouton pour sortir");
    } else {
        display.println("Break...");
        display.println("Button to exit");
    }
    display.setCursor(0, 0);
    if (langage == 0) {
        display.print("Suivant -> ");
    } else {
        display.print("Next -> ");
    }
    display.print(sequence + 1);
    display.print("/");
    display.print(totalSeq);
    display.display();
}

void Options()
{
    bool exitLoop = false;
    execMode = 0; // 0 = "---", 1 = "ON", 2 = "OFF"
    bool inExecModeMenu = false;
    int displayOffset = 0; // Décalage pour l'affichage des options

    while (analogRead(yVal) < 1000) {
        delay(200);
    }

    while (!exitLoop)
    {
        int joyX = analogRead(xVal);
        int joyY = analogRead(yVal);

        // Affichage des options
        display.clearDisplay();
        display.setCursor(0, 0);
        if (langage == 0) {
            display.println("- Mode lecture -");
        } else {
            display.println("- Reading mode -");
        }

        // Affichage des options avec décalage si nécessaire
        for (int i = 1; i <= 3; i++) {
            int optionToDisplay = i + displayOffset;
            if (optionToDisplay <= 4) {
                display.print((lectureOPT == optionToDisplay && !inExecModeMenu) ? ">" : " ");
                if (optionToDisplay == 1) display.println("1- sequentiel");
                else if (optionToDisplay == 2) display.println("2- # unique");
                else if (optionToDisplay == 3) display.println("3- sequ. + pauses");
                else if (optionToDisplay == 4) {
                    display.print("4- exec. AUTO ");
                    if (inExecModeMenu) {
                        display.setTextColor(BLACK, WHITE);
                        if (execMode == 0) display.println("---");
                        else if (execMode == 1) display.println("ON ");
                        else if (execMode == 2) display.println("OFF");
                        display.setTextColor(WHITE, BLACK);
                    } else {
                        display.println("");
                    }
                }
            }
        }

        display.display();

        // Navigation entre les options principales
        if (!inExecModeMenu) {
            if (joyY > 4000) {
                if (lectureOPT < 4) {
                    lectureOPT++;
                    if (lectureOPT > 3) {
                        displayOffset = 1; // Décalage pour afficher la 4ème option
                    }
                }
                delay(200);
            }
            else if (joyY < 1000) {
                if (lectureOPT > 1) {
                    lectureOPT--;
                    if (lectureOPT <= 3) {
                        displayOffset = 0; // Retour à l'affichage initial
                    }
                }
                delay(200);
            }
            // Entrée dans le menu execMode
            else if (joyX > 4000 && lectureOPT == 4) {
                inExecModeMenu = true;
                delay(200);
            }
        }
        // Navigation dans le menu execMode
        else {
            if (joyX > 4000) { // Droite : cycle des valeurs
                execMode = (execMode + 1) % 3;
                delay(300);
            }
            else if (joyX < 1000) { // Gauche : sortie et mémorisation
                inExecModeMenu = false;
                delay(200);
            }
        }

        // Sortie complète du menu
        if (joyX < 1000 && !inExecModeMenu) {
            if (lectureOPT == 4) {
                lectureOPT = 1;
            }
            exitLoop = true;
            delay(200);
        }
    }

    // Mémorisation de execMode (variable globale ou EEPROM)
    // Exemple : EEPROM.write(ADDR_EXEC_MODE, execMode);

    Serial.print("Option lecture : ");
    Serial.println(lectureOPT);
    Serial.print("execMode : ");
    Serial.println(execMode);

    while (analogRead(xVal) < 1000) {
        // Attente
    }
}

void attenteCload(int sequence, int totalSeq)
{
    display.clearDisplay();
    if (!mini && totalSeq > 1) {
        display.setCursor(0, 9);
        display.print(" - <O> +    ^:Opt.");
    }
            
    display.setCursor(0, 15);
    if (langage == 0) {
        display.println("Attente CLOAD...");
        display.println("Bouton pour sortir");
    } else {
        display.println("Wait for CLOAD...");
        display.println("Button to exit");
    }
    display.setCursor(0, 0);
    display.print(fileNameFromBuffer);
    display.print(" -> ");
    if (sequence == 0) {
        display.print(sequence +1);
    } else {
        display.print(sequence);
    }
    
    display.print("/");
    display.print(totalSeq);
    display.display();
}

void attenteCload2()
{
    display.clearDisplay();            
    display.setCursor(0, 17);
    if (langage == 0) {
        display.println("Attente CLOAD...");
        display.println("Bouton pour sortir");
    } else {
        display.println("Wait for CLOAD...");
        display.println("Button to exit");
    }
    display.setCursor(0, 0);
    display.print("<-- ");
    display.print(fileNameFromBuffer);
    display.println(" -->");
    display.print(" exec. Auto <> ");
    if (execMode == 0) {
        display.print("---");
    }
    if (execMode == 1) {
        display.print("ON ");
    }
    if (execMode == 2) {
        display.print("OFF");
    }
    display.display();
}

void transfert_infoTAP_buffer()
{
    const uint8_t sequence1[] = {0x16, 0x16, 0x16, 0x24};
    const uint8_t sequence2[] = {0x16, 0x16, 0x16, 0x16, 0x24};
    const int sequenceLength1 = sizeof(sequence1);
    const int sequenceLength2 = sizeof(sequence2);

    int sequenceCount = 0;
    int sequenceIndexes[99]; // Pas plus de 99 séquences
    int sequenceSizes[99];   // Tailles des séquences
    int currentIndex1 = 0;
    int currentIndex2 = 0;
    String fileName = fileNameFromBuffer;   // nom du fichier
    String nom = "";    // nom de la séquence affichée
    String sequencesName[99];   // nom de chaque séquence
    File dataFile = SD.open("/" + cheminSd + "/" + fileName, FILE_READ);

    if (!dataFile)
    {
        Serial.println("Erreur : Fichier introuvable sur la carte SD.");
        commande = 0;
        display.clearDisplay();
        display.setCursor(0, 10);
        if (langage == 0) {
            display.println("Fichier introuvable !");
        } else {
            display.println("File doesn't exist !");
        }
        
        display.display();
        delay(3000);
        display.clearDisplay();
        display.display();
        return;
    }

    // Détecter le nombre de séquences comprenant la suite 0x16 0x16 0x16 0x24 ou 0x16 0x16 0x16 0x16 0x24 dans dataFile
    // mémoriser l'index de début de chaque séquence
    while (dataFile.available())
    {
        uint8_t data = dataFile.read();
        if (data == sequence1[currentIndex1])
        {
            currentIndex1++;
            if (currentIndex1 == sequenceLength1)
            {
                sequenceIndexes[sequenceCount] = dataFile.position() - sequenceLength1;
                sequenceCount++;
                currentIndex1 = 0;
            }
        }
        else
        {
            currentIndex1 = 0;
        }

        if (data == sequence2[currentIndex2])
        {
            currentIndex2++;
            if (currentIndex2 == sequenceLength2)
            {
                sequenceIndexes[sequenceCount] = dataFile.position() - sequenceLength2;
                sequenceCount++;
                currentIndex2 = 0;
            }
        }
        else
        {
            currentIndex2 = 0;
        }
    }

    // Calculer la taille de chaque séquence
    for (int i = 0; i < sequenceCount; i++)
    {
        int startIndex = sequenceIndexes[i];
        int endIndex = (i < sequenceCount - 1) ? sequenceIndexes[i + 1] : dataFile.size();
        sequenceSizes[i] = endIndex - startIndex;
        Serial.print("taille séquence ");
        Serial.print(i);
        Serial.print(" : ");
        Serial.println(sequenceSizes[i]);
    }

    // Pour chaque séquence on lit le nom et on le met dans sequencesName
    currentIndex1 = 1;
    dataFile.seek(0);   // Réinitialiser le fichier pour le lire à nouveau
    for (int i = 0; i < sequenceCount; i++) 
    {
        dataFile.seek(sequenceIndexes[i]);
        for (int x= 1; x < 32; x++)     // remplir le buffer du début de la séquence pour trouver ensuite le nom
        {
            uint8_t data = dataFile.read();
            buffer[x] = data;
        }
        sequencesName[i] = findNameInBuffer_simple(buffer, 31);
        Serial.println(sequencesName[i]);
    }

    // Remplir le buffer
    indexBuffer = 256;

    // // Remplir le buffer
    memset(buffer, 0x16, 256);

    for (uint16_t x = 0; x < sizeof(pageDir); x++)
    {
        buffer[indexBuffer] = pgm_read_byte_near(pageDir + x);
        indexBuffer++;
    }

    uint16_t adrFin = 48159 + (sequenceCount * 40);
    uint8_t octet1 = (adrFin >> 8) & 0xFF;
    uint8_t octet2 = adrFin & 0xFF;
    buffer[264] = octet1; // écrire adresse de fin dans le buffer
    buffer[265] = octet2;

    // Remplir les 800 octets suivants avec des espaces (0x20)
    memset(&buffer[indexBuffer], 0x20, 1081 - indexBuffer);

    // Ajouter le nom du fichier à la première ligne
    
    fileName = fileName + " (" + sequenceCount + ")";
    fileName.toUpperCase();
    fileName.toCharArray((char*)&buffer[indexBuffer], 40);
    
    indexBuffer += fileName.length(); // Incrémente indexBuffer de la longueur réelle du nom du fichier

    // Déterminer la largeur maximale nécessaire pour afficher les tailles des séquences
    int maxSizeWidth = 0;
    for (int i = 0; i < sequenceCount; i++)
    {
        int sizeWidth = String(sequenceSizes[i]).length();
        if (sizeWidth > maxSizeWidth)
        {
            maxSizeWidth = sizeWidth;
        }
    }

    // Trouver la longueur maximale des noms de séquences
    int maxNameLength = 0;
    for (int i = 0; i < sequenceCount; i++) {
        if (sequencesName[i].length() > maxNameLength) {
         maxNameLength = sequencesName[i].length();
        }
    }
    // Ajouter les informations des séquences avec alignement
    for (int i = 0; i < sequenceCount && i < 20; i++) {
        String sequenceInfo = " ";
        if (i < 9) {
            sequenceInfo += "  " + String(i + 1) + " - ";
        } else {
            sequenceInfo += " " + String(i + 1) + " - ";
        }

        // Ajouter le nom de la séquence
        // if (sequencesName[i].length() > 8) {
        //     sequencesName[i] = sequencesName[i].substring(0, 8);
        // }
        sequenceInfo += sequencesName[i];

        // Ajouter des espaces pour aligner la taille
        int spaces = maxNameLength - sequencesName[i].length() + 1; // +1 pour un espace après le nom
        for (int j = 0; j < spaces; j++) {
            sequenceInfo += " ";
        }

        // Ajouter la taille
        sequenceInfo += String(sequenceSizes[i]);

        // Copier dans le buffer
        sequenceInfo.toCharArray((char*)&buffer[indexBuffer], 40);
        indexBuffer += 40;
    }
    
    indexBuffer = 279 + 800;
    dataFile.close();
}



// Fonction pour mettre le directory dans le buffer
void transfert_pageDir_buffer()
{
    indexBuffer = 256;  //256
    uint16_t adrFin = 0;
    uint8_t octet1 = 0;
    uint8_t octet2 = 0;
    fileCount = NbRep + NbFichiers +1;
    int fileCountRest = fileCount - (page * 60);
    
    // ttPage = (fileCount / 60) + ((fileCount % 60) / 10);
    ttPage = (fileCount / 60);
    if (fileCount % 60 > 0) {
        ttPage++;
    }
    Serial.print(" Nombre de pages : ");
    Serial.print(ttPage);
    Serial.print(" affichés : ");
    if (fileCountRest > 60) {
        Serial.println("60");
    } else {
        Serial.println(fileCountRest);
    }
    
    if (fileCountRest > 60)
    { // adresse maxi
        octet1 = 0xBF;
        octet2 = 0x17;  //3F
    }
    else if (fileCountRest > 0)
    { // adr mini
        adrFin = 48119 + (((fileCountRest / 3) + (fileCountRest % 3)) * 40); //48159
        octet1 = (adrFin >> 8) & 0xFF;
        octet2 = adrFin & 0xFF;
    }
    else
    {
        octet1 = 0xBC;
        octet2 = 0x47;
    }
    // Serial.print(octet1, HEX);
    // Serial.println(octet2, HEX);

    for (uint16_t i = 0; i < 256; i++)  //256
    { // ajouter les 256 bytes à 0x16
        buffer[i] = 0x16;
    }
    for (uint16_t x = 0; x < sizeof(pageDir); x++)
    {
        buffer[indexBuffer] = pgm_read_byte_near(pageDir + x);
        // Serial.print(indexBuffer);
        // Serial.print(" ");
        // Serial.print(buffer[indexBuffer], HEX);
        // Serial.print(" ");
        indexBuffer++;
    }

    // Serial.println(indexBuffer);

    buffer[264] = octet1; // écrire adresse de fin dans le buffer
    buffer[265] = octet2;
    // Serial.print(buffer[264],HEX);
    // Serial.print(buffer[265],HEX);

    uint16_t imax = 1081;
    // Oric1 ajout 0x04 octet 8 pour mode auto
    if (Oric1) {
        buffer[263] = 0x04;
        buffer[267] = 0xf7;
        imax = 1082;
    } else {
        imax = 1081;
    }
    

    // Réinitialiser indexBuffer à 279 pour ajouter fileInfos
    indexBuffer = 279;  //279
    if (Oric1) {
        buffer[indexBuffer] = 0x60;
        indexBuffer++;
    }
    
    Serial.println(" ");

    // Remplir les 800 octets suivants avec des espaces (0x20)
    
    for (uint16_t i = indexBuffer; i < imax; i++)   //1081
    {
        buffer[i] = 0x20;
    }

    int filePage = fileCountRest;
    int pageIndex = 1100 + (page * 720);    //1100
    if (Oric1) {
        pageIndex++;
    }

    if (fileCount >= 60)
    {
        filePage = 60;
    }

    Serial.print("Noms / page : ");
    Serial.print(filePage);
    Serial.print(" Index page : ");
    Serial.print(pageIndex);

    // Ajouter le contenu de FileInfos dans le buffer
    for (int i = 0; i < filePage; i++)
    { // filecount
        // Lire le nom formaté directement depuis le buffer
        String name(reinterpret_cast<char *>(&buffer[pageIndex + i * 12]), 12);

        Serial.print(" ");
        Serial.print(name);

        if (name == "************") {
            name = "            ";
            commande = 2;
        }
        // Calculer la position de début pour aligner à droite dans une colonne de 12 caractères
        int startPos = indexBuffer + (12 - name.length());

        // Ajouter le nom formaté au buffer
        for (int j = 0; j < name.length(); j++)
        {
            char c = name.charAt(j);
            if (c >= 32 && c <= 125)
            { // Vérifier si le caractère est entre 32 et 125
                buffer[startPos + j] = c;
            }
            else
            {
                buffer[startPos + j] = ' '; // Remplacer par un espace si hors de la plage
            }
        }

        // Mettre à jour indexBuffer pour la prochaine colonne
        indexBuffer += 12;

        // Ajouter un espace entre les colonnes
        if ((i + 1) % 3 != 0)
        {
            buffer[indexBuffer++] = ' ';
        }

        // Passer à la ligne suivante après chaque groupe de 3 noms
        if ((i + 1) % 3 == 0 && i < filePage - 1)
        {
            buffer[indexBuffer++] = ' ';
            buffer[indexBuffer++] = ' ';
        }
    }
    indexBuffer = 279 + (((filePage / 3) + (filePage % 3)) * 40);   //279

    if (Oric1) {
        indexBuffer++;
    }
}

String nettoyerNomFichier(const String& file) {
    // 1. Vérifier la présence de "[]"
    int posCrochets = file.indexOf("[]");
    if (posCrochets != -1) {
        // Si "[]" est trouvé, retourner la partie avant
        return file.substring(0, posCrochets);
    }

    // 2. Sinon, reconstruire le nom du fichier
    String nomBase = file.substring(0, 8);
    nomBase.trim();

    int dernierPoint = file.lastIndexOf('.');
    String extension = "";
    if (dernierPoint != -1) {
        extension = file.substring(dernierPoint);
        extension.trim();
    }

    return nomBase + extension;
}

void displayFileContent() {
  file = SD.open("/" + cheminSd + "/" + selectedFile, FILE_READ);
  if (!file) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Fichier introuvable");
    display.display();
    delay(1000);
    return;
  }

  // Affiche le nom et la taille du fichier en première ligne
  String header ="";
  if (file.size() < 10000) {
    header = selectedFile + " (" + String(file.size()) + " o)";
  } else {
    header = selectedFile + " (" + String(file.size() / 1024) + " Ko)";
  }
  
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(header);
  display.display();
  delay(1000);

  // Lit le fichier par blocs pour éviter les problèmes de mémoire
  unsigned long fileSize = file.size();
  const int bytesPerLine = 5;  // Nombre d'octets par ligne (ajustable)
  const int bytesPerPage = bytesPerLine * LINES_PER_PAGE;
  unsigned char bufferDump[bytesPerPage];
  bool exitDisplay = false;
  unsigned long filePos = 0;

  while (!exitDisplay) {
    joyX = analogRead(xVal);
    joyY = analogRead(yVal);

    // Défilement vers le haut
    if (joyY < JOY_CENTER - JOY_DEADZONE) {
      if (filePos >= bytesPerPage) filePos -= bytesPerPage;
      delay(200);
    }
    // Défilement vers le bas
    else if (joyY > JOY_CENTER + JOY_DEADZONE) {
      if (filePos + bytesPerPage < fileSize) filePos += bytesPerPage;
      delay(200);
    }
    // Sortie si joystick vers la gauche
    else if (joyX < JOY_CENTER - JOY_DEADZONE) {
      exitDisplay = true;
      file.close();
      break;
    }

    // Lit un bloc de données
    file.seek(filePos);
    size_t bytesRead = file.read(bufferDump, bytesPerPage);

    // Affiche le contenu hexadécimal et ASCII
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(header);
    for (int i = 0; i < bytesRead; i += bytesPerLine) {
      String hexLine = "";
      String asciiLine = "";
      for (int j = 0; j < bytesPerLine; j++) {
        if (i + j < bytesRead) {
          // Formatage hexadécimal (ex: "41 ")
          char hex[4];
          snprintf(hex, sizeof(hex), "%02X ", bufferDump[i + j]);
          hexLine += hex;
          // Caractère ASCII (ou '.' si non imprimable)
          asciiLine += (bufferDump[i + j] >= 32 && bufferDump[i + j] <= 126) ? char(bufferDump[i + j]) : '.';
        }
      }
      // Affiche la ligne hex + ASCII
      display.setCursor(0, 10 + (i / bytesPerLine) * 10);
      display.print(hexLine);
      display.setCursor(95, 10 + (i / bytesPerLine) * 10);
      display.println(asciiLine);
    }
    display.display();
  }
  file.close();
}

void loop() //-------------------------------- LOOP --------------------------------
{ 
        
   if (digitalRead(DATA_PIN) == HIGH && !receiving && (analogRead(yVal) > 4000 | analogRead(yVal) < 1000) && mini == false) { // Sélection par joystick
        if (cheminSd != lastChemin) {
            listFilesAndDirectories();
        }
        
        displayFilesAndDirectories();

        // Boucle pour naviguer dans les fichiers et répertoires
        while (true) {
            
            // int reading = digitalRead(27); // Bouton de validation sur GPIO 27 = Fire

            if (analogRead(yVal) > 4000) {
                // Défilement vers le bas
                if (selectedIndex < (NbFichiers + NbRep)) {
                    selectedIndex++;
                    if (selectedIndex >= displayStartIndex + 3) {
                        displayStartIndex++;
                    }
                    displayFilesAndDirectories();
                    delay(200);
                }
            } else if (analogRead(yVal) < 1000) {
                // Défilement vers le haut
                if (selectedIndex > 0) {
                    selectedIndex--;
                    if (selectedIndex < displayStartIndex) {
                        displayStartIndex--;
                    }
                    displayFilesAndDirectories();
                    delay(200);
                }
            }
            if (analogRead(xVal) < 1000) {    // vers la gauche : quitter
                
                // display.display();
                affiche_pretReception();
                selectedFile ="";
                break;
            }

            if (analogRead(xVal) > 4000 && selectedIndex > NbRep) {     // vers la droite : afficher les infos et contenu du fichier sélectionné
                // Serial.println(selectedFile);
                String OldselectedFile = selectedFile;
                int debutIndex = 1100;
                if (Oric1) {
                    debutIndex++;
                }
                for (int j = 0; j < 12; j++) {
                    selectedFile += (char)buffer[debutIndex + selectedIndex * 12 + j];
                }
                selectedFile.trim();
                String nomNettoye = nettoyerNomFichier(selectedFile);
                Serial.println(nomNettoye);
                selectedFile = nomNettoye;
                displayFileContent();
                selectedFile = OldselectedFile;
                displayFilesAndDirectories;
                // delay(2000);
            }

            if (digitalRead(fire) == LOW) {     // Appui bouton pour sélection du fichier à lire
                display.clearDisplay();
                display.setCursor(0, 0);
                display.print("--> ");
                display.print(selectedFile);
                display.print(" <--");
                display.setCursor(0, 15);
                display.print("Preparation...");
                display.display();
                Serial.println(selectedIndex);
                // Afficher le nom d'origine du fichier ou répertoire sélectionné sur le terminal
                if (selectedIndex == 0) {
                    // Enlever le dernier répertoire du chemin
                    int lastSlash = cheminSd.lastIndexOf('/');
                    if (lastSlash != -1) {
                        cheminSd = cheminSd.substring(0, lastSlash);
                        Serial.println("Répertoire parent : " + cheminSd);
                    }
                    displayStartIndex = 0;
                    selectedIndex = 0;
                    if (lastChemin != cheminSd) {
                    listFilesAndDirectories();
                    }
                    lastChemin = cheminSd;
                    displayStartIndex = 0;
                    displayFilesAndDirectories();
                    // Serial.println("Répertoire .. " + cheminSd);
                    } else if (selectedIndex <= NbRep && selectedIndex > 0) {
                    // Serial.println("Répertoire sélectionné : " + originalDirectories[selectedIndex - 1]);
                    // Serial.println("Répertoire courant : " + cheminSd);
                    String nomNettoye = nettoyerNomFichier(selectedFile);
                    Serial.println("Répertoire : " + selectedFile);
                    cheminSd += "/" + nomNettoye;
                    Serial.println("Répertoire courant : " + cheminSd);
                    displayStartIndex = 0;
                    selectedIndex = 0;
                    displayStartIndex = 0;
                    lastChemin = cheminSd;
                    listFilesAndDirectories();
                    displayFilesAndDirectories();
                    } else {
                    // int fileIndex = selectedIndex - NbRep - 1;
                    if (selectedIndex <= (NbRep + NbFichiers)) {
                     // Serial.println("Fichier original : " + originalFiles[selectedIndex]);   //fileindex
                     // Serial.print("File index : ");
                     // Serial.println(fileIndex);
                     Serial.println("Fichier sélectionné sortie : " + selectedFile);
                     Serial.print("selected index : ");
                     Serial.println(selectedIndex);
                     String nomNettoye = nettoyerNomFichier(selectedFile);
                     Serial.println(nomNettoye);
                     fileNameFromBuffer = nomNettoye;
                     commande = 1;                    
                     }
                     // afficher attente cload
                     sequenceDetect();
                     setSeq = 1;
                     lectureOPT = 1;
                     Sequentiel = true;
                     if (SeqCount > 1) {
                        attenteCload(setSeq , SeqCount);
                     
                     while (digitalRead(START_PIN) == HIGH && digitalRead(bouton) == HIGH)
                        {
                        // vérifier si sequentiel est vraie et si on fait joystick gauche ou droit pour incrémenter ou décrémenter seq pour la suite
                        if (analogRead(xVal) < 1000 && !mini && SeqCount > 1) { // gauche (-)
                            if (setSeq > 1 ) {
                                 setSeq--;
                                Serial.print(" setseq -- : ");
                                Serial.println(setSeq);
                                delay(200);
                            }
                        } 
                        if (analogRead(xVal) > 4000 && !mini && SeqCount > 1) { // droite (+)
                            if (setSeq < SeqCount ) {
                                 setSeq++; 
                                Serial.print(" setseq ++ : ");
                                Serial.println(setSeq);
                                delay(200);
                            }
                        } 
                        
                        if (analogRead(yVal) < 1000 && !mini && SeqCount > 1) { // haut (options)
                    
                        Options();

                        }

                        attenteCload(setSeq, SeqCount);
                        display.display();
                        }
                        if (digitalRead(bouton) == LOW)
                        {
                            commande = 0;
                        }
                     } else {
                        attenteCload2();
                        while (digitalRead(START_PIN) == HIGH && digitalRead(bouton) == HIGH)
                        {
                        
                        if (analogRead(xVal) < 1000 && !mini) { // gauche (-)
                            if (execMode > 0 ) {
                                 execMode--;
                                Serial.print(" execMode -- : ");
                                Serial.println(execMode);
                                delay(200);
                            }
                        } 
                        if (analogRead(xVal) > 4000 && !mini) { // droite (+)
                            if (execMode < 2 ) {
                                 execMode++; 
                                Serial.print(" execMode ++ : ");
                                Serial.println(execMode);
                                delay(200);
                            }
                        } 

                        attenteCload2();
                        display.display();
                        }
                     }
                    while (digitalRead(bouton) == LOW)
                    {
                        delay(200);
                    }
                    
                    }
                break;
            }
        }
    }

    if (digitalRead(DATA_PIN) == HIGH && !receiving && digitalRead(bouton) == LOW) {  // appui bouton pour config
        int delai = millis();
        while (digitalRead(bouton) == LOW) {
            if (millis() - delai > 1000) {
                display.clearDisplay();

                if (millis() - delai > 1000 && millis() - delai < 3000) {
                    display.setCursor(0,0);
                    display.print("Joystick");                        
                    
                }

                if (millis() - delai > 3000 && millis() - delai < 5000) {
                    display.setCursor(0,0);
                    if (langage == 0) {
                        display.print("Vitesse");
                    } else {
                        display.print("Speed");
                    }
                }
                
                if (millis() - delai > 5000 && millis() - delai < 7000) {
                    display.setCursor(0,0);
                    display.print("Configuration");
                }
                if (millis() - delai > 7000 && millis() - delai < 9000) {
                    display.setCursor(0,0);
                    if (langage == 0) {
                        display.print("Langage");
                    } else {
                        display.print("Language");
                    }
                }
                if (millis() - delai > 9000) {
                    display.setCursor(0,0);
                    display.print("RESET");
                }

                display.setCursor(70, 10);
                display.print((millis() - delai) / 1000);
                display.print(" s.");
                display.display();
            }
        }
        
        display.clearDisplay();
        display.setCursor(0, 0);
        if (langage == 0) {
                    display.println("pret reception...");
                } else {
                    display.println("Waiting reception...");
                }
        display.setCursor(0, 10);

        if (millis() - delai > 1000 && millis() - delai < 3000) {
                    posJoystick();
                    return;
                }

        if (millis() - delai > 3000 && millis() - delai < 5000) {
            if (langage == 0) {
                        display.println("Vitesse lecture");
                    } else {
                        display.println("Read speed");
                    }
        
        if (Speed == 1) {
            Speed = 0;
            if (langage == 0) {
                        display.print("Sp1 Normale x1");
                    } else {
                        display.print("Sp1 Normal x1");
                    }
        } else {
            Speed = 1;
            display.print("Sp2 F16 (x1.6)");  
        }
        preferences.putBool(prefKeySpeed, Speed);
        display.display();
    }
        
        if (millis() - delai > 5000 && millis() - delai < 7000) {
            display.print("Config ");
        
        if (Oric1) {
            Oric1 = false;
            display.print(" Atmos");
        } else {
            Oric1 = true;
            display.print(" Oric 1");
        }
        // Sauvegarder la valeur Oric dans la mémoire flash
        preferences.putBool(prefKeyOric1, Oric1);
        display.display();
        }

        if (millis() - delai > 7000 && millis() - delai < 9000) {
            if (langage == 0) {
                display.print("Langage");
            } else {
                display.print("Language");
            }
            
        
        if (langage == 0) {
            display.print(" English");
            langage = 1;
            
        } else {
            display.print(" Francais");
            langage = 0;
        }
        // Sauvegarder la valeur langage dans la mémoire flash
        preferences.putChar(prefConfigKey, langage);
        display.display();
        }
        
        if (millis() - delai > 9000) {  // Reset et efface préférences
            preferences.clear();
            ESP.restart(); // Redémarre l'ESP32
        }

        if (millis() - delai < 1000) {
            
         // Gérer les niveaux de son
         if (NiveauSon == 0) {
          NiveauSon = 1;
          digitalWrite(nivSonQ1, LOW);
          digitalWrite(nivSonQ2, HIGH);
         } else if (NiveauSon == 1) {
           NiveauSon = 2;
           digitalWrite(nivSonQ1, LOW);
           digitalWrite(nivSonQ2, LOW);
         } else {
           NiveauSon = 0;
           digitalWrite(nivSonQ1, HIGH);
           digitalWrite(nivSonQ2, HIGH);
         }

        // Sauvegarder le niveau de son dans la mémoire flash
         preferences.putInt(prefKey, NiveauSon);
         displayNiveauSon();
    
        } 
        
    }
  
    int bits = 0;
    digitalWrite(SEND_PIN, HIGH); // Sortie à 1

    // Vérifie si le contact est fermé (début de transmission)
    if (digitalRead(START_PIN) == LOW)
    {
        receiving = true;
        configMode = false;
        startSignalCmd = false;
        firstBitDetected = false; // Réinitialise la détection du premier bit
        dataStarted = false;      // Réinitialise l'indicateur de début des données
        errorCount = 0;
        nbSynchro = 0;
        progressionPrecedente = -1; // Drapeau pour barre de progression
    }
    else
    {
        if (receiving)
        {
            // Fin de la transmission, sauvegarder les données sur la carte SD
            Serial.println(" Fin de la transmission, contact ouvert...");
            Serial.print("Error count = ");
            Serial.println(errorCount);
            affiche_pretReception();
            
            // display.display();
            delay(1000);

            if (!erreur && buffer[1] == 0x16)   //1 Sauvegarde fichier sur la carte SD
            {
                saveDataToSD();
            }

            if (buffer[1] == 0x5b) {            // Réception octets de commande, formatage du buffer
                int index = 0;
                for (int x = 1; x<17; x++) {    //1 à 17
                    if (buffer[x] == 0x5d) {
                        commandek7[index++] = 0x00;
                    } else {
                        commandek7[index++] = (char)buffer[x];
                    }
                    
                }
    
                bufferIndex = 0;
                
                memset(buffer, 0x16, 259);
                bufferIndex = 259;
                buffer[bufferIndex] = 0x24;
                bufferIndex +=10;
                for (int i = 1; i < 17; i++) {
                buffer[bufferIndex++] = commandek7[i];
                }
                buffer[bufferIndex] = 0x00;
                cmdRoutineK7 = true;
                String nom = findNameInBuffer(buffer,bufferIndex);    
                // Serial.println(nom);
            }

            erreur = false;
            bufferIndex = 0;
            nbSynchro = 1;
            indexPause = 0;
        }
        receiving = false;
        
    }

    // Si on est en train de recevoir des données
    if (receiving)
    {           
        // nomRecuTermine = false;
        // Serial.println("Receiving...");
        // Attendre que l'entrée passe à l'état haut
        while (digitalRead(DATA_PIN) == LOW)
        {
                    delayMicroseconds(delaiSignal); // Petit délai pour stabiliser le signal            
        }
        
        // Mesurer le début de la période
        unsigned long startTime = micros();
        digitalWrite(PERIOD_LED_PIN, HIGH); // Allumer la LED de période au début de la période

        // Attendre que l'entrée repasse à l'état bas
        while (digitalRead(DATA_PIN) == HIGH && digitalRead(START_PIN) == LOW)   //&& digitalRead(START_PIN) == LOW
        {
                    delayMicroseconds(delaiSignal); // Petit délai pour stabiliser le signal
        }

        // Attendre que l'entrée repasse à l'état haut
        while (digitalRead(DATA_PIN) == LOW && digitalRead(START_PIN) == LOW)    //&& digitalRead(START_PIN) == LOW
        {
            delayMicroseconds(delaiSignal); // Petit délai pour stabiliser le signal            
        }

        if (digitalRead(START_PIN) == HIGH)
        { // Fin de transmission
            delay(1000);
            bitDuration = TimerSpeed * 2;  // 416
        }

        // Mesurer la fin de la période
        unsigned long endTime = micros();
        bitDuration = endTime - startTime;
        if (Start && bitMdulation > 1 && (bitDuration > 10 && bitDuration < 500)) {    // on mesure le TimerSpeed à la preière transmission ou réception il reste ainsi tant qu'on a pas rebooté
                if (bitDuration > 370) {    // Détection ROM
                    TimerSpeed = 208;
                } else {
                    TimerSpeed = 0xB4; // 0xB4 bitDuration / 2;
                    delaiSignal = (4.9 * TimerSpeed) / 100;
                    Speed = 1;
                }
                Start = false;
                // Serial.println(bitDuration);
        }
        digitalWrite(PERIOD_LED_PIN, LOW); // Éteindre la LED de période à la fin de la période
        int T1mini = (TimerSpeed * 2) - (((TimerSpeed * 2) * 19) / 100);
        int T0mini = (TimerSpeed * 3) - (((TimerSpeed * 3) * 19) / 100);
        int T1maxi = (TimerSpeed * 2) + (((TimerSpeed * 2) * 19) / 100);
        int T0maxi = (TimerSpeed * 3) + (((TimerSpeed * 3) * 20) / 100);
        // Vérifier si la période est valide avant de commencer à compter les bits
        if (!firstBitDetected)
        {
            if (bitDuration < T1mini || bitDuration > 1100) //390
            {
                // Si la première période n'est pas valide, ignorer et continuer
                return;
            }
            firstBitDetected = true;
        }

        // Détection du début des données
        if (!dataStarted && bitDuration >= T0mini && bitDuration <= 1100)  //500 - 690
        {
            // Bit 0 détecté (début des données)
            
            dataStarted = true;
            bitCount = 0;
            receivedByte = 0;
            bitMdulation = 0;
            digitalWrite(DATA_LED_PIN, HIGH); // Allumer la LED de données au début des données
            // delayMicroseconds(1);
            digitalWrite(DATA_LED_PIN, LOW);
        }
        else
        {
            bitMdulation++;
            // TimerSpeed = bitDuration / 2;
            if (bitMdulation > 9 && CopyK7 == false)
            {
                // envoyer le prg vers l'Oric
                if (Start) {    // on mesure le TimerSpeed à la première transmission ou réception il reste ainsi tant qu'on a pas rebooté
                if (bitDuration > 370) {
                    TimerSpeed = 208;
                } else {
                    TimerSpeed = 0xB4; //0xB4 bitDuration / 2;
                    delaiSignal = (4.9 * TimerSpeed) / 100;
                    Speed = 1;
                }
                Start = false;
                }

                delay(250);
                
                Serial.println(" ");
                Serial.print("Timer speed : ");   // affichage de la vitesse de transfert qui a été configurée sur le via 6522 de l'Oric
                Serial.print(bitDuration / 2);   // TimerSpeed
                Serial.println(" ");
                if (digitalRead(START_PIN) == LOW) {
                    resendFromSD();
                }
                
                bitMdulation = 0;
            }
            if (bitMdulation >= 6 && bitMdulation <= 7 && CopyK7 == false)
            {
                indexPause = bufferIndex;
            }
        }

        // Réception des bits de données
        if (dataStarted)
        {
            int octetTime = micros();
            for (int i = 0; i < 8; i++)
            {
                // Mesurer le début de la période
                startTime = micros();
                digitalWrite(PERIOD_LED_PIN, HIGH); // Allumer la LED de période au début de la période
                delayMicroseconds(delaiSignal);     // Petit délai pour stabiliser le signal

                while (digitalRead(DATA_PIN) == HIGH)
                {
                    delayMicroseconds((TimerSpeed * 72) / 100); // (150) 72% de TimerSpeed. Petit délai pour stabiliser le signal                                  
                }
                
                // Attendre que l'entrée repasse à l'état haut
                while (digitalRead(DATA_PIN) == LOW)
                {
                    delayMicroseconds(delaiSignal); // Petit délai pour stabiliser le signal                    
                }

                // Mesurer la fin de la période
                endTime = micros();
                bitDuration = endTime - startTime;
                digitalWrite(PERIOD_LED_PIN, LOW); // Éteindre la LED de période à la fin de la période

                if (bitDuration >= TimerSpeed && bitDuration <= T1maxi)  //250 - 495
                {
                    // Bit 1 détecté
                    bits++;
                    receivedByte |= (1 << bitCount);
                }
                else //if (bitDuration >= 496 && bitDuration <= 750)  //590 - 655
                {
                    // Bit 0 détecté
                    // Ne rien faire, receivedByte reste inchangé
                } 
                digitalWrite(DATA_LED_PIN, HIGH); // Allumer la LED de données
                // delayMicroseconds(1);
                digitalWrite(DATA_LED_PIN, LOW);
                bitCount++;
            }
            // startTime = micros();
            bufferIndex++; 

            // Serial.print(" ");
            // Serial.print(bufferIndex);
            // Serial.print(":");
            // Serial.print(receivedByte);         

            buffer[bufferIndex] = receivedByte;
            

            receivedByte = 0;
            bitCount = 0;
            
            // Bit 9 (parité)
            // Mesurer le début de la période
            startTime = micros();
            digitalWrite(PERIOD_LED_PIN, HIGH); // Allumer la LED de période au début de la période

            while (digitalRead(DATA_PIN) == HIGH)
            {
                delayMicroseconds((TimerSpeed * 72) / 100); // (150) 72% de TimerSpeed. Petit délai pour stabiliser le signal                
            }
            
            // Attendre que l'entrée repasse à l'état haut
            
            while (digitalRead(DATA_PIN) == LOW)
            {
                delayMicroseconds(delaiSignal); // Petit délai pour stabiliser le signal                
            }

            // Mesurer la fin de la période
            endTime = micros();
            bitDuration = endTime - startTime;
            digitalWrite(PERIOD_LED_PIN, LOW); // Éteindre la LED de période à la fin de la période

            if (bitDuration >= TimerSpeed && bitDuration <= T1maxi)  //250-495
            {
                // Bit 1 détecté
                parity = 1;
            }
            else //if (bitDuration >= 540 && bitDuration <= 720) //590 - 660
            {
                // if (bitDuration < T1mini) {
                //     erreur = true;
                // }
                // Bit 0 détecté
                parity = 0;
            }

            // mesurer délai d'un octet (+ parité)
            octetTime = micros() - octetTime;
            octetTime = octetTime + (TimerSpeed *3) + (3 * (TimerSpeed *2));    // Tenir compte du bit de start et des 3 bits de stop en fonction de timerSpeed

            if (verifierPariteImpaire(bits, parity))
            {
                // parité ok
            }
            else
            {
                digitalWrite(DATA_LED_PIN, HIGH); // Allumer la LED de données
                digitalWrite(DATA_LED_PIN, LOW);
                errorCount++;
                if (TimerSpeed == 208) {
                    if (bufferIndex > 8) {  // 3
                    Serial.println(" Erreur de parité ! ");
                    Serial.print(bitDuration);
                    Serial.print(" bufferIndex : ");
                    Serial.println(bufferIndex); 
                    display.clearDisplay();
                    display.setCursor(0, 0);
                    if (langage == 0) {
                        display.println("Erreur communication");
                    } else {
                        display.println("Parity error");
                    }
                
                    display.print(buffer[bufferIndex]);
                    display.print(" ");
                    display.print(bits);
                    display.print(" ");
                    display.print(parity);
                    display.display();   
                    erreur = true;
                    Serial.print("Error count = ");
                    Serial.println(errorCount);
                    for (int i = 0; i < bufferIndex; i++) {
                        Serial.print(i);
                        Serial.print(":");
                        Serial.print(buffer[i]);
                        Serial.print(" ");
                    }
                    errorCount = 0;
                    delay(1000);
                    } else {
                        // buffer[bufferIndex] = 0x16;
                        // delayMicroseconds(10);
                    }
                    }                
                // }
            }

            if (!NameCload && TimerSpeed != 208 && buffer[2] != 16 && OrigineCload == "") {   // == 58 appel programme par CLOAD ":nomprg" sous ROM modifiée
                if (bufferIndex == 1) {
                    fileNameFromBuffer = "";
                    OrigineCload = "";
                }
                if (bufferIndex == 2) {
                    if (buffer[2] == 58) {
                        // rien
                    } else {
                        fileNameFromBuffer = char(buffer[2]);
                    }
                }
                if (buffer[bufferIndex] == 0) {
                    // Serial.println(fileNameFromBuffer);
                    if (buffer[2] == 58) {
                        commande = 1;
                        NameCload = true;
                        OrigineCload = ":" + fileNameFromBuffer;    // garder le nom d'origine
                        fileNameFromBuffer = "?" + fileNameFromBuffer;
                    } else {
                        OrigineCload = fileNameFromBuffer;
                        NameCload = false;
                        commande = 0;
                    }
                    // Serial.println("OrigineCload : ");
                    // Serial.println(OrigineCload);
                }
                if (!NameCload && (bufferIndex > 2 && bufferIndex < 18)) {
                    fileNameFromBuffer = fileNameFromBuffer + char(buffer[bufferIndex]);
                }

                if (NameCload) {
                    
                    // Copier le contenu de OrigineCload dans commandek7
                    for (int i = 0; i < fileNameFromBuffer.length(); i++) {
                        commandek7[i] = fileNameFromBuffer.charAt(i);
                        // Serial.print(commandek7[i]);
                        // Serial.print(" ");
                    }
                    
                    // Remplir le reste avec des zéros si nécessaire
                    for (int i = fileNameFromBuffer.length(); i < 17; i++) {
                        commandek7[i] = 0x00;
                    }
                    fileNameFromBuffer = "";

                    // Réinitialiser le buffer et les index
                    bufferIndex = 0;
                    memset(buffer, 0x16, 259);
                    bufferIndex = 259;
                    buffer[bufferIndex] = 0x24;
                    bufferIndex += 10;

                    // Copier commandek7 dans le buffer
                    for (int i = 0; i < 17; i++) {
                        buffer[bufferIndex++] = commandek7[i];
                        // Serial.print(commandek7[i]);
                        // Serial.print(" ");
                    }
                    buffer[bufferIndex] = 0x00;

                    // Afficher le nom extrait du buffer
                    String nom = findNameInBuffer(buffer, bufferIndex);
                    // Serial.println("Name Cload = ");
                    // Serial.println(nom);

                    // Réinitialiser les variables
                    erreur = false;
                    bufferIndex = 0;
                    nbSynchro = 1;
                    indexPause = 0;
                    receiving = false;
                }


            }

            // Barre de progression
            if (bufferIndex > 300) {
                int pasBarreProgress = 30;
                int progress = (bufferIndex * 100) / tailleFichierRecu;
                if (progress != progressionPrecedente &&  progress % pasBarreProgress == 0) {
                  progressionPrecedente = progress;
                  globalProgress = progress;
                }
            }

            digitalWrite(DATA_LED_PIN, HIGH); // Allumer la LED de données
            // delayMicroseconds(1);
            digitalWrite(DATA_LED_PIN, LOW);

            if (bufferIndex == 5) {
                nomRecuTermine = false;
                afficheNom = true;
                nomRecu = "";
                progressionPrecedente = -1; // Drapeau pour barre de progression
            }

            if (leader == false && buffer[bufferIndex] == 0x24)  {
                leader = true;
                memset(buffer, 0x16, 259);
                // Serial.print("leader = true, bufferIndex = ");
                // Serial.println(bufferIndex);               
                bufferIndex = 259;  // 260
                buffer[259] = 0x24;
            }

            if (bufferIndex == 288) {
                adrdebut = 0;
                adfrfin = 0;
                adrRecDebutH = buffer[266];
                adrRecDebutL = buffer[267];
                adrRecFinH = buffer[264];
                adrRecFinL = buffer[265];
                adrdebut = (adrRecDebutH << 8) | adrRecDebutL;
                adfrfin = (adrRecFinH << 8) | adrRecFinL;
                tailleFichierRecu = adfrfin - adrdebut;
            }

            // if (leader == false) {
            //     Serial.print(" ");
            //     Serial.print(buffer[bufferIndex]);
            // }
            if (bufferIndex > 268 && bufferIndex < 286 && leader == true && !nomRecuTermine) {
                if (buffer[bufferIndex] != 0 && bufferIndex < 286) {
                    nomRecu += char(buffer[bufferIndex]);
                } else {
                    if (buffer[bufferIndex] == 0) {
                    nomRecuTermine = true;
                    afficheNom = false;
                    }
                }
            }
            

            if (leader == false && buffer[bufferIndex] == 0x16)  {
               nbSynchro++;
            }
           
            if (bufferIndex == 9 && buffer[9] == 0x16)      // == 4 && CopyK7 == false
            { // Affichage réception
                int pause = micros();
                digitalWrite(DATA_LED_PIN, HIGH);
                display.clearDisplay();
                display.setCursor(0, 0);
                display.println("Reception...");
                display.display();
                int Taffich = micros() - pause;
                int pauseTotale = ((Taffich + octetTime -1) / octetTime);
                // Serial.print("Taffich ");
                // Serial.println(Taffich);
                // Serial.print("octetTime ");
                // Serial.println(octetTime);
                // Serial.print("pauseTotale ");
                // Serial.println(pauseTotale);
                while ((micros() - pause) < ((pauseTotale * octetTime))) // Pause de X x octetTime
                {                                  // correspondant à la réception de 3 octets 0x16
                                                   // le temps d'afficher "Réception"
                }
                // while ((micros() - pause) < 21130) // Pause de 21 ms
                // {                                  // correspondant à la réception de 3 octets 0x16
                //                                    // le temps d'afficher "Réception"
                // }
                // for (int i = 0; i < 3; i++)        //3 On remet dans le buffer les 0x16 perdus pendant l'affichage
                // {
                //     buffer[bufferIndex++] = 0x16;
                // }
                // bufferIndex = bufferIndex + pauseTotale;
                nbSynchro = nbSynchro + pauseTotale;
                digitalWrite(DATA_LED_PIN, LOW);
            }
            bits = 0;
            bitCount = 0;
            dataStarted = false; // Prêt pour la prochaine série de données            
        }
    }
}

// Sauvegarde sur carte SD
void saveDataToSD()
{
    Serial.println("");
    // Serial.print("Timer Speed = ");
    // Serial.println(TimerSpeed);
    Serial.println("Sauvegarde ");
    Serial.print("Index buffer ");
    Serial.println(bufferIndex);
    Serial.print("Chemin SD : ");
    Serial.println(cheminSd);
    Serial.print("Nbre synchros : ");
    Serial.println(nbSynchro);
    Serial.print("Cload : ");
    Serial.println(Cload);
    Serial.print("Buffer[1] : ");
    Serial.println(buffer[1]);
    Serial.print("Dir : ");
    Serial.println(dir);
    nbSynchro = 0;
    lastChemin = "";
    selectedIndex = 0;
    displayStartIndex = 0;
    nomRecuTermine = false;
    nomRecu = "";
    afficheNom = false;
    // afficheur == false;
    confirmed = false; // autorisation d'écrire
    // Trouver le nom dans le buffer
    String nom;
    if (buffer[1] == 0x16 && !Cload) {
        nom = findNameInBuffer(buffer, bufferIndex);
    }
    if (Cload) {
        nom = fileNameFromBuffer;
    }
    Serial.print("nom = ");
    Serial.println(nom);
    
    if (commande == 1)
    {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("Preparation...");
        display.display();
        sequenceDetect();
        while (digitalRead(START_PIN) == HIGH && digitalRead(bouton) == HIGH)
            {
                // vérifier si sequentiel est vraie et si on fait joystick gauche ou droit pour incrémenter ou décrémenter seq pour la suite
                if (analogRead(xVal) < 1000 && !mini && SeqCount > 1) { // gauche (-)
                    if (setSeq > 1 ) {
                        setSeq--;
                        Serial.println(" setseq -- (save) : ");
                        Serial.print(setSeq);
                        delay(200);
                    }
                } 
                if (analogRead(xVal) > 4000 && !mini && SeqCount > 1) { // droite (+)
                    if (setSeq < SeqCount ) {
                        setSeq++; 
                        Serial.print(" setseq ++ (save) : ");
                        Serial.println(setSeq);
                        delay(200);
                    }
                }
                if (analogRead(yVal) < 1000 && !mini && SeqCount > 1) { // haut (options)
                    
                Options();

                }
                
                attenteCload(setSeq, SeqCount);
                display.display();
            }
        // display.print(SeqCount);
        // if (SeqCount > 1) {
        //     setSeq++;
        // }
        
        if (digitalRead(bouton) == LOW)
        {
            commande = 0;
        }
        
    }
    else if (bufferIndex > 0 && nom != "")
    {
        // Serial.print("Nom trouvé : ");
        // Serial.println(fileNameFromBuffer);

        // Vérifier si les 8 premiers caractères sont des espaces
        bool allSpaces = true;
        for (int i = 0; i < 8; i++)
        {
            if (nom.charAt(i) != ' ')
            {
                allSpaces = false;
                break;
            }
        }

        // Vérifier si un point est présent dans les 9 premiers caractères
        int dotIndex = nom.indexOf('.');
        bool hasDot = (dotIndex >= 0 && dotIndex < 9);

        String fileName;
        if (allSpaces)
        {
            // Utiliser uniquement les caractères suivants et appliquer l'extension ".bin"
            fileName = nom.substring(8) + ".bin";
        }
        else if (hasDot)
        {
            // Utiliser les 3 caractères suivants le point pour déterminer l'extension
            String extension = nom.substring(dotIndex + 1, dotIndex + 4);
            fileName = nom.substring(0, dotIndex) + "." + extension;
        }
        else
        {
            // Utiliser les 8 premiers caractères et appliquer l'extension ".TAP"
            fileName = nom.substring(0, 8) + ".TAP";
        }

        
        file.close();
        delay(50);
        // Serial.println("Dir : ");
        // Serial.println(dir);
        Serial.println("Filename ");
        Serial.println(fileName);
        
        if (SD.exists("/" + cheminSd + "/" + fileName) && !dir && !StopCload)
        {
            delay(500);
            if (ajoutSeq == false) {
                
                timeOut = millis();
                while (digitalRead(bouton) == HIGH && (millis() - timeOut) < confirmationTimeout)
                {
                    display.clearDisplay();
                    display.setCursor(0, 0);
                    if (langage == 0) {
                    display.print("Fichier existant !");
                    display.setCursor(0, 10);
                    display.println("Remplacer ?");
                    display.print("Confirmez +3s ");
                    } else {
                    display.print("File already exist !");
                    display.setCursor(0, 10);
                    display.println("Remplace ?");
                    display.print("Confirm +3s ");
                    }
                    
                    display.print((confirmationTimeout / 1000) - ((millis() - timeOut) / 1000));
                    display.display();
                }
                // waitingForConfirmation = true;
                buttonPressTime = millis();
                while (digitalRead(bouton) == LOW && millis() - buttonPressTime < 3000)
                {

                }                
                // if (waitingForConfirmation) {
        
                    if (millis() - buttonPressTime >= buttonPressDuration && millis() - timeOut < confirmationTimeout) {
                        display.clearDisplay();
                        display.setCursor(0, 10);
                        if (langage == 0) {
                            display.print("Fichier remplace");
                        } else {
                            display.print("File stored");
                        }
                        
                        display.display();
                        delay(1500);
                        confirmed = true;
                    } else {
                        display.clearDisplay();
                        display.setCursor(0, 10);
                        if (langage == 0) {
                            display.println("Demande annulee !");
                        } else {
                            display.println("Canceled !");
                        }
                        
                        display.display();
                        confirmed = false;
                        delay(2000);
                    }
                
                } else {
                        
                    confirmed = true; // Si ajoutSeq est vrai, on confirme automatiquement
                }
        }
        else
        {
            confirmed = true;
        }

        if (dir | StopCload) {
            confirmed = false;
        }
        if (confirmed)
        {
            //Sauvegarde sur la carte SD
            File dataFile = SD.open("/" + cheminSd + "/" + fileName, ajoutSeq ? FILE_APPEND : FILE_WRITE);
            if (dataFile)
            {   
                delay(50);
                
                Serial.println("Ecriture sur carte SD");
                // for (int i = 0;i < bufferIndex +1; i++) {
                //     Serial.print(i);
                //     Serial.print("=");
                //     Serial.print(buffer[i]);
                //     Serial.print(" ");
                // }
                if (ajoutSeq == true) {
                    Serial.println("Ajout séquence");
                }
                int x = 0;
                // if (nbSynchro < 255) {
                //     x = 10;
                // } else {
                //     x = 255;
                // }
                while (buffer[x] != 0x24)
                {
                    x++;
                }
                // Serial.print("x = ");
                // Serial.println(x);
                if (x > 4) {
                    buffer[x-1] = 0x16;
                    buffer[x-2] = 0x16;
                    buffer[x-3] = 0x16;
                    buffer[x-4] = 0x16;
                    x = x-4;
                } else {
                    // buffer[0] = 0x16;
                    // buffer[1] = 0x16;
                    // buffer[2] = 0x16;
                    // buffer[3] = 0x16;
                }
                
                Serial.println(" ");
                for (int i = x; i < bufferIndex + 1; i++) // on garde 4 octets 0x16
                {
                    // Serial.print(i);
                    // Serial.print(":");
                    dataFile.write(buffer[i]);
                    // Serial.print(buffer[i]);
                    // Serial.print(" ");
                    delayMicroseconds(10);
                }
                delay(50);
                dataFile.close();
                delay(50);
                listFilesAndDirectories();
                Serial.printf(" Nb octets reçus : %d ", bufferIndex);
                Serial.println("Fichier sauvegardé sur la carte SD");
                display.clearDisplay();
                display.setCursor(0, 0);
                if (langage == 0) {
                    display.println("Sauvegarde OK !");
                } else {
                    display.println("Saved !");
                }
                // dataFile.close();
                // display.clearDisplay();
                display.setCursor(0, 9);
                display.println(nom);
                display.print("SD/");
                display.print(cheminSd);
                display.print("/");
                display.println(fileName);
                 display.println(bufferIndex);
                display.setCursor(90, 23);
                if (langage == 0) {
                   display.println("Octets.");
                } else {
                    display.println("Bytes.");
                }
                display.display();
                delay(500);
                memset(buffer,0,BUFFER_SIZE);   // efface le buffer
                bufferIndex = 0;
            }
            else
            {
                Serial.println("Erreur d'écriture sur la carte SD !");
                display.clearDisplay();
                display.setCursor(0, 0);
                if (langage == 0) {
                    display.println("Erreur carte SD !");
                } else {
                    display.println("SD card error !");
                }
                
                display.display();
                delay(5000);
            }
        }
        else
        {
            
            affiche_pretReception();
        }
        ajoutSeq = false;
        nom = "";
        leader = false;
        fileNameFromBuffer = "";
        OrigineCload = "";
        
    }
}


// Vérification de la parité
bool verifierPariteImpaire(int bits, int parity)
{
    // Calculer le bit de parité attendu
    bool pariteAttendue = (bits % 2 == 0) ? 1 : 0;

    // Comparer avec le bit de parité reçu
    return parity == pariteAttendue;
}

// Envoi d'un bit sur la GPIO 5
void sendBit(bool bitValue)
{
    if (Oric1) {
        bit1H = 190;    // délai état Haut bit 1
        bit1L = 226;    // délai état Bas bit 1
        bit0H = 370;    // délai état Haut bit 0
        bit0L = 254;    // délai état Bas bit 0
    }
    if (!Oric1) {
        bit1H = 171;
        bit1L = 203;
        bit0H = 333;
        bit0L = 227;
    }
    if (Speed == 1) {
        bit1H = 50; // 60
        bit1L = 50; // 60
        bit0H = 315; // 318
        bit0L = 215; // 218
    }
    if (TimerSpeed != 208) {    // Vitesse FSP Fast Speed avec ROM modifiée
        bit1H = 48;  //50 48 TimerSpeed;
        bit1L = 48;  //50 48 TimerSpeed;
        if (RLE) {
            bit0H = 93;  //93 200 RLE
            bit0L = 93;  //93 200 RLE
        } else {
            // if (pauseAffich) {
            //     bit0H = 450;  // Pause affichage
            //     bit0L = 450;  // 
            // } else {
                bit0H = 70;  //70 70 110  135 (TimerSpeed *3) / 2;
                bit0L = 70;  //70 70 110  135 (TimerSpeed *3) / 2;
            // }
        }      
    }
    if (bitValue)
    {
        digitalWrite(SEND_PIN, HIGH); // Période bit 1
        delayMicroseconds(bit1H);
        digitalWrite(SEND_PIN, LOW);
        delayMicroseconds(bit1L);
        digitalWrite(SEND_PIN, HIGH);
    }
    else
    {
        digitalWrite(SEND_PIN, HIGH); // Période bit 0
        delayMicroseconds(bit0H);
        digitalWrite(SEND_PIN, LOW);
        delayMicroseconds(bit0L);
        digitalWrite(SEND_PIN, HIGH);
    }
}

// Envoi d'un bit sur la GPIO 5 pour le joystick
void sendBitJSK(bool bitValue)
{
    
        int bit1H = 190;    // délai état Haut bit 1
        int bit1L = 226;    // délai état Bas bit 1
        int bit0H = 370;    // délai état Haut bit 0
        int bit0L = 254;    // délai état Bas bit 0
    
    if (TimerSpeed != 208) {    // Vitesse FSP Fast Speed avec ROM modifiée
        bit1H = 50;     // 50
        bit1L = 50;     // 50
        bit0H = 75;    // 110
        bit0L = 75;    // 110
    }

    if (bitValue)
    {
        digitalWrite(SEND_PIN, HIGH); // Période bit 1
        delayMicroseconds(bit1H);
        digitalWrite(SEND_PIN, LOW);
        delayMicroseconds(bit1L);
        digitalWrite(SEND_PIN, HIGH);
    }
    else
    {
        digitalWrite(SEND_PIN, HIGH); // Période bit 0
        delayMicroseconds(bit0H);
        digitalWrite(SEND_PIN, LOW);
        delayMicroseconds(bit0L);
        digitalWrite(SEND_PIN, HIGH);
    }
}

// Envoi de la séquence de bits de stop
void sendStopSequence()
{
    uint8_t nStop;
    if (Speed == 1 || TimerSpeed != 208) {
        nStop = nStopF16;   // 3 ou nStopF16 si vitesse F16
    } else {
        nStop = 3;
    }
    
    for (uint8_t x = 0; x < nStop; x++) {
        sendBit(1);
    }
}
// Envoi des 3 bits de stop pour directory
void sendStopSequenceDir()
{
    uint8_t nStopDir;
    if (Speed == 1) {
        nStopDir = 8;
    } else {
        nStopDir = 3;
    }
    for (uint8_t x = 0; x < nStopDir; x++) {
        sendBit(1);
    }
}

// Envoi position Joystick
void posJoystick()
{
    display.clearDisplay();
    display.setCursor(0,0);
    display.print(" Joystick Mode");
    if (AnalogicJoy) {
        display.print(" A");
    }
    display.setCursor(0,10);
    display.print("    ON");   
    display.setCursor(0,20); 
    if (langage == 0) {
        display.print("Bouton pour quitter");
    } else {
        display.print("Button to exit");
    }
                   
    display.display();
    while (digitalRead(bouton) == LOW)
    {
        // attendre que le bouton soit relaché
    }
    
    delay(200);
    int data = 0;
    int delaiSignal = 0;    // mesure le délai du signal, si > 6 ms on quitte
    
    while (digitalRead(bouton) == HIGH) { 

     while (digitalRead(DATA_PIN) == HIGH) {
        // attente signal de l'Oric
     }
     delaiSignal = millis();
     while (digitalRead(DATA_PIN) == LOW || millis() - delaiSignal < 6)
     {
        // mesure le délai du signal, si > 6 ms on quitte sinon on envoie la lecture du joystick
     }
    delaiSignal = millis() - delaiSignal;
        
    if (digitalRead(bouton) == LOW || delaiSignal > 6) { // le délai est supérieur à 6 ms (correspond à un POKE 768,63)
          break;
    }

    int jy = analogRead(yVal);
    int jx = analogRead(xVal);
    int jfire = digitalRead(fire);
    int jvalid = digitalRead(valid);
    
    // Serial.println(jy);
    if (!AnalogicJoy) {
        if (jy > 4000) {    // bas 172
            data = 251;
        }
        if (jy < 1000) {    // haut 83
         data = 247;
        }
        if (jx > 4000) {    // droite 86
            data = 254;
        }
        if (jx < 1000) {    // gauche 89
            data = 253;
        }
        if (jy > 4000 && jx > 4000) {    // bas + doite 88
            data = 245;
        }
        if (jy < 1000 && jx < 1000) {    // haut + gauche 102
            data = 252;
        }
        if (jx > 4000 && jy < 1000) {    // haut + droite 91
            data = 250;
        }
        if (jx < 1000 && jy > 4000) {    // bas + gauche 90
            data = 249;
        }
        if ((jy > 1000 && jy < 4000) && (jx > 1000 && jx < 4000)) {  // 85
            data = 239;
        }
    } 
    if (AnalogicJoy) {
        if (xy == false) {
            data = jx * 0.0308;
            xy = true;
        } else {
            data = (jy * 0.0308) + 128;
            xy = false;
        }
    }

    if (jfire == LOW) {     // 170  bouton select
        data = 255;
    }
    if (jvalid == LOW) {    // 169 bouton tir
        data = 127;
    }
    
    for (int x = 0; x <= 2; x++) {
        sendBitJSK(1);
    }
    sendBitJSK(0);
    if (TimerSpeed != 208) {   // Si ROM modifiée on inverse les bits de data pour accélérer le transfert
            data = 255 - data;
    }
    for (int i = 0; i <= 7; i++)
        { // Envoi des bits du LSB au MSB
            bool bit = ((data >> i) & 1);
            sendBitJSK(bit);
        }

    if (TimerSpeed == 208) {    // si ROM modifiée on ignore le bit de parité
        // Calcul et envoi du bit de parité
        uint8_t parity = 1;
        for (int i = 0; i < 8; i++)
        {
            parity ^= (data >> i) & 1;
        }
        // sendBit(parity);
        sendBitJSK(parity);
    }
    
    if (AnalogicJoy) {
        delay(2);
    }
    // Serial.print("Data : ");
    // Serial.println(data);

    }
    while (digitalRead(bouton) == LOW)
    {
        // attendre que le bouton soit relaché
    }
    delay(200);
    display.clearDisplay();
    display.setCursor(0,0);
    if (langage == 0) {
        display.print("attente reception");
    } else {
        display.print("waiting for reception");
    }
    display.setCursor(0,15);
    display.print("joystick OFF");              
    display.display();
}

// Renvoi des données depuis la carte SD
void resendFromSD()
{
    const uint8_t sequence0[] = {0x16, 0x16, 0x24};
    const uint8_t sequence1[] = {0x16, 0x16, 0x16, 0x24};
    const uint8_t sequence2[] = {0x16, 0x16, 0x16, 0x16, 0x24};
    const int sequenceLength0 = sizeof(sequence0);
    const int sequenceLength1 = sizeof(sequence1);
    const int sequenceLength2 = sizeof(sequence2);
    int sequenceCount = 0;
    int sequenceIndexes[99]; // Pas plus de 99 séquences
    int currentIndex0 = 0;
    int currentIndex1 = 0;
    int currentIndex2 = 0;
    afficheNom = true;  // Flag pour indiquer de ne pas afficher le nom reçu dans la barre de progression
    lastChemin = "";
    selectedIndex = 0;
    displayStartIndex = 0;
    // digitalWrite(DATA_LED_PIN, HIGH);
    // Serial.print(fileNameFromBuffer);
    Serial.println("");
    Serial.println("Lecture ");
    String fileName = fileNameFromBuffer;
    String nom = "";
    Serial.print("commande = ");
    Serial.println(commande,HEX);
    
    if (commande == 1)
    {
        File dataFile = SD.open("/" + cheminSd + "/" + fileName, FILE_READ);
        if (!dataFile)
        {
            Serial.println("Erreur : Fichier introuvable sur la carte SD.");
            commande = 0;
            display.clearDisplay();
            display.setCursor(0, 10);
            if (langage == 0) {
                display.println("Fichier introuvable !");
            } else {
                display.println("File not found !");
            }
            if (TimerSpeed != 208)  {   // débloquer CLOAD si ROM+
                commande = 12;
                StopCload = true;
            }


            display.display();
            delay(3000);
            display.clearDisplay();
            display.display();
            return;
        } else {
            StopCload = false;
        }

        int progress = 0;
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("Preparation...");
            // if (langage == 0) {
            //     display.println("Envoi en cours...");
            // } else {
            //     display.println("Sending ...");
            // }
        // if (TimerSpeed == 208) {
        //     updateProgressBar(progress);
        // }
        
        // updateProgressBar(progress);

        // Détecter le nombre de séquences comprenant la suite 0x16 0x16 0x16 0x24 ou 0x16 0x16 0x16 0x16 0x24 dans dataFile
        // mémoriser l'index de début de chaque séquence
        while (dataFile.available())
        {
            uint8_t data = dataFile.read();
            if (data == sequence0[currentIndex0])
            {
                currentIndex0++;
                if (currentIndex0 == sequenceLength0)
                {
                    sequenceIndexes[sequenceCount] = dataFile.position() - sequenceLength0;
                    sequenceCount++;
                    currentIndex0 = 0;
                }
            }
            else
            {
                currentIndex0 = 0;
            }

            if (data == sequence1[currentIndex1])
            {
                currentIndex1++;
                if (currentIndex1 == sequenceLength1)
                {
                    sequenceIndexes[sequenceCount] = dataFile.position() - sequenceLength1;
                    sequenceCount++;
                    currentIndex1 = 0;
                }
            }
            else
            {
                currentIndex1 = 0;
            }

            if (data == sequence2[currentIndex2])
            {
                currentIndex2++;
                if (currentIndex2 == sequenceLength2)
                {
                    sequenceIndexes[sequenceCount] = dataFile.position() - sequenceLength2;
                    sequenceCount++;
                    currentIndex2 = 0;
                }
            }
            else
            {
                currentIndex2 = 0;
            }
        }

        // Afficher le nombre de séquences trouvées et leurs index de début
        Serial.print("Nombre de séquences trouvées : ");
        Serial.println(sequenceCount);
        int seqMax = sequenceCount;
        int endIndex = 0;
        
        for (int i = 0; i < sequenceCount; i++)
        {
            Serial.print("Index de début de la séquence ");
            Serial.print(i + 1);
            Serial.print(" : ");
            Serial.println(sequenceIndexes[i]);
        }

        // Réinitialiser le fichier pour le lire à nouveau
        dataFile.seek(0);

        if (setSeq > 0) {
            if (!Sequentiel | (lectureOPT == 2)) {
                sequenceCount = setSeq; // si pas en mode séquentiel
            }
            // setSeq = setSeq - 1;
            Serial.print(" Séquence lue : ");
            Serial.print(setSeq);
        } else {
            setSeq = 1;
        }

        display.clearDisplay();
        display.setCursor(0, 0);
        
        if (langage == 0) {
             display.println("Envoi en cours...");
          } else {
             display.println("Sending ...");
        }
        // if (TimerSpeed == 208) {
        //     updateProgressBar(progress);
        // }
        
        // int StartFile = 0;

        for (int seq = setSeq - 1; seq < sequenceCount; seq++)
        {
            Serial.print(" seq lue : ");
            Serial.print(seq);
            Serial.println(" ");
            indexBuffer = 256;  // 256
            // Serial.println("Lecture timer");
            // BitTimer(); // détecttion du bitTimer définit dans le via 6522

            // Remplir les 259 premiers octets avec 0x16
            memset(buffer, 0x16, 256);

            // Transférer dans buffer les datas qui se trouvent entre la séquence actuelle et la suivante (si elle existe, sinon on transfère jusqu'à la fin du fichier)
            int startIndex = sequenceIndexes[seq];
            // int endIndex = 0; // (seq + 1 < sequenceCount) ? sequenceIndexes[seq + 1] : dataFile.size();
            // Serial.println(seq);
            // Serial.println(seqMax);
            if (seq >= (seqMax - 1)) {
                endIndex = dataFile.size();
            } else {
                endIndex = sequenceIndexes[seq + 1] - 1;
            }
            dataFile.seek(startIndex);
            Serial.print(" Start index : ");
            Serial.print(startIndex);
            Serial.print(" End index : ");
            Serial.print(endIndex);

            while (dataFile.position() < endIndex)  // && dataFile.available()
            {
                uint8_t data = dataFile.read();
                buffer[indexBuffer] = data;
                indexBuffer++;
                // Serial.print(" ");
                // Serial.print(data);
                // Serial.print(" ");
                // Serial.print(indexBuffer);
            }

            Serial.print(" FindNameinBuffer ");
            
            // Trouver le nom dans le buffer
            nom = findNameInBuffer(buffer, indexBuffer);
            tailleNom = tailleNom + nbSynchro + 10; //269; // détermine à quel endroit il faut envoyer les 6 ou 7 bits de check

            Serial.print(" Nom trouvé : ");
            Serial.println(nom);
            Serial.print(" Nb octets : ");
            Serial.print(indexBuffer);
            Serial.print(" Index pause : ");
            Serial.println(tailleNom);

            // Détection et conversion des adresses de début et de fin
            int adrDebutHaut = buffer[nbSynchro + 7];  // 266
            int adrDebutBas = buffer[nbSynchro + 8];  // 267
            int adrDebut = (adrDebutHaut << 8) | adrDebutBas;

            int adrFinHaut = buffer[nbSynchro + 5];  // 264
            int adrFinBas = buffer[nbSynchro + 6];  // 265
            int adrFin = (adrFinHaut << 8) | adrFinBas;
            
            int tailleFichier = adrFin - adrDebut;
            int indexFin_fichier = tailleNom + tailleFichier;
            int idBufRelatif = 1;

            if (execMode == 1) {
                buffer[nbSynchro + 4] = 0xC7;   // mode Auto
            }
            if (execMode == 2) {
                buffer[nbSynchro + 4] = 0x00;   // mode non Auto
            }
            // digitalWrite(DATA_LED_PIN, HIGH);
            display.clearDisplay();
            display.setCursor(0, 0);
            if (langage == 0) {
                display.println("Envoi en cours...");
            } else {
                display.println("Sending ...");
            }
            
            display.print(seq+1);
            display.print("/");
            display.println(sequenceCount);
            display.print(nom);
            display.print(" ");
            display.print(tailleFichier / 1024);
            if (langage == 0) {
                display.print("Ko");
            } else {
                display.print("kB");
            }
            
            display.display();
            int progress = 0;
            // if (TimerSpeed == 208) {
            //     updateProgressBar(progress);
            // }
            
            // digitalWrite(DATA_LED_PIN, LOW);

            // Affichage des adresses sur le terminal
            Serial.print("Adresse de début : ");
            Serial.println(adrDebut);
            Serial.print("Adresse de fin : ");
            Serial.println(adrFin);
            Serial.print("Taille du fichier : ");
            Serial.println(tailleFichier);
            Serial.print("Index fin de fichier : ");
            Serial.println(indexFin_fichier);
            Serial.print("Index buffer : ");
            Serial.println(indexBuffer);

            // trouverOctetLePlusFrequent(indexFin_fichier);
            // trouverSequencesRepetees(indexFin_fichier);

            progressionPrecedente = -1; // Drapeau pour barre de progression

            sendStopSequence();
            sendBit(1);
            int pasBarreProgress =  10; // 30   pas de la barre de progreession en pourcentage
            int StartFile = millis();   // Mesurer le délai de transfert

            for (int idbuf = 250; idbuf < indexFin_fichier + 2; idbuf++)   // 1
            {               // Envoi des données + bit de parité impaire
                RLE = false;
                if (TimerSpeed != 208 && idbuf > 280) {
                    if (buffer[idbuf - 1] == buffer[idbuf]) {
                        RLE = true;
                    }
                }

                sendBit(0); // Bit de start
                int data = buffer[idbuf];
                if (TimerSpeed != 208) {   // Si ROM modifiée on inverse les bits de data pour accélérer le transfert
                    // Serial.print(" ");
                    // Serial.print(data);
                    data = 255 - data;
                }
                if (!RLE) {
                    for (int i = 0; i <= 7; i++)
                    { // Envoi des bits du LSB au MSB
                        bool bit = ((data >> i) & 1);
                        sendBit(bit);
                    }
                }
                RLE = false;

                // Barre de progression
                if (TimerSpeed !=208 && idbuf > 300) {
                    OrigineCload = "";
                    int progress = (idbuf * 100) / indexBuffer;
                    if (progress != progressionPrecedente &&  progress % pasBarreProgress == 0) {
                    progressionPrecedente = progress;
                    globalProgress = progress;
                    sendBit(1);
                    }
         
                //  if (TimerSpeed == 208 && indexBuffer >= indexFin_fichier) {
                //     memset(buffer,0,BUFFER_SIZE);   // efface le buffer
                //  }
                }

                if (TimerSpeed == 208) {    // si ROM modifiée on ignore le bit de parité
                    // Calcul et envoi du bit de parité
                    uint8_t parity = 1;
                    for (int i = 0; i < 8; i++)
                    {
                     parity ^= (data >> i) & 1;
                    }
                    sendBit(parity);
                }
                
                
                // Envoi des bits de stop en fonction de la parité de idbuf
                if (idbuf % 2 == 1)
                {
                    sendStopSequence(); // Envoi de 3 bits de stop si idbuf est impair
                    if (Speed == 0) {
                        sendBit(1); // Envoi d'un bit de stop suplémentaire
                    }
                    
                    if (idbuf == tailleNom)
                    { // si on a atteint 270 octets + le nom d'origine de l'Oric alors on ajoute une séquence de stop suplémentaire
                        sendStopSequence();
                        // if (Speed == 1 | (Oric1 && Speed == 0)) {
                            for (int x = 1; x < 20; x++) {
                            sendBit(1); 
                        }
                        // } 
                    }
                    
                }
                else
                {
                    sendStopSequence();
                    if (idbuf == tailleNom)
                    { // si on a atteint 270 octets + le nom d'origine de l'Oric alors on ajoute une séquence de stop suplémentaire
                        sendStopSequence();
                        // if (Speed == 1 | (Oric1 && Speed == 0)) {
                            for (int x = 1; x < 20; x++) {
                            sendBit(1); 
                        }
                        // }
                    }
                }
                // Barre de progression
                if (TimerSpeed == 208) {
                    int progress = (idbuf * 100) / indexBuffer;
                    if (progress != progressionPrecedente && progress % pasBarreProgress == 0) {
                    progressionPrecedente = progress;
                    // updateProgressBar(progress);
                    globalProgress = progress;
                    }
                }
                if (digitalRead(bouton) == LOW) {
                    idbuf = indexBuffer;
                }
                
            }

            Serial.print("Chrono : ");
            Serial.print((millis() - StartFile) / 1000);
            Serial.println(" sec.");

            if (Speed == 1) {
                delay(600);
            }
            // if (TimerSpeed != 208 && NameCload == true) {
            //     delay(500);
            // }
           
            if (digitalRead(bouton) == LOW || lectureOPT == 2) {     // on arrête la lecture
                seq = sequenceCount;    
            }
            // Serial.println(" lectureOpt : ");
            // Serial.print(lectureOPT);
            // Serial.println(" ");
            digitalWrite(DATA_LED_PIN, LOW);
            if ((lectureOPT != 2 && digitalRead(START_PIN) == HIGH && seq + 1 != sequenceCount) || (lectureOPT == 3 && digitalRead(START_PIN) == LOW && seq + 1 != sequenceCount)) {  // | (lectureOPT == 3 && digitalRead(START_PIN) == LOW && seq + 1 != sequenceCount)
            affichePause(seq + 1, sequenceCount); // afficher la pause
            
            while (digitalRead(START_PIN) == HIGH && digitalRead(bouton) == HIGH)
            {
                
                if (analogRead(xVal) < 1000 && !mini) { // gauche (-)
                    if (seq >= 0 ) {
                        seq--;
                        Serial.println(" seq-- (resend): ");
                        Serial.print(seq);
                        Serial.println(" ");
                        affichePause(seq + 1, sequenceCount);
                        delay(200);
                    }
                } 
                if (analogRead(xVal) > 4000 && !mini) { // droite (+)
                    if (seq < (sequenceCount -2)) {
                        seq++;
                        Serial.println(" seq++ (resend): ");
                        Serial.print(seq);
                        Serial.println(" ");
                        affichePause(seq + 1, sequenceCount);
                        delay(200);
                    }
                } 
                if (analogRead(yVal) < 1000 && !mini && sequenceCount > 1) { // haut (options)
                    
                        Options();
                        affichePause(seq + 1, sequenceCount);
                        delay(200);
                }
            }
            if (lectureOPT == 3) {
                while (digitalRead(fire) == HIGH && digitalRead(bouton) == HIGH)   // pause, si appui bouton ou fire joystick on continue
                {
                   
                if (analogRead(xVal) < 1000 && !mini) { // gauche (-)
                    if (seq >= 0) {
                        seq--;
                        affichePause(seq + 1, sequenceCount);
                        delay(200);
                    }
                } 
                if (analogRead(xVal) > 4000 && !mini) { // droite (+)
                    if (seq < (sequenceCount - 2)) {
                        seq++;
                        affichePause(seq + 1, sequenceCount);
                        delay(200);
                    }
                } 
                if (analogRead(yVal) < 1000 && !mini && sequenceCount > 1) { // haut (options)
                    
                        Options();
                        affichePause(seq + 1, sequenceCount);
                        delay(200);
                }
                }
                
            }
            }         
        execMode = 0;
        }

        // Serial.print("Chrono : ");
        // Serial.print((millis() - StartFile) / 1000);
        // Serial.println(" sec.");

        lectureOPT = 1;
        Sequentiel = false;
        
        dataFile.close();
        if (TimerSpeed != 208) {
            memset(buffer,0,BUFFER_SIZE);   // efface le buffer
        }
        
        dir = false;
        catal = false;
        Cload = false;
        Joystick = false;
        nom = "";
        NameCload = false;
        OrigineCload = "";
        while (digitalRead(bouton) == LOW)
        {
            delay(200);
        }
        
    }
    else
    {
        if (TimerSpeed != 208) {
            if (OrigineCload == "SET") {
                commande = 10;
            }
            else if (OrigineCload == "JOYSTICK") {
                commande = 11;
            }
            else if (OrigineCload != "" && OrigineCload != "DIR" && !OrigineCload.startsWith(":")) {
                commande = 12;
            }
        }
        if (commande == 0)
        { // copie du programme DIR dans le buffer
            if (!dir && (OrigineCload == "" || OrigineCload == "DIR")) {
                if (!dirAlt && !Set) {
                    memset(buffer,0,BUFFER_SIZE);   // efface le buffer
                    transfert_dir_buffer();
                    routK7 = false;
                    
                } else {
                    if (!Set) {
                        transfert_Setvide_buffer();   // pré-charger settings dans le buffer
                    } else {
                        if (Joystick) {
                            transfert_joyVide_buffer(); // précharger jostick dans le buffer
                        } else {
                            transfert_vide_buffer();  // pré-charger les noms du directory
                        }
                        
                    }
                    
                    routK7 = true;
                    dirAlt = false;
                }
                
            } else {
                if (!routK7) {
                    transfert_routk7_buffer();
                }
                // if (Oric1) {
                //     dir = false;
                // }
            }
        }
        if (commande == 2)
        { // envoyer la page du catalogue
            listFilesAndDirectories();
            transfert_pageDir_buffer(); // copie du catalogue dans le buffer
        }
        if (commande == 3)
        { // copie du programme DIR dans le buffer
            // commande = 0;
            // transfert_dir_buffer();
            listFilesAndDirectories();
            transfert_pageDir_buffer();
            commande = 0;
        }
        if (commande == 4)  // Commande pour afficher la page DIR suivante
        {
            transfert_pageDir_buffer();
        }
        if (commande == 5)  // Commande pour afficher les séquences d'un fichier
        {
            // fileNameFromBuffer = nom;
            transfert_infoTAP_buffer();
        }
        
         if (commande == 10) {
            transfert_set_buffer();
            commande = 0;
            OrigineCload = "";
            // StopCload = true;
            Set = false;
        }
         if (commande == 11) {
            transfert_joystick_buffer();
            commande = 0;
            Set = false;
            Joystick = false;
            dir = false;
        }
        if (commande == 12) {
            transfert_notFound_buffer();
            commande = 0;
            Set = false;
            Joystick = false;
            dir = false;
        }
    }

    if (commande != 1 && digitalRead(START_PIN) == LOW) {
     // Trouver le nom dans le buffer
     nom = findNameInBuffer(buffer, indexBuffer);

     if (nom == "ROUTK7") {
        dir = false;
     }

     tailleNom = tailleNom + 269; // détermine à quel endroit il faut envoyer les 6 ou 7 bits de check +269

     Serial.print(" Nom trouvé : ");
     Serial.println(nom);
     Serial.print(" Nb octets : ");
     Serial.print(indexBuffer);
     Serial.print(" Index pause : ");
     Serial.println(tailleNom);

     digitalWrite(DATA_LED_PIN, HIGH);
     display.clearDisplay();
     display.setCursor(0, 0);
     if (langage == 0) {
        display.println("Envoi en cours...");
     } else {
        display.println("Sending...");
     }
     
     display.println(" ");
     display.println(nom);
     display.display();
     digitalWrite(DATA_LED_PIN, LOW);

     // Détection et conversion des adresses de début et de fin
     int adrDebutHaut = buffer[266]; //266
     int adrDebutBas = buffer[267];  //267
     int adrDebut = (adrDebutHaut << 8) | adrDebutBas;

     int adrFinHaut = buffer[264];   //264
     int adrFinBas = buffer[265];    //265
     int adrFin = (adrFinHaut << 8) | adrFinBas;
     int tailleFichier = adrFin - adrDebut;
     int indexFin_fichier = tailleNom + tailleFichier;
     int idBufRelatif = 1;

     // Affichage des adresses sur le terminal
     Serial.print("Adresse de début : ");
     Serial.println(adrDebut);
     Serial.print("Adresse de fin : ");
     Serial.println(adrFin);
     Serial.print("Taille du fichier : ");
     Serial.println(tailleFichier);
     Serial.print("Index fin de fichier : ");
     Serial.println(indexFin_fichier);
     Serial.print("Index buffer : ");
     Serial.println(indexBuffer);

    //  indexBuffer = indexBuffer -200;

    // if (TimerSpeed == 208 && nom == "SET" && indexFin_fichier > 300) {
    //     int progress = 0;
    //     updateProgressBar(progress);
    // }
    progressionPrecedente = -1; // Drapeau pour barre de progression

    sendStopSequence();
    sendBit(1);
    
     for (int idbuf = 250; idbuf < indexFin_fichier + 2; idbuf++)    //1    250
     {               // Envoi des données + bit de parité impaire
        RLE = false;
        
        if (TimerSpeed != 208 && idbuf > 280) {
            if (buffer[idbuf - 1] == buffer[idbuf]) {
                RLE = true;
            }
        }
         sendBit(0); // Bit de start
         int data = buffer[idbuf];
        //  Serial.print(data);
        //  Serial.print("=");

         if (TimerSpeed != 208) {   // Si ROM modifiée on inverse les bits de data pour accélérer le transfert
            data = 255 - data;
         }
        //  Serial.print(data);
        //  Serial.print(" ");
        if (!RLE) {
             for (int i = 0; i <= 7; i++)
         { // Envoi des bits du LSB au MSB
             bool bit = ((data >> i) & 1);
             sendBit(bit);
         }
        }
        RLE = false;
         if (TimerSpeed == 208) {
            // Calcul et envoi du bit de parité si ROM d'origine
            uint8_t parity = 1;  // 1
            for (int i = 0; i < 8; i++)
            {
                 parity ^= (data >> i) & 1;
            }
            sendBit(parity);
         }
         
        // Barre de progression
         if (TimerSpeed != 208 && nom == "SET" && indexFin_fichier > 300 && idbuf > 300) {
          int pasBarreProgress = 10;
          OrigineCload = "";
          int progress = (idbuf * 100) / indexBuffer;
         if (progress != progressionPrecedente &&  progress % pasBarreProgress == 0) {
            progressionPrecedente = progress;
            globalProgress = progress;
            sendBit(1);
            // updateProgressBar(progress);
         }
         
        //  if (indexBuffer >= indexFin_fichier) {
        //     memset(buffer,0,BUFFER_SIZE);   // efface le buffer
        //  }
         }

         // Envoi des bits de stop en fonction de la parité de idbuf
         if (idbuf % 2 == 1)
         {
             sendStopSequenceDir(); // Envoi de 3 bits de stop si idbuf est impair
             if (TimerSpeed == 208) {
                sendBit(1); // Envoi d'un bit de stop suplémentaire
             }
            
             if (idbuf == tailleNom)
             { // si on a atteint 270 octets + le nom d'origine de l'Oric alors on ajoute une séquence de stop suplémentaire
                 sendStopSequence();
                //  if (Speed == 1 | (Oric1 && Speed == 0)) {
                    for (int x = 1; x < 20; x++) { // 20
                    sendBit(1);
                 }
                //  }
             }
             
         }
         else
         {
             sendStopSequenceDir();
            
             if (idbuf == tailleNom)
             { // si on a atteint 270 octets + le nom d'origine de l'Oric alors on ajoute une séquence de stop suplémentaire
                 sendStopSequence();
                //  if (Speed == 1 | (Oric1 && Speed == 0)) {
                    for (int x = 1; x < 20; x++) {  // 20
                    sendBit(1);
                 }
                //  }
                
             }
         }
         
         // Barre de progression
         if (TimerSpeed == 208 && nom == "SET" && indexFin_fichier > 300 && idbuf > 280) {
          int pasBarreProgress = 10;
          OrigineCload = "";
          int progress = (idbuf * 100) / indexBuffer;
         if (progress != progressionPrecedente &&  progress % pasBarreProgress == 0) {
            progressionPrecedente = progress;
            // updateProgressBar(progress);
            globalProgress = progress;
         }
         
        //  if (indexBuffer >= indexFin_fichier) {
        //     memset(buffer,0,BUFFER_SIZE);   // efface le buffer
        //  }
         }
    }
    //  delay(600); 
    int finDir_delai = micros();
     if (nom == "DIR") {
        
        while (digitalRead(START_PIN) == 0 && (micros() - finDir_delai) < 15)   // 10
        {
            /* code */
        }
        finDir_delai = micros() - finDir_delai;
        Serial.print("Délai Dir : ");
        Serial.println(finDir_delai);
        if (finDir_delai < 10) {    // 6
            dir = true;
            Set = false;
            Joystick = false;
        } else {
            dir = false;
        }
        
        if (digitalRead(START_PIN) == LOW) {
            dirAlt = true;
        }
       }

     if (nom == "CATAL.BIN") {
        catal = true;
       }
    
     if (nom == "ROUTK7") {
        routK7 = true;
       }  
    }

    // if (nom =="SET" && !Oric1) {
    //     commande = 7;        
    //     Serial.print(" SET : commande = 7 ");
    //     return;
    // }

    if (nom == "DIR") {
        if (dir) {
            commande = 2;
        }
              
        } else {
            if (commande == 3) {
                 // ne rien faire
            } else {
            if (commande == 4 && page < ttPage - 1) {
                // ne rien faire
            } else {
               commande = 0;
            //    if (nom == "CATAL.BIN") {
            //     dir = true;
            //    }
               
            //    page = 0;
            } 
            commande = 0;
            // commande = 0;  // =0
            // if (nom == "ROUTK7") {
            //     dir = false;
            // }
        }

        
    }
    
    int finSet_delai= micros();
    if (OrigineCload == "SET" || (nom == "SET" && indexBuffer < 300)) {
        int tps = 50;
        int tpsSelect = 20;
        while (digitalRead(START_PIN) == 0 && (micros() - finSet_delai) < tps)   // 10
        {
            /* code */
        }
        finSet_delai = micros() - finSet_delai;
        Serial.print("Délai SET : ");
        Serial.println(finSet_delai);
        if (finSet_delai < tpsSelect || (TimerSpeed != 208 && OrigineCload == "SET")) {     // 6
            // Set = true;
            commande = 10;
        } else {
            Set = true;
            Joystick = true;
        }
        
    }

    uint16_t lim = 290;
    if (!Oric1) {
        lim = 290;
    } else {
        lim = 292;
    }
    if (OrigineCload == "JOYSTICK" || (nom == "JOYSTICK" && indexBuffer < lim)) {   //290
        while (digitalRead(START_PIN) == 0 && (micros() - finSet_delai) < 15)
        {
            /* code */
        }
        finSet_delai = micros() - finSet_delai;
        Serial.print("Délai JOY : ");
        Serial.println(finSet_delai);
        if (finSet_delai < 10 || (TimerSpeed != 208 && OrigineCload == "JOYSTICK")) {
            // Set = true;
            commande = 11;
            OrigineCload = "";
            Set = false;
            Joystick = false;
        } else {
            Set = true;
            Joystick = false;
        }
        
    }

    if (nom == "JOYSTICK" && indexBuffer > lim) {   //290
        commande = 0;
        Set = false;
        Joystick = false;
        dir = false;
        dirAlt = false;

        }
    
    if (nom == "!" && indexBuffer < lim && TimerSpeed != 208) {   //290
        Serial.print("!!! Not Found !!!");
        display.clearDisplay();
        display.print("!!! Not Found !!!");
        display.display();
        delay(1500);
        commande = 0;
        OrigineCload = "";
        NameCload = false;
        Set = false;
        Joystick = false;
        dir = false;
        dirAlt = false;
        }
        
    if (nom == "CATAL.BIN" && Oric1) {
        dir = false;
    }

    if (nom.startsWith(":") && TimerSpeed == 208) {          // Détection du nom du fichier à charger suite à CLOAD":nom"
        // Serial.println(originalFiles[0]);
        // fileNameFromBuffer = nom.substring(1);
        int tps = 50;
        int tpsSelect = 35;
        // if (Oric1) {
        //     tps = 50;
        //     tpsSelect = 15;
        // }
        while (digitalRead(START_PIN) == LOW && (micros() - finSet_delai) < tps)
        {
            /* code */
        }
        finSet_delai = micros() - finSet_delai;
        Serial.print("Délai Cde (:) : ");
        Serial.println(finSet_delai);
        if (finSet_delai < tpsSelect) {
            // Set = true;
            fileNameFromBuffer = nom.substring(1); // Prendre les caractères suivants
            // fileNameFromBuffer = "?" +  fileNameFromBuffer;
            commande = 1;
            Set = false;
            Joystick = false;
            Cload = true;
        Serial.print("chargement ");
        Serial.print(fileNameFromBuffer);
        } else {
            Set = true;
        }
        
    }

    if (nom.startsWith("::") && TimerSpeed == 208) {
        Set = false;
        Cload = false;
        Joystick = false;
        commande = 0;
        display.clearDisplay();
        display.setCursor(0, 15);
        display.println("Fichier introuvable !");
        display.display();
        delay(3000);
    }
    
}
