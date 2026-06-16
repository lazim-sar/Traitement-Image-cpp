#include <stdexcept>
/** @file
 * Filtres de conversion couleur <-> teintes de gris
 **/

#include <iostream>
using namespace std;
#include "pgm.hpp"
#include "sobel.hpp"
#include "seuillage.hpp"
#include "image-test.hpp"


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

    
    seuillageTest();
    doubleSeuillageTest();
    doubleSeuillageIteratifTest();

    //  On doit ABSOLUMENT ENLEVER LE RENORMALISE DANS LES FICHIERS DE SEUILLAGE CAR ON L'UTILISE 2 FOIS (  DANS SOBEL ET DANS SEUILLAGE) ET COMME LE FICHIER SEUILLAGE DEPEND DE SOBEL ALORS ON ENLEVE DANS SEUILLAGE.

    return 0;
}
