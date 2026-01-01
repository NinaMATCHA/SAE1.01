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

void menuNiveaux() {
    clearScreen();
    ifstream mNiveaux("../../mNiveaux.txt");

    string ligne;
    while (getline(mNiveaux, ligne)) {
        cout << ligne << endl;
    }
    mNiveaux.close();
}

void menuPVP() {
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
    clearScreen();
    ifstream mINFINI("../../mINFINI.txt");

    string ligne;
    while (getline(mINFINI, ligne)) {
        cout << ligne << endl;
    }
}

void OPTIONS() {
    clearScreen();
    ifstream options("../../mOPTIONS.txt");
    string ligne;
    while (getline(options, ligne)) {
        cout << ligne << endl;
    }
}

void changeDifficulte() {
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
