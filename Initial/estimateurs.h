#pragma once

#include "outils.h"
#include "cellules.h"

using namespace std;

//Constantes pour les taux de croissance
const double alpha0 = 0.5;
const double alpha1 = 0.5;
const double beta0 = 0.5;
const double beta1 = 0.5;

const double p10 = 0.8; // proba de se diviser en deux fils qui ne meurent pas
const double p1 = 0.05;//proba de se diviser en deux fils dont le nouveau meurt
const double p0 = 0.1; // proba de se diviser en deux fils dont le vieux meurt

const double proba_deces = 1 - (p10 + p1 + p0);

long int cardinal(IntTree* tree, int generation);//Cardinal de l'arbre jusqu'à génération incluse.

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

