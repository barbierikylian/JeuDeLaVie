# *Projet POO (C++) - Le Jeu de la Vie de Conway*

---

## **Introduction**

Le **jeu de la vie** est un automate cellulaire conçu par le mathématicien John Conway. Il simule l'évolution d'une population de cellules vivantes et mortes dans une grille. À chaque étape, l'état de chaque cellule est déterminé par des règles simples basées sur son voisinage immédiat.

### **Règles du Jeu**
1. Une **cellule morte** (0) ayant **exactement 3 voisines vivantes** (1) devient vivante.
2. Une **cellule vivante** (1) :
   - Reste vivante si elle a **2 ou 3 voisines vivantes**.
   - Meurt (0) si elle a **moins de 2** ou **plus de 3** voisines vivantes.

---

## **Fonctionnalités du Programme**

1. **Simulation Console :**
   - Lit un fichier texte d’entrée décrivant la grille initiale (taille et état des cellules).
   - L'utilisateur a le contrôle de l'évolution de la population car il a la possibilité de choisir le nombre d’itérations.
   - Sauvegarde les états après chaques itérations dans un fichier de sortie.

2. **Simulation Graphique :**
   - Affiche l’évolution des cellules dans une fenêtre graphique.
   - La durée entre deux itérations est ajustable.

---

## **Format d'Entrée**

Le programme consomme un fichier texte contenant :
- **Taille de la grille** : `hauteur largeur` (par ex. `5 10`).
- **Grille initiale** : Une matrice de `0` (mort) et `1` (vivant).

Exemple :

![image](https://github.com/user-attachments/assets/3af71cec-c9f2-4148-bb3b-667a90ee79b1)


## **Utilisation**

### **Compilation**
Pour exécuter le programme, assurez-vous que votre environnement dispose d’un compilateur **C++** et que la bibliothèque **SFML** est installée.

Pour compiler :

```bash
make
```
