#include <stdexcept>
/** @file
 * Lecture et ecriture d'images en niveau de gris au format PGM
 **/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/// BEGIN ImageGris

/** Structure de donnees pour representer une image en teintes de gris **/
typedef vector<vector<double> > ImageGris;
/// END ImageGris

/// BEGIN lirePGM

/** Construire une image en teintes de gris depuis un fichier PGM
 * @param source le nom d'un fichier PGM
 * @return une image en teintes de gris
 **/
ImageGris lirePGM(string source) {
    ifstream pgm;
    pgm.open(source);
    if (not pgm)
        throw runtime_error("Fichier non trouve: "+source);
   
    string formatP2;
    pgm >> formatP2;
    int colonne, ligne;
    pgm >> colonne >> ligne;
    int valeur_maxGris; // D'après Wikipédia : "Chaque niveau de gris est codé par une valeur entre 0 et cette valeur maximale, proportionnellement à son intensité" D'ou le nom valeur_maxGris.
    pgm >> valeur_maxGris;
    ImageGris image;
    image= ImageGris(ligne);

    for (int i=0; i<ligne;i++)
        image[i]=vector<double>(colonne);
    int pixel;
    for (int k=0;k<image.size();k++){
        for(int j=0;j<image[k].size();j++){
            pgm >> pixel;
            image[k][j]=pixel;
        }
    }
    pgm.close();
    return image;   
}

/// BEGIN ecrirePGM

/** Ecrit une image en teintes de gris dans un fichier PGM
 * @param img une image en teintes de gris
 * @param cible le nom d'un fichier PGM
 **/
void ecrirePGM(ImageGris img, string cible) {
    ofstream pgm;
    pgm.open(cible);
    
    int ligne= img.size(); // Cela correspond au nombre de ligne de l'image
    int colonne=img[0].size(); // Nombre de colonne dans une ligne. On prend la 1 ère ligne car c'est suffisant. Même N° de colonnes pour chaque ligne 
    pgm << "P2" << endl; // Correspond au format P2
    pgm << colonne << " " << ligne << endl; // Nb de colonne et de ligne
    pgm << 255 << endl; // intensité max du Gris

    for (int i=0; i<ligne; i++){
        for (int k=0; k<colonne; k++){
            pgm << ((int)img[i][k]) << endl; // écrit chaque pixel double converti en int, avec un pixel par ligne.
            
        }
    }
    pgm.close();
}

/** Construit une image cliché d'une image en niveau de gris
 * @param img une image en niveau de gris
 * @return l'image cliché qui inverse les niveaux de gris
 **/
ImageGris inversePGM(ImageGris img) { // Ici, l'inverse d'une valeur se fait par (ValeurMax-Valeur)
    // 0--> 255 ( 255-0); 1-->254 ( 255-1)
   // On donne déjà une image. Donc pas besoin de ifstream et de ofstream.
    
    int ligne= img.size(); // Cela correspond au nombre de ligne de l'image
    int colonne=img[0].size(); // Nombre de colonne dans une ligne. On prend la 1 ère ligne car c'est suffisant. Même N° de colonnes pour chaque ligne 
    ImageGris inverse_img;
    inverse_img= ImageGris(ligne);
    
    for (int i=0; i<ligne; i++)
        inverse_img[i]=vector<double>(colonne);
    
    for (int k=0; k<ligne; k++){
        for (int j=0; j<colonne; j++){
            inverse_img[k][j]= 255-img[k][j];
        }
    }
            
    return inverse_img;
}

void lirePGMTest(){
    cout << "Vérifier que les images obtenues dans 'pgm/' sont semblables à celles fournies dans 'pgm/correction/'" << endl;
    ecrirePGM(lirePGM("images/brain.pgm"),  "pgm/brain.pgm");
    ecrirePGM(lirePGM("images/illusion.pgm"),  "pgm/illusion.pgm");
}

void inversePGMTest() {
    ImageGris imageOriginale;
    cout << "Vérifier que les images obtenues dans 'pgm/' sont semblables à celles fournies dans 'pgm/correction/'" << endl;
    imageOriginale = lirePGM("images/brain.pgm");
    ecrirePGM(inversePGM(imageOriginale),  "pgm/brain-inverse.pgm");
    imageOriginale = lirePGM("images/illusion.pgm");
    ecrirePGM(inversePGM(imageOriginale),  "pgm/illusion-inverse.pgm");
}

int main() {
    lirePGMTest();
    inversePGMTest();
    return 0;
}

