#include <stdexcept>
/** @file
 * Affichage d'une image PBM
 **/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/// BEGIN affichePBM

/** Affiche une image binaire PBM à l'écran avec ' ' pour 0 et '@' pour 1
 * @param source le nom d'un fichier PBM
 **/
void affichePBM(string source)  {
    
    ifstream flux;
    flux.open(source);
    string formatP1;
    flux >> formatP1;
    int colonne;
    int ligne;
    flux >> colonne >> ligne;
    int entier;
    for(int i=0;i<ligne;i++){
        for(int j=0;j<colonne;j++){
            flux>>entier;
            if (entier==0){
                cout << "  ";
            }    
            else {
                cout << "@ ";
            }
           
        }
        cout<<endl;
        
     }   
     

    flux.close();
}

/** Echange le noir et le blanc dans une image PBM
 * @param source le nom du fichier PBM à lire
 * @param cible le nom du nouveau fichier PMB créé
 **/

void inversePBM(string source, string cible) {
    // Ici pour faire l'inverse de l'entier, on peut juste faire (1-entier) car 1-0=1 et 1-1=0
    
    ifstream flux1;
    ofstream flux2;
    
    flux1.open(source);
    flux2.open(cible);
   
    string formatP1;
    flux1 >> formatP1;
    int colonne;
    int ligne;
    flux1 >> colonne >> ligne;

    flux2 << formatP1 << endl;
    flux2 << colonne << " " << ligne <<endl;
    int entier;

    for (int i=0;i<ligne;i++){
        for (int j=0;j<colonne;j++){
            flux1 >> entier;
            flux2 << 1-entier<<" ";
        }   
        flux2 << endl;
    } 
    flux1.close();
    flux2.close();
}


int main(){
    cout << "Affichage du smiley " << endl;
    affichePBM("./images/smiley.pbm");
    cout << "Fabrication du smiley inversé (vérifiez que le nouveau fichier a été créé dans le dossier pbm/smiley-inverse.pbm" << endl;
    inversePBM("images/smiley.pbm","pbm/smiley-inverse.pbm");
    cout << "Affichage du smiley inversé" << endl;
    affichePBM("./pbm/smiley-inverse.pbm");
    return 0;
}

