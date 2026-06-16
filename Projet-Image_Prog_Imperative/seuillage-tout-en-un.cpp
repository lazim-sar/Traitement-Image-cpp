#include <stdexcept>
/** @file
 * Filtres de seuillage
 **/

#include <cmath>
#include <iostream>
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

/** Une image 4x4 en teintes de gris pour les tests de renormalisation **/
ImageGris imgGrisRenorm = {
    {0, 50, 0, 50},
    {0, 50, 0, 50},
    {0, 50, 0, 50},
    {0, 50, 0, 50},
};

/// BEGIN lissage4

/** Filtre de lissage à 4 voisins
 * Remplace la valeur de chaque pixel par la moyenne de ses 4 voisins
 * (haut, bas, gauche, droite).
 * Utile pour réduire le bruit avant d’appliquer le filtre de Sobel.
 * @param img une image en teintes de gris
 * @return une nouvelle image en teintes de gris lissée
 **/
ImageGris lissage4(ImageGris img) {
    ImageGris res(img.size(), vector<double>(img[0].size(), 0));

    for (int i = 1; i < img.size() - 1; i++) {
        for (int j = 1; j < img[0].size() - 1; j++) {
            res[i][j] = (img[i-1][j] + img[i+1][j] + img[i][j-1] + img[i][j+1]) / 4.0;
        }
    }

    return res;
}

/// END lissage4


/** filtre de Sobel
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite de img
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


/// BEGIN renormalise

/** Renormalize une image en teinte de gris, les ramenant dans l'intervalle [0,255]
 * @param img un image en teintes de gris
 * @return une image en teintes de gris
 **/

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


void lissageTest() {
    cout << "Création d'images lissées dans le dossier 'seuillage/'" << endl;
    ecrirePGM(lissage4(lirePGM("images/Billes.256.pgm")),
              "seuillage/Billes_lissee.256.pgm");
    ecrirePGM(lissage4(lirePGM("images/Willis.512.pgm")),
              "seuillage/Willis_lissee.512.pgm");

}


void renormaliseTest() {
    CHECK( ImageGrisEgal(renormalise( imgGrisRenorm),
              ImageGris( {
                  {0, 255, 0, 255},
                  {0, 255, 0, 255},
                  {0, 255, 0, 255},
                  {0, 255, 0, 255},
              }),
              0.001) );

}
/// BEGIN seuillage

/** Filtre de seuillage
 * @param img
 * @param seuil un entier dans l'intervalle [0,255]
 * @return image en noir et blanc obtenue en remplacant la teinte de
 *  chaque pixel par
 *  - du blanc si teinte < seuil
 *  - du noir  si teinte > seuil
 **/

ImageGris seuillage(ImageGris img, int seuil) {
    // Ici, 0 correspond à la couleur noire et le 255 correspond au blanc. Tout ce qui est dans l'intervalle ]0,255[ correspond à une intensité de gris.
    if (seuil<0 or seuil > 255)
        throw runtime_error("Le seuil est invalide ! ");
    int ligne=img.size();
    int colonne= img[0].size();
    
    ImageGris tab_seuil;
    tab_seuil= ImageGris(ligne);
    for (int i=0;i<ligne;i++)
        tab_seuil[i]= vector<double>(colonne);
    
    for (int i=0;i<ligne;i++){
        for (int j=0;j<colonne;j++){
            if (img[i][j]< seuil)
                tab_seuil[i][j]=255;
            else
                tab_seuil[i][j]=0;
        }
    }
    return tab_seuil;
}

/// BEGIN doubleSeuillage

/** Filtre de double seuillage
 * @param imgIntensite image d'intensite
 * @param imgContour image codant un ensemble de pixels selectionnes
 * @param seuil un entier de l'intervalle [0,255]
 * @return une copie d'imgIntensite modifiee de sorte que:
 *  -si teinte > seuil et voisin d'un pixel de imgContour, alors pixel noir
 *  -sinon pixel blanc
 **/

