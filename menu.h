/**
 * @file menu.h
 * @brief Ensemble de fonctions qui affichent des fichiers texte à l'écran
 * @author Nina MATIC CHARBIT, Ewan FRANCOIS sur la base du cours de Mr.Alain CASALI
 * @date 4 janvier 2026
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

// ===================================================================
//           FONCTIONS POUR LES DIFFERENTS MENU DU JEU
//                          ET LES MODES
// ===================================================================

/**
 * @brief Affiche le menu principal
 */
void menuMain() {
    clearScreen();
    ifstream menu("../../menu/menu.txt");

    if (!menu) {
        cerr << "erreur, le fichier n'a pas été trouvé" << endl;
        exit (1);
    }
    
    string ligne;
    while (getline(menu, ligne)) {
        cout << ligne << endl;
    }
    menu.close();
}

/**
 * @brief Affiche le menu du mode histoire.
 */
void menuHistoire() {
    clearScreen();
    ifstream mHISTOIRE("../../menu/mHISTOIRE.txt");

    if (!mHISTOIRE) {
        cerr << "erreur, le fichier n'a pas été trouvé" << endl;
        exit (1);
    }
    
    string ligne;
    while (getline(mHISTOIRE, ligne)) {
        cout << ligne << endl;
    }
    mHISTOIRE.close();
}

/**
 * @brief Affiche l'introduction de l'histoire.
 */
void HISTOIRE() {
    clearScreen();
    ifstream HISTOIRE("../../menu/HISTOIRE.txt");

    if (!HISTOIRE) {
        cerr << "erreur, le fichier n'a pas été trouvé" << endl;
        exit (1);
    }
    
    string ligne;
    while (getline(HISTOIRE, ligne)) {
        cout << ligne << endl;
    }
    HISTOIRE.close();
}

/**
 * @brief Affiche le menu de sélections des quatres différents niveaux.
 */
void menuNiveaux() {
    clearScreen();
    ifstream mNiveaux("../../menu/mNiveaux.txt");

    if (!mNiveaux) {
        cerr << "erreur, le fichier n'a pas été trouvé" << endl;
        exit (1);
    }
    
    string ligne;
    while (getline(mNiveaux, ligne)) {
        cout << ligne << endl;
    }
    mNiveaux.close();
}

/**
 * @brief Affiche le début de l'histoire avant de lancer le niveau 1.
 */
void afficherNIVEAU1() {
    clearScreen();
    ifstream niveau1("../../niveaux/niveau1.txt");

    if (!niveau1) {
        cerr << "erreur, le fichier n'a pas été trouvé" << endl;
        exit (1);
    }
    
    string ligne;
    while (getline(niveau1, ligne)) {
        cout << ligne << endl;
    }
    niveau1.close();
    cin.ignore();
    cout << "Appuyez sur entree pour continuer.";
    cin.get();
}

/**
 * @brief Affiche la suite l'histoire avant de lancer le niveau 2.
 */
void afficherNIVEAU2() {
    clearScreen();
    ifstream niveau2("../../niveaux/niveau2.txt");

    if (!niveau2) {
        cerr << "erreur, le fichier n'a pas été trouvé" << endl;
        exit (1);
    }
    
    string ligne;
    while (getline(niveau2, ligne)) {
        cout << ligne << endl;
    }
    niveau2.close();
    cin.ignore();
    cout << "Appuyez sur entree pour continuer.";
    cin.get();
}

/**
 * @brief Affiche la suite de l'histoire avant de lancer le niveau 3.
 */
void afficherNIVEAU3() {
    clearScreen();
    ifstream niveau3("../../niveaux/niveau3.txt");

    if (!niveau3) {
        cerr << "erreur, le fichier n'a pas été trouvé" << endl;
        exit (1);
    }
    
    string ligne;
    while (getline(niveau3, ligne)) {
        cout << ligne << endl;
    }
    niveau3.close();
    cin.ignore();
    cout << "Appuyez sur entree pour continuer.";
    cin.get();
}

