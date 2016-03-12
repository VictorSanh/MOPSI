#include <iostream>
#include "cellules.h"
#include "estimateurs.h"

using namespace std;

int prof_de_test = 8;
int main()
{
	InitRandom();
	//Initialisation sans bruit, voire constructeur pour enlever les bruits suivants.
	//IntTree* root = new IntTree(0, 0, 1, 0,0) ;
	//Initialisation avec bruit.
	/*IntTree* root = new IntTree(0, 0, 1, 0, gaussienne(0, 1)); //On initialise à age_new = 0, age_old = 0 et taux_croissance = 1 et generation = 0.
	construitArbre(root, prof_de_test + 1);
	long double alpha0 = estim_alpha_eps_r(root, 0, prof_de_test);
	long double alpha1 = estim_alpha_eps_r(root, 1, prof_de_test);
	long double bet0 = estim_beta_eps_r(root, 0, prof_de_test);
	long double bet1 = estim_beta_eps_r(root, 1, prof_de_test);
	cout << alpha0 << alpha1 << beta0 << beta1 << endl;
	estim_bruit(root, prof_de_test, alpha0, beta0, alpha1, beta1);
	cout <<"Racine" <<(*root).estim_bruit << (*root).bruit << endl;
	cout << (*root->getSon(0)).estim_bruit << endl;
	cout << "Statistique de test 35 : " << stat36(root, prof_de_test)  << endl;*/

	openWindow(1200, 650);
	histo35(10);

	click();
	endGraphics();

	//root->~IntTree();
	return 0;

}