// Ici, un voisin correspond à tout ce qu'il y a autour du pixel au milieu. ( Comme un carré avec le pixel au milieu)
ImageGris doubleSeuillage(ImageGris imgIntensite, ImageGris imgContour, int seuil) {
    
     if (seuil<0 or seuil > 255)
        throw runtime_error("Le seuil est invalide ! ");
    
    int ligne=imgIntensite.size();
    int colonne= imgIntensite[0].size();
    
    ImageGris tab_doubleSeuil;
    tab_doubleSeuil= ImageGris(ligne);
    for (int i=0;i<ligne;i++)
        tab_doubleSeuil[i]= vector<double>(colonne);
    
 
    for (int i = 0; i < ligne; i++) {
        for (int j = 0; j < colonne; j++) {

           /** Pour verifier si  le pixel est supérieur au seuil ET si au moins un voisin est dans imgContour est noir (0) **/
            
            if ((imgIntensite[i][j] > seuil) and 
((i > 0 and j > 0 and imgContour[i-1][j-1] == 0) or 
// voisin haut gauche
                
(i > 0 and imgContour[i-1][j] == 0) or // voisin haut milieu
                
(i > 0 and j < colonne-1 and imgContour[i-1][j+1] == 0) or // voisin haut-droite
                
(j > 0 and imgContour[i][j-1] == 0) or // voisin milieu gauche
// On va pas mettre le pixel tout au centre  vue que c'est le pixel dont on cherche les voisins.

(j < colonne-1 and imgContour[i][j+1] == 0) or 
// voisin droite
                    
(i < ligne-1 and j > 0 and imgContour[i+1][j-1] == 0) or // voisin bas gauche

(i < ligne-1 and imgContour[i+1][j] == 0) or        
// voisin bas milieu

(i < ligne-1 and j < colonne-1 and imgContour[i+1][j+1] == 0) // voisin basdroite
                )
            )
                tab_doubleSeuil[i][j] = 0;  // on met pixel noir
            else
                tab_doubleSeuil[i][j] = 255; // sinon, c est  blanc
        }
    }

    return tab_doubleSeuil;
}

/// BEGIN doubleSeuillageIteratif

/** Filtre de double seuillage iteratif
 * @param imgIntensite image d'intensité
 * @param seuilFort un entier de l'intervalle [0,255]
 * @param seuilFaible un entier de l'intervalle [0,255]
 * @param nbAmeliorations un entier non negatif: le nombre d'itérations
 * @return le double seuillage de img
 **/
                
ImageGris doubleSeuillage(ImageGris imgIntensite, int seuilFort, int seuilFaible, int nbAmeliorations) {
        
        if (seuilFort < 0 or seuilFort > 255 or seuilFaible < 0 or seuilFaible > 255)
        throw runtime_error("Les seuils sont invalides ! ");


        if (nbAmeliorations<0) 
        	throw runtime_error("Un nombre d'itérations négatives ?! ");

        int ligne= imgIntensite.size();
        int colonne= imgIntensite[0].size();
        
                
        ImageGris seuil_iteratif= seuillage(imgIntensite,seuilFort); // pixels supérieurs au seuil fort
       
// Va faire nbAmeliorations de fois la fonction doubleSeuillage 
        for ( int k=0 ;k < nbAmeliorations; k++ ){
ImageGris seuillageFaible=doubleSeuillage(imgIntensite,seuil_iteratif,seuilFaible);
        // Va calculer leurs voisins d'intensité sup à seuilFaible jusqu'a un voisin succesif i fois et va prendre tous les pixels qui sont d'intensité supérieure à seuilFaible. Si c'est supérieur au seuil et qu'il y a au moins un voisin qui est 0, alors le pixel est = 0.
            
            for (int i=0;i<ligne;i++){
                for( int j=0;j<colonne;j++){
                    if (seuillageFaible[i][j]==0){
                        seuil_iteratif[i][j]=0;
                    }
                }       
            }
        }
        return seuil_iteratif;       
}


