#include <stdexcept>
/** @file
 * Filtre Super Pixel
 **/


#include <cmath>
#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

#include "superpixel.hpp"
#include "pgm.hpp"
#include "ppm.hpp"
#include "gris-couleurs.hpp"
#include "image-test.hpp"




void distancePointsTest() {

    CHECK( distancePoints( Point( {2,0,1}), Point( {2,0,1})) == 0);
    CHECK( distancePoints( Point( {1,0,1}), Point( {1,0,0})) == 1);
    CHECK( distancePoints( Point( {2,2,2,2}), Point( {1,1,1,1})) == 2);
}

void plusProcheVoisinTest() {
    CHECK( plusProcheVoisin( Point( {1,0,1}),
                              EnsemblePoints( { Point({2,3,6}), Point({1,0,0}), Point({-1,2,0})}))
        == 1);
}

void testBarycentre() {
    

    EnsemblePoints Q = { {0,0}, {2,2}, {4,4} };
    Point b = barycentre(Q);

    CHECK(b[0] == 2 and b[1] == 2);
}
    
void pivotSuperPixelTest() {
    Image img(2, vector<Couleur>(2)); //  ici on met Couleur, pas Pixel

    img[0][0] = {10, 20, 30};
    img[0][1] = {40, 50, 60};
    img[1][0] = {70, 80, 90};
    img[1][1] = {100, 110, 120};

    double lambda = 1.0;
    int mu = 1;

    EnsemblePoints res = pivotSuperPixel(img, lambda, mu);

    CHECK(res.size() == 4);
    CHECK(res[0] == Point({0,0,10,20,30}));
    CHECK(res[1] == Point({0,1,40,50,60}));
    CHECK(res[2] == Point({1,0,70,80,90}));
    CHECK(res[3] == Point({1,1,100,110,120}));
}


/** Test du filtre SuperPixel **/
void superPixelTest() {
    // TODO: beaucoup d'étudiants ont eu 128.91
    CHECK( ImageGrisEgal(CouleurAuGris(superPixel( imgTest, 2, 60, 15 )),
              ImageGris( {
                  {128.91, 128.91, 128.91, 128.91},
                  {128.91, 128.91, 128.91, 128.91},
                  {128.91, 128.91, 128.91, 128.91},
                  {128.91, 128.91, 128.91, 128.91}
                  }),
              0.001) );
    cout << "Vérifier que les images obtenues dans 'superpixel/' sont semblables à celles fournies dans 'superpixel/correction/'" << endl;
    ecrirePPM(superPixel(lirePPM("images/Billes.256.ppm"), 1, 30, 25),  "superpixel/Billes.256.ppm");
    ecrirePPM(superPixel(lirePPM("images/Baboon.512.ppm"), 2, 60, 15),  "superpixel/Baboon.512.ppm");
    ecrirePPM(superPixel(lirePPM("images/Willis.512.ppm"  ), 1, 60, 15),  "superpixel/Willis.512.ppm");

    cout << "Proposer des paramètres pour Embryos.512.ppm et House.256.ppm et ajouter des tests ci-dessous" << endl;
}


void KMoyenneTest(){
    EnsemblePoints P;
    for(int i=0;i<100;i++){
        double xbiais=0.;
        double ybiais=0.;
        if(i%3==1){
            xbiais = 100.;
            ybiais = 0.;
        }
        if(i%3==2){
            xbiais = 0.;
            ybiais = 100.;
        }
        Point p;
        p.push_back(xbiais + 1.*(rand()%10)-20.);
        p.push_back(ybiais + 1.*(rand()%10)-20.);
        P.push_back(p);
    }

    EnsemblePoints C = {
        {75.,50.}, {50., 75.}, {25., 25.}};

    EnsemblePoints Cout = KMoyenne(P,C,100);
    EnsemblePoints CRef = FAST_KMoyenne(P,C,100);

    for(int i=0; i<2; i++)
    for(int j=0; j<2; j++)
        CHECK( abs( Cout[i][j] - CRef[i][j] ) <= 0.5 );
}


// Ecrire votre code ici


int main(){
    cerr << "Tests de la fonction distancePoints" << endl;
    distancePointsTest();
    cerr << "Tests de la fonction plusProcheVoisin" << endl;
    plusProcheVoisinTest();
    
    cerr << "Tests de la fonction barycentre" << endl;
    testBarycentre();

    cerr << "Tests de la fonction KMoyenne" << endl;
    KMoyenneTest();
    cerr << "Tests de la fonction pivotsuperPixel" << endl;
    pivotSuperPixelTest();

    /**cerr << "Tests de la fonction superPixel" << endl;
    
    
    superPixelTest();


     Remplacez cette ligne et la suivante par le code adéquat
    throw runtime_error("code non implanté ligne 99");
    **/

}

