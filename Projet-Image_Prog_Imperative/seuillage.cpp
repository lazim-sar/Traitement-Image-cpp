#include <stdexcept>
/** @file
 * Filtres de seuillage
 **/

#include <cmath>
#include "image.hpp"
#include "sobel.hpp"




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



