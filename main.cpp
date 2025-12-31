#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <fstream>
#include "tp10.h"
#include "menu.h"

int main() {
  // maybe inclure qlq trucs directement dans leurs fonctions, qui ressortiront un int ?
  // aussi faire un unsigned "sousChoix" pour eviter les redondances ( a l'exception de changer difficulté ou on doit enregistrer le choix ig )
  //jme disais aussi faire un "entrée" suffit au lieu de 1 pour qlq endroits mais c des details d'opti )
    unsigned choix; // Choix dans le menu
    unsigned cHistoire; // Choix dans le mode histoire
    unsigned cPvp;  // Choix dans le mode pvp
    unsigned cInfini;  // Choix dans le mode infinie
    unsigned cOptions;  // Choix dans les options
    unsigned cCredits; // Choix dans les crédits
    unsigned cChangeDifficulte; // Choix pour la difficulte

    menuMain(); // affiche l'écran de bienvenue
    do {

        cin >> choix;
        switch (choix) {
        case 1:
            menuHistoire();
            cin >> cHistoire;
            if (cHistoire == 1) {
                HISTOIRE();
                break;
            }
            else if (cHistoire == 2) {
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
            cin >> cPvp;
            if (cPvp == 1) {
                //PVP(); --> lance le mode pvp
            }
            else if (cPvp == 2) {
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
            cin >> cInfini;
            if (cInfini == 1) {
                // INFINI(); --> lance le mode infini
            }
            else if (cInfini == 2) {
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
            cin >> cOptions;
            if (cOptions == 1) {
                changeDifficulte();
                cin >> cChangeDifficulte;
                if (cChangeDifficulte == 1) {
                    // modeFacil(); --> init une matrice "simple" pour tout les modes
                }
                else if (cChangeDifficulte == 2) {
                    // modeMoyen(); --> init une matrice "moyen" pour tout les modes
                }
                else if (cChangeDifficulte == 3) {
                    // modeDifficil(); --> init une matrice "dur" pour tout les modes
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
            else if (cOptions == 2) {
                credits();
                cin >> cCredits;
                if (cCredits == 1) {
                    menuMain();
                    continue;
                }
                else {
                    cout << "Erreur entrez 1";
                    return 1;
                }
            }
            else if (cOptions == 3) {
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
