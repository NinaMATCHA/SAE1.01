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
    unsigned sousChoix; // Sous choix lorsqu'on est dans les differents menus
    unsigned cChangeDifficulte;

    menuMain(); // affiche l'écran de bienvenue
    do {

        cin >> choix;
        switch (choix) {
        case 1:
            menuHistoire();
            cin >> sousChoix;
            if (sousChoix == 1) {
                HISTOIRE();
                cin.ignore();
                cout << "Appuyez sur entree pour continuer.";
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
                //PVP(); --> lance le mode pvp
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
                // INFINI(); --> lance le mode infini
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
            else if (sousChoix == 2) {
                credits();
                cin.ignore();
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
