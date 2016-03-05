#include "estimateurs.h"

//Fonction qui donne une certaine seuil qui sera comparé à proba_mort, pour simuler aléatoirement la mort des cellules
//en fonction de leur age.
//Modélisation qui est pour le moment linéaire, c'est donc à affiner.
/*double modelisation_mort_age(int age_old){
	double x = ((double)rand() / (RAND_MAX));
	//cout << x << endl;
	x += 0.001*age_old;
	//cout << x << endl;
	return x;
	}*/

long int cardinal(IntTree* tree, int generation){
	// retourner le cardinal de l'arbre jusqu'à la génération "generation"
	if ((*tree).generation > generation){ return 0; }
	else{
		int fils = tree->nbSons();
		long int card = 0;
		for (int i = 0; i < fils; i++){
			card += cardinal(tree->getSon(i), generation);
		}
		return 1 + card;
	}
}


//Les estimateurs de alpha.
void somme_taux_croissance(IntTree* tree, int r, long double& result){
	if (tree->getGeneration() <= r){
		result += (*tree).taux_croissance;
		for (int k = 0; k < tree->nbSons(); k++){
			somme_taux_croissance(tree->getSon(k), r, result);
		}
	}
}
void somme_taux_croissance_carree(IntTree* tree, int r, long double& result){
	if (tree->getGeneration() <= r){
		result += pow((*tree).taux_croissance, 2);
		for (int k = 0; k < tree->nbSons(); k++){
			somme_taux_croissance_carree(tree->getSon(k), r, result);
		}
	}
}
void somme_taux_croissance_next(IntTree* tree, int eps, int r, long double& result){
	if (tree->getGeneration() <= r){
		assert(tree->nbSons() >= eps);
		result += (*tree->getSon(eps)).taux_croissance;
		for (int k = 0; k < tree->nbSons(); k++){
			somme_taux_croissance_next(tree->getSon(k), eps, r, result);
		}
	}
}
void somme_taux_croissance_croise(IntTree* tree, int eps, int r, long double& result){
	if (tree->getGeneration() <= r){
		assert(tree->nbSons() >= eps);
		result += (*tree->getSon(eps)).taux_croissance*(*tree).taux_croissance;
		for (int k = 0; k < tree->nbSons(); k++){
			somme_taux_croissance_croise(tree->getSon(k), eps, r, result);
		}
	}
}
long double estim_alpha_eps_r(IntTree* tree, int eps, int r){
	int card = cardinal(tree, r);
	card = float(card);
	//cout << "cardinal :  "<<card<< endl;
	long double somme = 0;
	long double somme_croisee = 0;
	long double somme_next = 0;
	long double somme_carree = 0;
	somme_taux_croissance(tree, r, somme);
	//cout <<"somme : " << somme << endl;
	somme_taux_croissance_croise(tree, eps, r, somme_croisee);
	//cout << "somme_croise : " << somme_croisee << endl;
	somme_taux_croissance_next(tree, eps, r, somme_next);
	//cout << "somme_next : "<< somme_next << endl;
	somme_taux_croissance_carree(tree, r, somme_carree);
	//cout << "somme_carree : " << somme_carree << endl;


	long double gros = (somme_croisee / card - (somme*somme_next) / (card*card)) / (somme_carree / card - (somme / card)*(somme / card));
	return gros;
}

long double estim_beta_eps_r(IntTree* tree, int eps, int r){
	int card = cardinal(tree, r);
	card = float(card);
	long double somme_next = 0;
	long double somme = 0;
	long double alpha_zero_r = estim_alpha_eps_r(tree, 0, r);
	somme_taux_croissance_next(tree, eps, r, somme_next);
	somme_taux_croissance(tree, r, somme);

	long double gros = somme_next / card - (alpha_zero_r*somme) / card;
	return gros;
}

long double estim_alpha_barre_r(IntTree* tree, int r){
	long double estim_alpha0 = estim_alpha_eps_r(tree, 0, r);
	long double estim_alpha1 = estim_alpha_eps_r(tree, 1, r);
	return (estim_alpha0 + estim_alpha1) / 2;
}

