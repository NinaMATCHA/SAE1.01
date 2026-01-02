#include <iostream>
#include <vector>

using namespace std;

typedef vector <unsigned> line; // un type représentant une ligne de la grille
typedef vector <line> mat; // un type représentant la grille

struct maPosition {
    unsigned abs; // colonne
    unsigned ord; // ligne
}; // une position dans la grille

// ----------------------------AFFICHAGE-----------------------------

void clearScreen () {
    cout << "\033[H\033[2J";
}

const unsigned KVide(0);

const unsigned KRouge   (31);
const unsigned KVert    (32);
const unsigned KBleu    (34);
const unsigned KMAgenta (35);

void couleur (const unsigned & coul) {
    cout << "\033[" << coul <<"m";
}

void initGrid (mat & grid, const unsigned & nbCandy){ // le changement de difficulté, nbCandy n'est plus une val globale, et définit la taille
    grid.resize(nbCandy);
    for (size_t i(0); i<nbCandy; ++i){
        grid[i].resize(nbCandy);
        for (size_t j(0); j<nbCandy; ++j){
            grid[i][j] = (rand()%nbCandy)+1;
        }
    }
}

void  displayGrid (const mat & grid){
    clearScreen();
    // indice d'une couleur dans la liste => couleur d'un nombre de cet indice
    const vector<unsigned> color = {KRouge,KVert,KMAgenta,KBleu,};

    cout << "   ";
    for(size_t j=0; j<grid.size(); ++j){
        cout << j << " "; // affiche les indices des colonnes
    }
    cout << endl;
    // sépare les indice des lignes avec '_' répétés deux fois la taille de la matrice
    cout << "   " << string(grid.size()*2, '_') << endl;

    for(size_t i=0; i<grid.size(); ++i){
        cout << i << " |"; // pour les indices des lignes
        for(unsigned candy : grid[i]){
            if(candy == KVide){
                cout << ". "; // affiche un point pour le vide
            }
            else{
                couleur(color[candy-1]); // -1 car les bonbons ne peuvent pas valoir 0 mais les indices de la liste commencent a 0
                cout << candy << " ";
                couleur(0);
            }
        }
        cout << endl;
    }
    cout << endl;
}

// évite les valeurs impossibles a l'entrée des lignes/colonnes
bool isValid(const mat& grid, const maPosition& pos) {
    return pos.ord < grid.size() && pos.abs < grid[0].size();
}

// changer makeAMove de void en maPosition permet de garder la valeur de newPos
maPosition makeAMove (mat & grid, const maPosition & pos, const char & direction, bool isPlayer1){
    maPosition newPos = pos;

    //selon le tour en pvp, change les touches valides
    vector<char> keys;
    if (isPlayer1)
        keys = {'z','s','a','e'};
    else
        keys = {'o','l','k','m'};

    bool isValidKey = false;
    for(char key : keys){
        if(key == direction)
            isValidKey = true;
    }

    while(!isValidKey){
        cout << "Mauvaises touches ! Elles sont indiquées ci-dessus !" << endl;
        for(char key : keys){
            if(key == direction)
                isValidKey = true;
        }
    }

    // on évite les débordements en plus de changer pos
    if ( direction == keys[0] && pos.ord > 0) --newPos.ord;
    else if ( direction == keys[1]  && pos.ord < grid.size() - 1) ++newPos.ord;
    else if ( direction == keys[2] && pos.abs > 0) --newPos.abs;
    else if ( direction == keys[3] && pos.abs < grid.size() - 1) ++newPos.abs;

    // fonction swap pour échanger directement
    swap(grid[pos.ord][pos.abs], grid[newPos.ord][newPos.abs]);
    return newPos;
}

// ----------------------------ALIGNEMENTS-----------------------------

bool atLeastThreeInAColumn (const mat & grid, maPosition & pos, unsigned & howMany){
    howMany = 1; //on compte le bonbon sur la position aussi
    unsigned valCandy = grid[pos.ord][pos.abs];
    if (valCandy == KVide) return false; // pas de points sur les cases vides

    // on verifie en haut
    unsigned li = pos.ord;
    while (li > 0 && grid[li-1][pos.abs] == valCandy){
        ++howMany;
        --li;
    }

    // en bas
    li = pos.ord;
    while (li < grid.size() - 1 && grid[li+1][pos.abs] == valCandy){
        ++howMany;
        ++li;
    }

    return (howMany >= 3);
}

