---
jupytext:
  text_representation:
    extension: .md
    format_name: myst
    format_version: 0.13
kernelspec:
  display_name: Python 3 (ipykernel)
  language: python
  name: python3
---

# Rapport de projet Image

*Les paragraphes en italique comme celui-ci vous donnent des
indications sur le contenu attendu; ils sont à supprimer une fois
votre rapport rédigé*

*Ce rapport pourra servir de support pour votre présentation orale*

*Soyez objectifs et factuels! Vous ne serez pas évalué sur ce que vous
affirmez, mais sur la pertinence et la justesse de ce que vous
affirmez.*

+++

## Auteurs

- SAR Lazim, lazim.sar@universite-paris-saclay.fr, L1 MI-1
- SADDEDINE Ismael, ismael.saddedine@universite-paris-saclay.fr, L1 MI-1

+++

## Résumé du travail effectué

*Pour chaque partie du sujet, décrire brièvement l'avancement de votre
projet. Exemples de réponses: «non traitée», «réalisée, documentée,
testée», «réalisée, sauf 2.3», «réalisée mais non testée», «réalisée
sauf 2.4 pour lequel notre programme ne compile pas». Pour les
questions «Aller plus loin» plus ouvertes, décrire plus en détail ce
que vous avez choisi de réaliser.*

*En plus du rapport, la documentation de chaque fonction dans le code
devra préciser son auteur et votre degré de confiance dans
l'implantation et les éléments factuels motivant cette confiance:
présence de tests, bogues et limitations connus, etc.*

- Partie 1: Actuellement, toutes les questions ont été traitées, réalisées et testées à l'aide du compilateur dans le terminal. Toutefois, testées sans le CHECK et pas vraiment documenté. J'ai seulement documenté les choses qui me semblaient plus difficles à visualiser et à expliquer.

- Partie 2: Toutes les questions ont été traitées, completées et testées à l'aide du dossier correction dans le dossier pgm. Elles ont été bien vérifiées et sont semblables. Comme la partie 1, j'ai documenté les choses qui me paraissaient intéressant et pertinent à expliquer.

- Partie 3: Presque toutes les questions ont été traitées, completées et testées si ce n'est les questions "Aller plus loin" excepté la fonction lissage qui a été faite et testée ( voir Rapport en bas part 4.) J'ai bien vérifié que les fichiers ont été crées grâce aux tests des fonctions complétées. Puis j'ai comparé les fichiers crées avec ceux de la correction et en utilisant le code du rapport ou de la partie 0 pour afficher une image PGM. Et j'ai bien vu que les images concordaient. Comme les autres parties, j'ai documenté les choses qui me semblaient complexes et importants à comprendre.

-  Partie 4: Toutes les questions ont été réalisées et testées.


- Partie 5: Toutes les questions ont été traitées, complétées et testée. J'ai bien compilé les fichiers comme dans la partie 4 avec le "make". Lors des tests de fonctions, il n'y a eu aucune erreur et les fichiers ont bien été génerés dans le dossier gris-couleurs qu'on a crée nous même au préalable. On a également pris une image sur Internet en format 512x512 et on a appliqué les fonctions et cela fonctionnait bien. Voir en bas. Et, j'ai également documenté les choses qui me paraissaient importants, intéressants ou difficiles.

  
- Partie 6: Actuellement, nous avons traité les questions de cette partie jusqu'à la question 6.6. On a bloqué à cette question. De plus, les questions complétées n'ont pas pu être testées car nous avons pas fini de completer la suite de la partie.

+++

## Démonstration

*Soutenez ce que vous affirmez dans la section précédente au moyen de
quelques exemples **bien choisis**. Vous pourrez par exemple compiler et
lancer certains de vos programmes, lancer des tests, afficher des images.*

*Ci-dessous, nous vous proposons un début de démonstration pour les différentes
parties*

*Ne gardez que des exemples pertinents qui mettent en valeur votre
travail. Inutile de perdre du temps sur le premier programme si vous
avez fait les suivants plus compliqués; l'auditeur se doutera bien que
vous avez réussi à le faire.*

+++

### Partie 1

*Les cellules commençant par `%%bash` sont interprétées comme des
commandes bash, comme dans un terminal* :

```{code-cell} ipython3
%%bash --login
clang++ pbm-affiche.cpp -o pbm-affiche
```

