#include <stdexcept>
/** @file
 * Filtres de Sobel
 **/
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

/** Structure de donnee pour representer une image en teintes de gris **/
typedef vector<vector<double> > ImageGris;



/** Infrastructure minimale de test **/
#define CHECK(test) if (!(test)) cerr << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl


/** Une image 4x4 en teintes de gris pour faire des tests **/
ImageGris imgGrisTest = {
    {0, 255, 54.213, 236.589},
    {18.411, 182.376, 200.787, 120},
    {139.583, 172.841, 94.0878, 88.4974},
    {158.278, 172.841, 89.0236, 80.0384}
};

// On rajoute la fonction renormalise de la question 3.2 pour tester sobel-tout-en-un.cpp :

ImageGris renormalise(ImageGris img) {
    // Ici, on veut utiliser toutes les teintes possibles dans le cas où les valeurs sont comprises dans un petit intervalle [0, v] avec v ≤ 255.
    // D'après l'indication , on peut chercher le max des valeurs
    // Donc si on pose le max des valeurs comme 255. On peut arriver à "renormaliser" l'image sous l'intervalle [0,255] en convertissant les autres pixels tq : 
    //(pixel/pixel_max)*255
    
    int ligne=img.size();
    int colonne= img[0].size();

    double max_valeur=0; // on met un double ici dans le cas ou on a un nombre à virgule après.
    for (int i=0;i<ligne;i++){
        for (int j=0;j<colonne;j++){
            if (max_valeur< img[i][j])
                max_valeur=img[i][j];
        }
    }
    // Attention à si max_valeur=0, on va diviser par 0 donc : 
    if (max_valeur==0)
        return img; // Retourne image car c'est deja renormaliser ( c'est dans l'intervalle dans tous les cas)
    
    ImageGris renormalize;
    renormalize= ImageGris(ligne);
    for (int i=0;i<ligne;i++)
        renormalize[i]= vector<double>(colonne);
    
    for (int i=0;i<ligne;i++){
        for (int j=0;j<colonne;j++){
            renormalize[i][j]= (img[i][j]/max_valeur)*255;
        }
    }
    return renormalize;
    
}



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
            pgm << ((int)img[i][k]) << " "; // écrit chaque pixel double converti en int, (version d'avant était avec un pixel par ligne.)
            
        }
        cout<< endl;
    }
    pgm.close();
}








/** Teste si deux images en teintes de gris sont égales modulo imprécision numérique
 * En cas de différence un message est affiché
 * @param a une image en teintes de gris
 * @param b une image en teintes de gris
 * @param precision un flottant positif: la précision souhaitée; typiquement 0.001
 * @return vrai si les images sont égales et faux sinon
 **/
bool ImageGrisEgal(ImageGris a, ImageGris b, float precision) {
    if (a.size() != b.size())  {
        cout << "Nombre de lignes différent" << endl;
        return false;
    }
    for (int i=0; i<a[0].size(); i++)
        if (a[0].size() != b[i].size()) {
            cout << "Nombre de colonnes différent" << endl;
            return false;
        }
    for (int i=0; i<a.size(); i++)
        for (int j=0; j<a[0].size(); j++)
            if (abs(a[i][j] - b[i][j]) > precision) {
                cout << "Valeur differentes en position " << i << "," << j
             << ": " << a[i][j] << " au lieu de " << b[i][j] << endl;
                return false;
            }
    return true;
}

/// BEGIN intensiteH

/** filtre de Sobel horizontal
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite horizontale de img
 **/

ImageGris intensiteH(ImageGris img) {
     int ligne= img.size(); // Cela correspond au nombre de ligne de l'image
    int colonne=img[0].size(); // Nombre de colonne dans une ligne. On prend la 1 ère ligne car c'est suffisant. Même N° de colonnes pour chaque ligne

    // On crée une nouvelle image pour l'intensité horizontale de même taille et initialisée à 0    
    ImageGris img_intensiteH;
    img_intensiteH= ImageGris(ligne);
    for (int i=0;i<ligne;i++)
        img_intensiteH[i]= vector<double>(colonne);
    
    for (int i=1;i<ligne-1 ;i++){ 
        for (int j=1;j<colonne-1 ;j++){ 
            // On met i=1 car dans la formule on utilise : i-1, i et i+1. si i=0 on a 0-1= erreur
            // Dans ces boucles, on fait((ligne et colonne) -1) parce que c’est le dernier index valide et on doit éviter de faire i+1 dessus. Car, d'après la consigne, on ne veut pas les bords donc on veut que cela soit <(ligne -1 et colonne -1) avec i=1.
           
            img_intensiteH[i][j]=img[i-1][j-1] + 2*img[i][j-1] + img[i+1][j-1]- img[i-1][j+1] - 2*img[i][j+1] - img[i+1][j+1];
        }
    }
    return img_intensiteH;
   
}


/// BEGIN intensiteV

