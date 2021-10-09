# TP1: Dessiner sur un canevas ASCII"

---

## Description

> Décrivez ici le projet. Commencez d'abord par une description générale, puis
> donnez ensuite des détails. Indiquez le contexte dans lequel ce travail est
> accompli (cours, sigle, enseignant, université).

⚠️ **À remplir**⚠️

### Description générale du projet

### Des détails

### Le contexte du projet

- **Cours** : Construction et maintenance de logiciels
- **Sigle** : INF3135
- **Enseignant** : Serge Dogny
- **Université** : UQAM

### Un lien vers le sujet

Aussi, insérer un lien vers le [sujet du travail](sujet.md).

⚠️ **À remplir**⚠️

## Auteur

> Indiquez ici votre prénom et nom, puis votre code permanent entre parenthèses,
> sans mettre en gras ou en italique.

Carl Montpetit (MONC08069000)

## Fonctionnement

> Expliquez d'abord en mots comment faire fonctionner le projet (imaginez que la
> personne qui l'utilisera ne connaît pas C, ne connaît pas le projet et souhaite
> seulement saisir une série de commandes pour l'exécuter). En particulier,
> indiquez **les commandes** qui doivent être entrées pour la **compilation** et
> **l'exécution**.

### Explication du fonctionnement

⚠️ **À remplir**⚠️

- À quoi sert votre programme?
- Comment le compiler?
- Comment l'exécuter?
- Quels sont les formats d'entrées et de sorties?
- Quels sont les cas d'erreur gérés?

## Tests

> Expliquez ici comment lancer la suite de tests automatiques avec la commande
> `make test`, ainsi que le résultat que vous obtenez.

### Explication du fonctionnement et du résultat des tests

Pour lancer la suite de tests il suffit de taper la commande  `make test` ce qui va lancer la ligne de commande `bats check.bats` du fichier Makefile du projet, mais il ne faut surtout pas oublier d'enlever préalablement le `skip` en haut de chacun des tests du fichier `check.bats` sinon les tests ne seront pas exécutés. 

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

> Indiquez ici les références que vous avez utilisées pour compléter le projet,
> avec l'hyperlien vers la référence. Pas besoin de mentionner les diapositives
> du cours, mais si vous avez eu recours à un site d'aide, un fragment de code ou
> une discussion sur un forum, mentionnez-le.

Aucunes références pour ce qui a été complété pour ce travail pratique.

## État du projet

> Indiquez toutes les tâches qui ont été complétés en insérant un `X` entre les
> crochets. Si une tâche n'a pas été complétée, expliquez pourquoi (lors de la
> remise, vous pouvez supprimer ce paragraphe).

⚠️ **À terminer**⚠️

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
* [x] Le nombre de tests qui réussissent/échouent avec la `make test` est
  indiqué quelque part dans le fichier `README.md`.
* [ ] Les sections incomplètes de ce fichier (`README.md`) ont été complétées.
* [x] L'en-tête du fichier est documentée.
* [x] L'en-tête des déclarations des fonctions est documentée (*docstring*).
* [x] Le programme ne contient pas de valeurs magiques.

---
