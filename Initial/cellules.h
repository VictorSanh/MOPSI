#pragma once

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

class IntTree{
public:
		vector <IntTree*> sons;

		int generation;
        int age_new; //age du nouveau pole
        int age_old; //age du vieux pole
		bool alive; //si true, alors la cellule n'est pas morte et peut donner naissance
		bool new_son_will_live;
		bool old_son_will_live;
		double taux_croissance;
		double bruit;
		double estim_bruit; //cf page 26 de guyon et page 16 de delmas

        // Create a node with given information
        IntTree(int age_new0,int age_old0, double taux_croissance0, int generation0, double bruit0);

        // Return age_new, age_old of this node
        pair<int,int> getData();

        //Destructeur
         ~ IntTree();

        // Set information of this node
        void setData(int age_new0,int age_old0);


		//Return aliveness of cellule
		bool isAlive();
		void setAlive(bool deadoralive);
		

		//Return the generation of cellule
		int getGeneration();

		// return aliveness of sons
		bool new_son_alive();
		bool old_son_alive();

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
void construitArbre(IntTree * tree, int generationMax); //Construit un arbre de profondeur "generationMax", la racine étant la génération 0.
double modelisation_mort_age(int age_old); //Pour la suite, cette fonction ne servira pas.
void estim_bruit(IntTree* tree, long double alpha0, long double beta0, long double alpha1, long double beta1);