/**
 * @brief Affiche la suite de l'histoire avant de lancer le niveau 4.
 */
void afficherNIVEAU4() {
    clearScreen();
    ifstream niveau4("../../niveaux/niveau4.txt");

    if (!niveau4) {
        cerr << "erreur, le fichier n'a pas été trouvé" << endl;
        exit (1);
    }
    
    string ligne;
    while (getline(niveau4, ligne)) {
        cout << ligne << endl;
    }
    niveau4.close();
    cin.ignore();
    cout << "Appuyez sur entree pour continuer.";
    cin.get();
}

/**
 * @brief Affiche la fin du mode histoire.
 */
void afficherFIN() {
    clearScreen();
    ifstream fin("../../niveaux/fin.txt");
    
    if (!fin) {
        cerr << "erreur, le fichier n'a pas été trouvé" << endl;
        exit (1);
    }
    
    string ligne;
    while (getline(fin, ligne)) {
        cout << ligne << endl;
    }
    fin.close();
    cin.ignore();
    cout << "Appuyez sur entree pour continuer.";
    cin.get();
}

/**
 * @brief Affiche le menu dans le mode PVP.
 */
void menuPVP() {
    clearScreen();
    ifstream mPVP("../../menu/mPVP.txt");

    if (!mPVP) {
        cerr << "erreur, le fichier n'a pas été trouvé" << endl;
        exit (1);
    }
    string ligne;
    while (getline(mPVP, ligne)) {
        cout << ligne << endl;
    }
    mPVP.close();
}

/**
 * @brief Affiche le menu d'introduction du mode "FreePlay".
 */
void menuFREEPLAY() {
    clearScreen();
    ifstream mFREEPLAY("../../menu/mFREEPLAY.txt");
    
    if (!mFREEPLAY) {
        cerr << "erreur, le fichier n'a pas été trouvé" << endl;
        exit (1);
    }
    
    string ligne;
    while (getline(mFREEPLAY, ligne)) {
        cout << ligne << endl;
    }
    mFREEPLAY.close();
}

/**
 * @brief Affiche le menu pour choisir les différents modes dans le mode "FreePlay".
 */
void menuChoixMode() {
    clearScreen();
    ifstream menuChoixMode("../../menu/menuChoixMode.txt");

    if (!menuChoixMode) {
        cerr << "erreur, le fichier n'a pas été trouvé" << endl;
        exit (1);
    }
    
    string ligne;
    while (getline(menuChoixMode, ligne)) {
        cout << ligne << endl;
    }
    menuChoixMode.close();
}

/**
 * @brief Affiche les options.
 */
void OPTIONS() {
    clearScreen();
    ifstream options("../../menu/mOPTIONS.txt");
    
    if (!options) {
        cerr << "erreur, le fichier n'a pas été trouvé" << endl;
        exit (1);
    }
    
    string ligne;
    while (getline(options, ligne)) {
        cout << ligne << endl;
    }
    options.close();
}

/**
 * @brief Affiche le menu pour changer de difficulte.
 */
void menuChangeDifficulte() {
    clearScreen();
    ifstream changeDifficulte("../../menu/changeDifficulte.txt");

    if (!changeDifficulte) {
        cerr << "erreur, le fichier n'a pas été trouvé" << endl;
        exit (1);
    }
    
    string ligne;
    while (getline(changeDifficulte, ligne)) {
        cout << ligne << endl;
    }
    changeDifficulte.close();
}

/**
 * @brief Affiche les credits.
 */
void credits() {
    clearScreen();
    ifstream credits("../../menu/CREDITS.txt");

    if (!credits) {
        cerr << "erreur, le fichier n'a pas été trouvé" << endl;
        exit (1);
    }
    
    string ligne;
    while (getline(credits, ligne)) {
        cout << ligne << endl;
    }
    credits.close();
}
