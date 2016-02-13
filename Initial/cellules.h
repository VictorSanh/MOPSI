#include <vector>
#include <string>
#include <Imagine/Graphics.h>
#include <Imagine/Images.h>
#include <iostream>
#include <math.h>
#include <cmath>
#include <ctime> 
#include "outils.h"

using namespace std;
using namespace Imagine;

const int nb_generations=8;
const int H = pow(2,nb_generations)*10;
const int rayon = 5;
const int espace = 60;
const double proba_mort = 0;

//Constantes pour les taux de croissance
const double alpha0 = 0.8;
const double alpha1 = 0.7;
const double beta0 = 0.6;
const double beta1 = 0.5;

const double p10 = 0.8; // proba de se diviser en deux fils qui ne meurent pas
const double p1 = 0.05;//proba de se diviser en deux fils dont le nouveau meurt
const double p0 = 0.1; // proba de se diviser en deux fils dont le vieux meurt

const double proba_deces = 1 - (p10 + p1 + p0);

class IntTree{
public:
		vector <IntTree*> sons;

		int generation;
        int age_new; //age du nouveau pole
        int age_old; //age du vieux pole
		bool alive; //si true, alors la cellule n'est pas morte et peut donner naissance
		double taux_croissance;
		double bruit;

        // Create a node with given information
        IntTree(int age_new0,int age_old0, double taux_croissance0, int generation0, double bruit0);

        // Return information of this node
        pair<int,int> getData();

        //Destructeur
         ~ IntTree();

        // Set information of this node
        void setData(int age_new0,int age_old0);

		//Return aliveness of cellule
		bool isAlive();

        // Return the number of sons of this node
        int nbSons();

        // Return the son at position pos, if any (considering left-most son is at position 0)
        IntTree* getSon(int pos);

        // Replace the exisiting son at position pos with newSon (left-most son at position 0)
        void setSon(int pos, IntTree* newSon);

        // Add newSon as supplementary right-most son of this node
        void addAsLastSon(IntTree* newSon);

        // Remove right-most son of this node
        void removeLastSon();

        //Display : méthode récursive
        void display();

        void newDisplay(int ordre, string prefix = "", string indent = "    ");
};

void graphicDisplay(IntTree* tree,int generation, int position); //Affichage graphique de l'arbre jusqu'à génération.
void construitArbre(IntTree * tree, int generation); //Construit un arbre jusqu'à génération
double modelisation_mort_age(int age_old); //Pour la suite, cette fonction ne servira pas.
int cardinal(IntTree* tree, int generation); //Cardinal de l'arbre jusqu'à génération incluse.

//Relatif aux estimateurs
double somme_taux_croissance(IntTree* tree, int i, int r);
double somme_taux_croissance_next(IntTree* tree, int i, int r);
double somme_taux_croissance_croise(IntTree* tree, int i, int r);