/** filtre de Sobel vertical
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite verticale de img
 **/

ImageGris intensiteV(ImageGris img) {
    int ligne= img.size(); // Cela correspond au nombre de ligne de l'image
    int colonne=img[0].size(); // Nombre de colonne dans une ligne. On prend la 1 ère ligne car c'est suffisant. Même N° de colonnes pour chaque ligne

    // On crée une nouvelle image pour l'intensité verticale de même taille et initialisée à 0    
    ImageGris img_intensiteV;
    img_intensiteV= ImageGris(ligne);
    
    for (int i=0;i<ligne;i++)
        img_intensiteV[i]= vector<double>(colonne);
    
    for (int i=1;i<ligne-1 ;i++){ 
        for (int j=1;j<colonne-1 ;j++){ 
            // On met i=1 car dans la formule on utilise : i-1, i et i+1. si i=0 on a 0-1= erreur
            // Dans ces boucles, on fait((ligne et colonne) -1) parce que c’est le dernier index valide et on doit éviter de faire i+1 dessus. Car, d'après la consigne, on ne veut pas les bords donc on veut que cela soit <(ligne -1 et colonne -1) avec i=1.
            img_intensiteV[i][j]=img[i-1][j-1] + 2*img[i-1][j] + img[i-1][j+1]- img[i+1][j-1] - 2*img[i+1][j] - img[i+1][j+1];
        }
    }
    return img_intensiteV;
}



/// BEGIN intensiteHV

/** filtre de Sobel
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite de img
 **/

ImageGris intensite(ImageGris img) {
    int ligne= img.size(); // Cela correspond au nombre de ligne de l'image
    int colonne=img[0].size(); // Nombre de colonne dans une ligne. On prend la 1 ère ligne car c'est suffisant. Même N° de colonnes pour chaque ligne

    // D'après l'indication, on stocke intensiteH et intensiteV dans un tableau h et v pour faciliter et rendre + lisible le code. Et, ils vont servir à calculer la norme (h,v) . D'ailleurs pas besoin de mettre ImageGris img car il est deja present au dessus.
    ImageGris h= intensiteH(img);
    ImageGris v= intensiteV(img);

    ImageGris norme_intensite;
    norme_intensite= ImageGris(ligne); 
    for (int i=0;i<ligne;i++)
            norme_intensite[i]=vector<double>(colonne);
        
    for (int i=1;i<ligne-1 ;i++){ 
        for (int j=1;j<colonne-1 ;j++){ 
            // On met i=1 car dans la formule on utilise : i-1, i et i+1. si i=0 on a 0-1= erreur
            // Dans ces boucles, on fait((ligne et colonne) -1) parce que c’est le dernier index valide et on doit éviter de faire i+1 dessus. Car, d'après la consigne, on ne veut pas les bords donc on veut que cela soit <(ligne -1 et colonne -1) avec i=1.
            norme_intensite[i][j]= sqrt(h[i][j]*h[i][j] + v[i][j]*v[i][j]);
            // Autre idée possible : norme_intensite[i][j]= sqrt(pow(h[i][j],2)+pow(v[i][j],2));
        }
    }
    return norme_intensite;
}


void testSobel() {
    CHECK( ImageGrisEgal(intensiteH(imgGrisTest),
              ImageGris( {
                  {0, 0, 0, 0},
                  {0, -373.47, 227.507, 0},
                  {0, -22.1312, 323.866, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
    CHECK( ImageGrisEgal(intensiteV(imgGrisTest),
              ImageGris( {
                  {0, 0, 0, 0},
                  {0, -15.1398, 150.501, 0},
                  {0, -9.0336, 273.023, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
    CHECK( ImageGrisEgal(intensite(imgGrisTest),
              ImageGris( {
                  {0, 0, 0, 0},
                  {0, 373.777, 272.782, 0},
                  {0, 23.9039, 423.593, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );

    cout << "Vérifier que les images obtenues dans 'sobel/' sont semblables à celles fournies dans 'sobel/correction/'" << endl;

    // Ici, j'ai rajouté la fonction renormalise que j'ai importé de la Question 3.2 pour pouvoir faire marcher le test du rapport de la partie 3
    ecrirePGM(renormalise(intensite(lirePGM("images/Willis.512.pgm" ))), "sobel/Willis.512.pgm");
    ecrirePGM(renormalise(intensite(lirePGM("images/Baboon.512.pgm" ))), "sobel/Baboon.512.pgm");
    ecrirePGM(renormalise(intensite(lirePGM("images/Billes.256.pgm" ))), "sobel/Billes.256.pgm");
    ecrirePGM(renormalise(intensite(lirePGM("images/Embryos.512.pgm"))), "sobel/Embryos.512.pgm");
    ecrirePGM(renormalise(intensite(lirePGM("images/House.256.pgm"  ))), "sobel/House.256.pgm");
}



int main(){

    testSobel();
    return 0 ;
}

