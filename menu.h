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

void afficherNIVEAU1() {
    clearScreen();
    ifstream niveau1("../../niveaux/niveau1.txt");

    string ligne;
    while (getline(niveau1, ligne)) {
        cout << ligne << endl;
    }
    niveau1.close();
    cin.ignore();
    cout << "Appuyez sur entree pour continuer.";
    cin.get();
}

void afficherNIVEAU2() {
    clearScreen();
    ifstream niveau2("../../niveaux/niveau2.txt");

    string ligne;
    while (getline(niveau2, ligne)) {
        cout << ligne << endl;
    }
    niveau2.close();
    cin.ignore();
    cout << "Appuyez sur entree pour continuer.";
    cin.get();
}

void afficherNIVEAU3() {
    clearScreen();
    ifstream niveau3("../../niveaux/niveau3.txt");

    string ligne;
    while (getline(niveau3, ligne)) {
        cout << ligne << endl;
    }
    niveau3.close();
    cin.ignore();
    cout << "Appuyez sur entree pour continuer.";
    cin.get();
}

void afficherNIVEAU4 () {
    clearScreen();
    ifstream niveau4("../../niveaux/niveau4.txt");

    string ligne;
    while (getline(niveau4, ligne)) {
        cout << ligne << endl;
    }
    niveau4.close();
    cin.ignore();
    cout << "Appuyez sur entree pour continuer.";
    cin.get();
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
