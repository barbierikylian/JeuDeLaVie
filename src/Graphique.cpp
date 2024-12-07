#include "Graphique.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <thread>
#include <chrono>

Graphique::Graphique(JeuDeLaVie& jeu) : jeu(jeu) {}

bool Graphique::chargerEtatInitial(const std::string& cheminFichier) {
    std::cout << "Chargement de l'état initial depuis : " << cheminFichier << "\n";
    bool result = jeu.EtatInitial(cheminFichier);
    if (result) {
        std::cout << "État initial chargé avec succès.\n";
    } else {
        std::cerr << "Erreur : Impossible de charger l'état initial.\n";
    }
    return result;
}

void Graphique::lancer() {
    int tailleCellule = 10; // Taille d'une cellule en pixels
    int lignes = jeu.getGrille()->getLignes(); // Nombre de lignes de la grille
    int colonnes = jeu.getGrille()->getColonnes(); // Nombre de colonnes de la grille
    int delai = 500; // Délai entre chaque étape en millisecondes
    bool enPause = false; // Indique si la simulation est en pause

    // Création de la fenêtre de 800x800 pixels
    sf::RenderWindow fenetre(sf::VideoMode(800, 800), "Jeu de la Vie");

    // Définir la vue initiale pour correspondre à la grille
    sf::View vue(sf::FloatRect(0, 0, colonnes * tailleCellule, lignes * tailleCellule));
    fenetre.setView(vue);

    int iteration = 0; // Compteur d'itérations

    // Boucle principale de la fenêtre
    while (fenetre.isOpen()) {
        sf::Event evenement;
        while (fenetre.pollEvent(evenement)) {
            // Condition 1 : Fermer la fenêtre
            if (evenement.type == sf::Event::Closed) {
                fenetre.close(); // L'utilisateur a cliqué sur "fermer"
            }
            // Condition 2 : Gestion de la molette pour le zoom
            else if (evenement.type == sf::Event::MouseWheelScrolled) {
                if (evenement.mouseWheelScroll.delta > 0) {
                    // Roulement vers le haut -> Zoom avant
                    vue.zoom(0.9f);
                    std::cout << "Zoom avant.\n";
                } else if (evenement.mouseWheelScroll.delta < 0) {
                    // Roulement vers le bas -> Zoom arrière
                    vue.zoom(1.1f);
                    std::cout << "Zoom arrière.\n";
                }
                fenetre.setView(vue); // Appliquer les modifications de la vue
            }
            // Condition 3 : Gestion des touches du clavier
            else if (evenement.type == sf::Event::KeyPressed) {
                // Appuyer sur ESPACE pour mettre en pause ou reprendre la simulation
                if (evenement.key.code == sf::Keyboard::Space) {
                    enPause = !enPause; // Inverser l'état de pause
                    std::cout << (enPause ? "Simulation mise en pause.\n" : "Simulation reprise.\n");
                }
                // Appuyer sur "R" pour réinitialiser la simulation
                else if (evenement.key.code == sf::Keyboard::R) {
                    jeu.EtatInitial("etat_initial.txt"); // Réinitialise l'état initial de la grille
                    std::cout << "Simulation réinitialisée.\n";
                    iteration = 0; // Réinitialiser le compteur d'itérations
                }
                // Appuyer sur la FLÈCHE HAUT pour augmenter la vitesse de simulation
                else if (evenement.key.code == sf::Keyboard::Up) {
                    delai = std::max(100, delai - 100); // Réduire le délai (minimum 100 ms)
                    std::cout << "Vitesse augmentée, délai : " << delai << " ms\n";
                }
                // Appuyer sur la FLÈCHE BAS pour réduire la vitesse de simulation
                else if (evenement.key.code == sf::Keyboard::Down) {
                    delai += 100; // Augmenter le délai entre les étapes
                    std::cout << "Vitesse réduite, délai : " << delai << " ms\n";
                }
            }
        }

        fenetre.clear(); // Effacer le contenu précédent de la fenêtre
        afficherGrille(fenetre, tailleCellule); // Dessiner la grille actuelle

        // Afficher les informations sur la console
        std::cout << (enPause ? "[Pause] " : "[En cours] ")
                  << "Itération : " << iteration << "\n";

        fenetre.display(); // Mettre à jour la fenêtre

        // Si la simulation n'est pas en pause
        if (!enPause) {
            jeu.getGrille()->calculerProchainsEtats(); // Calculer les prochains états de la grille
            jeu.getGrille()->actualiserEtats(); // Mettre à jour les états actuels
            iteration++; // Incrémenter le compteur d'itérations
        }

        // Pause entre chaque étape de simulation (en fonction du délai)
        std::this_thread::sleep_for(std::chrono::milliseconds(delai));
    }
}




void Graphique::afficherGrille(sf::RenderWindow& fenetre, int tailleCellule) {
    // Récupérer le nombre de lignes et de colonnes de la grille
    int lignes = jeu.getGrille()->getLignes();
    int colonnes = jeu.getGrille()->getColonnes();

    // Affichage d'informations dans la console (debugging)
    std::cout << "Affichage de la grille : " << lignes << " x " << colonnes << std::endl;

    // Parcourir chaque cellule de la grille
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            // Créer un rectangle pour représenter une cellule
            // La taille est légèrement réduite (tailleCellule - 1) pour créer une séparation visuelle entre les cellules
            sf::RectangleShape cellule(sf::Vector2f(tailleCellule - 1, tailleCellule - 1));

            // Placer la cellule à la bonne position dans la fenêtre
            cellule.setPosition(j * tailleCellule, i * tailleCellule);

            // Définir la couleur de la cellule en fonction de son état (vivante ou morte)
            if (jeu.getGrille()->getCellule(i, j)->estVivante()) {
                cellule.setFillColor(sf::Color::White); // Cellule vivante = blanc
                std::cout << "Cellule vivante à (" << i << ", " << j << ")\n"; // Debugging
            } else {
                cellule.setFillColor(sf::Color::Black); // Cellule morte = noir
                std::cout << "Cellule morte à (" << i << ", " << j << ")\n"; // Debugging
            }

            // Dessiner la cellule dans la fenêtre
            fenetre.draw(cellule);
        }
    }
}