```{code-cell} ipython3
%%bash --login
./pbm-affiche
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("pbm/smiley-inverse.pbm")      # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("pbm/correction/smiley-inverse.pbm")      # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
%%bash --login
clang++ pbm-tout-en-un.cpp -o pbm-tout-en-un
```

```{code-cell} ipython3
%%bash --login
./pbm-tout-en-un
```

```{code-cell} ipython3
# Vérification d'une des images obtenues
from open_ppm import open_ppm               # importe la commande open_ppm fournie
im = open_ppm("pbm/code.pbm")               # charge l'image
im.resize((160, 160))                         # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# Vérification d'une des images obtenues
from open_ppm import open_ppm               # importe la commande open_ppm fournie
im = open_ppm("pbm/correction/code.pbm")               # charge l'image
im.resize((160, 160))                         # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
from open_ppm import open_ppm               # importe la commande open_ppm fournie
im = open_ppm("pbm/smiley.pbm")               # charge l'image
im.resize((80, 80))                         # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
from open_ppm import open_ppm               # importe la commande open_ppm fournie
im = open_ppm("pbm/correction/smiley.pbm")               # charge l'image
im.resize((80, 80))                         # affiche l'image avec une taille donnée
```

### Partie 2

```{code-cell} ipython3
%%bash --login
clang++ pgm-tout-en-un.cpp -o pgm-tout-en-un
```

```{code-cell} ipython3
%%bash --login
./pgm-tout-en-un
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("pgm/brain.pgm")               # charge l'image
im.resize((100, 68))                         # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("pgm/correction/brain.pgm")               # charge l'image
im.resize((100, 68))                         # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("pgm/brain-inverse.pgm")       # charge l'image
im.resize((100, 68))                         # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("pgm/correction/brain-inverse.pgm")       # charge l'image
im.resize((100, 68))                         # affiche l'image avec une taille donnée
```

### Partie 3

```{code-cell} ipython3
%%bash --login
clang++ sobel-tout-en-un.cpp -o sobel-tout-en-un
```

```{code-cell} ipython3
! ./sobel-tout-en-un
```