long double estim_beta_barre_r(IntTree* tree, int r){
	long double estim_beta0 = estim_beta_eps_r(tree, 0, r);
	long double estim_beta1 = estim_beta_eps_r(tree, 1, r);
	return (estim_beta0 + estim_beta1) / 2;
}

void estim_sigma2_r(IntTree* tree, int r, long double& result){
	if (tree->getGeneration() <= r){
		assert(tree->nbSons() >= 2);
		result += pow((*tree->getSon(0)).estim_bruit, 2) + pow((*tree->getSon(1)).estim_bruit, 2);
		for (int k = 0; k < tree->nbSons(); k++){
			estim_sigma2_r(tree->getSon(k), r, result);
		}
	}
}

void estim_rho_r(IntTree* tree, int r, long double& result){
	if (tree->getGeneration() <= r){
		assert(tree->nbSons() >= 2);
		result += (*tree->getSon(0)).estim_bruit*(*tree->getSon(1)).estim_bruit;
		for (int k = 0; k < tree->nbSons(); k++){
			estim_rho_r(tree->getSon(k), r, result);
		}
	}
}

long double estim_mu1_r(IntTree* tree, int r){
	return estim_beta_barre_r(tree, r) / (1 - estim_alpha_barre_r(tree, r));
}

long double estim_mu2_r(IntTree* tree, int r){
	long double alpha0 = estim_alpha_eps_r(tree, 0, r);
	long double alpha1 = estim_alpha_eps_r(tree, 1, r);
	long double beta0 = estim_beta_eps_r(tree, 0, r);
	long double beta1 = estim_beta_eps_r(tree, 1, r);

	long double A = (alpha0*beta0 + alpha1*beta1) / 2;
	long double B = (beta0 + beta1) / 2;
	long double C = (beta0*beta0 + beta1*beta1) / 2;
	long double D = (alpha0*alpha0 + alpha1*alpha1) / 2;
	long double E = (alpha0 + alpha1) / 2;

	long double sigma2 = 0;
	estim_sigma2_r(tree, r, sigma2);
	sigma2 = sigma2 / (2 * cardinal(tree, r));

	return ((2 * A*B / (1 - E) + C + sigma2) / (1 - D));
}

//Proposition 35 de Guyon
long double stat35(IntTree* tree, int r){
	int card = cardinal(tree, r);

	long double sigma2 = 0;
	estim_sigma2_r(tree, r, sigma2);
	sigma2 = sigma2 / (2 * card);

	long double rho = 0;
	estim_rho_r(tree, r, rho);
	rho = rho / (card*sigma2);

	long double alpha0 = estim_alpha_eps_r(tree, 0, r);
	long double alpha1 = estim_alpha_eps_r(tree, 1, r);
	long double beta0 = estim_beta_eps_r(tree, 0, r);
	long double beta1 = estim_beta_eps_r(tree, 1, r);

	long double mu1 = estim_mu1_r(tree, r);
	long double mu2 = estim_mu2_r(tree, r);

	long double gros = pow(alpha0 - alpha1, 2)*(mu2 - mu1*mu1) + pow((alpha0 - alpha1)*mu1 + beta0 - beta1, 2);
	return (card / (2 * sigma2*(1 - rho)))*gros;
}

long double stat36(IntTree* tree, int r){
	int card = cardinal(tree, r);

	long double alpha0 = estim_alpha_eps_r(tree, 0, r);
	long double alpha1 = estim_alpha_eps_r(tree, 1, r);

	long double mu1 = estim_mu1_r(tree, r);
	long double mu2 = estim_mu2_r(tree, r);

	long double sigma2 = 0;
	estim_sigma2_r(tree, r, sigma2);
	sigma2 = sigma2 / (2 * card);

	long double rho = 0;
	estim_rho_r(tree, r, rho);
	rho = rho / (card*sigma2);

	return card*pow(alpha0 - alpha1, 2)*(mu2 - mu1*mu1) / (2 * sigma2*(1 - rho));
}
