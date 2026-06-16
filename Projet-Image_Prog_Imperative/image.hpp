/** @file
 * Structures de données pour représenter des images
 **/

#ifndef _IMAGE_H
#define _IMAGE_H
#include <vector>
using namespace std;

typedef vector<vector<double> > ImageGris;
typedef vector<vector<int> > ImageNB;



/** Structure de donnees pour representer un pixel en couleur **/
struct Couleur {
    /** Intensite de rouge **/
    double r;
    /** Intensite de vert **/
    double g;
    /** Intensite de bleu **/
    double b;
};

/** Structure de donnees pour representer une image **/
typedef vector<vector<Couleur> > Image;

#endif