bool atLeastThreeInARow (const mat & grid, maPosition & pos, unsigned & howMany){
    howMany = 1;
    unsigned valCandy = grid[pos.ord][pos.abs];
    if (valCandy == KVide) return false;

    // on verifie a gauche
    unsigned col = pos.abs;
    while (col > 0 && grid[pos.ord][col-1] == valCandy){
        ++howMany;
        --col;
    }

    // a droite
    col = pos.abs;
    while (col < grid[0].size() - 1 && grid[pos.ord][col+1] == valCandy){
        ++howMany;
        ++col;
    }

    return (howMany >= 3);
}

// ---------------------------------------------------------

void removalInColumn (mat & grid, maPosition & pos, const unsigned & howMany, const unsigned nbCandy, const bool infini){

    // on retrouve le début de la colonne de memes éléments
    unsigned currentCandy = grid[pos.ord][pos.abs];
    unsigned begin = pos.ord; // variable de position du debut des memes éléments
    // on remonte tant que c'est le meme bonbon
    while(begin > 0 && grid[begin-1][pos.abs] == currentCandy) {
        --begin;
    }

    // on décale vers le bas les valeurs au dessus des bonbons alignés
    for (unsigned currentRow = begin; currentRow < begin + howMany; ++currentRow) {// parcours la colonne par lignes

        // on fait descendre toute la colonne au dessus
        for(unsigned i = currentRow; i > 0; --i){
            grid[i][pos.abs] = grid[i-1][pos.abs];
        }

        // la case en haut n'ont plus de valeurs ou est remplacée selon si c'est le mode infini ou pas
        grid[0][pos.abs] = (infini) ?  (rand()%nbCandy)+1 : KVide;
    }
}

void removalInRow (mat & grid, maPosition & pos, const unsigned & howMany, const unsigned nbCandy, const bool infini){
    // on retrouve le début de la ligne de memes éléments
    unsigned currentCandy = grid[pos.ord][pos.abs];
    unsigned begin = pos.abs; // variable de position du debut des memes éléments
    // on remonte tant que c'est le meme bonbon
    while(begin > 0 && grid[pos.ord][begin-1] == currentCandy) {
        --begin;
    }

    //on descends toujours en colonne les valeurs mais dans la meme ligne ici
    for(unsigned currentCol = begin; currentCol < begin + howMany; ++currentCol){ //parcours la ligne par colonnes
        // on fait descendre toute la colonne au dessus de la colonne courante
        for(unsigned i = pos.ord; i > 0; --i){
            grid[i][currentCol] = grid[i-1][currentCol];
        }
        // La case du haut devient vide ou est remplacée selon si c'est le mode infini ou pas
        grid[0][currentCol] = (infini) ?  (rand()%nbCandy)+1 : KVide;
    }
}

// ---------------------------------------------------------

// calcule le score et teste les alignements sur ses différentes positions
unsigned scoreMatch(mat & grid, maPosition & pos, unsigned & howMany, const unsigned nbCandy, const bool infini){
    unsigned score = 0;
    unsigned valPos = grid[pos.ord][pos.abs]; // la valeur(chiffre) du bonbon
    if(valPos != KVide) {
        if(atLeastThreeInAColumn(grid, pos, howMany)){
            removalInColumn(grid, pos, howMany, nbCandy, infini);
            score += valPos * howMany;
        }
        else if(atLeastThreeInARow(grid, pos, howMany)){
            removalInRow(grid, pos, howMany, nbCandy, infini);
            score += valPos * howMany;
        }
    }
    return score;
}

// ---------------------- MODE HISTOIRE ---------------------------

