#include <iostream>
#include "cellules.h"
#include "estimateurs.h"

using namespace std;

int prof_de_test = 10;
int main()
{
	InitRandom();
	//Initialisation sans bruit, voire constructeur pour enlever les bruits suivants.
	//IntTree* root = new IntTree(0, 0, 1, 0,0) ;
	//Initialisation avec bruit.
	IntTree* root = new IntTree(0, 0, 1, 0, gaussienne(0, 1)); //On initialise à age_new = 0, age_old = 0 et taux_croissance = 1 et generation = 0.
	construitArbre(root, prof_de_test + 1);



	//cout << (*root).esti << endl;
	/*cout << (*root->getSon(0)).taux_croissance << endl;
	cout << (*root->getSon(1)).taux_croissance << endl;
	cout << (*root->getSon(0)->getSon(0)).taux_croissance << endl;
	cout << (*root->getSon(0)->getSon(1)).taux_croissance << endl;
	cout << (*root->getSon(1)->getSon(0)).taux_croissance << endl;
	cout << (*root->getSon(1)->getSon(1)).taux_croissance << endl;*/

	//double result = 0;
	//somme_taux_croissance_croise(root,1,1,result);
	//cout <<result << endl;


	//cout << "Statistiques : " << stat35(root, prof_de_test) << endl;
	estim_bruit(root, 0, 0, 0, 0);

	int card = cardinal(root, prof_de_test);

	long double sigma2 = 0;
	estim_sigma2_r(root, prof_de_test, sigma2);
	sigma2 = sigma2 / (2 * card);

	long double rho = 0;
	estim_rho_r(root, prof_de_test, rho);
	rho = rho / (card*sigma2);

	cout << "Statistique de test 36 : " << stat36(root, prof_de_test)  << endl;
	//cout << "Estimateur de Beta0 : " << estim_beta_eps_r(root, 0, prof_de_test) << endl;
	//cout << "Estimateur de Beta1 : " << estim_beta_eps_r(root, 1, prof_de_test) << endl; //Ca déconne un peu pour beta1...
	//cout << "Estimateur de Alpha0 : " << estim_alpha_eps_r(root, 0, prof_de_test) << endl;
	//cout << "Estimateur de Alpha1 : " << estim_alpha_eps_r(root, 1, prof_de_test) << endl;

	//openWindow(H,H);
	//graphicDisplay(root,0,H/2);
	//endGraphics();
	root->~IntTree();
	return 0;

}

