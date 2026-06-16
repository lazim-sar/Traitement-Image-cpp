#include <stdexcept>
/** @file
 * Filtres de conversion couleur <-> teintes de gris
 **/
#include "gris-couleurs.hpp"

ImageGris CouleurAuGris( Image img ) {
    int ligne= img.size();
    int colonne= img[0].size();
    ImageGris couleur_gris;
    couleur_gris= ImageGris(ligne);

    for (int i=0; i<ligne;i++)
        couleur_gris[i]=vector<double>(colonne);
     
    for (int i=0; i<ligne; i++){
        for (int j=0; j<colonne; j++){
// On récupère les valeurs r,g,b pour pouvoir l'utiliser dans la formule
            double r = (img[i][j].r);
            double g = (img[i][j].g);
            double b = (img[i][j].b);

// Conversion en niveau de gris selon une formule de luminance standard
            couleur_gris[i][j]=0.2126*r+0.7152*g+0.0722*b;

        }
    }
    return couleur_gris;
}

Image GrisACouleur( ImageGris img ) {
    int ligne= img.size();
    int colonne= img[0].size();
    Image gris_couleur;
    gris_couleur= Image(ligne);

    for (int i=0; i<ligne;i++)
        gris_couleur[i]=vector<Couleur>(colonne);
     
    for (int i=0; i<ligne; i++){
        for (int j=0; j<colonne; j++){
// Copie de la valeur de gris dans les trois canaux (R, G, B)
// Cela transforme l’image en couleur en gris. Chaque valeur de rgb est devenu un même gris.
            gris_couleur[i][j].r = (img[i][j]);
            gris_couleur[i][j].g = (img[i][j]);
            gris_couleur[i][j].b = (img[i][j]);
        }
    }
    return gris_couleur;
            
            
}

