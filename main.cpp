#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <fstream>
#include "jeu.h"
#include "menu.h"

//change a difficulté du jeu
unsigned changeDifficulte(unsigned choice){
    if (choice == 1){
        cout << "Difficulté changée en facile" << endl;
        return 5;
    }
    else if (choice == 2) {
        cout << "Difficulté changée en moyen" << endl;
        return 7;
    }
    cout << "Difficulté changée en difficile" << endl;
    return 9;
}

//gère les niveaux qui doivent se débloquer un par un
unsigned levelUnlock (unsigned choice, unsigned estJouable){
    if (choice == 1) {
        afficherNIVEAU1();
        estJouable = niveau1(play(6,4,false,false));
    }
    else if (choice == 2 && estJouable >= 2) {
        afficherNIVEAU2();
        estJouable = niveau2(play(8,6,false,false));
    }
    else if (choice == 3 && estJouable >= 3) {
        afficherNIVEAU3();
        estJouable = niveau3(play(9,7,false,false));
    }
    else if (choice == 4 && estJouable == 4) {
        afficherNIVEAU4();
        estJouable = niveau4(play(11,9,false,false));
    }
    else if (choice == 5 && estJouable == 5){
        afficherFIN();
    }
    else {
        cout << "Niveau pas encore debloqué !" << endl << "Appuyez sur ENTREE pour choisir un autre niveau." << endl;
    }
    return estJouable;
}

// fait une sauvegarde dans un fichier
void save(unsigned estJouable) {
    ofstream save("save.txt"); // dans un fichier save
    save << estJouable << endl; // on enregistre la progression de l'histoire
    save.close();
}

unsigned chargeSave() {
    ifstream save("save.txt");
    unsigned estJouable = 1;
    if (save) { // dans le cas ou le fichier existe on sort la valeur de la sauvegarde
        save >> estJouable;
    }
    return estJouable; // sinon on renvoie par defaut le niveau 1 debloqué seulement
}

int main() {
    //jme disais aussi faire un "entrée" suffit au lieu de 1 pour qlq endroits mais c des details d'opti
    unsigned choix; // Choix dans le menu
    unsigned sousChoix; // Sous choix lorsqu'on est dans les différents menus
    unsigned cDifficulte;
    unsigned cNiveau = 0;
    unsigned maxTimes = 7;
    unsigned nbCandy = 5;
    unsigned estJouable = 1;// valeur qui permet de se souvenir de la progression

    do {
        menuMain(); // affiche l'écran de bienvenue
        choix = enterInt(1,5); // entree sécurisee
        switch (choix) {
        case 1:
            menuHistoire();
            sousChoix = enterInt(1,2);
            if (sousChoix == 1) {
                HISTOIRE();
                while(true){
                    menuNiveaux();
                    cNiveau = enterInt(1,6);

                    if(cNiveau==6) break;//on retourne au menu

                    estJouable = chargeSave();
                    estJouable = levelUnlock(cNiveau, estJouable);
                    save(estJouable);
                    cin.get();
                }
            }
            break;
        case 2:
            menuPVP();
            sousChoix = enterInt(1,2);
            if (sousChoix == 1) {
                play(maxTimes,nbCandy,true,false);
                cin.get();
            }
            else if (sousChoix == 2) {
                continue;
            }
            break;
        case 3:
            menuINFINI();
            sousChoix = enterInt(1,2);
            if (sousChoix == 1) {
                play(maxTimes,nbCandy,false,true);
                cin.get();
            }
            else if (sousChoix == 2) {
                menuMain();
                continue;
            }
            break;
        case 4:
            OPTIONS();
            sousChoix = enterInt(1,3);
            if (sousChoix == 1) {
                menuChangeDifficulte();
                cDifficulte = enterInt(1,4);
                if (cDifficulte >= 1 || cDifficulte <= 3){
                    nbCandy = changeDifficulte(cDifficulte);
                    maxTimes = nbCandy + 2;
                }
                else if (cDifficulte == 4) {
                    menuMain();
                    continue;
                }
            }
            else if (sousChoix == 2) {
                credits();
                cin.get();
            }
            else if (sousChoix == 3) {
                menuMain();
                continue;
            }
            break;
        case 5:
            clearScreen();
            break;
        }
    } while(choix != 5);
    return 0;
}
