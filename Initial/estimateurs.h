#pragma once

#include "outils.h"
#include "cellules.h"

using namespace std;

//Constantes pour les taux de croissance
const double alpha0 = 0.8;
const double alpha1 = 0.7;
const double beta0 = 0.6;
const double beta1 = 0.5;

const double p10 = 0.8; // proba de se diviser en deux fils qui ne meurent pas
const double p1 = 0.05;//proba de se diviser en deux fils dont le nouveau meurt
const double p0 = 0.1; // proba de se diviser en deux fils dont le vieux meurt

const double proba_deces = 1 - (p10 + p1 + p0);

//Relatif aux estimateurs, voir papier pour plus de précisions.
void somme_taux_croissance(IntTree* tree, int r, double& result);
void somme_taux_croissance_carree(IntTree* tree, int r, double& result);
void somme_taux_croissance_next(IntTree* tree, int eps, int r, double& result);
void somme_taux_croissance_croise(IntTree* tree, int eps, int r, double& result);

//Estimateurs
double estimateur_alpha_eps_r(IntTree* tree, int eps, int r);
double estimtaeur_beta_eps_r(IntTree* tree, int eps, int r);