void niveau1() {
    mat matrice;
    initGrid(matrice, 4);
    displayGrid(matrice);

    cout << "Nombre de coup max : " << 5;
    unsigned coups = 2;
    char direction;
    unsigned howMany;
    unsigned score = 0;
    bool isPlayer1 = true;
    bool infini = false;
    unsigned nbCandy;

    // on entre dans une boucle tant qu’on n’a pas atteint le nombre maximal de coups :
    while(coups < 5) {

        displayGrid(matrice); // affiche la grille;
        cout << "Votre score actuel : " << score << endl;
        cout << "Encore " << 5 - coups << " coups !" << endl;

        // on saisit les coordonnées du bonbon a déplacer
        maPosition pos;
        cout << "Colonne :";
        cin >> pos.abs;
        cout << "Ligne :";
        cin >> pos.ord;

        if (!isValid(matrice, pos)) {
            cout << "Veuillez suivre les positions indiquées"<< endl;
            continue; // permet de recommencer du début la boucle
        }
        coups++;

        cout << "Ou voulez vous aller ? (a/z/e/s) : ";
        cin >> direction;

        // on récupère la nouvelle position en plus d'échanger les deux
        maPosition newPos = makeAMove(matrice, pos, direction, isPlayer1);

        while(newPos.abs == pos.abs && newPos.ord == pos.ord){
            cout << "Vous allez en dehors de la matrice ! Réessayez :";
            cin >> direction;
            newPos = makeAMove(matrice, pos, direction, isPlayer1);
        }

        //score et test sur l'ancienne position
        score += scoreMatch(matrice, pos, howMany, nbCandy, infini);

        //score et test sur la nouvelle position
        if(isValid(matrice, newPos)) {
            score+=scoreMatch(matrice, newPos, howMany, nbCandy, infini);
        }
    }
    if (score < 21) {
        clearScreen();
        cout << "Perdu ! Les monstres ont gagnes" << endl;
        exit(1);
    }
    else if (score >= 21){
        clearScreen();
        cin.ignore();
        cout << "Vous avez gagne et debloque le niveau 2 !" << endl;
        cout << "Appuyez sur ENTREE pour continuer";
        cin.get();
    }
}

void niveau2() {
    mat matrice;
    initGrid(matrice, 6);
    displayGrid(matrice);

    cout << "Nombre de coup max : " << 5;
    unsigned coups = 0;
    char direction;
    unsigned howMany;
    unsigned score = 0;
    bool isPlayer1 = true;
    bool infini = false;
    unsigned nbCandy;

    // on entre dans une boucle tant qu’on n’a pas atteint le nombre maximal de coups :
    while(coups < 5) {

        displayGrid(matrice); // affiche la grille;
        cout << "Votre score actuel : " << score << endl;
        cout << "Encore " << 5 - coups << " coups !" << endl;

        // on saisit les coordonnées du bonbon a déplacer
        maPosition pos;
        cout << "Colonne :";
        cin >> pos.abs;
        cout << "Ligne :";
        cin >> pos.ord;

        if (!isValid(matrice, pos)) {
            cout << "Veuillez suivre les positions indiquées"<< endl;
            continue; // permet de recommencer du début la boucle
        }
        coups++;

        cout << "Ou voulez vous aller ? (a/z/e/s) : ";
        cin >> direction;

        // on récupère la nouvelle position en plus d'échanger les deux
        maPosition newPos = makeAMove(matrice, pos, direction, isPlayer1);

        while(newPos.abs == pos.abs && newPos.ord == pos.ord){
            cout << "Vous allez en dehors de la matrice ! Réessayez :";
            cin >> direction;
            newPos = makeAMove(matrice, pos, direction, isPlayer1);
        }

        //score et test sur l'ancienne position
        score+=scoreMatch(matrice, pos, howMany, nbCandy, infini);

        //score et test sur la nouvelle position
        if(isValid(matrice, newPos)) {
            score+=scoreMatch(matrice, newPos, howMany, nbCandy, infini);
        }
    }
    if (score < 44) {
        clearScreen();
        cout << "Perdu ! Les betes vous ont mange(e)s" << endl;
        exit(1);
    }
    else if(score >= 44) {
        clearScreen();
        cout << "Vous avez gagne et debloque le niveau 3 !" << endl;
        cout << "Appuyez sur ENTREE pour continuer";
        cin.get();
    }
}

