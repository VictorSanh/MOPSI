#include "estimateurs.h"

//Fonction qui donne une certaine seuil qui sera comparé à proba_mort, pour simuler aléatoirement la mort des cellules
//en fonction de leur age.
//Modélisation qui est pour le moment linéaire, c'est donc à affiner.
double modelisation_mort_age(int age_old){
	double x = ((double)rand() / (RAND_MAX));
	//cout << x << endl;
	x += 0.001*age_old;
	//cout << x << endl;
	return x;
}

int cardinal(IntTree* tree, int generation){
	// retourner le cardinal de l'arbre jusqu'à la génération "generation"
	if ((*tree).generation > generation){ return 0; }
	else{
		int fils = tree->nbSons();
		int card = 0;
		for (int i = 0; i<fils; i++){
			card += cardinal(tree->getSon(i), generation);
		}
		return 1 + card;
	}
}


//Les estimateurs de alpha.
void somme_taux_croissance(IntTree* tree, int r, double& result){
	if (tree->getGeneration() <= r){
		result += (*tree).taux_croissance;
		for (int k = 0; k < tree->nbSons(); k++){
			somme_taux_croissance(tree->getSon(k), r, result);
		}
	}
}
void somme_taux_croissance_carree(IntTree* tree, int r, double& result){
	if (tree->getGeneration() <= r){
		result += (*tree).taux_croissance*(*tree).taux_croissance;
		for (int k = 0; k < tree->nbSons(); k++){
			somme_taux_croissance(tree->getSon(k), r, result);
		}
	}
}
void somme_taux_croissance_next(IntTree* tree, int eps, int r, double& result){
	assert(tree->nbSons() >= eps);
	if (tree->getGeneration() <= r){
		result += (*tree->getSon(eps)).taux_croissance;
		somme_taux_croissance_next(tree->getSon(0), eps, r, result);
		somme_taux_croissance_next(tree->getSon(1), eps, r, result);
	}
}
void somme_taux_croissance_croise(IntTree* tree, int eps, int r, double& result){
	assert(tree->nbSons() >= eps);
	if (tree->getGeneration() <= r){
		result += (*tree->getSon(eps)).taux_croissance*(*tree).taux_croissance;
		somme_taux_croissance_croise(tree->getSon(0), eps, r, result);
		somme_taux_croissance_croise(tree->getSon(1), eps, r, result);
	}
}
double estimateur_alpha_eps_r(IntTree* tree, int eps, int r){
	int card = cardinal(tree, r);
	card = float(card);
	double somme = 0;
	double somme_croisee = 0;
	double somme_next = 0;
	double somme_carree = 0;
	somme_taux_croissance(tree, r, somme);
	somme_taux_croissance_croise(tree, eps, r, somme_croisee);
	somme_taux_croissance_next(tree, eps, r, somme_next);
	somme_taux_croissance_carree(tree, r, somme_carree);

	double gros = (somme_carree / card - (somme*somme_next) / (card*card)) / (somme_carree / card - (somme / card)*(somme / card));
	return gros;
}

double estimateur_beta_eps_r(IntTree* tree, int eps, int r){
	int card = cardinal(tree, r);
	card = float(card);
	double somme_next = 0;
	double somme = 0;
	double alpha_zero_r = estimateur_alpha_eps_r(tree, 0, r);
	somme_taux_croissance_next(tree, eps, r, somme_next);
	somme_taux_croissance(tree, r, somme);

	double gros = somme_next / card - (alpha_zero_r*somme) / card;
	return gros;
}