#include <iostream>
#include <vector>
#include "jeu.h"
#include "menu.h"


/**
 * @brief change a difficulté du jeu.
 */
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

/**
 * @brief gère les niveaux qui doivent se débloquer un par un.
 */
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

/**
 * @brief fait une sauvegarde dans un fichier.
 */
void save(unsigned estJouable, vector<unsigned>& meilleursScores) {
    ofstream save("save.txt"); // dans un fichier save
    save << estJouable << endl; // on enregistre la progression de l'histoire
    for(unsigned score : meilleursScores){// et les meilleurs scores
        save << score << endl;
    }
    save.close();
}

/**
 * @brief charge le fichier de sauvegarde.
 */
void chargeSave(unsigned& estJouable, vector<unsigned>& meilleursScores) {
    ifstream save("save.txt");
    if (save) { // dans le cas ou le fichier existe on sort la valeur de la sauvegarde
        save >> estJouable;
        save >> meilleursScores[0];
        save >> meilleursScores[1];
    }
    else{
        estJouable = 1; // sinon on renvoie par defaut le niveau 1 debloqué seulement
    }
}

/**
 * @brief affiche un menu qui montre les meilleurs scores du joueur.
 */
void menuBestScores(vector<unsigned>& meilleursScores) {
    clearScreen();
    ifstream menuBestScores("../../menu/menuBestScores.txt");

    string ligne;
    while (getline(menuBestScores, ligne)) {
        cout << ligne << endl;
    }
    menuBestScores.close();

    cout << "Meilleur score du mode normal :" << meilleursScores[0] << endl;
    cout << "Meilleur score du mode infini :" << meilleursScores[1] << endl;
    cout << "------------------------------" << endl;
    cout << "------------------------------" << endl;
    cout << "Appuyez sur ENTREE pour revenir au menu." << endl;
}


int main() {
    unsigned choix; // Choix dans le menu
    unsigned sousChoix; // Sous choix lorsqu'on est dans les différents menus
    unsigned sousChoix2 = 0; // Sous choix du sous choix, a l'interieur d'un menu qui est a l'interieur d'un menu
    unsigned maxTimes = 7;
    unsigned nbCandy = 5;
    unsigned estJouable, score;
    vector<unsigned> meilleursScores(2,0);
    chargeSave(estJouable, meilleursScores);

    do {
        menuMain(); // affiche l'écran de bienvenue
        choix = enterInt(1,5); // entree sécurisee
        switch (choix) {
        case 1:
            menuHistoire();
            sousChoix = enterInt(1,2);
            if (sousChoix == 1) {
                HISTOIRE();
                cin.get();
                while(true){
                    menuNiveaux();
                    sousChoix2 = enterInt(1,6);

                    if(sousChoix2==6) break;//on retourne au menu
                    estJouable = levelUnlock(sousChoix2, estJouable);
                    save(estJouable, meilleursScores);
                }
            }
            break;
        case 2:
            menuPVP();
            sousChoix = enterInt(1,2);
            if (sousChoix == 1) {
                play(maxTimes,nbCandy,true,false);
            }
            else if (sousChoix == 2) {
                continue;
            }
            break;
        case 3:
            menuFREEPLAY();
            sousChoix = enterInt(1,2);
            if (sousChoix == 1) {
                while(true){
                menuChoixMode();
                sousChoix2 = enterInt(1,4);
                    if(sousChoix2==1){
                        score = play(maxTimes,nbCandy,false,false);
                        if(meilleursScores[0]<score) meilleursScores[0] = score;
                        save(estJouable, meilleursScores);
                    }
                    else if(sousChoix2==2) {
                        score = play(maxTimes,nbCandy,false,true);
                        if(meilleursScores[1]<score) meilleursScores[1] = score;
                        save(estJouable, meilleursScores);
                    }
                    else if(sousChoix2==3){
                        menuBestScores(meilleursScores);
                        cin.get();
                    }
                    else if(sousChoix2==4) break;
                }

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
                sousChoix2 = enterInt(1,4);
                if (sousChoix2 >= 1 || sousChoix2 <= 3){
                    nbCandy = changeDifficulte(sousChoix2);
                    maxTimes = nbCandy + 2;
                }
                else if (sousChoix2 == 4) {
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
