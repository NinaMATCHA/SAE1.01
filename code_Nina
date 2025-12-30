#include <iostream>
#include <vector>

using namespace std;

const unsigned KMaxTimes (5);
const unsigned KnbCandies(4);
const unsigned KVide(0);

typedef vector <unsigned> line; // un type représentant une ligne de la grille
typedef vector <line> mat; // un type représentant la grille

struct maPosition {
    unsigned abs; // colonne
    unsigned ord; // ligne
}; // une position dans la grille

void clearScreen () {
    cout << "\033[H\033[2J";
}

const unsigned KRouge   (31);
const unsigned KVert    (32);
const unsigned KBleu    (34);
const unsigned KMAgenta (35);

void couleur (const unsigned & coul) {
    cout << "\033[" << coul <<"m";
}

void initGrid (mat & grid, const size_t & matSize){
    grid.resize(matSize);
    for (size_t i(0); i<matSize; ++i){
        grid[i].resize(matSize);
        for (size_t j(0); j<matSize; ++j){
            grid[i][j] = (rand()%KnbCandies)+1;
        }
    }
}

void  displayGrid (const mat & grid){
    clearScreen();
    // indice d'une couleur dans la liste => couleur d'un nombre de cet indice
    const vector<unsigned> color = {KRouge,KVert,KMAgenta,KBleu};

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
maPosition makeAMove (mat & grid, const maPosition & pos, const char & direction){
    maPosition newPos = pos;

    // on évite les débordements en plus de changer pos
    if (direction == 'z' && pos.ord > 0) --newPos.ord;
    else if (direction == 's' && pos.ord < grid.size() - 1) ++newPos.ord;
    else if (direction == 'a' && pos.abs > 0) --newPos.abs;
    else if (direction == 'e' && pos.abs < grid.size() - 1) ++newPos.abs;

    // fonction swap pour échanger directement
    swap(grid[pos.ord][pos.abs], grid[newPos.ord][newPos.abs]);
    return newPos;
}

// ---------------------------------------------------------

bool atLeastThreeInAColumn (const mat & grid, maPosition & pos, unsigned & howMany){
    howMany = 1; //on compte le bonbon sur la position aussi
    unsigned nbCandy = grid[pos.ord][pos.abs];
    if (nbCandy == KVide) return false; // pas de points sur les cases vides

    // on verifie en haut
    unsigned li = pos.ord;
    while (li > 0 && grid[li-1][pos.abs] == nbCandy){
        ++howMany;
        --li;
    }

    // en bas
    li = pos.ord;
    while (li < grid.size() - 1 && grid[li+1][pos.abs] == nbCandy){
        ++howMany;
        ++li;
    }

    return (howMany >= 3);
}

bool atLeastThreeInARow (const mat & grid, maPosition & pos, unsigned & howMany){
    howMany = 1;
    unsigned nbCandy = grid[pos.ord][pos.abs];
    if (nbCandy == KVide) return false;

    // on verifie a gauche
    unsigned col = pos.abs;
    while (col > 0 && grid[pos.ord][col-1] == nbCandy){
        ++howMany;
        --col;
    }

    // a droite
    col = pos.abs;
    while (col < grid[0].size() - 1 && grid[pos.ord][col+1] == nbCandy){
        ++howMany;
        ++col;
    }

    return (howMany >= 3);
}

// ---------------------------------------------------------

void removalInColumn (mat & grid, maPosition & pos, const unsigned & howMany){

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

        // la case en haut n'ont plus de valeurs
        grid[0][pos.abs] = KVide;
    }
}

void removalInRow (mat & grid, maPosition & pos, const unsigned & howMany){
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
        // La case du haut devient vide
        grid[0][currentCol] = KVide;
    }
}

// calcule le score et teste les alignements sur ses différentes positions
unsigned scoreMatch(mat & grid, maPosition & pos, unsigned & howMany){
    unsigned score = 0;
    unsigned valPos = grid[pos.ord][pos.abs]; // la valeur(chiffre) du bonbon
    if(valPos != KVide) {
        if(atLeastThreeInAColumn(grid, pos, howMany)){
            removalInColumn(grid, pos, howMany);
            score += valPos * howMany;
        }
        else if(atLeastThreeInARow(grid, pos, howMany)){
            removalInRow(grid, pos, howMany);
            score += valPos * howMany;
        }
    }
    return score;
}

int main(){
    // on initialise la grille du jeu ainsi que le nombre de coup maximal;
    srand(time(0));
    mat matrice;
    initGrid(matrice,6);

    cout << "Nombres de coup max : " << KMaxTimes;
    unsigned coups = 0;
    char direction;
    unsigned howMany;
    unsigned score = 0;

    // on entre dans une boucle tant qu’on n’a pas atteint le nombre maximal de coups :
    while(coups < KMaxTimes){

        displayGrid(matrice); // affiche la grille;
        cout << "Votre score actuel : " << score << endl;
        cout << "Encore " << KMaxTimes - coups << " coups !" << endl;

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
        maPosition newPos = makeAMove(matrice, pos, direction);

        while(newPos.abs == pos.abs && newPos.ord == pos.ord){
            cout << "Vous allez en dehors de la matrice ! Réessayez :";
            cin >> direction;
            newPos = makeAMove(matrice, pos, direction);
        }

        //score et test sur l'ancienne position
        score+=scoreMatch(matrice, pos, howMany);

        //score et test sur la nouvelle position
        if(isValid(matrice, newPos)) {
            score+=scoreMatch(matrice, newPos, howMany);
        }
    }

    displayGrid(matrice);
    cout << "FINI ! Votre score final :" << score << endl;
}