void seuillageTest() {
    CHECK( ImageGrisEgal(seuillage( imgGrisTest, 80),
              ImageGris( {
                  {255, 0, 255, 0},
                  {255, 0, 0, 0},
                  {0, 0, 0, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
    CHECK( ImageGrisEgal(seuillage( intensite(imgGrisTest), 80),
              ImageGris( {
                  {255, 255, 255, 255},
                  {255, 0, 0, 255},
                  {255, 255, 0, 255},
                  {255, 255, 255, 255}
              }),
              0.001) );
    CHECK( ImageGrisEgal(doubleSeuillage(intensite(imgGrisTest), 200, 80, 4 ),
                         ImageGris( {
                              {255, 255, 255, 255},
                              {255, 0, 0, 255},
                              {255, 255, 0, 255},
                              {255, 255, 255, 255}
                          }),
                          0.001) );


    cout << "Vérifier que les images obtenues dans 'seuillage/' sont semblables à celles fournies dans 'seuillage/correction/'" << endl;
    ecrirePGM(seuillage(intensite(lirePGM("images/Billes.256.pgm")), 80), "seuillage/Billes.256.pgm");
    ecrirePGM(seuillage(intensite(lirePGM("images/Willis.512.pgm"  )), 110), "seuillage/Willis.512.pgm");
    cout << "\tProposer des seuils pour Embryos.512.pgm et House.256.pgm" << endl;


ecrirePGM(seuillage(intensite(lirePGM("images/Embryos.512.pgm")), 50), "seuillage/Embryos.512.pgm"); 
    ecrirePGM(seuillage(intensite(lirePGM("images/House.256.pgm")), 100), "seuillage/House.256.pgm");
}

                
void doubleSeuillageTest(){
    cout << "Vérifier que les images obtenues dans 'seuillage_double/' sont semblables à celles fournies dans 'seuillage_double/correction/'" << endl;
    ecrirePGM(doubleSeuillage(lirePGM("images/Willis.512.pgm"), seuillage(intensite(lirePGM("images/Willis.512.pgm")), 100), 80), "seuillage_double/Willis.512.pgm");
    ecrirePGM(doubleSeuillage(lirePGM("images/Billes.256.pgm"), seuillage(intensite(lirePGM("images/Billes.256.pgm")), 100), 80), "seuillage_double/Billes.256.pgm");
    cout << "\tProposer des seuils pour Embryos.512.pgm et House.256.pgm" << endl;
//  POUR EX 3.4 : en dessous: 
    ecrirePGM(doubleSeuillage(lirePGM("images/Embryos.512.pgm"), seuillage(intensite(lirePGM("images/Embryos.512.pgm")), 150), 50), "seuillage_double/Embryos.512.pgm");

                ecrirePGM(doubleSeuillage(lirePGM("images/House.256.pgm"), seuillage(intensite(lirePGM("images/House.256.pgm")), 200), 100), "seuillage_double/House.256.pgm");
    
    


                
}

void doubleSeuillageIteratifTest() {
    cout << "Vérifier que les images obtenues dans 'seuillage_double/' sont semblables à celles fournies dans 'seuillage_double/correction/'" << endl;
    ecrirePGM(doubleSeuillage(intensite(lirePGM("images/Willis.512.pgm")), 200, 80, 100), "seuillage_double/iteratif_Willis.512.pgm");

    cout << "\tProposer des seuils pour Billes.256.pgm, Embryos.512.pgm et House.256.pgm" << endl;

// À FAIRE ET REMPLIR
ecrirePGM(doubleSeuillage(intensite(lirePGM("images/Billes.256.pgm")), 250, 75, 150), "seuillage_double/iteratif_Billes.256.pgm");

ecrirePGM(doubleSeuillage(intensite(lirePGM("images/Embryos.512.pgm")), 150, 100, 125), "seuillage_double/iteratif_Embryos.512.pgm");

ecrirePGM(doubleSeuillage(intensite(lirePGM("images/House.256.pgm")), 200, 80, 100), "seuillage_double/iteratif_House.256.pgm");



    
}


int main(){
    // Ajouter les appels aux fonctions de test nécessaire

    renormaliseTest();
    seuillageTest();
    doubleSeuillageTest();
    doubleSeuillageIteratifTest();
    lissageTest();


    return 0;
}

