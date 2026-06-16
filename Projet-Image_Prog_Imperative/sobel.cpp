#include <stdexcept>
/** @file
 * Filtres de Sobel
 **/
#include <cmath>
#include "sobel.hpp"


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