void niveau3() {
    mat matrice;
    initGrid(matrice, 7);
    displayGrid(matrice);

    cout << "Nombre de coup max : " << 5;
    unsigned coups = 0;
    char direction;
    unsigned howMany;
    unsigned score = 0;
    bool isPlayer1 = true;
    bool infini = false;
    unsigned nbCandy;

    // on entre dans une boucle tant qu’on n’a pas atteint le nombre maximal de coups :
    while(coups < 5) {

        displayGrid(matrice); // affiche la grille;
        cout << "Votre score actuel : " << score << endl;
        cout << "Encore " << 5 - coups << " coups !" << endl;

        // on saisit les coordonnées du bonbon a déplacer
        maPosition pos;
        cout << "Colonne :";
        cin >> pos.abs;
        cout << "Ligne :";
        cin >> pos.ord;

        if (!isValid(matrice, pos)) {
            cout << "Veuillez suivre les positions indiquées"<< endl;
            continue; // permet de recommencer du début la boucle
        }
        coups++;

        cout << "Ou voulez vous aller ? (a/z/e/s) : ";
        cin >> direction;

        // on récupère la nouvelle position en plus d'échanger les deux
        maPosition newPos = makeAMove(matrice, pos, direction, isPlayer1);

        while(newPos.abs == pos.abs && newPos.ord == pos.ord){
            cout << "Vous allez en dehors de la matrice ! Réessayez :";
            cin >> direction;
            newPos = makeAMove(matrice, pos, direction, isPlayer1);
        }

        //score et test sur l'ancienne position
        score+=scoreMatch(matrice, pos, howMany, nbCandy, infini);

        //score et test sur la nouvelle position
        if(isValid(matrice, newPos)) {
            score+=scoreMatch(matrice, newPos, howMany, nbCandy, infini);
        }
    }
    if (score < 55) {
        clearScreen();
        cout << "Perdu ! Les cameras vous ont trouves" << endl;
        exit(1);
    }
    else if(score >= 55) {
        clearScreen();
        cout << "Vous avez gagne et debloque le niveau 4 !" << endl;
        cout << "Appuyez sur ENTREE pour continuer";
        cin.get();
    }
}

void niveau4() {
    mat matrice;
    initGrid(matrice, 9);
    displayGrid(matrice);

    cout << "Nombre de coup max : " << 6;
    unsigned coups = 0;
    char direction;
    unsigned howMany;
    unsigned score = 0;
    bool isPlayer1 = true;
    bool infini = false;
    unsigned nbCandy;

    // on entre dans une boucle tant qu’on n’a pas atteint le nombre maximal de coups :
    while(coups < 6) {

        displayGrid(matrice); // affiche la grille;
        cout << "Votre score actuel : " << score << endl;
        cout << "Encore " << 6 - coups << " coups !" << endl;

        // on saisit les coordonnées du bonbon a déplacer
        maPosition pos;
        cout << "Colonne :";
        cin >> pos.abs;
        cout << "Ligne :";
        cin >> pos.ord;

        if (!isValid(matrice, pos)) {
            cout << "Veuillez suivre les positions indiquées"<< endl;
            continue; // permet de recommencer du début la boucle
        }
        coups++;

        cout << "Ou voulez vous aller ? (a/z/e/s) : ";
        cin >> direction;

        // on récupère la nouvelle position en plus d'échanger les deux
        maPosition newPos = makeAMove(matrice, pos, direction, isPlayer1);

        while(newPos.abs == pos.abs && newPos.ord == pos.ord){
            cout << "Vous allez en dehors de la matrice ! Réessayez :";
            cin >> direction;
            newPos = makeAMove(matrice, pos, direction, isPlayer1);
        }

        //score et test sur l'ancienne position
        score+=scoreMatch(matrice, pos, howMany, nbCandy, infini);

        //score et test sur la nouvelle position
        if(isValid(matrice, newPos)) {
            score+=scoreMatch(matrice, newPos, howMany, nbCandy, infini);
        }
    }
    if (score < 70) {
        clearScreen();
        cout << "Perdu ! Le roi des monstres vous a elimine" << endl;
        exit(1);
    }
    else if(score >= 70) {
        clearScreen();
        cout << "Vous avez gagne ! Le monde est sauvee grace a vous !" << endl;
        cout << "Appuyez sur ENTREE pour continuer";
        cin.get();
    }
}

