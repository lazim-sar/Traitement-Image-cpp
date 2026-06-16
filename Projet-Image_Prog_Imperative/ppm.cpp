#include <stdexcept>
/** @file
 * Lecture et écriture d'images au format PPM
 **/


#include <iostream>
#include <fstream>
#include "image.hpp"
#include "ppm.hpp"

/** Structure de donnees pour representer une image **/
typedef vector<vector<Couleur> > Image;


Image lirePPM(string source) {
    ifstream ppm_couleur;
    ppm_couleur.open(source);
    if (not ppm_couleur)
        throw runtime_error("Fichier non trouve: "+source);
   
    string formatP3;
    ppm_couleur >> formatP3;
    int colonne, ligne;
    ppm_couleur >> colonne >> ligne;
    int valeurmax_RGB; // D'après Wikipédia : "Chaque niveau de couleur est codé par une valeur entre 0 et cette valeur maximale en fonction des couleurs principaux : Red,  Green, Blue
    ppm_couleur >> valeurmax_RGB;
   
    // Création d'un tableau 2D en plusieurs étapes pour mieux comprendre.
    Image image_couleur;
    image_couleur= Image(ligne);

    for (int i=0; i<ligne;i++)
        image_couleur[i]=vector<Couleur>(colonne);
    
    int rouge,vert,bleu; // On crée 3 variables pour lire les valeurs r,g,b


    
    // on lit des pixels : chaque pixel a 3 valeurs (R, G, B)
    for (int k=0;k<ligne;k++){
        for(int j=0;j<colonne;j++){
            ppm_couleur >> rouge >> vert >> bleu;
            image_couleur[k][j].r = rouge;
            image_couleur[k][j].g = vert;
            image_couleur[k][j].b = bleu;
        }
    }
    ppm_couleur.close();
    
    return image_couleur;   
}



void ecrirePPM(Image img, string cible) {
    ofstream ppm_couleur;
    ppm_couleur.open(cible);
    
    int ligne= img.size(); // Cela correspond au nombre de ligne de l'image
    int colonne=img[0].size(); // Nombre de colonne dans une ligne. On prend la 1 ère ligne car c'est suffisant. Même N° de colonnes pour chaque ligne 
    ppm_couleur << "P3" << endl; // Correspond au format P3
    ppm_couleur << colonne << " " << ligne << endl; // Nb de colonne et de ligne
    ppm_couleur << 255 << endl; // intensité max du Gris

    for (int i=0; i<ligne; i++){
        for (int k=0; k<colonne; k++){
            ppm_couleur << ((int)img[i][k].r) <<" " <<((int)img[i][k].g) <<" " << ((int)img[i][k].b)<<" " ; // écrit chaque pixels double convertis en int, avec les pixels RGB  par ligne tout en oubliant pas les espaces entre 
            
        }
        ppm_couleur<<"\n"; // Pareil que endl;
    }
    ppm_couleur.close();
}


