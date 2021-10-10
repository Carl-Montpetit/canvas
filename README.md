# TP1: Dessiner sur un canevas ASCII"

---

## Description

### Description générale du projet, des détails et le contexte du projet

- **Cours** : Construction et maintenance de logiciels
- **Sigle** : INF3135
- **Enseignant** : Serge Dogny
- **Université** : UQAM

Le projet consiste à construire un programme qui permet de dessiner sur un canvas préalablement acquis par l'entrée standard ou explicitement crée via des fonctionnalités implémentés. On peut soit dessiner des lignes, des cercles ou des rectangles avec des pixels de diverts couleurs. En dépend des options utilisés en ligne de commande il est possible de dessiner des formes différentes et couleur différente en dépend de la couleur du crayon (option -p). 

### Un lien vers le sujet

- https://gitlab.info.uqam.ca/montpetit.carl/inf3135-automne2021-tp1/-/blob/master/sujet.md

## Auteur

Carl Montpetit (MONC08069000)

## Fonctionnement

### Explication du fonctionnement

- Le programme permet de dessiner sur un canvas créer par le programme ou passer par entrée standard.

- Pour le compiler il suffit de faire la commande  `make ./canvascii`
- Pour l'exécuter il suffit de faire la commande `./canvascii` suivis des options désirés et valides
- Les formats d'entrée et de sortie sont 
  - `stdout` : sortie standard
  - `stdin` : entrée standard
  - `stderr` : canal d'erreur standard

## Tests

### Explication du fonctionnement et du résultat des tests

Pour lancer la suite de tests il suffit de taper la commande  `make test` ce qui va lancer la ligne de commande `bats check.bats` du fichier Makefile du projet, mais il ne faut surtout pas oublier d'enlever préalablement le `skip` en haut de chacun des tests du fichier `check.bats` sinon les tests ne seront pas exécutés. 

Si les test échouent, c'est seulement car l'implémentation n'a pas été complété avec le temps impartie.

Le résultat obtenu est le suivant :

-  ✓ With no argument, shows help
   ✓ Creating an empty 3x2 canvas
   ✓ Maximum allowed size is 40x80
   ✓ Loading and prints an empty 5x8 canvas
   ✓ Using all pens between 0 and 7
   ✓ Drawing horizontal line on 5x8 canvas with option -h
   ✓ Drawing vertical line on 5x8 canvas with option -v
   ✓ Drawing rectangle on 5x8 canvas with option -r
   ✗ Drawing line on 5x5 canvas with option -l
   ✗ Drawing circle on 5x8 canvas with option -c
   ✗ Combining multiple options
   ✗ Drawing non diagonal segment
   ✗ Drawing large circle
   ✗ Clipping line from (1,1) to (5,8)
   ✗ Clipping circle of radius 3 centered at (3,3)
   ✗ Option -k is recognized
   ✓ Forbidding character # in canvas
   ✓ Canvas of 41 lines is too high
   ✓ Canvas of 81 columns is too wide
   ✓ Width must be uniform for all lines
   ✓ Unrecognized option -a
   ✓ Option -n must be provided with values
   ✓ Wrong value with option -p
   ✓ Wrong value with option -h
   ✓ Wrong value with option -v
   ✓ Wrong syntax with option -n
   ✓ Wrong dimensions with option -n
   ✓ Negative value with option -h is forbidden
   ✓ Negative value with option -v is forbidden
   ✗ Negative positions with option -r are allowed
   ✓ Negative dimensions with option -r are forbidden
   ✗ Negative positions with option -l are allowed
   ✗ Negative positions with option -c are allowed
   ✗ Negative radius with option -c is forbidden

  **34 tests, 12 failures**
  make: *** [test] Error 1

## Dépendances

> Indiquez les dépendances du projet, avec lien officiel. Il faudrait au moins
> mentionner GCC et [Bats](https://github.com/bats-core/bats-core). Utiliser une
> liste à puces pour donner la liste des dépendances.

- La commande `make ./casvascii` dépend de `canvascii.c` 
  - La commande `make ./canvascii` lance :
    - `gcc -g -o canvascii -std=c11-Wextra  canvascii.c `
- La commande `make test` dépend de `check.bats` 
  - La commande lance :
    - `bats check.bats`
- La commande `make clean` dépend de rien
  - La command lance : 
    - `rm canvascii *.o`
    - Efface tout les fichiers créés par la commande `make ./canvascii` et les fichier `.o` 

## Références

Aucunes références pour ce qui a été complété pour ce travail pratique. Le tout a été complété avec les connaissances et l'effort de l'auteur.

## État du projet

* [x] Le nom du dépôt GitLab est exactement `inf3135-automne2021-tp1` (Pénalité de
  **50%**).
* [x] L'URL du dépôt GitLab est exactement (remplacer `utilisateur` par votre
  nom identifiant GitLab) `https://gitlab.info.uqam.ca/utilisateur/inf3135-automne2021-tp1`
  (Pénalité de **50%**).
* [x] L'utilisateur `dogny_g` a accès au projet en mode *Developer*
  (Pénalité de **50%**).
* [x] Le dépôt GitLab est un *fork* de [ce
  dépôt](https://gitlab.info.uqam.ca/dogny_g/tp1-inf3135-a21)
  (Pénalité de **50%**).
* [x] Le dépôt GitLab est privé (Pénalité de **50%**).
* [x] Le dépôt contient au moins un fichier `.gitignore`.
* [ ] Le fichier `Makefile` permet de compiler le projet lorsqu'on entre
  `make`. Il supporte les cibles `html`, `test` et `clean`.
  - Il manque seulement la cible `html`.
  - Manque de temps pour compléter.
* [x] Le nombre de tests qui réussissent/échouent avec la `make test` est
  indiqué quelque part dans le fichier `README.md`.
* [x] Les sections incomplètes de ce fichier (`README.md`) ont été complétées.
* [x] L'en-tête du fichier est documentée.
* [x] L'en-tête des déclarations des fonctions est documentée (*docstring*).
* [x] Le programme ne contient pas de valeurs magiques.

---
