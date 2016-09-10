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
//#include "estimateurs.h"

//Constantes pour les taux de croissance
const double alpha0 = 0.689382;
const double alpha1 = 0.373397;
const double beta0 = 0.0112346;
const double beta1 = 0.012144;

const double p10 = 0.8; // proba de se diviser en deux fils qui ne meurent pas
const double p1 = 0.05;//proba de se diviser en deux fils dont le nouveau meurt
const double p0 = 0.1; // proba de se diviser en deux fils dont le vieux meurt

const double proba_deces = 1 - (p10 + p1 + p0);

using namespace std;
using namespace Imagine;

const int nb_generations = 8;
const int H = pow(2, nb_generations) * 10;
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
	IntTree(int age_new0, int age_old0, double taux_croissance0, int generation0, double bruit0);

	// Return age_new, age_old of this node
	pair<int, int> getData();

	//Destructeur
	~IntTree();

	// Set information of this node
	void setData(int age_new0, int age_old0);


	//Return aliveness of cellule
	bool isAlive();
	void setAlive(bool deadoralive);


	//Return the generation of cellule
	int getGeneration();

	// return aliveness of sons
	bool new_son_alive();
	bool old_son_alive();
	
	//return taux de croissance
	double getTauxCroissance();

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

IntTree* load_experimental();
void load_tab(IntTree* arbre, double tab1[512]);
void liste_taux_simules(stack <double>& pile, queue<IntTree*> file);
void graphicDisplay(IntTree* tree, int generation, int position, int profondeur); //Affichage graphique de l'arbre jusqu'à génération.
void construitArbre(IntTree * tree, int generationMax);//Construit un arbre de profondeur "generationMax", la racine étant la génération 0.
void estim_bruit(IntTree* tree, int r, long double estim_alpha0, long double estim_beta0, long double estim_alpha1, long double estim_beta1); //Fonction HYPER IMPORTANTE avant d'apeller estim_sigma2 ou estim_rho