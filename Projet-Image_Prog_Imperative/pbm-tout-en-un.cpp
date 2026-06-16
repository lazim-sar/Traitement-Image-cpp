#include <stdexcept>
/** @file
 * Lecture et ecriture d'images binaires au format PBM
 **/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/// BEGIN ImageNB
/** Structure de données pour représenter une image binaire **/
typedef vector<vector<int> > ImageNB;
/// END ImageNB

/// BEGIN lirePBM

/** Construire une image binaire depuis un fichier PBM
 * @param source le nom d'un fichier PBM
 * @return une image binaire (0/1)
 **/
ImageNB lirePBM(string source) {
    ifstream PBM;
    PBM.open(source);
    if (not PBM)
        throw runtime_error("Fichier non trouve: "+source);
   
    string formatP1;
    PBM >> formatP1;
    int colonne, ligne;
    PBM >> colonne >> ligne;
    
    ImageNB image;// On déclare un novueeau tableau inverse
    image=ImageNB(ligne); // On ajoute les lignes
    
    for (int i=0;i<ligne;i++)
        image[i]=vector<int>(colonne); // On ajoute à chaque ligne des colonnes de taille (colonne)
    
    int entier;
    for (int k=0;k<image.size();k++){
        for(int j=0;j<image[k].size();j++){
            PBM >> entier;
            image[k][j]=entier;
        }
    }
    PBM.close();
    return image;    
}

/// BEGIN ecrirePBM

/** Ecrit une image binaire dans un fichier PBM
 * @param img une image binaire (0/1)
 * @param cible le nom d'un fichier PBM
 **/
void ecrirePBM(ImageNB img, string cible) {
    ofstream PBM;
    PBM.open(cible);
    int ligne= img.size(); // Cela correspond au nombre de ligne de l'image
    int colonne=img[0].size(); // Nombre de colonne dans une ligne. On prend la 1 ère ligne car c'est suffisant. Même N° de colonnes pour chaque ligne 
    PBM << "P1" << endl;
    PBM << colonne << " " << ligne << endl;

    for (int i=0; i<ligne; i++){
        for (int k=0; k<colonne; k++){
            PBM << img[i][k] << " ";
        }
        PBM << endl;
    }
    PBM.close();
}


/// BEGIN affichePBM

/** Affiche une image binaire PBM à l'écran avec ' ' pour 0 et '@' pour 1
 * @param img une image binaire (0/1)
 **/
// On cherche juste à afficher une image donnée et donc pas besoin de lire

void affichePBM(ImageNB img) {
    int ligne= img.size(); // Cela correspond au nombre de ligne de l'image
    int colonne=img[0].size(); // Nombre de colonne dans une ligne. On prend la 1 ère ligne car c'est suffisant. Même N° de colonnes pour chaque ligne 
    for (int i=0; i<ligne; i++){
        for (int k=0; k<colonne; k++){
            if (img[i][k]==0)
                cout << "  ";  
            else 
                cout << "@ ";
        }
        cout << endl;
    }
}

/// BEGIN inversePBM

/** Echange le noir et le blanc dans une image PBM
 * @param img une image binaire (0/1)
 * @return l'image où le blanc et le noir ont été inversés
 **/
ImageNB inversePBM(ImageNB img) {
    int ligne= img.size(); // Cela correspond au nombre de ligne de l'image
    int colonne=img[0].size(); // Nombre de colonne dans une ligne. On prend la 1 ère ligne car c'est suffisant. Même N° de colonnes pour chaque ligne 
    ImageNB img_inverse; // On déclare un novueeau tableau inverse
    img_inverse= ImageNB(ligne,vector<int>(colonne)); // On ajoute les lignes et les colonnes 
    
    for (int i=0; i<ligne; i++){
        for (int k=0; k<colonne; k++){
            img_inverse[i][k]= 1-img[i][k];
        }
    }
    return img_inverse;
    
}

void testLirePBM(){
    cout << "Vérifier que les images obtenues dans 'pbm/' sont semblables à celles fournies dans 'pbm/correction/'" << endl;
    ecrirePBM(lirePBM("images/smiley.pbm"),  "pbm/smiley.pbm");
    ecrirePBM(lirePBM("images/cercle.pbm"),  "pbm/cercle.pbm");
    ecrirePBM(lirePBM("images/code.pbm"), "pbm/code.pbm");
    ecrirePBM(lirePBM("images/damier.pbm"), "pbm/damier.pbm");
}

// On va reprendre le int main du fichier pbm-affiche.cpp mais en modifiant les fonctions qu'on veut appeler
int main(){
    testLirePBM();
    
    cout << "Lecture du smiley..." << endl;
    ImageNB img = lirePBM("images/smiley.pbm");

    cout << "Affichage du smiley :" << endl;
    affichePBM(img);

    cout << "Inversion de l'image..." << endl;
    ImageNB imgInverse = inversePBM(img);

    cout << "Affichage du smiley inversé :" << endl;
    affichePBM(imgInverse);

    cout << "Sauvegarde du smiley inversé..." << endl;
    ecrirePBM(imgInverse, "pbm/smiley-inverse.pbm");

    return 0;
}


