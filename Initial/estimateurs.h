#pragma once

#include "outils.h"
#include "cellules.h"

using namespace std;



int cardinal(IntTree* tree, int generation);//Cardinal de l'arbre jusqu'à génération incluse.

//Relatif aux estimateurs, voir papier pour plus de précisions.
void somme_taux_croissance(IntTree* tree, int r, long double & result);
void somme_taux_croissance_carree(IntTree* tree, int r, long double& result);
void somme_taux_croissance_next(IntTree* tree, int eps, int r, long double& result);
void somme_taux_croissance_croise(IntTree* tree, int eps, int r, long double& result);

//Estimateurs
long double estim_alpha_eps_r(IntTree* tree, int eps, int r);
long double estim_beta_eps_r(IntTree* tree, int eps, int r);

//Detecting of cellular aging (propositions 35, 36 et 37 dans Guyon)
long double estim_alpha_barre_r(IntTree* tree, int r);
long double estim_beta_barre_r(IntTree* tree, int r);
void estim_sigma2_r(IntTree* tree, int r, long double& result); //Attention, on a pas renormalisé par 2*Card(Tr) pour éviter d'appeler la fonction cardinal à chaque récursion.
void estim_rho_r(IntTree* tree, int r, long double& result); //Pareil, on a pas renormalisé par sigma2*Card(Tr)
long double estim_mu1_r(IntTree* tree, int r);
long double estim_mu2_r(IntTree* tree, int r);

//Proposition 35 de Guyon
long double stat35(IntTree* tree, int r);
//Proposition 36 de Guyon
long double stat36(IntTree* tree, int r);
//Proposition 37 de Guyon
//long double stat37(IntTree* tree, int r); // trop chiante, on ne la fera pas.

void histo35(int r);
void histo36(int r);