```{code-cell} ipython3

```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("sobel/Willis.512.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# Comparer avec l'image dand le dossier sobel correction
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("sobel/House.256.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("sobel/correction/House.256.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
%%bash --login
clang++ seuillage-tout-en-un.cpp -o seuillage-tout-en-un
```

```{code-cell} ipython3
! ./seuillage-tout-en-un
```

*Ajoutez des cellules et complétez avec les autres programmes implantés et images réalisées*

```{code-cell} ipython3
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage/Willis.512.pgm")       # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage_double/Willis.512.pgm")       # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage_double/iteratif_Willis.512.pgm")       # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage_double/iteratif_House.256.pgm")       # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage/Willis_lissee.512.pgm")       # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

### Partie 4

```{code-cell} ipython3
%%bash --login
make pgm-test
```

```{code-cell} ipython3
%%bash --login
./pgm-test
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("pgm/brain.pgm")       # charge l'image
im.resize((100, 68))                         # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
%%bash --login
clang++ sobel.cpp sobel-test.cpp pgm.cpp -o sobel-test
```

```{code-cell} ipython3
%%bash --login
./sobel-test
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("sobel/Willis.512.pgm")       # charge l'image
im.resize((100, 68))                         # affiche l'image avec une taille donnée
```

*Ajoutez des cellules et complétez avec les autres programmes implantés et images réalisées*

```{code-cell} ipython3
# Ici, on montre juste qu'on peut bien compiler et exécuter avec le make  
```

```{code-cell} ipython3
%%bash --login
make TIN
```

```{code-cell} ipython3
%%bash --login
./TIN -e images/Willis.512.pgm  partie4/Willis_sobel.pgm
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("partie4/Willis_sobel.pgm")       # charge l'image
im.resize((100, 100))     
```

### Partie 5

```{code-cell} ipython3
%%bash --login
make ppm-test
```

```{code-cell} ipython3
%%bash --login
./ppm-test
```

```{code-cell} ipython3
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("ppm/Willis.512.ppm")       # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("images/Willis.512.ppm")       # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("ppm/House.256.ppm")       # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
%%bash --login
make gris-couleurs-test
```

```{code-cell} ipython3
%%bash --login
./gris-couleurs-test
```

```{code-cell} ipython3
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("gris-couleurs/Willis.512.pgm")       # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("images/Willis.512.pgm")       # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# POUR ALLER PLUS LOIN PARTIE 5
```

```{code-cell} ipython3
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("gris-couleurs/Valo.pgm")       # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("images/Valo.ppm")       # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

### Partie 6

```{code-cell} ipython3
%%bash --login
make superpixel-test
```

```{code-cell} ipython3
%%bash --login
./superpixel-test
```

## Organisation du travail

*Décrire en quelques phrases comment vous vous êtes organisés pour
travailler sur le projet: nombre d'heures consacrées au projet,
répartition du travail dans le binôme, moyens mis en œuvre pour
collaborer, etc. Si vous avez bénéficié d'aide (en dehors de celle
de vos enseigants), précisez le.*



- Concernant l'organisation du travail pour le projet, on a procédé de cette manière : chacun de nous travaille en autonomie sur les parties et une fois que nous avons complété une partie, on se concerte. Ensuite, on met en commun nos travaux puis on compare et on discute. Autrement dit, nous avons fait une programmation côte à côte ( Chacun sur son poste et sur son code tout en échangeant sur comment procéder).
Cela nous permet de travailler vraiment sur le projet chacun de son côté et de comprendre les consignes et les questions attendues grâce à un fil conducteur). Et lorsqu'une personne bloque , alors on s'aide mutuellement et on explique donc le code qu'on s'est partagé. 

- Pour collaborer et échanger ensemble, nous avons utilisé des moyens de communications tels que : Discord ou Snapchat. La raison est que ces plateformes permettent de faire un partage écran en direct, ce qui est très pratique dans le cas où on veut discuter de quelque chose sur notre travail.

- Chacun de nous a consacré environ 4 h de travail en TP et 28 h en autonomie.
Et enfin , on a eu environ la même répartition de travail puisqu'on faisait les questions chacun de notre côté et après on mettait en commun et on corrigeait.

+++

## Prise de recul

*Décrire en quelques phrases les difficultés rencontrées, ce que vous
avez appris à l'occasion du projet, le cas échéant comment vous vous y
prendriez si vous aviez à le refaire.*


Concernant les diffcultés rencontrées lors du projet: 

- Parfois, nous avions des problèmes lors de la compréhension des consignes ou du code attendus. Mais alors pour y remedier, on s'aidait des autres fichiers disponibles comme les tests ou les documentations pour bien comprendre les attendus.

- Des problèmes de compilations: En effet, lors de l'exécution des fichiers, certains fichiers ne se créeait pas dans des dossiers ou prenait beaucoup de temps à se créer. Ce qui nous faisait croire à un sorte de  dysfonctionnement. Par conséquent, cela nous a pris pas mal de temps pour comprendre la source du problème.  Par exemple, avec le dossier sobel et certains fichiers.

-  Problème dans sobel-cpp et seuillage-tout-en-un: On avait dû copier et ajouter la fonction renormalize qui était à faire. lors de la question 3.1, quand on voulait exécuter, cela donnait une erreur. On a du implanté la fonction renormalize qui était a faire pour la q 3.2, dans la question 3.1 pour pouvoir exécuter et avoir les résultats attendus. Sans la fonction renormalize, on ne pouvait avoir l'image attendue pour cette question. On a dû l'implanter bien qu'elle n'était pas demandée.
On l'a bien evidemment intégré dans les tests.


Ce qu'on a appris : 

- On a appris à bien compiler des programmes et faire la compilation séparée. On a aussi appris à tester les fonctions et à repérer les erreurs pour ensuite deboguer le programme grâce aux messages d'erreurs du compilateur. On a appris qu'il ne fallait pas avoir peur de faire des erreurs mais plutôt de les utiliser à notre avantage et à apprendre justement de ces erreurs.

 Comment s'y prendre s'il  fallait le refaire:

- Au lieu d'utiliser une compilation simple et de copier-coller à chaque fois les fonctions réalisées, on pouvait faire plus rapide en utilisant une compilation séparée. Pour continuer, quand on bloque à une question, il ne faut pas hésiter se servir de tout ce qu'on a, dont les documentations du programme et les tests pour comprendre les attendus.

```{code-cell} ipython3

```
