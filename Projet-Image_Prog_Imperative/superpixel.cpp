#include <stdexcept>
/** @file
 * Filtre Super Pixel
 **/
#include <cmath>
#include "superpixel.hpp"

/** Structure de donnee representant un point dans l'espace
spacio colorimetrique **/
typedef vector<double> Point;

/** Structure de donnee representant un ensemble de points dans l'espace
    spacio colorimetrique **/
typedef vector<Point> EnsemblePoints;

double distancePoints(Point p, Point c) {
    double somme=0;
    for (int i=0;i<p.size();i++){
        double distance= c[i]-p[i];
        somme+= distance*distance;
        
    }
    return sqrt(somme);
}

double distanceAEnsemble(Point p, EnsemblePoints C) {
  
    double Minimum_distance= distancePoints(p,C[0]); 
    /** On calcule déjà le minimum entre p et le premier de C pour ensuite parcourir la liste et comparer.
 si on un nouveau minimum alors on remplace l'ancien minimun stocké dans la variable
    **/

    for (int i=1;i<C.size();i++){
        double testMinimum= distancePoints(p,C[i]);
        if ( testMinimum< Minimum_distance){
            Minimum_distance=testMinimum;
        }
    }
    return  Minimum_distance;
    
}

int plusProcheVoisin(Point p, EnsemblePoints C) {
    double Minimum_distance= distancePoints(p,C[0]);
    int index=0; // On cherche l'indice qui renvoie le mininum de distance
    

    for (int i=1;i<C.size();i++){
        double testMinimum= distancePoints(p,C[i]);
        if ( testMinimum< Minimum_distance){
            Minimum_distance=testMinimum;
            index=i;
        }
    }
    return index;
    
}


EnsemblePoints sousEnsemble(EnsemblePoints P,EnsemblePoints C,int k){
// Remplie l'ensemble de pt . Tous les points de p regardent le centre le plus proche; tOUS LES POINTS DONT LE CENTRE est c[k].{
    
    EnsemblePoints sous_ensemble;
    for (int i=0;i<P.size();i++){
        if (plusProcheVoisin(P[i],C)==k) {
            sous_ensemble.push_back(P[i]);
        }
        
    }
    return sous_ensemble;
    
}

Point barycentre(EnsemblePoints Q) {
    Point b;
   for (int k=0; k <Q[0].size(); k++){
        double somme = 0;
        int coeff = 0;
        for (int i=0; i<Q.size(); i++){
            somme = somme + Q[i][k];
            coeff++;
        }
        b.push_back(somme / coeff);
    }
    return b;
}


EnsemblePoints KMoyenne(EnsemblePoints P,EnsemblePoints C, int nbAmeliorations) {
    /**L’algorithme consiste à effectuer plusieurs fois une amélioration. Chaque amélioration est en deux phases:

Chaque point est associé au point pilote le plus proche;

Chaque point pilote est déplacé au barycentre de l’ensemble des points qui lui sont associés. (d'après énoncé )

Autrement dit, son but est de déplacer progressivement les centres C pour qu’ils soient au milieu des groupes de points P.

En sortie, elle renvoie les nouveaux centres finaux.
    **/

    
    for (int n = 0; n < nbAmeliorations; n++) {
        // Chaque tour= 1 itération de KMoyenne
        EnsemblePoints ancien_C = C; // pour garder les anciens centres car on veut modifier les ancien  points et pas les nouveaux.
        for (int k = 0; k < C.size(); k++) {
        // Re calculer ou le centre doit se déplacer
            EnsemblePoints Q = sousEnsemble(P, ancien_C, k); // c'est les points proches du centre k
            /** Sous ensemble: Elle renvoie tous les points de P qui sont plus proches du centre k que des autres centres. PlusProcheVoisin calcule le centre le plus proche. Si ce centre a l’indice k, alors p est ajouté dans Q
            **/
            C[k] = barycentre(Q); // on met à jour le centre avec le barycentre (, il prend la moyenne des coordonnées). Le centre c[k] se met au milleu des coordonnées de Q
        }
    }
    return C; // renvoie les centre finaux
}
 /** "Pendant plusieurs tours, pour chaque centre, je prends tous les points qui lui sont les plus proches (grâce à sousEnsemble, plusProcheVoisin et distancePoints), puis je déplace le centre au milieu de ces points avec barycentre."
 **/

