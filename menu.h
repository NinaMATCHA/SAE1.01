// CANDY CRUSH IN TERMINAL
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <fstream>

using namespace std;

struct infoMatch {
    bool trouvee;
    maPosition pos;
};

void Joueur1 (mat & grid, const maPosition & pos, const char & direction) {
    maPosition newPos = pos;
    switch (direction) {
    case 'z':
        if (pos.ord > 0) {
            newPos.ord = pos.ord - 1;
        }
        std::swap(grid[pos.ord][pos.abs], grid[newPos.ord][newPos.abs]);
        break;
    case 's':
        if (pos.ord < grid.size() - 1) {
            newPos.ord = pos.ord + 1;
        }
        swap(grid[pos.ord][pos.abs], grid[newPos.ord][newPos.abs]);
        break;
    case 'q':
        if (pos.abs > 0) {
            newPos.abs = pos.abs - 1;
        }
        swap(grid[pos.ord][pos.abs], grid[newPos.ord][newPos.abs]);
        break;
    case 'd':
        if (pos.abs < grid.size() - 1) {
            newPos.abs = pos.abs + 1;
        }
        swap(grid[pos.ord][pos.abs], grid[newPos.ord][newPos.abs]);
        break;
    }
}

void Joueur2 (mat & grid, const maPosition & pos, const char & direction) {
    maPosition newPos = pos;
    switch (direction) {
    case 'i':
        if (pos.ord > 0) {
            newPos.ord = pos.ord - 1;
        }
        std::swap(grid[pos.ord][pos.abs], grid[newPos.ord][newPos.abs]);
        break;
    case 'k':
        if (pos.ord < grid.size() - 1) {
            newPos.ord = pos.ord + 1;
        }
        swap(grid[pos.ord][pos.abs], grid[newPos.ord][newPos.abs]);
        break;
    case 'j':
        if (pos.abs > 0) {
            newPos.abs = pos.abs - 1;
        }
        swap(grid[pos.ord][pos.abs], grid[newPos.ord][newPos.abs]);
        break;
    case 'l':
        if (pos.abs < grid.size() - 1) {
            newPos.abs = pos.abs + 1;
        }
        swap(grid[pos.ord][pos.abs], grid[newPos.ord][newPos.abs]);
        break;
    }
}


// ===================================================================
//           FONCTIONS POUR LES DIFFERENTS MENU DU JEU
//                          ET LES MODES
// ===================================================================


void menuMain() {
    clearScreen();
    ifstream menu("../../menu.txt");

    string ligne;
    while (getline(menu, ligne)) {
        cout << ligne << endl;
    }
    menu.close();
}

void menuHistoire() {
    clearScreen();
    ifstream mHISTOIRE("../../mHISTOIRE.txt");

    string ligne;
    while (getline(mHISTOIRE, ligne)) {
        cout << ligne << endl;
    }
    mHISTOIRE.close();
}

void HISTOIRE() {
    clearScreen();
    ifstream HISTOIRE("../../HISTOIRE.txt");

    string ligne;
    while (getline(HISTOIRE, ligne)) {
        cout << ligne << endl;
    }
    HISTOIRE.close();
}

void menuPVP() {
    // TODO ; lance le mode PVP
    // On change juste makeAMove par "joueur1"
    // On fait donc un deuxième makeAMove qu'on nomme "joueur2" avec des touches differentes
    // On rajoute un truc random pour savoir qui joue en premier
    // Une fois qu'un joueur a fait un coup, il a son propre score
    // le joueur qui fait le plus de score a la fin gagne
    clearScreen();
    ifstream mPVP("../../mPVP.txt");

    if (!mPVP) {
        cerr << "ERROR" << endl;
        exit (1);
    }
    string ligne;
    while (getline(mPVP, ligne)) {
        cout << ligne << endl;
    }
}

void menuINFINI() {
    // TODO ; lance le mode infini
    // Comme le mode HISTOIRE sauf que lorsqu'une ligne/colonne est
    // supprimé, on génere de nouveau nombre
    // ou on fait monter les nombres en dessous
    // Au choix ^^
    clearScreen();
    ifstream mINFINI("../../mINFINI.txt");

    string ligne;
    while (getline(mINFINI, ligne)) {
        cout << ligne << endl;
    }
}

void OPTIONS() {
    /*
    TODO ; lance les options
    ==========================================
           /!\ SI TROP DUR ON FAIT PAS /!\
    ==========================================
    */
    clearScreen();
    ifstream options("../../mOPTIONS.txt");

    if (!options) {
        cerr << "ERROR" << endl;
        exit (1);
    }
    string ligne;
    while (getline(options, ligne)) {
        cout << ligne << endl;
    }
}

void changeDifficulte() {
    // TODO Fonction qui change la difficulte de chaque mode de jeu
    // que ce soit dans le mode pvp, histoire ou infini
    clearScreen();
    ifstream cDifficulte("../../changeDifficulte.txt");

    string ligne;
    while (getline(cDifficulte, ligne)) {
        cout << ligne << endl;
    }
}

void credits() {
    clearScreen();
    ifstream CREDITS("../../CREDITS.txt");

    string ligne;
    while (getline(CREDITS, ligne)) {
        cout << ligne << endl;
    }
}
