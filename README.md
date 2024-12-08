# **Projet POO (C++) - Le Jeu de la Vie de Conway**  
![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=flat-square&logo=c%2B%2B&logoColor=white)  
![SFML](https://img.shields.io/badge/SFML-008080?style=flat-square&logo=sfml&logoColor=white)  
![POO](https://img.shields.io/badge/POO-Programmation%20Orientée%20Objet-blue?style=flat-square&logo=code&logoColor=white)  

---

## **Introduction**  
Le **jeu de la vie** est un automate cellulaire conçu par le mathématicien John Conway. Il simule l'évolution d'une population de cellules vivantes et mortes dans une grille. Ce projet repose sur la **programmation orientée objet (POO)** et utilise **SFML** pour l'affichage graphique.  

---

### **Règles du Jeu**  

1. **Cellule morte (0)** :  
   - Devient vivante (1) si elle a exactement **3 voisines vivantes**.  
2. **Cellule vivante (1)** :  
   - **Reste vivante** si elle a **2 ou 3 voisines vivantes**.  
   - **Meurt** (devient 0) si elle a moins de **2** ou plus de **3** voisines vivantes.  

---

## **Fonctionnalités**  

### **1. Initialisation**  
- Chargement d'un fichier texte (`.txt`) contenant la grille initiale.  
- Choix entre deux modes :  
  - **Mode console**  
  - **Mode graphique**  

### **2. Mode Console**  
- Contrôle manuel : saisissez le nombre d'itérations souhaitées.  
- Sauvegarde automatique : chaque état est sauvegardé dans un fichier de sortie.  

### **3. Mode Graphique**  
- Affichage en temps réel de l'évolution de la population dans une fenêtre graphique.  
- Ajustez la durée entre deux itérations directement dans le programme.  

---

## **Structure des fichiers**  

```plaintext
jeuDeLaVie/  
├── src/         # Fichiers sources (.cpp)  
├── include/     # Fichiers d'en-tête (.h)  
├── obj/         # Fichiers objets (.o)  
├── bin/         # Exécutable final (`jeuDeLaVie`)  
├── resources/   # Données initiales (ex. `etat_initial.txt`)  
└── docs/        # Documentation (ex. `README.md`)  
```

## **Installation et Exécution**  

### **Pré-requis**  
Avant de pouvoir exécuter le programme, assurez-vous que vous avez les pré-requis suivants installés sur votre machine :

1. **Compilateur C++** (compatible avec C++11 ou supérieur).  
2. **Bibliothèque SFML** (version 2.5 ou plus récente).

---

### **Étapes pour lancer le jeu**  

Suivez les étapes ci-dessous pour installer et lancer le jeu :

1. **Clonez le dépôt ou téléchargez les fichiers**  
   Si vous avez **git** installé, vous pouvez cloner le dépôt avec la commande suivante :
   ```bash
   git clone https://github.com/votre-depot/jeuDeLaVie.git  
   cd jeuDeLaVie
---


