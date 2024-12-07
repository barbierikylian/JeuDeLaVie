# *Projet POO (C++) - Le Jeu de la Vie de Conway*
![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=flat-square&logo=c%2B%2B&logoColor=white)
![SFML](https://img.shields.io/badge/SFML-008080?style=flat-square&logo=sfml&logoColor=white)
![POO](https://img.shields.io/badge/POO-Programmation%20Orientée%20Objet-blue?style=flat-square&logo=code&logoColor=white)



---

## **Introduction**

Le **jeu de la vie** est un automate cellulaire conçu par le mathématicien John Conway. Il simule l'évolution d'une population de cellules vivantes et mortes dans une grille. À chaque itération, l'état de chaque cellule est déterminé par des règles simples basées sur son voisinage immédiat.

### **Règles du Jeu**
1. Une **cellule morte** (0) ayant **exactement 3 voisines vivantes** devient vivante (1).
2. Une **cellule vivante** (1) :
   - Reste vivante si elle a **2 ou 3 voisines vivantes**.
   - Meurt (0) si elle a **moins de 2** ou **plus de 3** voisines vivantes.

---

## **Fonctionnalités du Programme**

1. **Lancement du jeu**
   - Upload le fichier ".txt" contenant la grille avec les cellules afin d'initialiser le jeu. 
   - Choix du mode de fonctionnement (Console / Graphique) 

2. **Affichage Console :**
   - Contrôle de l'évolution de la population car il a la possibilité de choisir le nombre d’itérations.
   - Sauvegarde les états après chaques itérations dans un fichier de sortie.

3. **Affichage Graphique :**
   - Affiche l’évolution des cellules dans une fenêtre graphique.
   - La durée entre deux itérations est ajustable.

---

## **Organisation des fichiers du Jeu**

- src/ : Fichiers sources (.cpp)
- include/ : Fichiers d'en-tête (.h)
- obj/ : Fichiers objets (.o)
- bin/ : Exécutable final (`jeuDeLaVie`)
- resources/ : Données (ex. `etat_initial.txt`)
- docs/ : Documentation (`README.md`, etc.)

---

## **Ok mais maintenant comment lancer le JEU ?**
Pour exécuter le programme, assurez-vous que votre environnement dispose d’un compilateur **C++** et que la bibliothèque **SFML** est installée.

Pour lancer le Jeu, il faut être dans le dossier "bin". Afin d'y accéder suivez les étapes indiquées :

```bash
1. cd jeuDeLaVie
2. cd bin
3. ./jeuDeLaVie
```
## **Si tu modifies comment mettre à jour le JEU ?**

Ce projet vous permet de modifier les règles ou le comportement du Jeu de la Vie selon vos envies. Pour apporter des modifications, éditez simplement les fichiers source du projet. Une fois vos changements effectués, vous pouvez recompiler et mettre à jour le programme en exécutant la commande suivante :

```bash
make
```

---