EnsemblePoints FAST_KMoyenne(EnsemblePoints P,EnsemblePoints C, int nbAmeliorations) {
    vector<int> label;
    label.resize(P.size());
    for(int n=0; n<nbAmeliorations; n++) {
        vector<int> clusterSize;
        clusterSize.resize(C.size(),0);
        for (int p=((int)P.size())-1; p>=0; p--) {
            double di = 0;
            int nn=0;
            for(int d=((int)P[0].size())-1; d>=0; d--)
                di+=(P[p][d]-C[0][d])*(P[p][d]-C[0][d]);
            for(int c=((int)C.size())-1; c>=1; c--) {
                double dt=0;
                for(int d=((int)P[0].size())-1; d>=0; d--)
                    dt+=(P[p][d]-C[c][d])*(P[p][d]-C[c][d]);
                if(dt<di) {
                    di=dt;
                    nn=c;
                }
            }
            label[p]=nn;
            clusterSize[nn]++;
        }
        for (int p=((int)P.size())-1; p>=0; p--)
            for(int d=((int)P[0].size())-1; d>=0; d--)
                C[label[p]][d]+=P[p][d];
        for(int c=((int)C.size())-1; c>=0; c--)
            if(clusterSize[c]!=0)
                for(int d=((int)P[0].size())-1; d>=0; d--)
                    C[c][d] = C[c][d]/(clusterSize[c]+1);
    }
    return C;
}

EnsemblePoints pivotSuperPixel(Image img, double lambda, int mu) {
    EnsemblePoints ens_pts;
    for (int a=0; a*mu<img.size(); a++){
        for (int b=0; b*mu<img[0].size(); b++){
             Point B;
    /** Un point est de forme: (i,j,λr,λg,λb) 
        avec i,j = mu*a et mu*b
        **/
        
            B.push_back(mu*a);
            B.push_back(mu*b);
            B.push_back(lambda*img[mu*a][mu*b].r);
            B.push_back(lambda*img[mu*a][mu*b].g);
            B.push_back(lambda*img[mu*a][mu*b].b);
            ens_pts.push_back(B);
        }
    }

    return ens_pts;
}


    
    /**
    int ligne= img.size();
    int colonne= img[0].size();
    EnsemblePoints Ensemblepoints;
    for (int i= 0; i<ligne; i+=mu){
        for (int j=0;j<colonne;j+=mu){
             i+=mu et j+=mu, c'est pareil que mu*a et mu* b avec a et b = 0,1,2,3,4,5
                
            Point stock_points;
            // D'apres énoncé : point(i,j,r,g,b)
            stock_points.push_back(i);
            stock_points.push_back(j);
            stock_points.push_back(lambda*img[i][j].r);
            stock_points.push_back(lambda*img[i][j].g);
            stock_points.push_back(lambda*img[i][j].b);
            Ensemblepoints.push_back(stock_points);              
        }
    }
    return Ensemblepoints;
}
**/
EnsemblePoints superPixels(Image img,double lambda, int mu, int nbAmeliorations) {
    // Remplacez cette ligne et la suivante par le code adéquat
    throw runtime_error("Fonction superPixels non implantée ligne 79");
}

Image superPixel(Image img, double lambda, int mu, int nbAmeliorations) {
    // Remplacez cette ligne et la suivante par le code adéquat
    throw runtime_error("Fonction superPixel non implantée ligne 84");
}



// Ecrire votre code ici