// ----------------------------JEU-----------------------------

void play( const unsigned maxTimes, const unsigned nbCandy, const bool pvp, const bool infini){ // on change la difficulté et les modes ici
    // on initialise la grille du jeu ainsi que le nombre de coup maximal;
    srand(time(0)); // permet de pouvoir rendre réellement aléatoire la matrice
    mat matrice;
    initGrid(matrice, nbCandy);

    cout << "Nombres de coup max : " << maxTimes;
    char direction;
    unsigned howMany, score;
    unsigned score1 = 0, score2 = 0, coups = 0, coups2 = 0; // score et coups pour différents joueurs
    bool isPlayer1; // bool qui définit si c'est le joueur 1 qui joue ou non
    unsigned turn = (pvp) ? rand()%2 : 0; // if else en une seule ligne, rand définit qui joue en premier en pvp, en dehors du pvp le j1 joue toujours

    // on entre dans une boucle tant qu’on n’a pas atteint le nombre maximal de coups :
    while(coups < maxTimes && coups2 < maxTimes){
        isPlayer1 = turn%2==0;
        if(pvp){
            if(isPlayer1){
                coups++;
                cout << "C'est le tour du joueur 1" << endl;
            }
            else{
                coups2++;
                cout << "C'est le tour du joueur 2" << endl;
            }
        }
        score = (isPlayer1) ? score1 : score2; // le tour définit qui voit son score augmenter
        displayGrid(matrice); // affiche la grille;
        cout << "Votre score actuel : " << score << endl;
        cout << "Encore " << maxTimes - coups << " coups !" << endl;

        // on saisit les coordonnées du bonbon a déplacer
        maPosition pos;
        cout << "Colonne :";
        cin >> pos.abs;
        cout << "Ligne :";
        cin >> pos.ord;

        while(!isValid(matrice, pos)) {
            cout << "La position est en dehors de la matrice ! Réessayez :"<< endl;
            cout << "Colonne :";
            cin >> pos.abs;
            cout << "Ligne :";
            cin >> pos.ord;
        }

        if(isPlayer1)
            cout << "Ou voulez vous aller ? (a/z/e/s) : ";
        else
            cout << "Ou voulez vous aller ? (o/k/l/m) : ";

        cin >> direction;

        // on récupère la nouvelle position en plus d'échanger les deux
        maPosition newPos = makeAMove(matrice, pos, direction,isPlayer1);

        while(newPos.abs == pos.abs && newPos.ord == pos.ord){
            cout << "Vous allez en dehors de la matrice ! Réessayez :";
            cin >> direction;
            newPos = makeAMove(matrice, pos, direction,isPlayer1);
        }

        //score et test sur l'ancienne position
        score+=scoreMatch(matrice, pos, howMany, nbCandy, infini);

        //score et test sur la nouvelle position
        if(isValid(matrice, newPos)) {
            score+=scoreMatch(matrice, newPos, howMany, nbCandy, infini);
        }

        if(isPlayer1)
            score1 = score;
        else
            score2 = score;

        //si c'est le mode pvp, on definit a qui sera le tour de jouer la prochaine fois
        if(pvp)
            ++turn;
        else
            coups2 = coups; // permet de pouvoir sortir du while a la fin du jeu

    }

    displayGrid(matrice);
    if(pvp){
        cout << "FINI ! Vos scores finaux :" << endl;
        cout << "Joueur 1 : " << score1 << endl;
        cout << "Joueur 2 : " << score2 << endl;
        if(score1>score2){
            cout << "C'est le Joueur 1 qui a gagné !" << endl;
        }
        else if(score2>score1){
            cout << "C'est le Joueur 2 qui a gagné !" << endl;
        }
        else{
            cout << "Egalité entre les deux joueurs !" << endl;
        }
    }
    else{
        cout << "FINI ! Votre score final :" << score1 << endl;
    }
}
