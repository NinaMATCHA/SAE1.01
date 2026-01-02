#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <fstream>
#include "tp10.h"
#include "menu.h"

int main() {
    //jme disais aussi faire un "entrée" suffit au lieu de 1 pour qlq endroits mais c des details d'opti
    unsigned choix; // Choix dans le menu
    unsigned sousChoix; // Sous choix lorsqu'on est dans les différents menus
    unsigned cChangeDifficulte;
    unsigned maxTimes = 7;
    unsigned nbCandy = 5;

    menuMain(); // affiche l'écran de bienvenue
    do {

        cin >> choix;
        switch (choix) {
        case 1:
            menuHistoire();
            cin >> sousChoix;
            if (sousChoix == 1) {
                HISTOIRE();
                menuNiveaux();
                cin >> sousChoix;
                if (sousChoix == 1 && estJouableNiveau1 == true) {
                    afficherNIVEAU1();
                    niveau1();
                    menuNiveaux();
                    estJouableNiveau2 = true;
                }
                else if (sousChoix == 2 && estJouableNiveau2 == true) {
                    afficherNIVEAU2();
                    niveau2();
                    menuNiveaux();
                    estJouableNiveau3 = true;
                }
                else if (sousChoix == 3 && estJouableNiveau3 == true) {
                    afficherNIVEAU3();
                    niveau3();
                    menuNiveaux();
                    estJouableNiveau4 = true;
                }
                else if (sousChoix == 4 && estJouableNiveau4 == true) {
                    afficherNIVEAU4();
                    niveau4();
                }
                else {
                    cout << "Niveau pas encore debloque !" << endl;
                }
                break;
            }
            else if (sousChoix == 2) {
                menuMain();
                continue;
            }
            else {
                cout << "Erreur, entrez 1 ou 2" << endl;
                return 1;
            }
            break;
        case 2:
            menuPVP();
            cin >> sousChoix;
            if (sousChoix == 1) {
                play(maxTimes,nbCandy,true,false);
            }
            else if (sousChoix == 2) {
                menuMain();
                continue;
            }
            else {
                cout << "Erreur, entrez 1 ou 2" << endl;
                return 1;
            }
            break;
        case 3:
            menuINFINI();
            cin >> sousChoix;
            if (sousChoix == 1) {
                play(maxTimes,nbCandy,false,true);
            }
            else if (sousChoix == 2) {
                menuMain();
                continue;
            }
            else {
                cout << "Erreur, entrez 1 ou 2" << endl;
                return 1;
            }
            break;
        case 4:
            OPTIONS();
            cin >> sousChoix;
            if (sousChoix == 1) {
                changeDifficulte();
                cin >> cChangeDifficulte;
                if (cChangeDifficulte == 1) {
                    nbCandy = 4;
                    cout << "Difficulté changée en facile" << endl;
                }
                else if (cChangeDifficulte == 2) {
                    nbCandy = 6;
                    cout << "Difficulté changée en moyen" << endl;
                }
                else if (cChangeDifficulte == 3) {
                    nbCandy = 8;
                    cout << "Difficulté changée en difficile" << endl;
                }
                else if (cChangeDifficulte == 4) {
                    menuMain();
                    continue;
                }
                else {
                    cout << "Erreur, entrez 1, 2, 3 ou 4" << endl;
                    return 1;
                }
            }
            else if (sousChoix == 2) {
                credits();
                cin >> sousChoix;
                if (sousChoix == 1) {
                    menuMain();
                    continue;
                }
                else {
                    cout << "Erreur entrez 1";
                    return 1;
                }
            }
            else if (sousChoix == 3) {
                menuMain();
                continue;
            }
            else {
                cout << "Erreur, entrez 1, 2 ou 3" << endl;
                return 1;
            }
            break;
        case 5:
            clearScreen();
            break;
        default:
            cout << "Erreur, entrez un choix parmis : 1, 2, 3, 4 ou 5" << endl;
            return 1;
        }
    } while(choix != 5);
    return 0;
}
